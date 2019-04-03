#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n;//用“图的邻接矩阵”来储存一个无向图，此矩阵的阶数为n
	int m;//m是无向图的边数
	int e[11][11]={0};//这里只用一个10*10的矩阵，则要求n<=10
	int book[11]={0};
	int que[100];
	int head=0;
	int tail=1;
	int a,b,i,j,cur;
	printf("输入图的顶点数：");
	scanf("%d",&n);
	if(n>10||n<1) {printf("要求顶点数小于等于10。\n");system("pause");return 0;}
	printf("输入图的边数：");
	scanf("%d",&m);
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
