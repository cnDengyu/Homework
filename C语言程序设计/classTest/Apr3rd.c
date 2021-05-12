#include <stdio.h>

/*------------------------------------------

4 月 3 日课堂实验 
章登宇 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 

int classTestApr3rd(int argc, char** argv)
{
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	return 0;
}

/*第一题 
定义一个数组来储存 12 个学生的成绩 {72,89,65,58,87,91,53,82,71,93,76,68}，
统计各成绩等级（90分以上为 A，80~89分为 B，70~79分为 C，60~69分为 D，60分以下为 E）
的学生人数，并输出。 
*/
#define LEVELS 5
static void taskOne()
{
	int grades[] = {72,89,65,58,87,91,53,82,71,93,76,68};
	int studentNum = sizeof(grades)/sizeof(int);
	int numInLevel[LEVELS] = {}; 
	int i = 0;
	for(i=0; i<studentNum; i++)
	{
		switch(grades[i]/10)
		{
			case 10:case 9:
				numInLevel[0] += 1;
			break;
			case 8:
				numInLevel[1] += 1;
			break;
			case 7:
				numInLevel[2] += 1;
			break;
			case 6:
				numInLevel[3] += 1;
			break;
			case 5:case 4:case 3:case 2:case 1:case 0:
				numInLevel[4] += 1;
			break;
			default:
				printf("第%d个成绩（%d）不在0~100中",i+1,grades[i]);
			break;
		}
	}
	printf("A等级	B等级	C等级	D等级	E等级\n");
	for(i=0; i<LEVELS; i++)
	{
		printf("%-8d",numInLevel[i]); 
	}
	putchar('\n');
}

/*第二题
输入一个 3*3 的矩阵，将矩阵主对角线元素的值与反对角线对应位置上元素的值进行交换。
例如，下列矩阵：
1	2	3				3	2	1 
4	5	6	交换后为	4	5	6 
7	8	9 				9	8	7 
*/ 
static void taskTwo()
{
	double martix[3][3];
	double temp[3];
	int i,j;
	printf("请输入一个3*3的矩阵：\n");
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			scanf("%lf",&martix[i][j]);
		}
	}

	for(i=0,j=3-1; i<3,j>=0; i++,j--){
		temp[i] = martix[i][i];
		martix[i][i] = martix[i][j];
		martix[i][j] = temp[i];
	}
	
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			printf("%lf ",martix[i][j]);
		}
		putchar('\n');
	}
}
