#include <Windows.h>
#include <iostream>
using namespace std;
namespace thread_mutex
{
	int tickets=100;
	HANDLE mutex;//���¼ӵ���ߵ��߳�ID �� ӵ�д���

	DWORD WINAPI threadFunc1(LPVOID lpParam)//������ʽ
	{
		while(TRUE)
		{
			WaitForSingleObject(mutex,INFINITE);//һֱ�ȴ�������,��Mutex,�Ѿ���ӵ�����߳�,���Զ�ε���,��������1,
			//���û��ReleaseMutex�߳��˳�,����ϵͳ���Զ�ΪMutex��������0,ӵ���ߵ��߳�ID��0
			if(tickets>0)
			{
				Sleep(5);
				cout<<"threadFunc1 sale tickets:"<<tickets--<<endl;
			}else
			{
				break;
			}
			ReleaseMutex(mutex);//ֻ��ӵ���ߵ��̵߳��ò���Ч,�����̵߳�����Ч,��������1,ֱ��Ϊ0,�����߳̿���
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

		mutex=CreateMutex(NULL,FALSE,L"myTicks");//�������,FALSE�����߳̿���,��ΪTRUE,��������1
		if(mutex)
		{
			if(ERROR_ALREADY_EXISTS==GetLastError())// �������ֵ�,��һ�����ֻһ����������
			{
				cout<<"only one instance can run!"<<endl;
				getchar();
				return 1;
			}
		}
		HANDLE myThread1,myThread2;
		myThread1=CreateThread(NULL,0,threadFunc1,0,0,NULL);
		myThread2=CreateThread(NULL,0,threadFunc2,0,0,NULL);

		CloseHandle(myThread1);//���߳�ִ����ɻ�����Դ
		CloseHandle(myThread2);
		cout<<"main Thread runing"<<endl;
		Sleep(5*1000);//����ʱ��Ƭ
		getchar();
		return 1;
	}

};