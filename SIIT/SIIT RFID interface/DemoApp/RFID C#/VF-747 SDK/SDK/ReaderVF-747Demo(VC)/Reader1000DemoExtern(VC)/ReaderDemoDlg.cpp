// ReaderDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "ReaderDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
HWND	gMainHwnd	=	NULL;////������ҳ��

//////////////////////////////////////////////////////////////////////////
void PopupMenu()
{
	CPoint point;
	GetCursorPos( & point );
	CMenu menuPopup;
	menuPopup.CreatePopupMenu();
	
	menuPopup.AppendMenu( MF_STRING, 100, _T("��ʾ"));	
	menuPopup.AppendMenu( MF_SEPARATOR );
	menuPopup.AppendMenu( MF_STRING, 101, _T("�˳�"));
	
	int nCmd = (int) menuPopup.TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, AfxGetMainWnd() );
	switch( nCmd )
	{
	case 100:
		::PostMessage(gMainHwnd,WM_MYDATAMSG,   0,0);
		break;
	case 101:
		//AfxMessageBox(_T("�˳�"));
		//CMainFrame::OnEditComm ();
		//::SendMessage(FrameHwnd, WM_CLOSE, 0, 0);
		::PostMessage(gMainHwnd,WM_MYDATAMSG,   0,1);
		break;	
		
	default:
		break;
	}
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderDemoDlg dialog

CReaderDemoDlg::CReaderDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReaderDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReaderDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	bDispFlag	=	SW_SHOW;	//SW_SHOWΪ��ʾ��SW_HIDEΪ����

}

void CReaderDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReaderDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReaderDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CReaderDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_LISTUSERDATA, OnListuserdata)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderDemoDlg message handlers
void CReaderDemoDlg::OnInitUIText()//������ı�����
{
	SetWindowText(theApp.g_LoadString("IDWQB_A0001"));//������ı���
	if ( theApp.iantennaIndex	==	0)	//ѡ�ĸ�����,0-һ������,1-�ĸ�����
	{
		SetWindowText(theApp.g_LoadString("IDWQB_A0001"));//������ı���
	}
	else if ( theApp.iantennaIndex	==	1 )
	{
		SetWindowText(theApp.g_LoadString("IDWQB_A0002"));//������ı���
	}
	
	#if defined (ENABLETXVERCHANGE)
	SetWindowText("��д��");//������ı���
	#endif

	if ( 1 == iPlatform )//0---626, 1---218
	{
		CString strTitle;
		//���ݿ�ʵ����
		GetPrivateProfileString("Setting","Title","Demo",strTitle.GetBuffer(MAX_PATH),MAX_PATH, theApp.strConfigPath);
		strTitle.ReleaseBuffer();
		
		strTitle += _T("  ");
		//strTitle += _T("V1.57");
		strTitle += theApp.g_LoadString("IDWQC_A0003");//�汾		
		SetWindowText(strTitle);
	}

	CString strText;
	int iIndex = 0;
	CTabCtrl *pTab = m_Sheet.GetTabControl();
	
	TC_ITEM ti;
	ti.mask = TCIF_TEXT;
	strText	=	theApp.g_LoadString("IDWQB_B0001");//��д�����Ӳ���
	ti.pszText = strText.GetBuffer(MAX_PATH);
	strText.ReleaseBuffer();
	VERIFY (pTab->SetItem (iIndex++, &ti));
	
	#if defined (ENABLEREADERPARAM)
	strText	=	theApp.g_LoadString("IDWQB_C0001");//��д����������
	ti.pszText = strText.GetBuffer(MAX_PATH);
	strText.ReleaseBuffer();
	VERIFY (pTab->SetItem (iIndex++, &ti));
	#endif
	
	strText	=	theApp.g_LoadString("IDWQB_D0001");//ISO18000-6C����
	ti.pszText = strText.GetBuffer(MAX_PATH);
	strText.ReleaseBuffer();
	VERIFY (pTab->SetItem (iIndex++, &ti));
	
	strText	=	theApp.g_LoadString("IDWQB_E0001");//ISO18000-6B����
	ti.pszText = strText.GetBuffer(MAX_PATH);
	strText.ReleaseBuffer();
	VERIFY (pTab->SetItem (iIndex++, &ti));
	
	
	#if defined (ENABLEREADERMODES)
	//Сģ�����
	strText	=	theApp.g_LoadString("IDWQB_F0001");//�������
	#elif defined (ENABLErubbish)
	//�����������
	strText	=	"����";//�������
	#else
	strText	=	theApp.g_LoadString("IDWQB_F0001");//�������
	#endif

	ti.pszText = strText.GetBuffer(MAX_PATH);
	strText.ReleaseBuffer();
	VERIFY (pTab->SetItem (iIndex++, &ti));
	
	#if defined (ENABLEBPA9PROCTOL)
	strText	=	theApp.g_LoadString("IDWQB_G0001");//BPA9 test
	ti.pszText = strText.GetBuffer(MAX_PATH);
	strText.ReleaseBuffer();
	VERIFY (pTab->SetItem (iIndex++, &ti));
	#endif

}

