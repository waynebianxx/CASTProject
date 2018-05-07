
// CASTProjectView.h : CCASTProjectView ��Ľӿ�
//

#pragma once


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
};

#ifndef _DEBUG  // CASTProjectView.cpp �еĵ��԰汾
inline CCASTProjectDoc* CCASTProjectView::GetDocument() const
   { return reinterpret_cast<CCASTProjectDoc*>(m_pDocument); }
#endif

