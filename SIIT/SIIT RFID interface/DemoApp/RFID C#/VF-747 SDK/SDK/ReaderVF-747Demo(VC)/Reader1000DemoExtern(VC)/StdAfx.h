// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__57BD4D71_259A_4B9A_8C80_A7349D284048__INCLUDED_)
#define AFX_STDAFX_H__57BD4D71_259A_4B9A_8C80_A7349D284048__INCLUDED_

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

//#include <afxsock.h>		// MFC socket extensions

//#include "./Reader1000API.h"
//#pragma comment(lib, "Reader1000DLL.lib")//��̬���ӿ�

//#pragma comment(lib, "./Lib626/Reader626StaticLib.lib")//��̬���ӿ�


#include "./Lib626/Reader626API.h"
//#pragma comment(lib, "./Lib626/Reader626StaticLib.lib")//��̬���ӿ�
#pragma comment(lib, "ReaderDynamicLib.lib")//��̬���ӿ�

//**************************************************************************/
//������485���,��ǰ���������� add by mqs 20130711  �ϳ�һ��DEMO
//RS485��Э��
//����RS485���������ʱ����Ҫ��������RS485�ڵ�ͨ�����ʡ�RS485��������ݵĸ�ʽ��:
//BODY	CHECK
//STX	DATA	ETX	BCC
//02	���߱��(2���ֽ�ASCII��)	ID�Ż��Զ�����(8�ֽ�ASCII��)	03	У����/
//˵��:
//���ݿ�ʼ��־STX = 02H �����ݽ�����־ETX = 03H��
//DATAΪ���߱��(2Byte)+��ǩID��(8Bytes)������Ϊ10���ֽ�ASCII�롣��ʮ����������ת��ΪASCII��ʾ�ķ�����:
//�����ݰ��Ӹߵ��͵�˳��ÿ4λһ����зָ�ٰ�4λ����������ȡֵ��ASCII���ʾ������4λ����������ȡֵ��Χ��0H��FH�����ת�����ASCII��Ϊ30H��39H��41H��46H������:32λ��ź�����Ϊ6A90F103H��ת��Ϊ8���ֽڵ�ASCII���Ϊ��36H 41H 39H 30H 46H 31H 30H 33H��������1���(ASCII��)Ϊ��30H  31H��������2���(ASCII��)Ϊ��30H 32H����
#define					ENABLE485TXOUTPUT
//**************************************************************************/

//EPC��д16����
#define					EPCREADWRITEHEX


//�Ǳ굥��BPA�����BPA-9-proctol.pdf, �ӿ��б仯���ú����,add by mqs 20130118
//#define					ENABLEBPA9PROCTOL


//�����û��������Ƿ������������ý��棬����ENABLEREADERPARAM ���в������棬�����ޣ��ú����,add by mqs 20130222
#define					ENABLEREADERPARAM

//�ܹ���Ҫ��add by mqs 20130327 Ҫ��1.�ڱ�������ʾ����д����,Ӳ���汾��1000; ����汾��1000; ID�ţ���д��1000,
//#define					ENABLETXVERCHANGE


//Сģ��������ý��棬���� ENABLEREADERMODES ����Сģ��������棬�����ޣ��ú����,add by mqs 20130514
//#define					ENABLEREADERMODES


//������������,���� ENABLErubbish ��������������������棬�����ޣ��ú����,add by mqs 20130614
//#define					ENABLErubbish


//218Ϊ����߶���ǩ�ٶȣ������л����ߣ���һ����������Զ��л����ߣ����� ENABLE218TXNOAntenna  �����ޣ��ú����,add by mqs 20130910
//#define					ENABLE218TXNOAntenna

//#####################################################################
//add by martrin 20140110���ӻ�Ϊ˹������ǰ��Reader2600,���ڻ����Ŀڵ�
//R2000�ģ�����Ҫ����R2000Э��, ������R2000, ��������ǰ��
//#define					ENABLE_R2000_protocol

//#####################################################################

#define					WM_MYMESSAGE				(WM_USER+1)
#define					WM_MYDATAMSG				(WM_USER+2)
#define					WM_LISTUSERDATA				(WM_USER+3)	//������ҳ��
#define					WM_CONNECTDATACUSTOM		(WM_USER+4)	//���Ӷ�д��
#define					WM_READERPARMDATAMSG		(WM_USER+5)	//����ҳ
#define					WM_EPC6CTRANDATAMSG			(WM_USER+6)	//6C
#define					WM_USERTIMERDATATRan		(WM_USER+7)	//6B
#define					WM_OUTPUTTESTDATAMSG		(WM_USER+8)	//(WM_USER+300)//output test
#define					WM_DLGBPA9DATAMSG			(WM_USER+9)	//BPA9�Ĵ���
#define					WM_DLGSMALLMODEDATAMSG		(WM_USER+10)	//Сģ��Ĵ���


//RS485��Delayʱ��(ms)
#define					ReadRS485SleepTime				(60)//(300)

extern CString			g_szCurPath;		//��ǰ��ִ���ļ���·����
//////////////////////////////////////////////////////////////////////////
extern HWND				gMainHwnd;			//������ҳ��
extern HWND				gConnectReaderHwnd;	//���ӵĴ���ľ��
extern HWND				gReaderParamHwnd;	//��д������������
extern HWND				gReaderDParaHwnd;	//218����������
extern HWND				gEcpISO6C;			//6c����ľ��
extern HWND				gEcpISO6B;			//6B����ľ��
extern HWND				gOutputHwnd;		//������ԵĴ���ľ��
extern HWND				gDlgBpa9;			//Bpa9����ľ��



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__57BD4D71_259A_4B9A_8C80_A7349D284048__INCLUDED_)
