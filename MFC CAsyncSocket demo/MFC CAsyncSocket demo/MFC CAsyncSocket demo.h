
// MFC CAsyncSocket demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCCAsyncSocketdemoApp:
// �йش����ʵ�֣������ MFC CAsyncSocket demo.cpp
//

class CMFCCAsyncSocketdemoApp : public CWinApp
{
public:
	CMFCCAsyncSocketdemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCCAsyncSocketdemoApp theApp;