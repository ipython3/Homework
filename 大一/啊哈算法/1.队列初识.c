#include <stdio.h>
#include <stdlib.h>
struct queue
{
	int data[100];
	int head;
	int tail;
};
int main()
{
	struct queue q;
	int i;
	q.head=0;
	q.tail=9;
	for(i=0;i<9;i++) scanf("%d",&q.data[i]);
	while(q.head<q.tail)
	{
		printf("%d ",q.data[q.head++]);
		q.data[q.tail]=q.data[q.head];
		q.head++;
		q.tail++;
	}
	system("pause");
	return 0; 
}
