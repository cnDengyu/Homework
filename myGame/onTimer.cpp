#include <windows.h>
long myTime;
long myLastTime;

int dangoPositionX = 100;
int dangoPositionY = 100;
int dangoVelocityX = 80;
int dangoVelocityY = 80;

extern void onPaint(HWND hwnd, HDC hdc);

void onTimer(HWND hwnd){
	HDC hdc;
	HBITMAP hBmpMem,hPreBmp;
	RECT rect,smallRect;
	
	myTime = GetTickCount();
	
	if(myLastTime){
		hdc = GetDC(hwnd);
		GetClientRect(hwnd,&rect); 
		
		dangoPositionX = dangoPositionX + (myTime - myLastTime) * dangoVelocityX / 1000;
		dangoPositionY = dangoPositionY + (myTime - myLastTime) * dangoVelocityY / 1000;
	
		/* ÔÚË«»º³åÖÐ»æÍ¼ */
		onPaint(hwnd, hdc);
		
		smallRect.bottom = rect.bottom - 20;
		smallRect.left = rect.left + 20;
		smallRect.right = rect.right - 20;
		smallRect.top = rect.top + 20; 
		
		if((dangoPositionX + 80) > (smallRect.right) || (dangoPositionX - 20) < smallRect.left){
			dangoVelocityX = -dangoVelocityX;
		}
		if((dangoPositionY + 50) > (smallRect.bottom) || (dangoPositionY - 30) < smallRect.top){
			dangoVelocityY = -dangoVelocityY;
		}

		ReleaseDC(hwnd,hdc);
	}
	myLastTime = myTime;
}
