#define MY_API _declspec(dllexport)  //��#inlude֮ǰ,�ڲ�ʵ��,��dllexport
//#define MY_API extern "C" _declspec(dllexport) 

#include "MyMath.h"

#include <Windows.h>
#include <wchar.h>
int add(int a,int b) //ʵ���пɲ��� _declspec(dllexport)
{
	 return a+b;
}

//---��ʽ2,ʹ��.h
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

	HWND parentWnd=GetForegroundWindow();//�õ������ߵ�ǰʹ�õĴ���
	HDC dc=GetDC(parentWnd);
	wchar_t data[20];
	swprintf(data,L"��Ȩ����");

	TextOut(dc,x,y,data,wcslen(data));
	ReleaseDC(parentWnd,dc);
}
 int _stdcall multi(int a,int b)//��.def��,��ѡʹ�� MY_API
 {
	return a*b;
 }