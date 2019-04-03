#include <stdio.h>
#include <stdlib.h>
#define ROW 8
#define COL 15
struct note
{
	int x,y;//横坐标、纵坐标
	int s;//步数
	int f;//父亲在队列中的编号 
};
int main()
{
	char map[ROW][COL]={"---------------",
	                    "|    #        |",
	                    "|  #  # ### # |",
	                    "| ### #  #  # |",
                        "| #      #   #|",
	                    "| # #####  ## |",
	                    "|   #    #    |",
	                    "---------------"};
	int ax=1,ay=1,bx=5,by=13,tx,ty,i,j;//起点为A，坐标为(ax,ay)。终点为B，坐标为(bx,by)
	
	char MinRoute[ROW][COL];//MinRoute用于登记最短路径
	char book[ROW][COL];//book用于登记足迹，' '是未涉足之地，'.'是已涉足之地
	for(i=0;i<ROW;i++)
		for(j=0;j<COL;j++)
			MinRoute[i][j]=book[i][j]=map[i][j];
	book[ax][ay]='.';//首先，起点就是已涉足之地！
	
	
	int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//分别代表在迷宫中向右、下、左、上走
	int min=10000000;//min应该很快就会被刷新！
	int flag=0;//先假设没有到达终点 
	struct note que[ROW*COL];//因为地图大小为ROW*COL，所以队列扩展不会超过ROW*COL个 
	int head=0,tail=0;
	que[tail].x=ax;
	que[tail].y=ay;
	que[tail].s=0;
	que[tail].f=0;
	tail++;
	
	while(head<tail)//队列非空时进行循环 
	{
		for(i=0;i<4;i++)//枚举4个方向 
		{
			tx=que[head].x+next[i][0];
			ty=que[head].y+next[i][1];
			if(map[tx][ty]==' ' && book[tx][ty]==' ')//如果这个方向可以走 
			{
				book[tx][ty]='.';//踏上这里！
				que[tail].x=tx;
				que[tail].y=ty;
				que[tail].s=que[head].s+1;
				que[tail].f=head;//这一点的父亲是head
				tail++;
			}
			if(tx==bx && ty==by)//如果到了终点
			{
				flag=1;
				goto end;
			} 
		}
		head++;//一个点的各个方向都扩展完毕，就让他出队，下一轮循环去拓展下一个点 
	}
	end :
	if(flag==0)
	{
		printf("没有路径可以抵达终点！\n");
		system("pause");
		return 0;
	}
	
	//输出迷宫地图
	printf("\n迷宫地图（A为起点，B为终点）：\n");
	map[ax][ay]='A';
	map[bx][by]='B';
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
			printf("%c",map[i][j]);
		printf("\n");
	}
	
	//输出最少步数与最短路径 
	printf("\n\n最小步数：%d\n",que[--tail].s);
	printf("\n最短路径：\n");
	while(tail>0)
	{
		MinRoute[que[tail].x][que[tail].y]='.';
		tail=que[tail].f;
	}
	MinRoute[ax][ay]='A';
	MinRoute[bx][by]='B';
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
			printf("%c",MinRoute[i][j]);
		printf("\n");
	}
	system("pause");
	return 0; 
}
