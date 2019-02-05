// WriteCard.h : main header file for the WRITECARD application
//

#if !defined(AFX_WRITECARD_H__BC4FFDCD_0564_4B75_A624_5199D5BAFC0A__INCLUDED_)
#define AFX_WRITECARD_H__BC4FFDCD_0564_4B75_A624_5199D5BAFC0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWriteCardApp:
// See WriteCard.cpp for the implementation of this class
//

class CWriteCardApp : public CWinApp
{
public:
	CWriteCardApp();
	~CWriteCardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteCardApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	int iLanguage;	//��������,0---English,1---Chinese
	
	
	CString g_LoadString(CString szID);
	void g_SaveString(CString szID, CString strValue);
	BOOL MakeResource(int nID, CString szPathName, LPVOID *chBuf);



	//{{AFX_MSG(CWriteCardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
extern CWriteCardApp theApp;

extern int ConnectMode;
extern HANDLE m_hScanner;
extern WORD m_HardVersion,m_SoftVersion;
extern BOOL ifConnectReader;
extern int RS485Address;
extern BOOL NewConnect;

extern LPVOID			g_lpBuf;
extern SimParam Param;

extern ReaderBasicParam	*gBasicParam;
extern BYTE				gFre;	//ȡ�ĸ����ҵ�Ƶ��
extern ReaderAutoParam	*gAutoParam;
extern BYTE				gReaderID[33];			//��д��ID

extern int Wq_WriteAppLogFile(char* FileName, int Line, char* fmt, ...);
//extern Progress		*pgDlgPress;//�����ָ��

//�Ƿ����ҵĵ�����Ϊ"mashui",����Ϊ��,����Ϊ��
extern BOOL			g_ThsFlagMe;
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

#endif // !defined(AFX_WRITECARD_H__BC4FFDCD_0564_4B75_A624_5199D5BAFC0A__INCLUDED_)
