
// UDiskIconChanger.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDiskIconChangerApp:
// �йش����ʵ�֣������ UDiskIconChanger.cpp
//

class CUDiskIconChangerApp : public CWinApp
{
public:
	CUDiskIconChangerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDiskIconChangerApp theApp;