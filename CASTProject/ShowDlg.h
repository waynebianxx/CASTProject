#pragma once
#include "afxcmn.h"


// ShowDlg �Ի���

class ShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShowDlg)

public:
	ShowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShowDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Slider;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSlr();
	afx_msg void OnBnClickedButtonSll();
	int m_SldPos;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedCancel();
};