BOOL CReaderDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	gMainHwnd	=	this->GetSafeHwnd();
	CString strText;
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);


	//strText.Format("Reader626SDK   V5.1 Build:%04d-%02d-%02d %s", sysTime.wYear, sysTime.wMonth, sysTime.wDay, __TIME__);
	//�޸�Ϊ
	//strText.Format("%s", "Reader1100 Demo V1.1");
	//this->SetWindowText(strText);
	
	pgDlgPress	=	new CProgress();
	pgDlgPress->Create(IDD_PROGRESS_DIALOG, this);
	//pgDlgPress->ShowWindow(SW_SHOW);
	pgDlgPress->ShowWindow(SW_HIDE);


/*	apiReturn res;
	int i,k;
	char temp[256];
	BYTE ifEP500=0;

	CString nameList[100],portList[100];
	k=GetSystemPorts(nameList,portList);
	for(i=0;i<k;i++)
	{
		wsprintf(temp, "\\\\.\\%s",LPCTSTR(portList[i]));
		res=ConnectScanner(&m_hScanner,temp, 0);   // �Զ�д����ǰ����������
		if(res == _OK) break;
	}
//	res=ConnectScanner(&m_hScanner,"COM1",0);
	if(res != _OK)
	{
		MessageBox("Not found Reader connect to the COM!","Notice",MB_ICONWARNING);
		CDialog::OnCancel();
		return TRUE;
	}

	Sleep(500);
	for(i=0;i<5;i++)
	{
		res=GetReaderVersion(m_hScanner,&m_HardVersion,&m_SoftVersion);
		if (res==_OK)
			break;
	}
	if(res != _OK)
	{
		MessageBox("Not found Reader connect to the COM!","Notice",MB_ICONWARNING);
		CDialog::OnCancel();
		return TRUE;
	}
	m_Sheet.AddPage(&m_ReaderParameterPage);
	switch ((m_HardVersion>>8) & 0xFF)
	{
	case 0x16:
		m_Sheet.AddPage(&m_EPCC1G2TestPage);
		break;
	case 0x18:
		m_Sheet.AddPage(&m_TK900TestPage);
		break;
	case 0x14:
		m_Sheet.AddPage(&m_ISO6BTestPage);
		break;
	case 0x1A:
		m_Sheet.AddPage(&m_EPCC1G2TestPage);
		m_Sheet.AddPage(&m_ISO6BTestPage);
		m_Sheet.AddPage(&m_TK900TestPage);
		break;
	default:
		MessageBox("Not found Reader connect to the COM!","Notice",MB_ICONWARNING);
		CDialog::OnCancel();
		return TRUE;
	}
	m_Sheet.Create(this, WS_CHILD | WS_VISIBLE, 0);

	for (i=0;i<3;i++)
	{
		res=ReadIfEP500(m_hScanner,&ifEP500);
		if ((res==_OK) || (res==_invalid_command))
			break;
	}
	switch(res)
	{
		case _OK:
			if (ifEP500)
			{
				SetWindowText("Reader2600���԰� ���ó�ΪEP500  V5.2 ");
			}
			else
			{
				SetWindowText("Reader2600���԰� V 5.2 ");
			}
			break;
		case _invalid_command:
			SetWindowText("Reader2600���԰� V 5.2");
			break;
		default:
			SetWindowText("Reader2600���԰� V 5.2");
	}*/
	
	m_Sheet.AddPage(&m_ConnectReaderPage);
	SetPageForm();
	m_Sheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	//m_Sheet.Create();
	
	m_ConnectReaderPage.pMain=this;

	//SetAppHwnd(NULL);
	SetAppHwnd(this->m_hWnd);

	

	::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
	//OnInitUIText();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReaderDemoDlg::SetPageForm()
{
	
#if defined (ENABLEREADERPARAM)
	if ( 1 == iPlatform )//0---626, 1---218
	{
		m_Sheet.AddPage(&m_ReaderDParamePage);//218��������
	}
	else
	{
		m_Sheet.AddPage(&m_ReaderParameterPage);//626��������
	}
#endif
	
	m_Sheet.AddPage(&m_EPCC1G2TestPage);
	m_Sheet.AddPage(&m_ISO6BTestPage);
	//m_Sheet.AddPage(&m_TK900TestPage);
	
#if defined (ENABLEREADERMODES)
	//Сģ�����
	m_Sheet.AddPage(&m_ModesPage);
#elif defined (ENABLErubbish)
	//�����������
	m_Sheet.AddPage(&m_Rubbish);
#else
	m_Sheet.AddPage(&m_OutputPage);
#endif
	
	
#if defined (ENABLEBPA9PROCTOL)
	m_Sheet.AddPage(&m_BPAA9Page);
#endif
	//m_Sheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);
	
}

void CReaderDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	//��ΪҪ���ã�����������
	#if 0
	else if(nID == SC_MINIMIZE)
	{
		Thide();
		//ShowWindow(SW_MINIMIZE);
		ShowWindowEx(SW_HIDE);	
	}
	#endif
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReaderDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if ( bDispFlag == SW_SHOW )
		{
			ShowWindow(SW_SHOW);
		}
		else
		{
			ShowWindow(SW_HIDE);
			return;
		}

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReaderDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CReaderDemoDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
	case WM_MYMESSAGE:
		if( lParam==WM_RBUTTONUP || lParam==WM_LBUTTONUP )
		//if( lParam==WM_RBUTTONUP )
		{
			PopupMenu();			
		}
		break;
	case WM_MYDATAMSG:
		{
			int iLeft = (int)wParam;
			int iRight = (int)lParam;
			if ( 0 == iLeft )
			{
				if ( 0 == iRight )
				{
					ShowWindowEx(SW_SHOW);
				}
				else if ( 1 == iRight )
				{
					OnCancel();
				}
			}
			Tdehide();
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CReaderDemoDlg::ShowWindowEx(int iFlag)
{
	ShowWindow(iFlag);
}

void CReaderDemoDlg::Thide()
{
	//������ͼ��
	NOTIFYICONDATA tnd;
    tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=this->m_hWnd;
	tnd.uID=IDR_MAINFRAME;
    tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage=WM_MYMESSAGE;
	tnd.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(tnd.szTip,"AutoMakeEPC");
    Shell_NotifyIcon(NIM_ADD,&tnd);//�����������ͼ��
}

void CReaderDemoDlg::Tdehide()
{
	NOTIFYICONDATA tnd;
    tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=this->m_hWnd;
	tnd.uID=IDR_MAINFRAME;
    tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage=WM_MYMESSAGE;
	//�û��Զ������Ϣ����������������ϳ���ͼ���϶���ʱͼ�귢�͵���Ϣ
	tnd.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(tnd.szTip,"yyyy");//ͼ����ʾΪ"���Գ���"
    Shell_NotifyIcon(NIM_DELETE,&tnd);//����������
}


void CReaderDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CReaderDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//::SendMessage(gOutputHwnd, WM_OUTPUTTESTDATAMSG, 0, 0);//ͣ���߳�
	//PostQuitMessage(0);
	CDialog::OnClose();
}

//�û��Զ�����Ϣ WM_LISTUSERDATA
afx_msg LRESULT CReaderDemoDlg::OnListuserdata(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 2 == iwParam )
	{
		OnInitUIText();	//��������
	}
	else if ( 3 == iwParam )
	{
		int iPage = (int)ilParam;
		m_Sheet.SetActivePage(iPage);
	}
	else if ( 11 == iwParam )
	{
		//�л�ƽ̨�ã�218��626�����и�
		int i = 0;
		int iCount = m_Sheet.GetPageCount();
		while (iCount!=1)
		{
			m_Sheet.RemovePage(iCount-1);
			iCount = m_Sheet.GetPageCount();
		}
		
		//m_Sheet.
		SetPageForm();
		::PostMessage(gMainHwnd,WM_LISTUSERDATA,2,0);	//������ı�����
	}
	
	return 0;
}
