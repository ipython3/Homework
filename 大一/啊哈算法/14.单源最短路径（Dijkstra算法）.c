#include <stdio.h>
#include <stdlib.h>
int main()
{
	int inf=99999999;//infinity������
	int e[10][10];
	int dis[11];
	int book[11]={0};
	int i,j,k,n,m,a,b,c,min,u;
	printf("���붥�����������");
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=0;j<=n;j++)
			if(i==j) e[i][j]=0;
			else e[i][j]=inf;
	printf("��������䳤�ȣ�\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		e[a][b]=c;
	}
	book[1]=1; 
	for(i=1;i<=n;i++)
		dis[i]=e[1][i];
	//Dijkstra�㷨�������
	for(i=1;i<=n-1;i++)//���ѭ��Ҫ����n-1��
	{
		//��ʼѰ����1�Ŷ�������Ķ��㣡
		min=inf;
		for(j=1;j<=n;j++)//��dis�������������ɨ�裡
		{
			if(book[j]==0 && dis[j]<min)//���1�Ŷ��㵽�˶����·Ŀǰ����Ҵ˶���û�еǼǹ�
			{
				min=dis[j];
				u=j; 
			}
		}
		book[u]=1;//�������ϲ������ҵ��˵�ǰ��1�Ŷ�������ĵ㣡
		//��ʼ������ҵ��ĵ�ĸ������߽����ɳڣ�
		for(k=1;k<=n;k++)
			if(e[u][k]<inf && dis[k]>dis[u]+e[u][k])//��������ɳ�����
				dis[k]=dis[u]+e[u][k];
	}
	printf("\n1�Ŷ��㵽�������������̾��룺\n");
	for(i=1;i<=n;i++)
		printf("1��>%d : %d\n",i,dis[i]);
	system("pause");
	return 0; 
}
