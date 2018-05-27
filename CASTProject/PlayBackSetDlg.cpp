// PlayBackSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CASTProject.h"
#include "PlayBackSetDlg.h"
#include "afxdialogex.h"


// PlayBackSetDlg 对话框

IMPLEMENT_DYNAMIC(PlayBackSetDlg, CDialogEx)

PlayBackSetDlg::PlayBackSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PLAYBACKSET, pParent)
{

}

PlayBackSetDlg::~PlayBackSetDlg()
{
}

void PlayBackSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PlayBackSetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PBS, &PlayBackSetDlg::OnBnClickedButtonPBStart)
	ON_BN_CLICKED(IDC_BUTTON_PBE, &PlayBackSetDlg::OnBnClickedButtonPBEnd)
	ON_BN_CLICKED(IDOK, &PlayBackSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// PlayBackSetDlg 消息处理程序


void PlayBackSetDlg::OnBnClickedButtonPBStart()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T(".raw"), _T("*.raw"), OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, _T("raw文件(*.raw)|*.raw|JPEG文件(*.JPEG)|*.JPEG|位图文件(*.bmp)|*.bmp||"));
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDIT_STRPBS, dlg.GetPathName());
}


void PlayBackSetDlg::OnBnClickedButtonPBEnd()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T(".raw"), _T("*.raw"), OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, _T("raw文件(*.raw)|*.raw|JPEG文件(*.JPEG)|*.JPEG|位图文件(*.bmp)|*.bmp||"));
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDIT_STRPBE, dlg.GetPathName());
}


void PlayBackSetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	iSpeed = GetDlgItemInt(IDC_EDIT_PBSPEED);
	iSkipFrm = GetDlgItemInt(IDC_EDIT_PBSKIPFRM);
	bNomalShow = ((CButton *)GetDlgItem(IDC_RADIO_NORMAL))->GetCheck() == 1 ? 1 : 2;
	iCurPath = ((CButton *)GetDlgItem(IDC_RADIO_CUR))->GetCheck();
	GetDlgItemText(IDC_EDIT_STRPBS, strStart);
	GetDlgItemText(IDC_EDIT_STRPBE, strEnd);
	strPath = strEnd.Left(strEnd.ReverseFind('\\'));
	CDialogEx::OnOK();
}


BOOL PlayBackSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemInt(IDC_EDIT_PBSPEED, 50);
	SetDlgItemInt(IDC_EDIT_PBSKIPFRM, 1);
	((CButton *)GetDlgItem(IDC_RADIO_NORMAL))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_CUR))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
