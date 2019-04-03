#include <iostream>
//#include <iomanip>
#include <string>
#include <cmath>

#define POLY_AMOUNT 10 //最多可以同时储存的多项式的数量

//一些错误代码的含义
#define EXPONENT_NOT_INT -1 //多项式的项的指数不为整数
#define DIVIDE_ZERO_POLYNOMIAL -2 //除式为0
#define POWER_SMALLER_THAN_ZERO -3 //次方数小于0
#define DIVIDE_ZERO_NUMBER -4 //除数为0
#define INDEX_OUT_OF_RANGE -5 //索引值越界
#define INDEX_WRONG -6 //此操作无法在索引值所指的多项式上进行
#define OPERATION_OUT_OF_RANGE -7 //操作值越界
#define EXPRESSION_TOO_LOOG -8 //表达式太长
#define LN_NEGATIVE -9 // 函数log(x)的参数不能为负数
#define CAN_NOT_DIVIDE -10 //不能参与多项式除法（因为含有负指数项或函数log(x)）

using std::cin;
using std::cout;
using std::endl;
//using std::setprecision;
//using std::fixed;
using std::string;

//多项式中的某一项
struct item
{
    double base;//底数
    int exponent;//指数
    item *next;//指向下一项的指针
};

//多项式
class polynomial
{
public:
    polynomial()
    {
        head = new item;
        head->next = NULL;
        head->exponent = 0;
        tail = head;
    }

    ~polynomial()
    {
        item *q, *p = head;
        while (p)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }

    //清空多项式的内容
    void empty_poly();

    //深拷贝，使自己拥有和y一样的内容(y可以为空，自己原本的内容会被覆盖)
    void copy_poly(polynomial &y);

    //加入一项(同次数项会被合并，降幂排序)
    void add_item(double i_base, double i_exponent);

    //删除指数为i_exponent的项(如果不存在这样的项，则无任何操作)
    void delete_exponent(int i_exponent);

    //修改指数为i_exponent的项(如果不存在这样的项，则无任何操作)
    //如果i_base==0,效果与delete_exponent(i_exponent)相同
    void change_exponent(double i_base, int i_exponent);

    //自己与另一个多项式y相加，结果存在result中(自己和y都可以为空，result的内容会被覆盖)
    void add_poly(polynomial &y, polynomial &result);

    //自己减另一个多项式y，结果存在result中(自己和y都可以为空，result的内容会被覆盖)
    void subtract_poly(polynomial &y, polynomial &result);

    //自己与另一个多项式y相乘，结果存在result中(自己和y都可以为空，result的内容会被覆盖)
    //自己为空，或y为空，都会导致result为空
    void multiply_poly(polynomial &y, polynomial &result);

    //自己除以另一个多项式y，舍弃余式，结果存在result中(y不可为空，result的内容会被覆盖)
    //如果自己为空，或自己的最高指数小于y的最高指数，则result为空
    void divide_poly(polynomial &y, polynomial &result);

    //自己除以另一个多项式y，余式存在result中(y不可为空，result的内容会被覆盖)
    //如果自己为空，或自己的最高指数小于y的最高指数，则result等于y
    void mod_poly(polynomial &y, polynomial &result);

    //乘方，power为自然数，计算自己的power次方，结果存入result，result的原有内容被覆盖
    //若power!=0且自己为空，则结果为0
    //若power==0，则结果为1
    void power(polynomial &result, int power);

    //微分，结果保存在另一个多项式result中(自己可为空，result中内容会被覆盖)
    void differential(polynomial &result);

    //不定积分，常数项为0，结果保存在另一个多项式result中(自己可为空，result中内容会被覆盖)
    void indefinite_integral(polynomial &result);

    //让自己与某项相乘，自己可为空
    //若i_base==0，则相当于清空自己
    void self_multiply(double i_base, int i_exponent);

    //让自己与多项式y相乘(自己和y都可以为空)
    //y也可以是自己，从而计算自己的平方
    void self_multiply_poly(polynomial &y);

    //让自己与另一个多项式y相减(自己和y都可以为空)
    void self_subtract_poly(polynomial &y);

    //计算自己从x1到x2的定积分的值(自己可为空)
    double definite_integral(double x1, double x2);

