// ConnectReader.cpp : implementation file
//

#include "stdafx.h"
#include "readerdemo.h"
#include "ConnectReader.h"
#include "ReaderDemoDlg.h"

#include "Progress.h"

#include "./INC/EnumSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define						PLATFORMCTITLE					("626->218")
#define						PLATFORMDTITLE					("218->626")

//////////////////////////////////////////////////////////////////////////
HWND	gConnectReaderHwnd	=	NULL;	//���ӵĴ���ľ��
BOOL    nScanThread			=	FALSE;
DWORD dwThreadId;//�̺߳�  

void PopupMenuConnectReader()
{
	CString strTemp = _T("");
	CPoint point;
	GetCursorPos( & point );
	CMenu menuPopup;
	menuPopup.CreatePopupMenu();
	
	menuPopup.AppendMenu( MF_STRING, 100, _T("one"));
	menuPopup.AppendMenu( MF_STRING, 101, _T("four"));
	#if defined (ENABLEREADERPARAM)
	if ( 1 == iPlatform )//0---626, 1---218
	{
		menuPopup.AppendMenu( MF_STRING, 102, PLATFORMDTITLE);//218��������
	}
	else
	{
		menuPopup.AppendMenu( MF_STRING, 102, PLATFORMCTITLE);//626��������
	}
	#endif

	
	//menuPopup.AppendMenu( MF_SEPARATOR );
	//menuPopup.AppendMenu( MF_STRING, 102, _T("����б�"));
	
	int nCmd = (int) menuPopup.TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, AfxGetMainWnd() );
	switch( nCmd )
	{
	case	100:
		::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,1,0);	//һ��
		break;
	case	101:
		::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,1,1);	//�Ŀ�
		break;

	#if defined (ENABLEREADERPARAM)
	case	102:
		if ( 1 == iPlatform )//0---626, 1---218
		{
			iPlatform	=	0;
			strTemp	=	PLATFORMCTITLE;//626
		}
		else
		{
			iPlatform	=	1;
			strTemp	=	PLATFORMDTITLE;//218
		}
		
		menuPopup.ModifyMenu(2, MF_STRING|MF_BYPOSITION, 102, strTemp);
		//menuPopup.GetMenuString(102, strTemp, MF_STRING);
		::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,11,iPlatform);	//�任��218?626
		break;
	#endif
	
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
int compare00(const void *elem1, const void *elem2)
{   
	return(((CString*)elem2)->CompareNoCase(*((CString*)elem1))*-1);
}
/////////////////////////////////////////////////////////////////////////////
// CConnectReader property page

IMPLEMENT_DYNCREATE(CConnectReader, CPropertyPage)

CConnectReader::CConnectReader() : CPropertyPage(CConnectReader::IDD)
{
	//{{AFX_DATA_INIT(CConnectReader)
	m_Port = 0;
	m_HostPort = 0;
	m_ConnectMode = 1;//0-tcpip,1-rs232,2-485
	m_LanguageIndex	=	0;//0-English,1-chinese
	//}}AFX_DATA_INIT
	m_ScanExitThreadEvent	=	NULL;
}

CConnectReader::~CConnectReader()
{
	
}

void CConnectReader::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectReader)
	DDX_Control(pDX, IDC_LIST1_IPADDR, m_IPList);
	DDX_Control(pDX, IDC_IPADDRESS2_HostIPADDR, m_HostIPAddress);
	DDX_Control(pDX, IDC_IPADDRESS1_IP, m_IPAddress);
	DDX_Control(pDX, IDC_COMBO1_SerialPortA, m_SerialPort);
	DDX_Text(pDX, IDC_EDIT1_ReaderPort, m_Port);
	DDX_Text(pDX, IDC_EDIT2_HostPortA, m_HostPort);
	DDX_Radio(pDX, IDC_RADIO1_TCPIP, m_ConnectMode);
	DDX_Radio(pDX, IDC_RADIO_English, m_LanguageIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectReader, CPropertyPage)
	//{{AFX_MSG_MAP(CConnectReader)
	ON_BN_CLICKED(IDC_BUTTON1_ConnectReader, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2_DisconnectReader, OnButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1_IPADDR, OnClickList1)
	ON_BN_CLICKED(IDC_RADIO1_TCPIP, OnRadio1Tcpip)
	ON_BN_CLICKED(IDC_RADIO2_RS232, OnRadio2Rs232)
	ON_BN_CLICKED(IDC_RADIO3_RS485, OnRadio3Rs485)
	ON_BN_CLICKED(IDC_BUTTON1_ConnectScan, OnBUTTON1ConnectScan)
	ON_BN_CLICKED(IDC_BUTTON1_ScanStop, OnBUTTON1ScanStop)
	ON_CBN_SELCHANGE(IDC_COMBO_SelectAntNum, OnSelchangeCOMBOSelectAntNum)
	ON_BN_CLICKED(IDC_RADIO_English, OnRADIOEnglish)
	ON_BN_CLICKED(IDC_RADIO_Chinese, OnRADIOChinese)
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CONNECTDATACUSTOM, OnConnectdatacustom)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectReader message handlers

