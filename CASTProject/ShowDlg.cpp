// ShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CASTProject.h"
#include "ShowDlg.h"
#include "afxdialogex.h"


// ShowDlg 对话框

IMPLEMENT_DYNAMIC(ShowDlg, CDialogEx)

ShowDlg::ShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ShowDlg::~ShowDlg()
{
}

void ShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
}


BEGIN_MESSAGE_MAP(ShowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SLR, &ShowDlg::OnBnClickedButtonSlr)
	ON_BN_CLICKED(IDC_BUTTON_SLL, &ShowDlg::OnBnClickedButtonSll)
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// ShowDlg 消息处理程序


BOOL ShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Slider.SetRange(0, 7);
 	m_Slider.SetTicFreq(1);
	SetDlgItemInt(IDC_EDIT_HB, 15);
	SetDlgItemInt(IDC_EDIT_LB, 7);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ShowDlg::OnBnClickedButtonSlr()
{
	// TODO: 在此添加控件通知处理程序代码
	m_SldPos = m_Slider.GetPos() + 1;
	m_SldPos = m_SldPos > 7 ? 7 : m_SldPos;
	m_Slider.SetPos(m_SldPos);
	SetDlgItemInt(IDC_EDIT_HB, 15- m_SldPos);
	SetDlgItemInt(IDC_EDIT_LB, 7- m_SldPos);
}


void ShowDlg::OnBnClickedButtonSll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_SldPos = m_Slider.GetPos() - 1;
	m_SldPos = m_SldPos < 0 ? 0 : m_SldPos;
	m_Slider.SetPos(m_SldPos);
	SetDlgItemInt(IDC_EDIT_HB, 15 - m_SldPos);
	SetDlgItemInt(IDC_EDIT_LB, 7 - m_SldPos);
}


void ShowDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_SldPos = m_Slider.GetPos();
	SetDlgItemInt(IDC_EDIT_HB, 15 - m_SldPos);
	SetDlgItemInt(IDC_EDIT_LB, 7 - m_SldPos);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