    //输入x，计算多项式的值(可为空)
    double calculate(double x);

    //打印出自己的内容
    void print();

    //如果不能参与多项式除法（含有负指数或Ln），返回1，否则返回0
    int can_not_divide();

private:

    //判断浮点数x是否等于0
    int is_zero(double x);

    //快速幂算法，求base的exponent次方
    //exponent为自然数
    double fast_pow(double base, int exponent);

    //在链表尾部加一项(调用此函数时，必须保证此项的指数小于原链表的最小指数)
    //用户不能擅自使用此函数
    void add_item_tail(double i_base, int i_exponent);

    item *head;//指向头结点
    item *tail;//指向多项式的最后一项
};

void polynomial::empty_poly()
{
    item *q, *p = head->next;
    while (p)
    {
        q = p->next;
        delete p;
        p = q;
    }
    head->next = NULL;
    head->exponent = 0;
    tail = head;
}

void polynomial::copy_poly(polynomial &y)
{
    empty_poly();
    item *q = head, *p = (y.head)->next;
    while (p)
    {
        q->next = new item;
        q = q->next;
        q->base = p->base;
        q->exponent = p->exponent;
        p = p->next;
    }
    tail = q;
    tail->next = NULL;
}

void polynomial::add_item(double i_base, double i_exponent)
{
    if (is_zero(i_base)) return;
    if (!is_zero(i_exponent - (int)(i_exponent))) exit(EXPONENT_NOT_INT);
    if (head->next == NULL)
    {
        head->next = new item;
        tail = head->next;
        tail->base = i_base;
        tail->exponent = i_exponent;
        tail->next = NULL;
        return;
    }
    item *q, *p = head;
    while (p->next->exponent > i_exponent)
    {
        if (p->next->next == NULL)
        {
            tail->next = new item;
            tail = tail->next;
            tail->base = i_base;
            tail->exponent = i_exponent;
            tail->next = NULL;
            return;
        }
        p = p->next;
    }
    if (p->next->exponent == i_exponent)
    {
        if (is_zero(p->next->base + i_base))
        {
            q = p->next;
            p->next = q->next;
            delete q;
            if (p->next == NULL)
            {
                tail = p;
            }
            return;
        }
        p->next->base += i_base;
        return;
    }

    //运行到这里时，p->exponent < i_exponent
    q = new item;
    q->base = i_base;
    q->exponent = i_exponent;
    q->next = p->next;
    p->next = q;
}

void polynomial::delete_exponent(int i_exponent)
{
    item *q, *p = head;
    while (1)
    {
        if (p->next == NULL)
        {
            return;
        }
        if (p->next->exponent == i_exponent)
        {
            q = p->next;
            p->next = q->next;
            delete q;
            return;
        }
        p = p->next;
    }
}

void polynomial::change_exponent(double i_base, int i_exponent)
{
    item *p = head;
    while (1)
    {
        if (p->next == NULL)
        {
            return;
        }
        if (p->next->exponent == i_exponent)
        {
            if (is_zero(i_base))
            {
                delete_exponent(i_exponent);
                return;
            }
            p->next->base = i_base;
            return;
        }
        p = p->next;
    }
}

void polynomial::add_poly(polynomial &y, polynomial &result)
{
    item *p = head->next, *q = (y.head)->next;
    result.empty_poly();
    while (1)
    {
        if (p == NULL)
        {
            //把多项式y剩下的所有项添加到result中
            while (q)
            {
                result.add_item_tail(q->base, q->exponent);
                q = q->next;
            }
            return;
        }
        if (q == NULL)
        {
            //把自己剩下的所有项添加到result中
            while (p)
            {
                result.add_item_tail(p->base, p->exponent);
                p = p->next;
            }
            return;
        }
        if (p->exponent > q->exponent)
        {
            result.add_item_tail(p->base, p->exponent);
            p = p->next;
        }
        else if (p->exponent < q->exponent)
        {
            result.add_item_tail(q->base, q->exponent);
            q = q->next;
        }
        else
        {
            result.add_item_tail(p->base + q->base, p->exponent);
            p = p->next;
            q = q->next;
        }
    }
}

