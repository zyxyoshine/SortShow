
// SortShow.h : SortShow Ӧ�ó������ͷ�ļ�
//
#pragma once
 
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSortShowApp:
// �йش����ʵ�֣������ SortShow.cpp
//

class CSortShowApp : public CWinAppEx
{
public:
	CSortShowApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSortShowApp theApp;
