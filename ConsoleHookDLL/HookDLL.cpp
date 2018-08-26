#include <Windows.h>



//HWND g_hWnd=NULL;//全局变量,我测试在cmd窗口中按alt+f2,这个应该也会关闭???,如在记事本中就不会

#pragma data_seg("MySec");//建立一个Section,使用dumpbin -headers x.dll查看,Section  的名字不能超过8个
HWND g_hWnd=NULL;//必须初始化 ,因为放在共享Section中,如在记事本中,按alt+f2,这个应该就会关闭
#pragma data_seg()//结尾

//#pragma comment(linker,"/section:MySec,RWS")//共享Section,RWS=ReadWriteShare使用 dumpbin -headers x.dll查看会多一个Share
//也可以写在.def文件中,SECTIONS 下的Read WRITE shared可大写,也可小写

HHOOK g_hMouseHook=NULL;
HHOOK g_hKeyHook=NULL;
HINSTANCE g_hCurrentDLL=NULL;
LRESULT CALLBACK mouseHookFunc(int nCode,WPARAM wParam,LPARAM lParam)
{
	return 1;//返回非0,表示消息已经处理,不会向下传递
}
LRESULT CALLBACK keyHookFunc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if(VK_F2 == wParam && 1 ==(lParam>>29 & 0x01) )//第29位为1,表示alt键被按下
	{
		UnhookWindowsHookEx(g_hMouseHook);
		UnhookWindowsHookEx(g_hKeyHook);
		::SendMessage(g_hWnd,WM_CLOSE,0,0);//异步PostMessage,如同步使用SendMessage
		return 1;
	}
	return CallNextHookEx(g_hMouseHook,nCode,wParam,lParam);
}
 
/*
//VS 2010中加这个函数,使用这个dll的应该不能运行????????????
BOOL WINAPI  DllMain(HINSTANCE hInstance,DWORD fdwReason,LPVOID lpvReserved )//加载DLL时的入口,可以得到DLL的句柄
{
	g_hCurrentDLL=hinstDLL;
}
*/

void MyHook(HWND hWnd) //def文件中   @33 表示自己定ID
{
	g_hWnd=hWnd;//这里有修改全局变量,会先复制数据页,在复本上做修改
	g_hCurrentDLL=GetModuleHandle(L"ConsoleHookDLL.dll");//得到DLL句柄,方式二

	g_hMouseHook=SetWindowsHookEx(WH_MOUSE,mouseHookFunc,g_hCurrentDLL,0);//0表示当前桌面的所有线程
	g_hKeyHook=SetWindowsHookEx(WH_KEYBOARD,keyHookFunc,g_hCurrentDLL,0);
}
