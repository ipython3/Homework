#include <stdio.h>
#include <stdlib.h>
struct queue          //���У���¼������ 
{
	int data[1000];
	int head;
	int tail;
};
struct stack          //ջ����¼������ 
{
	int data[10];
	int top;
};
int main()
{
	int i,t,book[10]={0};                   //book���ڼ�¼��������Щ���ֵ��� 
	struct queue q1,q2;                     //q1��С�ߣ�q2��С�� 
	struct stack s;                         //s������ 
	q1.head=q1.tail=q2.head=q2.tail=0;
	s.top=-1;
	printf("С�����ƣ�");
	for(i=1;i<=6;i++)
		scanf("%d",&q1.data[q1.tail++]);
	printf("С�����ƣ�");
	for(i=1;i<=6;i++)
		scanf("%d",&q2.data[q2.tail++]);
	while(1)
	{
		t=q1.data[q1.head++];     //С�߳���������� 
		if(book[t]==1)            //���С�߷�����������ͬ���ֵ���
		{
			q1.data[q1.tail++]=t;
			while(1)
			{
				book[s.data[s.top]]=0;
				if((q1.data[q1.tail++]=s.data[s.top--])==t) break;
			}
		} 
		else book[s.data[++s.top]=t]=1;  //���С�߷�����������ͬ���ֵ���
		if(q1.head==q1.tail) {printf("С��ʤ��\n");break;}
		t=q2.data[q2.head++];     //С������������� 
		if(book[t]==1)            //���С��������������ͬ���ֵ���
		{
			q2.data[q2.tail++]=t;
			while(1)
			{
				book[s.data[s.top]]=0;
				if((q2.data[q2.tail++]=s.data[s.top--])==t) break;
			}
		} 
		else book[s.data[++s.top]=t]=1;  //���С��������������ͬ���ֵ���	
		if(q2.head==q2.tail) {printf("С��ʤ��\n");break;}
	}
	printf("С�������ƣ�");
	for(i=q1.head;i<q1.tail;i++)
		printf("%d ",q1.data[i]);
	printf("\nС�������ƣ�");
	for(i=q2.head;i<q2.tail;i++)
		printf("%d ",q2.data[i]);
	printf("\n�����ƣ�\n");
	for(i=s.top;i>=0;i--)
		printf("%d\n",s.data[i]);
	system("pause");
	return 0; 
}
