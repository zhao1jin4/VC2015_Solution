#define MY_API _declspec(dllexport)  //在#inlude之前,内部实现,是dllexport
//#define MY_API extern "C" _declspec(dllexport) 

#include "MyMath.h"

#include <Windows.h>
#include <wchar.h>
int add(int a,int b) //实现中可不加 _declspec(dllexport)
{
	 return a+b;
}

//---方式2,使用.h
/*
MY_API  int  subtract(int a,int b)
{
	 return a-b;
}
*/

MY_API  int _stdcall subtract(int a,int b) 
{
	 return a-b;
}



void Point::output(int x,int y)
{

	HWND parentWnd=GetForegroundWindow();//得到调用者当前使用的窗口
	HDC dc=GetDC(parentWnd);
	wchar_t data[20];
	swprintf(data,L"版权所有");

	TextOut(dc,x,y,data,wcslen(data));
	ReleaseDC(parentWnd,dc);
}
 int _stdcall multi(int a,int b)//对.def的,可选使用 MY_API
 {
	return a*b;
 }