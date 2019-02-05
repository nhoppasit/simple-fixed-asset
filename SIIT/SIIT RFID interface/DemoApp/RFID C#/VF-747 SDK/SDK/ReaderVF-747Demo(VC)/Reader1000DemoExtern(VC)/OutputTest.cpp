// OutputTest.cpp : implementation file
//

#include "stdafx.h"
#include "readerdemo.h"
#include "OutputTest.h"

#include <afxmt.h>

//#include "./INC/SkinStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//定义定时器的ID
//时间
#define					TIME_IDENTIFIER_OUTPUTTEST	(3000)		//时间ID号,检测有无标签
#define					INTERVALTIME_OUTPUT			(1000)		//多长时间执行一次(1s跑一次)

//////////////////////////////////////////////////////////////////////////
#define			CLR_WHITE			(RGB(0xFF,0xFF,0xFF))	//白色
#define			CLR_BLACK			(RGB(0x00,0x00,0x00))	//黑色
#define			CLR_RED				(RGB(0xFF,0x00,0x00))	//红色
#define			CLR_GREEN			(RGB(0x00,0xFF,0x00))	//绿色
#define			CLR_BLUE			(RGB(0x00,0x00,0xFF))	//蓝色
#define			CLR_YELLOW			(RGB(0xFF,0xFF,0x00))	//黄色
//////////////////////////////////////////////////////////////////////////
#define			TAGCOUNTVALUESTART	(0)//读到标签的计数，是从0还是从1

//////////////////////////////////////////////////////////////////////////
HWND	gOutputHwnd	=	NULL;
BOOL    nReadThread		=	FALSE;
static SOCKET hRaeadSocket	=	INVALID_SOCKET;//modify by mqs
HANDLE hComm	=	NULL;
char **chArray	=	NULL;
OVERLAPPED osReader = {0};
HANDLE	m_RecvThreadEvent;		//通讯线程退出事件句柄
CRITICAL_SECTION lpCriticalSection	=	{0};
char gRecvBuf[1025]	=	{0};
int giCount = TAGCOUNTVALUESTART;
int glen_temp	=	0;

int is485Out	=	0;
//////////////////////////////////////////////////////////////////////////
#define			MAX_EVENT_NUMBER			(1024)
struct _evt_data
{
    int  iEvent;
	char chPhCon[MAX_PATH*2];	//内容
};

typedef struct _T_EVENT_QUEUE
{
    struct _evt_data    d[MAX_EVENT_NUMBER];
    int               head;
    int               tail;
} T_EVENT_QUEUE;
T_EVENT_QUEUE    s_vmeEventQueue;//定义结构内容对应表

struct DataPacket
{
	int len;				//buffer length
	char chbuf[512];	//actual buffer
};

CTList<DataPacket> m_ReadListOut;
CCriticalSection m_readLock;
//////////////////////////////////////////////////////////////////////////
//将十六进制数转换成字符串
CString HextoStr(BYTE *HexBuffer,int BufferLen)
{
	CString str,strtemp;
	int i;
	
	for(i=0;i<BufferLen;i++)
	{
		strtemp.Format("%02X",HexBuffer[i]);
		str+=strtemp;
	}
	
	return str;
}

//将十进制数转换成字符串
CString DectoStr(BYTE *HexBuffer,int BufferLen)
{
	CString str,strtemp;
	int i;
	
	for(i=0;i<BufferLen;i++)
	{
		strtemp.Format("%02d",HexBuffer[i]);
		str+=strtemp;
	}
	
	return str;
}

//将十六进制时间转换成字符串
CString HextimetoStr(BYTE *HexBuffer,int BufferLen)
{
	CString str,strtemp;
	
	strtemp.Format("%02d",20);
	str+=strtemp;
	strtemp.Format("%02d",HexBuffer[0]);
	str+=strtemp;
	str+="/";
	strtemp.Format("%02d",HexBuffer[1]);
	str+=strtemp;
	str+="/";
	strtemp.Format("%02d",HexBuffer[2]);
	str+=strtemp;
	str+=" ";
	strtemp.Format("%02d",HexBuffer[3]);
	str+=strtemp;
	str+=":";
	strtemp.Format("%02d",HexBuffer[4]);
	str+=strtemp;
	str+=":";
	strtemp.Format("%02d",HexBuffer[5]);
	str+=strtemp;
	
	return str;
}
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
static void PopupMenu()
{
	CPoint point;
	GetCursorPos( & point );
	CMenu menuPopup;
	menuPopup.CreatePopupMenu();
	
	//menuPopup.AppendMenu( MF_STRING, 100, _T("Export"));
	menuPopup.AppendMenu( MF_STRING, 100, theApp.g_LoadString("IDWQB_F0059"));
	
	//menuPopup.AppendMenu( MF_SEPARATOR );
	//menuPopup.AppendMenu( MF_STRING, 101, _T("Exit"));
	
	int nCmd = (int) menuPopup.TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, AfxGetMainWnd() );
	switch( nCmd )
	{
	case	100:
		//AfxMessageBox(_T("退出"));
		//CMainFrame::OnEditComm ();
		//::SendMessage(FrameHwnd, WM_CLOSE, 0, 0);
		::PostMessage(gOutputHwnd,WM_OUTPUTTESTDATAMSG,3,0);	//导出TXT
		break;
		//case	101:
		//	::PostMessage(gEcpISO6C,WM_CLOSE,0,0);
		//	break;
		
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////

// COutputTest property page

IMPLEMENT_DYNCREATE(COutputTest, CPropertyPage)

COutputTest::COutputTest() : CPropertyPage(COutputTest::IDD)
{
	//{{AFX_DATA_INIT(COutputTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	int i = 0;
	chArray =new char*[200];
	for (i = 0; i < 200; i++)
	{
		chArray[i]	=	new char[166];
	}

	
	m_TagNumsFont	=	new CFont;
	m_TagNumsFont->CreateFont(66,0,0,0,700,FALSE,FALSE,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,DEFAULT_PITCH|FF_MODERN, _T("华文行楷"));     //

	//初始队列为空
	s_vmeEventQueue.head = 0;
    s_vmeEventQueue.tail = 0;

	is485Out	=	0;

}

COutputTest::~COutputTest()
{
	int i = 0;
	for (i = 0; i < 200; i++)
	{
		delete []chArray[i];
	}
	delete [] chArray;

	if ( osReader.hEvent != NULL )
	{
		CloseHandle(osReader.hEvent);
	}

	if ( m_TagNumsFont != NULL )
	{
		//释放
		delete m_TagNumsFont;
	}
}

void COutputTest::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputTest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutputTest, CPropertyPage)
	//{{AFX_MSG_MAP(COutputTest)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_WEG26START, OnButtonWeg26start)
	ON_BN_CLICKED(IDC_BUTTON_WEG26STOP, OnButtonWeg26stop)
	ON_BN_CLICKED(IDC_BUTTON_WEG34START, OnButtonWeg34start)
	ON_BN_CLICKED(IDC_BUTTON_WEG34STOP, OnButtonWeg34stop)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_ONE, OnCheckOne)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CLEARSCREEN, OnButtonClearscreen)
	ON_BN_CLICKED(IDC_CHECK1_OUTPUT, OnCheck1Output)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_ClearMemory, OnBUTTONClearMemory)
	ON_BN_CLICKED(IDC_BUTTON_ReportNow, OnBUTTONReportNow)
	ON_BN_CLICKED(IDC_BUTTON_GetTagInfo, OnBUTTONGetTagInfo)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_OUTPUTTESTDATAMSG, OnOutputtestdatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputTest message handlers
void COutputTest::OnInitUIText()//界面和文本更新
{
	SetWindowText(theApp.g_LoadString("IDWQB_F0001"));//6C Test

	GetDlgItem(IDC_BUTTON_START)->SetWindowText(theApp.g_LoadString("IDWQB_F0002"));//Start
	GetDlgItem(IDC_BUTTON_STOP)->SetWindowText(theApp.g_LoadString("IDWQB_F0003"));//Stop
	GetDlgItem(IDC_BUTTON_WEG26START)->SetWindowText(theApp.g_LoadString("IDWQB_F0004"));//Start
	GetDlgItem(IDC_BUTTON_WEG26STOP)->SetWindowText(theApp.g_LoadString("IDWQB_F0005"));//Stop
	GetDlgItem(IDC_BUTTON_WEG34STOP)->SetWindowText(theApp.g_LoadString("IDWQB_F0006"));//Stop
	GetDlgItem(IDC_BUTTON_WEG34START)->SetWindowText(theApp.g_LoadString("IDWQB_F0007"));//Start
	GetDlgItem(IDC_CHECK_ONE)->SetWindowText(theApp.g_LoadString("IDWQB_F0008"));//A label is listed only once
	GetDlgItem(IDC_STATIC_Wgand26)->SetWindowText(theApp.g_LoadString("IDWQB_F0009"));//Wiegand26
	GetDlgItem(IDC_STATIC_Wgand34)->SetWindowText(theApp.g_LoadString("IDWQB_F0010"));//Wiegand34
	GetDlgItem(IDC_STATIC_OUTMODE)->SetWindowText(theApp.g_LoadString("IDWQB_F0035"));//Cmd Mode(RS232)--->Auto Mode(RS232)
	GetDlgItem(IDC_BUTTON_CLEARSCREEN)->SetWindowText(theApp.g_LoadString("IDWQB_F0044"));//Clear Screen
	GetDlgItem(IDC_STATIC_ReadNumbers)->SetWindowText(theApp.g_LoadString("IDWQB_F0045"));//IDC_STATIC_ReadNumbers
	GetDlgItem(IDC_BUTTON_ClearMemory)->SetWindowText(theApp.g_LoadString("IDWQB_F0046"));//Clear Memory
	GetDlgItem(IDC_BUTTON_ReportNow)->SetWindowText(theApp.g_LoadString("IDWQB_F0047"));//ReportNow
	GetDlgItem(IDC_BUTTON_GetTagInfo)->SetWindowText(theApp.g_LoadString("IDWQB_F0048"));//Get Tag Info
	GetDlgItem(IDC_CHECK1_OUTPUT)->SetWindowText(theApp.g_LoadString("IDWQB_F0049"));//Whether to display the original records
	

}

