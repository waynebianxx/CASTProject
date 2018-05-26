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
END_MESSAGE_MAP()


// PlayBackSetDlg 消息处理程序
