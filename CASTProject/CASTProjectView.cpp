
// CASTProjectView.cpp : CCASTProjectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CASTProject.h"
#endif

#include <string>
#include "CASTProjectDoc.h"
#include "CASTProjectView.h"
#include "ShowDlg.h"
#include "PlayBackSetDlg.h"
#include "ImgCmpSetDlg.h"
#include "InnerFactTestSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCASTProjectView

IMPLEMENT_DYNCREATE(CCASTProjectView, CScrollView)

BEGIN_MESSAGE_MAP(CCASTProjectView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_LoadFile, &CCASTProjectView::OnLoadfile)
	ON_COMMAND(ID_PixInfo, &CCASTProjectView::OnPixinfo)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32775, &CCASTProjectView::OnShowSet)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_COMMAND(ID_PlayBack, &CCASTProjectView::OnPlayback)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_PixInfo, &CCASTProjectView::OnUpdatePixinfo)
	ON_COMMAND(ID_SUB_BLOCK, &CCASTProjectView::OnSubBlock)
	ON_UPDATE_COMMAND_UI(ID_SUB_BLOCK, &CCASTProjectView::OnUpdateSubBlock)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FIND, &CCASTProjectView::OnFind)
	ON_COMMAND(ID_IMGCMP_SET, &CCASTProjectView::OnImgcmpSet)
	ON_COMMAND(ID_INNRFCT_SET, &CCASTProjectView::OnInnerfactSet)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CCASTProjectView 构造/析构

CCASTProjectView::CCASTProjectView()
{
	// TODO: 在此处添加构造代码

}

CCASTProjectView::~CCASTProjectView()
{
}

BOOL CCASTProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	m_bToolTipOn = false;
	m_bSubBlkShow = false;
	m_bPBPause = false;
	m_MousePos.x = 0;
	m_MousePos.y = 0;
	return CScrollView::PreCreateWindow(cs);
}

// CCASTProjectView 绘制

void CCASTProjectView::OnDraw(CDC* pDC)
{
	CCASTProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (!CastImg.cimg.IsNull())
		pDC->StretchBlt(0, 0, CastImg.m_ImgW, CastImg.m_ImgH, &MemDc, 0, 0, CastImg.m_ImgW, CastImg.m_ImgH, SRCCOPY);
}

void CCASTProjectView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = 100;
	sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	//tool tip initial
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(100);
	m_TipStr = "";
	m_ToolTip.AddTool(this, m_TipStr);
	m_ToolTip.Activate(FALSE);
}


// CCASTProjectView 打印

BOOL CCASTProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCASTProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCASTProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCASTProjectView 诊断

#ifdef _DEBUG
void CCASTProjectView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCASTProjectView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCASTProjectDoc* CCASTProjectView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCASTProjectDoc)));
	return (CCASTProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CCASTProjectView 消息处理程序


int CCASTProjectView::FileToShow(CString strFileName)
{
	std::string strName = CT2A(strFileName.GetBuffer());
	CastImg.LoadFile(strName.c_str());
	CastImg.CreateCImg(CastImg.m_ImgW, CastImg.m_ImgH);
	CastImg.CopyDataToCImg(CastImg.m_pImgData, CastImg.m_ImgW, CastImg.m_ImgH);
	// set scroll view size
	CSize sizeTotal;
	sizeTotal.cx = CastImg.m_ImgW;
	sizeTotal.cy = CastImg.m_ImgH;
	SetScrollSizes(MM_TEXT, sizeTotal);
	//set image rect
	m_ShImgRect.left = 0;
	m_ShImgRect.right = CastImg.m_ImgW;
	m_ShImgRect.top = 0;
	m_ShImgRect.bottom = CastImg.m_ImgH;
	m_RealImgRect.left = 0;
	m_RealImgRect.right = CastImg.m_ImgW;
	m_RealImgRect.top = 0;
	m_RealImgRect.bottom = CastImg.m_ImgH;
	return 1;
}

void CCASTProjectView::OnLoadfile()
{
	// TODO: 在此添加命令处理程序代码
// 	CFileDialog dlg(TRUE, _T(".raw"), _T("*.raw"), OFN_HIDEREADONLY |
// 		OFN_OVERWRITEPROMPT, _T("raw文件(*.raw)|*.raw|JPEG文件(*.JPEG)|*.JPEG|位图文件(*.bmp)|*.bmp||"));
// 	if (dlg.DoModal() == IDOK)
// 	{
// 		CString fName = dlg.GetPathName();
//		FileToShow(fName);
// 	}
	FileToShow(_T("L32_mc_t0019_tdi32222_g11111_C1B_0.raw"));
	DrawMemDc(true);
}


void CCASTProjectView::OnPixinfo()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_bToolTipOn)
	{
		m_ToolTip.Activate(TRUE);
		m_bToolTipOn = true;
	}
	else
	{
		m_ToolTip.Activate(FALSE);
		m_bToolTipOn = false;
	}
}


