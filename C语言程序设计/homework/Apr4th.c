#include <stdio.h>

/*------------------------------------------

4 月 4 日作业 
章登宇 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

int homeworkApr4th(int argc, char** argv)
{
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/*第一题
编写一个函数，把两个数组中相对应的元素相加，然后把结果储存到第三个数组中。
也就是说，如果数组 1 中包含的值是 2、4、5、8，数组 2 中包含的值是 1、0、4、6，
那么该函数把 3、4、9、10 赋给第三个数组。
函数接受 3 个数组名和一个数组大小。在一个简单的程序中测试该函数。
*/
#define ARRAY_TYPE int
static void copyArray(ARRAY_TYPE a[], ARRAY_TYPE b[], ARRAY_TYPE c[], int length)
{
	int i;

	for(i=0; i<length; i++){
		c[i] = a[i] + b[i];
	}
}
static void taskOne()
{
	ARRAY_TYPE a[4] = {2,4,5,8};
	ARRAY_TYPE b[4] = {1,0,4,6};
	ARRAY_TYPE c[4];
	int i;
	copyArray(a,b,c,4);
	printf("c中的值为：");
	for(i=0; i<4; i++){
		printf("%5d",c[i]);
	}
	putchar('\n');
}

/*第二题
输入一个 N*N 的矩阵 (N 为用户输入值），
将矩阵主对角线元素的值与反对角线对应位置上元素的值进行交换。
例如，当 N=4 时，下列矩阵 
1	2	3	4				4	3	2	1 
5	6	7	8	交换后为：	5	7	6	8 
9	10	11	12				9	11	10	12 
13	14	15	16 				16	14	15	13 
*/
#define MARTIX_TYPE int
#define MARTIX_TYPE_INPUT "%d"
#define MARTIX_TYPE_OUTPUT "%5d"
static void taskTwo()
{
	int i,j,n;
	printf("请输入N：");
	scanf("%d",&n);
	MARTIX_TYPE martix[n][n];
	MARTIX_TYPE temp[n];
	printf("请输入一个%d*%d的矩阵：\n",n,n);
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			scanf(MARTIX_TYPE_INPUT,&martix[i][j]);
		}
	}
	for(i=0,j=n-1; i<n,j>=0; i++,j--){
		temp[i] = martix[i][i];
		martix[i][i] = martix[i][j];
		martix[i][j] = temp[i];
	}
	printf("替换后的矩阵为:\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf(MARTIX_TYPE_OUTPUT,martix[i][j]);
		}
		putchar('\n');
	}
} 

/*第三题
定义一个整型数组，设计程序获取此数组内的最大值和最小值
*/
static void taskThree()
{
	int a[] = {1,2,5,4,3};
	int length = sizeof(a)/sizeof(int);
	int i,max,min;
	max = min = a[0];
	for(i=0; i<length; i++){
		max = a[i]>max?a[i]:max;
		min = a[i]<min?a[i]:min;
	}
	printf("最大值为：%d，最小值为：%d\n",max,min);
} 
