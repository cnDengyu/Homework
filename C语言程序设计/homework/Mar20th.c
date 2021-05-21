#include <stdio.h>
#include <string.h>

/*------------------------------------------

3月20日作业
章登宇 

-------------------------------------------*/ 

static void taskOne();
static void taskTwo();
static void taskThree();
static void taskFour();
static void taskFive();
static void taskSix();
static void taskSeven();
static void taskEight();

//程序入口
int homeworkMar20th(int argc, char** argv)
{
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	puts("\n-------------------------第四题-------------------------\n");
	taskFour();
	puts("\n-------------------------第五题-------------------------\n");
	taskFive();
	puts("\n-------------------------第六题-------------------------\n");
	taskSix();
	puts("\n-------------------------第七题-------------------------\n");
	taskSeven();
	puts("\n-------------------------第八题-------------------------\n");
	taskEight();
	return 0; 
}

/*第一题 
用迭代法求 x = √a 求平方根的迭代公式为
x[n+1] = 1/2 (x[n] + a/x[n])
要求前后两次求出的 x 的差的绝对值小于 10^-5 
*/
static void taskOne()
{
	double xn,xn1,a;
	do{
		printf("请输入a的值：");
	}while(scanf("%lf",&a) != 1);
	
	xn1 = 5.0;
	do{
		xn = xn1;
		xn1 = 1.0/2.0*(xn+a/xn);
	}while(xn1 - xn >= 0.00001 || xn1 - xn <= -0.00001);
	
	printf("平方根为%.5lf±0.00001",xn);
}

/*第二题 
求 Σk (1~100) + Σk^2 (1~50) + Σ1/k (1~10) 
*/
static void taskTwo()
{
	double sum = 0;
	int i = 0;
	for(i = 1; i <= 100; i++){
		sum += i;
	}
	for(i = 1; i <= 50; i++){
		sum += i*i;
	}
	for(i = 1; i<=10; i++){
		sum += 1.0/i;
	}
	printf("所求的和为%lf",sum);
}

/*第三题 
编写一个程序，提示用户输入一周工作的小时数，然后打印工资总额、税金和净收入。做如下假设：
	a. 基本工资 = 1000 美元/小时
	b. 加班（超过40小时） = 1.5 倍的时间
	c. 税率：	前 300 美元为 15%
				续 150 美元为 20%
				余下的为 25% 
*/
static void taskThree()
{
	double hours,salary,tax,printSalary;
	const double timeStage = 40;
	const double basic = 1000;
	const double extraSalary = 1.5;
	const double taxStage1 = 300;
	const double taxStage2 = 150;
	const double taxRate1 = 0.15;
	const double taxRate2 = 0.2;
	const double taxRate3 = 0.25;
	do{
		printf("请输入一周工作的小时数：");
	}while(scanf("%lf",&hours)!=1 || hours < 0 || hours > 7*24);
	
	//计算工资总额 
	if(hours <= timeStage){
		salary = hours*basic;
	}else if((hours -= timeStage) > 0){
		salary = timeStage*basic;
		salary += hours*basic*extraSalary;
	}
	printSalary = salary;
	
	//计算税金
	if(salary <= taxStage1){
		tax = salary*taxRate1;
	} else if((salary -= taxStage1) <= taxStage2){
		tax = taxStage1*taxRate1;
		tax += salary*taxRate2;
	} else if((salary -= taxStage2) > 0){
		tax = taxStage1*taxRate1 + taxStage2*taxRate2;
		tax += salary*taxRate3;
	}
	//输出
	printf("工资总额%.2lf，税金%.2lf，净收入%.2lf", printSalary, tax, printSalary-tax);
}

/*第四题 
编写一个程序读取输入，读到 # 字符时停止。程序要打印每个输入的字符以及对应的 ASCII 码（10进制）。
一行打印 8 个字符。建议：使用字符计数和求模运算符（%）在每 8 个循环周期时打印一个换行符 
*/
static void taskFour()
{
	int i = 0;
	char c[256];
	printf("请输入，以#终止：");
	scanf("%s",c);
	while(i<strlen(c) && c[i]!='#'){
		printf("%3d ",c[i]);
		if(++i%8 == 0){
			putchar('\n');
		}
	}
	fflush(stdin);
}

/*第五题 
有四个圆塔，圆心分别为 (2,2) (-2,2) (-2,-2) (2,-2)，圆半径为 1 
这四个塔的高度为 10 m ，塔以外无建筑物。今输入任一点的坐标，求该点的建筑高度（塔外的高度为零） 
*/
static void taskFive()
{
	double x,y,h;
	do{
		printf("请输入一点的坐标：");
	}while(scanf("(%lf,%lf)", &x, &y) != 2);
	
	if((x-2)*(x-2)+(y-2)*(y-2)>1 &&\
	(x+2)*(x+2)+(y-2)*(y-2)>1 &&\
	(x-2)*(x-2)+(y+2)*(y+2)>1 &&\
	(x+2)*(x+2)+(y+2)*(y+2)>1 ){
		h = 0;
	} else {
		h = 10;
	}
	printf("该点的建筑高度为%.0lf",h);
}

/*第六题 
有一个数学等式 AB*CD = BA*DC ，式中的一个字母代表一位数字，试找出所有符合上述要求的乘积式并打印输出 
*/
static void taskSix()
{
	int i1,i2,i3,i4,count;
	for(i1=1; i1<10; i1++){
		for(i2=1; i2<10; i2++){
			for(i3=1; i3<10; i3++){
				for(i4=1; i4<10; i4++){
					if((i1*10+i2)*(i3*10+i4) == (i2*10+i1)*(i4*10+i3) &&\
					i1!=i2 && i2!=i3 && i3!=i4 && i1!=i3 && i1!=i4 && i2!=i4 && i3!=i4){
						printf("%d%d*%d%d = %d%d*%d%d  ",i1,i2,i3,i4,i2,i1,i4,i3);
						if(++count == 5){
							putchar('\n');
							count = 0;
						}
					}
				}
			}
		}
	} 
}

/*第七题 
一百个铜钱买了一百只鸡，其中公鸡一只 5 钱、母鸡一只 3 钱，小鸡一钱 3 只，
问一百只鸡中公鸡、母鸡、小鸡各多少。 
*/
static void taskSeven()
{
	int x,y,z;
	//5x + 3y + 1/3z = 100
	//x + y + z = 100
	for(x=0; x<=20; x++){
		for(y=0; y<34; y++){
			for(z=0; z<=100; z++){
				if(x+y+z == 100 && 5*x+3*y+(float)z/3.0 == 100.0){
					printf("公鸡 %d 只，母鸡 %d 只，小鸡 %d 只\n",x,y,z);
				}
			}
		}
	}
}

/*第八题 
输出 1000 以内能被 3 整除且个位数为 6 的所有整数 
*/
static void taskEight()
{
	int i = 0;
	printf("1000以内能被3整除且个位数为6的所有整数为\n");
	for(i = 1; i <= 1000; i++){
		if(i%3 == 0 && i%10 == 6){
			printf("%d ",i);
		}
	} 
}
