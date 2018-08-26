#pragma once

// MyShape command target
enum DrawType{T_POINT,T_LINE,T_ELLIPSE,T_RECTANGLE} ;
class MyShape : public CObject //为对象serializable 要CObject
{
	DECLARE_SERIAL(MyShape)  //为对象serializable 声明
public:
	MyShape();//要有无参数的构造函数
	MyShape(DrawType type,CPoint &start,CPoint &end);
	void Draw(CDC * pDC);
	virtual ~MyShape();
	virtual void Serialize(CArchive& ar);
private :
	DrawType m_drawType;
	CPoint m_start;
	CPoint m_end;

};


