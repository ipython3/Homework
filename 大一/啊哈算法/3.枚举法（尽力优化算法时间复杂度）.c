#include <stdio.h>
#include <stdlib.h>
int fun(int x)//输入整数x,返回这个整数需要的火柴棍数 
{
	int a[10]={6,2,5,5,4,5,6,3,7,6};//a[i]中记录的是数字i需要的火柴棍数
	int sum=0;
	while(x/10!=0)
	{
		sum+=a[x%10];
		x=x/10;
	}
	//经过以上处理，x只剩最高位的那个数字了 
	sum+=a[x];
	return sum;
}
int main()
{
	int a,b,c,bar,sum=0;
	printf("输入火柴棍数量：");
	scanf("%d",&bar);
	if(bar>24) {printf("要求火柴棍不超过24根！\n");goto end;}
	for(a=0;a<=1111;a++)
	{
		for(b=0;b<=1111;b++)
		{
			c=a+b;
			if(fun(a)+fun(b)+fun(c)+4==bar)
			{
				printf("%d+%d=%d\n",a,b,c);
				sum++;
			}
		}
	}
	printf("%d个火柴棍可以拼出%d个不同的等式！",bar,sum);
	end :
	system("pause");
	return 0; 
}
