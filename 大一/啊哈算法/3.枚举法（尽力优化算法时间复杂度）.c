#include <stdio.h>
#include <stdlib.h>
int fun(int x)//��������x,�������������Ҫ�Ļ����� 
{
	int a[10]={6,2,5,5,4,5,6,3,7,6};//a[i]�м�¼��������i��Ҫ�Ļ�����
	int sum=0;
	while(x/10!=0)
	{
		sum+=a[x%10];
		x=x/10;
	}
	//�������ϴ���xֻʣ���λ���Ǹ������� 
	sum+=a[x];
	return sum;
}
int main()
{
	int a,b,c,bar,sum=0;
	printf("�������������");
	scanf("%d",&bar);
	if(bar>24) {printf("Ҫ�����������24����\n");goto end;}
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
	printf("%d����������ƴ��%d����ͬ�ĵ�ʽ��",bar,sum);
	end :
	system("pause");
	return 0; 
}
