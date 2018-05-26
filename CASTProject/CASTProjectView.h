
// CASTProjectView.h : CCASTProjectView 类的接口
//

#pragma once

#include <vector>

#include "include/CAST_SrcData.h"

typedef struct 
{
	int m_TimeIntvl;
	int m_SkipFnum;
	int m_ShowMode;
	bool b_SubPath;
	std::vector<CString> str_Path;
	int cnt;
	int m_ttNum;
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
	//play back set
	PLAYBACK_PARAM m_PBParam;
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
	afx_msg void OnPlayback();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // CASTProjectView.cpp 中的调试版本
inline CCASTProjectDoc* CCASTProjectView::GetDocument() const
   { return reinterpret_cast<CCASTProjectDoc*>(m_pDocument); }
#endif

