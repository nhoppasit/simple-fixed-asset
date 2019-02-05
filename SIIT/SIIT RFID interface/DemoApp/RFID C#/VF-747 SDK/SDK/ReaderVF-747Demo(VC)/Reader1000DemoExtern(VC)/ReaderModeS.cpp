// ReaderModeS.cpp : implementation file
//

#include "stdafx.h"
#include "readerdemo.h"
#include "ReaderModeS.h"

#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL    nReadThreadS		=	FALSE;
CRITICAL_SECTION lpCriticalSectionS	=	{0};
HWND	gRSModeHwnd	=	NULL;
//创建关闭事件
HANDLE m_hCloseEvent;


struct DataPacketS
{
	int len;				//buffer length
	char chbuf[1025];	//actual buffer
};

CTList<DataPacketS> m_ReadListOutS;
CCriticalSection m_readLockS;


/////////////////////////////////////////////////////////////////////////////
// ReaderModeS dialog

IMPLEMENT_DYNCREATE(ReaderModeS, CPropertyPage)

ReaderModeS::ReaderModeS(): CPropertyPage(ReaderModeS::IDD)
{
	//{{AFX_DATA_INIT(ReaderModeS)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_DataFormat	=	-1;//0-16进制,1-10进制
}

ReaderModeS::~ReaderModeS()
{
}

void ReaderModeS::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ReaderModeS)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Radio(pDX, IDC_RADIO1_Hex16, m_DataFormat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ReaderModeS, CPropertyPage)
	//{{AFX_MSG_MAP(ReaderModeS)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1_MSGET, OnButton1Msget)
	ON_BN_CLICKED(IDC_BUTTON1_MSUPDATE, OnButton1Msupdate)
	ON_BN_CLICKED(IDC_BUTTON1_MSSTARTRECV, OnButton1Msstartrecv)
	ON_BN_CLICKED(IDC_BUTTON1_MSSTOPRECV, OnButton1Msstoprecv)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DLGSMALLMODEDATAMSG, OnRSModedatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ReaderModeS message handlers

BOOL ReaderModeS::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	gRSModeHwnd	=	this->GetSafeHwnd();

	InitializeCriticalSection(&lpCriticalSectionS);
	hReadThread	=	NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ReaderModeS::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	nReadThreadS	=	FALSE;
	SetEvent(m_hCloseEvent);//通知关闭系统
	Sleep(50);
	if ( NULL != hReadThread )
	{
		CloseHandle(hReadThread);
	}
	
	return;
}

void ReaderModeS::OnButton1Msget() 
{
	// TODO: Add your control notification handler code here
	//获取参数
	int				i			=	0;
	apiReturn		res			=	_no_scanner;
	BYTE			tBuf[32]	=	{0};
	int				iSize		=	0;
	CString strTemp;

	UpdateData(TRUE);

	for ( i = 0; i < 3; i++ )
	{
		res	=	GetReaderSmallModeParam(m_hScanner, tBuf, &iSize);
		if ( _OK == res )
		{
			break;
		}
	}

	if ( _OK == res )
	{
	
		//是否要前缀，前缀值，是否要回车符，数据输出格式0-16进制，1-十进制，数据起始地址，数据长度
		((CButton*)GetDlgItem(IDC_CHECK1_PERFIX))->SetCheck(tBuf[0]);//是否要前缀

		strTemp.Format("0x%02X", tBuf[1]);
		GetDlgItem(IDC_EDIT2_PERFIXVALUE)->SetWindowText(strTemp);//前缀值

		((CButton*)GetDlgItem(IDC_CHECK1_LF))->SetCheck(tBuf[2]);//是否要回车符

		m_DataFormat	=	tBuf[3];//0-16进制,1-10进制


		strTemp.Format("%d", tBuf[4]);
		GetDlgItem(IDC_EDIT2_MSDATAStart)->SetWindowText(strTemp);//数据起始地址

		strTemp.Format("%d", tBuf[5]);
		GetDlgItem(IDC_EDIT2_MSDATALEN)->SetWindowText(strTemp);//数据长度

	}
	else
	{
		MessageBox("set fail!","Warning",MB_ICONWARNING);
	}

	UpdateData(FALSE);

}