void CConnectReader::OnInitUIText()//������ı�����
{
	SetWindowText(theApp.g_LoadString("IDWQB_B0001"));//��д������
	GetDlgItem(IDC_BUTTON1_ConnectReader)->SetWindowText(theApp.g_LoadString("IDWQB_B0002"));//���Ӷ�д��
	GetDlgItem(IDC_BUTTON2_DisconnectReader)->SetWindowText(theApp.g_LoadString("IDWQB_B0003"));//�Ͽ���д��
	GetDlgItem(IDC_STATIC_CONNECTMODE)->SetWindowText(theApp.g_LoadString("IDWQB_B0004"));//����ģʽ
	GetDlgItem(IDC_STATIC_ReaderIPADDR)->SetWindowText(theApp.g_LoadString("IDWQB_B0005"));//��д����ַ
	GetDlgItem(IDC_STATIC_ReaderPort)->SetWindowText(theApp.g_LoadString("IDWQB_B0006"));//��д���˿�
	GetDlgItem(IDC_STATIC_HostIPADDR)->SetWindowText(theApp.g_LoadString("IDWQB_B0007"));//������ַ
	GetDlgItem(IDC_STATIC_HostPort)->SetWindowText(theApp.g_LoadString("IDWQB_B0008"));//�����˿�
	GetDlgItem(IDC_STATIC_SerialPortA)->SetWindowText(theApp.g_LoadString("IDWQB_B0009"));//�˿�
	GetDlgItem(IDC_STATIC_TCPIPA)->SetWindowText(theApp.g_LoadString("IDWQB_B0010"));//TCP/IP
	GetDlgItem(IDC_STATIC_RS232A)->SetWindowText(theApp.g_LoadString("IDWQB_B0011"));//RS232/RS485
	GetDlgItem(IDC_RADIO1_TCPIP)->SetWindowText(theApp.g_LoadString("IDWQB_B0012"));//TCP/IP
	GetDlgItem(IDC_RADIO2_RS232)->SetWindowText(theApp.g_LoadString("IDWQB_B0013"));//RS232
	GetDlgItem(IDC_RADIO3_RS485)->SetWindowText(theApp.g_LoadString("IDWQB_B0014"));//RS485
	GetDlgItem(IDC_STATIC_485Port)->SetWindowText(theApp.g_LoadString("IDWQB_B0015"));//485 Port
	GetDlgItem(IDC_BUTTON1_ConnectScan)->SetWindowText(theApp.g_LoadString("IDWQB_B0016"));//��ʼɨ��
	GetDlgItem(IDC_BUTTON1_ScanStop)->SetWindowText(theApp.g_LoadString("IDWQB_B0017"));//ֹͣɨ��
	GetDlgItem(IDC_STATIC_LANGUAGE)->SetWindowText(theApp.g_LoadString("IDWQB_B0018"));//����
	GetDlgItem(IDC_STATIC_SelectAntNum)->SetWindowText(theApp.g_LoadString("IDWQB_B0024"));//The number of antenna selection
	
	GetDlgItem(IDC_RADIO_English)->SetWindowText(theApp.g_LoadString("IDWQB_B0022"));//English
	GetDlgItem(IDC_RADIO_Chinese)->SetWindowText(theApp.g_LoadString("IDWQB_B0023"));//Simplified Chinese


	((CComboBox*)GetDlgItem(IDC_COMBO_SelectAntNum))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO_SelectAntNum))->AddString(theApp.g_LoadString("IDWQB_B0025"));//
	((CComboBox*)GetDlgItem(IDC_COMBO_SelectAntNum))->AddString(theApp.g_LoadString("IDWQB_B0026"));//
	((CComboBox*)GetDlgItem(IDC_COMBO_SelectAntNum))->SetCurSel(theApp.iantennaIndex);


	CListCtrl *mIPlist = (CListCtrl*)GetDlgItem(IDC_LIST1_IPADDR);
	LVCOLUMN listColumnTemp;
	CString	strText;
	
	strText	=	theApp.g_LoadString("IDWQB_B0019");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(0, &listColumnTemp);
	strText.ReleaseBuffer();

	strText	=	theApp.g_LoadString("IDWQB_B0020");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(1, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_B0021");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(2, &listColumnTemp);
	strText.ReleaseBuffer();
	

}

BOOL CConnectReader::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	UpdateData(TRUE);
	#if defined (ENABLEBPA9PROCTOL)
	m_ConnectMode = 2;//0-tcpip,1-rs232,2-485
	#endif

	// TODO: Add extra initialization here
	gConnectReaderHwnd	=	this->GetSafeHwnd();	//���ӵĴ���ľ��

	DWORD dwStyle = m_IPList.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_IPList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);
	CRect rect;
	m_IPList.GetClientRect(&rect);
	rect.right-=20;
	m_IPList.InsertColumn(0, "No.", LVCFMT_LEFT, int(rect.Width()*2.f/12.f));
	m_IPList.InsertColumn(1, "IP Address", LVCFMT_LEFT, int(rect.Width()*7.f/12.f));
	m_IPList.InsertColumn(2, "Port", LVCFMT_LEFT, int(rect.Width()*3.f/12));

	CStringArray ca;
	int i,k	=	15;
	CString nameList[100],portList[100];

	// Populate the list of serial ports.
	CString	strCom="";
	CArray<SSerInfo,SSerInfo&> asi;
	EnumSerialPorts(asi,FALSE);
	k	=	asi.GetSize();
	//k=GetSystemPorts(nameList,portList);
	for(i=0;i<k;i++)
	{
		int iComIndex =	0;
		int iComIndey =	0;

		strCom	=	asi[i].strFriendlyName;
		iComIndex = strCom.Find("COM");
		iComIndey = iComIndex;
		if ( iComIndex >= 0 )
		{
			iComIndex += 3;
			BOOL bFlag = FALSE;
			char *pp = (char*)(strCom.GetBuffer(MAX_PATH) + iComIndex);
			while ( *pp >= '0' && *pp <= '9' )
			{
				iComIndex++;
				pp++;
				
			}
			
			strCom.ReleaseBuffer();
			strCom = strCom.Mid(iComIndey, iComIndex-iComIndey);

		}
		else
		{
			break;
		}

		//portList[i].Format("COM%d", i+1);
		//m_SerialPort.AddString(strCom);
		ca.Add(strCom);
	}
 
	//�����������Ϊ0,��Ϊԭ���ķ���ö���еĴ���,Ϊ1,���ע����ж����еĴ���
#if 0	//����������������
	//��һ���ж�,add by mqs 20120110
	if ( i != 0 && i >= k )
	{
		qsort(ca.GetData(), ca.GetSize(), sizeof(CString), compare00);
		int nCount = 0;
		for (nCount = 0; nCount < k; nCount++)
		{
			m_SerialPort.AddString(ca.GetAt(nCount));
		}
	}