void polynomial::subtract_poly(polynomial &y, polynomial &result)
{
    item *p = head->next, *q = (y.head)->next;
    result.empty_poly();
    while (1)
    {
        if (p == NULL)
        {
            //把多项式y剩下的所有项取负值添加到result中
            while (q)
            {
                result.add_item_tail(-(q->base), q->exponent);
                q = q->next;
            }
            return;
        }
        if (q == NULL)
        {
            //把自己剩下的所有项添加到result中
            while (p)
            {
                result.add_item_tail(p->base, p->exponent);
                p = p->next;
            }
            return;
        }
        if (p->exponent > q->exponent)
        {
            result.add_item_tail(p->base, p->exponent);
            p = p->next;
        }
        else if (p->exponent < q->exponent)
        {
            result.add_item_tail(-(q->base), q->exponent);
            q = q->next;
        }
        else
        {
            result.add_item_tail(p->base - q->base, p->exponent);
            p = p->next;
            q = q->next;
        }
    }
}

void polynomial::multiply_poly(polynomial &y, polynomial &result)
{
    item *p = head->next, *q = (y.head)->next;
    result.empty_poly();
    if (p == NULL || q == NULL)
    {
        return;
    }
    while (q)
    {
        p = head->next;
        while (p)
        {
            result.add_item(p->base*q->base, p->exponent + q->exponent);
            p = p->next;
        }
        q = q->next;
    }
}

void polynomial::divide_poly(polynomial &y, polynomial &result)
{
    if ((y.head)->next == NULL)
    {
        exit(DIVIDE_ZERO_POLYNOMIAL);
    }
    if (head->next == NULL || head->next->exponent < (y.head)->next->exponent)
    {
        return;
    }
    result.empty_poly();
    polynomial t, x;
    x.copy_poly(*this);
    item *r = result.head, *p = (x.head)->next, *q = (y.head)->next;

    while (p->exponent >= q->exponent)
    {
        t.copy_poly(y);
        result.add_item_tail(p->base / q->base, p->exponent - q->exponent);
        r = r->next;
        t.self_multiply(r->base, r->exponent);
        x.self_subtract_poly(t);
        p = (x.head)->next;
        if (p == NULL)
        {
            break;
        }
    }
}

void polynomial::mod_poly(polynomial &y, polynomial &result)
{
    if ((y.head)->next == NULL)
    {
        exit(DIVIDE_ZERO_POLYNOMIAL);
    }
    if (head->next == NULL || head->next->exponent < (y.head)->next->exponent)
    {
        result.copy_poly(*this);
        return;
    }
    polynomial t, x;
    x.copy_poly(*this);
    item *p = (x.head)->next, *q = (y.head)->next;

    while (p->exponent >= q->exponent)
    {
        t.copy_poly(y);
        t.self_multiply(p->base / q->base, p->exponent - q->exponent);
        x.self_subtract_poly(t);
        p = (x.head)->next;
        if (p == NULL)
        {
            break;
        }
    }
    result.copy_poly(x);
}

void polynomial::power(polynomial &result, int power)
{
    if (power<0)
    {
        exit(POWER_SMALLER_THAN_ZERO);
    }
    result.empty_poly();
    if (power == 0)
    {
        result.add_item_tail(1, 0);
        return;
    }
    if (head->next == NULL)
    {
        return;
    }
    polynomial base;
    base.copy_poly(*this);
    result.add_item_tail(1, 0);

    while (power)
    {
        if (power & 1)
        {
            result.self_multiply_poly(base);
        }
        base.self_multiply_poly(base);
        power = power >> 1;
    }
}

void polynomial::differential(polynomial &result)
{
    result.empty_poly();
    item *p = head->next, *q = result.head;
    while (p)
    {
        if (p->exponent != 0)
        {
            q->next = new item;
            q = q->next;
            q->base = (p->base)*(p->exponent);
            q->exponent = (p->exponent) - 1;
        }
        p = p->next;
    }
    q->next = NULL;
    result.tail = q;
}

