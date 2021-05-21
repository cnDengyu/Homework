/*------------------------------------------

5 月 22 日作业 
章登宇 	

第五题程序入口：92行 taskOne()
第六题程序入口：148行 taskSix()
第七题程序入口：199行 taskSeven()
第八题程序入口：264行 taskEight()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 

#include <stdio.h>

#define DEBUG

static void taskFive();
static void taskSix(); 
static void taskEleven();
static void taskEight();

//程序入口 
int homeworkMay22nd(int argc, char** argv)
{
	puts("\n----------------------5月22日作业---------------------\n");
	#ifdef DEBUG
	printf("调试模式已启用\n");
	#endif
	puts("\n-------------------------第五题-------------------------\n");
	taskFive();
	puts("\n-------------------------第六题-------------------------\n");
	taskSix();
	puts("\n-------------------------第七题-------------------------\n");
	taskEleven();
	puts("\n-------------------回滚至第七题执行前-------------------\n");
	taskSix(); 
	puts("\n-------------------------第八题-------------------------\n");
	taskEight();
	return 0;
}

/* 第五题
 有 5 个学生，每个学生有 3 们课程的成绩，从键盘输入学生数据
 （包括学号，姓名，3 门课程成绩），计算出平均成绩，
 将原有数据和计算出的平均分数存放在磁盘文件“stud”中。 
*/

// 定义学生数据
#define MAX_LEN_NAME 15
#define NUM_COURSE 3 
typedef struct 
{
	int id;
	char name[MAX_LEN_NAME];
	int grades[NUM_COURSE];
	double average;
}Student;

static double student_calcAverage(Student *stu)
{
	int i=0;
	int sum = 0;
	for(i=0; i<NUM_COURSE; i++)
	{
		sum += stu->grades[i];
	}
	
	stu->average = (double) sum / NUM_COURSE;
	return stu->average;
}

static void student_printToScreen(Student *stu)
{
	printf("%d %s %d %d %d %lf\n", stu->id, stu->name, 
	stu->grades[0], stu->grades[1], stu->grades[2], stu->average);
}

static void student_printToFile(Student *stu, FILE *fp)
{
	fprintf(fp, "%d , %s , %d , %d , %d , %lf \n", stu->id, stu->name, \ 
	stu->grades[0], stu->grades[1], stu->grades[2], stu->average);
	#ifdef DEBUG
	printf("写入：");
	student_printToScreen(stu);
	#endif
}

#define NUM_STU 5
static void taskFive()
{
	int i;
	#ifdef DEBUG
	//编译期输入
	Student stus[NUM_STU]={{1001,"Zhang",{99,98,78},0},\
	{1002,"Wang",{87,88,90},0},{1003,"Zhao",{89,82,77},0},\
	{1004,"Li",{100,69,75},0},{1005,"Wei",{83,92,81},0}};
	#else 
	// 屏幕输入 
	Student stus[NUM_STU];
	Student *p;
	printf("请输入 5 名学生的学号、姓名、3门课程成绩：\n");
	for(i=0; i<NUM_STU; i++)
	{
		p = &stus[i];
		scanf("%d %s %d %d %d",\
		&p->id, p->name, &p->grades[0], &p->grades[1], &p->grades[2]);
	}
	#endif
	
	// 数据处理
	for(i=0; i<NUM_STU; i++)
	{
		student_calcAverage(&stus[i]);
	} 
	
	// 写盘
	FILE *fp;
	if((fp=fopen("stud.csv","w+"))==NULL)
	{
		printf("无法打开或创建文件\n");
		return;
	}
	for(i=0; i<NUM_STU; i++)
	{
		student_printToFile(&stus[i], fp);
	}
	fclose(fp);
}

/* 第六题
 将第 5 题“stud”文件中的学生书局，按平均分进行排序处理，
 将已排序的学生数据存入一个新文件“stu_sort”中。
 */ 

static void student_readFromFile(Student* stu, FILE *fp)
{
	fscanf(fp, "%d , %s , %d , %d , %d , %lf \n", &stu->id, stu->name, \
	&stu->grades[0], &stu->grades[1], &stu->grades[2], &stu->average);
	#ifdef DEBUG
	printf("读入：");
	student_printToScreen(stu);
	#endif
}

