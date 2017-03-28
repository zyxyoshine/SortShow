
// SortShowView.h : CSortShowView 类的接口
//
 
#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <stdlib.h>
#include "Sort.h"

class CSortShowView : public CFormView
{
protected: // 仅从序列化创建
	CSortShowView();
	DECLARE_DYNCREATE(CSortShowView)

public:
	enum{ IDD = IDD_SORTSHOW_FORM };

// 特性
public:
	CSortShowDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CSortShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_cbSortType;
	CSliderCtrl m_sliderSpeed;
	afx_msg void OnBnClickedButtonBeginsort();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonRestart();
	afx_msg void OnCbnSelchangeComboSorttype();
	void spwanData();
	void ChoseSortType();

private:
	BOOL isPause;
	int * data=NULL;
	int maxSize = 10000;
	int maxHeight;
	int maxWidth;
	int flishIndex = 0;
	int maxCashLength;
	double perWidth;
	CList<int>cashData;
	CString sortType[8];
	CString curSel;
	CRect startRect;
	CPoint startPoint;
	Sort *sort;
public:
	int m_Speed;
	int m_Size;
	int initdata[20] ={ 13,19,3,15,2,6,11,16,9,18,1,14,12,7,4,8,17,10,5,16 };
	afx_msg void OnBnClickedStaticGroup();
};

#ifndef _DEBUG  // SortShowView.cpp 中的调试版本
inline CSortShowDoc* CSortShowView::GetDocument() const
   { return reinterpret_cast<CSortShowDoc*>(m_pDocument); }
#endif