BOOL COutputTest::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	gOutputHwnd	=	this->GetSafeHwnd();
	Debug_SetEditHwnd(GetDlgItem(IDC_EDIT_Wiegand)->m_hWnd);
	hReadThread	=	NULL;

	InitializeCriticalSection(&lpCriticalSection);
	

	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM0");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM1");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM2");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM3");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM4");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM5");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM6");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM7");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM8");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->AddString("COM9");
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->SetCurSel(1);


	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM0");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM1");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM2");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM3");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM4");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM5");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM6");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM7");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM8");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->AddString("COM9");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->SetCurSel(1);

	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26RATE))->AddString("9600");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26RATE))->AddString("19200");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26RATE))->AddString("38400");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26RATE))->AddString("57600");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26RATE))->AddString("115200");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26RATE))->SetCurSel(0);



	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM0");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM1");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM2");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM3");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM4");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM5");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM6");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM7");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM8");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->AddString("COM9");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->SetCurSel(2);

	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34RATE))->AddString("9600");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34RATE))->AddString("19200");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34RATE))->AddString("38400");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34RATE))->AddString("57600");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34RATE))->AddString("115200");
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34RATE))->SetCurSel(0);

	
	//初始化时没有
	((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_BUTTON_ReportNow))->ShowWindow(SW_HIDE);
	

	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetFont(m_TagNumsFont);
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetWindowText("0");

	
	//显示与不显示，就是下面两句，你看着办。
	//((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValueS))->ShowWindow(SW_HIDE);
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValueS))->ShowWindow(SW_SHOW);
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValueS))->SetWindowText("0");

	//((CSkinStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetMyFont(m_TagNumsFont);
	//((CSkinStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetText("0", 0 , CLR_RED);
	
	((CListCtrl*)GetDlgItem(IDC_LIST_INFO))->GetWindowRect(&rectListInfo);
	ScreenToClient(&rectListInfo);         //转换到在对话框中的位置
	((CListCtrl*)GetDlgItem(IDC_EDIT_Wiegand))->GetWindowRect(&rectEditOutput);
	ScreenToClient(&rectEditOutput);         //转换到在对话框中的位置
	

	//是否显示调试窗口
	OnCheck1Output();
	//OnSetActive();

	//Output输出测试页
	::SendMessage(gOutputHwnd,WM_OUTPUTTESTDATAMSG,2,0);	//convert language

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL COutputTest::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CString strTemp;
	CString strTemp0 = theApp.g_LoadString("IDWQB_F0012");//No
	CString strTemp1 = theApp.g_LoadString("IDWQB_F0013");//First Time
	CString strTemp2 = theApp.g_LoadString("IDWQB_F0014");//End Time
	CString strTemp3 = theApp.g_LoadString("IDWQB_F0015");//Count
	CString strTemp4 = theApp.g_LoadString("IDWQB_F0016");//Antenna
	CString strTemp5 = theApp.g_LoadString("IDWQB_F0017");//Type
	CString strTemp6 = theApp.g_LoadString("IDWQB_F0018");//EPC

	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		strTemp3 = "RSSI";
	}

	CListCtrl *pListInfo	=	(CListCtrl*)GetDlgItem(IDC_LIST_INFO);
	DWORD dwStyle = pListInfo->SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	pListInfo->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);
	pListInfo->DeleteAllItems();
	
	LVCOLUMN listColumnTemp;

	is485Out	=	0;
	
#if defined (ENABLE485TXOUTPUT)
	if ( 1 == gAutoParam->OutInterface )
	{
		//485输出
		is485Out	=	1;
	}
#else
	is485Out	=	0;
#endif
	
	if ( 1 == is485Out )
	{
		
		
// 		pListInfo->InsertColumn(0, strTemp0, LVCFMT_LEFT, 40);
// 		
// 		pListInfo->InsertColumn(1, strTemp3, LVCFMT_LEFT, 60);
// 		
// 		pListInfo->InsertColumn(2, strTemp4, LVCFMT_LEFT, 60);
// 		
// 		pListInfo->InsertColumn(3, strTemp6, LVCFMT_LEFT, 300);


		pListInfo->DeleteColumn(0);
		pListInfo->InsertColumn(0, strTemp0, LVCFMT_LEFT, 40);
		pListInfo->DeleteColumn(1);
		pListInfo->InsertColumn(1, strTemp3, LVCFMT_LEFT, 60);
		pListInfo->DeleteColumn(2);
		pListInfo->InsertColumn(2, strTemp4, LVCFMT_LEFT, 60);
		pListInfo->DeleteColumn(3);
		pListInfo->InsertColumn(3, strTemp6, LVCFMT_LEFT, 300);
		

		
	}
	else
	{
		//(7)数据输出格式：0-简化格式，1-标准格式，2-XML格式。缺省值为0。
		if ( 0 == gAutoParam->OutputManner || 2 == gAutoParam->OutputManner )
		{
			//pListInfo->GetColumn(0, &listColumnTemp);
			
			pListInfo->GetColumn(1, &listColumnTemp);
			pListInfo->DeleteColumn(1);
			pListInfo->GetColumn(2, &listColumnTemp);
			pListInfo->DeleteColumn(2);
			pListInfo->GetColumn(3, &listColumnTemp);
			
			
			pListInfo->DeleteColumn(0);
			pListInfo->InsertColumn(0, strTemp0, LVCFMT_LEFT, 40);
			pListInfo->DeleteColumn(1);
			pListInfo->InsertColumn(1, strTemp3, LVCFMT_LEFT, 60);
			pListInfo->DeleteColumn(2);
			pListInfo->InsertColumn(2, strTemp4, LVCFMT_LEFT, 60);
			pListInfo->DeleteColumn(3);
			pListInfo->InsertColumn(3, strTemp5, LVCFMT_LEFT, 60);
			pListInfo->DeleteColumn(4);
			pListInfo->InsertColumn(4, strTemp6, LVCFMT_LEFT, 300);
			pListInfo->DeleteColumn(5);
			pListInfo->DeleteColumn(6);
			
		}
		else
		{
			pListInfo->DeleteColumn(0);
			pListInfo->InsertColumn(0, strTemp0, LVCFMT_LEFT, 40);
			pListInfo->DeleteColumn(1);
			pListInfo->InsertColumn(1, strTemp1, LVCFMT_LEFT, 140);
			pListInfo->DeleteColumn(2);
			pListInfo->InsertColumn(2, strTemp2, LVCFMT_LEFT, 140);
			pListInfo->DeleteColumn(3);
			pListInfo->InsertColumn(3, strTemp3, LVCFMT_LEFT, 60);
			pListInfo->DeleteColumn(4);
			pListInfo->InsertColumn(4, strTemp4, LVCFMT_LEFT, 60);
			pListInfo->DeleteColumn(5);
			pListInfo->InsertColumn(5, strTemp5, LVCFMT_LEFT, 60);
			pListInfo->DeleteColumn(6);
			pListInfo->InsertColumn(6, strTemp6, LVCFMT_LEFT, 300);
		}
	}

	//RS485输出口
	GetDlgItem(IDC_COMBO_RS485O)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLEARSCREEN)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BUTTON_ClearMemory)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ReportNow)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GetTagInfo)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_WEG26START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_WEG26STOP)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BUTTON_WEG34START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_WEG34STOP)->EnableWindow(TRUE);



	if ( ifConnectReader )
	{
		//连上了的
		switch(ConnectMode)
		{
		case 0://网口
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				//strTemp = "Cmd Mode(RJ45)--->Auto Mode(RS232)";
				strTemp = theApp.g_LoadString("IDWQB_F0019");
				GetDlgItem(IDC_COMBO_RS485O)->ShowWindow(SW_SHOW);
				break;
			case 1://1－RS485口
				//strTemp = "Cmd Mode(RJ45)--->Auto Mode(RS485)";
				strTemp = theApp.g_LoadString("IDWQB_F0020");
				//RS485输出口
				GetDlgItem(IDC_COMBO_RS485O)->ShowWindow(SW_SHOW);
				break;
			case 2://2－RJ45口
				//strTemp = "Cmd Mode(RJ45)--->Auto Mode(RJ45)";
				strTemp = theApp.g_LoadString("IDWQB_F0021");
				break;
			case 3://3- Wiegand26
				//strTemp = "Cmd Mode(RJ45)--->Auto Mode(Wiegand26)";
				strTemp = theApp.g_LoadString("IDWQB_F0022");
				break;
			case 4://4- Wiegand34
				//strTemp = "Cmd Mode(RJ45)--->Auto Mode(Wiegand34)";
				strTemp = theApp.g_LoadString("IDWQB_F0023");
				break;
			default:
				//strTemp = "Unknow Mode";
				strTemp = theApp.g_LoadString("IDWQB_F0034");
				break;
			}
			break;
		case 1://RS232
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				//strTemp = "Cmd Mode(RS232)--->Auto Mode(RS232)";
				strTemp = theApp.g_LoadString("IDWQB_F0024");
				break;
			case 1://1－RS485口
				//strTemp = "Cmd Mode(RS232)--->Auto Mode(RS485)";
				strTemp = theApp.g_LoadString("IDWQB_F0025");
				//RS485输出口
				GetDlgItem(IDC_COMBO_RS485O)->ShowWindow(SW_SHOW);
				break;
			case 2://2－RJ45口
				//strTemp = "Cmd Mode(RS232)--->Auto Mode(RJ45)";
				strTemp = theApp.g_LoadString("IDWQB_F0026");
				break;
			case 3://3- Wiegand26
				//strTemp = "Cmd Mode(RS232)--->Auto Mode(Wiegand26)";
				strTemp = theApp.g_LoadString("IDWQB_F0027");
				break;
			case 4://4- Wiegand34
				//strTemp = "Cmd Mode(RS232)--->Auto Mode(Wiegand34)";
				strTemp = theApp.g_LoadString("IDWQB_F0028");
				break;
			default:
				//strTemp = "Unknow Mode";
				strTemp = theApp.g_LoadString("IDWQB_F0034");
				break;
			}
			break;
		case 2://RS485
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				//strTemp = "Cmd Mode(RS485)--->Auto Mode(RS232)";
				strTemp = theApp.g_LoadString("IDWQB_F0029");
				GetDlgItem(IDC_COMBO_RS485O)->ShowWindow(SW_SHOW);
				break;
			case 1://1－RS485口
				//strTemp = "Cmd Mode(RS485)--->Auto Mode(RS485)";
				strTemp = theApp.g_LoadString("IDWQB_F0030");
				//RS485输出口
				//GetDlgItem(IDC_COMBO_RS485O)->ShowWindow(SW_SHOW);
				break;
			case 2://2－RJ45口
				//strTemp = "Cmd Mode(RS485)--->Auto Mode(RJ45)";
				strTemp = theApp.g_LoadString("IDWQB_F0031");
				break;
			case 3://3- Wiegand26
				//strTemp = "Cmd Mode(RS485)--->Auto Mode(Wiegand26)";
				strTemp = theApp.g_LoadString("IDWQB_F0032");
				break;
			case 4://4- Wiegand34
				//strTemp = "Cmd Mode(RS485)--->Auto Mode(Wiegand34)";
				strTemp = theApp.g_LoadString("IDWQB_F0033");
				break;
			default:
				//strTemp = "Unknow Mode";
				strTemp = theApp.g_LoadString("IDWQB_F0034");
				break;
			}
			break;
		}

	}
	else
	{
		//strTemp = "None Mode";
		strTemp = theApp.g_LoadString("IDWQB_F0035");

		// 没有连上
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CLEARSCREEN)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_ClearMemory)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ReportNow)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_GetTagInfo)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_BUTTON_WEG26START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_WEG26STOP)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_BUTTON_WEG34START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_WEG34STOP)->EnableWindow(FALSE);
		
				
		
	}

	if ( osReader.hEvent != NULL )
	{
		CloseHandle(osReader.hEvent);
		osReader.hEvent	=	NULL;
	}

	GetDlgItem(IDC_STATIC_OUTMODE)->SetWindowText(strTemp);
	
	return CPropertyPage::OnSetActive();
}

