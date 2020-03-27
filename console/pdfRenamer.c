#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <stddef.h>

/*--------------------------------------------

pdfReader (programThree) 代号 3 

fgets 没有给出想要的结果，所以改写了 myfgets

--------------------------------------------*/ 

char filenames[1000][30] = {}; //用于存储所有pdf文件的文件名 
int findFiles();	//用于查找文件夹内所有pdf文件 
char *myfgets(char *s, int n,  FILE *stream); //重写 fgets 函数使其认为 '\r' 也属于换行 

//程序入口 移植时请改为 main() 
int programThree(int argc, char** argv){
	int i;	//循环参量，控制读取的文件 
	int fileNum = 0;	//存储找到的总文件数量 
	int state = 0;
	FILE *fp = NULL;
	char buff[256];
	char newName[30];
	long filePosition = 0L;
	char whetherRename = 'N';
	
	fileNum = findFiles();	//查找目录下所有pdf文件，文件名存储到全局变量filenames中，返回总文件数 
	
	for(i = 0; i <= fileNum; i++){	//循环每一个文件 
		printf("\n开始处理文件%s\n",filenames[i]);
		fp = fopen(filenames[i], "r+");
		filePosition = 0L;		//检索位置归零 
		fseek(fp,filePosition,SEEK_SET);
		
		do{
			do{
			myfgets(buff,256,fp);
			filePosition = filePosition + (long)strlen(buff);

			//printf("%s",buff);		//调试时输出所有读到的字符串 
			//putchar('\n');
			
			if(!strncmp(buff,"stream",6)){		//之所以要在 stream 处作判断，是因为 
				//puts("（略去非文本流）");		//非文本流中含有让程序认为文件已经结束的特殊符号 
				while(strncmp(buff,"endstream",9)){	//到 endstream 处，非文本流截止 
					fseek(fp, ++filePosition, SEEK_SET);
					myfgets(buff,256,fp);
				}
				//puts("endstream");
			}

		}while(strncmp(buff,"/Title (",6));		//理论上，对于一个有目录的 pdf 文件，能读取到的第一个 /Title () 即为主题 
		
		sscanf(buff, "/Title (%[^\t\n)]", newName);
		strcat(newName,".pdf");

		printf("\n正在处理文件%s\n\
\n读取到标题%s，是否重命名？输入Y执行重命名，输入N则检索下一个可能的标题，输入其他则不再处理此文件。\n\
请注意：如果没能检测到下一个可能的标题，程序会进入死循环。\n",filenames[i],newName);
		scanf("%c",&whetherRename);
		getchar();		//用于消化掉上面输入产生的回车 
		
		}while(whetherRename == 'N');		//输入 N 则重新执行检索语句 
		
		fclose(fp);

		if(whetherRename == 'Y'){		//输入Y则执行重命名 
			if(rename(filenames[i], newName) < 0 ){ 
				printf("重命名出错!\n");
				perror("rename");
			} 
			else{ 
				printf("已经将%s重命名为%s\n", filenames[i], newName);
				system("pause");
			} 
		}else{ 		//输入其他则不再处理这个文件 
			printf("没有重命名%s\n",filenames[i]);
		}
		
		printf("文件%s处理完毕\n",filenames[i]);

	} 
	puts("所有文件处理完毕");
	system("pause");
}

int findFiles(){
	int i = 0;
	long handle;                                                     //用于查找的句柄	
	struct _finddata_t fileinfo;                                     //文件信息的结构体
	
	handle=_findfirst("*.pdf",&fileinfo);                          //第一次查找，找pdf文件 
	if(-1==handle){
		puts("没有找到pdf文件\n");
		return -1;
	}
	
	strcpy(filenames[0],fileinfo.name);	//将第一个文件名写入全局数组 
	printf("找到文件%s\n", fileinfo.name);
	while(!_findnext(handle,&fileinfo))                              //循环查找其他符合的文件，直到找不到其他的为止	
	{		
		i = i + 1;
		strcpy(filenames[i],fileinfo.name);	//将之后的文件名写入全局数组 
		printf("找到文件%s\n", fileinfo.name);
	}	
	_findclose(handle);                                              //关闭句柄		
	//printf("output done.\n");	
	//system("pause");
	return i;
}

//以 fgets() 为原型，仅仅添加了 || c == '\r'  语句 
char *myfgets(char *s, int n,  FILE *stream)   
{  
    register int c;  
    register char *cs;  
    cs=s;  
    while(--n>0 &&(c = getc(stream))!=EOF)
    	if ((*cs++=  c) =='\n' || c == '\r')  //这里添加了 || c == '\r' 
        	break;
    *cs ='\0';  
    return (c == EOF && cs == s) ?NULL :s ;  
}