#else
	int		chi		=	0;
	char **chComm	=	NULL;
	//��ζ�̬�����ά����
	chComm = (char**)malloc(sizeof(char*) * MAX_PATH);
	for (chi = 0; chi < MAX_PATH; chi++)
	{
		chComm[chi]	=	(char*)malloc(sizeof(char) * 16);
	}
				
	short nCurSelected	=	(short)GetSystemPorts(chComm);
	for (chi = 0; chi < nCurSelected; chi++)
	{
		m_SerialPort.AddString(chComm[chi]);
		
	}
	if ( nCurSelected > 0 )
	{
		m_SerialPort.SetCurSel(0);
	}
	

	for (chi = 0; chi < MAX_PATH; chi++)
	{
		free(chComm[chi]);
		chComm[chi]	=	NULL;
	}
	free(chComm);
	chComm	=	NULL;
	
	
#endif
// 	m_SerialPort.AddString("COM1");
//	m_SerialPort.AddString("COM2");
	//SerialPort.AddString("COM12");
	//SerialPort.SetCurSel(0);

	Readini(); 

	CString Result="";   
    WSADATA wsaData;   
    char Name[255];   
    hostent* hostinfo;   
    WORD wVersionRequested=MAKEWORD(2,2);   
    if (WSAStartup(wVersionRequested,&wsaData)==0)
	{   
		if (gethostname(Name,sizeof(Name))==0)
		{   
			hostinfo=gethostbyname(Name);   
            if(hostinfo!=NULL)   
				Result=inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);   
        }   
        WSACleanup();         
    }

	m_HostIPAddress.SetWindowText(Result);
	m_HostPort=5000;
	//�����������
	srand((unsigned)time(NULL));
	m_HostPort	=	1024+rand()%(60000-1024);//����1024-60000֮��Ķ˿�,������Զ�ģʽ�������˿ڳ�ͻ


	//��R2000Э��, �����ú�, ��������ǰ��
	#if defined (ENABLE_R2000_protocol)
	m_ConnectMode = 0;//0-tcpip,1-rs232,2-485
	#endif

	ConnectMode=m_ConnectMode;
	m_LanguageIndex	=	theApp.iLanguage;
	UpdateData(FALSE);

	GetDlgItem(IDC_EDIT1_485PORT)->SetWindowText("1");
	#if defined (ENABLEBPA9PROCTOL)
	GetDlgItem(IDC_EDIT1_485PORT)->SetWindowText("6464");
	#endif
	GetDlgItem(IDC_EDIT1_ReaderPort)->SetWindowText("1969");
	
	//��R2000Э��, �����ú�, ��������ǰ��
	#if defined (ENABLE_R2000_protocol)
	GetDlgItem(IDC_IPADDRESS1_IP)->SetWindowText("192.168.0.178");
	GetDlgItem(IDC_EDIT1_ReaderPort)->SetWindowText("4001");
	#endif


	UpdateStatus();

	hScanThread	=	NULL;
	GetDlgItem(IDC_BUTTON1_ScanStop)->EnableWindow(FALSE);


	//��Ϊ���ã�����Ҫ���ص�
	GetDlgItem(IDC_STATIC_SelectAntNum)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_SelectAntNum)->ShowWindow(SW_HIDE);

	
	//���ӽ���
	::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,2,0);	//convert language

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnectReader::UpdateStatus()
{
	GetDlgItem(IDC_IPADDRESS1_IP)->EnableWindow(!ifConnectReader && !ConnectMode);
	GetDlgItem(IDC_EDIT1_ReaderPort)->EnableWindow(!ifConnectReader && !ConnectMode);
	GetDlgItem(IDC_IPADDRESS2_HostIPADDR)->EnableWindow(!ifConnectReader && !ConnectMode);
	GetDlgItem(IDC_EDIT2_HostPortA)->EnableWindow(!ifConnectReader && !ConnectMode);
	GetDlgItem(IDC_BUTTON1_ConnectReader)->EnableWindow(!ifConnectReader);
	GetDlgItem(IDC_BUTTON2_DisconnectReader)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_LIST1_IPADDR)->EnableWindow(!ifConnectReader && !ConnectMode);	
	GetDlgItem(IDC_COMBO1_SerialPortA)->EnableWindow(!ifConnectReader && ConnectMode);
	GetDlgItem(IDC_BUTTON1_ConnectScan)->EnableWindow(!ifConnectReader && (ConnectMode==0));
	
	//ֻ��485ʱ������
	GetDlgItem(IDC_EDIT1_485PORT)->EnableWindow(!ifConnectReader && (ConnectMode==2));
}

void CConnectReader::Readini()
{
	//ȡ��Ӧ�ó���ǰ·��
	CString  FilePath;
	FilePath+=".\\IPAddress.ini";

	CString strSection="Number";
	CString strSectionKey="num";
	char inBuf[80];
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 

	int i,num;
	CString str;
	num=atoi(inBuf);
	for(i=0;i<num;i++)
	{
		//����ʵ��������Ƿ�Ҫ��
		#if 0
		str="";
		str.Format("%d",i+1);
		m_IPList.InsertItem(i,str);
		strSection="IP"+str;

		strSectionKey="Address";
		GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath);
		m_IPList.SetItemText(i,1,inBuf);

		strSectionKey="port";
		GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath);
		m_IPList.SetItemText(i,2,inBuf);
		#endif
	}
}

