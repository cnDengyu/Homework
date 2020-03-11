#include <windows.h>
extern long myTime;

void onTimer(HWND hwnd){
	myTime++;
	InvalidateRect(hwnd, NULL, FALSE);
}
