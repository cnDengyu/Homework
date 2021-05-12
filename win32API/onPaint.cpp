#include <windows.h>
/*------------------------

在这个文件中绘图 

------------------------*/

extern int dangoPositionX;
extern int dangoPositionY;

const int textWidth = 60;
const int textHeight = 17;



//由 WM_PAINT 回调 
void onPaint(HWND hwnd, HDC hdc)
{
	HDC hDCMem;
	HBITMAP hBmpMem,hPreBmp;
	RECT rect,smallRect;
	HBRUSH hBrush;
	HPEN hPen;
	
	/* 创建双缓冲区 */ 
	// 创建与当前DC兼容的内存DC
	hDCMem = CreateCompatibleDC(hdc);
	// 创建一块指定大小的位图
	GetClientRect(hwnd, &rect);
	hBmpMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom); 
	// 将该位图选入到内存DC中，默认是全黑色的
	hPreBmp = (HBITMAP)SelectObject(hDCMem, hBmpMem);
	
	//绘制背景 
	hBrush = CreateSolidBrush(0x00DDDDDD);
	FillRect(hDCMem, &rect, hBrush);
	DeleteObject(hBrush);
	hBrush = CreateSolidBrush(0x00FFFFFF);
	smallRect.bottom = rect.bottom - 20;
	smallRect.left = rect.left + 20;
	smallRect.right = rect.right - 20;
	smallRect.top = rect.top + 20; 
	FillRect(hDCMem, &smallRect, hBrush);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(0x00AAAAFF);
	hPen = CreatePen(PS_SOLID, 3, 0x00333399);
	SelectObject(hDCMem, hPen);
	SelectObject(hDCMem, hBrush);
	Ellipse(hDCMem, dangoPositionX - 20, dangoPositionY -30, dangoPositionX + 80, dangoPositionY + 50);
	DeleteObject(hPen);
	DeleteObject(hBrush); 
	
	hPen = CreatePen(PS_SOLID, 3, 0x00000000);
	SelectObject(hDCMem, hPen);
	MoveToEx(hDCMem, dangoPositionX + 20, dangoPositionY -20, NULL);
	LineTo(hDCMem, dangoPositionX + 20, dangoPositionY);
	MoveToEx(hDCMem, dangoPositionX + 40, dangoPositionY -20, NULL);
	LineTo(hDCMem, dangoPositionX + 40, dangoPositionY);
	DeleteObject(hPen);
		
	/* 将双缓冲区图像复制到显示缓冲区 */
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, hDCMem, 0, 0, SRCCOPY);
	/* 释放资源 */
	SelectObject(hDCMem, hPreBmp);
	DeleteObject(hBmpMem);
	DeleteDC(hDCMem);
}