void CConnectReader::OnButton1() 
{
	int i = 0;
	UpdateData(TRUE);
	DWORD dwIPAddress;
	CString m_strIPAddress,m_strHostIPAddress;
	CString strTemp;
	int iRate = 0;

	//��ʼ������
	int iiPos = 1;
	int iiMax = 6;
	if ( 1 == iPlatform )//218
	{
		iiMax = 7;
	}
	if ( NULL != pgDlgPress )
	{
		pgDlgPress->ShowWindow(SW_SHOW);
		pgDlgPress->m_Progress.SetRange32(0, iiMax);
		pgDlgPress->m_Progress.SetStep(1);
		pgDlgPress->m_Progress.SetPos(iiPos++);
		
	}

	GetDlgItem(IDC_EDIT1_485PORT)->GetWindowText(strTemp);
	RS485Address	=	atoi(strTemp);
	#if defined (ENABLEBPA9PROCTOL)
	RS485Address	=	0;
	iRate	=	atoi(strTemp.Left(2));
	*((char*)&RS485Address + 0)	=	iRate;
	iRate	=	atoi(strTemp.Right(2));
	*((char*)&RS485Address + 1)	=	iRate;
	#endif

	iRate	=	0;

	m_IPAddress.GetAddress(dwIPAddress);
	m_strIPAddress.Format("%d.%d.%d.%d",
		HIBYTE(HIWORD(dwIPAddress)),
		LOBYTE(HIWORD(dwIPAddress)),
		HIBYTE(LOWORD(dwIPAddress)),
		LOBYTE(LOWORD(dwIPAddress))
		);
	m_HostIPAddress.GetAddress(dwIPAddress);
	m_strHostIPAddress.Format("%d.%d.%d.%d",
		HIBYTE(HIWORD(dwIPAddress)),
		LOBYTE(HIWORD(dwIPAddress)),
		HIBYTE(LOWORD(dwIPAddress)),
		LOBYTE(LOWORD(dwIPAddress))
		);

	apiReturn res	=	_no_scanner;
	char port[32]	=	{0};
	char IPAddr[32]	=	{0};
	char hostIP[32]	=	{0};
	switch(ConnectMode)
	{
	case 0://����
		RS485Address	=	0;
		wsprintf(IPAddr, "%s",LPCTSTR(m_strIPAddress));
		wsprintf(hostIP, "%s",LPCTSTR(m_strHostIPAddress));
		res=Net_ConnectScanner(&m_hSocket,IPAddr,m_Port,hostIP,m_HostPort);
		break;
	case 1://RS232
		RS485Address	=	0;
		m_SerialPort.GetWindowText(strTemp);
		if ( m_SerialPort.GetCurSel() < 0 )
		{
			break;
		}

		m_SerialPort.GetLBText(m_SerialPort.GetCurSel(),IPAddr);
		wsprintf(port, "\\\\.\\%s",IPAddr);
		res=ConnectScanner(&m_hScanner,port, &iRate);
		break;
	case 2://RS485
		if ( m_SerialPort.GetCurSel() < 0 )
		{
			break;
		}

		m_SerialPort.GetLBText(m_SerialPort.GetCurSel(),IPAddr);
		wsprintf(port, "\\\\.\\%s",IPAddr);

		#if defined (ENABLEBPA9PROCTOL)
		res=ConnectScannerBPA(&m_hScanner, port, 9600, RS485Address);
		#else
		res=ConnectScanner485(&m_hScanner,port,0,RS485Address);
		#endif



		#if defined (ENABLEBPA9PROCTOL)
		if (res==_OK)
		{
			//�����ˣ�ѡ���ĸ�ģʽͨѸ���
			GetDlgItem(IDC_RADIO1_TCPIP)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO2_RS232)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO3_RS485)->EnableWindow(FALSE);

			GetDlgItem(IDC_BUTTON1_ConnectReader)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON2_DisconnectReader)->EnableWindow(TRUE);

			MessageBox(theApp.g_LoadString("IDWQB_B0037"), theApp.g_LoadString("IDWQB_B0038"),MB_ICONINFORMATION);
			

			//ifConnectReader=1;
			//NewConnect=1;
			
		//	UpdateStatus();
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->ShowWindow(SW_HIDE);
			}

			CReaderDemoDlg * pMainDlg=(CReaderDemoDlg *)pMain;
			pMainDlg->m_Sheet.SetActivePage(5);
			

		}
		else
		{
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->ShowWindow(SW_HIDE);
			}
			MessageBox(theApp.g_LoadString("IDWQB_B0039"), theApp.g_LoadString("IDWQB_B0040"),MB_ICONWARNING);
			OnButton2();//���ر�
		}
		return;
		#endif

		break;
	}

	if (res==_OK)
	{
		//�����ˣ�ѡ���ĸ�ģʽͨѸ���
		GetDlgItem(IDC_RADIO1_TCPIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2_RS232)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO3_RS485)->EnableWindow(FALSE);
		
		//#####################################################################
		//add by martrin 20140110���ӻ�Ϊ˹������ǰ��Reader2600,���ڻ����Ŀڵ�
		//R2000�ģ�����Ҫ����R2000Э��, ������R2000, ��������ǰ��
		//��R2000Э��, �����ú�, ��������ǰ��
		#if defined (ENABLE_R2000_protocol)
		
		#else
		//������ʾ
		if ( NULL != pgDlgPress )
		{
			pgDlgPress->m_Progress.SetPos(iiPos++);
		}
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		for (i = 0; i < 5; i++)
		{
			//ȡ�ĸ��汾
			switch(ConnectMode)
			{
			case 0://����
				res=Net_GetReaderVersion(m_hSocket,&m_HardVersion,&m_SoftVersion);
				break;
			case 1://RS232
				res=GetReaderVersion(m_hScanner,&m_HardVersion,&m_SoftVersion,0);
				strTemp.Format("h:%d,s:%d", m_HardVersion, m_SoftVersion);
				//AfxMessageBox(strTemp);
				break;
			case 2://RS485
				res=GetReaderVersion(m_hScanner,&m_HardVersion,&m_SoftVersion,RS485Address);
				break;
			}

			if ( res == _OK )
			{
				break;
			}
			else 
			{
				if ( 2 == ConnectMode )
				{
					Sleep(ReadRS485SleepTime);
				}
			}

		}
		if (res!=_OK)
		{
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->ShowWindow(SW_HIDE);
			}
			//MessageBox("Connect Reader Fail!(Version)","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_B0027"), theApp.g_LoadString("IDWQB_B0028"),MB_ICONWARNING);
			OnButton2();//���ر�
			return;
		}

		
		//������ʾ
		if ( NULL != pgDlgPress )
		{
			pgDlgPress->m_Progress.SetPos(iiPos++);
		}
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		for (i = 0; i < 5; i++)
		{
			//ȡ��������
			switch(ConnectMode)
			{
			case 0://����
				res=Net_ReadBasicParam(m_hSocket, gBasicParam);
				break;
			case 1://RS232
				res=ReadBasicParam(m_hScanner, gBasicParam, 0);
				break;
			case 2://RS485
				res=ReadBasicParam(m_hScanner, gBasicParam, RS485Address);
				break;
			}
			
			if ( res == _OK )
			{
				break;
			}
			else 
			{
				if ( 2 == ConnectMode )
				{
					Sleep(ReadRS485SleepTime);
				}
			}

		}
		if (res!=_OK)
		{
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->ShowWindow(SW_HIDE);
			}
			//MessageBox("Connect Reader Fail!(BasicParam)","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_B0029"), theApp.g_LoadString("IDWQB_B0030"),MB_ICONWARNING);
			OnButton2();//���ر�
			return;
		}


		
		//;1---����r1000,0----ֻ��1100,1400
		int iTemp	=	GetPrivateProfileInt(_T("SETTING"), _T("Reader1000"), 0,  theApp.strConfigPath);
		if ( 0 == iTemp )
		{
			//������ʾ
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->m_Progress.SetPos(iiPos++);
			}
			if ( 2 == ConnectMode )
			{
				Sleep(ReadRS485SleepTime);
			}
			for (i = 0; i < 5; i++)
			{
				////ȡ�ĸ����ҵ�Ƶ��
				switch(ConnectMode)
				{
				case 0://����
					res=Net_GetFrequencyRange(m_hSocket, &gFre);
					break;
				case 1://RS232
					res=GetFrequencyRange(m_hScanner, &gFre, 0);
					break;
				case 2://RS485
					res=GetFrequencyRange(m_hScanner, &gFre, RS485Address);
					break;
				}

				if ( res == _OK )
				{
					break;
				}
				else 
				{
					if ( 2 == ConnectMode )
					{
						Sleep(ReadRS485SleepTime);
					}
				}

			}
			if (res!=_OK)
			{
				if ( NULL != pgDlgPress )
				{
					pgDlgPress->ShowWindow(SW_HIDE);
				}
				//MessageBox("Connect Reader Fail!(Frequency)","Warring",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_B0031"), theApp.g_LoadString("IDWQB_B0032"),MB_ICONWARNING);
				OnButton2();//���ر�
				return;
			}
			

			//������ʾ
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->m_Progress.SetPos(iiPos++);
			}
			if ( 2 == ConnectMode )
			{
				Sleep(ReadRS485SleepTime);
			}
			for (i = 0; i < 5; i++)
			{
				//ȡ�Զ�����
				switch(ConnectMode)
				{
				case 0://����
					res=Net_ReadAutoParam(m_hSocket, gAutoParam);
					break;
				case 1://RS232
					res=ReadAutoParam(m_hScanner, gAutoParam, 0);
					break;
				case 2://RS485
					res=ReadAutoParam(m_hScanner, gAutoParam, RS485Address);
					break;
				}

				if ( res == _OK )
				{
					break;
				}
				else 
				{
					if ( 2 == ConnectMode )
					{
						Sleep(ReadRS485SleepTime);
					}
				}

			}
			if (res!=_OK)
			{
				if ( NULL != pgDlgPress )
				{
					pgDlgPress->ShowWindow(SW_HIDE);
				}
				//MessageBox("Connect Reader Fail!(AutoParam)","Warring",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_B0033"), theApp.g_LoadString("IDWQB_B0034"),MB_ICONWARNING);
				OnButton2();//���ر�
				return;
			}
		}
		

		//������ʾ
		if ( NULL != pgDlgPress )
		{
			pgDlgPress->m_Progress.SetPos(iiPos++);
		}
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		for (i = 0; i < 5; i++)
		{
			//ȡ��д��ID
			switch(ConnectMode)
			{
			case 0://����
				res=Net_GetReaderID(m_hSocket, gReaderID);
				break;
			case 1://RS232
				res=GetReaderID(m_hScanner, gReaderID, 0);
				break;
			case 2://RS485
				res=GetReaderID(m_hScanner, gReaderID, RS485Address);
				break;
			}

			if ( res == _OK )
			{
				break;
			}
			else 
			{
				if ( 2 == ConnectMode )
				{
					Sleep(ReadRS485SleepTime);
				}
			}

		}
		if (res!=_OK)
		{
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->ShowWindow(SW_HIDE);
			}
			//MessageBox("Connect Reader Fail!(GetReaderID)","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_B0035"), theApp.g_LoadString("IDWQB_B0036"),MB_ICONWARNING);
			OnButton2();//���ر�
			return;
		}

		if ( 1 == iPlatform )//218
		{
			//������ʾ
			if ( NULL != pgDlgPress )
			{
				pgDlgPress->m_Progress.SetPos(iiPos++);
			}
			if ( 2 == ConnectMode )
			{
				Sleep(ReadRS485SleepTime);
			}
			for (i = 0; i < 5; i++)
			{
				//ȡģ��İ汾,ͬʱȡƵ��
				switch(ConnectMode)
				{
				case 0:
					res=Net_GetModuleVer(m_hSocket,bModuleVer);
					res=Net_GetFrequencyRangeEx(m_hSocket, &FreT[0]);//ȡ�ĸ����ҵ�Ƶ��,87H
					break;
				case 1:
					res=GetModuleVer(m_hScanner,bModuleVer,0);
					res=GetFrequencyRangeEx(m_hScanner, &FreT[0],0);//ȡ�ĸ����ҵ�Ƶ��,87H
					break;
				case 2:
					res=GetModuleVer(m_hScanner,bModuleVer,RS485Address);
					Sleep(ReadRS485SleepTime);
					res=GetFrequencyRangeEx(m_hScanner, &FreT[0],RS485Address);//ȡ�ĸ����ҵ�Ƶ��,87H
					break;
				}
				
				if ( res == _OK )
				{
					break;
				}
				else 
				{
					if ( 2 == ConnectMode )
					{
						Sleep(ReadRS485SleepTime);
					}
				}
				
			}
			if (res!=_OK)
			{
				if ( NULL != pgDlgPress )
				{
					pgDlgPress->ShowWindow(SW_HIDE);
				}
				MessageBox("Connect Reader Fail!(GetModuleVer)","Warring",MB_ICONWARNING);
				OnButton2();//���ر�
				//MessageBox(theApp.g_LoadString("IDWQB_B0035"), theApp.g_LoadString("IDWQB_B0036"),MB_ICONWARNING);
				return;
			}
		}

		//������ʾ
		if ( NULL != pgDlgPress )
		{
			pgDlgPress->m_Progress.SetPos(iiPos++);
		}
		//(6)��д��������ʽ��0-������ʽ��1-���ʽ
		if ( 0 == gBasicParam->WorkMode )
		{
			if ( 2 == ConnectMode )
			{
				Sleep(ReadRS485SleepTime);
			}
			//�����������ʽ�����Ϊ����ģʽ
			for (i = 0; i < 5; i++)
			{
				//0-������ʽ��1-���ʽ
				switch(ConnectMode)
				{
				case 0://����
					res=Net_AutoMode(m_hSocket,1);
					break;
				case 1://RS232
					res=AutoMode(m_hScanner,1,0);
					break;
				case 2://RS485
					res=AutoMode(m_hScanner,1,RS485Address);
					break;
				}

				if ( res == _OK )
				{
					break;
				}
				else 
				{
					if ( 2 == ConnectMode )
					{
						Sleep(ReadRS485SleepTime);
					}
				}

			}

			if(res==_OK)
			{
				
			}
			else
			{
				if ( NULL != pgDlgPress )
				{
					pgDlgPress->ShowWindow(SW_HIDE);
				}
				MessageBox(theApp.g_LoadString("IDWQB_C0112"), theApp.g_LoadString("IDWQB_C0113"), MB_ICONWARNING);
				OnButton2();//���ر�
				return;
			}
			
		}

		//��R2000Э��, �����ú�, ��������ǰ��
		#endif
		//���ӳɹ������ص�
		if ( NULL != pgDlgPress )
		{
			pgDlgPress->ShowWindow(SW_HIDE);
		}
		

		ifConnectReader=1;
		NewConnect=1;

		UpdateStatus();
		//MessageBox("Connect Reader Success!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_B0037"), theApp.g_LoadString("IDWQB_B0038"),MB_ICONINFORMATION);
		
		CReaderDemoDlg * pMainDlg=(CReaderDemoDlg *)pMain;
		#if defined (ENABLEREADERMODES)
		//Сģ�����
		pMainDlg->m_Sheet.SetActivePage(4);
		#elif defined (ENABLErubbish)
		//�����������
		pMainDlg->m_Sheet.SetActivePage(4);
		//::PostMessage(gMainHwnd, WM_LISTUSERDATA, 3, 4);
		//��R2000Э��, �����ú�, ��������ǰ��
		#elif defined (ENABLE_R2000_protocol)
		pMainDlg->m_Sheet.SetActivePage(2);
		#else
		pMainDlg->m_Sheet.SetActivePage(1);
		#endif

		
	}
	else
	{
		if ( NULL != pgDlgPress )
		{
			pgDlgPress->ShowWindow(SW_HIDE);
		}
		//MessageBox("Connect Reader Fail!","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_B0039"), theApp.g_LoadString("IDWQB_B0040"),MB_ICONWARNING);
	}

}

