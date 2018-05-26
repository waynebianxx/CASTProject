#pragma once


// InnerFactTestSetDlg 对话框

class InnerFactTestSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InnerFactTestSetDlg)

public:
	InnerFactTestSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InnerFactTestSetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
