// WriteCard.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WriteCard.h"
#include "WriteCardDlg.h"

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

 
  
enum {MAXSIZE = 256 + 2, RADIX = 16};   
  
/* ans = first + second */ 
//ʵ������16�����ַ����Ĵ������,�磺
// first:ABCDEF123456ABCDEF123456ABCDEF123456
// second:ABCDEF123456ABCDEF123456ABCDEF123456
//������� ans:1579BDE2468AD579BDE2468AD579BDE2468AC
char *big_num_add(char *ans, char *first, char *second)   
{   
    int i = 0;      /* ans ������    */  
    int carry = 0;  /* ��λ, ��ʼΪ0 */  

	int ixA = 0;
	int ixB = 0;
	int iSu = strlen(second);

	char firstA[MAXSIZE] = {0};
	char secondB[MAXSIZE] = {0};
	int iLen = strlen(first);
	if ( iLen > iSu )
	{
		for (i = 0; i < iLen - iSu; i++)
		{
			secondB[i] = '0';
		}
		
	}
	else
	{
		for (i = 0; i < iSu - iLen; i++)
		{
			firstA[i] = '0';
		}
	}
	
	strcat(firstA, first);
	strcat(secondB, second);

    i = 0;
    char *strA = strrev(firstA);   
    char *strB = strrev(secondB);   
    do  
    {   
		if( (*strA >= '0') && (*strA <= '9') )
			ixA = *strA - '0';
		else if( (*strA >= 'a') && (*strA <= 'f') )
			ixA = *strA - 'a' + 10;
		else if( (*strA >= 'A') && (*strA <= 'F') )
			ixA = *strA - 'A' + 10;
		
		else {
			ixA = 0;
		}

		if( (*strB >= '0') && (*strB <= '9') )
			ixB = *strB - '0';
		else if( (*strB >= 'a') && (*strB <= 'f') )
			ixB = *strB - 'a' + 10;
		else if( (*strB >= 'A') && (*strB <= 'F') )
			ixB = *strB - 'A' + 10;
		
		else {
			ixB = 0;
		}

        //carry += (*strA &0xf) + (*strB & 0xf); 
		iSu = ixA + ixB + carry;
		if( iSu > 0x0F)
		{
			//carry	= 'A' + carry - 0x0a;
			carry = iSu / RADIX;
			iSu = iSu % RADIX;
		}
		else	
		{
			//carry	+= '0';
			carry = 0;
		}

		if( iSu > 0x09)
		{
			iSu	= 'A' + iSu - 0x0a;
		}
		else	
		{
			iSu	+= '0';
		}

		ans[i++] = iSu;
        //ans[i++] = carry % RADIX + '0';   
        //carry /= RADIX;   
    } while (*(++strA) && *(++strB));  /*ָ�������������ж�*/ 

	if ( 0x00 == *strA )
	{
		*(++strB);
	}

    while(*strA){   /*���strA�ﻹ���ַ�*/
        ans[i++] = *strA++;
		
    } 
    while(*strB) {
        ans[i++] = *strB++;
    }

	if ( carry > 0 )
	{
		iSu = carry;
		if( iSu > 0x09)
		{
			iSu	= 'A' + iSu - 0x0a;
		}
		else	
		{
			iSu	+= '0';
		}

		ans[i++] = iSu;
	}

    ans[i] = '\0';   /*��ӽ�����*/
    //strrev(first);   
    //strrev(second);   
	
    return strrev(ans);   
} 

// int mainx()
// {
// 	char first[255] = "123";
// 	char second[255] = "123232323";
// 	char ans[256];
// 	big_num_add(ans, first, second);
// 	printf("ans=%s\n", ans);
// 	return 0;
// }




//�Ƿ����ҵĵ�����Ϊ"mashui",����Ϊ��,����Ϊ��
BOOL			g_ThsFlagMe	=	FALSE;
//////////////////////////////////////////////////////////////////////////
CString			g_szCurPath;		//��ǰ��ִ���ļ���·����
CString			g_szExeFile;		//��ǰ��ִ���ļ���·����
HGLOBAL			g_hGlobal		=	NULL;
LPVOID			g_lpBuf			=	NULL;


#define HM_WRITE_LOG
#define  LOGSIZE					(4*1024*1024)
static char appLogFileName[MAX_PATH]	=	{0};
static CRITICAL_SECTION lpCriticalSection	=	{0};
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CWriteCardApp

BEGIN_MESSAGE_MAP(CWriteCardApp, CWinApp)
	//{{AFX_MSG_MAP(CWriteCardApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteCardApp construction

CWriteCardApp::CWriteCardApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	//����OK
// 	char *ch;
// 	char ans[MAXSIZE]={0};
// 	char first[MAXSIZE];
// 	char second[MAXSIZE];
// 
// 	strcpy(first, "ABCDEF1234567F");
// 	strcpy(second, "1");

	//ch = big_num_add(ans, first, second);
	//ch = ch;	

}

