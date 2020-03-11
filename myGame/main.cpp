#include <windows.h>
#include "myStrings.h"

#define IDT_TIMER 1

extern onPaint(HWND hwnd, HDC hdc,PAINTSTRUCT ps);
extern onTimer(HWND hwnd);

//所有全局变量用 my 开头 
long myTime = 0;

const int WindowWidth = 640;
const int WindowHeight = 480;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hdc,hDCMem;
	HBITMAP hBmpMem, hPreBmp;
	PAINTSTRUCT ps;
	RECT rect;
	HBRUSH hBrush;
	
	switch(Message) {
		case WM_CREATE: {
			SetTimer(hwnd, IDT_TIMER, 30, (TIMERPROC) NULL); //主窗口的句柄//计时器标识符// 1s 间隔//无定时器回调
			break;
		}
		
		case WM_TIMER: {
			switch(wParam){
				case IDT_TIMER: {
					onTimer(hwnd);
					break;
				}
			}
			break;
		}
		
		case WM_PAINT: {
			hdc = BeginPaint(hwnd, &ps);
			/* 创建双缓冲区 */ 
			// 创建与当前DC兼容的内存DC
			hDCMem = CreateCompatibleDC(hdc);   
			// 创建一块指定大小的位图
			GetClientRect(hwnd, &rect);
			hBmpMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom); 
			// 将该位图选入到内存DC中，默认是全黑色的
			hPreBmp = (HBITMAP)SelectObject(hDCMem, hBmpMem);
			
			/* 在双缓冲中绘图 */
			onPaint(hwnd, hDCMem, ps);
			
			/* 将双缓冲区图像复制到显示缓冲区 */
			BitBlt(hdc, 0, 0, rect.right, rect.bottom, hDCMem, 0, 0, SRCCOPY);
			/* 释放资源 */
			SelectObject(hDCMem, hPreBmp);
			DeleteObject(hBmpMem);
			DeleteDC(hDCMem);

			EndPaint(hwnd, &ps);
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass",str_mainTitle,WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		WindowWidth, /* width */
		WindowHeight, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
