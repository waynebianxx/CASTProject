
// CASTProjectView.cpp : CCASTProjectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
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

	return CScrollView::PreCreateWindow(cs);
}

// CCASTProjectView 绘制

void CCASTProjectView::OnDraw(CDC* /*pDC*/)
{
	CCASTProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CCASTProjectView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
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