BOOL CCASTProjectView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_MOUSEMOVE)
		m_ToolTip.RelayEvent(pMsg);

// 	if (pMsg->message == WM_KEYDOWN)
// 	{
// 		switch (pMsg->wParam)
// 		{
// 		case 'F':
// 			if (::GetKeyState(VK_CONTROL) < 0)
// 			{
// 				FindDataDlg FDDlg;
// 				if (FDDlg.DoModal())
// 					//copy param from the dlg class
// 					;
// 			}
// 			break;
// 		default:
// 			break;
// 
// 		}
// 	}

	return CScrollView::PreTranslateMessage(pMsg);
}


void CCASTProjectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bToolTipOn)
	{
		if (m_MousePos.x!=point.x || m_MousePos.y!=point.y)
		{
			m_ttPos = GetScrollPosition();
			m_ttPos.x += point.x;
			m_ttPos.y += point.y;
			m_ttPix.m_PixV = CastImg.cimg.GetPixel(m_ttPos.x, m_ttPos.y);
			m_TipStr.Format(_T("X:%d Y:%d\nR:%d\nG:%d\nB:%d\nSRC:0x%X"), m_ttPos.x, m_ttPos.y, m_ttPix.RGBA.m_R, m_ttPix.RGBA.m_G, m_ttPix.RGBA.m_B, m_ttPix.m_PixV);
			m_ToolTip.UpdateTipText(m_TipStr, this);
		}
	}
	m_MousePos.x = point.x;
	m_MousePos.y = point.y;
	CScrollView::OnMouseMove(nFlags, point);
}

void CCASTProjectView::OnShowSet()
{
	// TODO: 在此添加命令处理程序代码
	ShowDlg SDlg;
	if (IDOK==SDlg.DoModal())
	{
		BIT_RANGE BitRg=from15to8;
		switch (SDlg.m_SldPos)
		{
		case 0:
			BitRg = from15to8;
		case 1:
			BitRg = from14to7;
		case 2:
			BitRg = from13to6;
		case 3:
			BitRg = from12to5;
		case 4:
			BitRg = from11to4;
		case 5:
			BitRg = from10to3;
		case 6:
			BitRg = from9to2;
		case 7:
			BitRg = from8to1;
		case 8:
			BitRg = from7to0;
		default:
			break;
		}
		CastImg.CopyDataToCImg(CastImg.m_pImgData, CastImg.m_ImgW, CastImg.m_ImgH, BitRg);
		m_ShImgRect.left = 0;
		m_ShImgRect.right = CastImg.m_ImgW;
		m_ShImgRect.top = 0;
		m_ShImgRect.bottom = CastImg.m_ImgH;
		DrawMemDc(false);
	}
}

void CCASTProjectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	bool bCtrl = GetAsyncKeyState(VK_CONTROL) < 0;
	if (bCtrl)
	{
		switch (nChar)
		{
		case 'F':
			FDDlg.Create(IDD_DIALOG_FINDSET,this);
			FDDlg.ShowWindow(SW_SHOW);
			//copy param from the dlg class
			break;
		default:
			break;
		}
	}
	if (GetAsyncKeyState(VK_SPACE)<0)
		m_bPBPause = !m_bPBPause;
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCASTProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bSubBlkShow)
	{
		m_SubShowRect.left = point.x;
		m_SubShowRect.top = point.y;
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CCASTProjectView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bSubBlkShow)
	{
		if (m_SubShowRect.left < point.x)
			m_SubShowRect.right = point.x;
		else
		{
			m_SubShowRect.right = m_SubShowRect.left;
			m_SubShowRect.left = point.x;
		}
		if (m_SubShowRect.top < point.y)
			m_SubShowRect.bottom = point.y;
		else
		{
			m_SubShowRect.bottom = m_SubShowRect.top;
			m_SubShowRect.top = point.y;
		}
		DrawMemDc(false);
	}
	CScrollView::OnLButtonUp(nFlags, point);
}


