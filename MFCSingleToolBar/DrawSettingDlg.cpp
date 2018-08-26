// DrawSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleToolBar.h"
#include "DrawSettingDlg.h"
#include "afxdialogex.h"


// DrawSettingDlg dialog

IMPLEMENT_DYNAMIC(DrawSettingDlg, CDialogEx)

DrawSettingDlg::DrawSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DrawSettingDlg::IDD, pParent)
	, m_nLineWidth(1)
	, m_lineStyle(0)
{
	m_brush.CreateSolidBrush(RGB(0,0,125));
	m_font.CreatePointFont(120,L"黑体");
}

DrawSettingDlg::~DrawSettingDlg()
{
}

void DrawSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LINE_WIDTH, m_nLineWidth);
	DDV_MinMaxUInt(pDX, m_nLineWidth, 1, 20);
	DDX_Radio(pDX, IDC_LINE_SOLID, m_lineStyle);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(DrawSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MY_FONT, &DrawSettingDlg::OnBnClickedMyFont)
	ON_EN_CHANGE(IDC_EDIT_LINE_WIDTH, &DrawSettingDlg::OnEnChangeEditLineWidth)
	ON_BN_CLICKED(IDC_LINE_SOLID, &DrawSettingDlg::OnBnClickedLineSolid)
	ON_BN_CLICKED(IDC_LINE_DASH, &DrawSettingDlg::OnBnClickedLineDash)
	ON_BN_CLICKED(IDC_LINE_DOT, &DrawSettingDlg::OnBnClickedLineDot)
	ON_WM_CTLCOLOR()//WM_CTLCOLOR 消息
END_MESSAGE_MAP()


// DrawSettingDlg message handlers


//---我的代码,在对话框中再弹出 字体对话框
void DrawSettingDlg::OnBnClickedMyFont()
{
	
	
	 CFontDialog dlg;
 
	 CMFCSingleToolBarView * vew =((CMainFrame*)AfxGetMainWnd())->GetRightPane();
	// CFont t_font=vew->m_font;//编译时报不能仿问 private
	 
	 if(IDOK== dlg.DoModal())
	{ 
		if(!vew->m_font.m_hObject)
		{
			//vew->m_font.DeleteObject();
			vew->m_font.CreateFontIndirectW(dlg.m_cf.lpLogFont);
		}
		
	  //CString m_fontName=dlg.m_cf.lpLogFont->lfFaceName;//字体名;
	}
 
}

void DrawSettingDlg::drawSample() 
{
	UpdateData();//取最新的数据
	
	//Invalidate();//当线从宽到窄,重画没有??????????
	CClientDC dc(this);
	
	CPen pen(m_lineStyle,m_nLineWidth,RGB(255,0,0));
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);//得到屏幕坐标
	ScreenToClient(rect);//把屏幕坐标转换为窗口的坐标
	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);

}
void DrawSettingDlg::OnEnChangeEditLineWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	drawSample();
 
}


void DrawSettingDlg::OnBnClickedLineSolid()
{
	drawSample();
}


void DrawSettingDlg::OnBnClickedLineDash()
{
	drawSample();
}


void DrawSettingDlg::OnBnClickedLineDot()
{
	drawSample();
}


HBRUSH DrawSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)//所有子控件都会调用 一次这个函数
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	if(pWnd->GetDlgCtrlID() == IDC_SAMPLE)
	{
		pDC->SetTextColor(RGB(0,255,0));
		pDC->SetBkMode(TRANSPARENT);//文字的北景色由白色变为透明
		return m_brush;//CBrush 有 operator HBRUSH,转换
	}
	if(pWnd->GetDlgCtrlID() == IDC_EDIT_LINE_WIDTH)
	{
		pDC->SetTextColor(RGB(0,255,0));
		pDC->SetBkMode(TRANSPARENT); 
		return m_brush; 
	}
	if(pWnd->GetDlgCtrlID() == IDC_TEXT)
	{
		pDC->SelectObject(&m_font);
		return m_brush; 
	}

	if(pWnd->GetDlgCtrlID() == IDOK)//对按钮无效
	{
		pDC->SetTextColor(RGB(0,255,0));
	 	return m_brush; 
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
	
	
}
