#include <stdio.h>
#include <string.h> 

/*------------------------------------------

4 月 10 日作业 
章登宇 	

第一题程序入口：37行 taskOne()
第二题程序入口：75行 taskTwo()
第三题程序入口：91行 taskThree()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int homeworkApr10th(int argc, char** argv)
{
	puts("\n--------------------4月10日课后作业---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/*第一题
输入一行字符，分别统计出其中英文字母、空格、数字和其他字符的个数 
*/
static void taskOne()
{
	char buffer[256];
	char c;	//暂存一个字符 
	int i = 0;
	int num_letter = 0;
	int num_space = 0;
	int num_number = 0;
	int num_others = 0;
	printf("请输入一行字符：");
	fgets(buffer, 256, stdin);		//gets(buffer)的安全代码 
	while((c=buffer[i++])!= '\n')	//检测字符直到字符串尾 
	{
		if( (c<='Z'&&c>='A') || (c<='z'&&c>='a') )
		{
			num_letter++;
			continue;
		}
		if( c>='0'&&c<='9')
		{
			num_number++;
			continue;
		}
		if( c == ' ' )
		{
			num_space++;
			continue;
		}
		num_others++;
	}
	printf("英文字母有 %d 个，空格有 %d 个，数字有 %d 个，其他字符有 %d 个。\n",\
	num_letter, num_space, num_number, num_others);
} 

/*第二题
输入一行字符，输出其反序字符串 
如输入 string 则输出 gnirts 
*/
static void taskTwo()
{
	char buffer[256];
	int i=0;
	printf("请输入一行字符：");
	fgets(buffer,256,stdin);	//gets(buffer)
	for(i=strlen(buffer)-1; i>=0; i--)
	{
		printf("%c",buffer[i]);
	}
}

/*第三题
输入一行字符，将单词反序输出，输入的单词用空格分开 
如输入 see you later 则输出 later see you 
*/ 
static void taskThree()
{
//拷贝自课堂练习-开始----------------------------------- 
#define MAX_WORD_LENGTH 15
#define MAX_WORD_NUM 30
	char buffer[256];	//存储输入的字符串 
	int i = 0;
	int j = 0;
	int num = 0;
	int indexStart = 0;	//暂存一个单词的起点 
	int indexEnd = 0; 	//暂存一个单词的终点 
	int length;			//暂存一个单词的长度
	char words[MAX_WORD_NUM][MAX_WORD_LENGTH]; //存放所有单词 
	
	printf("请输入一行字符：");
	fgets(buffer,256,stdin);	//gets(buffer); 
	
	//把输入的字符串分解成多个单词 
	while((buffer[i]) != '\0')//循环直到检测到字符串尾 
	{ 
		if((buffer[i] == ' ' || buffer[i] == '\n'))
		//如果当前字符为空格或换行，且它前一个字符（若为首字符，则取本身）不为空格
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
		i++;
	}
//拷贝自课堂练习-结束-------------------------------------------
	
	//输出
	for(i=num-1; i>=0; i--)
	{
		printf("%s ",words[i]);
	} 
}
