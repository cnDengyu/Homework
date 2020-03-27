#include <stdio.h>
/*------------------------------------------

3月 27日作业
章登宇 

-------------------------------------------*/ 

static void taskTwo();
static void taskThree();
static void taskFour();
static void taskFive();

//程序入口
int homeworkMar27th(int argc, char** argv)
{
	puts("\n-------------------------第一题-------------------------\n");
	puts("（设计函数min(x,y)，没有输出）");
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	puts("\n-------------------------第四题-------------------------\n");
	taskFour();
	puts("\n-------------------------第五题-------------------------\n");
	taskFive();
	return 0; 
}

/*第一题 
设计一个函数 min(x,y)，返回两个 double 类型值的较小值 
*/ 
static double min(double x, double y)
{
	return x>y?x:y;
}

/*第二题 
设计程序，计算并输出两个矩阵相乘的结果
（提示用户输入三个整数，分别作为第一个矩阵的行数、列数及第二个矩阵的列数） 
*/ 
static void taskTwo()
{
	int m1line,m1row,m2row,i,j,k;
	printf("请以空格分开，输入第一个矩阵的行数、列数和第二个矩阵的列数："); 
	scanf("%d %d %d", &m1line, &m1row, &m2row);
	float martix1[m1line][m1row], martix2[m1row][m2row],martixResult[m1line][m2row];
	printf("请输入x矩阵：\n");
	for(i=0; i<m1line; i++){
		for(j=0; j<m1row; j++){
			scanf("%f", &martix1[i][j]);
		}
	}
	printf("请输入y矩阵：\n");
	for(i=0; i<m1row; i++){
		for(j=0; j<m2row; j++){
			scanf("%f", &martix2[i][j]);
		}
	}
	for(i=0; i<m1line; i++){
		for(j=0; j<m2row; j++){
			martixResult[i][j]=0;
			for(k=0; k<m1row; k++){
				martixResult[i][j] += martix1[i][k]*martix2[k][j];
			}
		}
	}
	printf("计算得到的矩阵是：\n"); 
	for(i=0; i<m1line; i++){
		for(j=0; j<m2row; j++){
			printf("%f ",martixResult[i][j]);
		}
		putchar('\n');
	}
}

/*第三题 
编一程序，将两个字符串连接起来，不要用 strcat 函数 
*/ 
static void myStrCat(char* str1, char* str2)
{
	char *p,*q;
	p = str1;
	q = str2;
	while(*p++ != '\0');
	p--;
	while((*p++ = *q++) != '\0');
}

#define MAX_STR 30
static void taskThree()
{
	char str1[MAX_STR], str2[MAX_STR];
	printf("请输入第一个字符串：");
	scanf("%s", str1);
	printf("请输入第二个字符串：");
	scanf("%s", str2);
	myStrCat(str1, str2);
	printf("拼接后的字符串为：%s",str1);
}

/*第四题 
输入 10 个学生 5 门课程的成绩，分别用函数实现下列功能：
计算每个学生的平均分
计算每门课的平均分
找出所有 50 个分数中最高的分数所对应的学生和课程
计算平均分方差：（公式略） 
*/ 
#define NUM_STU 10
#define NUM_CLS 5
static void stuAverage(float grades[NUM_STU][NUM_CLS])
{
	int i,j;
	float sum = 0;
	for(i=0; i<NUM_STU; i++){
		sum = 0;
		for(j=0; j<NUM_CLS; j++){
			sum += grades[i][j];
		}
		printf("第 %d 位同学的平均分为 %.1f\n", i+1, sum/NUM_CLS);
	}
}
static void clsAverage(float grades[NUM_STU][NUM_CLS])
{
	int i,j;
	float sum = 0;
	for(j=0; j<NUM_CLS; j++){
		sum = 0;
		for(i=0; i<NUM_STU; i++){
			sum += grades[i][j];
		}
		printf("第 %d 门课程的平均分为 %.1f\n", j+1, sum/NUM_STU);
	}
}
static void grdMax(float grades[NUM_STU][NUM_CLS])
{
	int i,j;
	float max = 0;;
	for(i=0; i<NUM_STU; i++){
		for(j=0; j<NUM_CLS; j++){
			if(grades[i][j]>max){
				max = grades[i][j];
			}
		}
	}
	for(i=0; i<NUM_STU; i++){
		for(j=0; j<NUM_CLS; j++){
			if(grades[i][j] == max){
				printf("最高分为 %f ，是第 %d 位同学在第 %d 门课程中取得的。\n", max, i+1, j+1);
			}
		}
	}
}
static void stuVariance(float grades[NUM_STU][NUM_CLS])
{
	int i,j;
	float sum = 0;
	float stuAverage[NUM_STU];
	float variance = 0;
	float temp = 0;
	for(i=0; i<NUM_STU; i++){
		sum = 0;
		for(j=0; j<NUM_CLS; j++){
			sum += grades[i][j];
		}
		stuAverage[i] = sum/NUM_CLS;
	}
	for(i=0; i<NUM_STU; i++){
		variance += stuAverage[i]*stuAverage[i]/NUM_STU;
		temp += stuAverage[i];
	}
	variance -= (temp/NUM_STU)*(temp/NUM_STU);
	printf("平均分方差为 %f \n",variance);
}
//#define DEBUG
static void taskFour()
{
	#ifdef DEBUG
	float grades[NUM_STU][NUM_CLS] = {{99,98,97,96,95},{94,93,92,91,90},\
	{89,88,87,86,85},{84,83,82,81,80},{79,78,77,76,75},\
	{99,98,97,96,95},{94,93,92,91,90},{89,88,87,86,85},\
	{84,83,82,81,80},{79,78,77,76,99}};
	#else
	float grades[NUM_STU][NUM_CLS];
	int i,j;
	for(i=0; i<NUM_STU; i++){
		for(j=0; j<NUM_CLS; j++){
			printf("\n请输入第 %d 位同学的第 %d 门成绩：", i+1, j+1);
			scanf("%f",&grades[i][j]);
		}
	}
	#endif
	stuAverage(grades);
	clsAverage(grades);
	grdMax(grades);
	stuVariance(grades);
}

/*第五题 
给定一个整数数组 nums 和一个目标值 target, 
在 nums 数组中找出和为目标值的 那两个整数，
并返回他们的数组下标。
例：给定 nums = {2, 7, 11, 15}, target = 9
因为 nums[0] + nums[1] = 2+7 = 9
所以返回 [0,1] 
*/ 
static void taskFive()
{
	int nums[] = {2,7,11,15};
	int target = 9;
	int i,j;
	int returnValue[2];
	for(i=0; i<sizeof(nums)/sizeof(int); i++){
		for(j=0; j<sizeof(nums)/sizeof(int); j++){
			if(nums[i]+nums[j] == target){
				returnValue[0] = i;
				returnValue[1] = j;
			}
		}
	}
	printf("[%d,%d]",returnValue[0],returnValue[1]);
}

