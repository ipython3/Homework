#include <stdio.h>
#include <stdlib.h>
int main()
{
	int inf=99999999;//infinity，无限
	int e[10][10];
	int dis[11];
	int book[11]={0};
	int i,j,k,n,m,a,b,c,min,u;
	printf("输入顶点数与边数：");
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
		for(j=0;j<=n;j++)
			if(i==j) e[i][j]=0;
			else e[i][j]=inf;
	printf("输入边与其长度：\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&a,&b,&c);
		e[a][b]=c;
	}
	book[1]=1; 
	for(i=1;i<=n;i++)
		dis[i]=e[1][i];
	//Dijkstra算法核心语句
	for(i=1;i<=n-1;i++)//这个循环要进行n-1次
	{
		//开始寻找离1号顶点最近的顶点！
		min=inf;
		for(j=1;j<=n;j++)//对dis数组进行完整的扫描！
		{
			if(book[j]==0 && dis[j]<min)//如果1号顶点到此顶点的路目前最短且此顶点没有登记过
			{
				min=dis[j];
				u=j; 
			}
		}
		book[u]=1;//经过以上操作，找到了当前离1号顶点最近的点！
		//开始对这个找到的点的各个出边进行松弛！
		for(k=1;k<=n;k++)
			if(e[u][k]<inf && dis[k]>dis[u]+e[u][k])//如果满足松弛条件
				dis[k]=dis[u]+e[u][k];
	}
	printf("\n1号顶点到其他各顶点的最短距离：\n");
	for(i=1;i<=n;i++)
		printf("1—>%d : %d\n",i,dis[i]);
	system("pause");
	return 0; 
}
