#include <stdio.h>
#include <stdlib.h>
int det(int **v,int n); 
int sig(int n);
int MinorDet(int **p,int n,int x,int y);
void RankArray();
int **GetArray(int m,int n);
float **GetArrayFloat(int m,int n);
void FreeArrayFloat(float **v);
void FreeArrayInt(int **v);
void ScanArray(int **v,int m,int n);
void PrintArray(int **v,int m,int n);
void PrintArrayFloat(float **v,int m,int n);
int **Multiplication(int **pa,int rowa,int cola,int **pb,int rowb,int colb);

void RankArray_Convert(float **v,int m,int n,int *r);
int RowAllZero(float **v,int m,int n);
int ColAllZero(float **v,int m,int n);
void SwapArray(float **v,int n,int a,int b);
void LambdaAddArray(float **v,int n,float lambda,int a,int b);

int **Sondet(int n,int row[],int col[]);
int RankArray_Sondet(int **v,int m,int n);
int **SelectPosition(); 
int factorial(int n);
int combination(int m,int n);


int main()
{
    int menu;
    printf("欢迎使用矩阵计算器！\n");
    printf("【注意】：只支持整数矩阵！\n\n");
    printf("可选择的操作：\n");
    printf("0.关闭程序\n1.行列式\n2.矩阵乘法\n3.矩阵求逆\n4.矩阵求秩\n");
    printf("请选择操作（输入序号）：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 0:return 0;
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
        case 4:RankArray();break;
        default :printf("没有此选项！重新输入：");goto error;
    }
    system("pause");
    return 0;
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
void RankArray()
{
    int m,n,**pa;
    printf("输入矩阵A的行数和列数：");
    scanf("%d%d",&m,&n);            
    pa=GetArray(m,n);
    printf("输入矩阵A（从左到右，从上到下）：");
    ScanArray(pa,m,n);
    printf("矩阵A为：\n");
    PrintArray(pa,m,n);
    int menu;
    printf("计算秩的方法：\n");
    printf("1.非零子式的最大阶数\n2.初等变换\n请选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            //printf("\n计算得 rank(A)=%d\n",RankArray_Sondet(pa,m,n));
            break;
        }
        case 2:
        {
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


/*


int **Sondet(int n,int row[],int col[])
//取一个n阶子式，行的取法在row[]中，列的取法在col[]中 
{
    int **v;
    v=GetArray(n,n);
    int *p,*q,*t=*v;
    for(p=row;p<row+n;p++)
    {
        for(q=col;q<col+n;q++,t++)
        {
            *t=v[*p][*q];
        }
    }
    return v;
}
int RankArray_Sondet(int **v,int m,int n)//通过求“非零子式的最大阶数”来求秩
{
    int min=m>n?n:m,r=min,**row,**col;
    for(;r>0;r--)
    {
        ;//关键之处啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊 
    }
    return r;
}
int **SelectPosition()//如果改动参数表，记得函数声明那里也要改啊啊啊啊啊啊啊啊！ 
//选择位置，各种排列组合要放进一个二维数组里 
{
    ; 
} 
int factorial(int n)//求n的阶乘
{
    int i,s;
    for(s=1,i=1;i<=n;i++) s*=i;
    return s;
}
int combination(int m,int n)//求组合数C(m,n)，m在右上角，n在右下角
{
    return (factorial(n)/factorial(m))/factorial(n-m);
}

*/
