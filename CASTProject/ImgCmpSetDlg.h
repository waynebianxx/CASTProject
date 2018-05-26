#pragma once


// ImgCmpSetDlg 对话框

class ImgCmpSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImgCmpSetDlg)

public:
	ImgCmpSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ImgCmpSetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
