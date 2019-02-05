// Connect.cpp : implementation file
//

#include "stdafx.h"
#include "WriteCard.h"
#include "Connect.h"
#include "WriteCardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
HWND	gConnectReaderHwnd	=	NULL;	//���ӵĴ���ľ��
BOOL    nThreadFlag			=	FALSE;







//////////////////////////////////////////////////////////////////////////
//��;:		ȡ��ϵͳ��COM��
//������:	VHGetSystemPorts
//����:		
//�������:	CComboBox ָ��
//�������:	
//����ֵ:	��
//��ע:		
//////////////////////////////////////////////////////////////////////////
void _stdcall VHGetSystemPorts(CComboBox *tempCombBox)
{    
    CRegKey RegKey;  
    int nCount = 0;       
    CString tempCStr;
	long i;
	HKEY hAppKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	
	i=RegKey.Open(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"),KEY_READ );
	
	
	//��HKEY_CURRENT_USER\"Software"
	//i	=	RegOpenKeyEx(HKEY_CURRENT_USER, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_WRITE|KEY_READ,
	//	&hSoftKey);
	
	
    if(i == ERROR_SUCCESS)    
    {    
        while(true)
        {    
            char ValueName[_MAX_PATH];
            unsigned char ValueData[_MAX_PATH];
            DWORD nValueSize = _MAX_PATH;
            DWORD nDataSize = _MAX_PATH;
            DWORD nType;
			
            if(::RegEnumValue(HKEY(RegKey), nCount, ValueName, &nValueSize, NULL, &nType, ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)    
            {    
                break;
            }
			if(strlen((char*)ValueData))
			{
				tempCStr.Format(_T("%s"),ValueData);
				tempCombBox->AddString(tempCStr);
			}
			nCount++;
        }
    }    
    
	RegKey.Close();
}


//�����ض����������罫COM1,COM11,COM2,COM23,COM15�ų����£�
//1:COM1,COM2,COM11,COM15,COM23,���������ų������⣺
//2:COM1,COM11,COM15,COM2,COM23,
//ע�Ȿ���ǵ�һ��
int zzcmp(const void *a, const void *b)
{
	int ia	=	0;
	int ib	=	0;
	char *x	=	(char *)((char*)a+3);
	char *y	=	(char *)((char*)b+3);
	
	ia	=	atoi(x);
	ib	=	atoi(y);
	//Asc2Bcd((char*)&ia, x, 2);
	//Asc2Bcd((char*)&ib, y, 2);
    //return strcmp(x, y);
	
	return ia >= ib ? 1 : -1;
}

//////////////////////////////////////////////////////////////////////////
//��;:		ȡ��ϵͳ��COM��
//������:	VH75GetSystemPorts
//����:		
//�������:	char ** tempCombBoxΪ�ַ�������ָ��
//�������:	
//����ֵ:	���ظ���
//��ע:		
//////////////////////////////////////////////////////////////////////////
int _stdcall VH75GetSystemPorts(char **tempCombBox)
{    
    //CRegKey RegKey;  
    int nCount = 0;
	long i;
	HKEY hAppKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	char chCCom[MAX_PATH][16]	=	{0};
	int k =0;
	
	//i=RegKey.Open(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"),KEY_READ );
	
	
	//��HKEY_LOCAL_MACHINE\\DEVICEMAP\\SERIALCOMM"
	i	=	RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hSoftKey);
	
    if(i == ERROR_SUCCESS)    
    {    
        while(TRUE)    
        {    
            char ValueName[_MAX_PATH];
            unsigned char ValueData[_MAX_PATH];
            DWORD nValueSize = _MAX_PATH;
            DWORD nDataSize = _MAX_PATH;
            DWORD nType;
			
            if(RegEnumValue(hSoftKey, nCount, ValueName, &nValueSize, NULL, &nType, ValueData, &nDataSize) == ERROR_NO_MORE_ITEMS)    
            {    
                break;    
            }
			if(strlen((char*)ValueData))
			{
				//tempCStr.Format(_T("%s"),ValueData);
				//tempCombBox->AddString(tempCStr);
				strcpy((char*)&chCCom[k], (char*)ValueData);
				k++;
			}
			nCount++;
        }
		
		qsort(chCCom,k,16*sizeof(char),zzcmp);
		if ( NULL != tempCombBox )
		{
			for ( i = 0; i < k; i++)
			{
				strcpy((char*)tempCombBox[i], (char*)&chCCom[i]);
			}
		}
		
		
    }
	
	RegCloseKey(hSoftKey);
	
	return k;
}


/////////////////////////////////////////////////////////////////////////////
// CConnect property page

IMPLEMENT_DYNCREATE(CConnect, CPropertyPage)

CConnect::CConnect() : CPropertyPage(CConnect::IDD)
{
	//{{AFX_DATA_INIT(CConnect)
		// NOTE: the ClassWizard will add member initialization here
	m_ConnectMode = 1;//0-rs232, 1-USB
	m_LanguageIndex	=	0;//0-English,1-chinese
	//}}AFX_DATA_INIT
}

CConnect::~CConnect()
{
}

void CConnect::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Radio(pDX, IDC_RADIO_ConnectRS232, m_ConnectMode);
	DDX_Radio(pDX, IDC_RADIO_CONEnglish, m_LanguageIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnect, CPropertyPage)
	//{{AFX_MSG_MAP(CConnect)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO_ConnectRS232, OnRADIOConnectRS232)
	ON_BN_CLICKED(IDC_RADIO_ConnectUSB, OnRADIOCONUsb)
	ON_BN_CLICKED(IDC_RADIO_CONEnglish, OnRADIOCONEnglish)
	ON_BN_CLICKED(IDC_RADIO_CONChinese, OnRADIOCONChinese)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CONNECTDIS, OnButtonConnectdis)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CONNECTDATACUSTOM, OnConnectdatacustom)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnect message handlers