void COutputTest::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	//输出按钮开始
	apiReturn res	=	_no_scanner;
	int i = 0;

	//先清LIST
	CListCtrl *mListID	=	(CListCtrl*)GetDlgItem(IDC_LIST_INFO);
	mListID->DeleteAllItems();
	giCount	=	TAGCOUNTVALUESTART;
	GetDlgItem(IDC_EDIT_Wiegand)->SetWindowText("");

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

	switch(ConnectMode)
	{
		case 0://网口
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				for (i = 0; i < 3; i++)
				{
					res = Net_AutoMode(m_hSocket,1);
					if ( _OK == res )
					{
						break;
					}
				}
				
				if(res==_OK)//网口对串口(命令模式网口，自动模式串口)
				{
					int ret = -1;
					int nRate;
					char sCom[32],tmp[32];
					((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetCurSel(),tmp);
					
					nRate=gBasicParam->BaudRate-4; 
					sprintf(sCom, "\\\\.\\%s",tmp);
					
					hComm	=	NULL;
					ret=ConnecCom(&hComm,sCom,nRate);
					if(ret!=0)
					{
						//MessageBox("端口打开失败！","Notice",MB_ICONERROR);
						MessageBox(theApp.g_LoadString("IDWQB_F0036"), theApp.g_LoadString("IDWQB_F0037"),MB_ICONERROR);
						return;
					}
				}
				break;
			case 1://1－RS485口
				for (i = 0; i < 3; i++)
				{
					res = Net_AutoMode(m_hSocket,1);
					if ( _OK == res )
					{
						break;
					}
				}
				if (res == _OK)//网口对串口(命令模式网口，自动模式485)
				{
					int ret = -1;
					int nRate;
					char sCom[32],tmp[32];
					((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetCurSel(),tmp);
					
					nRate=gBasicParam->BaudRate-4; 
					sprintf(sCom, "\\\\.\\%s",tmp);
					
					hComm	=	NULL;
					ret=ConnecCom(&hComm,sCom,nRate);
					if(ret!=0)
					{
						//MessageBox("端口打开失败！","Notice",MB_ICONERROR);
						MessageBox(theApp.g_LoadString("IDWQB_F0036"), theApp.g_LoadString("IDWQB_F0037"),MB_ICONERROR);
						return;
					}
				}	
				break;
			case 2://2－RJ45口
				for (i = 0; i < 3; i++)
				{
					res = Net_AutoMode(m_hSocket,1);
					if ( _OK == res )
					{
						break;
					}
				}
				if (res == _OK)//网口对串口(命令模式网口，自动RJ45)
				{
					int ret = -1;
					ret=ConnectRj45();
				}
				break;
			case 3://3- Wiegand26
				for (i = 0; i < 3; i++)
				{
					res = Net_AutoMode(m_hSocket,1);
					if ( _OK == res )
					{
						break;
					}
				}
				if(res==_OK)//串口对网口(命令模式串口，自动模式Wiegand26)
				{
					
				}

				break;
			case 4://4- Wiegand34
				for (i = 0; i < 3; i++)
				{
					res = Net_AutoMode(m_hSocket,1);
					if ( _OK == res )
					{
						break;
					}
				}
				if(res==_OK)//串口对网口(命令模式串口，自动模式Wiegand34)
				{
					
				}
				
				break;
			default:
				
				break;
			}
			break;
		case 1://RS232
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,0);
					if ( _OK == res )
					{
						break;
					}
				}
				if(res==_OK)//串口对串口(命令模式串口，自动模式串口)
				{
					PurgeComm(m_hScanner,PURGE_TXCLEAR|PURGE_RXCLEAR);
				}
				break;
			case 1://1－RS485口
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,0);
					if ( _OK == res )
					{
						break;
					}
				}
				if(res==_OK)//串口对485(命令模式串口，自动模式485)
				{
					int ret = -1;
					int nRate;
					char sCom[32],tmp[32];
					((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetCurSel(),tmp);

					nRate=gBasicParam->BaudRate-4; 
					sprintf(sCom, "\\\\.\\%s",tmp);
					
					hComm	=	NULL;
					ret=ConnecCom(&hComm,sCom,nRate);
					if(ret!=0)
					{
						//MessageBox("端口打开失败！","Notice",MB_ICONERROR);
						MessageBox(theApp.g_LoadString("IDWQB_F0036"), theApp.g_LoadString("IDWQB_F0037"),MB_ICONERROR);
						return;
					}
				}				
				break;
			case 2://2－RJ45口
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,0);
					if ( _OK == res )
					{
						break;
					}
				}
				if(res==_OK)//串口对网口(命令模式串口，自动模式RJ45)
				{
					int ret = -1;
					ret=ConnectRj45();
					
				}				
				break;
			case 3://3- Wiegand26
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,0);
					if ( _OK == res )
					{
						break;
					}
				}
				if(res==_OK)//串口对网口(命令模式串口，自动模式Wiegand26)
				{
					
				}

				break;
			case 4://4- Wiegand34
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,0);
					if ( _OK == res )
					{
						break;
					}
				}
				if(res==_OK)//串口对网口(命令模式串口，自动模式Wiegand34)
				{
					
				}
				break;

			default:
				
				break;
			}
			break;
		case 2://RS485
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,RS485Address);
					if ( _OK == res )
					{
						break;
					}
					else
					{
						Sleep(ReadRS485SleepTime);
					}
				}
				if(res==_OK)//485对串口(命令模式485，自动模式串口)
				{
					int ret = -1;
					int nRate;
					char sCom[32],tmp[32];
					((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetCurSel(),tmp);
					
					nRate=gBasicParam->BaudRate-4; 
					sprintf(sCom, "\\\\.\\%s",tmp);
					
					hComm	=	NULL;
					ret=ConnecCom(&hComm,sCom,nRate);
					if(ret!=0)
					{
						//MessageBox("端口打开失败！","Notice",MB_ICONERROR);
						MessageBox(theApp.g_LoadString("IDWQB_F0036"), theApp.g_LoadString("IDWQB_F0037"),MB_ICONERROR);
						return;
					}
				}
				break;
			case 1://1－RS485口
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,RS485Address);
					if ( _OK == res )
					{
						break;
					}
					else
					{
						Sleep(ReadRS485SleepTime);
					}
				}
				if(res==_OK)//485对485(命令模式485，自动模式485)
				{
					//int ret = -1;
					//int nRate;
					//char sCom[32],tmp[32];
					//((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_RS485O))->GetCurSel(),tmp);
					//
					//nRate=gBasicParam->BaudRate-4; 
					//sprintf(sCom, "\\\\.\\%s",tmp);
					//
					//hComm	=	NULL;
					//ret=ConnecCom(&hComm,sCom,nRate);
					//if(ret!=0)
					//{
					//	//MessageBox("端口打开失败！","Notice",MB_ICONERROR);
					//	MessageBox(theApp.g_LoadString("IDWQB_F0036"), theApp.g_LoadString("IDWQB_F0037"),MB_ICONERROR);
					//	return;
					//}
					if(res==_OK)//串口对串口(命令模式串口，自动模式串口)
					{
						PurgeComm(m_hScanner,PURGE_TXCLEAR|PURGE_RXCLEAR);
					}
					

				}
				break;
			case 2://2－RJ45口
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,RS485Address);
					if ( _OK == res )
					{
						break;
					}
					else
					{
						Sleep(ReadRS485SleepTime);
					}
				}
				if(res==_OK)//485对网口(命令模式485，自动模式RJ45)
				{
					int ret = -1;
					ret=ConnectRj45();
				}
				break;
			case 3://3- Wiegand26
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,RS485Address);
					if ( _OK == res )
					{
						break;
					}
					else
					{
						Sleep(ReadRS485SleepTime);
					}
				}
				if(res==_OK)//串口对网口(命令模式串口，自动模式Wiegand26)
				{
					
				}
				
				break;
			case 4://4- Wiegand34
				for (i = 0; i < 3; i++)
				{
					res = AutoMode(m_hScanner,1,RS485Address);
					if ( _OK == res )
					{
						break;
					}
					else
					{
						Sleep(ReadRS485SleepTime);
					}
				}
				if(res==_OK)//串口对网口(命令模式串口，自动模式Wiegand34)
				{
					
				}
				break;
				
			default:
				
				break;
			}
			break;

	}//end of switch(ConnectMode)

	if ( gAutoParam->OutInterface == 3 || gAutoParam->OutInterface == 4 )
	{
		if(res==_OK)
		{
			GetDlgItem(IDC_CHECK_ONE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		}
	}
	else
	{
		if(res==_OK)
		{
			#if 1
			nReadThread	=	FALSE;
			//创建线程退出事件句柄
			m_RecvThreadEvent	=	CreateEvent(NULL,FALSE,FALSE,NULL);
			hReadThread	=	CreateThread(NULL,0,ReadThreadFuncTag,this,0,NULL);
			if( hReadThread != NULL )
			{		
				nReadThread	=	TRUE;
				GetDlgItem(IDC_CHECK_ONE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);

			}
			else
			{
				//MessageBox("Create ReadThread Error!","Notice",MB_ICONERROR);
				MessageBox(theApp.g_LoadString("IDWQB_F0038"), theApp.g_LoadString("IDWQB_F0039"),MB_ICONERROR);

			}
			#endif
		}
		else
		{
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		}
	}

	return;

}

