#include <stdio.h>
#include <stdlib.h>
int n;//�á�ͼ���ڽӾ���������һ������ͼ���˾���Ľ���Ϊn
int m;//m������ͼ�ı���
int e[11][11];//����ֻ��һ��10*10�ľ�����Ҫ��n<=10
int book[11];
int sum=0;//sum���Ѿ����ʹ��Ķ��������
void dfs(int cur)//cur�ǵ�ǰ���ڵĶ������
{
	int i;
	printf("%d ",cur);
	book[cur]=1;
	sum++;
	if(sum==n) return;
	for(i=1;i<=n;i++)
		if(e[cur][i]==1 && book[i]==0)
			dfs(i);
}
int main()
{
	int a,b;
	printf("����ͼ�Ķ�������");
	scanf("%d",&n);
	if(n>10||n<1) {printf("Ҫ�󶥵���С�ڵ���10��\n");system("pause");return 0;}
	printf("����ͼ�ı�����");
	scanf("%d",&m);
	int i,j;
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
	dfs(1); 
	system("pause");
	return 0; 
}
