#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n;//�á�ͼ���ڽӾ���������һ������ͼ���˾���Ľ���Ϊn
	int m;//m������ͼ�ı���
	int e[11][11]={0};//����ֻ��һ��10*10�ľ�����Ҫ��n<=10
	int book[11]={0};
	int que[100];
	int head=0;
	int tail=1;
	int a,b,i,j,cur;
	printf("����ͼ�Ķ�������");
	scanf("%d",&n);
	if(n>10||n<1) {printf("Ҫ�󶥵���С�ڵ���10��\n");system("pause");return 0;}
	printf("����ͼ�ı�����");
	scanf("%d",&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(i!=j) e[i][j]=99999999;
	printf("����ߣ������бߵ������������ţ���\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d %d",&a,&b);
		e[a][b]=1;
		e[b][a]=1;
	}
	//��һ�Ŷ��㿪ʼ���� 
	book[1]=1;
	que[0]=1;
	while(head<tail)
	{
		cur=que[head];
		for(i=1;i<=n;i++)
		{
			if(e[cur][i]==1 && book[i]==0)
			{
				book[i]=1;
				que[tail++]=i;
			}
			if(tail==n) goto end;
		}
		head++;
	}
	end :
	for(i=0;i<tail;i++) printf("%d ",que[i]);
	system("pause");
	return 0; 
}
