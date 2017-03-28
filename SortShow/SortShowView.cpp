
// SortShowView.cpp : CSortShowView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SortShow.h"
#endif

#include "SortShowDoc.h"
#include "SortShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSortShowView

IMPLEMENT_DYNCREATE(CSortShowView, CFormView)

BEGIN_MESSAGE_MAP(CSortShowView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_BeginSort, &CSortShowView::OnBnClickedButtonBeginsort)
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CSortShowView::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_Restart, &CSortShowView::OnBnClickedButtonRestart)
	ON_CBN_SELCHANGE(IDC_COMBO_SortType, &CSortShowView::OnCbnSelchangeComboSorttype)
	ON_BN_CLICKED(IDC_STATIC_Group, &CSortShowView::OnBnClickedStaticGroup)
END_MESSAGE_MAP()

// CSortShowView 构造/析构

CSortShowView::CSortShowView()
	: CFormView(CSortShowView::IDD)
	, m_Speed(1)
	, m_Size(20)
{
	// TODO:  在此处添加构造代码
	isPause = false;
	sort = new Sort();
}

CSortShowView::~CSortShowView()
{
	delete[]data;
}
 
int indexA = 0, indexB = 0;

CBrush cb_ChangeRect(RGB(255, 0, 0));
CPen   cp_Round(PS_SOLID, 1, RGB(0, 0, 0));
CPen   cp_ChangeRect(PS_SOLID, 1, RGB(0, 0, 0));
CPen   cp_FlishRoud(PS_SOLID, 1, RGB(0, 0, 0));

void CSortShowView::OnDraw(CDC * pDC)
{
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC,maxWidth,maxHeight);
	CBitmap * pOldBitmap = MemDC.SelectObject(&MemBitmap);
	
	MemDC.FillSolidRect(0,0,maxWidth,maxHeight, RGB(240, 240, 240));
	
	for (int i = 0; i < m_Size ; i++)
	{
		CBrush cb_VisitRect(RGB((data[i] %25)*10, (5 + data[i] %20)*10, (3 + data[i]%21)*10));
		CBrush *pOldBrush = MemDC.SelectObject(&cb_VisitRect);
		CPen   *pOldPen = MemDC.SelectObject(&cp_Round);
		CPoint p1, p2;
		p1.x = startPoint.x + int(perWidth*i);
		p1.y = startPoint.y - data[i] + 10;
		p2.x = p1.x + (int)perWidth;
		p2.y = startPoint.y + 10;

		MemDC.Rectangle(CRect(p1, p2));
		if (perWidth < 1)
		{
			MemDC.MoveTo(p1);
			MemDC.LineTo(p2);
		}

		MemDC.SelectObject(pOldBrush);
		MemDC.SelectObject(pOldPen);

	}
	for (int i = 0; i<m_Speed; i++)
	{
		if (cashData.GetCount() > 0 && !isPause)
		{
			Sleep(345);
			flishIndex = 0;
			int valueB=-1,indexA=-1;
			indexA = cashData.GetHead();
			cashData.RemoveHead();
			int valueA = cashData.GetHead();
			cashData.RemoveHead();

			if (cashData.GetCount()> 0)
			{
				indexB = cashData.GetHead();
				cashData.RemoveHead();
				valueB = cashData.GetHead();
				cashData.RemoveHead();
			}

			CPoint p1, p2, p3, p4;
			p1.x = startPoint.x + int(perWidth* (indexA));
			p1.y = startPoint.y - data[indexA] + 10;
			p2.x = p1.x + (int)perWidth;
			p2.y = startPoint.y + 10;

			if (indexB >= 0)
			{
				p3.x = startPoint.x + int(perWidth* (indexB));
				p3.y = startPoint.y - data[indexB] + 10;
				p4.x = p3.x + (int)perWidth;
				p4.y = startPoint.y + 10;
			}
			CBrush *pOldBrush = MemDC.SelectObject(&cb_ChangeRect);
			CPen   *pOldPen = MemDC.SelectObject(&cp_ChangeRect);

			MemDC.Rectangle(CRect(p1, p2));
			if (perWidth < 1)
			{
				MemDC.MoveTo(p1);
				MemDC.LineTo(p2);
			}
			

			if (indexB >= 0)
			{
				MemDC.Rectangle(CRect(p3, p4));
				if (perWidth < 1)
				{
					MemDC.MoveTo(p3);
					MemDC.LineTo(p4);
				}
			}
			MemDC.SelectObject(pOldBrush);
			MemDC.SelectObject(pOldPen);

			data[indexA] = valueA;

			if (indexB >= 0)
			{
				data[indexB] = valueB;
			}

		}
	}

	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->BitBlt(0,0,maxWidth,maxHeight,&MemDC,0,0,SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	

}

