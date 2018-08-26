
#include <iostream>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

//--以下是为CString
#include <Windows.h>
#include <cstringt.h>
#include <atlstr.h>

using namespace std;
namespace other_chinese
{
	void VC()
	{
		CString varStr=L"中华人民共和国";
		wchar_t* wStr=varStr.GetBuffer();//可修改但必须 调用ReleaseBuffer()
		const wchar_t* wContStr=varStr.GetString();//不可修改的
		wprintf(L"CString -> wchar* :%ls \n",wStr);//不要显示在控制台,因为控制是GBK编码,可以Debug看
		wprintf(L"CString 中文 -> wchar* :%ls\n",wStr);//格式中有 中文就不输出了
		
		char* hello="hello world";
		CString eng= CString (hello);//只有英文可以 把char*到CString
		
		
		CString str1=_T("abc中文");//这里不能是变量
		wchar_t * convered=str1.GetBuffer();//char*中文 -> CString->wchar_t * 成功,但不能是变量
		
	}
	void Common()
	{
		//可以把char*当做二进制, 可以适当的强制指针
		
		const char* con_char="char*中文";
		//CString str2=_T(con_char);//_T( )中不可以是变量???

		//----------char*是正常中文 ->转换到wchar_t* ,失败???
		wchar_t wData[50];
		wmemset(wData,0,50);

		mbstate_t state;
		memset(&state,0,sizeof(state));
	
		mbsrtowcs(wData,&con_char,50,&state);//char*是正常中文 ->转换到wchar_t* ,失败???
		mbstowcs(wData,con_char,50);//,失败???

		int len=strlen(con_char);
		wData[len]='\0';

		CString result=CString(wData);

	}

	//---------------------------------------

	int main(int argc,char* argv[] )
	{
		VC();
		 

		getchar();
		return 1;
	}
}
