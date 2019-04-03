//��Floodfill��ˮ��䷨��������䷨����һ��ͼ�ж�����ͼ�ĸ��� 
#include <stdio.h>
#include <stdlib.h>
#define ROW 10
#define COL 10
struct note
{
	int x;
	int y;
};
int main()
{
	int map[ROW][COL]={{1,2,1,0,0,0,0,0,2,3},
	            	   {3,0,2,0,1,2,1,0,1,2},
	        	       {4,0,1,0,1,2,3,2,0,1},
	    	           {3,2,0,0,0,1,2,4,0,0},
		               {0,0,0,0,0,0,1,5,3,0},
		               {0,1,2,1,0,1,5,4,3,0},
  	            	   {0,1,2,3,1,3,6,2,1,0},
	        	       {0,0,3,4,8,9,7,5,0,0},
	    	           {0,0,0,3,7,8,6,0,1,2},
		               {0,0,0,0,0,0,0,0,1,0}};
	int book[ROW][COL]={0};
	struct note queue[ROW*COL];
	int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
	int sum=0;
	int i,j,i1,j1,k,tx,ty;
	printf("��������ͼ�����ִ����Σ���\n");
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
			printf("%3d",map[i][j]);
		printf("\n");
	}	
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if(map[i][j]>0)//�����δ�����½��
			{	
				//�ս������λ�ã�����һ��Ϊ�����к�ˮ��ɢʽȾɫ
				sum++;//��������1 
				book[i][j]=1;//̤�Ͽս���
				map[i][j]=-sum;
				int head=0;
				int tail=0;
				queue[tail].x=i;
				queue[tail].y=j;//���г�ʼ��
				tail++;
				while(head<tail)
				{
					for(k=0;k<4;k++)
					{
						tx=queue[head].x+next[k][0];
						ty=queue[head].y+next[k][1];
						if(tx<0 || tx>=ROW || ty<0 || ty>=COL) continue;
						if(map[tx][ty]>0 && book[tx][ty]==0)
						{
							book[tx][ty]=1;
							queue[tail].x=tx;
							queue[tail].y=ty;
							tail++;
							map[tx][ty]=-sum;
						}
					}
					head++;
				}
			} 
		}
	}
	printf("\n\n����%d��������\n",sum);
	printf("\n��������ͼ��\n");
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
			printf("%3d",map[i][j]);
		printf("\n");
	}
	system("pause");
	return 0; 
}
