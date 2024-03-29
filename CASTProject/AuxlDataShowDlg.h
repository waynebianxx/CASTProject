#pragma once

// AuxlDataShowDlg 对话框

class AuxlDataShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AuxlDataShowDlg)

public:
	AuxlDataShowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AuxlDataShowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AUXLDATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListCtrl;
	void ListInsert(void* pData, bool b_parse = false);
	void ShowPlot();
	int LineCnt;
};
