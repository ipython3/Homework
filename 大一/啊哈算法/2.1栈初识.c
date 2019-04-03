#include <stdio.h>
#include <stdlib.h>
struct queue          //队列，记录手中牌 
{
	int data[1000];
	int head;
	int tail;
};
struct stack          //栈，记录桌上牌 
{
	int data[10];
	int top;
};
int main()
{
	int i,flag=0;                         //flag用于记录出牌后桌上牌的重复情况 
	struct queue q1,q2;                     //q1是小哼，q2是小哈 
	struct stack s;                         //s是桌子 
	q1.head=q1.tail=q2.head=q2.tail=0;
	s.top=-1;
	printf("小哼：");
	for(i=1;i<=6;i++)
		scanf("%d",&q1.data[q1.tail++]);
	printf("小哈：");
	for(i=1;i<=6;i++)
		scanf("%d",&q2.data[q2.tail++]);
	while(1)
	{
		for(i=0;i<=s.top;i++)
			if(s.data[i]==q1.data[q1.head]) {flag=1;break;}
		s.data[++s.top]=q1.data[q1.head++];
		if(flag)
			while(s.top>=i)
				q1.data[q1.tail++]=s.data[s.top--];
		if(q1.head==q1.tail) {printf("小哈胜！\n");break;}
		flag=0;
		for(i=0;i<=s.top;i++)
			if(s.data[i]==q2.data[q2.head]) {flag=1;break;}
		s.data[++s.top]=q2.data[q2.head++];
		if(flag)
			while(s.top>=i)
				q2.data[q2.tail++]=s.data[s.top--];
		if(q2.head==q2.tail) {printf("小哼胜！\n");break;}
		flag=0;
	}
	printf("小哼手中牌：");
	for(i=q1.head;i<q1.tail;i++)
		printf("%d ",q1.data[i]);
	printf("\n小哈手中牌：");
	for(i=q2.head;i<q2.tail;i++)
		printf("%d ",q2.data[i]);
	printf("\n桌上牌：\n");
	for(i=s.top;i>=0;i--)
		printf("%d\n",s.data[i]);
	system("pause");
	return 0; 
}
