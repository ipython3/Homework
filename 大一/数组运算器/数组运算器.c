#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void Config();//配置系统参数：一行打印元素个数、每个元素的打印宽度等
void printarr();//打印数组
int FillArray();//生成数组的样本数据，返回样本数据的个数
void Delete();//删除
void DeletePos(int pos);//删除下标为pos的元素
void DeleteVal(int val);//删除值为val的元素
void DeleteRange(int s, int t);//删除s..t下标区间的元素
void Insert();//插入
void InsertPos(int pos, int val);//在数组中pos下标处插入新元素val
void InsertOrder(int val,int condition);//在有序数组中插入新元素保持有序性
void judge();//判断 
int isAsc();//判断数组是否升序排列
int isDesc();//判断数组是否降序排列
int isEqual();//判断数组是否全相等
void statistic();//统计 
int maxarr(void);//返回数组最大值的下标
int minarr(void);//返回数组最小值的下标
float average();//计算数组的平均值
float variance();//计算方差 
void arrange();//排列
void Reverse();//逆置数组
void ReverseAll();//逆置数组（整体）
void ReversePart(int low,int high);//逆置数组（部分）
void sort();//排序
void BubbleSort();//冒泡排序
void SelectSort();//选择排序
void ExchangeSort();//交换排序
void Search();//查找
int NormalSearch(int val);//普通查找
int BiSearch(int val);//二分查找
int LeftRotate(int m);//左旋m位
int RightRotate(int m);//右旋m位
void Apply();//数组的其他应用：1）约瑟夫环 2）筛法求素数
void Josephus();//约瑟夫环
void PrimeNumber(int val);//筛法求素数
void special();//特色功能
int **GetArray(int m,int n);
float **GetArrayFloat(int m,int n);
void FreeArrayFloat(float **v);
void FreeArrayInt(int **v);
void ScanArray(int **v,int m,int n);
void PrintArray(int **v,int m,int n);
void PrintArrayFloat(float **v,int m,int n);
int **Multiplication(int **pa,int rowa,int cola,int **pb,int rowb,int colb);
int det(int **v,int n); 
int sig(int n);
int MinorDet(int **p,int n,int x,int y);
void RankArray_Convert(float **v,int m,int n,int *r);
int RowAllZero(float **v,int m,int n);
int ColAllZero(float **v,int m,int n);
void SwapArray(float **v,int n,int a,int b);
void LambdaAddArray(float **v,int n,float lambda,int a,int b);
int hang=5,kuan=5;//hang是每行打几个元素，kuan是每个元素的宽度
int n=1,a[500];//n是样本数据的个数
int main()
{
    int menu=0;
    a[0]=1;
    for(;;)
    {
        printf("\n\n          ----------------------------------------\n");
        printf("                    欢迎使用数组运算器！\n");
        printf("             0--退出程序       6--统计\n");
        printf("             1--配置系统参数   7--查找\n");
        printf("             2--生成样本数据   8--判断\n");
        printf("             3--显示数组       9--排列\n");
        printf("             4--删除           10--数组应用\n");
        printf("             5--插入           11--特色功能\n");
        printf("             选择（输入序号）：");
        error :scanf("%d",&menu);
        switch(menu)
        {
            case 0:return 0;
            case 1:Config();break;
            case 2:FillArray();break;
            case 3:printarr();break;
            case 4:Delete();break;
            case 5:Insert();break;
            case 6:statistic();break;
            case 7:Search();break;
            case 8:judge();break;
            case 9:arrange();break;
            case 10:Apply();break;
            case 11:special();break;
            default:printf("输入错误！重新输入：");goto error;
        }
    }
}
void printarr()
//打印数组
{
    int i,j;
    char s[5]="%5d";
    s[1]='0'+kuan;
    for(i=0;i<n;i++)
    {
        printf(s,a[i]);
        if((i+1)%hang==0) printf("\n");
    }
}
int FillArray()
//生成数组的样本数据，返回样本数据的个数
{
    int menu,i,m;
    printf("\n生成样本数据的个数（小于等于500）：");
    error1 :scanf("%d",&n);
    if(n<1||n>500) {printf("输入错误！重新输入：");goto error1;}
    printf("可选生成方式：\n");
    printf("(1)用指定范围的随机数填充数组\n");
    printf("(2)键盘输入\n");
    printf("(3)整个数组填同一个值\n");
    printf("(4)用等差序列填充数组\n");
    printf("选择：");
    error2 :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            int low,high;
            printf("输入随机数的下界和上界：");
            scanf("%d%d",&low,&high);
            m=high-low+1;
            srand((unsigned)time(NULL));
            for(i=0;i<n;i++) a[i]=low+rand()%m;
            break;
        }
        case 2:
        {
            printf("请用键盘输入%d个整数：",n);
            for(i=0;i<n;i++) scanf("%d",&a[i]);
            break;
        }
        case 3:
        {
            printf("输入要填入的值：");
            scanf("%d",&m);
            for(i=0;i<n;i++) a[i]=m;
            break;
        }
        case 4:
        {
            int start,gap;
            printf("输入等差数列的首项和公差：");
            scanf("%d%d",&start,&gap);
            for(i=0;i<n;i++) {a[i]=start;start+=gap;}
            break;
        }
        default :printf("输入错误！重新输入：");goto error2;
    }
    printf("生成样本数据成功！");
    return n;
}
void Config()
//配置系统参数：一行打印元素个数、每个元素的打印宽度 
{
    printf("\n一行打印几个元素：");
    scanf("%d",&hang);
    printf("每个元素的打印宽度：");
    error :scanf("%d",&kuan);
    if(kuan<1||kuan>9)
        {printf("宽度应大于等于1，小于等于9，重新输入：");goto error;}
    printf("配置系统参数成功！");
}
void Delete()
//删除
{
    int menu;
    printf("可选的删除方式：\n");
    printf("(1)删除指定下标的元素\n");
    printf("(2)删除指定值的元素\n");
    printf("(3)删除按指定下标区间的一组元素\n");
    printf("选择：");
    error1 :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            int pos;
            printf("输入下标：") ;
            error2 :scanf("%d",&pos);
            if(pos<0||pos>n-1) {printf("输入错误！重新输入：");goto error2;}
            DeletePos(pos);
            break;
        }
        case 2:
        {
            int val,m=n; 
            printf("输入值：");
            scanf("%d",&val);
            DeleteVal(val);
            if(n==m) {printf("查无此值！");return;}
            break;
        }
        case 3:
        {
            int s,t;
            printf("输入区间开头与结尾的下标：") ;
            error3 :scanf("%d%d",&s,&t);
            if(s>t||s<0||t>n-1)
                {printf("输入错误！重新输入：");goto error3;}
            else DeleteRange(s,t);
            break;
        }
        default :printf("输入错误！重新输入：");goto error1;
    }
    printf("删除成功！");
}
void DeletePos(int pos)
//删除下标为pos的元素
{
    int i;
    for(i=pos;i<n-1;i++) a[i]=a[i+1];
    n--;
}
void DeleteVal(int val)
//删除值为val的元素
{ 
    int *p,*q;
    for(p=a,q=a;p<a+n;)
    {
        if(*p!=val)
        {
            if(p>q) *q=*p;
            p++;q++;continue;
        }
        search :
        if(*p==val) {p++;goto search;}
        if(p==a+n) break;
        *q=*p;p++;q++;
    }
    n=q-a;
}
void DeleteRange(int s, int t)
//删除s..t下标区间的元素
{
    if(s==t) {DeletePos(s);return;}
    int i;
    for(i=s;i<n-t+s-1;i++) a[i]=a[i+t-s+1];
    n=n-t+s-1;
}
void Insert()
//插入
{
    if(n+1>500) {printf("数组空间已满，不能再插入啦！");return;}
    int menu;
    printf("可选的插入方式：\n");
    printf("(1)按指定下标位置插入新元素\n");
    printf("(2)在有序数组中插入新元素（保持有序）\n");
    printf("选择：");
    error1 :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            int pos,val;
            printf("输入要插入的位置（下标）：");
            error2 :scanf("%d",&pos);
            if(pos<0||pos>n) {printf("输入错误！重新输入：");goto error2;}
            printf("输入要插入的值（整数）：");
            scanf("%d",&val);
            InsertPos(pos,val);
            break;
        }
        case 2:
        {
            int val,con;
            if(isAsc()) con=1;
            else if(isDesc()) con=2;
            else {printf("不是有序数组！若要进行此操作，请先排序。");return;}
            printf("输入要插入的值（整数）：");
            scanf("%d",&val);
            InsertOrder(val,con);
            break;
        }
        default :
        {
            printf("输入错误！重新输入：");
            goto error1;
        }
    }
    printf("插入成功！");
}
void InsertPos(int pos, int val)
//在数组中pos下标处插入新元素
{
    if(pos==n) {a[n]=val;n++;return;}
    int i;
    for(i=n;i>pos;i--) a[i]=a[i-1];
    a[pos]=val;
    n++;
}
void InsertOrder(int val,int condition)
//在有序数组中插入新元素保持有序性，condition：1为升序，2为降序 
{
    int i,j;
    if(condition==1)
    {
        for(i=0;i<n;i++)
        {
            if(val<a[i])
            {
                for(j=n;j>i;j--) a[j]=a[j-1];
                a[i]=val;
                n++;
                return;
            }
        }
        a[n]=val;
        n++;
    }
    else
    {
        for(i=0;i<n;i++)
        {
            if(val>a[i])
            {
                for(j=n;j>i;j--) a[j]=a[j-1];
                a[i]=val;
                n++;
                return;
            }
        }
        a[n]=val;
        n++;
    }
}
void judge()
//判断
{
    int menu;
    printf("可选的判断方式：\n");
    printf("(1)判断数组是否升序排列\n");
    printf("(2)判断数组是否降序排列\n");
    printf("(3)判断数组是否全相等\n");
    printf("选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            if(isAsc()) printf("是升序排列！");
            else printf("非升序排列！"); 
            break;
        }
        case 2:
        {
            if(isDesc()) printf("是降序排列！");
            else printf("非降序排列！"); 
            break;
        }
        case 3:
        {
            if(isEqual()) printf("是全相等！");
            else printf("非全相等！"); 
            break;
        }
        default :printf("输入错误！重新输入：");goto error;
    }
}
int isAsc()
//判断数组是否升序排列
{
    int i;
    for(i=0;i<n-1;i++)
        if(a[i]>a[i+1]) return 0;
    return 1;
}
int isDesc()
//判断数组是否降序排列
{
    int i;
    for(i=0;i<n-1;i++)
        if(a[i]<a[i+1]) return 0;
    return 1;
}
int isEqual()
//判断数组是否全相等
{
    int i;
    for(i=0;i<n;i++)
        if(a[0]!=a[i]) return 0;
    return 1;
}
void statistic()
//统计 
{
    int menu;
    printf("可选的统计操作：\n");
    printf("(1)求最大值\n");
    printf("(2)求最小值\n");
    printf("(3)求平均值\n");
    printf("(4)求方差和均方差\n");
    printf("选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            int m=maxarr();
            printf("最大值为a[%d]=%d",m,a[m]);
            break;
        }
        case 2:
        {
            int m=minarr();
            printf("最小值为a[%d]=%d",m,a[m]);
            break;
        }
        case 3:
        {
            printf("平均值为：%f",average()); 
            break;
        }
        case 4:
        {
            float m=variance();
            printf("方差为：%f\n",m);
            printf("均方差为：%f\n",sqrt(m));
            break;
        }
        default :printf("输入错误！重新输入：");goto error;
    } 
} 
int maxarr()
//返回数组最大值的下标
{
    int i,j=0;
    for(i=0;i<n;i++)
        if(a[j]<a[i]) j=i;
    return j;
}
int minarr()
//返回数组最小值的下标
{
    int i,j=0;
    for(i=0;i<n;i++)
        if(a[j]>a[i]) j=i;
    return j;
}
float average()
//计算数组的平均值
{
    int i,s=0;
    for(i=0;i<n;i++) s+=a[i];
    return (float)s/(float)n;
}
float variance()
//计算方差 
{
    int i,s=0;
    float avg=average();
    for(i=0;i<n;i++) s+=a[i]*a[i];
    return (float)s/(float)n-avg*avg;
}
void arrange()
//排列
{
    int menu,m;
    printf("可选的排列操作：\n");
    printf("(1)排序\n");
    printf("(2)逆置数组\n");
    printf("(3)左旋数组\n");
    printf("(4)右旋数组\n");
    printf("选择：");
    error1 :scanf("%d",&menu);
    switch(menu)
    {
        case 1:sort();break;
        case 2:Reverse();break;
        case 3:
        {
            printf("输入要左旋多少位：");
            scanf("%d",&m);
            m=m%n;
            if(m==0) goto skip1;
            if(m<0) {m=-m;goto skip2;}
            skip4 :
            LeftRotate(m);
            skip1 :
            printf("左旋成功！");
            break;
        }
        case 4:
        {
            printf("输入要右旋多少位：");
            scanf("%d",&m);
            m=m%n;
            if(m==0) goto skip3;
            if(m<0) {m=-m;goto skip4;}
            skip2 :
            RightRotate(m);
            skip3 :
            printf("右旋成功！");
            break;
        }
        default :printf("输入错误！重新输入：");goto error1;
    } 
}
void Reverse()
//逆置数组
{
    int menu; 
    printf("可选的逆置方式：\n");
    printf("(1)整体逆置\n");
    printf("(2)部分逆置\n");
    printf("选择：");
    error1 :scanf("%d",&menu);
    switch(menu)
    {
        case 1:ReverseAll();break;
        case 2:
        {
            int low,high;
            printf("输入要逆置的区间的开头与结尾的下标）：");
            error2 :scanf("%d%d",&low,&high);
            if(low>high||low<0||high>n-1) 
            {
                printf("输入错误！重新输入：");
                goto error2;
            }
            ReversePart(low,high);
            break;
        }
        default :printf("输入错误！重新输入：");goto error1;
    }
    printf("逆置成功！");
}
void ReverseAll()
//逆置数组（整体） 
{
    int i,j,t;
    for(i=0,j=n-1;i<j;i++,j--) {t=a[i];a[i]=a[j];a[j]=t;}; 
}
void ReversePart(int low,int high)
//逆置数组（部分） 
{
    if(low==high) return;
    int i,j,t;
    for(i=low,j=high;i<j;i++,j--) {t=a[i];a[i]=a[j];a[j]=t;}
}
int LeftRotate(int m)
//左旋m位
{
    ReversePart(0,m-1);
    ReversePart(m,n-1);
    ReverseAll();
}
int RightRotate(int m)
//右旋m位
{
    LeftRotate(n-m);
}
void sort()
//排序
{
    int menu;
    printf("可选的排序方式（排成升序）：\n");
    printf("(1)冒泡排序\n");
    printf("(2)选择排序\n");
    printf("(3)交换排序\n");
    printf("选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:BubbleSort();break;
        case 2:SelectSort();break;
        case 3:ExchangeSort();break;
        default :printf("输入错误！重新输入：");goto error;
    }
    printf("排序成功！");
}
void BubbleSort()
//冒泡排序（排成升序） 
{
    int i,j,t;
    for(i=n-1;i>0;i--)
        for(j=0;j<i;j++)
            if(a[j]>a[j+1]) {t=a[j];a[j]=a[j+1];a[j+1]=t;}
}
void SelectSort()
//选择排序（排成升序） 
{
    int k,i,j,t;
    for(k=0;k<n-1;k++)
    {
        for(i=k,j=k;i<n;i++)
            if(a[j]>a[i]) j=i;
        t=a[k];a[k]=a[j];a[j]=t;
    }
}
void ExchangeSort()
//交换排序（排成升序） 
{
    int i,j,t;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
            if(a[i]>a[j]) {t=a[i];a[i]=a[j];a[j]=t;}
}
void Search()
//查找
{
    int menu,val;
    printf("输入要查找的值：\n");
    scanf("%d",&val);
    printf("可选的查找方式：\n");
    printf("(1)普通查找\n");
    printf("(2)二分查找\n");
    printf("选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:NormalSearch(val);break;
        case 2:
        {
            if(isAsc()) BiSearch(val);
            else printf("不是升序，不可使用二分查找！");
            break;
        }
        default :printf("输入错误！重新输入：");goto error;
    }
}
int NormalSearch(int val)
//普通查找,找到返回其下标，找不到返回-1
{
    int i;
    for(i=0;i<n;i++)
    {
        if(val==a[i])
        {
            printf("查找到a[%d]=%d",i,val);
            return i;
        }
    }
    printf("查无此值！");
    return -1;
}
int BiSearch(int val)
//二分查找,找到返回其下标，找不到返回-1
{
    int low=0,high=n-1,mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(a[mid]>val) high=mid-1;
        else if(a[mid]<val) low=mid+1;
        else
        {
            printf("查找到a[%d]=%d",mid,val);
            return mid;
        } 
    }
    printf("查无此值！");
    return -1;
}
void Apply()
//数组的其他应用：1）约瑟夫环 2）筛法求素数
{
    int menu;
    printf("可选的应用：\n");
    printf("(1)约瑟夫环\n");
    printf("(2)筛法求1到指定数之间的所有素数\n");
    printf("选择：");
    error1 :scanf("%d",&menu);
    switch(menu)
    {
        case 1:Josephus();break;
        case 2:
        {
            int val;
            printf("为求1至指定数之间的所有素数，请输入指定数（小于等于500）：");
            error2 :scanf("%d",&val);
            if(val<2||val>500) {printf("输入错误！重新输入：");goto error2;}
            printf("1至%d之间的所有素数为：\n",val);
            PrimeNumber(val);
            break;
        }
        default :printf("输入错误！重新输入：");goto error1;
    }  
}
void Josephus()
//约瑟夫环
{
    int man,gap,pro,life,i,j;
    printf("输入人数（大于等于1，小于等于500）：");
    error1 :scanf("%d",&man); 
    if(man<1||man>500) {printf("输入错误！重新输入：");goto error1;}
    printf("输入报数间隔：");
    error2 :scanf("%d",&gap);
    if(gap<1) {printf("输入错误！重新输入：");goto error2;}
    printf("输入要保护的人数：");
    error3 :scanf("%d",&pro);
    if(pro<1||pro>=man) {printf("输入错误！重新输入：");goto error3;}
    for(i=0;i<man;i++) a[i]=1;        //大家都活着 
    life=man;
    for(i=0,j=1;;)
    {
        if(a[i]==0) goto jump;        //遇到死人要跳过 
        if(j%gap==0) {a[i]=0;life--;} //喊出“gap”的人要死
        if(life==pro) break;          //只剩下要保护的人就结束游戏
        j++; jump : i++;
        if(i==man) i=0;               //转了一圈回到开头 
    }             
    printf("被保护的人应站的位置：\n");
    for(i=0;i<man;i++) if(a[i]) printf("%4d",i+1);
}
void PrimeNumber(int val)
//筛法求素数
{
    int i,j;
    for(i=0;i<=val;i++) a[i]=1;
    for(i=2;i<=val;i++)
    {
        if(a[i])
        {
            printf("%4d",i);
            for(j=i+1;j<=val;j++)
                if(j%i==0) a[j]=0;
        }
    }
}
void special()
{
    int menu;
    printf("欢迎使用矩阵计算器！\n");
    printf("【注意】：只支持整数矩阵！\n\n");
    printf("可选择的操作：\n");
    printf("0.返回数组运算器主菜单\n1.行列式\n2.矩阵乘法\n3.矩阵求逆\n4.矩阵求秩\n");
    printf("请选择操作（输入序号）：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 0:return;
        case 1:
        {
            int n,**pa;
            printf("输入矩阵A的阶数：");
            error1 :scanf("%d",&n);
            if(n<1) {printf("要求n为正整数！重新输入：");goto error1;} 
            pa=GetArray(n,n);
            printf("输入矩阵A（从左到右，从上到下）：");
            ScanArray(pa,n,n);
            printf("矩阵A为：\n");
            PrintArray(pa,n,n);
            printf("\n计算得：det(A)=%d\n",det(pa,n));
            break;
        }
        case 2:
        {
            int rowa,cola,rowb,colb,**pa,**pb,**pc;
            error2 :
            printf("输入矩阵A的行数和列数：");
            scanf("%d%d",&rowa,&cola);
            printf("输入矩阵B的行数和列数：");
            scanf("%d%d",&rowb,&colb);
            if(cola!=rowb)
            {
                printf("\nA的列数要与B的行数相同！再来一次！\n");
                goto error2;
            }
            pa=GetArray(rowa,cola);
            pb=GetArray(rowb,colb);
            printf("输入矩阵A（从左到右，从上到下）：");
            ScanArray(pa,rowa,cola);
            printf("输入矩阵B（从左到右，从上到下）：");
            ScanArray(pb,rowb,colb);
            printf("矩阵A为：\n");
            PrintArray(pa,rowa,cola);
            printf("矩阵B为：\n");
            PrintArray(pb,rowb,colb);
            printf("矩阵AB为：\n");
            pc=Multiplication(pa,rowa,cola,pb,rowb,colb);
            PrintArray(pc,rowa,colb);
            break;
        }
        case 3:
        {
            int n,**pa;
            printf("输入矩阵A的阶数：");
            error3 :scanf("%d",&n);
            if(n<1) {printf("要求n为正整数！重新输入：");goto error3;} 
            pa=GetArray(n,n);
            printf("输入矩阵A（从左到右，从上到下）：");
            ScanArray(pa,n,n);
            printf("矩阵A为：\n");
            PrintArray(pa,n,n);
            int deta=det(pa,n);
            if(deta==0) {printf("因为det(A)=0，所以矩阵A不可逆！\n");break;}
            int i,j;
            float **pb;
            pb=GetArrayFloat(n,n);
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    pb[j][i]=((float)(sig(i+j)*MinorDet(pa,n,i,j)))/((float)deta);
            printf("\n矩阵A的逆矩阵为：\n");
            PrintArrayFloat(pb,n,n);
            break;
        }
        case 4:
        {
            int m,n,**pa;
            printf("输入矩阵A的行数和列数：");
            scanf("%d%d",&m,&n);            
            pa=GetArray(m,n);
            printf("输入矩阵A（从左到右，从上到下）：");
            ScanArray(pa,m,n);
            printf("矩阵A为：\n");
            PrintArray(pa,m,n);
            int i,j;
            float **pb=GetArrayFloat(m,n);
            for(i=0;i<m;i++)
            {
                for(j=0;j<n;j++)
                {
                    pb[i][j]=(float)(pa[i][j]);
                }
            }
            FreeArrayInt(pa);
            int rank=0;
            int *r=&rank;
            RankArray_Convert(pb,m,n,r);
            printf("\n计算得：rank(A)=%d\n",*r);
            break;
        }
        default :printf("没有此选项！重新输入：");goto error;
    }
}
int MinorDet(int **p,int n,int x,int y)//n阶矩阵p的p[x][y]元素的余子式
{
    int **v,i,j;
    v=GetArray(n-1,n-1);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i<x)
            {
                if(j<y) v[i][j]=p[i][j];
                else if(j>y) v[i][j-1]=p[i][j];
            }
            else if(i>x)
            {
                if(j<y) v[i-1][j]=p[i][j];
                else if(j>y) v[i-1][j-1]=p[i][j];
            }
        }
    }
    return det(v,n-1);
} 
int **GetArray(int m,int n)//动态申请一个m行n列的int型二维数组
{
    int **v,*p,i;
    p=(int *)malloc(sizeof(int)*m*n);
    v=(int **)malloc(sizeof(int *)*m);
    for(i=0;i<m;i++) v[i]=p+i*n;
    return v;
}
float **GetArrayFloat(int m,int n)//动态申请一个m行n列的float型二维数组
{
    float **v,*p;
    int i;
    p=(float *)malloc(sizeof(float)*m*n);
    v=(float **)malloc(sizeof(float *)*m);
    for(i=0;i<m;i++) v[i]=p+i*n;
    return v;
}
void FreeArrayInt(int **v)//释放int型矩阵v的空间 
{
    free(*v);
    free(v);
}
void FreeArrayFloat(float **v)//释放float型矩阵v的空间 
{
    free(*v);
    free(v);
}
void ScanArray(int **v,int m,int n)//输入一个m行n列的int型二维数组
{
    int *p=*v,*q=*(v+m-1)+n;
    for(;p<q;p++) scanf("%d",p);
}
void PrintArray(int **v,int m,int n)//打印一个m行n列的int型二维数组 
{
    int *p=*v,*q=*(v+m-1)+n,i=1;
    for(;p<q;p++,i++)
    {
        printf("%5d",*p);
        if(i%n==0) {printf("\n");i=0;} 
    }
}
void PrintArrayFloat(float **v,int m,int n)
{
    float *p=*v,*q=*(v+m-1)+n;
    int i=1;
    for(;p<q;p++,i++)
    {
        printf("%9.3f",*p);
        if(i%n==0) {printf("\n");i=0;} 
    }
}
int **Multiplication(int **pa,int rowa,int cola,int **pb,int rowb,int colb)
//矩阵A为rowa行cola列，矩阵B为rowb行colb列，二者都是int型二维数组，求AB
{
    int **pc,i,j,k;
    pc=GetArray(rowa,colb);
    for(i=0;i<rowa;i++)
    {
        for(j=0;j<colb;j++)
        {
            pc[i][j]=0;
            for(k=0;k<cola;k++)
                pc[i][j]+=pa[i][k]*pb[k][j];
        }
    }
    return pc;
}
int det(int **v,int n)//计算一个n阶的int型矩阵的行列式（结果必为int型）
{
    if(n==1) return **v; 
    if(n==2) return v[0][0]*v[1][1]-v[0][1]*v[1][0];
    int t,i,j,s=0,**p;
    p=GetArray(n-1,n-1);
    for(t=0;t<n;t++)
    {
        for(i=0;i<n-1;i++)
        {
            for(j=0;j<n-1;j++)
            {
                if(t==0&&j==0) p[i][j]=v[i+1][j+1];
                if(j<t) p[i][j]=v[i+1][j];
                if(j>t) p[i][j]=v[i+1][j+1];
            }
        }
        s+=sig(t)*v[0][t]*det(p,n-1);
    }
    return s;
}
int sig(int n)
{
    if(n%2==0) return 1;
    else return -1;
}
void RankArray_Convert(float **v,int m,int n,int *r)
//通过“初等行变换”来求秩,结果储存在*r中，调用此函数前要先将*r初始化为0 
{
    int RowZero=RowAllZero(v,m,n);
    if(RowZero)
    {
        //printf("发现全零行：%d\n",RowZero);
        if(m==1) return;
        int i,j;
        float **p=GetArrayFloat(m-1,n);
        for(i=0;i<m;i++)
        {
            if(i<RowZero-1)
                for(j=0;j<n;j++)
                    p[i][j]=v[i][j];
            else if(i>RowZero-1)
                for(j=0;j<n;j++)
                    p[i-1][j]=v[i][j];
        }
        FreeArrayFloat(v);
        RankArray_Convert(p,m-1,n,r);
        return;
    }
    if(m==1) {*r+=1;return;}
    int ColZero=ColAllZero(v,m,n);
    if(ColZero)
    {
        //printf("发现全零列：%d\n",ColZero);
        int i,j;
        float **p=GetArrayFloat(m,n-1);
        for(j=0;j<n;j++)
        {
            if(j<ColZero-1)
                for(i=0;i<m;i++)
                    p[i][j]=v[i][j];
            else if(j>ColZero-1)
                for(i=0;i<m;i++)
                    p[i][j-1]=v[i][j];
        }
        FreeArrayFloat(v);
        RankArray_Convert(p,m,n-1,r);
        return;
    }
    //经过以上处理，已经没有全零的行或列
    int i,j;
    for(i=0;i<m;i++) if(v[i][0]) break;
    SwapArray(v,n,1,i+1);
    //经过以上处理，矩阵v的最左上角元素非零
    for(i=1;i<m;i++)
        if(v[i][0])
            LambdaAddArray(v,n,-v[i][0]/v[0][0],1,i+1);
    *r+=1;
    float **p=GetArrayFloat(m-1,n);
    for(i=1;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            p[i-1][j]=v[i][j];
        }
    }
    FreeArrayFloat(v);
    RankArray_Convert(p,m-1,n,r);
} 
int RowAllZero(float **v,int m,int n)//检查有无全零行，有则返回是第几行，无则返回0
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            if(v[i][j]>0.001||v[i][j]<-0.001)
                goto jump;
        return i+1;
        jump :;
    }
    return 0;
}
int ColAllZero(float **v,int m,int n)//检查有无全零列，有则返回是第几列，无则返回0
{
    int i,j;
    for(j=0;j<n;j++)
    {
        for(i=0;i<m;i++)
            if(v[i][j]>0.001||v[i][j]<-0.001)
                goto jump;
        return j+1;
        jump :;
    }
    return 0;
}
void SwapArray(float **v,int n,int a,int b)
//v是m*n矩阵，交换第a行与第b行
{
    if(a==b) return;
    float *p=&v[a-1][0],*q=&v[b-1][0],*end=p+n,t;
    for(;p<end;p++,q++) {t=*p;*p=*q;*q=t;}
}
void LambdaAddArray(float **v,int n,float lambda,int a,int b)
//v是m*n矩阵，将第a行的lambda倍加到第b行 
{
    float *p=&v[a-1][0],*q=&v[b-1][0],*end=p+n;
    for(;p<end;p++,q++) *q+=(*p)*lambda;
}
