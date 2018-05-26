
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


void CCASTProjectView::OnLoadfile()
{
	// TODO: 在此添加命令处理程序代码
// 	CFileDialog dlg(TRUE, _T(".raw"), _T("*.raw"), OFN_HIDEREADONLY |
// 		OFN_OVERWRITEPROMPT, _T("raw文件(*.raw)|*.raw|JPEG文件(*.JPEG)|*.JPEG|位图文件(*.bmp)|*.bmp||"));
// 	if (dlg.DoModal() == IDOK)
// 	{
// 		CString fName = dlg.GetPathName();
// 		std::string strName = CT2A(fName.GetBuffer());
// 		CastImg.LoadFile(strName.c_str());
// 	}
	CastImg.LoadFile("L32_mc_t0019_tdi32222_g11111_C1B_0.raw");
	CastImg.CreateCImg();
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

	return CScrollView::PreTranslateMessage(pMsg);
}


void CCASTProjectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bToolTipOn)
	{
		m_ttPos = GetScrollPosition();
		m_ttPos.x += point.x;
		m_ttPos.y += point.y;
		m_ttPix.m_PixV = CastImg.cimg.GetPixel(m_ttPos.x, m_ttPos.y);
		m_TipStr.Format(_T("X:%d Y:%d\nR:%d\nG:%d\nB:%d\nSRC:0x%X"), m_ttPos.x, m_ttPos.y, m_ttPix.RGBA.m_R, m_ttPix.RGBA.m_G, m_ttPix.RGBA.m_B, m_ttPix.m_PixV);
		m_ToolTip.UpdateTipText(m_TipStr, this);
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CCASTProjectView::OnShowSet()
{
	// TODO: 在此添加命令处理程序代码
	ShowDlg SDlg;
	if (IDOK==SDlg.DoModal())
	{
		CastImg.CopyDataToCImg((BIT_RANGE)SDlg.m_SldPos);
		m_ShImgRect.left = 0;
		m_ShImgRect.right = CastImg.m_ImgW;
		m_ShImgRect.top = 0;
		m_ShImgRect.bottom = CastImg.m_ImgH;
		DrawMemDc(false);
	}
}


void CCASTProjectView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		MemDc.FillSolidRect(m_RealImgRect, RGB(255, 255, 255));
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
			BrowseCurrentAllFile(strPath); //递归调用  
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
	//PlayBackSetDlg PBDlg;
	BrowseCurrentAllFile(_T("G:\\myproject\\vs\\CASTProject\\src_data"));
	m_PBParam.cnt = 0;
	m_PBParam.m_ttNum = m_PBParam.str_Path.size();
	SetTimer(1, 1000, NULL);
}


void CCASTProjectView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1==nIDEvent)//normal playback
	{
		std::string strName = CT2A(m_PBParam.str_Path[m_PBParam.cnt].GetBuffer());
		CastImg.LoadFile(strName.c_str());
		if (0 == m_PBParam.cnt)
		{
			CastImg.CreateCImg();
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
		}
		CastImg.CopyDataToCImg(from15to8);
		DrawMemDc(0 == m_PBParam.cnt);
		++m_PBParam.cnt;
		m_PBParam.cnt = m_PBParam.cnt == m_PBParam.m_ttNum ? 0 : m_PBParam.cnt;
		Invalidate();
	}
	CScrollView::OnTimer(nIDEvent);
}
