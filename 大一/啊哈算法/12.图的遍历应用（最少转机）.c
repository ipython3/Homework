#include <stdio.h>
#include <stdlib.h>
struct note
{
	int x;//城市序号 
	int s;//转机次数
};
int main()
{
	int n,m,i,j,a,b,cur,start,end,head=0,tail=1;
	int e[11][11];
	int book[11]={0};
	struct note que[11];
	printf("输入城市数量：");
	scanf("%d",&n);
	printf("输入航线数量：");
	scanf("%d",&m);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j) e[i][j]=0;
			else e[i][j]=99999999;
		}
	}
	printf("输入航线：\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d %d",&a,&b);
		e[a][b]=1;
		e[b][a]=1;
	}
	printf("输入出发城市与终点城市的序号："); 
	scanf("%d %d",&start,&end);
	book[start]=1;
	que[0].x=start;
	que[0].s=0;
	while(head<tail)
	{
		cur=que[head].x;
		for(i=1;i<=n;i++)
		{
			if(e[cur][i]!=99999999 && book[i]==0)
			{
				book[i]=1;
				que[tail].x=i;
				que[tail].s=que[head].s+1;
				tail++;
			}
			if(que[tail-1].x==end) goto end;
		}
		head++;
	}
	end :
	printf("从%d号城市到%d号城市最少需要转机%d次。\n",start,end,que[tail-1].s);
	printf("tail=%d",tail);
	system("pause");
	return 0; 
}