apiReturn COutputTest::TranAutoStopMode()
{
	int i = 0;
	apiReturn res	=	_no_scanner;

	for(i = 0; i < 3; i++)
	{
	switch(ConnectMode)
	{
		case 0://网口
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				PurgeComm(m_hScanner, PURGE_TXCLEAR);  // flush transimition queue
				PurgeComm(m_hScanner, PURGE_RXCLEAR);  // flush receiveing queue

				res = Net_AutoMode(m_hSocket,0);
				if(res==_OK)//网口对串口(命令模式网口，自动模式串口)
				{
					if ( NULL != hComm )
					{
						DisconnectCom(hComm);
						hComm	=	NULL;
					}
				}
				break;
			case 1://1－RS485口
				res = Net_AutoMode(m_hSocket,0);
				if (res == _OK)//网口对串口(命令模式网口，自动模式485)
				{
					if ( NULL != hComm )
					{
						DisconnectCom(hComm);
						hComm	=	NULL;
					}
				}	
				break;
			case 2://2－RJ45口
				res = Net_AutoMode(m_hSocket,0);
				if (res == _OK)//网口对串口(命令模式网口，自动RJ45)
				{
					if ( INVALID_SOCKET != hRaeadSocket)
					{
						DisconnectRj45();
						hRaeadSocket	=	INVALID_SOCKET;
					}
				}
				break;
			case 3://3- Wiegand26
				res = Net_AutoMode(m_hSocket,0);
				if(res==_OK)//网口对串口(命令模式网口，自动模式Wiegand26)
				{
					
				}
				break;

			case 4://4- Wiegand34
				res = Net_AutoMode(m_hSocket,0);
				if(res==_OK)//网口对串口(命令模式网口，自动模式Wiegand34)
				{
					
				}
				break;

			default:
				
				break;
			}
			break;
		case 1://RS232
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				res = AutoMode(m_hScanner,0,0);
				if(res==_OK)//串口对串口(命令模式串口，自动模式串口)
				{
					PurgeComm(m_hScanner,PURGE_TXCLEAR|PURGE_RXCLEAR);
				}
				break;
			case 1://1－RS485口
				res = AutoMode(m_hScanner,0,0);
				if(res==_OK)//串口对485(命令模式串口，自动模式485)
				{
					if ( NULL != hComm )
					{
						DisconnectCom(hComm);
						hComm	=	NULL;
					}
				}				
				break;
			case 2://2－RJ45口
				res = AutoMode(m_hScanner,0,0);
				if(res==_OK)//串口对网口(命令模式串口，自动模式RJ45)
				{
					if ( INVALID_SOCKET != hRaeadSocket)
					{
						DisconnectRj45();
						hRaeadSocket	=	INVALID_SOCKET;
					}
				}				
				break;
			case 3://3- Wiegand26
				res = AutoMode(m_hScanner,0,0);
				if(res==_OK)//网口对串口(命令模式网口，自动模式Wiegand26)
				{
					
				}
				break;

			case 4://4- Wiegand34
				res = AutoMode(m_hScanner,0,0);
				if(res==_OK)//网口对串口(命令模式网口，自动模式Wiegand34)
				{
					
				}
				break;
				
			default:
				
				break;
			}
			break;
		case 2://RS485
			switch (gAutoParam->OutInterface)
			{
			case 0://0－RS232口
				res = AutoMode(m_hScanner,0,RS485Address);
				if(res==_OK)//485对串口(命令模式485，自动模式串口)
				{
					if ( NULL != hComm )
					{
						DisconnectCom(hComm);
						hComm	=	NULL;
					}
				}
				break;
			case 1://1－RS485口
				res = AutoMode(m_hScanner,0,RS485Address);
				if(res==_OK)//485对485(命令模式485，自动模式485)
				{
					if ( NULL != hComm )
					{
						DisconnectCom(hComm);
						hComm	=	NULL;
					}
				}
				break;
			case 2://2－RJ45口
				res = AutoMode(m_hScanner,0,RS485Address);
				if(res==_OK)//485对网口(命令模式485，自动模式RJ45)
				{
					if ( INVALID_SOCKET != hRaeadSocket)
					{
						DisconnectRj45();
						hRaeadSocket	=	INVALID_SOCKET;
					}
				}
				break;
			case 3://3- Wiegand26
				res = AutoMode(m_hScanner,0,RS485Address);
				if(res==_OK)//网口对串口(命令模式网口，自动模式Wiegand26)
				{
					
				}
				break;
				
			case 4://4- Wiegand34
				res = AutoMode(m_hScanner,0,RS485Address);
				if(res==_OK)//网口对串口(命令模式网口，自动模式Wiegand34)
				{
					
				}
				break;

			default:
				
				break;
			}
			break;

		}//end of switch(ConnectMode)

		if ( res == _OK )
		{
			res = _OK;
			break;
		}

	}


	return	res;
}

void COutputTest::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	//停止按钮开始
	int i = 0;
	apiReturn res	=	_no_scanner;
	CString str	=	"";

	GetDlgItem(IDC_CHECK_ONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);

	nReadThread	=	FALSE;
	if ( hReadThread != NULL )
	{
		//WaitForSingleObject(hReadThread,500);//INFINITE
		//CloseHandle(hReadThread);
		//hReadThread	=	NULL;
		
		//if(::WaitForSingleObject(hReadThread,800)   ==   WAIT_TIMEOUT)   
		//{   
		//	//如果超时：   
		//	TerminateThread(hReadThread,NULL);
		//}
		//结束通讯线程
		SetEvent(m_RecvThreadEvent);
		Sleep(100);
		//关闭线程退出事件句柄
		CloseHandle(m_RecvThreadEvent);

		CloseHandle(hReadThread);
		hReadThread   =   NULL;
		
	}


	res=	TranAutoStopMode();
	if(res==_OK)
	{
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	}
	else
	{
		str="Stop Auto Mode Fail!";
		//MessageBox(str,"Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_F0040"), theApp.g_LoadString("IDWQB_F0041"),MB_ICONERROR);

	}


	


	return;

}

void COutputTest::OnButtonClearscreen() 
{
	// TODO: Add your control notification handler code here
	//清除屏幕
	CListCtrl *mListID	=	(CListCtrl*)GetDlgItem(IDC_LIST_INFO);
	mListID->DeleteAllItems();
	//this->RedrawWindow();
	//GetDlgItem(IDC_EDIT_Wiegand)->SetWindowText("");

	CString strtmp;
	
	giCount = 0;
	strtmp.Format("%d", giCount);
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetWindowText(strtmp);
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValueS))->SetWindowText(strtmp);
	RECT rect;
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->GetWindowRect(&rect);
	ScreenToClient(&rect);         //转换到在对话框中的位置
	InvalidateRect(&rect,TRUE);

	GetDlgItem(IDC_EDIT_Wiegand)->SetWindowText("");
	
}

void COutputTest::OnBUTTONClearMemory() 
{
	// TODO: Add your control notification handler code here
	//清除内存
	apiReturn res;
	
	switch(ConnectMode)
	{
	case 0://网口
		res = Net_ClearTagMemory(m_hSocket);
		break;
	case 1://RS232
		PurgeComm(m_hScanner, PURGE_TXCLEAR);  // flush transimition queue
		PurgeComm(m_hScanner, PURGE_RXCLEAR);  // flush receiveing queue
		Sleep(30);
		res = ClearTagMemory(m_hScanner, 0);
		break;
	case 2://RS485
		res = ClearTagMemory(m_hScanner, RS485Address);
		break;
	}
	if(res==_OK)
	{
		//MessageBox("Clear Memory Successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_F0050"),theApp.g_LoadString("IDWQB_F0051"),MB_ICONINFORMATION);
	}
	else
	{
		//MessageBox("Clear Memory Fail!","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_F0052"),theApp.g_LoadString("IDWQB_F0053"),MB_ICONERROR);
	}


	return;
}

void COutputTest::OnBUTTONReportNow() 
{
	// TODO: Add your control notification handler code here
	//立即通知
}

void COutputTest::OnBUTTONGetTagInfo() 
{
	// TODO: Add your control notification handler code here
	//获取记录
	apiReturn res;
	int i,j,k,len_data,len_epc;
	CString datee,dates,num_read,antno,tagtype,data_epc,str;
	BYTE data[256],relistlen;
	
	
	CListCtrl *mListID	=	(CListCtrl*)GetDlgItem(IDC_LIST_INFO);
	mListID->DeleteAllItems();

	k=mListID->GetItemCount();
	i=0;
	
	
	for(;;)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res = Net_GetTagInfo(m_hSocket, i*8+1, 8, &relistlen, data);
			break;
		case 1://RS232
			res = GetTagInfo(m_hScanner, i*8+1, 8, &relistlen, data,0);
			break;
		case 2://RS485
			res = GetTagInfo(m_hScanner, i*8+1, 8, &relistlen, data,RS485Address);
			break;
		}
		
		if(res != _OK)
		{
			//MessageBox("获得标签记录失败!","Notice",MB_ICONINFORMATION);
			MessageBox(theApp.g_LoadString("IDWQB_F0054"),theApp.g_LoadString("IDWQB_F0055"),MB_ICONERROR);
			
			return;
		}
		if((relistlen == 0)&&(i==0))
		{
			//MessageBox("标签记录不存在!","Notice",MB_ICONINFORMATION);
			MessageBox(theApp.g_LoadString("IDWQB_F0056"),theApp.g_LoadString("IDWQB_F0057"),MB_ICONERROR);
			
			return;
		}
		len_data = 0;
		for(j=0;j<relistlen;j++)
		{
			dates = HextimetoStr(&data[len_data],6);
			datee = HextimetoStr(&data[len_data+6],6);
			num_read = DectoStr(&data[len_data+12],2);
			antno = HextoStr(&data[len_data+14],1);
			tagtype = HextoStr(&data[len_data+15],1);
			len_epc = data[len_data+16]*2;
			if ( 0 == len_epc )
			{
				continue;
			}
			data_epc = HextoStr(&data[len_data+17],len_epc);
			len_data += len_epc+17; 
			str.Format("%02d",k+1);
			mListID->InsertItem(k,0);
			mListID->SetItemText(k,0,str);
			mListID->SetItemText(k,1,dates);
			mListID->SetItemText(k,2,datee);
			mListID->SetItemText(k,3,num_read);
			mListID->SetItemText(k,4,antno);
			mListID->SetItemText(k,5,tagtype);
			mListID->SetItemText(k,6,data_epc);
			mListID->EnsureVisible(k,TRUE);
			k++;
		}
		if(relistlen < 8)
			break;
		i++;
	}
	
	k=mListID->GetItemCount();

	CString strTemp;
	strTemp.Format("%d", k);
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValueS))->SetWindowText(strTemp);
	if ( k > 9999 )
	{
		strTemp	=	"9999";
	}
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetWindowText(strTemp);
	
	RECT rect;
	((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->GetWindowRect(&rect);
	ScreenToClient(&rect);         //转换到在对话框中的位置
	InvalidateRect(&rect,TRUE);


	
}

void COutputTest::OnButtonWeg26start() 
{
	// TODO: Add your control notification handler code here
	//weg26开始
	int ret = -1;
	int nRate;
	char sCom[32],tmp[32];
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_WEG26PROT))->GetCurSel(),tmp);
	
	nRate	=	((CComboBox*)GetDlgItem(IDC_COMBO_WEG26RATE))->GetCurSel();
	sprintf(sCom, "\\\\.\\%s",tmp);
	
	hComm	=	NULL;
	ret=ConnecCom(&hComm,sCom,nRate);
	if(ret!=0)
	{
		//MessageBox("端口打开失败！","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_F0036"), theApp.g_LoadString("IDWQB_F0037"),MB_ICONERROR);
		return;
	}


	nReadThread	=	FALSE;
	hReadThread	=	CreateThread(NULL,0,ReadThreadFuncTag,this,0,NULL);
	if( hReadThread != NULL )
	{		
		nReadThread	=	TRUE;
		GetDlgItem(IDC_BUTTON_WEG26START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_WEG26STOP)->EnableWindow(TRUE);
		
	}
	else
	{
		//MessageBox("Create ReadThread Error!","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_F0038"), theApp.g_LoadString("IDWQB_F0039"),MB_ICONERROR);
		
	}

}

