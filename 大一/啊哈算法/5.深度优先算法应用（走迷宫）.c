#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 8
#define COL 16//char�Ͷ�ά����map��ROW�У�COL��(ÿ�е�������\0,�������ʱ����puts)
char **MakeMap(int m,int n)//��̬����һ��m��n�е�char�Ͷ�ά����
{
	char **v,*p,i;
	p=(char *)malloc(sizeof(char)*m*n);
	v=(char **)malloc(sizeof(char *)*m);
	for(i=0;i<m;i++) v[i]=p+i*n;
	return v;
}
void search(char **map,int m,int n,int ax,int ay,int bx,int by,
           int next[][2],int step,int *min,char **book,char **route,int *condition)
//��������ͼ�����ַ����ͼ��������ͼ������������꣬�յ����꣬
//ö���߷���˳��,���߲��������ַ����С���������ַ�����·�������ַ,���������״̬ 
//�����ɹ�condition��ֵ�ᱻ��Ϊ1
{
	int i,j;
	int tx,ty;//��һ��������
	if(ax==bx && ay==by)//����������յ�
	{
		if(*min>step)
		{
			*condition=1; 
			*min=step;//��¼��С���� 
			for(i=0;i<m;i++)
				for(j=0;j<n;j++)
					route[i][j]=book[i][j];//��¼���·�� 
		}
		return;
	}
	for(i=0;i<4;i++)//ö����һ����4���߷� 
	{
		tx=ax+next[i][0];
		ty=ay+next[i][1];
		if(map[tx][ty]==' ' && book[tx][ty]==' ')//�����һ��û���ϰ��Ҳ����������֮�� 
		{
			book[tx][ty]='.';//̤����� 
			search(map,m,n,tx,ty,bx,by,
			next,step+1,min,book,route,condition);//�õݹ�ȥ����������·��
			book[tx][ty]=' ';//ȥ����������·������������ĺۼ�Ĩȥ
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
	int ax=1,ay=1,bx=5,by=13,i,j;//���ΪA������Ϊ(ax,ay)���յ�ΪB������Ϊ(bx,by)��
	int min=10000000;//minӦ�úܿ�ͻᱻˢ�£�
	char **MinRoute=MakeMap(ROW,COL);//MinRoute���ڵǼ����·��
	char **book=MakeMap(ROW,COL);//book���ڵǼ��㼣��' '��δ����֮�أ�'.'��������֮��
	for(i=0;i<ROW;i++)
		for(j=0;j<COL;j++)
			book[i][j]=map[i][j];
	book[ax][ay]='.';//���ȣ�������������֮�أ�
	int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//�ֱ�������Թ������ҡ��¡�������
	int condition=-1;//�ȼ���������ʧ�� 
	
	//������ʼ��excited!
	search(map,ROW,COL,ax,ay,bx,by,next,0,&min,book,MinRoute,&condition);
	if(condition==-1)
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
		puts(map[i]);
	
	//������ٲ��������·�� 
	printf("\n\n���ٲ�����%d\n",min);
	printf("\n���·����\n");
	MinRoute[ax][ay]='A';
	MinRoute[bx][by]='B';
	for(i=0;i<ROW;i++)
		puts(MinRoute[i]);
	system("pause");
	return 0; 
}