void polynomial::indefinite_integral(polynomial &result)
{
    result.empty_poly();
    item *p = head->next, *r_head = result.head, *q = result.head;
    while (p)
    {
        if (p->exponent != -1)
        {
            q->next = new item;
            q = q->next;
            q->base = (p->base) / ((p->exponent) + 1);
            q->exponent = (p->exponent) + 1;
        }
        else
        {
            r_head->exponent = 1;
            r_head->base = p->base;
        }
        p = p->next;
    }
    q->next = NULL;
    result.tail = q;
}

void polynomial::self_multiply(double i_base, int i_exponent)
{
    if (is_zero(i_base))
    {
        empty_poly();
        return;
    }
    item *p = head->next;
    while (p)
    {
        p->base *= i_base;
        p->exponent += i_exponent;
        p = p->next;
    }
}

void polynomial::self_multiply_poly(polynomial &y)
{
    if (head->next == NULL)
    {
        return;
    }
    if ((y.head)->next == NULL)
    {
        empty_poly();
        return;
    }
    polynomial result;
    item *p, *q = (y.head)->next;
    while (q)
    {
        p = head->next;
        while (p)
        {
            result.add_item(p->base*q->base, p->exponent + q->exponent);
            p = p->next;
        }
        q = q->next;
    }
    copy_poly(result);
}

void polynomial::self_subtract_poly(polynomial &y)
{
    item *t, *p = head->next, *q = (y.head)->next;
    double result_base;
    while (1)
    {
        if (p == NULL)
        {
            //把多项式y剩下的所有项取负值添加到自己中
            while (q)
            {
                add_item_tail(-(q->base), q->exponent);
                q = q->next;
            }
            return;
        }
        if (q == NULL)
        {
            return;
        }
        if (p->exponent > q->exponent)
        {
            p = p->next;
        }
        else if (p->exponent < q->exponent)
        {
            add_item(-(q->base), q->exponent);
            q = q->next;
        }
        else
        {
            result_base = p->base - q->base;
            t = p->next;
            if (is_zero(result_base))
            {
                delete_exponent(p->exponent);
                p = t;
                q = q->next;
            }
            else
            {
                change_exponent(result_base, p->exponent);
                p = p->next;
                q = q->next;
            }
        }
    }
}

double polynomial::definite_integral(double x1, double x2)
{
    if (head->next == NULL)
    {
        return 0;
    }
    polynomial y;
    indefinite_integral(y);
    return y.calculate(x2) - y.calculate(x1);
}

double polynomial::calculate(double x)
{
    double result = 0;
    if (head->exponent == 1)
    {
        if (x < 0)
        {
            exit(LN_NEGATIVE);
        }
        result += head->base * log(x);
    }
    item *p = head->next;
    while (p)
    {
        if (is_zero(x) && p->exponent < 0) exit(DIVIDE_ZERO_NUMBER);
        result += (p->base) * (p->exponent < 0 ? 1 / fast_pow(x, -(p->exponent)) : fast_pow(x, p->exponent));
        p = p->next;
    }
    return result;
}

void polynomial::print()
{
    int flag = 0;
    if (head->next != NULL)
    {
        flag = 1;
        item *p = head->next;
        if (p->exponent == 0)
        {
            cout << p->base;
        }
        else
        {
            if (p->base == -1)
            {
                cout << '-';
            }
            else if (p->base != 1)
            {
                cout << p->base;
            }
            cout << 'x';
            if (p->exponent != 1)
            {
                cout << "^(" << p->exponent << ')';
            }
        }
        //cout << setprecision(POINTS) << fixed;
        p = p->next;
        while (p)
        {
            if (p->base > 0)
            {
                cout << "+";
            }
            if (p->exponent == 0)
            {
                cout << p->base;
            }
            else
            {
                if (p->base == -1)
                {
                    cout << '-';
                }
                else if (p->base != 1)
                {
                    cout << p->base;
                }
                cout << 'x';
                if (p->exponent != 1)
                {
                    cout << "^(" << p->exponent << ')';
                }
            }
            p = p->next;
        }
    }
    if (head->exponent == 1)
    {
        if (head->base > 0)
        {
            cout << "+";
            if (head->base != 1)
            {
                cout << head->base;
            }
        }
        else
        {
            if (head->base == -1)
            {
                cout << "-";
            }
            else
            {
                cout << head->base;
            }
        }
        cout << "Ln[x]";
    }
    else
    {
        if (flag == 0)
        {
            cout << 0.;
        }
    }
}

