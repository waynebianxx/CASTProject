#pragma once


// PlayBackSetDlg 对话框

class PlayBackSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlayBackSetDlg)

public:
	PlayBackSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PlayBackSetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PLAYBACKSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPBStart();
	afx_msg void OnBnClickedButtonPBEnd();

public:
	CString strStart;
	CString strEnd;
	CString strPath;
	int iSpeed;
	int iSkipFrm;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	int bNomalShow;
	int iCurPath;
};
