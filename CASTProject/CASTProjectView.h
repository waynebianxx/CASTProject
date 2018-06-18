
// CASTProjectView.h : CCASTProjectView 类的接口
//

#pragma once

#include <vector>

#include "include/CAST_SrcData.h"
#include "FindDataDlg.h"
#include "AuxlDataShowDlg.h"

typedef struct
{
	int m_TimeIntvl;
	int m_SkipFnum;
	int m_ShowMode;//1 is normal show, 2 is scroll
	bool b_SubPath;
	std::vector<CString> str_Path;
	int m_FrameCnt;
	int m_LineCnt;
	int m_ttNum;
	//used to scroll mode
	BYTE* pSrc1;
	BYTE* pSrc2;
	BYTE* pDst;
}PLAYBACK_PARAM;

class CCASTProjectView : public CScrollView
{
protected: // 仅从序列化创建
	CCASTProjectView();
	DECLARE_DYNCREATE(CCASTProjectView)

// 特性
public:
	CCASTProjectDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCASTProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLoadfile();
	afx_msg void OnPixinfo();

public:
	//tool tip
	CToolTipCtrl m_ToolTip; 
	CString m_TipStr;
	bool m_bToolTipOn;
	PIXEL_PACK m_ttPix;//tool tip pix info to show
	CPoint m_ttPos;
	//show image
	CDC MemDc;
	CRect m_ShImgRect;
	CRect m_RealImgRect;
	bool m_bSubBlkShow;
	CRect m_SubShowRect;
	//play back set
	PLAYBACK_PARAM m_PBParam;
	bool m_bPBPause;//play back pause, 'space key'
	//mouse
	CPoint m_MousePos;
	//find data
	FindDataDlg FDDlg;
	//auxiliary data
	AuxlDataShowDlg AxlDSDlg;
	bool m_bAuxlParse;
public:
	CAST_IMG CastImg;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnShowSet();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	int DrawMemDc(bool b_create);
	void BrowseCurrentAllFile(CString strDir);

	//in this function, file load to CAST_SrcData, create cImage, copy data to cImage, set scroll view size, initial rect
	int FileToShow(CString strFileName);

	afx_msg void OnPlayback();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdatePixinfo(CCmdUI *pCmdUI);
	afx_msg void OnSubBlock();
	afx_msg void OnUpdateSubBlock(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFind();
	afx_msg void OnImgcmpSet();
	afx_msg void OnInnerfactSet();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAuxlidataShow();
	afx_msg void OnHlthchkStatic();
	afx_msg void OnHlthchkDynmc();
};

#ifndef _DEBUG  // CASTProjectView.cpp 中的调试版本
inline CCASTProjectDoc* CCASTProjectView::GetDocument() const
   { return reinterpret_cast<CCASTProjectDoc*>(m_pDocument); }
#endif

