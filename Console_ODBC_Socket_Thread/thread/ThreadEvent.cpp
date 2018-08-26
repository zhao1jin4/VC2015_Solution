
#include <Windows.h>
#include <iostream>
using namespace std;
namespace thread_event
{
	int tickets=100;
	HANDLE _event;

	DWORD WINAPI threadFunc1(LPVOID lpParam)//������ʽ
	{
		while(TRUE)
		{
			WaitForSingleObject(_event,INFINITE);//����ʹ���¼�����,����Ѿ���ӵ���ߣ������ٴ�ӵ�У�Ҫ��
			//ResetEvent(_event);//�����ֹ���,û�õ�
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
			//ResetEvent(_event);//�����ֹ���,û�õ�
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc2 sale tickets:"<<tickets--<<endl;
				SetEvent(_event);
			}else
			{
				SetEvent(_event);//��Ҫ����break;֮��
				break;
			}
		
		}
		return 0;
	}
	int main(int argc,char* argv[] )
	{

		_event=::CreateEvent(NULL,FALSE,FALSE,L"tickts") ;//manual����ΪFALSE,ֻ��һ���߿��Եõ�
		//��manualΪTRUE,�����̵߳�WaitForSingleObject(_event ,INFINITE)������ͬʱִ�У����ٵ���ResetEvent,û��ʵ��ͬ����û�õ�
		if(_event)
		{
			if(ERROR_ALREADY_EXISTS==GetLastError())//�������ֵ�
			{
				cout<<"only one instance can run!"<<endl;
				getchar();
				return 1;
			}
		}
		::SetEvent(_event);//����Ϊsingled,�������̲߳��õ�
		 
		HANDLE myThread1,myThread2;
		myThread1=CreateThread(NULL,0,threadFunc1,0,0,NULL);
		myThread2=CreateThread(NULL,0,threadFunc2,0,0,NULL);

		CloseHandle(myThread1);//���߳�ִ����ɻ�����Դ
		CloseHandle(myThread2);

		cout<<"main Thread runing"<<endl;
		Sleep(5*1000);//����ʱ��Ƭ
		getchar();
		CloseHandle(_event);//���Թر���
		return 1;
	}

};