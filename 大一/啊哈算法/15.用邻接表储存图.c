#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n,m,i,j;
	int u[6],v[6],w[6];
	int first[5],next[5];
	printf("�����붥�����������");
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++) first[i]=-1;
	printf("������%d���ߣ�\n",m);
	for(i=1;i<=m;i++)
	{
		scanf("%d %d %d",&u[i],&v[i],&w[i]);
		next[i]=first[u[i]];
		first[u[i]]=i;
	}
	for(i=1;i<=n;i++)
	{
		printf("%d�Ŷ���ĳ����У�\n",i);
		j=first[i];
		while(j!=-1)
		{
			printf("%d %d %d\n",u[j],v[j],w[j]);
			j=next[j];
		}
		printf("\n");
	}
	system("pause");
	return 0; 
}
