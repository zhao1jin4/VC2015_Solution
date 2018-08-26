#pragma once


// MyButton

class MyButton : public CButton
{
	DECLARE_DYNAMIC(MyButton)

public:
	MyButton * m_pAnother;
	MyButton();
	virtual ~MyButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


