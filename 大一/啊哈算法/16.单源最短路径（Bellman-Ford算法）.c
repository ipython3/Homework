#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i,k,n,m,u[6],v[6],w[6],dis[6];
	int inf=99999999;
	printf("���붥�����������");
	scanf("%d %d",&n,&m);
	printf("����ߣ�\n");
	for(i=1;i<=m;i++)
		scanf("%d %d %d",&u[i],&v[i],&w[i]);
	
	//��ʼ��dis���飨1�Ŷ��㵽������ĳ�ʼ·�̣� 
	for(i=2;i<=n;i++)
		dis[i]=inf;
	dis[1]=0;
	
	//Bellman-Ford�������
	for(k=1;k<=n-1;k++)
		for(i=1;i<=m;i++)
			if(dis[v[i]]>dis[u[i]]+w[i])
				dis[v[i]]=dis[u[i]]+w[i];
	
	//������
	for(i=1;i<=n;i++)
		printf("%d ",dis[i]); 
	system("pause");
	return 0; 
}
