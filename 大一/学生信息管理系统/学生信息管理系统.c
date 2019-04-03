#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student 
{
    int num;//学号
    char name[20];//姓名
    float score;//成绩
    struct student *next;
};
typedef struct student STUDENT;//以后写STUDENT就代表了struct student 
STUDENT *head=NULL;
STUDENT *MakeNode(int n,char a[],float s);
//创建一个学生结点，返回的是指向这个节点的指针
void Make();//创建链表
void MakeHead();//头插法创建链表
void MakeTail();//尾插法创建链表
void MakeSort();//有序插法（学号有序）创建链表
void MakeInput();//读取数据文件
void Print();//打印全部记录
int PrintPos(int pos);//打印位序为pos的那一条学生信息
void Insert();//插入一条记录
int InsertPos(int n,char a[],float s,int pos); 
//按照位序插入，插到第pos个节点之前
int InsertNum(int n,char a[],float s,int search_num);
//按照指定学号插入，插到学号为search_num的节点之前
void Delete();//删除一条记录
int DeletePos(int pos);//删除第pos个节点
int DeleteNum(int search_num);//删除学号为search_num的节点
void Search();//按学号查找记录
int SearchNum(int n);//查找学号为n的结点，返回其位序
void Statistic();//统计
int StatisticPopulation();//统计链表中的总人数
void Output();//输出学生信息数据文件
void Destroy();//销毁链表
void DestroyHead(STUDENT **h);//销毁头指针为"h指向的指针"的链表
void Sort();//排序
void SortNum(STUDENT **h);//排序（按学号）
int main()
{
    int menu=0;
    for(;;)
    {
        printf("\n\n          ----------------------------------------\n");
        printf("              欢迎使用学生信息管理系统！\n");
        printf("             0--退出程序       5--按学号查找记录\n");
        printf("             1--创建链表       6--统计\n");
        printf("             2--打印全部记录   7--输出学生信息数据文件\n");
        printf("             3--插入一条记录   8--销毁链表\n");
        printf("             4--删除一条记录   9--排序\n");
        printf("             选择（输入序号）：");
        error :scanf("%d",&menu);
        switch(menu)
        {
            case 0:return 0;
            case 1:Make();break;
            case 2:Print();break;
            case 3:Insert();break;
            case 4:Delete();break;
            case 5:Search();break;
            case 6:Statistic();break;
            case 7:Output();break;
            case 8:Destroy();break;
            case 9:Sort();break;
            default:printf("输入错误！重新输入：");goto error;
        }
    }
}
STUDENT *MakeNode(int n,char a[],float s)
//创建一个学生结点，返回的是指向这个节点的指针
{
    STUDENT *p;
    p=(STUDENT *)malloc(sizeof(STUDENT));
    p->num=n;
    strcpy(p->name,a);
    p->score=s;
    p->next=NULL;
    return p;
} 
void Make()//创建链表
{
    if(head!=NULL) {printf("已有链表！要再次创建，请先销毁现有的链表！\n");return;}
    int menu;
    printf("可选创建链表方式：\n");
    printf("1.头插法\n2.尾插法\n3.有序插法\n4.读取数据文件\n请选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:MakeHead();break;
        case 2:MakeTail();break;
        case 3:MakeSort();break;
        case 4:MakeInput();break;
        default:printf("无此选项！重新选择：");goto error;
    }
}
void MakeHead()//头插法创建链表
{
    STUDENT *p;
    int n;char a[20];float s;
    while(1)
    {
        printf("请输入学号（若要停止输入学生信息，请输入0）：");
        scanf("%d",&n);
        if(n==0) break;
        getchar();
        printf("请输入姓名：");
        gets(a);
        printf("请输入成绩：");
        scanf("%f",&s);
        p=MakeNode(n,a,s);
        p->next=head;
        head=p;
    }
}
void MakeTail()//尾插法创建链表
{
    STUDENT *p,*r=NULL;
    int n;char a[20];float s;
    while(1)
    {
        printf("请输入学号（若要停止输入学生信息，请输入0）：");
        scanf("%d",&n);
        if(n==0) break;
        getchar();
        printf("请输入姓名：");
        gets(a);
        printf("请输入成绩：");
        scanf("%f",&s);
        p=MakeNode(n,a,s);
        if(head==NULL) head=p;
        else r->next=p;
        r=p;
    }
    printf("尾插法创建链表成功！\n");
}
void MakeSort()//有序插法（学号有序）创建链表
{
    STUDENT **h=&head;
    MakeHead();
    SortNum(h);
    printf("有序插法（学号有序）创建链表成功！\n");
}
void MakeInput()//读取数据文件
{
    FILE *fp=fopen("student.dat","r");
    if(fp==NULL) {printf("文件打开失败！\n");return;}
    head=NULL;
    STUDENT t;
    STUDENT *p,*r=NULL;
    while(1)
    {
        fread(&t,sizeof(STUDENT),1,fp);
        if(feof(fp)) break;
        p=MakeNode(t.num,t.name,t.score);
        if(head==NULL) head=p;
        else r->next=p;
        r=p;
    }
    printf("读取数据文件成功！\n");
}
void Print()//打印全部记录
{
    if(head==NULL) {printf("链表为空！请先创建链表，再来打印！\n");return;}
    printf("打印全部记录：\n");
    printf("             学号           姓名            成绩\n");
    printf("       —————————————————————\n");
    STUDENT *p;
    for(p=head;p!=NULL;p=p->next)
    {
        printf("%16d",p->num);
        printf("%16s",p->name);
        printf("%16.1f\n",p->score);
    }
}
int PrintPos(int pos)
//打印位序为pos的那一条学生信息
//若链表为空返回-1
//若位序超出正常范围返回1 
//若打印成功返回0 
{
    if(head==NULL) return -1;
    if(pos<1||pos>StatisticPopulation()) return 1;
    STUDENT *p=head;
    int i=1;
    while(1)
    {
        if(i==pos)
        {
            printf("          学号              姓名            成绩\n");
            printf("       —————————————————————\n");
            printf("%16d",p->num);
            printf("%16s",p->name);
            printf("%16.1f\n",p->score);
            return 0;
        }
        p=p->next;
        i++;
    }
} 
void Insert()//插入一条记录
{
    if(head==NULL) {printf("链表为空！请先创建链表，再进行插入操作！");return;}
    int n;char a[20];float s;
    printf("请输入学号：");
    scanf("%d",&n);
    getchar();
    printf("请输入姓名：");
    gets(a);
    printf("请输入成绩：");
    scanf("%f",&s);
    int menu;
    printf("可选插入方式：\n");
    printf("1.按照位序\n2.按照指定学号\n请选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            int pos,con; 
            printf("要插入到第几个学生之前：");
            scanf("%d",&pos);
            con=InsertPos(n,a,s,pos);
            if(con==1) printf("您要求的位序超出范围！\n"); 
            else if(con==0) printf("按照位序插入成功！\n");
            break;
        }
        case 2:
        {
            int search_num,con; 
            printf("要插入到学号为多少的学生之前：");
            scanf("%d",&search_num);
            con=InsertNum(n,a,s,search_num);
            if(con==0) printf("按照指定学号插入成功！\n");
            else if(con==1) printf("查无此学号！\n");
            break;
        }
        default:printf("无此选项！重新选择：");goto error;
    }
}
int InsertPos(int n,char a[],float s,int pos)
//按照位序插入，插到第pos个节点之前
//若链表为空，返回-1 
//若位序超出正常范围，返回1
//插入成功返回0
{
    if(head==NULL) return -1;
    if(pos<1||pos>StatisticPopulation()+1) return 1;
    if(pos==1)
    {
        STUDENT *p;
        p=MakeNode(n,a,s);
        p->next=head;
        head=p;
        return 0;
    }
    int i=1;
    STUDENT *p=head,*r;
    while(i<pos-1){p=p->next;i++;}
    r=MakeNode(n,a,s);
    r->next=p->next;
    p->next=r;
    return 0; 
}
int InsertNum(int n,char a[],float s,int search_num)
//按照指定学号插入，插到学号为search_num的节点之前
//若链表为空，返回-1 
//若查无此学号，返回1
//插入成功返回0 
{
    if(head==NULL) return -1;
    int pos=SearchNum(search_num);
    if(pos) {InsertPos(n,a,s,pos);return 0;} 
    else return 1;
}
void Delete()//删除一条记录
{
    if(head==NULL) {printf("链表为空！没有什么可删除的！\n");return;};
    int menu;
    printf("可选删除方式：\n");
    printf("1.按照位序\n2.按照指定学号\n请选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:
        {
            int pos,con; 
            printf("要删除第几个学生：");
            scanf("%d",&pos);
            con=DeletePos(pos);
            if(con==1) printf("您要求的位序超出范围！\n"); 
            else if(con==0) printf("按照位序删除成功！\n");
            break;
        }
        case 2:
        {
            int search_num,con; 
            printf("要删除学号为多少的学生：");
            scanf("%d",&search_num);
            con=DeleteNum(search_num);
            if(con==0) printf("按照指定学号删除成功！\n");
            else if(con==1) printf("查无此学号！\n");
            break;
        }
        default:printf("无此选项！重新选择：");goto error;
    }
}
int DeletePos(int pos)
//删除第pos个节点
//若链表为空，返回-1 
//若位序超出正常范围，返回1
//删除成功返回0
{
    if(head==NULL) return -1;
    if(pos<1||pos>StatisticPopulation()) return 1;
    STUDENT *p=head; 
    if(pos==1)
    {
        head=p->next;
        free(p);
        return 0;
    }
    STUDENT *r;
    int i=1;
    while(i<pos-1){p=p->next;i++;}
    r=p->next;
    p->next=r->next;
    free(r);
    return 0; 
}
int DeleteNum(int search_num)
//删除学号为search_num的节点
//若链表为空，返回-1 
//若查无此学号，返回1
//删除成功返回0 
{
    if(head==NULL) return -1;
    int pos=SearchNum(search_num);
    if(pos) {DeletePos(pos);return 0;}
    else return 1;
}
void Search()//按学号查找记录
{
    if(head==NULL) {printf("链表为空！请先去创建链表，再来查找记录！\n");return;}
    int n;
    printf("要按学号查找记录，请输入要查找的学号：");
    scanf("%d",&n);
    int pos=SearchNum(n);
    if(pos==0) printf("查无此号！\n");
    else
    {
        printf("发现符合要求的学生，在链表当中的位序：%d\n",pos);
        printf("详细信息：\n");
        PrintPos(pos);
    }
}
int SearchNum(int n)
//查找学号为n的结点，返回其位序，链表为空则返回-1，链表非空却找不到则返回0
{
    if(head==NULL) return -1;
    STUDENT *p;
    int i=1;
    for(p=head;p!=NULL;i++,p=p->next)
        if(p->num==n) return i;
    return 0;
}
void Statistic()//统计
{
    if(head==NULL) {printf("链表为空！请先去创建链表，再来做统计！\n");return;}
    int pop=0,failed=0;
    float s=0,high=-99999;
    STUDENT *p=head;
    while(1)
    {
        pop++;
        s+=p->score;
        if(p->score<60) failed++;
        if(p->score>high) high=p->score;
        if(p->next==NULL) break;
        p=p->next;
    }
    s=s/pop;
    printf("总人数：%d\n",pop);
    printf("平均分：%.2f\n",s);
    printf("最高分：%.2f\n",high);
    printf("不及格人数：%d\n",failed);
}
int StatisticPopulation()//统计链表中的总人数
{
    if(head==NULL) return 0;
    int n=1;
    STUDENT *p=head;
    while(p->next!=NULL) {n++;p=p->next;}
    return n;
}
void Output()//输出学生信息数据文件
{
    if(head==NULL) {printf("链表为空！请先去创建链表，再来输出数据文件！\n");return;}
    int menu;
    FILE *fp; 
    printf("可选输出数据文件方式：\n");
    printf("1.追加到原有数据之后\n2.完全覆盖原有数据\n请选择：");
    error :scanf("%d",&menu);
    switch(menu)
    {
        case 1:fp=fopen("student.dat","ab");break;
        case 2:fp=fopen("student.dat","wb");break;
        default:printf("无此选项！重新选择：");goto error;
    }
    if(fp==NULL) {printf("文件打开失败！\n");return;}
    STUDENT *p=head;
    while(1)
    {
        fwrite(p,sizeof(STUDENT),1,fp);
        if(p->next==NULL) break;
        p=p->next;
    }
    fclose(fp);
    printf("输出学生信息数据文件成功！\n");
}
void Destroy()//销毁链表
{
    if(head==NULL) {printf("链表为空！没有什么可销毁的！\n");return;}
    STUDENT **h=&head; 
    DestroyHead(h);
    printf("销毁链表成功！\n");
}
void DestroyHead(STUDENT **h)//销毁头指针为"h指向的指针"的链表
{
    if(*h==NULL) return;
    if((*h)->next==NULL)
    {
        free(*h);
        *h=NULL;
        return; 
    }
    STUDENT *p=*h,*r=(*h)->next;
    while(1)
    {
        free(p);
        p=r;
        if(p->next==NULL) break;
        r=p->next;
    }
    *h=NULL;
} 
void Sort()//排序
{
    if(head==NULL) {printf("链表为空！请先去创建链表，再来按学号排序！\n");return;}
    STUDENT **h=&head;
    SortNum(h);//排序（按学号）
    printf("按学号排序成功！\n");
}
void SortNum(STUDENT **h)//排序（按学号）
{
    if(*h==NULL) return;
    STUDENT *head2=NULL,*t=*h,*p;
    p=MakeNode(t->num,t->name,t->score);
    p->next=NULL;
    head2=p;
    STUDENT *r;
        while(1)
        {
            if(t->next==NULL) break;
            t=t->next;
            p=MakeNode(t->num,t->name,t->score);
            r=head2;
            if(p->num<=r->num)
            {
                p->next=head2;
                head2=p;
                continue;
            }
            while(1)
            {
                if(r->next==NULL) break;
                if((p->num>=r->num)&&(p->num<=r->next->num)) break;
                r=r->next;
            }
            p->next=r->next;
            r->next=p;
        }
    DestroyHead(h); 
    *h=head2;
}
