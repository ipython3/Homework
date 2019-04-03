#include <stdio.h>
#include <stdlib.h>
int n;//用“图的邻接矩阵”来储存一个无向图，此矩阵的阶数为n
int m;//m是无向图的边数
int e[11][11];//这里只用一个10*10的矩阵，则要求n<=10
int book[11];
int sum=0;//sum是已经访问过的顶点的数量
void dfs(int cur)//cur是当前所在的顶点序号
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
	printf("输入图的顶点数：");
	scanf("%d",&n);
	if(n>10||n<1) {printf("要求顶点数小于等于10。\n");system("pause");return 0;}
	printf("输入图的边数：");
	scanf("%d",&m);
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(i!=j) e[i][j]=99999999;
	printf("输入边（输入有边的两个顶点的序号）：\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d %d",&a,&b);
		e[a][b]=1;
		e[b][a]=1;
	}
	//从一号顶点开始出发 
	dfs(1); 
	system("pause");
	return 0; 
}
