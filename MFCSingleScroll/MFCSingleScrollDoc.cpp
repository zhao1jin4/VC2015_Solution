
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
	//----�ҵĴ���
	//�ڳ�������ʱ����
	//SetTitle(L"�ҵ��ĵ�ABC");//�����޸��ĵ��ı���,
	//Ҳ����Resource View�е�String Table��һ��IDR_MAINFRAME,��\n�ָ�,�ڶ����ǿտ����޸���,���ȼ���
	//Ҳ�����޸�String Table �е�IDR_MAINFRAME��ֵ


	return TRUE;
}




// CMFCSingleScrollDoc serialization


void CMFCSingleScrollDoc::Serialize(CArchive& ar) 
{
	//----------------�ҵĴ��� ,�ļ�->�� ���� ���� ��������
	/*
	if (ar.IsStoring())
	{
		int id=2008;
		CString name=L"��";
		ar<<id<<name;
	}
	else
	{
		//����Ѿ�����,�ٴ�ͬһ���ļ��Ͳ������Serialize����,���Ѿ����ڴ���
		int id;
		CString name;
		ar>>id>>name;
		CString result;
		result.Format(L"id=%d,name=%s",id,name);
		AfxMessageBox(result);
	}*/


	//Doc�еõ�View
	POSITION pos=GetFirstViewPosition();
	CMFCSingleScrollView * view=(CMFCSingleScrollView*)GetNextView(pos);
	/*
	if (ar.IsStoring())//---ͼ����
	{
		int len=view->m_allLine.GetSize();
		ar<<len;//�Զ���,��д��¼��
		int i;
		for (i=0;i<len;i++)
		{
			MyShape* shape=(MyShape*)view->m_allLine.GetAt(i);
			ar<<shape;//����ָ��,CObject*
		}
	}else
	{
		int len;
		ar>>len;;//�ȶ���¼��
		int i;
		MyShape* shape;
		for (i=0;i<len;i++)
		{
			ar>>shape;
			view->m_allLine.Add(shape);
		}
	}
	*/

	//Ҳ���԰Ѽ�������Doc����,View����GetDocment();
	m_allObj.Serialize(ar);//������,CPtrArray���е�,Ҫʹ��ʹ�� CObArray
 
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

//----�Լ��Ĵ���,��������Դ,���ڴ򿪻����½��ĵ�ʱ���� 
void CMFCSingleScrollDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	
	//------View�е� ����
	/*
	//Doc�еõ�View
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
	//------Doc�е� ����
	//int len=m_allObj.GetSize();
	int i;
	for(i=0;i<m_allObj.GetSize();)
	{
		delete m_allObj.GetAt(i);//��ı� Size ��С,for��Ҫʹ��i<m_allObj.GetSize(),ȥi++
		m_allObj.RemoveAt(i);
	}
	//m_allObj.RemoveAll();

	CDocument::DeleteContents();
}
