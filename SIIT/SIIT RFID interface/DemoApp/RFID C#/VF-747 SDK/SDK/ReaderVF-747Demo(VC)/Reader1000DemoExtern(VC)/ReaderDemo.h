// ReaderDemo.h : main header file for the READERDEMO application
//

#if !defined(AFX_READERDEMO_H__E1866EB2_17C0_4EF4_9CE6_8C7CC526901E__INCLUDED_)
#define AFX_READERDEMO_H__E1866EB2_17C0_4EF4_9CE6_8C7CC526901E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Progress.h"
/////////////////////////////////////////////////////////////////////////////
// CReaderDemoApp:
// See ReaderDemo.cpp for the implementation of this class
//

class CReaderDemoApp : public CWinApp
{
public:
	CReaderDemoApp();
	~CReaderDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReaderDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	int iLanguage;	//何种语言,0---English,1---Chinese
	int iantennaIndex;	//选哪根天线,0-一根天线,1-四根天线
	
	CString strTempPath;
	CString strConfigPath;	//配置参数ini的路径
	CString strIniDir;
	CString g_LoadString(CString szID);
	void g_SaveString(CString szID, CString strValue);
	BOOL MakeResource(int nID, CString szPathName, LPVOID *chBuf);
	
	//{{AFX_MSG(CReaderDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
extern CReaderDemoApp theApp;

extern SOCKET m_hSocket;
extern HANDLE m_hScanner;
extern WORD m_HardVersion,m_SoftVersion;
extern BOOL ifTXMode,ifAddress;
extern int RS485Address;
extern BOOL ifConnectReader;
extern BOOL NewConnect;
extern int ConnectMode;
extern int _stdcall GetSystemPorts(CString *pNameList, CString *pPortList);

extern ReaderBasicParam	*gBasicParam;
extern BYTE				gFre;	//取哪个国家的频率
extern ReaderAutoParam	*gAutoParam;
extern LPVOID			g_lpBuf;
extern BYTE				gReaderID[33];			//读写器ID
extern int Wq_WriteAppLogFile(char* FileName, int Line, char* fmt, ...);
extern CProgress		*pgDlgPress;//窗体的指针

extern int iPlatform;	//0---626, 1---218
extern BYTE bModuleVer[10];
extern BYTE FreT[6];
//////////////////////////////////////////////////////////////////////////
//218相关定义
extern int		nHostPort;
extern char nHostNetAddr[33];
extern int nReaderMyPort;
extern char nReaderNetAddr[33];
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//用途:		将文件中所有数据载入BUF中
//函数名:	ReadBufFile
//功能:		读文件到BUF
//输入参数:	buf指字符指针,FilePathName指全路径名
//输出参数:	读出的数据存入buf，FilePathNameLen指读出的长度
//返回值:	DWORD型的数值返回长度
//备注:		如果buf为NULL，则只返回长度
//////////////////////////////////////////////////////////////////////////
extern DWORD ReadBufFile(char *buf, CString FilePathName, DWORD& FilePathNameLen);



//////////////////////////////////////////////////////////////////////////
//用途:		将buf中的Count的长度写入到文件中
//函数名:	WriteBufFile
//功能:		写数据到文件中
//输入参数:	buf指字符指针,Count要写的长度,FilePathName指全路径名,FilePathNameLen暂不用
//输出参数:	无
//返回值:	DWORD型的数值写入的字节数
//备注:		注意写回失败则返回0
//注意: modeNoTruncate的作用是不将文件的长度截断为0,如果不加modeNoTruncate
//////////////////////////////////////////////////////////////////////////
extern DWORD WriteBufFile(char* buf, DWORD Count, CString FilePathName, DWORD FilePathNameLen);



//////////////////////////////////////////////////////////////////////////
//用途:		将buf中的Count的长度写入到文件中
//函数名:	WriteBufFileEx
//功能:		写数据到文件中
//输入参数:	buf指字符指针,Count要写的长度,FilePathName指全路径名,FilePathNameLen暂不用
//输出参数:	无
//返回值:	DWORD型的数值写入的字节数
//备注:		注意写回失败则返回0
//注意: modeReadWrite|CFile::modeCreate直接清了原文件
//////////////////////////////////////////////////////////////////////////
extern DWORD WriteBufFileEx(char* buf, DWORD Count, CString FilePathName, DWORD FilePathNameLen);



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERDEMO_H__E1866EB2_17C0_4EF4_9CE6_8C7CC526901E__INCLUDED_)