static void taskSix()
{
	int i;
	// 读文件 
	Student stus[NUM_STU] = {};
	FILE *fp;
	if((fp=fopen("stud.csv","r+"))==NULL)
	{
		printf("读取文件失败\n");
		return;
	}
	for(i=0; i<NUM_STU; i++)
	{
		student_readFromFile(&stus[i], fp);
	}
	fclose(fp);
	
	// 排序
	int j;
	int order[NUM_STU] = {0,1,2,3,4};
	int temp;
	for(i=0; i<NUM_STU; i++)
	{
		for(j=i; j<NUM_STU; j++)
		{
			if(stus[order[j]].average>stus[order[i]].average)
			{
				temp = order[j];
				order[j] = order[i];
				order[i] = temp;
			}
		}
	} 
	
	// 依序输出
	if((fp=fopen("stu_sort.csv", "w+"))==NULL)
	{
		printf("无法打开或创建文件\n");
		return;
	}
	for(i=0; i<NUM_STU; i++)
	{
		student_printToFile(&stus[order[i]], fp);
	}
	fclose(fp);
}

/* 第七题 
将第六题已排序的学生成绩文件进行插入处理。插入一个学生的三门课程成绩，
程序先计算新插入学生的平均成绩，然后将它按成绩高低顺序插入，插入后建立一个新文件。
*/ 
static void taskEleven()
{
	int i;
	// 读文件
	Student stus[NUM_STU];
	FILE *fp;
	if((fp=fopen("stu_sort.csv", "r"))==NULL)
	{
		printf("读取文件失败\n");
		return;
	}
	for(i=0; i<NUM_STU; i++)
	{
		student_readFromFile(&stus[i], fp);
	}
	fclose(fp);
	 
	#ifdef DEBUG
	// 编译期输入
	Student toInsert = {1021, "Cai", {85,86,87}, 0}; 
	#else 
	// 屏幕输入
	Student toInsert;
	printf("请输入要插入的学生的学号、姓名、三门成绩：\n");
	scanf("%d %s %d %d %d", &toInsert->id, toInsert->name, \
	&toInsert->grades[0], &toInsert->grades[1], &toInsert->grades[2]);
	#endif 
	
	// 记录插入位置 
	int insertIndex = NUM_STU;
	bool isFound = false;
	student_calcAverage(&toInsert);
	for(i=0; i<NUM_STU; i++)
	{
		if(stus[i].average<toInsert.average)
		{
			insertIndex = i;
			isFound = true;
			break;
		}
	}
	
	// 写文件
	if((fp=fopen("stu_sort_new.csv", "w+"))==NULL)
	{
		printf("打开或创建文件失败\n");
		return;
	} 
	for(i=0; i<NUM_STU; i++)
	{
		if(i == insertIndex)
		{
			student_printToFile(&toInsert, fp);
		}
		student_printToFile(&stus[i], fp);
	}
	if(NUM_STU == insertIndex)
	{
		student_printToFile(&toInsert, fp);
	}
	fclose(fp);
}
/* 第八题 
将第 7 题结果仍存入原有的“stu_sort”文件而不另新建文件。 
*/
static void taskEight()
{
	int i;
	// 读文件
	Student stus[NUM_STU];
	FILE *fp;
	if((fp=fopen("stu_sort.csv", "r"))==NULL)
	{
		printf("读取文件失败\n");
		return;
	}
	for(i=0; i<NUM_STU; i++)
	{
		student_readFromFile(&stus[i], fp);
	}
	fclose(fp);
	 
	#ifdef DEBUG
	// 编译期输入
	Student toInsert = {1021, "Cai", {85,86,87}, 0}; 
	#else 
	// 屏幕输入
	Student toInsert;
	printf("请输入要插入的学生的学号、姓名、三门成绩：\n");
	scanf("%d %s %d %d %d", &toInsert->id, toInsert->name, \
	&toInsert->grades[0], &toInsert->grades[1], &toInsert->grades[2]);
	#endif 
	
	// 记录插入位置 
	int insertIndex = NUM_STU;
	bool isFound = false;
	student_calcAverage(&toInsert);
	for(i=0; i<NUM_STU; i++)
	{
		if(stus[i].average<toInsert.average)
		{
			insertIndex = i;
			isFound = true;
			break;
		}
	}
	
	// 写文件
	if((fp=fopen("stu_sort.csv", "w+"))==NULL)
	{
		printf("打开或创建文件失败\n");
		return;
	} 
	for(i=0; i<NUM_STU; i++)
	{
		if(i == insertIndex)
		{
			student_printToFile(&toInsert, fp);
		}
		student_printToFile(&stus[i], fp);
	}
	if(NUM_STU == insertIndex)
	{
		student_printToFile(&toInsert, fp);
	}
	fclose(fp);
}