#define Epsilon 1e-6
int polynomial::is_zero(double x)
{
    if (x <= Epsilon && x >= -Epsilon)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
#undef Epsilon

double polynomial::fast_pow(double base, int exponent)
{
    if (exponent<0)
    {
        exit(POWER_SMALLER_THAN_ZERO);
    }
    double result = 1;
    while (exponent)
    {
        if (exponent & 1)
        {
            result *= base;
        }
        base *= base;
        exponent = exponent >> 1;
    }
    return result;
}

void polynomial::add_item_tail(double i_base, int i_exponent)
{
    if (is_zero(i_base))
    {
        return;
    }
    tail->next = new item;
    tail = tail->next;
    tail->base = i_base;
    tail->exponent = i_exponent;
    tail->next = NULL;
}

int polynomial::can_not_divide()
{
    if (head->exponent == 1) return 1;
    item *p = head->next;
    while (p)
    {
        if (p->exponent < 0) return 1;
        p = p->next;
    }
    return 0;
}

//如果是合法的索引值，正常返回。否则直接结束程序。
void check_index(int index)
{
    if (index<0 || index >= POLY_AMOUNT)
    {
        exit(INDEX_OUT_OF_RANGE);
    }
    else
    {
        return;
    }
}

//将一个字符转换为int型整数
//若这个字符不是数字，则返回-1
int char_to_number(char a)
{
    if (a >= '0' && a <= '9')
    {
        return a - '0';
    }
    else
    {
        return -1;
    }
}

//比较运算符的优先级
//若a高于b，返回1
//若a等于b，返回0
//若a小于b，返回-1
int operator_compare(char a, char b)
{
    if (a == '*' || a == '/')
    {
        if (b == '*' || b == '/')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (b == '*' || b == '/')
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

int main()
{
    int operate;
    polynomial *data[POLY_AMOUNT];
    for (int i = 0; i<POLY_AMOUNT; i++)
    {
        data[i] = NULL;
    }
    while (1)
    {
        cin >> operate;
        switch (operate)
        {

            case 0://退出
            {
                exit(0);
            }

            case 1://创建
            {
                int index;
                double base, exponent;
                cin >> index;
                check_index(index);
                if (data[index] == NULL)
                {
                    data[index] = new polynomial;
                }
                else
                {
                    (*data[index]).empty_poly();
                }
                while (1)
                {
                    cin >> base >> exponent;
                    if (base == 0 && exponent == 0)
                    {
                        break;
                    }
                    (*data[index]).add_item(base, exponent);
                }
                break;
            }

            case 2://显示
            {
                int index;
                cin >> index;
                check_index(index);
                if (data[index])
                {
                    (*data[index]).print();
                    cout << endl;
                }
                else
                {
                    cout << "NULL" << endl;
                }
                break;
            }

            case 3://复制
            {
                int index1, index2;
                cin >> index1 >> index2;
                check_index(index1);
                check_index(index2);
                if (index1 == index2 || data[index1] == NULL)
                {
                    exit(INDEX_WRONG);
                }
                if (data[index2] == NULL)
                {
                    data[index2] = new polynomial;
                }
                (*data[index2]).copy_poly(*data[index1]);
                break;
            }
            case 4://求和
            {
                int index1, index2, result;
                cin >> index1 >> index2 >> result;
                check_index(index1);
                check_index(index2);
                check_index(result);
                if (data[index1] == NULL || data[index2] == NULL
                    || index1 == index2 || index1 == result || index2 == result)
                {
                    exit(INDEX_WRONG);
                }
                if (data[result] == NULL)
                {
                    data[result] = new polynomial;
                }
                (*data[index1]).add_poly(*data[index2], *data[result]);
                break;
            }
            case 5://求差
            {
                int index1, index2, result;
                cin >> index1 >> index2 >> result;
                check_index(index1);
                check_index(index2);
                check_index(result);
                if (data[index1] == NULL || data[index2] == NULL || index1 == result || index2 == result)
                {
                    exit(INDEX_WRONG);
                }
                if (data[result] == NULL)
                {
                    data[result] = new polynomial;
                }
                if (index1 != index2)
                {
                    (*data[index1]).subtract_poly(*data[index2], *data[result]);
                }
                else
                {
                    (*data[result]).empty_poly();
                }
                break;
            }
            case 6://求值
            {
                int index;
                double x;
                cin >> index >> x;
                check_index(index);
                if (data[index] == NULL)
                {
                    exit(INDEX_WRONG);
                }
                //cout << setprecision(POINTS) << fixed;
                cout << (*data[index]).calculate(x) << endl;
                break;
            }
            case 7://销毁
            {
                int index;
                cin >> index;
                check_index(index);
                if (data[index] != NULL)
                {
                    delete data[index];
                    data[index] = NULL;
                }
                break;
            }
            case 8://清空
            {
                int index;
                cin >> index;
                check_index(index);
                if (data[index] == NULL)
                {
                    exit(INDEX_WRONG);
                }
                (*data[index]).empty_poly();
                break;
            }
            case 9://修改
            {
                int index, operation;
                cin >> index >> operation;
                check_index(index);
                if (data[index] == NULL)
                {
                    exit(INDEX_WRONG);
                }
                if (operation < 1 || operation >3)
                {
                    exit(OPERATION_OUT_OF_RANGE);
                }
                if (operation == 1)//插入新项
                {
                    double base;
                    double exponent;
                    cin >> base >> exponent;
                    (*data[index]).add_item(base, exponent);
                }
                else if (operation == 2)//删除指数为exponent的项
                {
                    int exponent;
                    cin >> exponent;
                    (*data[index]).delete_exponent(exponent);
                }
                else//修改指数为exponent的项
                {
                    double base;
                    int exponent;
                    cin >> base >> exponent;
                    (*data[index]).change_exponent(base, exponent);
                }
                break;
            }
            case 10://微分
            {
                int index1, index2;
                cin >> index1 >> index2;
                check_index(index1);
                check_index(index2);
                if (data[index1] == NULL || index1 == index2)
                {
                    exit(INDEX_WRONG);
                }
                if (data[index2] == NULL)
                {
                    data[index2] = new polynomial;
                }
                (*data[index1]).differential(*data[index2]);
                break;
            }
            case 11://不定积分
            {
                int index1, index2;
                cin >> index1 >> index2;
                check_index(index1);
                check_index(index2);
                if (data[index1] == NULL || index1 == index2)
                {
                    exit(INDEX_WRONG);
                }
                if (data[index2] == NULL)
                {
                    data[index2] = new polynomial;
                }
                (*data[index1]).indefinite_integral(*data[index2]);
                break;
            }
            case 12://定积分
            {
                int index;
                double x1, x2;
                cin >> index >> x1 >> x2;
                check_index(index);
                if (data[index] == NULL)
                {
                    exit(INDEX_WRONG);
                }
                //cout << setprecision(POINTS) << fixed;
                cout << (*data[index]).definite_integral(x1, x2) << endl;
                break;
            }
            case 13://求积
            {
                int index1, index2, result;
                cin >> index1 >> index2 >> result;
                check_index(index1);
                check_index(index2);
                check_index(result);
                if (data[index1] == NULL || data[index2] == NULL
                    || index1 == index2 || index1 == result || index2 == result)
                {
                    exit(INDEX_WRONG);
                }
                if (data[result] == NULL)
                {
                    data[result] = new polynomial;
                }
                (*data[index1]).multiply_poly(*data[index2], *data[result]);
                break;
            }
            case 14://求商
            {
                int index1, index2, result;
                cin >> index1 >> index2 >> result;
                check_index(index1);
                check_index(index2);
                check_index(result);
                if (data[index1] == NULL || data[index2] == NULL
                    || index1 == index2 || index1 == result || index2 == result)
                {
                    exit(INDEX_WRONG);
                }
                if ((*data[index1]).can_not_divide() || (*data[index2]).can_not_divide())
                {
                    exit(CAN_NOT_DIVIDE);
                }
                if (data[result] == NULL)
                {
                    data[result] = new polynomial;
                }
                (*data[index1]).divide_poly(*data[index2], *data[result]);
                break;
            }
            case 15://求余
            {
                int index1, index2, result;
                cin >> index1 >> index2 >> result;
                check_index(index1);
                check_index(index2);
                check_index(result);
                if (data[index1] == NULL || data[index2] == NULL
                    || index1 == index2 || index1 == result || index2 == result)
                {
                    exit(INDEX_WRONG);
                }
                if ((*data[index1]).can_not_divide() || (*data[index2]).can_not_divide())
                {
                    exit(CAN_NOT_DIVIDE);
                }
                if (data[result] == NULL)
                {
                    data[result] = new polynomial;
                }
                (*data[index1]).mod_poly(*data[index2], *data[result]);
                break;
            }
            case 16://乘方
            {
                int index1, index2, power;
                cin >> index1 >> index2 >> power;
                check_index(index1);
                check_index(index2);
                if (data[index1] == NULL || index1 == index2)
                {
                    exit(INDEX_WRONG);
                }
                if (data[index2] == NULL)
                {
                    data[index2] = new polynomial;
                }
                (*data[index1]).power(*data[index2], power);
                break;
            }
        
            case 17://四则运算
            {
                //输入并检查表达式
                int result, c_to_n;
                string expression;
                cin >> result;
                cin >> expression;
                check_index(result);
                if (expression.size()>50)
                {
                    exit(EXPRESSION_TOO_LOOG);
                }
                for (string::iterator it = expression.begin(); it != expression.end(); it++)
                {
                    c_to_n = char_to_number(*it);
                    if (c_to_n >= 0)
                    {
                        check_index(c_to_n);
                        if (c_to_n == result)
                        {
                            exit(INDEX_WRONG);
                        }
                    }
                }

                //将中缀表达式转换为后缀表达式
                //在symbol中放入运算符号，在out中储存中间结果与最终结果
                char symbol[50], out[50];
                char *s = symbol, *o = out, *p = out;
                for (string::iterator it = expression.begin(); it != expression.end(); it++)
                {
                    c_to_n = char_to_number(*it);
                    if (c_to_n == -1)//如果是运算符
                    {
                        if (s == symbol || (*(s - 1)) == '(' || (*it) == '('
                            || operator_compare(*it, *(s - 1)) == 1)
                        {
                            *s = *it;
                            s++;
                        }
                        else if ((*it) == ')')
                        {
                            s--;
                            while (*s != '(')
                            {
                                *o = *s;
                                o++;
                                s--;
                            }
                        }
                        else
                        {
                            s--;
                            *o = *s;
                            o++;
                            it--;
                        }
                    }
                    else
                    {
                        *o = *it;
                        o++;
                    }
                }
                while (s>symbol)
                {
                    *o = *(s - 1);
                    o++;
                    s--;
                }

                //计算后缀表达式的值
                polynomial t[25];
                polynomial t1, t2, t3;
                polynomial *n = t;
                while (p<o)
                {
                    c_to_n = char_to_number(*p);
                    if (c_to_n >= 0)
                    {
                        (*n).copy_poly(*data[c_to_n]);
                        n++;
                    }
                    else
                    {
                        if (*p == '+')
                        {
                            t1.copy_poly(*(n - 2));
                            t2.copy_poly(*(n - 1));
                            t1.add_poly(t2, t3);
                            (*(n - 2)).copy_poly(t3);
                        }
                        else if (*p == '-')
                        {
                            t1.copy_poly(*(n - 2));
                            t2.copy_poly(*(n - 1));
                            t1.subtract_poly(t2, t3);
                            (*(n - 2)).copy_poly(t3);
                        }
                        else if (*p == '*')
                        {
                            t1.copy_poly(*(n - 2));
                            t2.copy_poly(*(n - 1));
                            t1.multiply_poly(t2, t3);
                            (*(n - 2)).copy_poly(t3);
                        }
                        else
                        {
                            t1.copy_poly(*(n - 2));
                            t2.copy_poly(*(n - 1));
                            t1.divide_poly(t2, t3);
                            (*(n - 2)).copy_poly(t3);
                        }
                        n--;
                    }
                    p++;
                }
                if (data[result] == NULL)
                {
                    data[result] = new polynomial;
                }
                (*data[result]).copy_poly(t[0]);
                break;
            }
            default:
            {
                exit(INDEX_OUT_OF_RANGE);
            }
        }
    }
}
