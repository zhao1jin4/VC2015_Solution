#include <Windows.h>



//HWND g_hWnd=NULL;//ȫ�ֱ���,�Ҳ�����cmd�����а�alt+f2,���Ӧ��Ҳ��ر�???,���ڼ��±��оͲ���

#pragma data_seg("MySec");//����һ��Section,ʹ��dumpbin -headers x.dll�鿴,Section  �����ֲ��ܳ���8��
HWND g_hWnd=NULL;//�����ʼ�� ,��Ϊ���ڹ���Section��,���ڼ��±���,��alt+f2,���Ӧ�þͻ�ر�
#pragma data_seg()//��β

//#pragma comment(linker,"/section:MySec,RWS")//����Section,RWS=ReadWriteShareʹ�� dumpbin -headers x.dll�鿴���һ��Share
//Ҳ����д��.def�ļ���,SECTIONS �µ�Read WRITE shared�ɴ�д,Ҳ��Сд

HHOOK g_hMouseHook=NULL;
HHOOK g_hKeyHook=NULL;
HINSTANCE g_hCurrentDLL=NULL;
LRESULT CALLBACK mouseHookFunc(int nCode,WPARAM wParam,LPARAM lParam)
{
	return 1;//���ط�0,��ʾ��Ϣ�Ѿ�����,�������´���
}
LRESULT CALLBACK keyHookFunc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if(VK_F2 == wParam && 1 ==(lParam>>29 & 0x01) )//��29λΪ1,��ʾalt��������
	{
		UnhookWindowsHookEx(g_hMouseHook);
		UnhookWindowsHookEx(g_hKeyHook);
		::SendMessage(g_hWnd,WM_CLOSE,0,0);//�첽PostMessage,��ͬ��ʹ��SendMessage
		return 1;
	}
	return CallNextHookEx(g_hMouseHook,nCode,wParam,lParam);
}
 
/*
//VS 2010�м��������,ʹ�����dll��Ӧ�ò�������????????????
BOOL WINAPI  DllMain(HINSTANCE hInstance,DWORD fdwReason,LPVOID lpvReserved )//����DLLʱ�����,���Եõ�DLL�ľ��
{
	g_hCurrentDLL=hinstDLL;
}
*/

void MyHook(HWND hWnd) //def�ļ���   @33 ��ʾ�Լ���ID
{
	g_hWnd=hWnd;//�������޸�ȫ�ֱ���,���ȸ�������ҳ,�ڸ��������޸�
	g_hCurrentDLL=GetModuleHandle(L"ConsoleHookDLL.dll");//�õ�DLL���,��ʽ��

	g_hMouseHook=SetWindowsHookEx(WH_MOUSE,mouseHookFunc,g_hCurrentDLL,0);//0��ʾ��ǰ����������߳�
	g_hKeyHook=SetWindowsHookEx(WH_KEYBOARD,keyHookFunc,g_hCurrentDLL,0);
}
