#include <stdio.h>
#include <stdlib.h>
#define ROW 8
#define COL 15
struct note
{
	int x,y;//�����ꡢ������
	int s;//����
	int f;//�����ڶ����еı�� 
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
	int ax=1,ay=1,bx=5,by=13,tx,ty,i,j;//���ΪA������Ϊ(ax,ay)���յ�ΪB������Ϊ(bx,by)
	
	char MinRoute[ROW][COL];//MinRoute���ڵǼ����·��
	char book[ROW][COL];//book���ڵǼ��㼣��' '��δ����֮�أ�'.'��������֮��
	for(i=0;i<ROW;i++)
		for(j=0;j<COL;j++)
			MinRoute[i][j]=book[i][j]=map[i][j];
	book[ax][ay]='.';//���ȣ�������������֮�أ�
	
	
	int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//�ֱ�������Թ������ҡ��¡�������
	int min=10000000;//minӦ�úܿ�ͻᱻˢ�£�
	int flag=0;//�ȼ���û�е����յ� 
	struct note que[ROW*COL];//��Ϊ��ͼ��СΪROW*COL�����Զ�����չ���ᳬ��ROW*COL�� 
	int head=0,tail=0;
	que[tail].x=ax;
	que[tail].y=ay;
	que[tail].s=0;
	que[tail].f=0;
	tail++;
	
	while(head<tail)//���зǿ�ʱ����ѭ�� 
	{
		for(i=0;i<4;i++)//ö��4������ 
		{
			tx=que[head].x+next[i][0];
			ty=que[head].y+next[i][1];
			if(map[tx][ty]==' ' && book[tx][ty]==' ')//��������������� 
			{
				book[tx][ty]='.';//̤�����
				que[tail].x=tx;
				que[tail].y=ty;
				que[tail].s=que[head].s+1;
				que[tail].f=head;//��һ��ĸ�����head
				tail++;
			}
			if(tx==bx && ty==by)//��������յ�
			{
				flag=1;
				goto end;
			} 
		}
		head++;//һ����ĸ���������չ��ϣ����������ӣ���һ��ѭ��ȥ��չ��һ���� 
	}
	end :
	if(flag==0)
	{
		printf("û��·�����Եִ��յ㣡\n");
		system("pause");
		return 0;
	}
	
	//����Թ���ͼ
	printf("\n�Թ���ͼ��AΪ��㣬BΪ�յ㣩��\n");
	map[ax][ay]='A';
	map[bx][by]='B';
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
			printf("%c",map[i][j]);
		printf("\n");
	}
	
	//������ٲ��������·�� 
	printf("\n\n��С������%d\n",que[--tail].s);
	printf("\n���·����\n");
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