void CCASTProjectView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CScrollView::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CCASTProjectView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetKeyState(VK_CONTROL)<0)//image zoom show
	{
		float w = m_ShImgRect.right, h = m_ShImgRect.bottom;
		float scale = 1.0f + zDelta / 120.0*0.1f;
		w = w*scale;
		h = h*scale;
		m_ShImgRect.right = w < 1.0f ? 1 : w;
		m_ShImgRect.bottom = h < 1.0f ? 1 : h;
		DrawMemDc(false);
	}
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


void CCASTProjectView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//show normal mode
	m_ShImgRect.left = 0;
	m_ShImgRect.right = CastImg.m_ImgW;
	m_ShImgRect.top = 0;
	m_ShImgRect.bottom = CastImg.m_ImgH;
	m_bSubBlkShow = false;
	DrawMemDc(false);
	CScrollView::OnMButtonDown(nFlags, point);
}


int CCASTProjectView::DrawMemDc(bool b_create)
{
	if (b_create)
	{
		if (MemDc.m_hDC != NULL)
			MemDc.DeleteDC();
		MemDc.CreateCompatibleDC(this->GetDC());
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(this->GetDC(), m_RealImgRect.Width(), m_RealImgRect.Height());
		MemDc.SelectObject(&bitmap);
		MemDc.FillSolidRect(m_RealImgRect, RGB(255, 255, 255));
		CastImg.cimg.Draw(MemDc.GetSafeHdc(), m_RealImgRect);
		bitmap.DeleteObject();
	}
	else
	{
		if (MemDc.m_hDC == NULL)
		{
			MemDc.CreateCompatibleDC(this->GetDC());
			CBitmap bitmap;
			bitmap.CreateCompatibleBitmap(this->GetDC(), m_RealImgRect.Width(), m_RealImgRect.Height());
			MemDc.SelectObject(&bitmap);
		}
		MemDc.FillSolidRect(m_RealImgRect, RGB(255, 255, 255));
		if (m_bSubBlkShow)
			CastImg.cimg.Draw(MemDc.GetSafeHdc(), 0, 0, m_SubShowRect.Width(), m_SubShowRect.Height(), m_SubShowRect.left, m_SubShowRect.top, m_SubShowRect.Width(), m_SubShowRect.Height());
		else
			CastImg.cimg.Draw(MemDc.GetSafeHdc(), m_ShImgRect);
	}
	Invalidate();
	return 0;
}

void CCASTProjectView::BrowseCurrentAllFile(CString strDir)
{
	if (strDir == _T(""))
		return;
	else
	{
		if (strDir.Right(1) != _T("\\"))
			strDir += L"\\";
		strDir = strDir + _T("*.*");
	}
	CFileFind finder;
	CString strPath;
	BOOL bWorking = finder.FindFile(strDir);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		strPath = finder.GetFilePath();
		if (finder.IsDirectory() && !finder.IsDots())
			BrowseCurrentAllFile(strPath);
		else if (!finder.IsDirectory() && !finder.IsDots())
			m_PBParam.str_Path.push_back(strPath);
		else
			continue;
	}
	return;
}

void CCASTProjectView::OnPlayback()
{
	// TODO: 在此添加命令处理程序代码
	PlayBackSetDlg PBDlg;
	if (IDOK == PBDlg.DoModal())
	{
		BrowseCurrentAllFile(PBDlg.strPath);
		m_PBParam.m_SkipFnum = PBDlg.iSkipFrm;
		m_PBParam.m_TimeIntvl = PBDlg.iSpeed;
		m_PBParam.m_ShowMode = PBDlg.bNomalShow;
		m_PBParam.b_SubPath = (PBDlg.iCurPath == 0);
	}
	m_PBParam.m_FrameCnt = 0;
	m_PBParam.m_LineCnt = 0;
	m_PBParam.m_ttNum = m_PBParam.str_Path.size();
	FileToShow(m_PBParam.str_Path[0]);
	m_bPBPause = false;
	SetTimer(m_PBParam.m_ShowMode, m_PBParam.m_TimeIntvl, NULL);
}


