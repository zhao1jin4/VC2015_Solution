#pragma once


// MyStyleButton

class MyStyleButton : public CButton{
	DECLARE_DYNAMIC(MyStyleButton)

public:
	MyStyleButton();
	virtual ~MyStyleButton();

protected:
	DECLARE_MESSAGE_MAP()


public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


