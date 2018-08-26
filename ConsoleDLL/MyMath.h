
//---方式1
_declspec(dllexport) int add(int a,int b);
//只有加_declspec(dllexport) ,的函数外部才可以使用,使用dumpbin -exports ConsoleDLL.dll查看,
//实现中不用加 _declspec(dllexport)

//---方式2  以.h方式向外提供
#ifdef MY_API //对内部实现
#else
#define MY_API _declspec(dllimport)  //对外部
//#define MY_API extern "C" _declspec(dllimport)//导出的函数符号没有符加码(为重载),不能导出类,如加_stdcall还是有名字改编
//可以使用.def文件,加_stdcall,就不会有名字改编
#endif

//MY_API  int  subtract(int a,int b);
MY_API  int _stdcall subtract(int a,int b);//_stdcall只能加在 返回类型和函数名中间

/*
class MY_API Point{ //对类中所有函数都导出,但private的外部还是不能仿问
public :
	void output(int x,int y);
private :
	void inner();
};
*/
 
class  Point{ 
public :
	MY_API	void output(int x,int y);//导出类中指定的函数,但Point类还是要导出的
private :
	void inner();
};

 int _stdcall multi(int a,int b);//对使用def文件的,对使用_stdcall的,函数没有名字改编,可选使用 MY_API
 


