#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i,k,n,m,u[6],v[6],w[6],dis[6];
	int inf=99999999;
	printf("输入顶点数与边数：");
	scanf("%d %d",&n,&m);
	printf("输入边：\n");
	for(i=1;i<=m;i++)
		scanf("%d %d %d",&u[i],&v[i],&w[i]);
	
	//初始化dis数组（1号顶点到各顶点的初始路程） 
	for(i=2;i<=n;i++)
		dis[i]=inf;
	dis[1]=0;
	
	//Bellman-Ford核心语句
	for(k=1;k<=n-1;k++)
		for(i=1;i<=m;i++)
			if(dis[v[i]]>dis[u[i]]+w[i])
				dis[v[i]]=dis[u[i]]+w[i];
	
	//输出结果
	for(i=1;i<=n;i++)
		printf("%d ",dis[i]); 
	system("pause");
	return 0; 
}
