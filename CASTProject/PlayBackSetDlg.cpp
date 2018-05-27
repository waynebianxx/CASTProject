// PlayBackSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CASTProject.h"
#include "PlayBackSetDlg.h"
#include "afxdialogex.h"


// PlayBackSetDlg �Ի���

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


// PlayBackSetDlg ��Ϣ�������


void PlayBackSetDlg::OnBnClickedButtonPBStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T(".raw"), _T("*.raw"), OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, _T("raw�ļ�(*.raw)|*.raw|JPEG�ļ�(*.JPEG)|*.JPEG|λͼ�ļ�(*.bmp)|*.bmp||"));
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDIT_STRPBS, dlg.GetPathName());
}


void PlayBackSetDlg::OnBnClickedButtonPBEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T(".raw"), _T("*.raw"), OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, _T("raw�ļ�(*.raw)|*.raw|JPEG�ļ�(*.JPEG)|*.JPEG|λͼ�ļ�(*.bmp)|*.bmp||"));
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDIT_STRPBE, dlg.GetPathName());
}


void PlayBackSetDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemInt(IDC_EDIT_PBSPEED, 50);
	SetDlgItemInt(IDC_EDIT_PBSKIPFRM, 1);
	((CButton *)GetDlgItem(IDC_RADIO_NORMAL))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_CUR))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
