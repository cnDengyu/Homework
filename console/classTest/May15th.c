#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------

5 月 15 日课堂练习 
章登宇 	

第一题程序入口：46行 taskOne()
第二题所求函数：106行 deleteNode 
第三题所求函数：160行 insertNode 

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int classTestMay15th(int argc, char** argv)
{
	puts("\n----------------------5月15日实验课---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/*第一题
有三个学生， 每个学生的数据包括学号、姓名及两门成绩。
从键盘输入学生的数据，要求输出两门课程的总平均成绩，以及最高分学生的学号 
*/
#define NAME_LEN 10
typedef struct
{
	int id;
	char name[NAME_LEN];
	int grade1;
	int grade2;
} student;
static void taskOne()
{
	//定义 
	student students[3];
	int i;
	
	//输入
	for(i=0; i<3; i++)
	{
		printf("请输入第 %d 个学生的学号：", i+1);
		scanf("%d", &students[i].id);
		printf("请输入第 %d 个学生的姓名：", i+1);
		scanf("%s", students[i].name);
		printf("请输入第 %d 个学生的第 1 门成绩：", i+1);
		scanf("%d", &students[i].grade1);
		printf("请输入第 %d 个学生的第 2 门成绩：", i+1);
		scanf("%d", &students[i].grade2);
	} 
	
	//处理
	double average1,average2;
	int max, id;
	//计算平均成绩
	average1 = average2 = 0;
	for(i=0; i<3; i++)
	{
		average1 += (double)students[i].grade1;
		average2 += (double)students[i].grade2;
	}
	average1 = average1/3.0;
	average2 = average2/3.0;
	//计算最高分学生
	max = students[0].grade1 + students[0].grade2;
	id = students[0].id;
	for(i=1; i<3; i++)
	{
		if(students[i].grade1 + students[i].grade2 > max)
		{
			max = students[i].grade1 + students[i].grade2;
			id = students[i].id;
		}
	}
	
	//输出
	printf("第一门课程的总平均成绩为：%lf\n", average1);
	printf("第二门课程的总平均成绩为：%lf\n", average2);
	printf("最高分学生的学号为：%d", id); 
} 

/*第二题
编写一个函数 delete, 用来删除动态链表中的指定第 N 个节点 
*/
//定义链表节点 
typedef student listContent;	//定义链表存储的内容 
typedef struct Example
{
	listContent content;
	struct Example* next;
} listNode;					//定义链表节点 
//题目所求的 delete 函数 
static void deleteNode(listNode* head, int n)
{
	listNode* p = head;
	listNode* temp;
	
	//找到第 n-1 个节点 
	int i;
	for(i=1; i<n-1; i++)
	{
		if(p!=NULL)	//空安全 
		{ 
			if(p->next != NULL)
			{
				p = p->next;
			}
		}
		else
		{
			printf("没能找到第%d个节点，以最后一个代替\n");
		}
	}
	
	//删除节点 
	if(p == NULL)					//传入的头节点为空，不进行操作 
	{
		printf("传入的头节点为空\n");
	}
	else if(p->next == NULL)		//第 n 个节点为空，不进行操作 
	{
		printf("要删除的节点为空\n");
	}
	else if(p->next->next == NULL)	//要删除的恰好是最后一个节点 
	{
		free(p->next);
		p->next = NULL;
	}
	else							//前、后节点均存在 
	{
		temp = p->next->next;
		free(p->next);
		p->next = temp; 
	}
}
static void taskTwo()
{
	puts("所写的删除链表节点的函数为\n static void deleteNode(listNode* head, int n)");
}

/*第三题
编写一个函数 insert, 用来向一个动态链表插入节点 
*/
//链表节点的定义在上一题中 
//下面这个函数是题目所求的 insert 函数 
//参数： 头节点、第几个、插入节点存储的内容 
static listNode* insertNode(listNode* head, int n, listContent newContent)
{
	listNode* p = head;
	listNode *temp, *newNode;
 
	//创建新节点（暂不连接） 
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->content = newContent;
	
	//找到第 n-1 个节点 
	int i;
	for(i=1; i<n-1; i++)
	{
		if(p!=NULL)	//空安全 
		{ 
			if(p->next != NULL)
			{
				p = p->next;
			}
		}
		else
		{
			printf("没能找到第%d个节点，以最后一个代替\n");
		}
	}
	//连接新节点 
	if(p == NULL)				//这种情况只有可能头节点为空 
	{
		head = newNode;			//新节点直接作为新的头节点 
	}
	else if(p->next == NULL)	//这种情况可能是尾节点，只有前节点没有后节点 
	{
		head->next = newNode;
		newNode->next = NULL;
	}
	else						//连接前后节点 
	{
		temp = p->next;
		newNode->next = temp;
		p->next = newNode;
	}
	return newNode;
}
static void taskThree()
{
	puts("所写的插入链表节点的函数为\n static void insertNode(listNode* head, int n, listContent newContent)");
}
