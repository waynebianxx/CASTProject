// AuxlDataShowDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CASTProject.h"
#include "AuxlDataShowDlg.h"
#include "afxdialogex.h"

#include "include/CAST_SrcData.h"
#include "include/PyInterface.h"
// AuxlDataShowDlg 对话框

IMPLEMENT_DYNAMIC(AuxlDataShowDlg, CDialogEx)

AuxlDataShowDlg::AuxlDataShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AUXLDATA, pParent)
{

}

AuxlDataShowDlg::~AuxlDataShowDlg()
{
}

void AuxlDataShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AUXLDATA, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(AuxlDataShowDlg, CDialogEx)
END_MESSAGE_MAP()


// AuxlDataShowDlg 消息处理程序


BOOL AuxlDataShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowWindow(SW_SHOWMAXIMIZED);
	LineCnt = 0;
	CRect rect;
	GetClientRect(&rect);
	m_ListCtrl.MoveWindow(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列
	m_ListCtrl.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50, 0);
	for (int i = 1; i != HEAD_INFO_ITEM_NUMS + 1; ++i)
		m_ListCtrl.InsertColumn(i, GetHeadInfoItemStr(i - 1), LVCFMT_CENTER, rect.Width() / 20, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void AuxlDataShowDlg::ListInsert(void* pData, bool b_parse)
{
	CString strNum;
	strNum.Format(_T("%d"), LineCnt);
	m_ListCtrl.InsertItem(LineCnt, strNum);
	BYTE* pHeadData = (BYTE*)pData;
	if (b_parse)
	{
		for (int i = 0; i != HEAD_INFO_ITEM_NUMS; ++i)
		{
			int ByteSize = GetHeadInfoItemSize(i);
			int ByteOff = GetHeadInfoItemOff(i);
			CString strData;
			if (i == 0 || i == 2)
				strData.Format(_T("%c%c%c"), pHeadData[ByteOff], pHeadData[ByteOff + 1], pHeadData[ByteOff + 2]);
			else if (i == 16 || i == 18)
				strData.Format(_T("%c%c%c%c%c%c%c%c"), pHeadData[ByteOff + 7], pHeadData[ByteOff + 6], pHeadData[ByteOff + 5], pHeadData[ByteOff + 4], pHeadData[ByteOff + 3], pHeadData[ByteOff + 2], pHeadData[ByteOff + 1], pHeadData[ByteOff + 0]);
			else if (i == 17)
				strData.Format(_T("%d年%d月%d日 %d:%d:%d"), pHeadData[ByteOff + 5], pHeadData[ByteOff + 4], pHeadData[ByteOff + 3], pHeadData[ByteOff + 2], pHeadData[ByteOff + 1], pHeadData[ByteOff]);
			else
			{
				if (ByteSize <= 8)
				{
					unsigned long long iData = 0;
					memcpy(&iData, pHeadData + ByteOff, ByteSize);
					strData.Format(_T("%lld"), iData);
				}
				else
				{
					strData = "0x";
					for (int j = ByteOff + ByteSize - 1; j != ByteOff - 1; --j)
					{
						CString strTmp;
						strTmp.Format(_T("%x"), pHeadData[j]);
						strData += strTmp;
					}
				}
			}
			m_ListCtrl.SetItemText(LineCnt, i + 1, strData);
		}
	}
	else
	{
		for (int i = 1; i != HEAD_INFO_ITEM_NUMS + 1; ++i)
		{
			int ByteSize = GetHeadInfoItemSize(i - 1);
			int ByteOff = GetHeadInfoItemOff(i - 1);
			CString strData;
			strData = "0x";
			for (int j = ByteOff + ByteSize - 1; j != ByteOff - 1; --j)
			{
				CString strTmp;
				strTmp.Format(_T("%x"), pHeadData[j]);
				strData += strTmp;
			}
			m_ListCtrl.SetItemText(LineCnt, i, strData);
		}
	}
	++LineCnt;
	return;
}
void AuxlDataShowDlg::ShowPlot()
{
	test_Alux("curve","Auxliary Data Plot");
	return;
}