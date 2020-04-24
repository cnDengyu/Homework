#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int times = 0;

int caller()
{
	return ++times;
}

int main(int argc, char** argv) {
	int i;
	for(i=0; i<8; i++)
	{
		printf("我被调用了 %d 次\n", caller());
	}
	return 0;
}
