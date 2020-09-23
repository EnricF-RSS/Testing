
// PIC32_EcatLinkStatus_LogFileProcView.cpp : implementation of the CPIC32EcatLinkStatusLogFileProcView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PIC32_EcatLinkStatus_LogFileProc.h"
#endif

#include "PIC32_EcatLinkStatus_LogFileProcDoc.h"
#include "PIC32_EcatLinkStatus_LogFileProcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPIC32EcatLinkStatusLogFileProcView

IMPLEMENT_DYNCREATE(CPIC32EcatLinkStatusLogFileProcView, CView)

BEGIN_MESSAGE_MAP(CPIC32EcatLinkStatusLogFileProcView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPIC32EcatLinkStatusLogFileProcView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPIC32EcatLinkStatusLogFileProcView construction/destruction

CPIC32EcatLinkStatusLogFileProcView::CPIC32EcatLinkStatusLogFileProcView() noexcept
{
	// TODO: add construction code here

}

CPIC32EcatLinkStatusLogFileProcView::~CPIC32EcatLinkStatusLogFileProcView()
{
}

BOOL CPIC32EcatLinkStatusLogFileProcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPIC32EcatLinkStatusLogFileProcView drawing

void CPIC32EcatLinkStatusLogFileProcView::OnDraw(CDC* /*pDC*/)
{
	CPIC32EcatLinkStatusLogFileProcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CPIC32EcatLinkStatusLogFileProcView printing


void CPIC32EcatLinkStatusLogFileProcView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPIC32EcatLinkStatusLogFileProcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPIC32EcatLinkStatusLogFileProcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPIC32EcatLinkStatusLogFileProcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPIC32EcatLinkStatusLogFileProcView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPIC32EcatLinkStatusLogFileProcView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPIC32EcatLinkStatusLogFileProcView diagnostics

#ifdef _DEBUG
void CPIC32EcatLinkStatusLogFileProcView::AssertValid() const
{
	CView::AssertValid();
}

void CPIC32EcatLinkStatusLogFileProcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPIC32EcatLinkStatusLogFileProcDoc* CPIC32EcatLinkStatusLogFileProcView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPIC32EcatLinkStatusLogFileProcDoc)));
	return (CPIC32EcatLinkStatusLogFileProcDoc*)m_pDocument;
}
#endif //_DEBUG


// CPIC32EcatLinkStatusLogFileProcView message handlers
