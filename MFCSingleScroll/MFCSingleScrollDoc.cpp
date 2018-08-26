
// MFCSingleScrollDoc.cpp : implementation of the CMFCSingleScrollDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCSingleScroll.h"
#endif

#include "MFCSingleScrollDoc.h"
#include "MFCSingleScrollView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCSingleScrollDoc

IMPLEMENT_DYNCREATE(CMFCSingleScrollDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCSingleScrollDoc, CDocument)
END_MESSAGE_MAP()


// CMFCSingleScrollDoc construction/destruction

CMFCSingleScrollDoc::CMFCSingleScrollDoc()
{
	// TODO: add one-time construction code here

}

CMFCSingleScrollDoc::~CMFCSingleScrollDoc()
{
}

BOOL CMFCSingleScrollDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	//----我的代码
	//在程序启动时调用
	//SetTitle(L"我的文档ABC");//可以修改文档的标题,
	//也可在Resource View中的String Table有一个IDR_MAINFRAME,以\n分隔,第二个是空可以修改它,优先级低
	//也可以修改String Table 中的IDR_MAINFRAME的值


	return TRUE;
}




// CMFCSingleScrollDoc serialization


void CMFCSingleScrollDoc::Serialize(CArchive& ar) 
{
	//----------------我的代码 ,文件->打开 或者 保存 调用这里
	/*
	if (ar.IsStoring())
	{
		int id=2008;
		CString name=L"李";
		ar<<id<<name;
	}
	else
	{
		//如果已经保存,再打开同一个文件就不会调用Serialize函数,因已经在内存中
		int id;
		CString name;
		ar>>id>>name;
		CString result;
		result.Format(L"id=%d,name=%s",id,name);
		AfxMessageBox(result);
	}*/


	//Doc中得到View
	POSITION pos=GetFirstViewPosition();
	CMFCSingleScrollView * view=(CMFCSingleScrollView*)GetNextView(pos);
	/*
	if (ar.IsStoring())//---图形类
	{
		int len=view->m_allLine.GetSize();
		ar<<len;//自定的,先写记录数
		int i;
		for (i=0;i<len;i++)
		{
			MyShape* shape=(MyShape*)view->m_allLine.GetAt(i);
			ar<<shape;//对象指针,CObject*
		}
	}else
	{
		int len;
		ar>>len;;//先读记录数
		int i;
		MyShape* shape;
		for (i=0;i<len;i++)
		{
			ar>>shape;
			view->m_allLine.Add(shape);
		}
	}
	*/

	//也可以把集合入在Doc类中,View类有GetDocment();
	m_allObj.Serialize(ar);//集合类,CPtrArray不行的,要使用使用 CObArray
 
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCSingleScrollDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCSingleScrollDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCSingleScrollDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCSingleScrollDoc diagnostics

#ifdef _DEBUG
void CMFCSingleScrollDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCSingleScrollDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCSingleScrollDoc commands

//----自己的代码,用于清资源,会在打开或者新建文档时调用 
void CMFCSingleScrollDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	
	//------View中的 集合
	/*
	//Doc中得到View
	POSITION pos=GetFirstViewPosition();
	CMFCSingleScrollView * view=(CMFCSingleScrollView*)GetNextView(pos);
	
	int len=view->m_allLine.GetSize();
	int i;
	for(i=0;i<len;i++)
	{
		delete view->m_allLine.GetAt(i);
	}
	view->m_allLine.RemoveAll();
	*/
	//------Doc中的 集合
	//int len=m_allObj.GetSize();
	int i;
	for(i=0;i<m_allObj.GetSize();)
	{
		delete m_allObj.GetAt(i);//会改变 Size 大小,for中要使用i<m_allObj.GetSize(),去i++
		m_allObj.RemoveAt(i);
	}
	//m_allObj.RemoveAll();

	CDocument::DeleteContents();
}
