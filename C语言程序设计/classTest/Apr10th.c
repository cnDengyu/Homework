#include <stdio.h>
#include <string.h> 

/*------------------------------------------

4 月 10 日课堂实验 
章登宇 
正文开始自：23行 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 

int classTestApr10th(int argc, char** argv)
{
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	return 0;
}

/*第一题
输入一行字符，统计其中有多少个单词，单词之间用空格分开。
如输入：I am Chinese 则输出“有 3 个单词” 
*/ 
static void taskOne()
{
	char buffer[256];//存储输入的字符串 
	int i = 0;
	int num = 0;
	printf("请输入一行字符：");
	gets(buffer);//安全代码：fgets(buffer,256,stdin);
	do
	{ 
		if((buffer[i] == ' ' || buffer[i] == '\0') && buffer[i>0?i-1:0] != ' ')
		//如果当前字符为空格或字符串尾，且它前一个字符（若为首字符，则取本身）不为空格
		{
			num++;
		}
	}while((buffer[i++]) != '\0');//循环直到检测到字符串尾 
	printf("有 %d 个单词",num); 
} 

/*第二题 
输入一行字符，找出其中所有包含某个字符串的单词，输入的单词用空格分开
如输入：app 以及 apple evil application sad 等单词
则输出“符合条件的单词有：apple application 
*/
#define MAX_WORD_LENGTH 15
#define MAX_WORD_NUM 30
static void taskTwo()
{
	char buffer[256];	//存储输入的字符串 
	int i = 0;
	int j = 0;
	int num = 0;
	int indexStart = 0;	//暂存一个单词的起点 
	int indexEnd = 0; 	//暂存一个单词的终点 
	int length;			//暂存一个单词的长度
	char key[MAX_WORD_LENGTH] = "";	//存放关键词 
	char keyLength = 0;
	bool patt[MAX_WORD_NUM] = {};	//存放每个单词的匹配结果，初值为假 
	char words[MAX_WORD_NUM][MAX_WORD_LENGTH]; //存放所有单词 
	
	//提示输入关键词和字符串 
	printf("请输入关键词:");
	scanf("%s",key);
	getchar();		//消化回车 
	printf("请输入一行字符：");
	gets(buffer);	//安全代码：fgets(buffer,256,stdin);
	
	//把输入的字符串分解成多个单词 
	do
	{ 
		if((buffer[i] == ' ' || buffer[i] == '\0'))
		//如果当前字符为空格或字符串尾，且它前一个字符（若为首字符，则取本身）不为空格
		{
			if(buffer[i>0?i-1:0] != ' ')
			{
				indexEnd = i-1;//空格前一个非空格字符为单词终点 
				if(num++ > MAX_WORD_NUM)
				{
					printf("异常，单词数量溢出\n");
					return;
				}
				length = indexEnd-indexStart+1;
				if(length < MAX_WORD_LENGTH)
				{
					strncpy(words[j], &buffer[indexStart], length);
					words[j++][length] = '\0';
				}
				else
				{
					printf("异常，单词长度溢出\n");
					return; 
				}
			}
			indexStart = i+1;//空格后一个非空格字符为单词起点 
		}
	}while((buffer[i++]) != '\0');//循环直到检测到字符串尾 
	
	//分别处理每一个单词 
	keyLength = strlen(key);//关键词长度 
	for(i=0; i<num; i++)
	{
		length = strlen(words[i])>keyLength?strlen(words[i])-keyLength+1:0; 
		for(j=0; j<length; j++)
		{
			if(!strncmp(&words[i][j], key, keyLength))
			//将关键词与输入词的每个字母连带后几个字母比较 
			{
				patt[i] = true;
				break;
			}
		}
//		printf("%s",words[i]);
	}
	
	//输出匹配结果
	printf("符合条件的单词有：");
	for(i=0; i<num; i++)
	{
		if(patt[i])
		{
			printf("%s ",words[i]);
		}
	} 
}
