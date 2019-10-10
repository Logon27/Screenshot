#include <iostream>
#include <windows.h>

// compile with g++ main.cpp -o test -mwindows
// or simply add -mwindows to your linker inside your ide

using namespace std;

void screenshot(POINT a, POINT b)
{
	//Copy screen to a bitmap
	HDC     hScreen = GetDC(NULL);
	HDC     hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, abs(b.x - a.x), abs(b.y - a.y));
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL    bRet = BitBlt(hDC, 0, 0, abs(b.x - a.x), abs(b.y - a.y), hScreen, a.x, a.y, SRCCOPY);

	//Save the bitmap to the clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard();

	//Clean up objects
	SelectObject(hDC, old_obj);
	DeleteDC(hDC);
	ReleaseDC(NULL, hScreen);
	DeleteObject(hBitmap);
}

int main()
{
	POINT a, b;
	a.x = 0;
	a.y = 0;

	int horizontal = 0;
	int vertical = 0;

	RECT desktop;
	//Grab a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	//pass size of the screen to variable desktop
	GetWindowRect(hDesktop, &desktop);
	//The top left corner will have coordinates (0,0)
	//the bottom right corner will have coordinates (horizontal, vertical)
	b.x = desktop.right;
	b.y = desktop.bottom;

	//take a screenshot of the entire desktop. should target the main monitor
	screenshot(a, b);
}