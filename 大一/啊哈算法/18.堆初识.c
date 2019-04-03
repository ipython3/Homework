#include <stdio.h>
#include <stdlib.h>
int n=14;
int h[15]={0,1,2,5,12,7,17,25,19,36,99,22,28,46,92};
void swap(int a,int b)
{
	int t;
	t=h[a];
	h[a]=h[b];
	h[b]=t;
}
void shiftdown(int i)
{
	int t,flag=0;
	while(flag==0 && i*2<=n)
	{
		if(h[i*2]<h[i]) t=i*2;
		else t=i;
		if(i*2+1<=n && h[i*2+1]<h[t]) t=2*i+1;
		if(t!=i)
		{
			swap(t,i);
			i=t;
		}
		else flag=1;
	}
}
int main()
{
	long i;
	int low=0,high=100,m;
    m=high-low+1;
    srand((unsigned)time(NULL));
	for(i=0;i<100000000;i++)//1ÒÚ´Î£¡Ô¼3.509s 
	{
		h[1]=low+rand()%m;
		shiftdown(1);
	}
	for(i=1;i<=n;i++) printf("%4d",h[i]);
	//system("pause");
	return 0; 
}
