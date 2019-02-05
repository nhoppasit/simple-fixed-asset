// ReaderDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "ReaderDemoDlg.h"



#include <string>
#include <afxmt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include   <imagehlp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
CString			g_szCurPath;		//��ǰ��ִ���ļ���·����
CString			g_szExeFile;		//��ǰ��ִ���ļ���·����
HGLOBAL			g_hGlobal		=	NULL;
LPVOID			g_lpBuf			=	NULL;
CProgress		*pgDlgPress		=	NULL;//�����ָ��

#define HM_WRITE_LOG
#define  LOGSIZE					(4*1024*1024)
static char appLogFileName[MAX_PATH]	=	{0};
static CRITICAL_SECTION lpCriticalSection	=	{0};
/////////////////////////////////////////////////////////////////////////////
// CReaderDemoApp

BEGIN_MESSAGE_MAP(CReaderDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CReaderDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderDemoApp construction

CReaderDemoApp::CReaderDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	iPlatform	=	0;	//0---626, 1---218

	char *data;
	char chUsername[16] = {0};			//�û���
	char chPassword[16] = {0};			//����
	char chTrycheckceode[8]	=	{0};	//��֤��
	
	
	data = ("username=root&password=123456");
	
	printf("Content type: text/html\n\n");
	
	sscanf(data, "username=%[^&]&password=%s",chUsername, chPassword);

	iPlatform = 0;

}