void CConnect::OnInitUIText()//������ı�����
{
	SetWindowText(theApp.g_LoadString("IDWQF_B0001"));//��д������
	
	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(theApp.g_LoadString("IDWQF_B0002"));//���Ӷ�д��
	GetDlgItem(IDC_STATIC_ConnectMode)->SetWindowText(theApp.g_LoadString("IDWQF_B0004"));//����ģʽ
	GetDlgItem(IDC_RADIO_ConnectRS232)->SetWindowText(theApp.g_LoadString("IDWQF_B0005"));//RS232
	GetDlgItem(IDC_BUTTON_CONNECTDIS)->SetWindowText(theApp.g_LoadString("IDWQF_B0003"));//�Ͽ�����
	GetDlgItem(IDC_STATIC_CONLanguage)->SetWindowText(theApp.g_LoadString("IDWQF_B0007"));//����
	GetDlgItem(IDC_RADIO_CONEnglish)->SetWindowText(theApp.g_LoadString("IDWQF_B0008"));//Ӣ��
	GetDlgItem(IDC_RADIO_CONChinese)->SetWindowText(theApp.g_LoadString("IDWQF_B0009"));//��������
	
	
}

void CConnect::UpdateStatus()//����ʹ���벻ʹ��
{
	UpdateData(TRUE);
	
 	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(!ifConnectReader);
 	GetDlgItem(IDC_BUTTON_CONNECTDIS)->EnableWindow(ifConnectReader);

	GetDlgItem(IDC_RADIO_ConnectRS232)->EnableWindow(!ifConnectReader);
	GetDlgItem(IDC_COMBO1)->EnableWindow(!ifConnectReader);
	
 	
 	if ( 1 == m_ConnectMode )
 	{
 		//���USBѡ��
 		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
 	}
	
	UpdateData(FALSE);
}

BOOL CConnect::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//////////////////////////////////////////////////////////////////////////
	//UpdateStatus();//����ʹ���벻ʹ��
	::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,2,0);	//convert language

	return CPropertyPage::OnSetActive();
}

BOOL CConnect::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}

