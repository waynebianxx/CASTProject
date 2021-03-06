#pragma once

#include <vector>
#include <string>
using namespace std;

// HealthCheckDlg 对话框

class HealthCheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HealthCheckDlg)

public:
	HealthCheckDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HealthCheckDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HEALTH_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vector<CString> m_FNameVecCstr;
	vector<string> m_FNameVecChar;
	vector<BYTE*> m_pDataVec;

	//check result
	vector<vector<float>> m_BadPixInfo;//file num, pix_h_pos, pix_w_pos, Difference value
	vector<BYTE> m_MeanValueVec;//imgage mean value
	vector<int> m_LineSkipVec;//which frame have Line skip.
	float m_Uniformity_;//uniformity percent
	vector<vector<BYTE>> m_LineMean;
	vector<vector<BYTE>> m_LineMeanIncre;
	
	bool m_bStaticCh;

	int m_BadPixThrhd;
	int m_SkipThrhd;
	int m_SplicePixNum;
	int m_ErrLineThrhd;
	int m_ErrLineStackNum;
	afx_msg void OnBnClickedOk();
	void HealthStaticCalc();
	void HealthDynamicCalc();
};
