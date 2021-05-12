#include <stdio.h>
#include <math.h>

/*

给定一个正整数n，请求出所有满足如下两个条件的正整数集合x[1],x[2]...x[n]:
1. x[1]+x[2]+...+x[n]=2n
2. 不存在一个划分将集合划分成和相等的两部分，也就是说，集合的任意子集和均不为n。
请按照集合中元素升序排序后字典序从小到大的顺序输出答案，若不存在这样的集合请不要输出任何字符。

*/

static void traverse(int*, int, int);
static bool check(int* c, int n);

int findASpecialCollection()
{	
	// 输入
	int n; 
	scanf("%d", &n);
	
	// 初始化要用到的数组 
	int i;

	// 由于 x[n] 中全部为正整数，而和为 2n，
	// 先把 n 个 1 分配到 x[n] 中 
	// 则剩下 n 个 1 任意分配到 x[n] 中
	// 设第 k 个 1 分配到 c[k] 中
	// 此时 x[n] 由 c[n] 完全确定，只需要遍历 c[n] 
	int c[n+1];
	
	// 遍历 c[n] 
	c[n]=n-1;
	traverse(c, n, n-1); 
	 
	return 0;
}

// 遍历所有可能的数组 
static void traverse(int* c, int n, int i)
{
	int j;
	// 递归退出条件
	if(i == 0)
	{
		// 遍历最后一个 1 分配到的位置 
		for(j=*(c+i+1); j>=0; j--)
		{
			*(c+i) = j;
			check(c, n);
		}
		return;
	}
	else
	{
		// 遍历第 i 个 1 分配到的位置 
		for(j=*(c+i+1); j>=0; j--)
		{
			*(c+i) = j;
			traverse(c, n, i-1);
		}
	}
}

// 判断数组是否符合要求
static bool check(int* c, int n)
{
	int j;				// 计数变量 
	int sum=0;			// 暂存和 
	int result = true;	// 存放结果 
	int x[n];			// 存放按 c[n] 分配后的数组
	unsigned int child=0;		// 存放二进制子集信息 
	int p,q;			// 用于拷贝数组 
	
	// 初始化 x[n]
	for(j=0; j<n; j++)
	{
		x[j] = 1;		// 一开始给所有项分配的 1 
	} 
	// 按 c[n] 分配数组
	for(j=0; j<n; j++)
	{
		x[*(c+j)] += 1;	// 按照 c[n] 给 x[n] 分配的 1 
	} 
	
	// 二进制数 child 递增 
	for(child=0; child<pow(2.0,n); child++)
	{
		sum=0;
		// 遍历 child 的每一位 
		for(j=0; j<n; j++)
		{
			// 获取右数第 j 位 
			if((child>>j)&0b01)
			{
				sum += x[j]; 
			}
		}
		if(sum == n)
		{
			result = false;
			break;
		}
	}
	
	if(result)
	{ 
		// 判断是否顺序
		result=true;
		for(j=0; j<n-1; j++)
		{
			if(x[j]>x[j+1])
			{
				result = false;
			}
		} 
		
		if(result)
		{
			// 输出数组 
			for(j=0; j<n-1; j++)
			{
				printf("%d ",x[j]);
			}
			printf("%d\n",x[n-1]);
		}
	}
} 