void CConnectReader::OnButton2() 
{
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
	ifConnectReader=0;
	NewConnect=0;
	m_HardVersion=0;
	m_SoftVersion=0;
	m_hScanner	=	NULL;
	UpdateStatus();

	GetDlgItem(IDC_RADIO1_TCPIP)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2_RS232)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO3_RS485)->EnableWindow(TRUE);
}

void CConnectReader::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos;
	pos=m_IPList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		while (pos)
		{
			int nItemSelected = m_IPList.GetNextSelectedItem(pos);
			m_Port=atoi(m_IPList.GetItemText(nItemSelected,2));
			m_IPAddress.SetWindowText(m_IPList.GetItemText(nItemSelected,1));
	
			UpdateData(FALSE);
		}
	}
	
	*pResult = 0;
}


void CConnectReader::OnRadio1Tcpip() 
{
	// TODO: Add your control notification handler code here
	//tcpip��ʽ
	UpdateData(TRUE);
	ConnectMode=m_ConnectMode;
	UpdateData(FALSE);

	UpdateStatus();
}

void CConnectReader::OnRadio2Rs232() 
{
	// TODO: Add your control notification handler code here
	//RS232��ʽ
	UpdateData(TRUE);
	ConnectMode=m_ConnectMode;
	UpdateData(FALSE);

	UpdateStatus();
}