BOOL CConnect::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_STATIC_ConnectMode)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_RADIO_ConnectUSB)->ShowWindow(SW_HIDE);//USB
	GetDlgItem(IDC_RADIO_ConnectRS232)->ShowWindow(SW_HIDE);//RS232

	//���ҪҪ��������ʾ���ԣ���Ҫ��������,�����ѡ�����ԣ�����������
	#if 0
	GetDlgItem(IDC_STATIC_CONLanguage)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_RADIO_CONEnglish)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_RADIO_CONChinese)->ShowWindow(SW_HIDE);//
	#endif

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);//
	GetDlgItem(IDC_BUTTON_CONNECTDIS)->EnableWindow(FALSE);//

	//Ϊ�˵����ã�����ʦ����ôŪ�ģ��ͻ��õ������ֻҪ����������mashui/maquan,��ֻ��ʾUSB��
	//�Ƿ����ҵĵ�����Ϊ"mashui",����Ϊ��,����Ϊ��
	if ( g_ThsFlagMe )
	{
		GetDlgItem(IDC_STATIC_ConnectMode)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_ConnectRS232)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_ConnectUSB)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_CONRS232)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SerialPort)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);

	}
	else
	{
		GetDlgItem(IDC_STATIC_ConnectMode)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_ConnectRS232)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_ConnectUSB)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_CONRS232)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SerialPort)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	}


	//	CComboBox *m_SerialPort	=	(CComboBox*)GetDlgItem(IDC_COMBO1);
	// 	m_SerialPort->AddString("COM1");
	// 	m_SerialPort->AddString("COM2");
	// 	m_SerialPort->AddString("COM3");
	// 	m_SerialPort->AddString("COM4");
	// 	m_SerialPort->AddString("COM5");
	// 	m_SerialPort->AddString("COM6");
	// 	m_SerialPort->AddString("COM7");
	// 	m_SerialPort->AddString("COM8");
	// 	m_SerialPort->AddString("COM9");
	// 	m_SerialPort->AddString("COM10");
	// 	m_SerialPort->AddString("COM11");
	// 	m_SerialPort->AddString("COM12");
	//////////////////////////////////////////////////////////////////////////
	//ȡϵͳ�е�COM��
	CComboBox *m_SerialPort	=	(CComboBox*)GetDlgItem(IDC_COMBO1);
	//m_SerialPort->AddString("COM1");
	//VHGetSystemPorts(m_SerialPort);
	
	int		chi		=	0;
	char **chComm	=	NULL;
	//��ζ�̬�����ά����
	chComm = (char**)malloc(sizeof(char*) * MAX_PATH);
	for (chi = 0; chi < MAX_PATH; chi++)
	{
		chComm[chi]	=	(char*)malloc(sizeof(char) * 16);
	}
				
	short nCurSelected	=	(short)VH75GetSystemPorts(chComm);
	for (chi = 0; chi < nCurSelected; chi++)
	{
		m_SerialPort->AddString(chComm[chi]);
		
	}
	if ( nCurSelected > 0 )
	{
		m_SerialPort->SetCurSel(0);
	}
	
	
	for (chi = 0; chi < MAX_PATH; chi++)
	{
		free(chComm[chi]);
		chComm[chi]	=	NULL;
	}
	free(chComm);
	chComm	=	NULL;


	#if 1
	UpdateData(TRUE);
	// TODO: Add extra initialization here
	gConnectReaderHwnd	=	this->GetSafeHwnd();	//���ӵĴ���ľ��
	
	
	ConnectMode		=	1;
	m_LanguageIndex	=	theApp.iLanguage;
	UpdateData(FALSE);
	
	
	//////////////////////////////////////////////////////////////////////////
	UpdateStatus();//����ʹ���벻ʹ��
	
	//������
	Wq_WriteAppLogFile(__FILE__, __LINE__, "Connect...\r\n" );
	//::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
	//���ӽ���
	
	#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnect::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CConnect::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	
	//���Ӷ�д��
	UpdateData(TRUE);
	
	apiReturn res	=	_no_scanner;
	int i = 0;
	char port[MAX_PATH]={0},IPAddr[MAX_PATH]={0};
	CComboBox *m_SerialPort	=	(CComboBox*)GetDlgItem(IDC_COMBO1);
	m_SerialPort->GetLBText(m_SerialPort->GetCurSel(),IPAddr);
	sprintf(port,"\\\\.\\%s",IPAddr);

	//�������:	lOpt Ϊ���ַ�ʽͨ��(0--TCP/IP, 1--RS232,2--RS485, 3--USB)
	long lopt = 0;

	Wq_WriteAppLogFile(__FILE__, __LINE__, "OnButtonConnect1\r\n" );
