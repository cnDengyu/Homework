#include <windows.h>
/*------------------------

在这个文件中绘图 

------------------------*/

extern long myTime;

int textPositionX = 100;
int textPositionY = 100;
int textVelocityX = 2;
int textVelocityY = 2;

long lastTime = 0;

const int textWidth = 60;
const int textHeight = 17;



//由 WM_PAINT 回调 
void onPaint(HWND hwnd, HDC hdc, PAINTSTRUCT ps)
{
	RECT rect;
	HBRUSH hBrush;
	HPEN hPen;
	GetClientRect(hwnd, &rect);
	//绘制背景 
	hBrush = CreateSolidBrush(0x00DDDDDD);
	FillRect(hdc, &rect, hBrush);
	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(0x00FFFFFF);
	rect.bottom = rect.bottom - 20;
	rect.left = rect.left + 20;
	rect.right = rect.right - 20;
	rect.top = rect.top + 20; 
	FillRect(hdc, &rect, hBrush);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(0x00AAAAFF);
	hPen = CreatePen(PS_SOLID, 3, 0x00333399);
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
	Ellipse(hdc, textPositionX - 20, textPositionY -30, textPositionX + 80, textPositionY + 50);
	DeleteObject(hPen);
	DeleteObject(hBrush); 
	
	hPen = CreatePen(PS_SOLID, 3, 0x00000000);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, textPositionX + 20, textPositionY -20, NULL);
	LineTo(hdc, textPositionX + 20, textPositionY);
	MoveToEx(hdc, textPositionX + 40, textPositionY -20, NULL);
	LineTo(hdc, textPositionX + 40, textPositionY);
	DeleteObject(hPen);
	
	textPositionX = textPositionX + (myTime - lastTime) * textVelocityX;
	textPositionY = textPositionY + (myTime - lastTime) * textVelocityY;
	if((textPositionX + 80) > (rect.right) || (textPositionX - 20) < rect.left){
		textVelocityX = -textVelocityX;
	}
	if((textPositionY + 50) > (rect.bottom) || (textPositionY - 30) < rect.top){
		textVelocityY = -textVelocityY;
	}
	//TextOut(hdc, textPositionX, textPositionY, TEXT("欢迎光临"), strlen("欢迎光临"));
	lastTime = myTime;
}