void COutputTest::OnButtonWeg26stop() 
{
	// TODO: Add your control notification handler code here
	//weg26停止
	if ( NULL != hComm )
	{
		DisconnectCom(hComm);
		hComm	=	NULL;
		GetDlgItem(IDC_BUTTON_WEG26START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WEG26STOP)->EnableWindow(FALSE);
	}
}

void COutputTest::OnButtonWeg34start() 
{
	// TODO: Add your control notification handler code here
	//weg34开始
	int ret = -1;
	int nRate;
	char sCom[32],tmp[32];
	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->GetLBText(((CComboBox*)GetDlgItem(IDC_COMBO_WEG34PORT))->GetCurSel(),tmp);
	
	nRate	=	((CComboBox*)GetDlgItem(IDC_COMBO_WEG34RATE))->GetCurSel();
	sprintf(sCom, "\\\\.\\%s",tmp);
	
	hComm	=	NULL;
	ret=ConnecCom(&hComm,sCom,nRate);
	if(ret!=0)
	{
		//MessageBox("端口打开失败！","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_F0036"), theApp.g_LoadString("IDWQB_F0037"),MB_ICONERROR);
		return;
	}
	
	
	nReadThread	=	FALSE;
	hReadThread	=	CreateThread(NULL,0,ReadThreadFuncTag,this,0,NULL);
	if( hReadThread != NULL )
	{		
		nReadThread	=	TRUE;
		GetDlgItem(IDC_BUTTON_WEG34START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_WEG34STOP)->EnableWindow(TRUE);
		
	}
	else
	{
		//MessageBox("Create ReadThread Error!","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_F0038"), theApp.g_LoadString("IDWQB_F0039"),MB_ICONERROR);
		
	}
}

void COutputTest::OnButtonWeg34stop() 
{
	// TODO: Add your control notification handler code here
	//weg34停止
	if ( NULL != hComm )
	{
		DisconnectCom(hComm);
		hComm	=	NULL;
		GetDlgItem(IDC_BUTTON_WEG34START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WEG34STOP)->EnableWindow(FALSE);
	}
}

void COutputTest::OnCheckOne() 
{
	// TODO: Add your control notification handler code here
	//先清LIST
	CListCtrl *mListID	=	(CListCtrl*)GetDlgItem(IDC_LIST_INFO);
	mListID->DeleteAllItems();
}

HBRUSH COutputTest::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	int nID = pWnd->GetDlgCtrlID();
	pDC->SetBkMode(OPAQUE);
	if( ( nID == IDC_STATIC_ReadNumValue ) //对指定的控件设属性,你也可以用上面的方法针对所有的标签
		)
	{
		
		pDC->SetTextColor(CLR_RED);//多此一举,你可以设文字其它的颜色
		pDC->SetBkMode(TRANSPARENT);
		
		hbr=HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void COutputTest::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	::KillTimer(gOutputHwnd,TIME_IDENTIFIER_OUTPUTTEST);
	
	

	nReadThread	=	FALSE;
	if ( hReadThread != NULL )
	{
		//WaitForSingleObject(hReadThread,800);//INFINITE
		//CloseHandle(hReadThread);
		//hReadThread	=	NULL;
		
		//if(::WaitForSingleObject(hReadThread,800)   ==   WAIT_TIMEOUT)   
		//{   
			//如果超时：   
			//TerminateThread(hReadThread,NULL);
		//}
		//CloseHandle(hReadThread);
		//hReadThread   =   NULL;
		
		//结束通讯线程
		SetEvent(m_RecvThreadEvent);
		Sleep(100);
		//关闭线程退出事件句柄
		CloseHandle(m_RecvThreadEvent);

		CloseHandle(hReadThread);
		hReadThread   =   NULL;
	}

	DeleteCriticalSection(&lpCriticalSection);

	TranAutoStopMode();

	if ( NULL != hComm )
	{
		DisconnectCom(hComm);
		hComm	=	NULL;
	}
	
	if ( INVALID_SOCKET != hRaeadSocket )
	{
		DisconnectRj45();
		hRaeadSocket	=	INVALID_SOCKET;
	}

	if ( osReader.hEvent != NULL )
	{
		CloseHandle(osReader.hEvent);
		osReader.hEvent	=	NULL;
	}

}


void COutputTest::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnClose();
}