#if 1
	switch ( m_ConnectMode )
	{
		case 0://RS232
			lopt	=	1;//RS232
			Wq_WriteAppLogFile(__FILE__, __LINE__, "OnButtonConnectaaa\r\n" );
			res=ConnectScanner(&m_hScanner,port,0);
			Wq_WriteAppLogFile(__FILE__, __LINE__, "OnButtonConnectbbb\r\n" );
			break;
		case 1://USB
			lopt	=	3;//USB
			Wq_WriteAppLogFile(__FILE__, __LINE__, "OnButtonConnectxxx\r\n" );
			res=VH_ConnectScannerUsb(&m_hScanner);
			Wq_WriteAppLogFile(__FILE__, __LINE__, "OnButtonConnectyyy\r\n" );
			break;
		default:
			Wq_WriteAppLogFile(__FILE__, __LINE__, "OnButtonConnectzzz\r\n" );
	}
	ConnectMode = lopt;
	Wq_WriteAppLogFile(__FILE__, __LINE__, "OnButtonConnect2\r\n" );

	if (res==_OK)
	{
		//��ͨ�ŷ�ʽ������
		//VH_SetCommunicationOpt(lopt, (void*)&m_hScanner);
		VH_SetCommunicationOpt(lopt, (int)m_hScanner);
		//Sleep(1000);
// 		for (i = 0; i < 3; i++)
// 		{
// 			//��ֹͣ�Զ�
// 			res=AutoMode(m_hScanner, 0x00);
// 			if ( _OK == res )
// 			{
// 				break;
// 			}
// 		}
// 		if (res!=_OK)
// 		{
// 			//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
// 			MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
// 			OnButtonConnectdis();
// 			return;
// 		}
		

		for (i = 0; i < 3; i++)
		{
			//���汾
			res=VH_GetVersion(m_hScanner,&m_HardVersion,&m_SoftVersion);
			if ( _OK == res )
			{
				break;
			}
		}
		if (res!=_OK)
		{
			//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
			OnButtonConnectdis();
			return;
		}

		for (i = 0; i < 3; i++)
		{
			//����������
			res=ReadBasicParam(m_hScanner,gBasicParam);
			if ( _OK == res )
			{
				break;
			}
		}
		if (res!=_OK)
		{
			//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
			OnButtonConnectdis();
			return;
		}

		for (i = 0; i < 3; i++)
		{
			//����Ƶ��
			res=GetFrequencyRange(m_hScanner, &gFre);
			if ( _OK == res )
			{
				break;
			}
		}
		if (res!=_OK)
		{
			//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
			OnButtonConnectdis();
			return;
		}

		for (i = 0; i < 3; i++)
		{
			//��auto����
			res=ReadAutoParam(m_hScanner,gAutoParam);
			if ( _OK == res )
			{
				break;
			}
		}
		if (res!=_OK)
		{
			//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
			OnButtonConnectdis();
			return;
		}

		for (i = 0; i < 3; i++)
		{
			//��ID
			res=GetReaderID(m_hScanner,gReaderID);
			if ( _OK == res )
			{
				break;
			}
		}
		if (res!=_OK)
		{
			//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
			OnButtonConnectdis();
			return;
		}


		//Ϊ�˵����ã�һ�㲻�ᷢ���������ڵ�����
		if ( g_ThsFlagMe )
		{
			
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				//���������
				res=ReadSimParam(m_hScanner,&Param);
				if ( _OK == res )
				{
					break;
				}
			}
			if (res!=_OK)
			{
				//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
				OnButtonConnectdis();
				return;
			}
		}

		ifConnectReader=1;
		NewConnect=1;

		//�����ˣ���ر��
		UpdateStatus();//����ʹ���벻ʹ��

		//MessageBox("Connect Reader Success!", "info",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQF_B0013"), theApp.g_LoadString("IDWQF_B0014"), MB_ICONINFORMATION);

		CWriteCardDlg * pMainDlg=(CWriteCardDlg *)pMain;
		if ( NULL != pMainDlg )
		{
			pMainDlg->m_Sheet.SetActivePage(1);
		}
		
		
	}
	else
	{
		//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
		OnButtonConnectdis();
		
	}

#endif
	UpdateData(FALSE);

	return;

}

void CConnect::OnButtonConnectdis() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	switch ( m_ConnectMode )
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
	
	m_hScanner	=	0;
	ifConnectReader=0;
	NewConnect=0;
	m_HardVersion=0;
	m_SoftVersion=0;

	//�����ˣ���ر��
	UpdateStatus();//����ʹ���벻ʹ��

	UpdateData(FALSE);
	return;
}


