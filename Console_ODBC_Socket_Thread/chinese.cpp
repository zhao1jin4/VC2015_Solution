
#include <iostream>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

//--������ΪCString
#include <Windows.h>
#include <cstringt.h>
#include <atlstr.h>

using namespace std;
namespace other_chinese
{
	void VC()
	{
		CString varStr=L"�л����񹲺͹�";
		wchar_t* wStr=varStr.GetBuffer();//���޸ĵ����� ����ReleaseBuffer()
		const wchar_t* wContStr=varStr.GetString();//�����޸ĵ�
		wprintf(L"CString -> wchar* :%ls \n",wStr);//��Ҫ��ʾ�ڿ���̨,��Ϊ������GBK����,����Debug��
		wprintf(L"CString ���� -> wchar* :%ls\n",wStr);//��ʽ���� ���ľͲ������
		
		char* hello="hello world";
		CString eng= CString (hello);//ֻ��Ӣ�Ŀ��� ��char*��CString
		
		
		CString str1=_T("abc����");//���ﲻ���Ǳ���
		wchar_t * convered=str1.GetBuffer();//char*���� -> CString->wchar_t * �ɹ�,�������Ǳ���
		
	}
	void Common()
	{
		//���԰�char*����������, �����ʵ���ǿ��ָ��
		
		const char* con_char="char*����";
		//CString str2=_T(con_char);//_T( )�в������Ǳ���???

		//----------char*���������� ->ת����wchar_t* ,ʧ��???
		wchar_t wData[50];
		wmemset(wData,0,50);

		mbstate_t state;
		memset(&state,0,sizeof(state));
	
		mbsrtowcs(wData,&con_char,50,&state);//char*���������� ->ת����wchar_t* ,ʧ��???
		mbstowcs(wData,con_char,50);//,ʧ��???

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
