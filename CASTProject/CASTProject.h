
// CASTProject.h : CASTProject Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCASTProjectApp:
// �йش����ʵ�֣������ CASTProject.cpp
//

class CCASTProjectApp : public CWinApp
{
public:
	CCASTProjectApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCASTProjectApp theApp;