void CConnect::OnRADIOCONEnglish() 
{
	// TODO: Add your control notification handler code here
	BOOL bFlag = FALSE;
	theApp.iLanguage	=	0;
	
	if ( theApp.iLanguage == 0 )	//Ӣ��
	{
		
		theApp.MakeResource(theApp.iLanguage, _T(""), &g_lpBuf);
		bFlag	=	TRUE;
	}
	else if ( theApp.iLanguage == 1 ) //����
	{
		
		theApp.MakeResource(theApp.iLanguage, _T(""), &g_lpBuf);
		bFlag	=	TRUE;
	}
	
	if ( bFlag )
	{
		//��ǰ������
		::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
		//���ӽ���
		::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,2,0);	//convert language
		//����ҳ
		//::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,2,0);	//convert language
		//����ҳ
		//::PostMessage(gBlueToothHwnd,WM_READERBLUETOOTHMSG,2,0);	//convert language
		//��������ҳ
		//::PostMessage(gDataDownHwnd,WM_DOWNLOADDATAMSG,2,0);	//convert language
		
		
	}
	
	return;

}

void CConnect::OnRADIOCONChinese() 
{
	// TODO: Add your control notification handler code here
	BOOL bFlag = FALSE;
	theApp.iLanguage	=	1;
	
	if ( theApp.iLanguage == 0 )	//Ӣ��
	{

		theApp.MakeResource(theApp.iLanguage, _T(""), &g_lpBuf);
		bFlag	=	TRUE;
	}
	else if ( theApp.iLanguage == 1 ) //����
	{

		theApp.MakeResource(theApp.iLanguage, _T(""), &g_lpBuf);
		bFlag	=	TRUE;
	}
	
	if ( bFlag )
	{
		//��ǰ������
		::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
		//���ӽ���
		::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,2,0);	//convert language
		//����ҳ
		//::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,2,0);	//convert language
		//����ҳ
		//::PostMessage(gBlueToothHwnd,WM_READERBLUETOOTHMSG,2,0);	//convert language
		//��������ҳ
		//::PostMessage(gDataDownHwnd,WM_DOWNLOADDATAMSG,2,0);	//convert language
		
	}
	
	return;

}

void CConnect::OnRADIOConnectRS232()
{
	UpdateStatus();//����ʹ���벻ʹ��
}

void CConnect::OnRADIOCONUsb()
{
	UpdateStatus();//����ʹ���벻ʹ��
}

//////////////////////////////////////////////////////////////////////////
//��;:		��ģ�����Ϣ��̬��Ա����,�ص�����
//������:	CallBack_MyTimeListDisp
//����:		
//�������:	hWnd--handle of CWnd that called SetTimer
//			nMsg--WM_TIMER
//			nIDEvent--timer identification
//			dwTime--system time 
//�������:	��
//����ֵ:	��
//��ע:TIME_IDENTIFIER_LISTDISP, INTERVALTIME_LISTDISP
//////////////////////////////////////////////////////////////////////////
void WINAPI CConnect::CallBack_MyTimeListDisp(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime)
{
	//Debug_Printf("r:%s\r\n","hello");
	if ( TIME_IDENTIFIER_LISTDISP == nIDEvent )
	{
		::PostMessage(gConnectReaderHwnd, WM_CONNECTDATACUSTOM, 0, 0);
	}
}

