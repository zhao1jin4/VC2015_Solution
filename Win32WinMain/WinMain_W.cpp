
//�һ���Ŀ->properties->Configuration Properties->General->Character Set�е�ѡ��Ϊ  Unicode
//����Win32 Project->Windows application ,Empty 
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
//--������ΪCString
#include <Windows.h>
#include <cstringt.h>
#include <atlstr.h>


LRESULT CALLBACK WinSunProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);

int WINAPI WinMain(
  HINSTANCE hInstance,      // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,          // command line
  int nCmdShow              // show state
)
{
	WNDCLASS wndcls;
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	wndcls.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor=LoadCursor(NULL,IDC_CROSS);
	wndcls.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndcls.hInstance=hInstance;
	wndcls.lpfnWndProc=WinSunProc;
	wndcls.lpszClassName=_T("Weixin2003");
	wndcls.lpszMenuName=NULL;
	wndcls.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	HWND hwnd;
	hwnd=CreateWindow(L"Weixin2003",L"����ά�¿�ѧ������ѵ����",WS_OVERLAPPEDWINDOW,
		0,0,600,400,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	MSG msg;
	while(GetMessage(&msg,NULL,0,0))//���ﲢ���Ǻܺ�,�����һ���߳�,�е�ȡ��Ϣ��û��ʱӦ������
	{//����WM_QUITʱ����0
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WinSunProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
	printf("");
	switch(uMsg)
	{
	case WM_CHAR:
		wchar_t szChar[20];
		swprintf(szChar,L"char is %d",wParam);
		MessageBox(hwnd,szChar,L"weixin",0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd,L"mouse clicked",L"weixin",0);
		HDC hdc;
		hdc=GetDC(hwnd);
		TextOut(hdc,0,50,L"��������������ѵ",strlen("��������������ѵ"));
		ReleaseDC(hwnd,hdc);
		break;
	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC=BeginPaint(hwnd,&ps);//BeginPaintֻ����WM_PAINT��Ϣ��ʹ��
		TextOut(hDC,0,0,L"ά����ѵ",strlen("ά����ѵ"));
		EndPaint(hwnd,&ps);
		break;
	case WM_CLOSE:
		if(IDYES==MessageBox(hwnd,L"�Ƿ���Ľ�����",L"weixin",MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY: 
		//������������ MessageBox�Ƿ���Ľ���,������ʱ,��DestroyWindow�������ú󴰿��Ѿ���ʧ��
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);//���ﲻ��ʡ��,���Լ����о���Ȥ��Ϣ,Ҫ��Ĭ�ϴ���
	}
	return 0;
}