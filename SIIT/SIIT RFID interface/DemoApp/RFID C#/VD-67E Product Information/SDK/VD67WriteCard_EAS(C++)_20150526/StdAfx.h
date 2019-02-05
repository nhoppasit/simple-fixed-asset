// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E711E176_C22D_432B_A416_BD6064541359__INCLUDED_)
#define AFX_STDAFX_H__E711E176_C22D_432B_A416_BD6064541359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT




#include "./INC/VHDllLib.h"
#include "./INC/VHHandsetAPI.h"
#pragma comment(lib, "./INC/VHLib.lib")


//EPC��д16����
#define					EPCREADWRITEHEX

//�û��Զ��屨������ add by martrin 20140916
#define					ENABLECUSTOMBUZZER

//���Ӳ���(������ʱ�ᵯ�����߲���������) add by martrin 20150427
//#define					ENABLETESTT

////////////////////�ۺϲ�ѯ���涨ʱ��/////////////////////////////////////
//���嶨ʱ����ID
//ʱ��
#define					TIME_IDENTIFIER_LISTDISP		(200)			//ʱ��ID��
#define					INTERVALTIME_LISTDISP			(300)			//�೤ʱ��ִ��һ��
//////////////////////////////////////////////////////////////////////////


//�Ƿ�����������ʾ�� ENABLE_PROGRESSDISPTIP ������н�����ʾ����,����û��
//#define					ENABLE_PROGRESSDISPTIP


#define					WM_LISTUSERDATA				(WM_USER+3)		//������ҳ��
#define					WM_CONNECTDATACUSTOM		(WM_USER+4)		//���Ӷ�д��
#define					WM_READERPARMDATAMSG		(WM_USER+5)		//����ҳ
#define					WM_6CWRITEDATAMSG			(WM_USER+6)		//6C��дҳ��
#define					WM_6CREADDATAMSG			(WM_USER+7)		//6C�Ķ�ҳ��
#define					WM_6BWRITEDATAMSG			(WM_USER+8)		//6B��дҳ��
#define					WM_6BREADDATAMSG			(WM_USER+9)		//6B�Ķ�ҳ��
#define					WM_EPC6CTRANDATAMSG			(WM_USER+18)		//6C



extern CString			g_szCurPath;		//��ǰ��ִ���ļ���·����
//////////////////////////////////////////////////////////////////////////
extern HWND				gMainHwnd;			//������ҳ��
extern HWND				gConnectReaderHwnd;	//���ӽ���ҳ��

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E711E176_C22D_432B_A416_BD6064541359__INCLUDED_)