void CCASTProjectView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_bPBPause)
	{
		if (1 == nIDEvent)//normal playback
		{
			std::string strName = CT2A(m_PBParam.str_Path[m_PBParam.m_FrameCnt].GetBuffer());
			CastImg.LoadFile(strName.c_str());
			CastImg.CopyDataToCImg(CastImg.m_pImgData, CastImg.m_ImgW, CastImg.m_ImgH);
			DrawMemDc(false);
			//counter set
			m_PBParam.m_FrameCnt += m_PBParam.m_SkipFnum;
			m_PBParam.m_FrameCnt = m_PBParam.m_FrameCnt >= m_PBParam.m_ttNum ? 0 : m_PBParam.m_FrameCnt;
		}
		else if (2 == nIDEvent)//scroll screen playback
		{
			if (0 == m_PBParam.m_LineCnt)
			{
				std::string strName1 = CT2A(m_PBParam.str_Path[m_PBParam.m_FrameCnt].GetBuffer());
				std::string strName2 = CT2A(m_PBParam.str_Path[m_PBParam.m_FrameCnt + 1].GetBuffer());
				CastImg.ReadFile(strName1.c_str(), m_PBParam.pSrc1);
				CastImg.ReadFile(strName2.c_str(), m_PBParam.pSrc2);
				m_PBParam.pDst = (BYTE*)CastImg.m_pImgData;
			}
			//src to dst
			int iOffSet = 32;
			//copy from src1
			memcpy(m_PBParam.pDst, \
				m_PBParam.pSrc1 + iOffSet + m_PBParam.m_LineCnt*CastImg.m_LinePitch, \
				(CastImg.m_ImgH - m_PBParam.m_LineCnt)*CastImg.m_LinePitch);
			//copy from src2
			memcpy(m_PBParam.pDst + (CastImg.m_ImgH - m_PBParam.m_LineCnt)*CastImg.m_LinePitch, \
				m_PBParam.pSrc2 + iOffSet, \
				m_PBParam.m_LineCnt*CastImg.m_LinePitch);
			//counter set
			m_PBParam.m_LineCnt += m_PBParam.m_SkipFnum;
			if (m_PBParam.m_LineCnt >= CastImg.m_CImgH)
			{
				++m_PBParam.m_FrameCnt;
				m_PBParam.m_FrameCnt = m_PBParam.m_FrameCnt == m_PBParam.m_ttNum ? 0 : m_PBParam.m_FrameCnt;
				m_PBParam.m_LineCnt = 0;
				delete[]m_PBParam.pSrc1;
				delete[]m_PBParam.pSrc2;
			}
			CastImg.CopyDataToCImg(CastImg.m_pImgData, CastImg.m_ImgW, CastImg.m_ImgH);
			DrawMemDc(false);
		}
		else
			int i = 0;//nothing to do
	}
	CScrollView::OnTimer(nIDEvent);
}


void CCASTProjectView::OnUpdatePixinfo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bToolTipOn);
}


void CCASTProjectView::OnSubBlock()
{
	// TODO: 在此添加命令处理程序代码
	m_bSubBlkShow = !m_bSubBlkShow;
}


void CCASTProjectView::OnUpdateSubBlock(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bSubBlkShow);
}


void CCASTProjectView::OnFind()
{
	// TODO: 在此添加命令处理程序代码
	FindDataDlg FdDlg;
	if (FdDlg.DoModal())
	{
		//read param from the dlg class
	}
	//do the find
}


void CCASTProjectView::OnImgcmpSet()
{
	// TODO: 在此添加命令处理程序代码
	ImgCmpSetDlg ICSDlg;
	if (ICSDlg.DoModal())
	{
		//read param from the dlg class
	}
	//do the compare
}


void CCASTProjectView::OnInnerfactSet()
{
	// TODO: 在此添加命令处理程序代码
	InnerFactTestSetDlg IFTSDlg;
	if (IFTSDlg.DoModal())
	{
		//read param from the dlg class
	}
	//do the testing
}