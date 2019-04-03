#include <stdio.h>
#include <stdlib.h>
int e[10][10];
int book[10];
int n;//图中的顶点数 
int m;//图中的边数
int min=99999999; 
void dfs(int cur,int dis)//cur是当前所在的顶点的序号,dis是已经走过的路程 
{
	if(dis>=min) return;//当前走过的路程已经超过最小记录值，没必要继续了
	if(cur==n)//如果到达了目标城市
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
	printf("输入顶点数：");
	scanf("%d",&n);
	printf("输入边数：");
	scanf("%d",&m);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(i!=j) e[i][j]=99999999;
	printf("输入边的端点与长度：\n"); 
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		e[a][b]=c;
	}
	
	//以顶点1为起点
	book[1]=1; 
	dfs(1,0);
	printf("最短路程：%d\n",min);
	system("pause");
	return 0; 
}
