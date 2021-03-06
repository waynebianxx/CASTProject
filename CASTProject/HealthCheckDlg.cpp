// HealthCheckDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CASTProject.h"
#include "HealthCheckDlg.h"
#include "afxdialogex.h"
#include "include/CAST_SrcData.h"
#include "include/PyInterface.h"
// HealthCheckDlg 对话框

IMPLEMENT_DYNAMIC(HealthCheckDlg, CDialogEx)

HealthCheckDlg::HealthCheckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HEALTH_SET, pParent)
	, m_BadPixThrhd(35)
	, m_SkipThrhd(35)
	, m_SplicePixNum(100)
	, m_ErrLineThrhd(10)
	, m_ErrLineStackNum(100)
	, m_bStaticCh(true)
{

}

HealthCheckDlg::~HealthCheckDlg()
{
}

void HealthCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BAD_THR, m_BadPixThrhd);
	DDX_Text(pDX, IDC_EDIT_SKIP_THR, m_SkipThrhd);
	DDX_Text(pDX, IDC_EDIT_SPLC_NUM, m_SplicePixNum);
	DDX_Text(pDX, IDC_EDIT_ERRLINE_THR, m_ErrLineThrhd);
	DDX_Text(pDX, IDC_EDIT_ERRLINE_STACKNUM, m_ErrLineStackNum);
}


BEGIN_MESSAGE_MAP(HealthCheckDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &HealthCheckDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void HealthCheckDlg::HealthDynamicCalc()
{
	int fnum = m_pDataVec.size();
	int img_w = 6192;
	int img_h = 1024;
	for (int i=0;i!=fnum;++i)
	{
		memcpy(&img_w, m_pDataVec[i] + 13, 3);
		memcpy(&img_h, m_pDataVec[i] + 16, 3);
		BYTE* pImg = m_pDataVec[i] + 177;
		int idx = 0;
		vector<BYTE> tmpMean;
		vector<BYTE> tmpMeanIncr;
		for (int h=0;h!=img_h;++h)
		{
			float fLineSum = 0.0f;
			for (int w=0;w!=img_w;++w)
				fLineSum += pImg[idx++];
			BYTE LineMean = fLineSum / img_w;
			BYTE MeanIcre = h == 0 ? 0 : LineMean - tmpMean[h - 1];
			tmpMean.push_back(LineMean);
			tmpMeanIncr.push_back(MeanIcre);
		}
		m_LineMean.push_back(tmpMean);
		m_LineMeanIncre.push_back(tmpMeanIncr);
		delete[](m_pDataVec[i]);
	}
	return;
}

// HealthCheckDlg 消息处理程序
void HealthCheckDlg::HealthStaticCalc()
{
	float fThredhold = m_BadPixThrhd / 100.0f;
	int fnum = m_pDataVec.size();
	int img_w = 6192;
	int img_h = 1024;
	unsigned long long LineCnt = 0;
	float MeanMin = 0.0f, MeanMax = 0.0f, MeanSum = 0.0f;
	//In order to reduce the amount of computation, 
	//all indexes of static health checking are calculated in one loop.
	for (int i=0;i!=fnum;++i)
	{
		int LineCntOff = 41;
		unsigned long long curLineCnt;
		memcpy(&curLineCnt, m_pDataVec[i] + LineCntOff, 8);
		memcpy(&img_w, m_pDataVec[i] + 13, 3);
		memcpy(&img_h, m_pDataVec[i] + 16, 3);
		if (i == 0)
			LineCnt = curLineCnt;
		else
		{
			if (LineCnt != curLineCnt)
				m_LineSkipVec.push_back(i);
		}

		BYTE* pData = m_pDataVec[i] + 177;//skip head info
		float ImgSum = 0.0f;
		for (int h=0;h!=img_h;++h)
		{
			for (int w=0;w!=img_w;++w)
			{
				int idx = h * img_w + w;
				BYTE intThred = fThredhold * pData[idx];
				ImgSum += pData[idx];
				int xstart = (w - 1) < 0 ? 0 : w - 1;
				int xend = (w + 1) == img_w ? img_w - 1 : w + 1;
				int ystart = (h - 1) < 0 ? 0 : h - 1;
				int yend = (h + 1) == img_h ? img_h - 1 : h + 1;
				bool b_bad = false;
				//sub with around the pixel
				for (int y = ystart; y <= yend; ++y)
				{
					for (int x = xstart; x <= xend; ++x)
					{
						int cur_idx = y * img_w + x;
						BYTE sub = abs(pData[idx] - pData[cur_idx]);
						if (sub > intThred)
						{
							b_bad = true;
							vector<float> info_vec;
							info_vec.push_back(i);
							info_vec.push_back(h);
							info_vec.push_back(w);
							info_vec.push_back(sub / 100.0f);
							m_BadPixInfo.push_back(info_vec);
							break;
						}
					}
					if(b_bad)
						break;
				}
			}
		}
		float MeanVal = ImgSum / (img_w*img_h);
		MeanMin = i == 0 ? MeanVal : (MeanVal > MeanMin ? MeanMin : MeanVal);
		MeanMax = i == 0 ? MeanVal : (MeanVal > MeanMax ? MeanVal : MeanMax);
		MeanSum += MeanVal;
		m_MeanValueVec.push_back(MeanVal);
		delete[](m_pDataVec[i]);
	}
	m_Uniformity_ = (MeanMax - MeanMin) / MeanSum;
	return;
}

void HealthCheckDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//read file
	//vector<cstring> to vector<const char*>
	int fnum = m_FNameVecCstr.size();
	for (int i=0;i!=fnum;++i)
	{
		BYTE* pTmp = nullptr;
		m_pDataVec.push_back(pTmp);
		string strTmp = CT2A(m_FNameVecCstr[i].GetBuffer());
		m_FNameVecChar.push_back(strTmp);
	}
	CAST_IMG CastImgTmp;
	CastImgTmp.ReadMultiFile(m_FNameVecChar, m_pDataVec);
	//calculation
	if (m_bStaticCh)
		HealthStaticCalc();
	else
		HealthDynamicCalc();
	//generate report
	//add code, may use python call the docx library

	CDialogEx::OnOK();
}
