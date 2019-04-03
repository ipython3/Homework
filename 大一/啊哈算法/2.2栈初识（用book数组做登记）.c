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
	int i,t,book[10]={0};                   //book用于记录桌上有哪些数字的牌 
	struct queue q1,q2;                     //q1是小哼，q2是小哈 
	struct stack s;                         //s是桌子 
	q1.head=q1.tail=q2.head=q2.tail=0;
	s.top=-1;
	printf("小哼拿牌：");
	for(i=1;i<=6;i++)
		scanf("%d",&q1.data[q1.tail++]);
	printf("小哈拿牌：");
	for(i=1;i<=6;i++)
		scanf("%d",&q2.data[q2.tail++]);
	while(1)
	{
		t=q1.data[q1.head++];     //小哼抽出他的手牌 
		if(book[t]==1)            //如果小哼发现桌上有相同数字的牌
		{
			q1.data[q1.tail++]=t;
			while(1)
			{
				book[s.data[s.top]]=0;
				if((q1.data[q1.tail++]=s.data[s.top--])==t) break;
			}
		} 
		else book[s.data[++s.top]=t]=1;  //如果小哼发现桌上无相同数字的牌
		if(q1.head==q1.tail) {printf("小哈胜！\n");break;}
		t=q2.data[q2.head++];     //小哈抽出他的手牌 
		if(book[t]==1)            //如果小哈发现桌上有相同数字的牌
		{
			q2.data[q2.tail++]=t;
			while(1)
			{
				book[s.data[s.top]]=0;
				if((q2.data[q2.tail++]=s.data[s.top--])==t) break;
			}
		} 
		else book[s.data[++s.top]=t]=1;  //如果小哈发现桌上无相同数字的牌	
		if(q2.head==q2.tail) {printf("小哼胜！\n");break;}
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
