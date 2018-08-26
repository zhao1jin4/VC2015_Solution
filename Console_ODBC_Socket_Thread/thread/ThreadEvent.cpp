
#include <Windows.h>
#include <iostream>
using namespace std;
namespace thread_event
{
	int tickets=100;
	HANDLE _event;

	DWORD WINAPI threadFunc1(LPVOID lpParam)//函数形式
	{
		while(TRUE)
		{
			WaitForSingleObject(_event,INFINITE);//可以使用事件对象,如果已经是拥有者，不可再次拥有，要等
			//ResetEvent(_event);//对于手工的,没用的
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc1 sale tickets:"<<tickets--<<endl;
			}else
			{
				break;
			}
			SetEvent(_event);
		}
		
		return 0;
	}
	DWORD WINAPI threadFunc2(LPVOID lpParam) 
	{
		while(TRUE)
		{
			WaitForSingleObject(_event,INFINITE);
			//ResetEvent(_event);//对于手工的,没用的
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc2 sale tickets:"<<tickets--<<endl;
				SetEvent(_event);
			}else
			{
				SetEvent(_event);//不要放在break;之后
				break;
			}
		
		}
		return 0;
	}
	int main(int argc,char* argv[] )
	{

		_event=::CreateEvent(NULL,FALSE,FALSE,L"tickts") ;//manual多数为FALSE,只可一个线可以得到
		//如manual为TRUE,其它线程的WaitForSingleObject(_event ,INFINITE)都可以同时执行，如再调用ResetEvent,没有实现同步，没用的
		if(_event)
		{
			if(ERROR_ALREADY_EXISTS==GetLastError())//对有名字的
			{
				cout<<"only one instance can run!"<<endl;
				getchar();
				return 1;
			}
		}
		::SetEvent(_event);//设置为singled,即其它线程不用等
		 
		HANDLE myThread1,myThread2;
		myThread1=CreateThread(NULL,0,threadFunc1,0,0,NULL);
		myThread2=CreateThread(NULL,0,threadFunc2,0,0,NULL);

		CloseHandle(myThread1);//当线程执行完成会清资源
		CloseHandle(myThread2);

		cout<<"main Thread runing"<<endl;
		Sleep(5*1000);//放弃时间片
		getchar();
		CloseHandle(_event);//可以关闭它
		return 1;
	}

};