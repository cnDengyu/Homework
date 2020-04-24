#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

double myPow(double, int);

int main(int argc, char *argv[]) {
	double x=1;
	int n=0;
	
	printf("请输入 x 和 n：");
	scanf("%lf", &x);
	scanf("%d", &n);
	printf("%lf 的 %d 次方为：%lf",x,n, myPow(x,n));
	return 0;
}

double myPow(double x, int n)
{
	if(n == 1)
	{
		return x;
	}
	else
	{
		return x*myPow(x, n-1);
	}
}
