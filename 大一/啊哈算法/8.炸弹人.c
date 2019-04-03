#include <stdio.h>
#include <stdlib.h>
#define ROW 13
#define COL 13
struct note
{
	int x;
	int y;
};
char map[ROW][COL]={"#############",
                    "#GG.GGG#GGG.#",
                    "###.#G#G#G#G#",
                    "#.......#..G#",
                    "#G#.###.#G#G#",
                    "#GG.GGG.#.GG#",
                    "#G#.#G#.#.#.#",
                    "##G...G.....#",
                    "#G#.#G###.GG#",
                    "#...G#GGG.GG#",
                    "#G#.#G#G#.#G#",
                    "#GG.GGG#G.GG#",
                    "#############"};
int getnum(int i,int j)//参数是坐标，返回值是能消灭的敌人数
{
	int sum=0,x,y;
	x=i;y=j;
	while(map[x][y]!='#')
	{
		if(map[x][y]=='G') sum++;
		x--;
	}
	x=i;y=j;
	while(map[x][y]!='#')
	{
		if(map[x][y]=='G') sum++;
		x++;
	}
	x=i;y=j;
	while(map[x][y]!='#')
	{
		if(map[x][y]=='G') sum++;
		y--;
	}
	x=i;y=j;
	while(map[x][y]!='#')
	{
		if(map[x][y]=='G') sum++;
		y++;
	}
	return sum;
} 
int main()
{
	int i,j;
	int ax=3,ay=3;//起点坐标是(ax,ay)，必须是空地‘.’！否则会出错！ 
	int tx,ty,mx=ax,my=ay;//下一点坐标是(tx,ty)，消灭最多敌人的点是(mx,my) 
	struct note que[ROW*COL];
	int head=0;
	int tail=0;
	que[tail].x=ax;
	que[tail].y=ay;
	tail++;
	int book[ROW][COL]={0};
	book[ax][ay]=1;
	int next[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
	int sum,max=getnum(ax,ay);
	
	printf("炸弹人游戏地图：\n");
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
			printf("%2c",map[i][j]);
		printf("\n");
	}
	
	while(head<tail)
	{
		for(i=0;i<4;i++)
		{
			tx=que[head].x+next[i][0];
			ty=que[head].y+next[i][1];
			if(map[tx][ty]=='.' && book[tx][ty]==0)
			{
				book[tx][ty]=1;
				que[tail].x=tx;
				que[tail].y=ty;
				tail++;
				sum=getnum(tx,ty);
				if(sum>max)
				{
					max=sum;
					mx=tx;
					my=ty;
				}
			}
		}
		head++;
	}
	printf("将炸弹放置在(%d,%d)处,可以消灭%d个敌人。\n",mx,my,max);
	
	
	system("pause");
	return 0; 
}
