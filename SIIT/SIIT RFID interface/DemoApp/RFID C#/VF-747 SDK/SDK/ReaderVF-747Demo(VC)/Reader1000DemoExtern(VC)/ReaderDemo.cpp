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
CString			g_szCurPath;		//当前可执行文件的路径名
CString			g_szExeFile;		//当前可执行文件的路径名
HGLOBAL			g_hGlobal		=	NULL;
LPVOID			g_lpBuf			=	NULL;
CProgress		*pgDlgPress		=	NULL;//窗体的指针

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
	char chUsername[16] = {0};			//用户名
	char chPassword[16] = {0};			//密码
	char chTrycheckceode[8]	=	{0};	//验证码
	
	
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
BOOL ifConnectReader=	0;//读写器是否连接，1---连接,0---没有连接
BOOL NewConnect		=	0;
int ConnectMode		=	-1;//连接的模式,0---网口，1---RS232，2---RS485

ReaderBasicParam	*gBasicParam	=	NULL;
BYTE				gFre			=	0;	//取哪个国家的频率
ReaderAutoParam		*gAutoParam		=	NULL;
BYTE				gReaderID[33]	=	{0};			//读写器ID

int iPlatform	=	0;	//0---626, 1---218
//////////////////////////////////////////////////////////////////////////
//218相关定义
int		nHostPort	=	0;
char nHostNetAddr[33]={0};
int nReaderMyPort;
char nReaderNetAddr[33]={0};
BYTE bModuleVer[10]	=	{0};
BYTE FreT[6]=	{0};
//////////////////////////////////////////////////////////////////////////
//用途:		向buffer中读取指定的字符串
//函数名:	Wq_GetPrivateProfileString
//功能:		与API的GetPrivateProfileString相似
//输入参数:	lpstrSection 指section如:[Setting]
//			lpstrEntry 指条目，如：Language=,等于号前面的
//			lpstrDefault 指取不到则默认值的字符串
//			strValue 指读成功后的字符串
//			nSize	指花多大的大小读
//			m_strBuf 指被读的整个BUF区字符串
//输出参数:	无
//返回值:	返回 TRUE 为成功，否则 FALSE 为失败
//备注:		获取指定的键值(注意目前只是针对ASCII格式的文本文件)
//////////////////////////////////////////////////////////////////////////
BOOL   Wq_GetPrivateProfileString(LPCTSTR lpstrSection,  LPCTSTR   lpstrEntry,   LPCTSTR lpstrDefault,LPTSTR   strValue,DWORD nSize,LPCTSTR  m_strBuf)   
{
	int ii = 0;
	CString   strSection, strEntry, strDefault;
	strSection = lpstrSection;
	strEntry = lpstrEntry;
	strDefault = lpstrDefault;
	int iLen = strDefault.GetLength();
	////先判断前两个参数是否为空   
	if(strSection   ==   _T("")   ||   strEntry   ==   _T(""))   
	{   
		for(ii = 0 ; ii < iLen ; ii++ )
			strValue[ii] = strDefault.GetAt(ii);
		strValue[ii] = 0x00;
		return   FALSE;       ///不成功则返回默认值   
	}   
	
	CString     strCombine;
	
	TRY   
	{
		
		strCombine = m_strBuf;
		
		//////开始查找，看section和entry是否已经存在   
		int   iIndex1,   iIndex2,   iIndex3,   iIndexT;           
		iIndex1   =   strCombine.Find(L"["   +   strSection   +   L"]\r\n");   
		if(iIndex1   ==   -1)     ///没找到   
		{   
			
			for(ii = 0 ; ii < iLen ; ii++ )
				strValue[ii] = strDefault.GetAt(ii);
			strValue[ii] = 0x00;
			
			return   FALSE;   
		}   
		iIndexT   =   iIndex1   +   4   +   strSection.GetLength();   
		iIndex2   =   strCombine.Find(strEntry   +   L"=",   iIndexT);   
		if(iIndex2   ==   -1)     ///没找到   
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
	END_CATCH             ///结束调试宏   
		
	return   FALSE;   
}


  
//////////////////////////////////////////////////////////////////////////
//用途:		向buffer中写入指定的字符串
//函数名:	Wq_WritePrivateProfileString
//功能:		与API的WritePrivateProfileString相似
//输入参数:	lpstrSection 指section如:[Setting]
//			lpstrEntry 指条目，如：Language=,等于号前面的
//			lpstrValue 指要写入的的字符串
//			m_strBuf 指被读的整个BUF区字符串
//输出参数:	无
//返回值:	返回 TRUE 为成功，否则 FALSE 为失败
//备注:		向指定的BUF对应的INI中某一段里,为特定的键写入一个CString值
//////////////////////////////////////////////////////////////////////////
BOOL     Wq_WritePrivateProfileString(LPCTSTR lpstrSection,   LPCTSTR lpstrEntry,   LPCTSTR lpstrValue, LPTSTR  m_strBuf)   
{   
	
	CString strSection, strEntry, strValue;
	strSection = lpstrSection;
	strEntry = lpstrEntry;
	strValue = lpstrValue;
	////先判断所有参数是否为空   
	if(lpstrSection   ==   _T("")   ||   lpstrEntry   ==   _T("")   ||   lpstrValue   ==   _T(""))
	{   
		return   FALSE;   
	}   

	CString     strCombine;   
	UINT   nLength	=	0;

	TRY   
	{   
		
		///把缓冲区地址赋给CString对象，为了使用CString包含的函数。   
		///一般Ini文件比较小，所以从缓冲区到CString的复制过程用时很短、耗费资源也很少   
		 

		///先创建大的缓冲区   
		//strCombine.GetBuffer(MAX_PATH);
		strCombine = m_strBuf;
		
		//////开始查找，看section和entry是否已经存在   
		//   iIndex1记录strSection位置   
		//   iIndex2记录strEntry位置   
		//   iIndex3记录strValue的结束位置   
		//   iIndexT记录插入的位置   

		int   iIndex1,   iIndex2,   iIndex3,   iIndexT;           
		iIndex1   =   strCombine.Find(L"["   +   strSection   +   L"]\r\n");   

		if(iIndex1   ==   -1)     ///没找到   
		{   
			strCombine   +=   L"["   +   strSection   +   L"]"   +   L"\r\n"     
				+   strEntry   +   L"="   +   strValue   +   L"\r\n";   

			///得到strCombine包含的缓冲区首地址   
			LPTSTR     lpCombine   =   strCombine.GetBuffer(0);
			
			return   FALSE;   
		}   

		iIndexT   =   iIndex1   +   4   +   strSection.GetLength();
		iIndex2   =   strCombine.Find(strEntry   +   L"=",   iIndexT);

		if(iIndex2   ==   -1)     ///没找到   
		{   
			strCombine.Insert(iIndexT,   strEntry   +   L"="   +   strValue   +   L"\r\n");   

			///得到strCombine包含的缓冲区首地址   
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

			//   替换掉已有的键值   
			iIndexT   =   iIndex2   +   1   +   strEntry.GetLength();   
			strCombine.Delete(iIndexT,   iIndex3   -   iIndexT);   
			strCombine.Insert(iIndexT,   strValue);   

			///得到strCombine包含的缓冲区首地址   
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
		/* ////用于调试，得到出错信息   
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
	END_CATCH           ///结束调试宏   

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
	//获取当前路径
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

	strConfigPath	=	g_szCurPath;	//配置参数ini的路径
	strConfigPath	+=	_T("Reader1100_1400.ini");

	gBasicParam	=	new ReaderBasicParam;
	if ( NULL == gBasicParam )
	{
		return FALSE;
	}
	else
	{
// 		gBasicParam->BaudRate		=	0;			//(1)串口的通信速率，取值：00H~08H，代表速率同"设定波特率"命令。
// 		gBasicParam->Power			=	20;			//(2)发射功率值，取值：20~30dBm。
// 		gBasicParam->Min_Frequence	=	1;		//(3)发射微波信号频率的起始点，取值： 1~63。
// 		gBasicParam->Max_Frequence	=	63;		//(4)发射微波信号频率的终止点，取值： 1~63。
// 		gBasicParam->Reserve5		=	0;			//(5)保留
// 		gBasicParam->WorkMode		=	0;			//(6)读写器工作方式：0-主动方式，1-命令方式
// 		gBasicParam->ReaderAddress	=	1;		//(7)RS485地址:0--255
// 		gBasicParam->NumofCard		=	5;			//(8)最多读卡数目。
// 		gBasicParam->TagType		=	2;			//(9)标签种类：01H－ISO18000-6B，02H－EPCC1，04H－EPCC1G2，08H－EM4442。
// 		gBasicParam->ReadDuration	=	0;		//(10)读卡持续时间：射频发射持续时间，只针对EM标签有效；0－10ms，1－20ms，2－30ms，3－40ms。
// 		gBasicParam->ReadTimes		=	2;			//(11)读卡次数M：收到上位机读卡命令，读写器执行M次此命令。
// 		gBasicParam->EnableBuzzer	=	1;		//(12)1:使能蜂鸣器0:不使能蜂鸣器
// 		gBasicParam->IP1;			    //(13)读写器IP地址
// 		gBasicParam->IP2;			    //(14)
// 		gBasicParam->IP3;			    //(15)
// 		gBasicParam->IP4;			    //(16)
// 		gBasicParam->Port1;				//(17)读写器端口高位
// 		gBasicParam->Port2;				//(18)
// 		gBasicParam->Mask1;				//(19)读写器掩码1
// 		gBasicParam->Mask2;				//(20)读写器掩码2
// 		gBasicParam->Mask3;				//(21)读写器掩码3
// 		gBasicParam->Mask4;				//(22)读写器掩码4
// 		gBasicParam->Gateway1;			//(23)读写器地址网关
// 		gBasicParam->Gateway2;			//(24)
// 		gBasicParam->Gateway3;			//(25)
// 		gBasicParam->Gateway4;			//(26)
// 		gBasicParam->MAC1;			    //(27)读写器MAC地址
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
	//iantennaIndex	=	0;	//选哪根天线,0-一根天线,1-四根天线
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
		//     繁体; 
		
		
		break;   
	case   0x0409:   
	case   0x0809:   
		//   英文; 
		iLanguage	=	0;
		break;   
	case   0x0804:   
		//     简体;
		iLanguage	=	1;
		break; 
	case  0x41F:
		//土耳其, "Turkey";
		
		break; 
	case 0x43E:
		//马来西亚, "Malaysia";
		break;
		
	case	0x81A:
		//塞尔维亚语(拉丁文)=$0000081A ,"Serbian";
		break;
		
	default:
		iLanguage	=	0;
	}
	MakeResource(iLanguage, szCurPath, &g_lpBuf);
	//////////////////////////////////////////////////////////////////////////

	
	

	CReaderDemoDlg dlg;
	//CProgress dlg;//测试用
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
 * 函数名称:g_LoadString
 * 说明:	根据标识 szID到选定的语言文件中加载字符串
 * 作者:	
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


	szValue.Replace("\\n","\n");	//替换回换行符号

	return szValue;
}



/*********************************************************************
 * 函数名称:g_SaveString
 * 说明:	根据标识 szID到选定的语言文件中加载字符串, strValue 指要写入的字串
 * 作者:	
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
 * 函数名称:CReaderDemoApp::MakeResource
 * 说明:	如果未找到所需的资源文件(如设置文件，语言文件等)，从程序中产生
 * chBuf 指读到这个buf中
 * 作者:  
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
	//我测试用的
	//CString strTemp;
	//HANDLE hUpdate;

	//strTemp	=	g_LoadString("IDWQA_B0003");
	//strTemp	=	"联机";
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
//用途:		将文件中所有数据载入BUF中
//函数名:	ReadBufFile
//功能:		读文件到BUF
//输入参数:	buf指字符指针,FilePathName指全路径名
//输出参数:	读出的数据存入buf，FilePathNameLen指读出的长度
//返回值:	DWORD型的数值返回长度
//备注:		如果buf为NULL，则只返回长度
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
//用途:		将buf中的Count的长度写入到文件中
//函数名:	WriteBufFile
//功能:		写数据到文件中
//输入参数:	buf指字符指针,Count要写的长度,FilePathName指全路径名,FilePathNameLen暂不用
//输出参数:	无
//返回值:	DWORD型的数值写入的字节数
//备注:		注意写回失败则返回0
//注意: modeNoTruncate的作用是不将文件的长度截断为0,如果不加modeNoTruncate
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
//用途:		将buf中的Count的长度写入到文件中
//函数名:	WriteBufFileEx
//功能:		写数据到文件中
//输入参数:	buf指字符指针,Count要写的长度,FilePathName指全路径名,FilePathNameLen暂不用
//输出参数:	无
//返回值:	DWORD型的数值写入的字节数
//备注:		注意写回失败则返回0
//注意: modeReadWrite|CFile::modeCreate直接清了原文件
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


