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
int getnum(int i,int j)//���������꣬����ֵ��������ĵ�����
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
	int ax=3,ay=3;//���������(ax,ay)�������ǿյء�.������������ 
	int tx,ty,mx=ax,my=ay;//��һ��������(tx,ty)�����������˵ĵ���(mx,my) 
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
	
	printf("ը������Ϸ��ͼ��\n");
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
	printf("��ը��������(%d,%d)��,��������%d�����ˡ�\n",mx,my,max);
	
	
	system("pause");
	return 0; 
}