void CConnectReader::OnRadio3Rs485() 
{
	// TODO: Add your control notification handler code here
	//485��ʽ
	UpdateData(TRUE);
	ConnectMode=m_ConnectMode;
	UpdateData(FALSE);

	UpdateStatus();
}

void CConnectReader::OnBUTTON1ConnectScan() 
{
	// TODO: Add your control notification handler code here
	//ɨ��˿�
	//((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1_IP))->SetAddress(recvbuf[3],recvbuf[4],recvbuf[5],recvbuf[6]);
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1_IP))->SetWindowText("");
	((CEdit*)GetDlgItem(IDC_EDIT1_ReaderPort))->SetWindowText("");


	if ( NULL == m_ScanExitThreadEvent )
	{
		m_ScanExitThreadEvent	=	CreateEvent(NULL,FALSE,FALSE,NULL);
	}
	hScanThread	=	CreateThread(NULL,0,ScanPortIpThread,this,0,&dwThreadId);
	if( hScanThread != NULL )
	{		
		nScanThread	=	TRUE;
		GetDlgItem(IDC_BUTTON1_ConnectScan)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1_ScanStop)->EnableWindow(TRUE);
		
	}
	else
	{
		//MessageBox("Create ScanPortIpThread Error!","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_B0041"), theApp.g_LoadString("IDWQB_B0042"),MB_ICONERROR);
	}

	return;
	
}

