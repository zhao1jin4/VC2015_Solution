
//---��ʽ1
_declspec(dllexport) int add(int a,int b);
//ֻ�м�_declspec(dllexport) ,�ĺ����ⲿ�ſ���ʹ��,ʹ��dumpbin -exports ConsoleDLL.dll�鿴,
//ʵ���в��ü� _declspec(dllexport)

//---��ʽ2  ��.h��ʽ�����ṩ
#ifdef MY_API //���ڲ�ʵ��
#else
#define MY_API _declspec(dllimport)  //���ⲿ
//#define MY_API extern "C" _declspec(dllimport)//�����ĺ�������û�з�����(Ϊ����),���ܵ�����,���_stdcall���������ָı�
//����ʹ��.def�ļ�,��_stdcall,�Ͳ��������ָı�
#endif

//MY_API  int  subtract(int a,int b);
MY_API  int _stdcall subtract(int a,int b);//_stdcallֻ�ܼ��� �������ͺͺ������м�

/*
class MY_API Point{ //���������к���������,��private���ⲿ���ǲ��ܷ���
public :
	void output(int x,int y);
private :
	void inner();
};
*/
 
class  Point{ 
public :
	MY_API	void output(int x,int y);//��������ָ���ĺ���,��Point�໹��Ҫ������
private :
	void inner();
};

 int _stdcall multi(int a,int b);//��ʹ��def�ļ���,��ʹ��_stdcall��,����û�����ָı�,��ѡʹ�� MY_API
 


