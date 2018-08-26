#include <Windows.h>
#include <iostream>
using namespace std;
namespace thread_mutex
{
	int tickets=100;
	HANDLE mutex;//会记录拥有者的线程ID 和 拥有次数

	DWORD WINAPI threadFunc1(LPVOID lpParam)//函数形式
	{
		while(TRUE)
		{
			WaitForSingleObject(mutex,INFINITE);//一直等待到可用,对Mutex,已经是拥有者线程,可以多次调用,计数器加1,
			//如果没有ReleaseMutex线程退出,操作系统会自动为Mutex计数器清0,拥有者的线程ID清0
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc1 sale tickets:"<<tickets--<<endl;
			}else
			{
				break;
			}
			ReleaseMutex(mutex);//只对拥有者的线程调用才有效,其它线程调用无效,计数器减1,直到为0,其它线程可用
		}
		
		return 0;
	}
	DWORD WINAPI threadFunc2(LPVOID lpParam) 
	{
		while(TRUE)
		{
			WaitForSingleObject(mutex,INFINITE);
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc2 sale tickets:"<<tickets--<<endl;
			}else
			{
				break;
			}
			ReleaseMutex(mutex);
		}
		return 0;
	}
	int main(int argc,char* argv[] )
	{

		mutex=CreateMutex(NULL,FALSE,L"myTicks");//互斥对象,FALSE其它线程可用,如为TRUE,计数器加1
		if(mutex)
		{
			if(ERROR_ALREADY_EXISTS==GetLastError())// 对有名字的,对一个软件只一个进程运行
			{
				cout<<"only one instance can run!"<<endl;
				getchar();
				return 1;
			}
		}
		HANDLE myThread1,myThread2;
		myThread1=CreateThread(NULL,0,threadFunc1,0,0,NULL);
		myThread2=CreateThread(NULL,0,threadFunc2,0,0,NULL);

		CloseHandle(myThread1);//当线程执行完成会清资源
		CloseHandle(myThread2);
		cout<<"main Thread runing"<<endl;
		Sleep(5*1000);//放弃时间片
		getchar();
		return 1;
	}

};