int  COutputTest::ConnecCom(HANDLE *hScanner, char *szPort, int nBaudRate)
{
	HANDLE hComm;
	
	hComm = CreateFile( szPort,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
	if (hComm == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	
	SetupComm(hComm, 0x400, 0x400);  //InQueueSize,OutQueueSize
	SetCommMask(hComm, 0); // disable events  
	
	COMMTIMEOUTS  cto;
	GetCommTimeouts(hComm, &cto);
	cto.ReadIntervalTimeout = 100;
	cto.ReadTotalTimeoutMultiplier = 20 ;
	cto.ReadTotalTimeoutConstant = 200 ;
	cto.WriteTotalTimeoutMultiplier = 20 ;
	cto.WriteTotalTimeoutConstant = 200 ;
	if (!SetCommTimeouts( hComm, &cto))
	{
		CloseHandle(hComm);
		return -1;
	}
	
	int BaudRate[]={9600,19200,38400,57600,115200};
	
	DCB dcb;
	GetCommState(hComm,&dcb);
	
	dcb.BaudRate = BaudRate[nBaudRate];
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity   = NOPARITY;    // 如果8位数据, 则必须无校验
	if(!SetCommState(hComm, &dcb))	
	{
		CloseHandle(hComm);
		return -1;
	}
	
	PurgeComm(hComm, PURGE_TXCLEAR);  // flush transimition queue
	PurgeComm(hComm, PURGE_RXCLEAR);  // flush receiveing queue
	
	
	GetCommTimeouts(hComm, &cto);
	cto.ReadIntervalTimeout = 500;
	cto.ReadTotalTimeoutMultiplier = 100 ;
	cto.ReadTotalTimeoutConstant = 1000 ;
	cto.WriteTotalTimeoutMultiplier = 100 ;
	cto.WriteTotalTimeoutConstant = 1000 ;
	
	SetCommTimeouts( hComm, &cto);
	
	*hScanner = hComm;
	return 0;
}

//断开连接
int COutputTest::DisconnectCom(HANDLE hScanner)
{
	CloseHandle(hScanner);
	
	return 0;
}


int COutputTest::ConnectRj45()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int retval;
	SOCKADDR_IN addrSock;
	
	DWORD dwError	=	0;
	char recvbuf[2049]	=	{0};
	int iRecvLen	=	0;
	int recv_len	=	0;
	SOCKADDR_IN SockAddrIn;
	SockAddrIn.sin_family=AF_INET;
	//TRACE("ReadThreadpo:%d\n",m_InforeaderIP[hSocket-m_InitSocket].port);
	//TRACE("ReadThreadip:%s\n",m_InforeaderIP[hSocket-m_InitSocket].ip);
	//SockAddrIn.sin_port=htons(9000);
	//SockAddrIn.sin_addr.S_un.S_addr=inet_addr("192.168.0.120");
	
	iRecvLen	=	sizeof(SOCKADDR);
	int m_HostPort	=	0;
	m_HostPort		=	gAutoParam->Port1;
	m_HostPort		=	(m_HostPort<<8)+gAutoParam->Port2;
	
	
	if(hRaeadSocket==INVALID_SOCKET)
	{
		WSADATA WSAData;
		if (WSAStartup(MAKEWORD(2,2),&WSAData)!=0)
		{
			WSACleanup();
			return 1;
		}

		hRaeadSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		//hRaeadSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);
		if (hRaeadSocket==INVALID_SOCKET)
		{
			//MessageBox("网络连接创建失败！");
			dwError	=	GetLastError();
			MessageBox(theApp.g_LoadString("IDWQB_F0042"));
			return 1;
		}
		
		DWORD u1 = 1;
		ioctlsocket(hRaeadSocket, FIONBIO, &u1);//不阻塞
		
		addrSock.sin_family=AF_INET;
		addrSock.sin_port=htons(m_HostPort);
		addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
		retval=bind(hRaeadSocket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
		if(SOCKET_ERROR==retval)
		{
			closesocket(hRaeadSocket);
			//MessageBox("网络连接绑定失败！");
			MessageBox(theApp.g_LoadString("IDWQB_F0043"));
			return 1;
		}
		recv_len	=	recvfrom(hRaeadSocket,(char*)recvbuf,2048,0,(SOCKADDR*)&SockAddrIn,&iRecvLen);
		
	}
	
	return 0;
}

void COutputTest::DisconnectRj45()
{
	closesocket(hRaeadSocket);
	hRaeadSocket = INVALID_SOCKET;
}


//WM_OUTPUTTESTDATAMSG
afx_msg LRESULT COutputTest::OnOutputtestdatamsg(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 0 == iwParam )
	{
		if ( 0 == lParam )
		{
			

			//OnButtonStop();
			nReadThread	=	FALSE;
			if ( hReadThread != NULL )
			{
				//WaitForSingleObject(hReadThread,500);//INFINITE

				//结束通讯线程
				SetEvent(m_RecvThreadEvent);
				Sleep(50);
				//关闭线程退出事件句柄
				CloseHandle(m_RecvThreadEvent);

				CloseHandle(hReadThread);
				hReadThread	=	NULL;
				
				
			}
			
			int iMsgCnt		=	0;
			int iMsgCount	=	0xFFFF;
			MSG msg;
			while ( iMsgCnt < iMsgCount )
			{
				//清空队列消息
				if ( 0 == PeekMessage(&msg,gOutputHwnd,WM_OUTPUTTESTDATAMSG,WM_OUTPUTTESTDATAMSG,PM_REMOVE) )
				{
					iMsgCount	=	iMsgCount;
					break;
				}
				iMsgCnt ++;
			}

			TranAutoStopMode();

			//RS485输出口
			GetDlgItem(IDC_COMBO_RS485O)->ShowWindow(SW_HIDE);
			
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_CLEARSCREEN)->EnableWindow(TRUE);
			
			GetDlgItem(IDC_BUTTON_ClearMemory)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_ReportNow)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_GetTagInfo)->EnableWindow(TRUE);
			
			GetDlgItem(IDC_BUTTON_WEG26START)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_WEG26STOP)->EnableWindow(TRUE);
			
			GetDlgItem(IDC_BUTTON_WEG34START)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_WEG34STOP)->EnableWindow(TRUE);

			::PostMessage(gOutputHwnd, WM_OUTPUTTESTDATAMSG, 0, 2);

			
		}
		else if ( 1 == lParam )
		{
			int i = 0;
			int k = 0;
			DWORD dwRes	=	0;
			char tempbuf[1025]	=	{0};
			int recv_len	=	0;
			char chContent[4096] = {0};//内容
			
			CString strtmp;
			int iIndexItem	=	0;

			CListCtrl *m_ListInfo	=	((CListCtrl*)GetDlgItem(IDC_LIST_INFO));
			CButton	*m_checkone		=	(CButton*)GetDlgItem(IDC_CHECK_ONE);

			
			if ( 0 == giCount )
			{
				giCount = 0;
				return 0;
			}
			Debug_Printf("(%d):%s\r\n",giCount, (char*)gRecvBuf);
			#if 0
			

			//先看队列中是否有
			if (s_vmeEventQueue.head == s_vmeEventQueue.tail)
			{
				s_vmeEventQueue.head = s_vmeEventQueue.tail;
				WriteAppLogFile(__FILE__, __LINE__, "Empty=(%d,%d)", s_vmeEventQueue.head, s_vmeEventQueue.tail);
				return FALSE;
			}
			
			
			
			strcpy(chContent, s_vmeEventQueue.d[s_vmeEventQueue.head].chPhCon);
			
			s_vmeEventQueue.head = (s_vmeEventQueue.head + 1) % (MAX_EVENT_NUMBER);
			
			glen_temp	=	strlen(chContent);
			#else
			DataPacket dt;
			if ( FALSE == m_ReadListOut.IsEmpty() )
			{
				
				
				dt = m_ReadListOut.GetHead();

				CSingleLock csl(&m_readLock);
				csl.Lock();
				m_ReadListOut.RemoveHead();
				csl.Unlock();


				memcpy(chContent, dt.chbuf, dt.len);
				glen_temp	=	dt.len;
				//TRACE("%d:%s\n", dt.len, dt.chbuf);
			}

			#endif


			//得到解析的数据
			//dwRes	=	GetAutoModeRecvTran((char *)gRecvBuf, glen_temp, chArray, k);
			dwRes	=	GetAutoModeRecvTran((char *)chContent, glen_temp, chArray, k);
			if ( dwRes )
			{
				iIndexItem	=	m_ListInfo->GetItemCount();

				if ( 1 == is485Out )
				{
					//0.No
					//1.Count
					//2.Antenna
					//3.EPC
					strtmp	=	chArray[0];//
					for ( i = 0; i < iIndexItem; i++)
					{
						m_ListInfo->GetItemText(i, 3, tempbuf, MAX_PATH);//原来的EPC在第4列
						if ( strtmp.Find(tempbuf) != -1 )
						{
							//找到
							break;
						}
					}
				}
				else
				{
					//(7)数据输出格式：0-简化格式，1-标准格式，2-XML格式。缺省值为0。
					if ( 0 == gAutoParam->OutputManner || 2 == gAutoParam->OutputManner )
					{
						//0.No
						//1.Count
						//2.Antenna
						//3.Type
						//4.EPC
						strtmp	=	chArray[3];//解析在第3下标,取EPC

						//;是否输出如这种格式的EPC,如:1234 5678 1122 3344,四位一组.1---是,0---不是(保持原来的)
						int iG = GetPrivateProfileInt("Setting","FormatG", 0, theApp.strConfigPath);
						if (iG)
						{	
							//输出EPC如：1234 5678 1122 3344
							//EPC
							strtmp.Replace("\r\n", "");
							strtmp.Replace(" ", "");
							int mm = strtmp.GetLength();
							int mi = 0;
							CString strR = "";
							while (mi < mm)
							{
								if ( 0 != mi && mi % 4 == 0 )
								{
									strR += " ";
								}
								strR += strtmp.Mid(mi,1);
								mi++;
							}
							strtmp = strR;
							
						}

						for ( i = 0; i < iIndexItem; i++)
						{
							m_ListInfo->GetItemText(i, 4, tempbuf, MAX_PATH);//原来的EPC在第4列
							if ( strtmp.Find(tempbuf) != -1 )
							{
								//找到
								break;
							}
						}
						
					}
					else
					{
						//0.No
						//1.First Time
						//2.End Time
						//3.Count
						//4.Antenna
						//5.Type
						//6.EPC
						strtmp	=	chArray[5];//解析在第5列,取EPC

						//;是否输出如这种格式的EPC,如:1234 5678 1122 3344,四位一组.1---是,0---不是(保持原来的)
						int iG = GetPrivateProfileInt("Setting","FormatG", 0, theApp.strConfigPath);
						if (iG)
						{	
							//输出EPC如：1234 5678 1122 3344
							//EPC
							strtmp.Replace("\r\n", "");
							strtmp.Replace(" ", "");
							int mm = strtmp.GetLength();
							int mi = 0;
							CString strR = "";
							while (mi < mm)
							{
								if ( 0 != mi && mi % 4 == 0 )
								{
									strR += " ";
								}
								strR += strtmp.Mid(mi,1);
								mi++;
							}
							strtmp = strR;
							
						}

						for ( i = 0; i < iIndexItem; i++)
						{
							m_ListInfo->GetItemText(i, 6, tempbuf, MAX_PATH);//原来的EPC在第6列
							if ( strtmp.Find(tempbuf) != -1 )
							{
								//找到
								break;
							}
						}

					}
				}
				

				if ( m_checkone->GetCheck() == 0 )
				{
					//没有选中时
					i = iIndexItem;
					giCount = i+1;
					
				}
				else
				{
					//选中时
					giCount	=	iIndexItem;
				}

				if ( tempbuf[0] == 0x00 )
				{
					i = iIndexItem;
				}

				if ( i < iIndexItem )
				{
					//修改的
					if ( 1 == is485Out )
					{
						m_ListInfo->GetItemText(i, 1, tempbuf, MAX_PATH);
						k = atoi(tempbuf);
						k++;
						sprintf(tempbuf, "%04d", k);
						m_ListInfo->SetItemText(i, 1, tempbuf);
					}
					else
					{
					if ( 0 == gAutoParam->OutputManner || 2 == gAutoParam->OutputManner )
					{
						m_ListInfo->GetItemText(i, 1, tempbuf, MAX_PATH);
						k = atoi(tempbuf);
						k++;
						sprintf(tempbuf, "%04d", k);
						m_ListInfo->SetItemText(i, 1, tempbuf);
					}
					else
					{
						m_ListInfo->GetItemText(i, 3, tempbuf, MAX_PATH);
						k = atoi(tempbuf);
						k++;
						if ( iPlatform	==	1 )	//0---626, 1---218)
						{
							sprintf(tempbuf, "%s", chArray[2]);
						}
						else
						{
							sprintf(tempbuf, "%04d", k);
						}
						m_ListInfo->SetItemText(i,3,tempbuf);
					}
					}
				}
				else
				{
					//新增加的
					//0.No
					//1.First Time
					//2.End Time
					//3.Count
					//4.Antenna
					//5.Type
					//6.EPC
					//解析出来的
					

					if ( 1 == is485Out )
					{
						//0.No
						//1.Count
						//2.Antenna
						//3.EPC
						for ( i = iIndexItem; i < k+iIndexItem; i++)
						{
							itoa(i+1,tempbuf,10);
							m_ListInfo->InsertItem(i,tempbuf);	//序号
							m_ListInfo->EnsureVisible(i, FALSE); 

							strtmp	=	chArray[0];
							m_ListInfo->SetItemText(i,2,strtmp.Left(2));
							m_ListInfo->SetItemText(i,3,strtmp.Right(strtmp.GetLength() - 2));
							
						}

						giCount += k-1;
					}
					else
					{
						itoa(iIndexItem+1,tempbuf,10);
						m_ListInfo->InsertItem(iIndexItem,tempbuf);	//序号
						m_ListInfo->EnsureVisible(iIndexItem, FALSE); 

						//(7)数据输出格式：0-简化格式，1-标准格式，2-XML格式。缺省值为0。
						for ( i = 0; i < k; i++)
						{
							strtmp	=	chArray[i];

							//;是否输出如这种格式的EPC,如:1234 5678 1122 3344,四位一组.1---是,0---不是(保持原来的)
							int iG = GetPrivateProfileInt("Setting","FormatG", 0, theApp.strConfigPath);
							if (iG)
							{	
								int cc = 5;
								//(7)数据输出格式：0-简化格式，1-标准格式，2-XML格式。缺省值为0。
								if ( 0 == gAutoParam->OutputManner || 2 == gAutoParam->OutputManner )
								{
									cc = 3;
								}
								//输出EPC如：1234 5678 1122 3344
								if ( cc == i )
								{
									//EPC
									strtmp.Replace("\r\n", "");
									strtmp.Replace(" ", "");
									int mm = strtmp.GetLength();
									int mi = 0;
									CString strR = "";
									while (mi < mm)
									{
										if ( 0 != mi && mi % 4 == 0 )
										{
											strR += " ";
										}
										strR += strtmp.Mid(mi,1);
										mi++;
									}
									strtmp = strR;
								}
							}

							m_ListInfo->SetItemText(iIndexItem,i+1,strtmp);
						}
					}

				}

				
			}

			//////////////////////////////////////////////////////////////////////////
			strtmp.Format("%d", giCount);
			((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValueS))->SetWindowText(strtmp);
			if ( giCount > 9999 )
			{
				strtmp = "9999";
			}
			((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetWindowText(strtmp);
			RECT rect;
			((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->GetWindowRect(&rect);
			ScreenToClient(&rect);         //转换到在对话框中的位置
			InvalidateRect(&rect,TRUE);

			//////////////////////////////////////////////////////////////////////////
			
			
			
		}
		else if ( 2 == lParam )
		{
			giCount = 0;
			CString strtmp;
			strtmp.Format("%d", giCount);
			((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->SetWindowText(strtmp);
			((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValueS))->SetWindowText(strtmp);
			RECT rect;
			((CStatic*)GetDlgItem(IDC_STATIC_ReadNumValue))->GetWindowRect(&rect);
			ScreenToClient(&rect);         //转换到在对话框中的位置
			InvalidateRect(&rect,TRUE);
			
			GetDlgItem(IDC_EDIT_Wiegand)->SetWindowText("");
		}
	}
	else if ( 2 == iwParam )
	{
		OnInitUIText();//界面和文本更新
	}
	else if ( 3 == iwParam )
	{
		//右键
		//导出写TXT文件
		CListCtrl *pListInfo	=	(CListCtrl*)GetDlgItem(IDC_LIST_INFO);
			int nRow	=	pListInfo->GetItemCount();	//取得有多少行
			if ( nRow <= 0 )
			{
				if ( 0 == ilParam )
				{
					//MessageBox("List is empty!","VI-720", MB_ICONERROR|MB_OK );
					MessageBox(theApp.g_LoadString("IDWQB_F0061"),theApp.g_LoadString("IDWQB_F0057"), MB_ICONERROR|MB_OK );
				}
				return 1;
			}


			CString filename;
			//取当前日期，时间
			SYSTEMTIME sysTime;

			GetLocalTime(&sysTime);
			CString strTime;
			
			strTime.Format("%04d%02d%02d.csv", sysTime.wYear, sysTime.wMonth, sysTime.wDay);

			if ( 0 == ilParam )
			{
				//CFileDialog dlg(FALSE,NULL,NULL,OFN_EXPLORER ,_T("TXT files(*.txt)|*.TXT"));
				CFileDialog dlg(FALSE,_T("csv"),strTime,
					OFN_EXPLORER,
					_T("csv files(*.csv)|*.csv|\0"),NULL);
				
				dlg.m_ofn.lpstrTitle	=	_T("export");
				//dlg.m_ofn.lpstrTitle	=	theApp.g_LoadString("IDWQB_D0157");
				if(dlg.DoModal()==IDOK)
				{
					filename=dlg.GetPathName();	//取得全路径名
				}
				else
				{
					return 1;
				}
			}
			else 
			{
				filename = "";
				filename += g_szCurPath;
				filename += strTime;
			}

			
			int i	=	0;
			char *chRecv	=	new char[2*1024*1024];
			int chCnt	=	0;
			CString strT;

			while ( i < nRow )
			{
				//strT	=	m_ListID.GetItemText(i,0);//NO
				//memcpy(chRecv+chCnt, strT, strT.GetLength());
				//chCnt	+=	strT.GetLength();

				//*(chRecv + chCnt++)	=	',';

				//(7)数据输出格式：0-简化格式，1-标准格式，2-XML格式。缺省值为0。
				if ( 0 == gAutoParam->OutputManner || 2 == gAutoParam->OutputManner )
				{
					*(chRecv + chCnt++)	= '\x09';	//"\x27";
					strT	=	pListInfo->GetItemText(i,1);//Count
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();

					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,2);//Antenna
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();

					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,3);//Type
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();

					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,4);//EPC
					memcpy(chRecv+chCnt, strT, strT.GetLength()-2);
					chCnt	+=	strT.GetLength()-2;

					

					
				}
				else
				{
					*(chRecv + chCnt++)	= '\x09';	//"\x27";
					strT	=	pListInfo->GetItemText(i,1);//First Time
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();
					
					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,2);//End Time
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();
					
					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,3);//Count
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();
					
					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,4);//Antenna
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();
				
					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,5);//Type
					memcpy(chRecv+chCnt, strT, strT.GetLength());
					chCnt	+=	strT.GetLength();

					*(chRecv + chCnt++)	=	',';

					*(chRecv + chCnt++)	= '\x09';
					strT	=	pListInfo->GetItemText(i,6);//EPC
					memcpy(chRecv+chCnt, strT, strT.GetLength()-2);
					chCnt	+=	strT.GetLength()-2;

				}

				

				
				
				//*(chRecv + chCnt++)	=	',';

				*(chRecv + chCnt++)	=	0x0D;
				*(chRecv + chCnt++)	=	0x0A;

				i++;

			}// end of while ( iCnt < nRow )


			*(chRecv + chCnt)	=	0x00;

			WriteBufFile(chRecv, chCnt, filename,0);

			delete[] chRecv;

			if ( 0 == ilParam )
			{
				//AfxMessageBox("Export finished!");
				//MessageBox("Export finished!","VI-720", MB_ICONINFORMATION|MB_OK );
				MessageBox(theApp.g_LoadString("IDWQB_F0060"),theApp.g_LoadString("IDWQB_F0058"), MB_ICONINFORMATION|MB_OK );
				ShellExecute(NULL,"open",filename,NULL,NULL,SW_SHOWNORMAL);
			

			}



	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//用途:		本模块的消息静态成员函数,回调函数
