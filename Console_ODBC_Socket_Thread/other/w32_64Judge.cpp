#include <Windows.h>
#include <iostream>
using namespace std;
namespace other_judge
{
	int main(int argc,char* argv[] )
	{
		SYSTEM_INFO info;
		GetSystemInfo(&info);//GetNativeSystemInfo
		int arc=info.wProcessorArchitecture;//CPU
		if(PROCESSOR_ARCHITECTURE_INTEL==arc)//x86
		{
			cout<<"GetSystemInfo 32bit CPU"<<endl;
		}else if(PROCESSOR_ARCHITECTURE_AMD64==arc)//x64(AMD or intel)
		{
			cout<<"GetSystemInfo 64bit CPU"<<endl;
		}
		cout<<"number of processor:"<<info.dwNumberOfProcessors<<endl;
		//----------
		BOOL is64bit=FALSE;
		IsWow64Process(GetCurrentProcess(),&is64bit);//CPU
		if(is64bit)
			cout<<"IsWow64Process 64bit CPU"<<endl;
		else
			cout<<"IsWow64Process 32bit CPU"<<endl;

		//----------
		int len=0;
		len=sizeof(char*);//VC2012 32λʱ��4,64λʱ��8,ֻ��֪����ǰ�ĳ����Ƕ���λ�����
		len=sizeof(int *);//VC2012 32λʱ��4,64λʱ��8,ֻ��֪����ǰ�ĳ����Ƕ���λ�����
		char * app=(len==4)?"32bit":"64bit";
		cout<<"current application compiled is "<<app<<endl;

		//----------
		OSVERSIONINFO ver;//OSVERSIONINFO �� OSVERSIONINFOEX
		ver.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
		GetVersionEx(&ver);
		DWORD major=ver.dwMajorVersion;//5��xp,2000,2003 server,6��vista, 2008 server
		DWORD min=ver.dwMinorVersion;//  XP��5.1,vista��6.0 , win7��6.1,win8��6.2
		TCHAR* sp=ver.szCSDVersion;//Server Pack n

		//���֪��windows��λ��????
		getchar();
		return 1;
	}
};