CReaderDemoApp::~CReaderDemoApp()
{
	if ( g_hGlobal != NULL )
	{
		FreeResource(g_hGlobal);
		g_hGlobal	=	NULL;
	}
	
	{
		DeleteCriticalSection(&lpCriticalSection);
	}
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CReaderDemoApp object

CReaderDemoApp theApp;

BOOL ifTXMode,ifAddress;
int RS485Address	=	1;
//int Address;
SOCKET m_hSocket	=	NULL;
HANDLE m_hScanner	=	NULL;
WORD m_HardVersion	=	0;
WORD m_SoftVersion	=	0;
BOOL ifConnectReader=	0;//��д���Ƿ����ӣ�1---����,0---û������
BOOL NewConnect		=	0;
int ConnectMode		=	-1;//���ӵ�ģʽ,0---���ڣ�1---RS232��2---RS485

ReaderBasicParam	*gBasicParam	=	NULL;
BYTE				gFre			=	0;	//ȡ�ĸ����ҵ�Ƶ��
ReaderAutoParam		*gAutoParam		=	NULL;
BYTE				gReaderID[33]	=	{0};			//��д��ID

int iPlatform	=	0;	//0---626, 1---218
//////////////////////////////////////////////////////////////////////////
//218��ض���
int		nHostPort	=	0;
char nHostNetAddr[33]={0};
int nReaderMyPort;
char nReaderNetAddr[33]={0};
BYTE bModuleVer[10]	=	{0};
BYTE FreT[6]=	{0};
//////////////////////////////////////////////////////////////////////////
//��;:		��buffer�ж�ȡָ�����ַ���
//������:	Wq_GetPrivateProfileString
//����:		��API��GetPrivateProfileString����
//�������:	lpstrSection ָsection��:[Setting]
//			lpstrEntry ָ��Ŀ���磺Language=,���ں�ǰ���
//			lpstrDefault ָȡ������Ĭ��ֵ���ַ���
//			strValue ָ���ɹ�����ַ���
//			nSize	ָ�����Ĵ�С��
//			m_strBuf ָ����������BUF���ַ���
//�������:	��
//����ֵ:	���� TRUE Ϊ�ɹ������� FALSE Ϊʧ��
//��ע:		��ȡָ���ļ�ֵ(ע��Ŀǰֻ�����ASCII��ʽ���ı��ļ�)
//////////////////////////////////////////////////////////////////////////
BOOL   Wq_GetPrivateProfileString(LPCTSTR lpstrSection,  LPCTSTR   lpstrEntry,   LPCTSTR lpstrDefault,LPTSTR   strValue,DWORD nSize,LPCTSTR  m_strBuf)   
{
	int ii = 0;
	CString   strSection, strEntry, strDefault;
	strSection = lpstrSection;
	strEntry = lpstrEntry;
	strDefault = lpstrDefault;
	int iLen = strDefault.GetLength();
	////���ж�ǰ���������Ƿ�Ϊ��   
	if(strSection   ==   _T("")   ||   strEntry   ==   _T(""))   
	{   
		for(ii = 0 ; ii < iLen ; ii++ )
			strValue[ii] = strDefault.GetAt(ii);
		strValue[ii] = 0x00;
		return   FALSE;       ///���ɹ��򷵻�Ĭ��ֵ   
	}   
	
	CString     strCombine;
	
	TRY   
	{
		
		strCombine = m_strBuf;
		
		//////��ʼ���ң���section��entry�Ƿ��Ѿ�����   
		int   iIndex1,   iIndex2,   iIndex3,   iIndexT;           
		iIndex1   =   strCombine.Find(L"["   +   strSection   +   L"]\r\n");   
		if(iIndex1   ==   -1)     ///û�ҵ�   
		{   
			
			for(ii = 0 ; ii < iLen ; ii++ )
				strValue[ii] = strDefault.GetAt(ii);
			strValue[ii] = 0x00;
			
			return   FALSE;   
		}   
		iIndexT   =   iIndex1   +   4   +   strSection.GetLength();   
		iIndex2   =   strCombine.Find(strEntry   +   L"=",   iIndexT);   
		if(iIndex2   ==   -1)     ///û�ҵ�   
		{   
			
			for(ii = 0 ; ii < iLen ; ii++ )
				strValue[ii] = strDefault.GetAt(ii);
			strValue[ii] = 0x00;
			return   FALSE;   
		}   
		else   
		{   
			iIndex3   =   strCombine.Find(_T("\r\n"),   iIndex2   +   1);   
			
			if(iIndex3   ==   -1)   
			{   
				
				for(ii = 0 ; ii < iLen ; ii++ )
					strValue[ii] = strDefault.GetAt(ii);
				strValue[ii] = 0x00;
				
				return   FALSE;   
			}   
			
			iIndexT   =   iIndex2   +   1   +   strEntry.GetLength();   
			
			
			CString cstrValue   =   strCombine.Mid(iIndexT,   iIndex3   -   iIndexT);  
			
			iLen = cstrValue.GetLength();
			
			for(ii = 0 ; ii < iLen ; ii++ )
				strValue[ii] = cstrValue.GetAt(ii);
			strValue[ii] = 0x00;
			//cstrValue.ReleaseBuffer();
			
			return     TRUE;   
		}   
	}   
	CATCH(CFileException,   e)   
	{   
	}   
	END_CATCH             ///�������Ժ�   
		
	return   FALSE;   
}


  
//////////////////////////////////////////////////////////////////////////
//��;:		��buffer��д��ָ�����ַ���
//������:	Wq_WritePrivateProfileString
//����:		��API��WritePrivateProfileString����
//�������:	lpstrSection ָsection��:[Setting]
//			lpstrEntry ָ��Ŀ���磺Language=,���ں�ǰ���
//			lpstrValue ָҪд��ĵ��ַ���
//			m_strBuf ָ����������BUF���ַ���
//�������:	��
//����ֵ:	���� TRUE Ϊ�ɹ������� FALSE Ϊʧ��
//��ע:		��ָ����BUF��Ӧ��INI��ĳһ����,Ϊ�ض��ļ�д��һ��CStringֵ
//////////////////////////////////////////////////////////////////////////
BOOL     Wq_WritePrivateProfileString(LPCTSTR lpstrSection,   LPCTSTR lpstrEntry,   LPCTSTR lpstrValue, LPTSTR  m_strBuf)   
{   
	
	CString strSection, strEntry, strValue;
	strSection = lpstrSection;
	strEntry = lpstrEntry;
	strValue = lpstrValue;
	////���ж����в����Ƿ�Ϊ��   
	if(lpstrSection   ==   _T("")   ||   lpstrEntry   ==   _T("")   ||   lpstrValue   ==   _T(""))
	{   
		return   FALSE;   
	}   

	CString     strCombine;   
	UINT   nLength	=	0;

	TRY   
	{   
		
		///�ѻ�������ַ����CString����Ϊ��ʹ��CString�����ĺ�����   
		///һ��Ini�ļ��Ƚ�С�����Դӻ�������CString�ĸ��ƹ�����ʱ�̡ܶ��ķ���ԴҲ����   
		 

		///�ȴ�����Ļ�����   
		//strCombine.GetBuffer(MAX_PATH);
		strCombine = m_strBuf;
		
		//////��ʼ���ң���section��entry�Ƿ��Ѿ�����   
		//   iIndex1��¼strSectionλ��   
		//   iIndex2��¼strEntryλ��   
		//   iIndex3��¼strValue�Ľ���λ��   
		//   iIndexT��¼�����λ��   

		int   iIndex1,   iIndex2,   iIndex3,   iIndexT;           
		iIndex1   =   strCombine.Find(L"["   +   strSection   +   L"]\r\n");   

		if(iIndex1   ==   -1)     ///û�ҵ�   
		{   
			strCombine   +=   L"["   +   strSection   +   L"]"   +   L"\r\n"     
				+   strEntry   +   L"="   +   strValue   +   L"\r\n";   

			///�õ�strCombine�����Ļ������׵�ַ   
			LPTSTR     lpCombine   =   strCombine.GetBuffer(0);
			
			return   FALSE;   
		}   

		iIndexT   =   iIndex1   +   4   +   strSection.GetLength();
		iIndex2   =   strCombine.Find(strEntry   +   L"=",   iIndexT);

		if(iIndex2   ==   -1)     ///û�ҵ�   
		{   
			strCombine.Insert(iIndexT,   strEntry   +   L"="   +   strValue   +   L"\r\n");   

			///�õ�strCombine�����Ļ������׵�ַ   
			LPTSTR     lpCombine   =   strCombine.GetBuffer(0);   
			
			return   FALSE;   
		}   
		else   
		{   
			iIndex3   =   strCombine.Find(_T("\r\n"),   iIndex2   +   1);   

			if(iIndex3   ==   -1)   
			{   
								
				return   FALSE;   
			}   

			//   �滻�����еļ�ֵ   
			iIndexT   =   iIndex2   +   1   +   strEntry.GetLength();   
			strCombine.Delete(iIndexT,   iIndex3   -   iIndexT);   
			strCombine.Insert(iIndexT,   strValue);   

			///�õ�strCombine�����Ļ������׵�ַ   
			char *cBuf = new char[strCombine.GetLength()*2 + 1];
			memset(cBuf,0x00,strCombine.GetLength()*2 + 1);
			//WideCharToMultiByte (CP_OEMCP,0,strCombine.GetBuffer(MAX_PATH),strCombine.GetLength(),cBuf,strCombine.GetLength()*2 + 1,NULL,FALSE);
			//m_IniFile.SetLength(0);       
			
			strcpy(m_strBuf, strCombine);
			strCombine.ReleaseBuffer();
			
			
			delete[] cBuf;
			return   TRUE;   
		}   

	}   ///end   TRY   
	CATCH(CFileException,   e)   
	{   
		/* ////���ڵ��ԣ��õ�������Ϣ   
		CString   strT;   
		switch(e->m_cause)   
		{   
		case   CFileException::generic:   
		case   CFileException::badPath:   
		case   CFileException::accessDenied:   
		case   CFileException::hardIO:   
		case   CFileException::diskFull:   
		...............   
		default:   
		}   
	*/
	}   
	END_CATCH           ///�������Ժ�   

	return   FALSE;   
}  



/////////////////////////////////////////////////////////////////////////////
// CReaderDemoApp initialization

BOOL CReaderDemoApp::InitInstance()
{

	//if (!AfxSocketInit())
	//{
	//	AfxMessageBox("100");
	//	return FALSE;
	//}
	InitializeCriticalSection(&lpCriticalSection);

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//////////////////////////////////////////////////////////////////////////
	//��ȡ��ǰ·��
	CString szCurPath("");
	GetModuleFileName(NULL,szCurPath.GetBuffer(MAX_PATH),MAX_PATH);	
	szCurPath.ReleaseBuffer();
	g_szCurPath = szCurPath.Left(szCurPath.ReverseFind('\\') + 1);
	g_szExeFile	= szCurPath;


#ifdef HM_WRITE_LOG
	strcpy(appLogFileName, g_szCurPath);
	strcat(appLogFileName, "log\\");
	
	SYSTEMTIME sysTime;
	
	GetLocalTime(&sysTime);
	sprintf(appLogFileName + strlen(appLogFileName), "R%04d%02d%02d.log", sysTime.wYear,sysTime.wMonth, sysTime.wDay);
	TRACE("log232path:%s\n",appLogFileName);
	//Wq_WriteAppLogFile(__FILE__, __LINE__, "%s\r\n", appLogFileName);
#endif

	strConfigPath	=	g_szCurPath;	//���ò���ini��·��
	strConfigPath	+=	_T("Reader1100_1400.ini");

	gBasicParam	=	new ReaderBasicParam;
	if ( NULL == gBasicParam )
	{
		return FALSE;
	}
	else
	{
// 		gBasicParam->BaudRate		=	0;			//(1)���ڵ�ͨ�����ʣ�ȡֵ��00H~08H����������ͬ"�趨������"���
// 		gBasicParam->Power			=	20;			//(2)���书��ֵ��ȡֵ��20~30dBm��
// 		gBasicParam->Min_Frequence	=	1;		//(3)����΢���ź�Ƶ�ʵ���ʼ�㣬ȡֵ�� 1~63��
// 		gBasicParam->Max_Frequence	=	63;		//(4)����΢���ź�Ƶ�ʵ���ֹ�㣬ȡֵ�� 1~63��
// 		gBasicParam->Reserve5		=	0;			//(5)����
// 		gBasicParam->WorkMode		=	0;			//(6)��д��������ʽ��0-������ʽ��1-���ʽ
// 		gBasicParam->ReaderAddress	=	1;		//(7)RS485��ַ:0--255
// 		gBasicParam->NumofCard		=	5;			//(8)��������Ŀ��
// 		gBasicParam->TagType		=	2;			//(9)��ǩ���ࣺ01H��ISO18000-6B��02H��EPCC1��04H��EPCC1G2��08H��EM4442��
// 		gBasicParam->ReadDuration	=	0;		//(10)��������ʱ�䣺��Ƶ�������ʱ�䣬ֻ���EM��ǩ��Ч��0��10ms��1��20ms��2��30ms��3��40ms��
// 		gBasicParam->ReadTimes		=	2;			//(11)��������M���յ���λ�����������д��ִ��M�δ����
// 		gBasicParam->EnableBuzzer	=	1;		//(12)1:ʹ�ܷ�����0:��ʹ�ܷ�����
// 		gBasicParam->IP1;			    //(13)��д��IP��ַ
// 		gBasicParam->IP2;			    //(14)
// 		gBasicParam->IP3;			    //(15)
// 		gBasicParam->IP4;			    //(16)
// 		gBasicParam->Port1;				//(17)��д���˿ڸ�λ
// 		gBasicParam->Port2;				//(18)
// 		gBasicParam->Mask1;				//(19)��д������1
// 		gBasicParam->Mask2;				//(20)��д������2
// 		gBasicParam->Mask3;				//(21)��д������3
// 		gBasicParam->Mask4;				//(22)��д������4
// 		gBasicParam->Gateway1;			//(23)��д����ַ����
// 		gBasicParam->Gateway2;			//(24)
// 		gBasicParam->Gateway3;			//(25)
// 		gBasicParam->Gateway4;			//(26)
// 		gBasicParam->MAC1;			    //(27)��д��MAC��ַ
// 		gBasicParam->MAC2;			    //(28)
// 		gBasicParam->MAC3;			    //(29)
// 		gBasicParam->MAC4;			    //(30)
// 		gBasicParam->MAC5;			    //(31)
// 		gBasicParam->MAC6;			    //(32)
	}
	gAutoParam	=	new ReaderAutoParam;
	if ( NULL == gAutoParam )
	{
		delete gBasicParam;
		return FALSE;
	}

	memset(gAutoParam, 0x00, sizeof(ReaderAutoParam));
	//iantennaIndex	=	0;	//ѡ�ĸ�����,0-һ������,1-�ĸ�����
	iantennaIndex	=	GetPrivateProfileInt(_T("SETTING"), _T("Antenna"), 0,  theApp.strConfigPath);
	//iPlatform	=	0;	//0---626, 1---218
	iPlatform		=	GetPrivateProfileInt(_T("SETTING"), _T("Platform"), 0,  theApp.strConfigPath);
	//////////////////////////////////////////////////////////////////////////GetTempPath(MAX_PATH, strTempPath.GetBuffer(MAX_PATH));
	GetTempPath(MAX_PATH, strTempPath.GetBuffer(MAX_PATH));
	strTempPath.ReleaseBuffer();
	strIniDir	=	strTempPath;
	szCurPath	=	strTempPath;
	
	//////////////////////////////////////////////////////////////////////////
	iLanguage	=	0;	//0---English,1---Chinese
	LANGID   type   =   GetSystemDefaultLangID();   
	switch(type)   
	{   
	case   0x0404:   
		//     ����; 
		
		
		break;   
	case   0x0409:   
	case   0x0809:   
		//   Ӣ��; 
		iLanguage	=	0;
		break;   
	case   0x0804:   
		//     ����;
		iLanguage	=	1;
		break; 
	case  0x41F:
		//������, "Turkey";
		
		break; 
	case 0x43E:
		//��������, "Malaysia";
		break;
		
	case	0x81A:
		//����ά����(������)=$0000081A ,"Serbian";
		break;
		
	default:
		iLanguage	=	0;
	}
	MakeResource(iLanguage, szCurPath, &g_lpBuf);
	//////////////////////////////////////////////////////////////////////////

	
	

	CReaderDemoDlg dlg;
	//CProgress dlg;//������
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CReaderDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(ConnectMode)
	{
	case 0:
		Net_DisconnectScanner();
		break;
	case 1:
		DisconnectScanner(m_hScanner);
		break;
	case 2:
		DisconnectScanner(m_hScanner);
		break;
	}

	if ( gBasicParam != NULL )
	{
		delete gBasicParam;
		gBasicParam	=	NULL;
	}

	if ( NULL != gAutoParam )
	{
		delete gAutoParam;
		gAutoParam	=	NULL;
	}
	if ( NULL != pgDlgPress )
	{
		
		pgDlgPress->DestroyWindow();
		delete pgDlgPress;
		pgDlgPress	=	NULL;
		
	}

	m_hScanner	=	NULL;
	DeleteAppHwnd();
	return CWinApp::ExitInstance();
}

////////////////////////////////////////////////////////////////////////////
/*********************************************************************
 * ��������:g_LoadString
 * ˵��:	���ݱ�ʶ szID��ѡ���������ļ��м����ַ���
 * ����:	
*********************************************************************/
CString CReaderDemoApp::g_LoadString(CString szID)
{
	CString szValue;
	DWORD dwSize = 1000;
	//GetPrivateProfileString("String",szID,"NotFound",
	//	szValue.GetBuffer(dwSize),dwSize,strTempPath);
	//szValue.ReleaseBuffer();

	Wq_GetPrivateProfileString("String",szID,"NotFound",
		szValue.GetBuffer(dwSize),dwSize,(LPCTSTR)g_lpBuf);
	szValue.ReleaseBuffer();


	szValue.Replace("\\n","\n");	//�滻�ػ��з���

	return szValue;
}



/*********************************************************************
 * ��������:g_SaveString
 * ˵��:	���ݱ�ʶ szID��ѡ���������ļ��м����ַ���, strValue ָҪд����ִ�
 * ����:	
*********************************************************************/
void CReaderDemoApp::g_SaveString(CString szID, CString strValue)
{
	DWORD dwSize = 1000;
	//GetPrivateProfileString("String",szID,"NotFound",
	//	szValue.GetBuffer(dwSize),dwSize,strTempPath);
	//szValue.ReleaseBuffer();

	Wq_WritePrivateProfileString("String",szID, strValue, (LPTSTR)g_lpBuf);


	return;
}



/*********************************************************************
 * ��������:CReaderDemoApp::MakeResource
 * ˵��:	���δ�ҵ��������Դ�ļ�(�������ļ��������ļ���)���ӳ����в���
 * chBuf ָ�������buf��
 * ����:  
*********************************************************************/
BOOL CReaderDemoApp::MakeResource(int nID, CString szPathName, LPVOID *chBuf)
{
	//0---English,1---Chinese
	int IDD	=	IDR_ENGLISH;
	if ( 0 == nID )
	{
		IDD	=	IDR_ENGLISH;
	}
	else if ( 1 == nID )
	{
		IDD	=	IDR_CHINESE;
	}

	HRSRC hSrc = FindResource(NULL,MAKEINTRESOURCE(IDD),_T("LANG_DATA"));
	if(hSrc == NULL)	return FALSE;

	FreeResource(g_hGlobal);
	g_hGlobal	= LoadResource(NULL,hSrc);
	
	if(g_hGlobal == NULL)	return FALSE;
	
	LPVOID lp = LockResource(g_hGlobal);
	DWORD dwSize = SizeofResource(NULL,hSrc);
	//*((char*)lp + dwSize)	=	0x00;

	*chBuf	=	lp;


	//////////////////////////////////////////////////////////////////////////
	//�Ҳ����õ�
	//CString strTemp;
	//HANDLE hUpdate;

	//strTemp	=	g_LoadString("IDWQA_B0003");
	//strTemp	=	"����";
	//g_SaveString("IDWQA_B0003", strTemp);
	
	//hUpdate = BeginUpdateResource(g_szExeFile, FALSE);
	//BOOL ret = UpdateResource(hUpdate, _T("LANG_DATA"), MAKEINTRESOURCE(nID), 0, (LPVOID)lp, dwSize);

	//EndUpdateResource(hUpdate, FALSE);
	//if (!ret)
    //{
	//	
    //}
	//////////////////////////////////////////////////////////////////////////
	
	

	//CFile file;
	//if(file.Open(szPathName,CFile::modeCreate|CFile::modeWrite))
	//{
	//	file.Write(lp,dwSize);
	//	file.Close();
	//}
	
	return TRUE;
}



int Wq_WriteAppLogFile(char* FileName, int Line, char* fmt, ...)
{
#ifdef HM_WRITE_LOG
	int		fd	=	1;
    char	buffer[5120];
	char	strTemp[600];
    va_list ap;
    struct stat sbuf;
	
	char	chCurr[20];
    char	buf[5120];
	//CCriticalSection WtLogCriticalSection;
	
	SYSTEMTIME sysTime;
	
	DWORD	dwChLen	=	0;
	
	
	
	ZeroMemory(&sbuf, sizeof(sbuf));
	
	memset(buf,0x00,sizeof(buf));
	memset(buffer,0x00,sizeof(buffer));
    memset(strTemp,0x00,sizeof(strTemp));
	
	//////////////////////////////////////////////////////////////////////////
	//WtLogCriticalSection.Lock();
	if ( lpCriticalSection.LockSemaphore != NULL )
	{
		EnterCriticalSection(&lpCriticalSection);
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
	memcpy(buf,buffer,sizeof(buffer));
    va_end(ap);
    
	
    stat(appLogFileName, &sbuf);
	
	
    if(sbuf.st_size>=LOGSIZE)
	{
		
		fd = open(appLogFileName, O_CREAT | O_RDWR | O_RDWR, 0600);
	}
	else
	{
		fd = open(appLogFileName, O_CREAT | O_RDWR | O_RDWR, 0600);
	}
    
    if (fd < 0)
	{
		//WtLogCriticalSection.Unlock();
		if ( lpCriticalSection.LockSemaphore != NULL )
		{
			LeaveCriticalSection(&lpCriticalSection);
		}
		
		return -1;
	}
	
    lseek(fd,0,SEEK_END);
	
	
	if ( 1 )
	{
		GetLocalTime(&sysTime);
		memset(chCurr, 0x00, sizeof(chCurr));
		//sprintf(chCurr, "%4d-%02d-%02d %02d:%02d:%02d:%03d",sysTime.wYear,
		//	sysTime.wMonth, sysTime.wDay, sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
		
		sprintf(chCurr, "%02d:%02d:%02d:%03d",sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
		
		//sprintf(strTemp,"%s  Line:%-6d FileName:%s ", chCurr,Line,FileName);
		sprintf(strTemp,"%s ", chCurr);
		
		dwChLen	=	strlen(strTemp);
		
		
		write(fd, strTemp, dwChLen);
	}
	
	dwChLen	=	strlen(buf);
	
	
    write(fd, buf, dwChLen);
    close(fd);
	
	//WtLogCriticalSection.Unlock();
	if ( lpCriticalSection.LockSemaphore != NULL )
	{
		LeaveCriticalSection(&lpCriticalSection);
	}
#endif	
    return 0;
}


//////////////////////////////////////////////////////////////////////////
//��;:		���ļ���������������BUF��
//������:	ReadBufFile
//����:		���ļ���BUF
//�������:	bufָ�ַ�ָ��,FilePathNameָȫ·����
//�������:	���������ݴ���buf��FilePathNameLenָ�����ĳ���
//����ֵ:	DWORD�͵���ֵ���س���
//��ע:		���bufΪNULL����ֻ���س���
//////////////////////////////////////////////////////////////////////////
DWORD ReadBufFile(char *buf, CString FilePathName, DWORD& FilePathNameLen)
{
	CFile file;
	DWORD Count=0;
	if( !file.Open (FilePathName,CFile::modeRead) )
	{
		//AfxMessageBox("Can't Open File!(Read)");
		return 0;
	}
	Count=(DWORD)file.GetLength ();
	FilePathNameLen=Count;
	if ( NULL != buf )
	{
		file.Read(buf,Count);
		
	}
	file.Close();
	return Count;
}


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
DWORD WriteBufFile(char* buf, DWORD Count, CString FilePathName, DWORD FilePathNameLen)
{
	CFile file;
	CString strFilePath=FilePathName;
	if( !file.Open (strFilePath,CFile::modeNoTruncate|CFile::modeReadWrite|CFile::modeCreate) )
	{
		//AfxMessageBox("Can't Open File!(Write)");
		file.Close();
		return 0;
	}
	file.SeekToEnd();
	
	file.Write(buf,Count);
	file.Close();
	return Count;
}



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
DWORD WriteBufFileEx(char* buf, DWORD Count, CString FilePathName, DWORD FilePathNameLen)
{
	CFile file;
	CString strFilePath=FilePathName;
	if( !file.Open (strFilePath,CFile::modeReadWrite|CFile::modeCreate) )
	{
		//AfxMessageBox("Can't Open File!(Write)");
		file.Close();
		return 0;
	}
	file.SeekToEnd();
	char *buffer = new char[Count+1];
	memset(buffer, 0x00, Count+1);
	memcpy(buffer, buf, Count);
	
	file.Write(buffer,Count);
	file.Close();
	delete[] buffer;
	return Count;
}


