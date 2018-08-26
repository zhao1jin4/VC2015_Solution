#include <Windows.h>
#include <iostream>
using namespace std;
namespace thread_critical
{
	int tickets=100;
	CRITICAL_SECTION section;

	DWORD WINAPI threadFunc1(LPVOID lpParam)//函数形式
	{
		while(TRUE)
		{
			EnterCriticalSection(&section);
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc1 sale tickets:"<<tickets--<<endl;
				LeaveCriticalSection(&section);
			}else
			{
				LeaveCriticalSection(&section);//不要在break;之后
				break;
			}
		
		}
		
		return 0;
	}
	DWORD WINAPI threadFunc2(LPVOID lpParam) 
	{
		while(TRUE)
		{
			EnterCriticalSection(&section);
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc2 sale tickets:"<<tickets--<<endl;
				LeaveCriticalSection(&section);
			}else
			{
				LeaveCriticalSection(&section);
				break;
			}
		 
		}
		return 0;
	}
	int main(int argc,char* argv[] )
	{

		InitializeCriticalSection(&section);
		 
		HANDLE myThread1,myThread2;
		myThread1=CreateThread(NULL,0,threadFunc1,0,0,NULL);
		myThread2=CreateThread(NULL,0,threadFunc2,0,0,NULL);

		CloseHandle(myThread1);//当线程执行完成会清资源
		CloseHandle(myThread2);

		cout<<"main Thread runing"<<endl;
		Sleep(5*1000);//放弃时间片
		getchar();
		
		DeleteCriticalSection(&section);
		return 1;
	}

};