//函数名:	CallBack_DataOutput
//功能:		
//输入参数:	hWnd--handle of CWnd that called SetTimer
//			nMsg--WM_TIMER
//			nIDEvent--timer identification
//			dwTime--system time 
//输出参数:	无
//返回值:	无
//备注:TIME_IDENTIFIER_TEST, INTERVALTIME
//////////////////////////////////////////////////////////////////////////
void WINAPI COutputTest::CallBack_DataOutput(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime)
{
	//Debug_Printf("r:%s\r\n","hello");
}


//自动模式下读线程函数
DWORD WINAPI COutputTest::ReadThreadFuncTag(LPVOID pParam)
{
	
	DWORD dwRes;
	char recvbuf[4096]	=	{0};
	char tempbuf[4096]	=	{0};
	
	int recv_len	=	0;
	int len_temp	=	0;
	DWORD lReadSize =	0;
	
	CString strtmp;
	int m=0;
	HANDLE hRSTemp	=	INVALID_HANDLE_VALUE;

	COutputTest* m_pStandard	=	(COutputTest*)pParam;

	int iRecvLen	=	0;
	SOCKADDR_IN SockAddrIn;
	SockAddrIn.sin_family=AF_INET;
	iRecvLen	=	sizeof(SOCKADDR);

	int iIndexItem	=	0;
	int iRecvCombyte	=	166;
	

#if defined (ENABLE485TXOUTPUT)
	if ( 1 == gAutoParam->OutInterface )
	{
		//485输出
		is485Out	=	1;
	}
#else
	is485Out	=	0;
#endif

	if ( 1 == is485Out )
	{
		iRecvCombyte	=	166;
	}
	
	//输出接口：0－RS232口，1－RS485口，2－RJ45口。缺省值为0。 3- Wiegand26    4- Wiegand34
	//主动模式的标记 -1--谁都不是，0--串口，1--485模式,2--网口,3-Wiegand26;4-Wiegand34;
	switch(ConnectMode)
	{
	case 0://网口
		switch (gAutoParam->OutInterface)
		{
		case 0://0－RS232口
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 1://1－RS485口
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 2://2－RJ45口
			
			break;
		case 3://3- Wiegand26
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 4://4- Wiegand34
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		default:
			
			break;
		}
		break;
	case 1://RS232
		switch (gAutoParam->OutInterface)
		{
		case 0://0－RS232口
			hRSTemp = m_hScanner;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 1://1－RS485口
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 2://2－RJ45口
			
			break;
		case 3://3- Wiegand26
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 4://4- Wiegand34
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		default:
			
			break;
		}
		break;
	case 2://RS485
		switch (gAutoParam->OutInterface)
		{
		case 0://0－RS232口
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 1://1－RS485口
			hRSTemp = m_hScanner;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 2://2－RJ45口
			
			break;
		case 3://3- Wiegand26
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		case 4://4- Wiegand34
			hRSTemp = hComm;
			osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			break;
		default:
			
			break;
		}
		break;
	}

	recv_len=0;
	HANDLE WaitHandles[2]; //监听事件数组
	WaitHandles[0] = m_RecvThreadEvent;
	WaitHandles[1] = osReader.hEvent;


	while( nReadThread )
	{
		if ( lpCriticalSection.LockSemaphore != NULL )
		{
			EnterCriticalSection(&lpCriticalSection);
		}

		if (WaitForSingleObject(m_RecvThreadEvent, 0) == WAIT_OBJECT_0)
		{
			if ( lpCriticalSection.LockSemaphore != NULL )
			{
				LeaveCriticalSection(&lpCriticalSection);
			}
			break;
		}

		Sleep(1);
		//TRACE("nReadThread=%d\n", nReadThread);

		//这里是为了测试显示的
		memset(recvbuf, 0, 1024);
		//memcpy(recvbuf,"abcd",4);
		//Debug_Printf("r:%s\r\n",recvbuf);
		//continue;

		if ( gAutoParam->OutInterface	==	2 )//主动模式的标记 -1--谁都不是，0--串口，1--485模式,2--网口,3-Wiegand26;4-Wiegand34;
		{
			recv_len	=	recvfrom(hRaeadSocket, (char*)recvbuf, 1024, 0, (SOCKADDR*)&SockAddrIn, &iRecvLen);
			len_temp	=	recv_len;

		}
		else if ( 0 == gAutoParam->OutInterface || 1 == gAutoParam->OutInterface || 3 == gAutoParam->OutInterface || 4 == gAutoParam->OutInterface)//0--串口
		{
			
			//If the function succeeds, the return value is nonzero. 
			if (!ReadFile(hRSTemp, (char*)recvbuf, 166, &lReadSize, &osReader))  
			{
				if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
				{
					// Error in communications; report it.
					//continue;
				}
				else
				{
					BOOL bFlag = FALSE;
					//dwRes = WaitForSingleObject(osReader.hEvent, INFINITE);
					dwRes=WaitForMultipleObjects(2,WaitHandles,FALSE,INFINITE);
					switch(dwRes)
					{
					case WAIT_OBJECT_0 + 0:
						{
							bFlag = TRUE;
							if ( lpCriticalSection.LockSemaphore != NULL )
							{
								LeaveCriticalSection(&lpCriticalSection);
							}
							break;
						}
						// Read completed.
					case WAIT_OBJECT_0 + 1:
						if (!GetOverlappedResult(hRSTemp, &osReader, &lReadSize, FALSE))
						{
							// Error in communications; report it.
							//continue;
						}
						break;
					}
					
					if (bFlag)
					{
						break;
					}

				}
			}

			len_temp = (int)lReadSize;
			
		}//end of if if ( nActiveModeFlag	=	2 )//主动模式的标记 -1--谁都不是，0--串口，1--485模式,2--网口,3-Wiegand26;4-Wiegand34;

	

		strtmp = _T("");
		//continue;
		if ( len_temp > 0 && len_temp < 512 )
		{

			Bcd2Asc(strtmp.GetBuffer(2048), (char*)recvbuf, len_temp*2);
			strtmp.ReleaseBuffer();

			//strtmp.Replace("0D0A","\r\n");
			WriteAppLogFile(__FILE__, __LINE__, "Recv[%04d]:(%04d)%s\r\n", len_temp, giCount, strtmp);
#if 0			
			
			//////////////////////////////////////////////////////////////////////////
			memset(gRecvBuf, 0x00, sizeof(gRecvBuf));
			memcpy(gRecvBuf, recvbuf, len_temp);
			glen_temp	=	len_temp;

			if (((s_vmeEventQueue.tail + 1) % (MAX_EVENT_NUMBER)) == s_vmeEventQueue.head)
			{
				//队列溢出了
				glen_temp	=	len_temp;
				WriteAppLogFile(__FILE__, __LINE__, "Full=(%d,%d)", s_vmeEventQueue.head, s_vmeEventQueue.tail);
			}
			else
			{
				strcpy(s_vmeEventQueue.d[s_vmeEventQueue.tail].chPhCon , recvbuf);
				s_vmeEventQueue.tail = (s_vmeEventQueue.tail + 1) % (MAX_EVENT_NUMBER);
			}
#else
			DataPacket dt;
			dt.len	=	len_temp;
			sprintf(dt.chbuf, _T("%s"), recvbuf);
			
			CSingleLock csl(&m_readLock);
			csl.Lock();

			m_ReadListOut.AddTail(dt);

			csl.Unlock();

#endif
			::PostMessage(gOutputHwnd, WM_OUTPUTTESTDATAMSG, 0, 1);
			//////////////////////////////////////////////////////////////////////////
			

			giCount++;

		}
		else if ( len_temp > 512 )
		{
			Bcd2Asc(strtmp.GetBuffer(2048), (char*)recvbuf, len_temp*2);
			strtmp.ReleaseBuffer();
			//strtmp.Replace("0D0A","\r\n");
			WriteAppLogFile(__FILE__, __LINE__, "Recw[%04d]:(%04d)%s\r\n", len_temp, giCount, strtmp);

			//giCount++;
		}
		else 
		{
			WriteAppLogFile(__FILE__, __LINE__, "Recx[%04d]:(%04d)%s\r\n", len_temp, giCount, strtmp);
			
			//giCount++;
		}


		if ( lpCriticalSection.LockSemaphore != NULL )
		{
			LeaveCriticalSection(&lpCriticalSection);
		}

	}//end of while( nReadThread )


	if ( osReader.hEvent != NULL )
	{
		CloseHandle(osReader.hEvent);
		osReader.hEvent	=	NULL;
	}
	

	return 0;

}


