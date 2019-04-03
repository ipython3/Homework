/*
哈希表

1.  输入关键字序列；

2.  用除留余数法构建哈希函数，用线性探测法解决冲突，构建哈希表HT1；

3.  用除留余数法构建哈希函数，用拉链法解决冲突，构建哈希表HT2；

4.  分别对HT1和HT2计算在等概率情况下查找成功和查找失败的ASL；

5.  分别在HT1和HT2中查找给定的关键字，给出比较次数
*/

#include <cstdio>

struct Node
{
    int key;
    Node *next;
};

//使用拉链法的哈希表
class HashTableTwo
{
public:
    HashTableTwo(int p, int n, int *a)
    {
        int i, h;
        this->p = p;
        this->n = n;
        for (i = 0; i < p; i++)
        {
            data[i] = NULL;
        }
        for (i = 0; i < n; i++)
        {
            h = a[i] % p;
            if (data[h] == NULL)
            {
                data[h] = new Node;
                (data[h])->key = a[i];
                (data[h])->next = NULL;
            }
            else
            {
                Node *t = data[h];
                while (t->next != NULL)
                {
                    t = t->next;
                }
                t->next = new Node;
                t = t->next;
                t->key = a[i];
                t->next = NULL;
            }
        }
    }

    //求位置pos上的查找成功次数(最大值)
    int success_pos(int pos)
    {
        int i = 0;
        Node *t = data[pos];
        while (t != NULL)
        {
            i++;
            t = t->next;
        }
        return i;
    }

    //求位置pos上的查找失败次数
    int fail_pos(int pos)
    {
        return success_pos(pos) + 1;
    }

    //计算得到关于成功的一些情况
    void get_success()
    {
        int i, sum = 0;
        for (i = 0; i < p; i++)
        {
            success[i] = success_pos(i);
            sum += success[i]*(success[i]+1)/2;
        }
        avg_success = ((float)sum) / ((float)n);
    }

    //计算得到关于失败的一些情况
    void get_fail()
    {
        int i, sum = 0;
        for (i = 0; i < p; i++)
        {
            fail[i] = fail_pos(i);
            sum += fail[i];
        }
        avg_fail = ((float)sum) / ((float)p);
    }

    int p;
    int n;
    Node *data[100];
    int success[100];
    int fail[100];
    float avg_success;
    float avg_fail;
};


int main()
{
    int n, p, i, max, j;
    int data[100];
    Node *t;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
    }
    scanf("%d", &p);
    HashTableTwo HT2(p, n, data);
    HT2.get_success();
    HT2.get_fail();

    printf("哈希表的地址#  表中的关键字#    成功查找次数#\n");
    for (i = 0; i < p; i++)
    {
        printf("%5d", i);
        printf("#");
        if (HT2.data[i] == NULL)
        {
            printf("   - ");
        }
        else
        {
            t = HT2.data[i];
            while (t != NULL)
            {
                printf("%5d", t->key);
                t = t->next;
            }
        }
        printf("#");
        if (HT2.data[i] == NULL)
        {
            printf("%5d", 0);
        }
        else
        {
            max = HT2.success[i];
            for (j = 1; j <= max; j++)
            {
                printf("%5d", j);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("失败查找次数：");
    for (i = 0; i < p; i++)
    {
        printf("%5d", HT2.fail[i]);
    }
    printf("\n");

    printf("查找成功的平均查找长度：%.2f\n", HT2.avg_success);
    printf("查找失败的平均查找长度：%.2f", HT2.avg_fail);

    return 0;
}

