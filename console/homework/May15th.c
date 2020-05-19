#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------

5 月 15 日作业 
章登宇 	

第一题程序入口：45行 taskOne()
第二题所求函数：104行 find()
第三题程序入口：205行 taskThree()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int homeworkMay15th(int argc, char** argv)
{
	puts("\n----------------------5月15日作业---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/*第一题 
定义一个枚举类型 level，用枚举元素代表成绩的“等级”
如：90分以上为优（excellent），80-90分之间为良（good），
60-70分之间为中（general），60分以下为差（fail），
通过键盘输入一个学生的成绩，然后输出该生成绩的等级。 
*/
enum level
{
	excellent,good,general,fail
};
static void taskOne()
{
	//输入
	int input;
	printf("请输入一个学生的成绩：");
	scanf("%d",&input);
	
	//处理
	enum level lev;
	switch(input/10)
	{
		case 10: case 9:
			lev = excellent;
		break;
		case 8:
			lev = good;
		break;
		case 7: case 6:
			lev = general;
		break;
		case 5: case 4: case 3: case 2: case 1: case 0:
			lev = fail;
		break;
		default:
			printf("分数不合理\n");
		break;
	} 
	
	//输出
	switch(lev)
	{
		case excellent:
			printf("成绩为优\n");
		break;
		case good:
			printf("成绩为良\n");
		break;
		case general:
			printf("成绩为中\n");
		break;
		case fail:
			printf("成绩为差\n");
		break;
	} 
}

/*第二题 
编写一个函数 find，用来在链表中查找一个数据是否存在。
如果存在，输出是第几个节点 
*/
//定义链表存储的数据类型
typedef int listContent;
//定义链表节点 
typedef struct listNode
{
	listContent content;
	listNode* next;
} listNode;

static int find(listNode* head, listContent toFind)
{
	int i = 0;
	while((head = head->next) != NULL)
	{
		i++;
		if(head->content == toFind)
		{
			printf("第%d个节点即为所求\n");
			return i;
		}
	}
	return 0;
}
static void taskTwo()
{
	puts("所写的函数为static int find(listNode* head, listContent toFind)");
}

/*第三题 
存在两个链表 a, b（链表长度均可设为 3），设节点中包含学号、姓名，
要求把两个链表合并，按学号升序排列 
*/
//定义链表节点
#define MAX_LEN 10
typedef struct studentListNode 
{
	int id;
	char name[MAX_LEN];
	studentListNode* next;
} studentListNode;
//函数：在某节点之后插入元素 
static studentListNode* insertNext(studentListNode* toInsert, int id, char* name)
{
	studentListNode *newNode, *temp;
	newNode = (studentListNode*) malloc(sizeof(studentListNode));
	newNode->id = id;
	strncpy(newNode->name,name,MAX_LEN); 
	if(toInsert == NULL)
	{
		newNode->next = NULL;
	}
	else if(toInsert->next == NULL)
	{
		toInsert->next = newNode;
		newNode->next = NULL;
	}
	else
	{
		temp = toInsert->next;
		toInsert->next = newNode;
		newNode->next = temp;
	}
	return newNode;
}

static studentListNode* mergeById(studentListNode* headA, studentListNode* headB)
{
	//检查链表 A 的顺序
	int checkId = headA->id;
	studentListNode *pA = headA;
	do{
		if(pA->id < checkId)
		{
			printf("链表a没有按顺序排列，暂时无法合并\n");
			return NULL;
		}
	}while((pA=pA->next)!=NULL);
	
	//在合适的位置把链表 b 中节点插入链表a
	studentListNode* pB = headB;
	studentListNode* last = NULL;
	studentListNode* newStart;
	do{
		pA = headA;
		while(pA!=NULL && pA->id < pB->id)
		{
			last = pA;
			pA=pA->next; 
		}
		if(last == NULL)	//在头部插入 
		{
			newStart = (studentListNode*) malloc(sizeof(studentListNode));
			newStart->id = pB->id;
			strncpy(newStart->name, pB->name, MAX_LEN);
			newStart->next = headA; 
			headA = newStart;
		}
		else
		{
			insertNext(last, pB->id, pB->name);
		}
	}while((pB=pB->next) != NULL);
	return headA;
}
static void print(studentListNode* head)
{
	do{
		printf("%d   %s\n", head->id, head->name);
	}while((head=head->next)!=NULL);
}
static void taskThree()
{
	//创建链表 a 和 b 
	studentListNode *headA, *headB, *pA, *pB;
	headA = headB = NULL;
	headA = pA = insertNext(headA, 1, "学生1");
	pA = insertNext(pA, 2, "学生2");
	pA = insertNext(pA, 3, "学生3");
	headB = pB = insertNext(headB, 5, "学生5");
	pB = insertNext(pB, 4, "学生4");
	pB = insertNext(pB, 6, "学生6");
	
	//输出原表
	print(headA);
	print(headB); 
	
	//合并链表 a 和 b
	headA = mergeById(headA, headB);
	
	//输出新表 
	print(headA);
}
