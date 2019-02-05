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
	int iLanguage;	//��������,0---English,1---Chinese
	int iantennaIndex;	//ѡ�ĸ�����,0-һ������,1-�ĸ�����
	
	CString strTempPath;
	CString strConfigPath;	//���ò���ini��·��
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
extern BYTE				gFre;	//ȡ�ĸ����ҵ�Ƶ��
extern ReaderAutoParam	*gAutoParam;
extern LPVOID			g_lpBuf;
extern BYTE				gReaderID[33];			//��д��ID
extern int Wq_WriteAppLogFile(char* FileName, int Line, char* fmt, ...);
extern CProgress		*pgDlgPress;//�����ָ��

extern int iPlatform;	//0---626, 1---218
extern BYTE bModuleVer[10];
extern BYTE FreT[6];
//////////////////////////////////////////////////////////////////////////
//218��ض���
extern int		nHostPort;
extern char nHostNetAddr[33];
extern int nReaderMyPort;
extern char nReaderNetAddr[33];
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//��;:		���ļ���������������BUF��
//������:	ReadBufFile
//����:		���ļ���BUF
//�������:	bufָ�ַ�ָ��,FilePathNameָȫ·����
//�������:	���������ݴ���buf��FilePathNameLenָ�����ĳ���
//����ֵ:	DWORD�͵���ֵ���س���
//��ע:		���bufΪNULL����ֻ���س���
//////////////////////////////////////////////////////////////////////////
extern DWORD ReadBufFile(char *buf, CString FilePathName, DWORD& FilePathNameLen);



//////////////////////////////////////////////////////////////////////////
//��;:		��buf�е�Count�ĳ���д�뵽�ļ���
//������:	WriteBufFile
//����:		д���ݵ��ļ���
//�������:	bufָ�ַ�ָ��,CountҪд�ĳ���,FilePathNameָȫ·����,FilePathNameLen�ݲ���
//�������:	��
//����ֵ:	DWORD�͵���ֵд����ֽ���
//��ע:		ע��д��ʧ���򷵻�0
//ע��: modeNoTruncate�������ǲ����ļ��ĳ��Ƚض�Ϊ0,�������modeNoTruncate
//////////////////////////////////////////////////////////////////////////
extern DWORD WriteBufFile(char* buf, DWORD Count, CString FilePathName, DWORD FilePathNameLen);



//////////////////////////////////////////////////////////////////////////
//��;:		��buf�е�Count�ĳ���д�뵽�ļ���
//������:	WriteBufFileEx
//����:		д���ݵ��ļ���
//�������:	bufָ�ַ�ָ��,CountҪд�ĳ���,FilePathNameָȫ·����,FilePathNameLen�ݲ���
//�������:	��
//����ֵ:	DWORD�͵���ֵд����ֽ���
//��ע:		ע��д��ʧ���򷵻�0
//ע��: modeReadWrite|CFile::modeCreateֱ������ԭ�ļ�
//////////////////////////////////////////////////////////////////////////
extern DWORD WriteBufFileEx(char* buf, DWORD Count, CString FilePathName, DWORD FilePathNameLen);



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERDEMO_H__E1866EB2_17C0_4EF4_9CE6_8C7CC526901E__INCLUDED_)