void ReaderModeS::OnButton1Msupdate() 
{
	// TODO: Add your control notification handler code here
	//更新参数
	int				i			=	0;
	apiReturn		res			=	_no_scanner;
	BYTE			tBuf[32]	=	{0};
	int				iSize		=	0;
	CString strTemp;
	
	UpdateData(TRUE);
	
	//是否要前缀，前缀值，是否要回车符，数据输出格式0-16进制，1-十进制，数据起始地址，数据长度
	tBuf[0]	=	((CButton*)GetDlgItem(IDC_CHECK1_PERFIX))->GetCheck();//是否要前缀
	
	
	GetDlgItem(IDC_EDIT2_PERFIXVALUE)->GetWindowText(strTemp);//前缀值
	strTemp = strTemp.Right(2);
	Asc2Bcd((char*)&tBuf[1], strTemp.GetBuffer(0), 2);
	
	tBuf[2]	=	((CButton*)GetDlgItem(IDC_CHECK1_LF))->GetCheck();//是否要回车符
	
	tBuf[3]	=	m_DataFormat;//0-16进制,1-10进制
	
	
	
	GetDlgItem(IDC_EDIT2_MSDATAStart)->GetWindowText(strTemp);//数据起始地址
	tBuf[4] = atoi(strTemp);
	
	GetDlgItem(IDC_EDIT2_MSDATALEN)->GetWindowText(strTemp);//数据长度
	tBuf[5] = atoi(strTemp);

	for ( i = 0; i < 3; i++ )
	{
		res	=	SetReaderSmallModeParam(m_hScanner, tBuf, 6);
		if ( _OK == res )
		{
			break;
		}
	}
	if ( _OK == res )
	{
		MessageBox("set ok!","info",MB_ICONINFORMATION);
		
	}
	else
	{
		MessageBox("set fail!","Warning",MB_ICONWARNING);
	}
	
	UpdateData(FALSE);


}


void ReaderModeS::OnButton1Msstartrecv() 
{
	// TODO: Add your control notification handler code here
	int				i			=	0;
	apiReturn		res			=	_no_scanner;

	GetDlgItem(IDC_BUTTON1_MSSTARTRECV)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1_MSSTOPRECV)->EnableWindow(TRUE);


	for ( i = 0; i < 3; i++ )
	{
		res = AutoMode(m_hScanner,1,0);
		if ( res == _OK)
		{
			break;
		}
	}
	
	if(res==_OK)//串口对串口(命令模式串口，自动模式串口)
	{
		PurgeComm(m_hScanner,PURGE_TXCLEAR|PURGE_RXCLEAR);

		nReadThreadS	=	FALSE;
		hReadThread	=	CreateThread(NULL,0,ReadThreadS,this,0,NULL);
		if( hReadThread != NULL )
		{		
			nReadThreadS	=	TRUE;
			GetDlgItem(IDC_BUTTON1_MSSTARTRECV)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON1_MSSTOPRECV)->EnableWindow(TRUE);
			
		}
		else
		{
			MessageBox("Create ReadThread Error!","Notice",MB_ICONERROR);
			
			
		}

	}
	else
	{
		MessageBox("set fail!","Warning",MB_ICONWARNING);
	}

	return;
}


void ReaderModeS::OnButton1Msstoprecv() 
{
	// TODO: Add your control notification handler code here
	//停止接收
	GetDlgItem(IDC_BUTTON1_MSSTARTRECV)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1_MSSTOPRECV)->EnableWindow(TRUE);

	
	nReadThreadS	=	FALSE;
	SetEvent(m_hCloseEvent);//通知关闭系统
	Sleep(50);
	CloseHandle(hReadThread);
	hReadThread   =   NULL;


	GetDlgItem(IDC_BUTTON1_MSSTOPRECV)->EnableWindow(FALSE);
	return;
}



