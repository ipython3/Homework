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
	int i,flag=0;                         //flag���ڼ�¼���ƺ������Ƶ��ظ���� 
	struct queue q1,q2;                     //q1��С�ߣ�q2��С�� 
	struct stack s;                         //s������ 
	q1.head=q1.tail=q2.head=q2.tail=0;
	s.top=-1;
	printf("С�ߣ�");
	for(i=1;i<=6;i++)
		scanf("%d",&q1.data[q1.tail++]);
	printf("С����");
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
		if(q1.head==q1.tail) {printf("С��ʤ��\n");break;}
		flag=0;
		for(i=0;i<=s.top;i++)
			if(s.data[i]==q2.data[q2.head]) {flag=1;break;}
		s.data[++s.top]=q2.data[q2.head++];
		if(flag)
			while(s.top>=i)
				q2.data[q2.tail++]=s.data[s.top--];
		if(q2.head==q2.tail) {printf("С��ʤ��\n");break;}
		flag=0;
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
