#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i,j,k,n,m,u[8],v[8],w[8];
	int first[6],next[8],dis[6],book[6]; 
	int que[100],head=0,tail=0;
	int inf=99999999;
	printf("���붥�����������");
	scanf("%d %d",&n,&m);
	
	//��ʼ��dis���飨1�Ŷ��㵽������ĳ�ʼ·�̣� 
	for(i=2;i<=n;i++)
		dis[i]=inf;
	dis[1]=0;
	
	//��ʼ��book����
	for(i=1;i<=n;i++) book[i]=0; 
	
	//��ʼ��first���飨��ʾ���ж�����ʱ��û�бߣ� 
	for(i=1;i<=n;i++) first[i]=-1;
	
	printf("����ߣ�\n");
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&u[i],&v[i],&w[i]);
		//�����ڽӱ�
		next[i]=first[u[i]];
		first[u[i]]=i;
	}
	
	//1�Ŷ������
	que[tail++]=1;
	//�Ǽ�1�Ŷ���
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
	
	//������
	for(i=1;i<=n;i++)
		printf("%d ",dis[i]); 
	system("pause");
	return 0; 
}
