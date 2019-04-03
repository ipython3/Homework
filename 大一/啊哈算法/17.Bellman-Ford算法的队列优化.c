#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i,j,k,n,m,u[8],v[8],w[8];
	int first[6],next[8],dis[6],book[6]; 
	int que[100],head=0,tail=0;
	int inf=99999999;
	printf("输入顶点数与边数：");
	scanf("%d %d",&n,&m);
	
	//初始化dis数组（1号顶点到各顶点的初始路程） 
	for(i=2;i<=n;i++)
		dis[i]=inf;
	dis[1]=0;
	
	//初始化book数组
	for(i=1;i<=n;i++) book[i]=0; 
	
	//初始化first数组（表示所有顶点暂时都没有边） 
	for(i=1;i<=n;i++) first[i]=-1;
	
	printf("输入边：\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&u[i],&v[i],&w[i]);
		//建立邻接表
		next[i]=first[u[i]];
		first[u[i]]=i;
	}
	
	//1号顶点入队
	que[tail++]=1;
	//登记1号顶点
	book[1]=1;
	
	while(head<tail)
	{
		k=first[que[head]];
		while(k!=-1)
		{
			if(dis[v[k]]>dis[u[k]]+w[k])
			{
				dis[v[k]]=dis[u[k]]+w[k];
				if(book[v[k]]==0)
				{
					que[tail++]=v[k];
					book[v[k]]=1;
				}
			}
			k=next[k];
		}
		book[que[head]]=0;
		head++;
	}
	
	//输出结果
	for(i=1;i<=n;i++)
		printf("%d ",dis[i]); 
	system("pause");
	return 0; 
}
