#include <stdio.h>

/*------------------------------------------

5 月 22 日课堂练习 
章登宇 	

第一题程序入口：52行 taskOne()
第二题程序入口：101行 taskTwo()
第三题程序入口：146行 taskThree()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int classTestMay22nd(int argc, char** argv)
{
	puts("\n----------------------5月22日实验课---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/* 第一题
ppt 28 页：从键盘输入10个学生的相关数据，
然后把它们转存到磁盘文件上去
*/
// 调试模式 
//#define DEBUG 
// 定义存放的文件名 
#define DIR_DATA "student_data.csv"
// 定义学生数据 
#define MAX_LEN_NAME 10
#define MAX_LEN_ADDR 15
typedef struct
{
	char name[MAX_LEN_NAME];
	int id;
	int age;
	char addr[MAX_LEN_ADDR];
}Student;
#define NUM_STU 10
static void taskOne()
{
	int i=0;
	#ifdef DEBUG
	// 编译期输入 
	Student stus[NUM_STU] = {{"Zhang",1001,19,"room_101"},\
	{"Sun",1002,20,"room_102"},{"Tan",1003,21,"room_103"},\
	{"Ling",1004,21,"room_104"},{"Li",1006,22,"room_105"},\
	{"Wang",1007,20,"room_106"},{"Zhen",1008,16,"room_107"},\
	{"Fu",1010,18,"room_108"},{"Qin",1012,19,"room_109"},\
	{"Liu",1014,21,"room_110"}};
	#else
	// 屏幕输入
	Student stus[NUM_STU];
	printf("请输入10个学生的数据：\n");
	for(i=0; i<NUM_STU; i++)
	{
		scanf("%s", stus[i].name);
		scanf("%d", &stus[i].id);
		scanf("%d", &stus[i].age);
		scanf("%s", stus[i].addr);
	}
	#endif
	
	// 写文件
	FILE *fp;
	if((fp = fopen(DIR_DATA, "w")) == NULL)
	{
		printf("无法打开或创建文件\n");
		return;
	}
	else
	{
		for(i=0; i<NUM_STU; i++)
		{
			// 输出到文件缓冲区
			fprintf(fp, "%s ,%d ,%d ,%s\n", \
			stus[i].name, stus[i].id, stus[i].age, stus[i].addr);
		}
		
		// 关闭文件
		fclose(fp); 
	}
} 

/* 第二题
ppt 37 页：在磁盘上存有 10 个学生的相关数据，
要求将第 1，3，5，7，9 个学生的数据输出 
*/
static void taskTwo()
{
	// 读文件
	FILE *fp;
	Student stus[NUM_STU];
	int i;
	if((fp = fopen(DIR_DATA, "r")) == NULL)
	{
		printf("读取文件失败\n");
		return;
	}
	else
	{
		for(i=0; i<NUM_STU; i++)
		{
			fscanf(fp, "%s ,%d ,%d ,%s", \
			stus[i].name, &stus[i].id, &stus[i].age, stus[i].addr); 
		}
		
		// 输出 
		printf("学生数据为：\n");
		for(i=0; i<NUM_STU; i++)
		{
			printf("%-10s%4d%4d%15s\n",\
			stus[i].name, stus[i].id, stus[i].age, stus[i].addr);
		} 
	}
}

/* 第三题
从键盘输入一个字符串，将其中的小写字母全部转换为大写字母，
然后输入到一个磁盘文件“test”中进行保存。
*/
static void lowerToUpper(char* buffer, int max)
{
	char c; 
	while((c=*buffer)!='\0' && max-->0)
	{
		if('a'<=c && c<='z')
		{
			*buffer = c-32;
		}
		buffer++;
	}
} 
static void taskThree()
{
	// 屏幕输入
	char buffer[256];
	printf("请输入一个字符串：");
	scanf("%s", buffer);
	
	//处理
	lowerToUpper(buffer, 256);
	
	//写文件
	FILE *fp;
	if((fp=fopen("test.txt","w"))==NULL)
	{
		printf("打开或创建文件失败\n");
		return;
	} 
	else
	{
		fputs(buffer, fp);
		fclose(fp);
	} 
} 
