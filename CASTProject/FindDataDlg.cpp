// FindDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CASTProject.h"
#include "FindDataDlg.h"
#include "afxdialogex.h"


// FindDataDlg 对话框

IMPLEMENT_DYNAMIC(FindDataDlg, CDialogEx)

FindDataDlg::FindDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FINDSET, pParent)
{

}

FindDataDlg::~FindDataDlg()
{
}

void FindDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FindDataDlg, CDialogEx)
END_MESSAGE_MAP()


// FindDataDlg 消息处理程序
