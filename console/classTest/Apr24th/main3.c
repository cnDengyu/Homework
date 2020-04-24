#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

extern double circleS(double);
extern double circleLoopS(double,double);

int main(int argc, char** argv) {
	double s1 = circleS(2.2);
	double s2 = circleLoopS(3.0,2.0);
	printf("圆的面积为 %lf\n", s1);
	printf("圆环的面积为 %lf\n", s2);
	return 0;
}
