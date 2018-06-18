// ImgCmpSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CASTProject.h"
#include "ImgCmpSetDlg.h"
#include "afxdialogex.h"

#include "include/CAST_SrcData.h"
#include "include/PyInterface.h"

// ImgCmpSetDlg 对话框

IMPLEMENT_DYNAMIC(ImgCmpSetDlg, CDialogEx)

ImgCmpSetDlg::ImgCmpSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMGCMPSET, pParent)
{
	vector<float> tmpVec(0);
	m_SpectDN.push_back(tmpVec);
	m_SpectDN.push_back(tmpVec);
	m_SpectDN.push_back(tmpVec);
	m_SpectDN.push_back(tmpVec);
	m_SpectDN.push_back(tmpVec);
	m_CameraLab = 18;
	m_Algr = 6;
	m_ImgLineNum = 1024;
	m_FilterGear = 2;
	m_GainVal = 10;
	m_ClmpSerl = 12;
	m_IntegTime = 2;
	m_SaveTime = 1;
	m_Serial = 5;
	m_CalcNum = 100;
}

ImgCmpSetDlg::~ImgCmpSetDlg()
{
}

void ImgCmpSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CMPSET_CAMERALAB, m_CameraLab);
	DDX_Text(pDX, IDC_EDIT_CMPSET_ALG, m_Algr);
	DDX_Text(pDX, IDC_EDIT_CMPSET_LINENUM, m_ImgLineNum);
	DDX_Text(pDX, IDC_EDIT_CMPSET_FILT, m_FilterGear);
	DDX_Text(pDX, IDC_EDIT_CMPSET_GAIN, m_GainVal);
	DDX_Text(pDX, IDC_EDIT_CMPSET_CLMP, m_ClmpSerl);
	DDX_Text(pDX, IDC_EDIT_CMPSET_INTTIME, m_IntegTime);
	DDX_Text(pDX, IDC_EDIT_CMPSET_SAVEDATE, m_SaveTime);
	DDX_Text(pDX, IDC_EDIT_CMPSET_SERIL, m_Serial);
	DDX_Text(pDX, IDC_EDIT_CMPCALLINENUM, m_CalcNum);
}


BEGIN_MESSAGE_MAP(ImgCmpSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ImgCmpSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ImgCmpSetDlg 消息处理程序
void ImgCmpSetDlg::FileFilter(vector<CString>& WholFiles)
{
	//tmp set
	m_FileteredFNameVecCstr = m_FNameVecCstr;
	//filter the whole files according to the dlg params
	//add code here
	return;
}

void ImgCmpSetDlg::CalcMeanValue()
{
	int fnum = m_pDataVec.size();
	int img_w = 6192;
	int img_h = 1024;
	BYTE spectNum = 0;
	for (int i = 0; i != fnum; ++i)
	{
		memcpy(&img_w, m_pDataVec[i] + 13, 3);
		memcpy(&img_h, m_pDataVec[i] + 16, 3);
		memcpy(&spectNum, m_pDataVec[i] + 21, 1);
		BYTE* pImg = m_pDataVec[i] + 177;
		int idx = 0;
		float fImgSum = 0.0f;
#ifdef _DEBUG
		assert(m_CalcNum <= img_h);
#endif
		for (int h = 0; h != m_CalcNum; ++h)
		{
			for (int w = 0; w != img_w; ++w)
				fImgSum += pImg[idx++];
		}
		m_SpectDN[spectNum].push_back(fImgSum / (m_CalcNum*img_w));
		delete[](m_pDataVec[i]);
	}
	return;
}

void ImgCmpSetDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//read file
	FileFilter(m_FNameVecCstr);//then the m_FileteredFNameVecCstr have configed
	//vector<cstring> to vector<const char*>
	int fnum = m_FileteredFNameVecCstr.size();
	for (int i = 0; i != fnum; ++i)
	{
		BYTE* pTmp = nullptr;
		m_pDataVec.push_back(pTmp);
		string strTmp = CT2A(m_FNameVecCstr[i].GetBuffer());
		m_FileteredFNameVecChar.push_back(strTmp);
	}
	CAST_IMG CastImgTmp;
	CastImgTmp.ReadMultiFile(m_FileteredFNameVecChar, m_pDataVec);
	CalcMeanValue();
	draw_multi_plot(m_SpectDN);
	CDialogEx::OnOK();
}
