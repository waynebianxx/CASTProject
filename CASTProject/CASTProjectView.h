
// CASTProjectView.h : CCASTProjectView ��Ľӿ�
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
protected: // �������л�����
	CCASTProjectView();
	DECLARE_DYNCREATE(CCASTProjectView)

// ����
public:
	CCASTProjectDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCASTProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // CASTProjectView.cpp �еĵ��԰汾
inline CCASTProjectDoc* CCASTProjectView::GetDocument() const
   { return reinterpret_cast<CCASTProjectDoc*>(m_pDocument); }
#endif