//WM_CONNECTDATACUSTOM
afx_msg LRESULT CConnect::OnConnectdatacustom(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 0 == iwParam )
	{
		if ( 0 == ilParam )
		{
			apiReturn res	=	_no_scanner;

			if ( iCount > 0 )
			{
				res	=	VH_GetVersion(m_hScanner,&m_HardVersion,&m_SoftVersion);
				if ( _OK == res )
				{
					//������
					iCount = 0;
					::KillTimer(gConnectReaderHwnd, TIME_IDENTIFIER_LISTDISP);
					//�ص����ȿ�
					#if defined (ENABLE_PROGRESSDISPTIP)
					::PostMessage(gProgressHwnd, WM_PROGRESS, 2, 0);
					::PostMessage(gProgressHwnd, WM_PROGRESS, 3, 0);
					#endif

					ifConnectReader=1;
					NewConnect=1;
					
					//�����ˣ���ر��
					UpdateStatus();//����ʹ���벻ʹ��
					
					//MessageBox("Connect Reader Success!", "info",MB_ICONINFORMATION);
					MessageBox(theApp.g_LoadString("IDWQF_B0013"), theApp.g_LoadString("IDWQF_B0014"), MB_ICONINFORMATION);
					
					CWriteCardDlg * pMainDlg=(CWriteCardDlg *)pMain;
					if ( NULL != pMainDlg )
					{
						pMainDlg->m_Sheet.SetActivePage(1);
					}

				}

				#if defined (ENABLE_PROGRESSDISPTIP)
				::PostMessage(gProgressHwnd, WM_PROGRESS, 1, iCount);
				#endif

				iCount--;
			}
			else
			{

				::KillTimer(gConnectReaderHwnd, TIME_IDENTIFIER_LISTDISP);
				

				#if defined (ENABLE_PROGRESSDISPTIP)
				::PostMessage(gProgressHwnd, WM_PROGRESS, 1, 0);
				#endif

				Sleep(500);
				::PostMessage(gConnectReaderHwnd, WM_CONNECTDATACUSTOM, 0, 1);
			}
		}
		else if ( 1 == ilParam )
		{

			Sleep(500);
			#if defined (ENABLE_PROGRESSDISPTIP)
			::PostMessage(gProgressHwnd, WM_PROGRESS, 2, 0);
			::PostMessage(gProgressHwnd, WM_PROGRESS, 3, 0);
			#endif

			//��ʾû��������
			::PostMessage(gConnectReaderHwnd, WM_CONNECTDATACUSTOM, 3, 0);

		}
		else if ( 2 == ilParam )
		{
			#if defined (ENABLE_PROGRESSDISPTIP)
			//������ʾ�����ֵ
			::PostMessage(gProgressHwnd, WM_GRESSINIT, icnt, iNum);
			::PostMessage(gProgressHwnd, WM_PROGRESS, 0, iCount);
			#endif
			
			//����ʱ��
			::KillTimer(gConnectReaderHwnd, TIME_IDENTIFIER_LISTDISP);
			//����ʱ��
			::SetTimer(gConnectReaderHwnd,TIME_IDENTIFIER_LISTDISP, INTERVALTIME_LISTDISP, CallBack_MyTimeListDisp);
		}
		else if ( 3 == ilParam )
		{
			nThreadFlag	=	FALSE;
			DWORD dwTmpTheaedID = 0;
			hDispThread	=	CreateThread(NULL,0,ThreadListDispPro,this,0, &dwTmpTheaedID);
			if( hDispThread != NULL )
			{		
				nThreadFlag	=	TRUE;
				icnt	=	0;
				iNum	=	100;
				iCount	=	100;
				//�������˰�ť����ֹ�ٵ�
				#if defined (ENABLE_PROGRESSDISPTIP)
				//������ʾ�����ֵ
				::PostMessage(gProgressHwnd, WM_GRESSINIT, icnt, iNum);
				::PostMessage(gProgressHwnd, WM_PROGRESS, 0, iCount);
				#endif
			}
			else
			{
				MessageBox(_T("Create Thread Error!"), _T("Notice"),MB_ICONERROR);
				
			}

		}
	}
	else if ( 1 == iwParam )
	{
		if ( 0 == ilParam )	//��ģ̬����ʾ���ȿ�
		{
			
		}
		else if ( 1 == ilParam )	//ģ̬����ʾ���ȿ�
		{
			//����������
			#if defined (ENABLE_PROGRESSDISPTIP)
			VH73BProgress dlg;
			dlg.DoModal();
			#endif
		}

	}
	else if ( 2 == iwParam )
	{
		if ( 0 == ilParam )
		{
			OnInitUIText();	//��������
		}
		
	}
	else if ( 3 == iwParam )
	{
		if ( 0 == ilParam )
		{
			//��ʾ���Ӳ���
			OnButtonConnectdis();
			//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_B0011"), theApp.g_LoadString("IDWQF_B0012"), MB_OK | MB_ICONERROR);
		}
	}
	else if ( 4 == iwParam )
	{
		if ( 0 == ilParam )
		{
			UpdateStatus();//����ʹ���벻ʹ��
		}
		else
		{
			OnButtonConnectdis();// �ر�
		}
	}
	
	
	return 0;
}


//������ʾ
DWORD WINAPI CConnect::ThreadListDispPro(LPVOID pParam)
{
	CConnect* m_pStandard;
	
	m_pStandard=(CConnect*)pParam;
	
	//��ʼ��ѯ
	::PostMessage(gConnectReaderHwnd, WM_CONNECTDATACUSTOM, 0, 2);
	
	//����������
	#if defined (ENABLE_PROGRESSDISPTIP)
	::SendMessage(gConnectReaderHwnd, WM_CONNECTDATACUSTOM, 1, 1);
	#endif
	
	
	return 0;
	
}


