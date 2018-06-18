#pragma once
#include <vector>
#include <string>
using namespace std;

// ImgCmpSetDlg 对话框

class ImgCmpSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImgCmpSetDlg)

public:
	ImgCmpSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ImgCmpSetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMGCMPSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_CameraLab;
	int m_Algr;
	int m_ImgLineNum;
	int m_FilterGear;
	int m_GainVal;
	int m_ClmpSerl;
	int m_IntegTime;
	int m_SaveTime;
	int m_Serial;
	int m_CalcNum;
	afx_msg void OnBnClickedOk();
	void FileFilter(vector<CString>& WholFiles);
	void CalcMeanValue();
	vector<CString> m_FNameVecCstr;
	vector<CString> m_FileteredFNameVecCstr;
	vector<string> m_FileteredFNameVecChar;
	vector<BYTE*> m_pDataVec;
	vector<vector<float>> m_SpectDN;//Each spectrum section's DN mean value, according to cal line num
};