void CConnectReader::OnBUTTON1ScanStop() 
{
	// TODO: Add your control notification handler code here
	nScanThread	=	FALSE;
	GetDlgItem(IDC_BUTTON1_ConnectScan)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1_ScanStop)->EnableWindow(FALSE);
	if ( hScanThread != NULL )
	{

		if ( NULL != m_ScanExitThreadEvent )
		{
			SetEvent(m_ScanExitThreadEvent);
			Sleep(100);
			CloseHandle(m_ScanExitThreadEvent);
			m_ScanExitThreadEvent	=	NULL;
		}
		//WaitForSingleObject(hScanThread,500);
		CloseHandle(hScanThread);
		hScanThread	=	NULL;
	}

}



//�Զ�ģʽ�¶��̺߳���
DWORD WINAPI CConnectReader::ScanPortIpThread(LPVOID pParam)
{
	CConnectReader* m_pStandard;
	
	m_pStandard=(CConnectReader*)pParam;

	CString strTemp;
	SOCKET  hGetSocket=INVALID_SOCKET;
	SOCKADDR_IN addrSock;
	int retval;
	int iRecvLen	=	0;
	
	iRecvLen	=	sizeof(SOCKADDR);
	
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2,2),&WSAData)!=0)
	{
		WSACleanup();
		return _init_net_error;
	}

	hGetSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hGetSocket==INVALID_SOCKET)
	{
		nScanThread	=	FALSE;
		((CButton*)m_pStandard->GetDlgItem(IDC_BUTTON1_ConnectScan))->EnableWindow(TRUE);
		return 1;
	}
	
	addrSock.sin_family=AF_INET;
	addrSock.sin_port=htons(4444);
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	retval=bind(hGetSocket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(SOCKET_ERROR==retval)
	{
		closesocket(hGetSocket);
		nScanThread	=	FALSE;
		((CButton*)m_pStandard->GetDlgItem(IDC_BUTTON1_ConnectScan))->EnableWindow(TRUE);
		return 1;
	}
	DWORD u1 = 1;
	ioctlsocket(hGetSocket, FIONBIO, &u1);//������

	//test
	//::SendMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,0,0);	//
#if 1
	while( nScanThread )
	{	
		int recv_len=0;
		BYTE recvbuf[2048]	=	{0};
		BYTE recvtmp[32]	=	{0};
		int port;
		
		
		//Sleep(5);
		if (WaitForSingleObject(m_pStandard->m_ScanExitThreadEvent, 0) == WAIT_OBJECT_0)
		{
			nScanThread = FALSE;
			break;
		}

			
		memset(recvbuf,0,32);
		//recv_len=recv(hGetSocket,(char*)recvbuf,32,0);
		recv_len	=	recvfrom(hGetSocket,(char*)recvbuf,2048,0,(SOCKADDR*)&addrSock,&iRecvLen);
		if((recv_len<16)||(recv_len>20))
		{
			continue;
		}
			
		//m_IPAddress.SetAddress(recvbuf[3],recvbuf[4],recvbuf[5],recvbuf[6]);
		port=recvbuf[7];
		port=(port<<8)+recvbuf[8];

		strTemp.Format("%d.%d.%d.%d", recvbuf[3],recvbuf[4],recvbuf[5],recvbuf[6]);
		BOOL bFlag = FALSE;
		int k = ((CListCtrl*)m_pStandard->GetDlgItem(IDC_LIST1_IPADDR))->GetItemCount();
		for ( int i = 0; i < k; i++)
		{
			((CListCtrl*)m_pStandard->GetDlgItem(IDC_LIST1_IPADDR))->GetItemText(i,1,(char*)recvtmp, 32);
			if ( strTemp.Find((char*)recvtmp) >= 0 )
			{
				bFlag = TRUE;
				break;
			}

		}

		if ( FALSE == bFlag )
		{
			strTemp.Format("%d",k+1);
			((CListCtrl*)m_pStandard->GetDlgItem(IDC_LIST1_IPADDR))->InsertItem(k, strTemp);
			
			strTemp.Format("%d.%d.%d.%d", recvbuf[3],recvbuf[4],recvbuf[5],recvbuf[6]);
			((CListCtrl*)m_pStandard->GetDlgItem(IDC_LIST1_IPADDR))->SetItemText(k,1,strTemp);
			
			strTemp.Format("%d", port);
			((CListCtrl*)m_pStandard->GetDlgItem(IDC_LIST1_IPADDR))->SetItemText(k,2,strTemp);


			((CIPAddressCtrl*)m_pStandard->GetDlgItem(IDC_IPADDRESS1_IP))->SetAddress(recvbuf[3],recvbuf[4],recvbuf[5],recvbuf[6]);
			
			port=recvbuf[7];
			port=(port<<8)+recvbuf[8];
			
			//m_Port=port;
			strTemp.Format("%d", port);
			
			((CEdit*)m_pStandard->GetDlgItem(IDC_EDIT1_ReaderPort))->SetWindowText(strTemp);

		}
		

		//nScanThread	=	FALSE;

	}
#endif

	closesocket(hGetSocket);
	nScanThread	=	FALSE;
	((CButton*)m_pStandard->GetDlgItem(IDC_BUTTON1_ConnectScan))->EnableWindow(TRUE);

	return 0;
}

void CConnectReader::OnSelchangeCOMBOSelectAntNum() 
{
	// TODO: Add your control notification handler code here
	theApp.iantennaIndex	=	((CComboBox*)GetDlgItem(IDC_COMBO_SelectAntNum))->GetCurSel();

}



