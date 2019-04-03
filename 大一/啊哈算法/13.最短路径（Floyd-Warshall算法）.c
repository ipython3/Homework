//用Floyd-Warshall算法得出任意两点间的最短路程
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int inf=99999999;//infinity，无限
	int e[10][10];
	int i,j,k,n,m,a,b,c;
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
	//Floyd-Warshall算法核心语句！ 
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(e[i][k]<inf && e[k][j]<inf && e[i][j]>e[i][k]+e[k][j])
					e[i][j]=e[i][k]+e[k][j];
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			printf("%10d",e[i][j]);
		printf("\n");
	}
	system("pause");
	return 0; 
}
