
// CASTProjectView.cpp : CCASTProjectView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CASTProject.h"
#endif

#include "CASTProjectDoc.h"
#include "CASTProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCASTProjectView

IMPLEMENT_DYNCREATE(CCASTProjectView, CScrollView)

BEGIN_MESSAGE_MAP(CCASTProjectView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCASTProjectView ����/����

CCASTProjectView::CCASTProjectView()
{
	// TODO: �ڴ˴���ӹ������

}

CCASTProjectView::~CCASTProjectView()
{
}

BOOL CCASTProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CCASTProjectView ����

void CCASTProjectView::OnDraw(CDC* /*pDC*/)
{
	CCASTProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CCASTProjectView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CCASTProjectView ��ӡ

BOOL CCASTProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCASTProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCASTProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CCASTProjectView ���

#ifdef _DEBUG
void CCASTProjectView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CCASTProjectView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCASTProjectDoc* CCASTProjectView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCASTProjectDoc)));
	return (CCASTProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CCASTProjectView ��Ϣ�������
