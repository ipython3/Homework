#include <stdio.h>
#include <stdlib.h>
int e[10][10];
int book[10];
int n;//ͼ�еĶ����� 
int m;//ͼ�еı���
int min=99999999; 
void dfs(int cur,int dis)//cur�ǵ�ǰ���ڵĶ�������,dis���Ѿ��߹���·�� 
{
	if(dis>=min) return;//��ǰ�߹���·���Ѿ�������С��¼ֵ��û��Ҫ������
	if(cur==n)//���������Ŀ�����
	{
		if(dis<min) min=dis;
		return;
	}
	int i;
	for(i=1;i<=n;i++)
	{
		if(e[cur][i]!=99999999 && book[i]==0)
		{
			book[i]=1;
			dfs(i,dis+e[cur][i]);
			book[i]=0;
		}
	}
}
int main()
{
	int i,j,a,b,c;
	printf("���붥������");
	scanf("%d",&n);
	printf("���������");
	scanf("%d",&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(i!=j) e[i][j]=99999999;
	printf("����ߵĶ˵��볤�ȣ�\n"); 
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		e[a][b]=c;
	}
	
	//�Զ���1Ϊ���
	book[1]=1; 
	dfs(1,0);
	printf("���·�̣�%d\n",min);
	system("pause");
	return 0; 
}
