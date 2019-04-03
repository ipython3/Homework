#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 8
#define COL 16//char型二维数组map有ROW行，COL列(每行的最后包含\0,所以输出时可用puts)
char **MakeMap(int m,int n)//动态申请一个m行n列的char型二维数组
{
	char **v,*p,i;
	p=(char *)malloc(sizeof(char)*m*n);
	v=(char **)malloc(sizeof(char *)*m);
	for(i=0;i<m;i++) v[i]=p+i*n;
	return v;
}
void search(char **map,int m,int n,int ax,int ay,int bx,int by,
           int next[][2],int step,int *min,char **book,char **route,int *condition)
//参数：地图储存地址，地图行数，地图列数，起点坐标，终点坐标，
//枚举走法的顺序,已走步数储存地址，最小步数储存地址，最短路径储存地址,搜索结果的状态 
//搜索成功condition的值会被改为1
{
	int i,j;
	int tx,ty;//下一步的坐标
	if(ax==bx && ay==by)//如果到达了终点
	{
		if(*min>step)
		{
			*condition=1; 
			*min=step;//记录最小步数 
			for(i=0;i<m;i++)
				for(j=0;j<n;j++)
					route[i][j]=book[i][j];//记录最短路径 
		}
		return;
	}
	for(i=0;i<4;i++)//枚举下一步的4种走法 
	{
		tx=ax+next[i][0];
		ty=ay+next[i][1];
		if(map[tx][ty]==' ' && book[tx][ty]==' ')//如果下一步没有障碍物，也不是已涉足之地 
		{
			book[tx][ty]='.';//踏上这里！ 
			search(map,m,n,tx,ty,bx,by,
			next,step+1,min,book,route,condition);//用递归去搜索将来的路！
			book[tx][ty]=' ';//去尝试其他的路，把来过这里的痕迹抹去
		}
	}
}
int main()
{
	char **map=MakeMap(ROW,COL);
	strcpy(map[0],"---------------");
	strcpy(map[1],"|    #        |");
	strcpy(map[2],"|  #  # ### # |");
	strcpy(map[3],"| ### #  #  # |");
	strcpy(map[4],"| #      #   #|");
	strcpy(map[5],"| # #####  ## |");
	strcpy(map[6],"|   #    #    |");
	strcpy(map[7],"---------------");
	int ax=1,ay=1,bx=5,by=13,i,j;//起点为A，坐标为(ax,ay)。终点为B，坐标为(bx,by)。
	int min=10000000;//min应该很快就会被刷新！
	char **MinRoute=MakeMap(ROW,COL);//MinRoute用于登记最短路径
	char **book=MakeMap(ROW,COL);//book用于登记足迹，' '是未涉足之地，'.'是已涉足之地
	for(i=0;i<ROW;i++)
		for(j=0;j<COL;j++)
			book[i][j]=map[i][j];
	book[ax][ay]='.';//首先，起点就是已涉足之地！
	int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//分别代表在迷宫中向右、下、左、上走
	int condition=-1;//先假设搜索会失败 
	
	//搜索开始！excited!
	search(map,ROW,COL,ax,ay,bx,by,next,0,&min,book,MinRoute,&condition);
	if(condition==-1)
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
		puts(map[i]);
	
	//输出最少步数与最短路径 
	printf("\n\n最少步数：%d\n",min);
	printf("\n最短路径：\n");
	MinRoute[ax][ay]='A';
	MinRoute[bx][by]='B';
	for(i=0;i<ROW;i++)
		puts(MinRoute[i]);
	system("pause");
	return 0; 
}