void CConnectReader::OnRADIOEnglish() 
{
	// TODO: Add your control notification handler code here
	BOOL bFlag = FALSE;
	theApp.iLanguage	=	0;
	
	if ( theApp.iLanguage == 0 )	//Ӣ��
	{
		theApp.strTempPath = theApp.strIniDir;
		theApp.strTempPath += "ReaderEnglish.ini";
		theApp.MakeResource(theApp.iLanguage, theApp.strIniDir, &g_lpBuf);
		bFlag	=	TRUE;
	}
	else if ( theApp.iLanguage == 1 ) //����
	{
		theApp.strTempPath = theApp.strIniDir;
		theApp.strTempPath += "ReaderChinese.ini";
		theApp.MakeResource(theApp.iLanguage, theApp.strIniDir, &g_lpBuf);
		bFlag	=	TRUE;
	}
	
	if ( bFlag )
	{
		//��ǰ������
		::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
		//���ӽ���
		::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,2,0);	//convert language
		//����ҳ
		::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,2,0);	//convert language
		::PostMessage(gReaderDParaHwnd,WM_READERPARMDATAMSG,2,0);	//convert language
		//6C����ҳ
		::PostMessage(gEcpISO6C,WM_EPC6CTRANDATAMSG,2,0);	//convert language
		//6B����ҳ
		::PostMessage(gEcpISO6B,WM_USERTIMERDATATRan,2,0);	//convert language
		//Output�������ҳ
		::PostMessage(gOutputHwnd,WM_OUTPUTTESTDATAMSG,2,0);	//convert language


		#if defined (ENABLEBPA9PROCTOL)
		//BPA9 test
		::PostMessage(gDlgBpa9,WM_DLGBPA9DATAMSG,2,0);	//convert language
		#endif
		
	}
	
	return;
}

void CConnectReader::OnRADIOChinese() 
{
	// TODO: Add your control notification handler code here
	BOOL bFlag = FALSE;
	theApp.iLanguage	=	1;
	
	if ( theApp.iLanguage == 0 )	//Ӣ��
	{
		theApp.strTempPath = theApp.strIniDir;
		theApp.strTempPath += "ReaderEnglish.ini";
		theApp.MakeResource(theApp.iLanguage, theApp.strIniDir, &g_lpBuf);
		bFlag	=	TRUE;
	}
	else if ( theApp.iLanguage == 1 ) //����
	{
		theApp.strTempPath = theApp.strIniDir;
		theApp.strTempPath += "ReaderChinese.ini";
		theApp.MakeResource(theApp.iLanguage, theApp.strIniDir, &g_lpBuf);
		bFlag	=	TRUE;
	}
	
	if ( bFlag )
	{
		//��ǰ������
		::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
		//���ӽ���
		::PostMessage(gConnectReaderHwnd,WM_CONNECTDATACUSTOM,2,0);	//convert language
		//����ҳ
		::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,2,0);	//convert language
		::PostMessage(gReaderDParaHwnd,WM_READERPARMDATAMSG,2,0);	//convert language
		//6C����ҳ
		::PostMessage(gEcpISO6C,WM_EPC6CTRANDATAMSG,2,0);	//convert language
		//6B����ҳ
		::PostMessage(gEcpISO6B,WM_USERTIMERDATATRan,2,0);	//convert language
		//Output�������ҳ
		::PostMessage(gOutputHwnd,WM_OUTPUTTESTDATAMSG,2,0);	//convert language
		

		#if defined (ENABLEBPA9PROCTOL)
		//BPA9 test
		::PostMessage(gDlgBpa9,WM_DLGBPA9DATAMSG,2,0);	//convert language
		#endif

	}
	
	return;
}

void CConnectReader::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PopupMenuConnectReader();
	CPropertyPage::OnRButtonDown(nFlags, point);
}

//WM_CONNECTDATACUSTOM
afx_msg LRESULT CConnectReader::OnConnectdatacustom(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 2 == iwParam )
	{
		OnInitUIText();	//��������
	}
	else if ( 0 == iwParam )
	{
		if ( 0 == ilParam )
		{
			//test
			//CProgress dlg;
			//dlg.DoModal();
		}
	}
	else if ( 1 == iwParam )
	{
		if ( 0 == ilParam )
		{
			//һ��
			theApp.iantennaIndex	=	0;	//ѡ�ĸ�����,0-һ������,1-�ĸ�����
			OnInitUIText();	//��������
			::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
		}
		else if ( 1 == ilParam )
		{
			//�Ŀ�
			theApp.iantennaIndex	=	1;	//ѡ�ĸ�����,0-һ������,1-�ĸ�����
			OnInitUIText();	//��������
			::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
		}
		char chTemp[10];
		//iantennaIndex	=	0;	//ѡ�ĸ�����,0-һ������,1-�ĸ�����
		sprintf(chTemp, "%d", theApp.iantennaIndex);
		WritePrivateProfileString(_T("SETTING"), _T("Antenna"), chTemp,  theApp.strConfigPath);
	}
	else if ( 11 == iwParam )
	{
		//�л�ƽ̨
		char chTemp[10];
		//iPlatform	=	0;	//0---626, 1---218
		sprintf(chTemp, "%d", iPlatform);
		WritePrivateProfileString(_T("SETTING"), _T("Platform"), chTemp,  theApp.strConfigPath);

		//��һ�¶Ͽ�
		OnButton2();

		::PostMessage(gMainHwnd,WM_LISTUSERDATA,11,ilParam);	//218��626�໥�л�
	}
	
	return 0;
}





void CConnectReader::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	nScanThread	=	FALSE;
	if ( hScanThread != NULL )
	{
		if ( NULL != m_ScanExitThreadEvent )
		{
			SetEvent(m_ScanExitThreadEvent);
			Sleep(100);
			CloseHandle(m_ScanExitThreadEvent);
			m_ScanExitThreadEvent	=	NULL;
		}
		//WaitForSingleObject(hScanThread,500);
		CloseHandle(hScanThread);
		hScanThread	=	NULL;
	}
}
