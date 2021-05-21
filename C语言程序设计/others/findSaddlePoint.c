/*---------------------------------------
程序：找鞍点
行内最大且列内最小的点为鞍点 
---------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#define DEBUG
#define NUM 3

int findSaddlePoint()
{
	//定义 
	int i,j;						//计数 
	int lineMax[NUM],rowMin[NUM];	//存放
	int tempmax,tempmin;			//暂存 
	bool exists=false;				//是否存在 
	
	//输入 
	#ifdef DEBUG
	int array[NUM][NUM] = {{1,2,3},{4,5,6},{7,8,9}};
	#else
	int array[NUM][NUM];
	printf("请输入 3×3 的数组：\n");
	for(i=0; i<NUM; i++)
	{
		for(j=0; j<NUM; j++)
		{
			scanf("%d", &array[i][j]);
		}
	}
	#endif
	
	//计算行最大 
	for(i=0; i<NUM; i++)
	{
		tempmax = array[i][0];
		lineMax[i] = 0;
		for(j=0; j<NUM; j++)
		{
			if(array[i][j]>tempmax)
			{
				tempmax = array[i][j];
				lineMax[i] = j;
			}
		}
	}
	//计算列最小
	for(j=0; j<NUM; j++)
	{
		i=0;
		tempmin = array[i][j];
		rowMin[j] = i;
		for(i=0; i<NUM; i++)
		{
			if(array[i][j]<tempmin)
			{
				tempmin = array[i][j];
				lineMax[j] = i;
			}
		}
	}
	
	//比较输出
	for(i=0; i<NUM; i++)
	{
		j = lineMax[i];
		if(rowMin[j] == i)
		{
			exists = true;
			printf("第 %d 行，第 %d 列存在鞍点：%d\n",\
			 i+1, j+1, array[i][j]);
		}
	} 
	
	if(!exists)
	{
		printf("不存在鞍点");
	}
}