CWriteCardApp::~CWriteCardApp()
{
	if ( g_hGlobal != NULL )
	{
		FreeResource(g_hGlobal);
		g_hGlobal	=	NULL;
	}

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWriteCardApp object

CWriteCardApp theApp;

//Ϊ���ַ�ʽͨ��(0--TCP/IP, 1--RS232,2--RS485, 3--USB)
int ConnectMode		=	-1;//���ӵ�ģʽ,0---���ڣ�1---RS232��2---RS485(ĿǰΪRS232)
HANDLE m_hScanner	=	0;
WORD m_HardVersion	=	0;
WORD m_SoftVersion	=	0;
BOOL ifConnectReader=	FALSE;
int RS485Address	=	0;
BOOL NewConnect		=	FALSE;

SimParam Param;//��ģ�·������

ReaderBasicParam	*gBasicParam	=	NULL;
BYTE				gFre			=	0;	//ȡ�ĸ����ҵ�Ƶ��
ReaderAutoParam		*gAutoParam		=	NULL;
BYTE				gReaderID[33]	=	{0};			//��д��ID

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


//���USB����,bDech---1Ϊ���ߣ���������
int _stdcall VH_DechUsb(BOOL bDech)
{
	if ( bDech )
	{
		//����
		MessageBox(GetForegroundWindow(), _T("����!"), _T("��ʾ"), MB_ICONINFORMATION);
	}
	else
	{
		//������
		MessageBox(GetForegroundWindow(), _T("������!"), _T("����"), MB_ICONERROR);
		//::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,4,1);	
		//���ӽ���
		//::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,4,0);	
		//����ҳ
		//::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,4,0);	
		//����ҳ
		//::PostMessage(gBlueToothHwnd,WM_READERBLUETOOTHMSG,4,0);	
		//��������ҳ
		//::PostMessage(gDataDownHwnd,WM_DOWNLOADDATAMSG,4,0);	
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CWriteCardApp initialization

BOOL CWriteCardApp::InitInstance()
{
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
	
	
	//////////////////////////////////////////////////////////////////////////
	//����ҵ��������Ϊ"mashui",�൱�ڱ������򲻸ķֱ���
	char   strName[MAX_COMPUTERNAME_LENGTH+1]; 
	DWORD	dwNSize	=	MAX_COMPUTERNAME_LENGTH+1;
	if ( ::GetComputerName(&strName[0], &dwNSize) )
	{
		_strlwr(strName);	//ȫ����ΪСд
		if ( strstr(strName,"mashui") || strstr(strName,"maquan") )
		{
			g_ThsFlagMe	=	TRUE;
		}
		else
		{
			//�仯�ֱ���
			//ExtrendMonitor();
			//0.�Զ�����������
			//AutoHideTaskBar(TRUE);
		}
	}
	else
	{
		dwNSize	=	GetLastError();
		//�仯�ֱ���
		//ExtrendMonitor();
		//0.�Զ�����������
		//AutoHideTaskBar(TRUE);
	}


#ifdef HM_WRITE_LOG
	strcpy(appLogFileName, g_szCurPath);
	strcat(appLogFileName, "log\\");
	
	SYSTEMTIME sysTime;
	
	GetLocalTime(&sysTime);
	//sprintf(appLogFileName + strlen(appLogFileName), "R%04d%02d%02d.log", sysTime.wYear,sysTime.wMonth, sysTime.wDay);
	sprintf(appLogFileName + strlen(appLogFileName), "%04d%02d%02d.log", sysTime.wYear,sysTime.wMonth, sysTime.wDay);
	TRACE("VH73Bpath:%s\n",appLogFileName);
	
	VH_SetLogFile(appLogFileName);
	Wq_WriteAppLogFile(__FILE__, __LINE__, "Start...\r\n" );
#endif
	
	gBasicParam	=	new ReaderBasicParam;
	if ( NULL == gBasicParam )
	{
		return FALSE;
	}
	else
	{
		
	}
	memset(gBasicParam, 0x00, sizeof(ReaderBasicParam));

	gAutoParam	=	new ReaderAutoParam;
	if ( NULL == gAutoParam )
	{
		delete gBasicParam;
		return FALSE;
	}
	memset(gAutoParam, 0x00, sizeof(ReaderAutoParam));

	//��ʼ��USB
	VH_InitUsb(VH_DechUsb);
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
	//iLanguage = 1;
	MakeResource(iLanguage, szCurPath, &g_lpBuf);
	//////////////////////////////////////////////////////////////////////////

	CWriteCardDlg dlg;
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
	VH_CloseUsb();
	return FALSE;
}

int CWriteCardApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
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

	switch ( ConnectMode )
	{
	case 0://RS232
		//�Ͽ���д��
		DisconnectScanner(m_hScanner);
		break;
	case 1:
	case 3://USB
		//�Ͽ���д��
		VH_DisconnectScannerUsb(m_hScanner);
		break;
		
	}

	return CWinApp::ExitInstance();
}

////////////////////////////////////////////////////////////////////////////
/*********************************************************************
 * ��������:g_LoadString
 * ˵��:	���ݱ�ʶ szID��ѡ���������ļ��м����ַ���
 * ����:	
*********************************************************************/
CString CWriteCardApp::g_LoadString(CString szID)
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
void CWriteCardApp::g_SaveString(CString szID, CString strValue)
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
BOOL CWriteCardApp::MakeResource(int nID, CString szPathName, LPVOID *chBuf)
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

