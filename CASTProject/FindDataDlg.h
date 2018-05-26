#pragma once


// FindDataDlg 对话框

class FindDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FindDataDlg)

public:
	FindDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FindDataDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