//得到解析的数据
BOOL	COutputTest::GetAutoModeRecvTran(char *chInBuf, int iInSize, char **chOutBuf, int &iOutSize)
{
	int m = 0;
	int k = 0;
	int i = 0;
	char chSub[16];
	char chTemp[MAX_PATH]	=	{0};
	char *chTmp	=	NULL;
	char *pTemp	=	NULL;
	char *pStart	=	chInBuf;
	char *pEnd = (char*)(chInBuf+iInSize);

	int j = 0;
	char *chFind[]	=	{"Disc:", "Last:", "Count:", "Ant:", "Type:", "Tag:"};
	//(7)数据输出格式：0-简化格式，1-标准格式，2-XML格式。缺省值为0。
	BYTE	OutputManner	=	gAutoParam->OutputManner;
	
	try
	{
		if ( 1 == is485Out )
		{
			//TRACE("aa=%d\n", iInSize);
			BOOL bFlagLeft = 0;
			while ( i < iInSize )
			{
				if ( chInBuf[i] == 0x02 )
				{
					m = i;
					bFlagLeft	=	1;
				}
				else if ( chInBuf[i] == 0x03 )
				{
					if ( bFlagLeft == 1 )
					{
						bFlagLeft	=	0;

						j = i - m - 1;
						if ( j > 166 || j <= 0 )
						{
							i++;
							continue;
						}
						memset(chTemp, 0x00, MAX_PATH);
						memcpy(chTemp, &chInBuf[m+1], j);
						
						
						memcpy(chOutBuf[k], chTemp, j);
						
						*(chOutBuf[k]+j)	=	0x00;
						
						k++;
					}
					
				}
				i++;
			}
		}
		else
		{
			if ( 0 == OutputManner )
			{
				//0-简化格式
				//如:00001, 0F, 02, 2222                                                                                                                        
				strcpy(chSub, ", ");
				while ( pStart < pEnd )
				{
					pTemp	=	strstr(pStart, chSub);
					if ( NULL == pTemp )
					{
						pTemp	=	pEnd;
						
					}
					
					int iF = 0;
					//取每一个字段
					memset(chTemp, 0x00, MAX_PATH);
					memcpy(chTemp, pStart, pTemp-pStart);
					
					memcpy(chOutBuf[k], chTemp, pTemp-pStart);
					
					*(chOutBuf[k]+(pTemp-pStart-iF))	=	0x00;
					
					
					k++;//取下一个字符串
					j++;//查下一个
					
					
					pStart	=	pTemp + strlen(chSub);
					
					
				}



			}
			else if ( 1 == OutputManner )
			{
				//1-标准格式
				//如:Disc:2012/11/19 10:05:19, Last:2012/11/19 10:05:19, Count:00001, Ant:0F, Type:02, Tag:2222                                                                          
				strcpy(chSub, ", ");
				while ( pStart < pEnd )
				{
					pTemp	=	strstr(pStart, chSub);
					if ( NULL == pTemp )
					{
						pTemp	=	pEnd;
						
					}
					
					int iF = strlen(chFind[j]);
					//取每一个字段
					memset(chTemp, 0x00, MAX_PATH);
					memcpy(chTemp, pStart, pTemp-pStart);
					chTmp	=	strstr(chTemp, chFind[j]);
					if ( chTmp == NULL )
					{
						memcpy(chOutBuf[k], chTemp, pTemp-pStart);
					}
					else
					{
						memcpy(chOutBuf[k], chTemp+iF, pTemp-pStart-iF);
					}
					*(chOutBuf[k]+(pTemp-pStart-iF))	=	0x00;


					k++;//取下一个字符串
					j++;//查下一个

					
					pStart	=	pTemp + strlen(chSub);


				}

				
			}
			else 
			{
				return FALSE;
			}
		}

		iOutSize	=	k;
	}
	catch (CException *e)
	{
		TRACE(_T("Warning: 异常. 错误信息: Error:%d; 文件: %s; 行: %d\n"), e->ReportError(), __FILE__, __LINE__);
		return FALSE;
	}


	return TRUE;
}

void COutputTest::OnCheck1Output() 
{
	// TODO: Add your control notification handler code here
	//是否显示调试窗口
	RECT rcTemp	=	{0,0,0,};
	if ( ((CButton*)GetDlgItem(IDC_CHECK1_OUTPUT))->GetCheck() == 1 )
	{
		//选中，显示调试输出
		rcTemp.left		=	rectListInfo.left;
		rcTemp.top		=	rectListInfo.top;
		rcTemp.right	=	rectListInfo.right;
		rcTemp.bottom	=	rectListInfo.bottom;
		
		((CListCtrl*)GetDlgItem(IDC_EDIT_Wiegand))->ShowWindow(SW_SHOW);
		((CListCtrl*)GetDlgItem(IDC_LIST_INFO))->MoveWindow(&rcTemp, TRUE);

	}
	else
	{
		
		rcTemp.left		=	rectListInfo.left;
		rcTemp.top		=	rectListInfo.top;
		rcTemp.right	=	rectListInfo.right;
		rcTemp.bottom	=	rectEditOutput.bottom;
		
		((CListCtrl*)GetDlgItem(IDC_EDIT_Wiegand))->ShowWindow(SW_HIDE);
		((CListCtrl*)GetDlgItem(IDC_LIST_INFO))->MoveWindow(&rcTemp, TRUE);
	}

}

void COutputTest::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//TRACE("(%d,%d)\n", point.x, point.y);
	CPropertyPage::OnMouseMove(nFlags, point);
}


BOOL COutputTest::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	::PostMessage(gOutputHwnd, WM_OUTPUTTESTDATAMSG, 0, 0);
	return CPropertyPage::OnKillActive();
}

BOOL COutputTest::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//如果在列表中点右键
	if(WM_RBUTTONDOWN == pMsg->message )
	{
		if ( pMsg->hwnd == GetDlgItem(IDC_LIST_INFO)->m_hWnd )
		{
			PopupMenu();
			return TRUE;
		}
	}
	return CPropertyPage::PreTranslateMessage(pMsg);
}