void CSortShowView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SortType, m_cbSortType);
}

BOOL CSortShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CFormView::PreCreateWindow(cs);
}

void CSortShowView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);

	sortType[0] = "直接插入排序";
	sortType[1] = "折半插入排序";
	sortType[2] = "希尔排序";
	sortType[3] = "冒泡排序";
	sortType[4] = "快速排序";
	sortType[5] = "直接选择排序";
	sortType[6] = "堆排序";
	sortType[7] = "二路归并排序";
	for (int i = 0; i < 8; i++)
	{
		m_cbSortType.AddString(sortType[i]);
	}

	CRect rect;
	GetDlgItem(IDC_STATIC_Group)->GetWindowRect(&rect);
	ScreenToClient(rect);
	startPoint.x = rect.left;
	startPoint.y = rect.bottom;
	maxHeight = rect.bottom - rect.top;
	maxWidth = rect.right - rect.left + 10;
	startRect = rect;
	spwanData();
}

void CSortShowView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
}

void CSortShowView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CSortShowView 诊断

#ifdef _DEBUG
void CSortShowView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSortShowView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSortShowDoc* CSortShowView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortShowDoc)));
	return (CSortShowDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortShowView 消息处理程序

void CSortShowView::OnTimer(UINT_PTR nIDEvent)
{
	InvalidateRect(startRect, false);
	CClientDC dc(this);
}
void CSortShowView::OnBnClickedButtonBeginsort()
{
	if (data == NULL)
	{
		spwanData();
	}

	if (isPause)
	{
		isPause = false;
	}
	else
	{
		ChoseSortType();
	}
	SetTimer(1, 33, NULL);
}
void CSortShowView::OnBnClickedButtonPause()
{
	// TODO:  在此添加控件通知处理程序代码
	isPause = true;
}
void CSortShowView::OnBnClickedButtonRestart()
{
	// TODO:  在此添加控件通知处理程序代码
	Invalidate();
	spwanData();
	isPause = false;
	cashData.RemoveAll();
	SetTimer(1,0,NULL);
}
void CSortShowView::OnCbnSelchangeComboSorttype()
{
	// TODO:  在此添加控件通知处理程序代码
	int curIndex = m_cbSortType.GetCurSel();
	m_cbSortType.GetLBText(curIndex,curSel);
}

void CSortShowView::spwanData()
{
	UpdateData(TRUE);
	data = new int[m_Size];
	flishIndex = 0;
	maxCashLength = 1;

	perWidth = ((double)maxWidth - 10) / (double) m_Size;
	double perHeight = (double)maxHeight / (double)m_Size;
	
	for (int i = 0; i < m_Size; i++)
	{
		data[i]= int(perHeight * (initdata[i]+1));
	}
	data[m_Size - 1]++;
	CClientDC dc(this);
	CBrush backGroud(RGB(245, 245, 245));
	dc.FillRect(startRect, &backGroud);
}

void CSortShowView::ChoseSortType()
{
	UpdateData(TRUE);
	if (curSel == sortType[0])
	{
		sort->Insert(data, m_Size, &cashData);
	}
	else if (curSel == sortType[1])
	{
		sort->Insert2(data, m_Size, &cashData);
	}
	else if (curSel == sortType[2])
	{
		sort->Shell(data, m_Size, &cashData);
	}
	else if (curSel == sortType[3])
	{
		sort->Bubble(data, m_Size, &cashData);
	}
	else if (curSel == sortType[4])
	{
		sort->Quick(data, m_Size, &cashData);
	}
	else if (curSel == sortType[5])
	{
		sort->Select(data, m_Size, &cashData);
	}
	else if (curSel == sortType[6])
	{
		sort->Heap(data, m_Size, &cashData);
	}
	else if (curSel == sortType[7])
	{
		sort->Merge(data, m_Size, &cashData);
	}
	maxCashLength = cashData.GetCount();
}


void CSortShowView::OnBnClickedStaticGroup()
{
	// TODO: 在此添加控件通知处理程序代码
}