//自动模式下读线程函数
DWORD WINAPI ReaderModeS::ReadThreadS(LPVOID pParam)
{
	
	//DWORD dwRes;
	char recvbuf[4096]	=	{0};
	char tempbuf[4096]	=	{0};
	
	OVERLAPPED osReader = {0};

	int recv_len	=	0;
	int len_temp	=	0;
	DWORD lReadSize =	0;
	
	CString strtmp;
	int m=0;
	HANDLE hRSTemp	=	INVALID_HANDLE_VALUE;

	ReaderModeS* m_pStandard	=	(ReaderModeS*)pParam;

	int iRecvLen	=	0;
	SOCKADDR_IN SockAddrIn;
	SockAddrIn.sin_family=AF_INET;
	iRecvLen	=	sizeof(SOCKADDR);

	int iIndexItem	=	0;
	int iRecvCombyte	=	166;
	DWORD dwError	=	0;
	

	
	HANDLE WaitHandles[2]; //监听事件数组
	DWORD dwSignaledHandle;

	
	osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//创建关闭事件
	m_hCloseEvent	= CreateEvent(NULL,TRUE,FALSE,NULL);
			


	WaitHandles[0] = m_hCloseEvent;
	WaitHandles[1] = osReader.hEvent;


	SetCommMask(m_hScanner, EV_ERR | EV_RLSD | EV_RING ); 

	while( nReadThreadS )
	{
		if ( lpCriticalSectionS.LockSemaphore != NULL )
		{
			EnterCriticalSection(&lpCriticalSectionS);
		}

		//Sleep(1);
		//TRACE("nReadThread=%d\n", nReadThread);

		//这里是为了测试显示的
			
			//If the function succeeds, the return value is nonzero. 
			if (!ReadFile(m_hScanner, (char*)recvbuf, 1024, &lReadSize, &osReader))  
			{
				dwError	=	GetLastError();
				if ( dwError != ERROR_IO_PENDING )     // read not delayed?
				{
					// Error in communications; report it.
					//continue;
					
				}
				else
				{
					//dwRes = WaitForSingleObject(osReader.hEvent, INFINITE);
					dwSignaledHandle=WaitForMultipleObjects(2, WaitHandles, FALSE, INFINITE);
					switch(dwSignaledHandle)
					{

					case WAIT_OBJECT_0:
						//退出
						TRACE("ExitThread!\r\n");
						break;

					case WAIT_OBJECT_0+1:// Read completed.
						if (!GetOverlappedResult(m_hScanner, &osReader, &lReadSize, FALSE))
						{
							// Error in communications; report it.
							//continue;
						}
						break;
					}
				}
			}

			len_temp = (int)lReadSize;
	
	

		strtmp = _T("");
		//continue;
		if ( len_temp > 0 && len_temp < 1024 )
		{

			Bcd2Asc(strtmp.GetBuffer(2048), (char*)recvbuf, len_temp*2);
			strtmp.ReleaseBuffer();
			*(recvbuf + len_temp)	=	0x00;

			//strtmp.Replace("0D0A","\r\n");
			WriteAppLogFile(__FILE__, __LINE__, "Recv[%04d]:%s\r\n", len_temp, strtmp);

			DataPacketS dt;
			dt.len	=	len_temp;
			memcpy(dt.chbuf, recvbuf, len_temp);
			
			CSingleLock csl(&m_readLockS);
			csl.Lock();

			m_ReadListOutS.AddTail(dt);

			csl.Unlock();


			::PostMessage(gRSModeHwnd, WM_DLGSMALLMODEDATAMSG, 0, 1);
			//////////////////////////////////////////////////////////////////////////
			


		}
		


		if ( lpCriticalSectionS.LockSemaphore != NULL )
		{
			LeaveCriticalSection(&lpCriticalSectionS);
		}

	}//end of while( nReadThread )


	PurgeComm(m_hScanner, PURGE_RXABORT | PURGE_RXCLEAR);
	if ( osReader.hEvent != NULL )
	{
		CloseHandle(osReader.hEvent);
		osReader.hEvent	=	NULL;
	}
	

	if ( m_hCloseEvent != NULL )
	{
		CloseHandle(m_hCloseEvent);
		m_hCloseEvent	=	NULL;
	}
	


	return 0;

}


//WM_DLGSMALLMODEDATAMSG
afx_msg LRESULT ReaderModeS::OnRSModedatamsg(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 0 == iwParam )
	{
		if ( 0 == lParam )
		{
		}
		else if ( 1 == lParam )
		{
			int i = 0;
			int k = 0;
			DWORD dwRes	=	0;
			char tempbuf[4097]	=	{0};
			int recv_len	=	0;
			
			
			CString strtmp;
			CString strtmx;
			int iIndexItem	=	0;
			
			
			DataPacketS dt;
			if ( FALSE == m_ReadListOutS.IsEmpty() )
			{
				
				
				dt = m_ReadListOutS.GetHead();
				
				
				
				
				memcpy(tempbuf, dt.chbuf, dt.len);
				*(tempbuf + dt.len)	=	0x00;
				
				Bcd2Asc(strtmp.GetBuffer(2048), (char*)tempbuf, dt.len*2);
				strtmp.ReleaseBuffer();

				//TRACE("%d:%s\n", dt.len, strtmp);
				if ( strtmp.Find("CC") >= 0 )
				{
					strtmp = strtmp;
				}

				GetDlgItem(IDC_EDIT_MODESMALL)->GetWindowText(strtmx);
				strtmx	+=	strtmp;
				strtmx	+=	"\r\n";
				strtmx	+=	"\r\n";
				GetDlgItem(IDC_EDIT_MODESMALL)->SetWindowText(strtmx);
				((CEdit*)GetDlgItem(IDC_EDIT_MODESMALL))->SetSel(strtmx.GetLength(), strtmx.GetLength());
				((CEdit*)GetDlgItem(IDC_EDIT_MODESMALL))->SetFocus();

				CSingleLock csl(&m_readLockS);
				csl.Lock();
				m_ReadListOutS.RemoveHead();
				csl.Unlock();


			}
			



		}
	}

	return 0;
}

