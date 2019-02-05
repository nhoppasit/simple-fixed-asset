// ISO6BTest.cpp : implementation file
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "ISO6BTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
HWND	gEcpISO6B;	//6B窗体的句柄
BYTE ISO6B_IDBuffer[MAX_LABELS][ID_MAX_SIZE_64BIT+1]={0};
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
static void PopupMenu()
{
	CPoint point;
	GetCursorPos( & point );
	CMenu menuPopup;
	menuPopup.CreatePopupMenu();
	
	//menuPopup.AppendMenu( MF_STRING, 100, _T("Export"));
	menuPopup.AppendMenu( MF_STRING, 100, theApp.g_LoadString("IDWQB_E0037"));
	
	//menuPopup.AppendMenu( MF_SEPARATOR );
	//menuPopup.AppendMenu( MF_STRING, 101, _T("Exit"));
	
	int nCmd = (int) menuPopup.TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, AfxGetMainWnd() );
	switch( nCmd )
	{
	case	100:
		//AfxMessageBox(_T("退出"));
		//CMainFrame::OnEditComm ();
		//::SendMessage(FrameHwnd, WM_CLOSE, 0, 0);
		::PostMessage(gEcpISO6B,WM_USERTIMERDATATRan,0,0);	//导出TXT
		break;
		//case	101:
		//	::PostMessage(gEcpISO6C,WM_CLOSE,0,0);
		//	break;
		
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////


// CISO6BTest property page

IMPLEMENT_DYNCREATE(CISO6BTest, CPropertyPage)

CISO6BTest::CISO6BTest() : CPropertyPage(CISO6BTest::IDD)
{
	//{{AFX_DATA_INIT(CISO6BTest)
	m_Antenna1 = TRUE;
	m_Antenna2 = FALSE;
	m_Antenna3 = FALSE;
	m_Antenna4 = FALSE;
	m_ListTag = FALSE;
	m_ListTagID = FALSE;
	m_RWAddress = 0;
	m_RWLen = 1;
	m_RWData = _T("");
	m_ReadDataBlock = FALSE;
	m_WriteDataBlock = FALSE;
	m_ListSelectTagID = FALSE;
	m_SCmd = 0;
	m_SAddress = 0;
	m_SData = _T("");
	m_PAddress = 0;
	m_WriteAByteData = FALSE;
	//}}AFX_DATA_INIT
}

CISO6BTest::~CISO6BTest()
{
}

void CISO6BTest::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CISO6BTest)
	DDX_Control(pDX, IDC_COMBO2, m_TagID);
	DDX_Control(pDX, IDC_LIST2, m_ListData);
	DDX_Control(pDX, IDC_COMBO1, m_Interval);
	DDX_Control(pDX, IDC_LIST1, m_ListID);
	DDX_Check(pDX, IDC_CHECK1, m_Antenna1);
	DDX_Check(pDX, IDC_CHECK2, m_Antenna2);
	DDX_Check(pDX, IDC_CHECK3, m_Antenna3);
	DDX_Check(pDX, IDC_CHECK4, m_Antenna4);
	DDX_Check(pDX, IDC_CHECK5, m_ListTag);
	DDX_Check(pDX, IDC_CHECK6, m_ListTagID);
	DDX_Text(pDX, IDC_EDIT1, m_RWAddress);
	DDX_Text(pDX, IDC_EDIT2, m_RWLen);
	DDX_Text(pDX, IDC_EDIT3, m_RWData);
	DDV_MaxChars(pDX, m_RWData, 32);
	DDX_Check(pDX, IDC_CHECK8, m_ReadDataBlock);
	DDX_Check(pDX, IDC_CHECK9, m_WriteDataBlock);
	DDX_Check(pDX, IDC_CHECK7, m_ListSelectTagID);
	DDX_Radio(pDX, IDC_RADIO1, m_SCmd);
	DDX_Text(pDX, IDC_EDIT5, m_SAddress);
	DDX_Text(pDX, IDC_EDIT6, m_SData);
	DDV_MaxChars(pDX, m_SData, 16);
	DDX_Text(pDX, IDC_EDIT4, m_PAddress);
	DDX_Check(pDX, IDC_CHECK10, m_WriteAByteData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CISO6BTest, CPropertyPage)
	//{{AFX_MSG_MAP(CISO6BTest)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USERTIMERDATATRan, OnUsertimerdatatran)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CISO6BTest message handlers
void CISO6BTest::OnInitUIText()//界面和文本更新
{
	SetWindowText(theApp.g_LoadString("IDWQA_E0001"));//6C Test

	GetDlgItem(IDC_STATIC_SetAntForTest_6B)->SetWindowText(theApp.g_LoadString("IDWQB_E0002"));//Select Antenna for Test
	GetDlgItem(IDC_STATIC_ListIDofTags_6B)->SetWindowText(theApp.g_LoadString("IDWQB_E0003"));//List ID of Tags
	GetDlgItem(IDC_STATIC_Interval_6B)->SetWindowText(theApp.g_LoadString("IDWQB_E0004"));//Interval
	GetDlgItem(IDC_STATIC_RWDBlock_6B)->SetWindowText(theApp.g_LoadString("IDWQB_E0005"));//Read and Write Data Block
	GetDlgItem(IDC_STATIC_SelectTagByCon)->SetWindowText(theApp.g_LoadString("IDWQB_E0006"));//Select Tags by Condition
	GetDlgItem(IDC_STATIC_Informationt)->SetWindowText(theApp.g_LoadString("IDWQB_E0007"));//Information
	GetDlgItem(IDC_STATIC_WritePro)->SetWindowText(theApp.g_LoadString("IDWQB_E0008"));//Write Protect
	GetDlgItem(IDC_CHECK1)->SetWindowText(theApp.g_LoadString("IDWQB_E0009"));//ANT1
	GetDlgItem(IDC_CHECK2)->SetWindowText(theApp.g_LoadString("IDWQB_E0010"));//ANT2
	GetDlgItem(IDC_CHECK3)->SetWindowText(theApp.g_LoadString("IDWQB_E0011"));//ANT3
	GetDlgItem(IDC_CHECK4)->SetWindowText(theApp.g_LoadString("IDWQB_E0012"));//ANT4
	GetDlgItem(IDC_CHECK5)->SetWindowText(theApp.g_LoadString("IDWQB_E0013"));//LabelPresent
	GetDlgItem(IDC_CHECK6)->SetWindowText(theApp.g_LoadString("IDWQB_E0014"));//List Tag ID
	GetDlgItem(IDC_STATIC_AofTagAA)->SetWindowText(theApp.g_LoadString("IDWQB_E0015"));//Address of Tag Data(0/8-223):
	GetDlgItem(IDC_STATIC_LegTagDataBB)->SetWindowText(theApp.g_LoadString("IDWQB_E0016"));//Length of Tag Data(1-32/16):
	GetDlgItem(IDC_STATIC_WrittDataAC)->SetWindowText(theApp.g_LoadString("IDWQB_E0017"));//Written Data(Hex):
	GetDlgItem(IDC_STATIC_SelTagB_6B)->SetWindowText(theApp.g_LoadString("IDWQB_E0018"));//Select Tag
	GetDlgItem(IDC_STATIC_ADdTagDataBC)->SetWindowText(theApp.g_LoadString("IDWQB_E0019"));//Address of Tag Data(8/0-223):
	GetDlgItem(IDC_BUTTON1)->SetWindowText(theApp.g_LoadString("IDWQB_E0020"));//Set Protect
	GetDlgItem(IDC_BUTTON2)->SetWindowText(theApp.g_LoadString("IDWQB_E0021"));//Check Protect
	GetDlgItem(IDC_STATIC_AddressOfTagDAD)->SetWindowText(theApp.g_LoadString("IDWQB_E0022"));//Address of Tag Data(0-223):
	GetDlgItem(IDC_STATIC_CondiBA)->SetWindowText(theApp.g_LoadString("IDWQB_E0023"));//Condition(<=8 HEX Number):
	GetDlgItem(IDC_CHECK7)->SetWindowText(theApp.g_LoadString("IDWQB_E0024"));//List ID of Selected Tags
	GetDlgItem(IDC_CHECK8)->SetWindowText(theApp.g_LoadString("IDWQB_E0025"));//Read
	GetDlgItem(IDC_CHECK9)->SetWindowText(theApp.g_LoadString("IDWQB_E0026"));//Write 4 Bytes
	GetDlgItem(IDC_RADIO1)->SetWindowText(theApp.g_LoadString("IDWQB_E0027"));//Equal Condition
	GetDlgItem(IDC_RADIO2)->SetWindowText(theApp.g_LoadString("IDWQB_E0028"));//Unequal Condition
	GetDlgItem(IDC_RADIO3)->SetWindowText(theApp.g_LoadString("IDWQB_E0029"));//Greater than Condition
	GetDlgItem(IDC_RADIO4)->SetWindowText(theApp.g_LoadString("IDWQB_E0030"));//Less than Condition
	GetDlgItem(IDC_CHECK10)->SetWindowText(theApp.g_LoadString("IDWQB_E0031"));//Write a Byte

	CListCtrl *mIPlist = (CListCtrl*)GetDlgItem(IDC_LIST1);
	LVCOLUMN listColumnTemp;
	CString	strText;
	
	strText	=	theApp.g_LoadString("IDWQB_E0032");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(0, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_E0033");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(1, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_E0034");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(2, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_E0035");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(3, &listColumnTemp);
	strText.ReleaseBuffer();
	


}

void CISO6BTest::UpdateStatus()
{
	switch(m_HardVersion & 0xFF)
	{
	case 0x0B:
		GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		break;
	case 0x0C:
		GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
		GetDlgItem(IDC_CHECK2)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		break;
	case 0x0E:
		GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
		GetDlgItem(IDC_CHECK2)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
		GetDlgItem(IDC_CHECK3)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
		GetDlgItem(IDC_CHECK4)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
		break;
	default:
		if ( ifConnectReader )
		{
			GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		}
	}

	GetDlgItem(IDC_BUTTON1)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_CHECK5)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_CHECK6)->EnableWindow(ifConnectReader && !m_ListTag && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_CHECK7)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock);
	GetDlgItem(IDC_CHECK8)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_CHECK9)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_CHECK10)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_COMBO1)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_COMBO2)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_EDIT1)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_EDIT2)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_EDIT3)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_EDIT4)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_EDIT5)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_EDIT6)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_RADIO1)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_RADIO2)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_RADIO3)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);
	GetDlgItem(IDC_RADIO4)->EnableWindow(ifConnectReader && !m_ListTag && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListSelectTagID);


	//看看RS485通信如何,下面要不要启用?
	#if 0
	if ( ConnectMode == 2 )
	{
		//RS485，则定为500ms
		m_Interval.SetCurSel(6);
		m_Interval.EnableWindow(FALSE);
	}
	#endif
	
}
BOOL CISO6BTest::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	gEcpISO6B = this->GetSafeHwnd();

	DWORD dwStyle = m_ListID.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_ListID.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);

	m_ListID.InsertColumn(0, "No.", LVCFMT_LEFT, 50);
	m_ListID.InsertColumn(1, "ID", LVCFMT_LEFT, 200);
	m_ListID.InsertColumn(2, "Success", LVCFMT_LEFT, 75);
	m_ListID.InsertColumn(3, "Times", LVCFMT_LEFT, 75);

	m_Interval.SetCurSel(3);
	//MSG msg;
//for(;::PeekMessage(&msg,NULL,0,0,PM_REMOVE););//清空队列消息
	UpdateData(FALSE);
	UpdateStatus();

	//6B测试页
	::SendMessage(gEcpISO6B,WM_USERTIMERDATATRan,2,0);	//convert language
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CISO6BTest::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( theApp.iantennaIndex == 0 )
	{
		//一根天线,其它三根不要
		GetDlgItem(IDC_CHECK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK4)->ShowWindow(SW_HIDE);
		
	}
	else
	{
		//四根天线,其它三根要
		GetDlgItem(IDC_CHECK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK4)->ShowWindow(SW_SHOW);
		
	}

	UpdateData(TRUE);
	UpdateStatus();
	UpdateData(FALSE);

	::PostMessage(gEcpISO6B,WM_USERTIMERDATATRan,2,0);	//convert language
	return CPropertyPage::OnSetActive();
}

void CISO6BTest::OnTimer(UINT nIDEvent) 
{
	apiReturn res;
	BYTE be_antenna	=	0;
	int i,j,k,nCounter=0;
	CString str,str_temp,str_tem;
	char temp[64];

	//////////////////////////////////////////////////////////////////////////
	//add by mqs 20130710 新方法
	int itmpAnt	=	0;
	
	itmpAnt	=	Read_times % iModAnt;
	
	itmpAnt = gAntenna[itmpAnt];
	
	Read_times++;

	switch(ConnectMode)
	{
	case 0://网口
		res=Net_SetAntenna(m_hSocket, itmpAnt);
		break;
	case 1://RS232
		res=SetAntenna(m_hScanner, itmpAnt,0);
		break;
	case 2://RS485
		res=SetAntenna(m_hScanner, itmpAnt,RS485Address);
		break;
	}
	//本来开始的时候，只RS485 sleep 一下。可相到218操作R2000模块，所以改成如下
	//if ( 2 == ConnectMode )
	if ( 1 == iPlatform )//0---626, 1---218
	{
		Sleep(ReadRS485SleepTime);
	}
	else if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	if ( _OK != res )
	{
		return;//继续下一轮天线
	}
	//////////////////////////////////////////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////
//原来的旧方法

// 	switch(m_antenna_sel)
// 	{
// 	case 1:
// 	case 2:
// 	case 4:
// 	case 8:
// 		break;
// 	case 3:
// 	case 5:
// 	case 9:
// 		switch (Read_times%2)
// 		{
// 		case 0:
// 			be_antenna=m_antenna_sel-1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 	
// 	case 6:
// 	case 10:
// 		switch (Read_times%2)
// 		{
// 		case 0:
// 			be_antenna=m_antenna_sel-2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 
// 	case 12:
// 		switch (Read_times%2)
// 		{
// 		case 0:
// 			be_antenna=m_antenna_sel-4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 	
// 	case 7:
// 		switch (Read_times%3)
// 		{
// 		case 0:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 
// 	case 11:
// 		switch (Read_times%3)
// 		{
// 		case 0:
// 			be_antenna=8;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 
// 	case 13:
// 		switch (Read_times%3)
// 		{
// 		case 0:
// 			be_antenna=8;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 
// 	case 14:
// 		switch (Read_times%3)
// 		{
// 		case 0:
// 			be_antenna=8;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 
// 	case 15:
// 		switch (Read_times%4)
// 		{
// 		case 0:
// 			be_antenna=8;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 3:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
// 				break;
// 			case 1://RS232
// 				res = SetAntenna(m_hScanner, m_antenna_sel,0);
// 				break;
// 			case 2://RS485
// 				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 	}

	switch(nIDEvent)
	{
	case 0:
		switch(ConnectMode)
		{
		case 0:
			res=Net_ISO6B_LabelPresent(m_hSocket,&nCounter);
			break;
		case 1:
			res=ISO6B_LabelPresent(m_hScanner,&nCounter,0);
			break;
		case 2:
			res=ISO6B_LabelPresent(m_hScanner,&nCounter,RS485Address);
			break;
		}
		if (res==_OK)
		{
			if (nCounter)
			{
				m_ListData.AddString("Found Tag!");
			}
			else
			{
				m_ListData.AddString("No Tag!");
			}
		}
		else
		{
			m_ListData.AddString("No Tag!");
		}
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;
	case 1:
//		if (ifTXMode)
//			res=ISO6B_ReadLabelID_TXMode(m_hScanner,&(ISO6B_IDBuffer[0][0]),&nCounter,RS485Address);
//		else
		{
			switch(ConnectMode)
			{
			case 0:
				res=Net_ISO6B_ReadLabelID(m_hSocket,&(ISO6B_IDBuffer[0][0]),&nCounter);
				break;
			case 1:
				res=ISO6B_ReadLabelID(m_hScanner,&(ISO6B_IDBuffer[0][0]),&nCounter,0);
				break;
			case 2:
				res=ISO6B_ReadLabelID(m_hScanner,&(ISO6B_IDBuffer[0][0]),&nCounter,RS485Address);
				break;
			}
		}

		k=m_ListID.GetItemCount();
		if (res==_OK)
		{
			if (nCounter>0)
			{
				MessageBeep(-1);
			}

			for(i=0;i<nCounter;i++)
			{
				str="";
				for(j=1;j<ID_MAX_SIZE_64BIT+1;j++)
				{
					wsprintf(temp, "%02X", *(BYTE *)&ISO6B_IDBuffer[i][j]);
					str += temp;
				}

				for(j=0;j<k;j++)
				{
					m_ListID.GetItemText(j,1,temp,17);
					str_temp=temp;
					if(str == str_temp) break;
				}
				if(j == k)
				{
					m_ListID.InsertItem(k,itoa(k+1,temp,10));
					m_ListID.SetItemText(k,1,str);
					m_ListID.SetItemText(k,2,"1");
					k++;
				}
				else
				{
					str_temp=m_ListID.GetItemText(j,2);
					m_ListID.SetItemText(j,2,itoa(atoi(str_temp)+1,temp,10));
				}
			}
		}
		for(i=0;i<k;i++)
			m_ListID.SetItemText(i,3,itoa(Read_times,temp,10));
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;
	case 2:
		switch(ConnectMode)
		{
		case 0:
			res=Net_ISO6B_ListSelectedID(m_hSocket,cmd,ptr,mask,DB,&(ISO6B_IDBuffer[0][0]),&nCounter);
			break;
		case 1:
			res=ISO6B_ListSelectedID(m_hScanner,cmd,ptr,mask,DB,&(ISO6B_IDBuffer[0][0]),&nCounter,0);
			break;
		case 2:
			res=ISO6B_ListSelectedID(m_hScanner,cmd,ptr,mask,DB,&(ISO6B_IDBuffer[0][0]),&nCounter,RS485Address);
			break;
		}
		k=m_ListID.GetItemCount();
		if (res==_OK)
		{
			if (nCounter>0)
			{
				MessageBeep(-1);
			}

			for(i=0;i<nCounter;i++)
			{
				str="";
				for(j=0;j<ID_MAX_SIZE_64BIT+1;j++)
				{
					wsprintf(temp, "%02X", *(BYTE *)&ISO6B_IDBuffer[i][j]);
					str += temp;
				}

				for(j=0;j<k;j++)
				{
					m_ListID.GetItemText(j,1,temp,17);
					str_temp=temp;
					if(str == str_temp) break;
				}
				if(j == k)
				{
					m_ListID.InsertItem(k,itoa(k+1,temp,10));
					m_ListID.SetItemText(k,1,str);
					m_ListID.SetItemText(k,2,"1");
					k++;
				}
				else
				{
					str_temp=m_ListID.GetItemText(j,2);
					m_ListID.SetItemText(j,2,itoa(atoi(str_temp)+1,temp,10));
				}
			}
		}
		for(i=0;i<k;i++)
			m_ListID.SetItemText(i,3,itoa(Read_times,temp,10));
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;
	case 3:
		switch(ConnectMode)
		{
		case 0:
			res=Net_ISO6B_ReadByteBlock(m_hSocket,IDTemp,ptr,len,&(DB[0]));
			break;
		case 1:
			res=ISO6B_ReadByteBlock(m_hScanner,IDTemp,ptr,len,&(DB[0]),0);
			break;
		case 2:
			res=ISO6B_ReadByteBlock(m_hScanner,IDTemp,ptr,len,&(DB[0]),RS485Address);
			break;
		}
		if (res==_OK)
		{
			str="HEX:";
			for(i=0;i<len;i++)
			{
				str_temp.Format("%02X ",DB[i]);
				str+=str_temp;
			}

			m_ListData.AddString(str);
			m_ListData.AddString("------------------------------");
			m_ListData.SetCurSel(m_ListData.GetCount()-1);
		}
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;
	case 4:
		switch(ConnectMode)
		{
		case 0:
			res=Net_ISO6B_WriteByteBlock(m_hSocket,IDTemp,ptr,len,DB);
			break;
		case 1:
			res=ISO6B_WriteByteBlock(m_hScanner,IDTemp,ptr,len,DB,0);
			break;
		case 2:
			res=ISO6B_WriteByteBlock(m_hScanner,IDTemp,ptr,len,DB,RS485Address);
			break;
		}
		if (res==_OK)
		{
			m_ListData.AddString("Write Successfully!");
		}
		else
		{
			m_ListData.AddString("Write Fail!");
		}
		m_ListData.SetCurSel(m_ListData.GetCount()-1);
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;
	case 5:
		switch(ConnectMode)
		{
		case 0:
			res=Net_ISO6B_WriteAByte(m_hSocket,IDTemp,ptr,len,DB);
			break;
		case 1:
			res=ISO6B_WriteAByte(m_hScanner,IDTemp,ptr,len,DB,0);
			break;
		case 2:
			res=ISO6B_WriteAByte(m_hScanner,IDTemp,ptr,len,DB,RS485Address);
			break;
		}
		if (res==_OK)
		{
			m_ListData.AddString("Write Successfully!");
		}
		else
		{
			m_ListData.AddString("Write Fail!");
		}
		m_ListData.SetCurSel(m_ListData.GetCount()-1);
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;
	}
	
	CPropertyPage::OnTimer(nIDEvent);
}

void CISO6BTest::OnCheck5() 
{
	apiReturn res;
	UpdateData(TRUE);

	int i = 0;
	int interval[]={10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_ListTag)
	{
		int k = 0;
		BYTE	bTmpAnt[4]	=	{0};
		m_antenna_sel=0;
		bTmpAnt[0] = 0;
		bTmpAnt[1] = 0;
		bTmpAnt[2] = 0;
		bTmpAnt[3] = 0;
		gAntenna[0] = 0;
		gAntenna[1] = 0;
		gAntenna[2] = 0;
		gAntenna[3] = 0;
		iModAnt	=	0;
		if(m_Antenna1)
		{
			bTmpAnt[0] = 1;
			iModAnt++;
			m_antenna_sel += 1;
		}
		
		if(m_Antenna2)
		{
			bTmpAnt[1] = 2;
			iModAnt++;
			m_antenna_sel += 2;
		}
		
		if(m_Antenna3)
		{
			bTmpAnt[2] = 4;
			iModAnt++;
			m_antenna_sel += 4;
		}
		
		if(m_Antenna4)
		{
			bTmpAnt[3] = 8;
			iModAnt++;
			m_antenna_sel += 8;
		}
		
		for (i = 0; i < 4; i++)
		{
			if ( bTmpAnt[i] != 0 )
			{
				gAntenna[k]	=	bTmpAnt[i];
				k++;
			}
		}

		switch(m_antenna_sel)
		{
		case 0:
			MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			m_ListTag=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			if (m_HardVersion!=0x140B)
			{
				switch(ConnectMode)
				{
				case 0://网口
					res = Net_SetAntenna(m_hSocket, m_antenna_sel);
					break;
				case 1://RS232
					res = SetAntenna(m_hScanner, m_antenna_sel,0);
					break;
				case 2://RS485
					res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
					break;
				}
				if (res!=_OK)
				{
					MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
					m_ListTag=FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			break;
		}

		m_ListID.DeleteAllItems();
		Read_times=0;
		UpdateStatus();
		SetTimer(0,timer_interval,NULL);
	}
	else
	{
		KillTimer(0);
		UpdateStatus();
	}
}

void CISO6BTest::OnCheck6() 
{
	apiReturn res;
	UpdateData(TRUE);

	int i = 0;
	int interval[]={10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_ListTagID)
	{
		int k = 0;
		BYTE	bTmpAnt[4]	=	{0};
		m_antenna_sel=0;
		bTmpAnt[0] = 0;
		bTmpAnt[1] = 0;
		bTmpAnt[2] = 0;
		bTmpAnt[3] = 0;
		gAntenna[0] = 0;
		gAntenna[1] = 0;
		gAntenna[2] = 0;
		gAntenna[3] = 0;
		iModAnt	=	0;
		if(m_Antenna1)
		{
			bTmpAnt[0] = 1;
			iModAnt++;
			m_antenna_sel += 1;
		}
		
		if(m_Antenna2)
		{
			bTmpAnt[1] = 2;
			iModAnt++;
			m_antenna_sel += 2;
		}
		
		if(m_Antenna3)
		{
			bTmpAnt[2] = 4;
			iModAnt++;
			m_antenna_sel += 4;
		}
		
		if(m_Antenna4)
		{
			bTmpAnt[3] = 8;
			iModAnt++;
			m_antenna_sel += 8;
		}
		
		for (i = 0; i < 4; i++)
		{
			if ( bTmpAnt[i] != 0 )
			{
				gAntenna[k]	=	bTmpAnt[i];
				k++;
			}
		}

		switch(m_antenna_sel)
		{
		case 0:
			MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			m_ListTagID=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			if (m_HardVersion!=0x140B)
			{
				switch(ConnectMode)
				{
				case 0://网口
					res = Net_SetAntenna(m_hSocket, m_antenna_sel);
					break;
				case 1://RS232
					res = SetAntenna(m_hScanner, m_antenna_sel,0);
					break;
				case 2://RS485
					res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
					break;
				}
				if (res!=_OK)
				{
					MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
					m_ListTagID=FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			break;
		}

		m_ListID.DeleteAllItems();
		Read_times=0;
		UpdateStatus();

//		if (ifTXMode)
//		{
//			int nCounter;
//			ISO6B_ReadLabelID_TXMode(m_hScanner,&(ISO6B_IDBuffer[0][0]),&nCounter,RS485Address);
//		}
//		else
			SetTimer(1,timer_interval,NULL);
	}
	else
	{
		//KillTimer(1);

//		if (ifTXMode)
//			ISO6B_StopListID(m_hScanner,RS485Address);
//		else
			KillTimer(1);

		m_TagID.ResetContent();

		int k=m_ListID.GetItemCount();
		CString str;
		char temp[64];

		for(int i=0;i<k;i++)
		{
			str="";
			m_ListID.GetItemText(i,1,temp,17);

			for(int j=0;j<8;j++)
			{
				ISO6B_IDBuffer[i][j]=(BYTE)strtol((CString)temp[j*2]+(CString)temp[j*2+1],NULL,16);
			}

			str.Format("%02d.",i+1);
			str+=temp;
			m_TagID.AddString(str);
		}

		m_TagID.SetCurSel(0);

		UpdateStatus();
	}
}

void CISO6BTest::OnCheck8() 
{
	apiReturn res;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first than choose a tag!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_RWAddress<0) || (m_RWAddress>223))
	{
		MessageBox("Please input Address of Tag Data between 0 and 223!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT1))->SetSel(0,-1);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_RWLen<1) || (m_RWLen>32))
	{
		MessageBox("Please input Length of Tag Data between 1 and 32!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT2))->SetSel(0,-1);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
	else
	{
		if (m_RWAddress+m_RWLen>224)
		{
			m_RWLen=224-m_RWAddress;
			UpdateData(FALSE);
		}
	}

	ptr=m_RWAddress;
	len=m_RWLen;

	int CurSel=m_TagID.GetCurSel();
	for(int i=0;i<8;i++)
	{
		IDTemp[i]=ISO6B_IDBuffer[CurSel][i];
	}

	int interval[]={10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_ReadDataBlock)
	{
		int k = 0;
		BYTE	bTmpAnt[4]	=	{0};
		m_antenna_sel=0;
		bTmpAnt[0] = 0;
		bTmpAnt[1] = 0;
		bTmpAnt[2] = 0;
		bTmpAnt[3] = 0;
		gAntenna[0] = 0;
		gAntenna[1] = 0;
		gAntenna[2] = 0;
		gAntenna[3] = 0;
		iModAnt	=	0;
		if(m_Antenna1)
		{
			bTmpAnt[0] = 1;
			iModAnt++;
			m_antenna_sel += 1;
		}
		
		if(m_Antenna2)
		{
			bTmpAnt[1] = 2;
			iModAnt++;
			m_antenna_sel += 2;
		}
		
		if(m_Antenna3)
		{
			bTmpAnt[2] = 4;
			iModAnt++;
			m_antenna_sel += 4;
		}
		
		if(m_Antenna4)
		{
			bTmpAnt[3] = 8;
			iModAnt++;
			m_antenna_sel += 8;
		}
		
		for (i = 0; i < 4; i++)
		{
			if ( bTmpAnt[i] != 0 )
			{
				gAntenna[k]	=	bTmpAnt[i];
				k++;
			}
		}

		switch(m_antenna_sel)
		{
		case 0:
			MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			m_ReadDataBlock=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			if (m_HardVersion!=0x140B)
			{
				switch(ConnectMode)
				{
				case 0://网口
					res = Net_SetAntenna(m_hSocket, m_antenna_sel);
					break;
				case 1://RS232
					res = SetAntenna(m_hScanner, m_antenna_sel,0);
					break;
				case 2://RS485
					res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
					break;
				}
				if (res!=_OK)
				{
					MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
					m_ReadDataBlock=FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			break;
		}

		m_ListData.ResetContent();
		Read_times=0;
		UpdateStatus();
		SetTimer(3,timer_interval,NULL);
	}
	else
	{
		KillTimer(3);
		UpdateStatus();
	}
}

void CISO6BTest::OnCheck9() 
{
	apiReturn res;
	CString str;
	int i;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_RWAddress<8) || (m_RWAddress>223))
	{
		MessageBox("Please input Address of Tag Data between 8 and 223!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT1))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_RWLen<1) || (m_RWLen>16))
	{
		MessageBox("Please input Address of Tag Data between 1 and 16!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT2))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
	else
	{
		if (m_RWAddress+m_RWLen>224)
		{
			m_RWLen=224-m_RWAddress;
			UpdateData(FALSE);
		}
	}

	ptr=m_RWAddress;
	len=m_RWLen;

	str=m_RWData.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_RWData))
	{
		MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
	str=m_RWData;
	int str_len=strlen(str);
	if ((str_len==0) || (str_len<len*2))
	{
		MessageBox("Please input enough Length of Tag Data!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
	for(i=0;i<len;i++)
	{
		DB[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	int CurSel=m_TagID.GetCurSel();
	for(i=0;i<8;i++)
	{
		IDTemp[i]=ISO6B_IDBuffer[CurSel][i];
	}

	int interval[]={10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_WriteDataBlock)
	{
		int k = 0;
		BYTE	bTmpAnt[4]	=	{0};
		m_antenna_sel=0;
		bTmpAnt[0] = 0;
		bTmpAnt[1] = 0;
		bTmpAnt[2] = 0;
		bTmpAnt[3] = 0;
		gAntenna[0] = 0;
		gAntenna[1] = 0;
		gAntenna[2] = 0;
		gAntenna[3] = 0;
		iModAnt	=	0;
		if(m_Antenna1)
		{
			bTmpAnt[0] = 1;
			iModAnt++;
			m_antenna_sel += 1;
		}
		
		if(m_Antenna2)
		{
			bTmpAnt[1] = 2;
			iModAnt++;
			m_antenna_sel += 2;
		}
		
		if(m_Antenna3)
		{
			bTmpAnt[2] = 4;
			iModAnt++;
			m_antenna_sel += 4;
		}
		
		if(m_Antenna4)
		{
			bTmpAnt[3] = 8;
			iModAnt++;
			m_antenna_sel += 8;
		}
		
		for (i = 0; i < 4; i++)
		{
			if ( bTmpAnt[i] != 0 )
			{
				gAntenna[k]	=	bTmpAnt[i];
				k++;
			}
		}
		
		switch(m_antenna_sel)
		{
		case 0:
			MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			m_WriteDataBlock=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			if (m_HardVersion!=0x140B)
			{
				switch(ConnectMode)
				{
				case 0://网口
					res = Net_SetAntenna(m_hSocket, m_antenna_sel);
					break;
				case 1://RS232
					res = SetAntenna(m_hScanner, m_antenna_sel,0);
					break;
				case 2://RS485
					res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
					break;
				}
				if (res!=_OK)
				{
					MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
					m_WriteDataBlock=FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			break;
		}

		m_ListData.ResetContent();
		Read_times=0;
		UpdateStatus();
		SetTimer(4,timer_interval,NULL);
	}
	else
	{
		KillTimer(4);
		UpdateStatus();
	}
}

void CISO6BTest::OnCheck10() 
{
	apiReturn res;
	CString str;
	int i;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_RWAddress<8) || (m_RWAddress>223))
	{
		MessageBox("Please input Address of Tag Data between 8 and 223!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT1))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_RWLen<1) || (m_RWLen>16))
	{
		MessageBox("Please input Address of Tag Data between 1 and 16!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT2))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
	else
	{
		if (m_RWAddress+m_RWLen>224)
		{
			m_RWLen=224-m_RWAddress;
			UpdateData(FALSE);
		}
	}

	ptr=m_RWAddress;
	len=m_RWLen;

	str=m_RWData.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_RWData))
	{
		MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
	str=m_RWData;
	int str_len=strlen(str);
	if ((str_len==0) || (str_len<len*2))
	{
		MessageBox("Please input enough Length of Tag Data!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
	for(i=0;i<len;i++)
	{
		DB[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	int CurSel=m_TagID.GetCurSel();
	for(i=0;i<8;i++)
	{
		IDTemp[i]=ISO6B_IDBuffer[CurSel][i];
	}

	int interval[]={10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_WriteAByteData)
	{
		int k = 0;
		BYTE	bTmpAnt[4]	=	{0};
		m_antenna_sel=0;
		bTmpAnt[0] = 0;
		bTmpAnt[1] = 0;
		bTmpAnt[2] = 0;
		bTmpAnt[3] = 0;
		gAntenna[0] = 0;
		gAntenna[1] = 0;
		gAntenna[2] = 0;
		gAntenna[3] = 0;
		iModAnt	=	0;
		if(m_Antenna1)
		{
			bTmpAnt[0] = 1;
			iModAnt++;
			m_antenna_sel += 1;
		}
		
		if(m_Antenna2)
		{
			bTmpAnt[1] = 2;
			iModAnt++;
			m_antenna_sel += 2;
		}
		
		if(m_Antenna3)
		{
			bTmpAnt[2] = 4;
			iModAnt++;
			m_antenna_sel += 4;
		}
		
		if(m_Antenna4)
		{
			bTmpAnt[3] = 8;
			iModAnt++;
			m_antenna_sel += 8;
		}
		
		for (i = 0; i < 4; i++)
		{
			if ( bTmpAnt[i] != 0 )
			{
				gAntenna[k]	=	bTmpAnt[i];
				k++;
			}
		}

		switch(m_antenna_sel)
		{
		case 0:
			MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			m_WriteDataBlock=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			if (m_HardVersion!=0x140B)
			{
				switch(ConnectMode)
				{
				case 0://网口
					res = Net_SetAntenna(m_hSocket, m_antenna_sel);
					break;
				case 1://RS232
					res = SetAntenna(m_hScanner, m_antenna_sel,0);
					break;
				case 2://RS485
					res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
					break;
				}
				if (res!=_OK)
				{
					MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
					m_WriteDataBlock=FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			break;
		}

		m_ListData.ResetContent();
		Read_times=0;
		UpdateStatus();
		SetTimer(5,timer_interval,NULL);
	}
	else
	{
		KillTimer(5);
		UpdateStatus();
	}
	
}

void CISO6BTest::OnCheck7() 
{
	apiReturn res;
	CString str;
	UpdateData(TRUE);

	cmd=m_SCmd;

	if ((m_SAddress<0) || (m_SAddress>223))
	{
		MessageBox("Please input Address of Tag Data between 0 and 223!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT5)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
		m_ListSelectTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	ptr=m_SAddress;

	str=m_SData.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_SData))
	{
		MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT6)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
		m_ListSelectTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	str=m_SData;
	int str_len=strlen(str);
	if ((str_len==0) || (str_len%2==1))
	{
		MessageBox("Please input enough Length of Tag Data!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT6)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
		m_ListSelectTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	for(int i=0;i<str_len/2;i++)
	{
		DB[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	switch (str_len/2)
	{
	case 1: 
		mask=0x80;
		break;
	case 2: 
		mask=0xC0;
		break;
	case 3: 
		mask=0xE0;
		break;
	case 4: 
		mask=0xF0;
		break;
	case 5: 
		mask=0xF8;
		break;
	case 6: 
		mask=0xFC;
		break;
	case 7: 
		mask=0xfe;
		break;
	case 8: 
		mask=0xFF;
		break;
	}

	int interval[]={10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_ListSelectTagID)
	{
		int k = 0;
		BYTE	bTmpAnt[4]	=	{0};
		m_antenna_sel=0;
		bTmpAnt[0] = 0;
		bTmpAnt[1] = 0;
		bTmpAnt[2] = 0;
		bTmpAnt[3] = 0;
		gAntenna[0] = 0;
		gAntenna[1] = 0;
		gAntenna[2] = 0;
		gAntenna[3] = 0;
		iModAnt	=	0;
		if(m_Antenna1)
		{
			bTmpAnt[0] = 1;
			iModAnt++;
			m_antenna_sel += 1;
		}
		
		if(m_Antenna2)
		{
			bTmpAnt[1] = 2;
			iModAnt++;
			m_antenna_sel += 2;
		}
		
		if(m_Antenna3)
		{
			bTmpAnt[2] = 4;
			iModAnt++;
			m_antenna_sel += 4;
		}
		
		if(m_Antenna4)
		{
			bTmpAnt[3] = 8;
			iModAnt++;
			m_antenna_sel += 8;
		}
		
		for (i = 0; i < 4; i++)
		{
			if ( bTmpAnt[i] != 0 )
			{
				gAntenna[k]	=	bTmpAnt[i];
				k++;
			}
		}

		switch(m_antenna_sel)
		{
		case 0:
			MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			m_ListSelectTagID=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			if (m_HardVersion!=0x140B)
			{
				switch(ConnectMode)
				{
				case 0://网口
					res = Net_SetAntenna(m_hSocket, m_antenna_sel);
					break;
				case 1://RS232
					res = SetAntenna(m_hScanner, m_antenna_sel,0);
					break;
				case 2://RS485
					res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
					break;
				}
				if (res!=_OK)
				{
					MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
					m_ListSelectTagID=FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			break;
		}

		m_ListID.DeleteAllItems();
		Read_times=0;
		UpdateStatus();
		SetTimer(2,timer_interval,NULL);
	}
	else
	{
		KillTimer(2);
		UpdateStatus();

		m_TagID.ResetContent();

		int k=m_ListID.GetItemCount();
		CString str;
		char temp[64];

		for(int i=0;i<k;i++)
		{
			str="";
			m_ListID.GetItemText(i,1,temp,17);

			for(int j=0;j<8;j++)
			{
				ISO6B_IDBuffer[i][j]=(BYTE)strtol((CString)temp[j*2]+(CString)temp[j*2+1],NULL,16);
			}

			str.Format("%02d.",i+1);
			str+=temp;
			m_TagID.AddString(str);
		}

		m_TagID.SetCurSel(0);
	}
}

void CISO6BTest::OnButton1() 
{
	apiReturn res;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first than choose a tag!","Warning",MB_ICONWARNING);
		m_ListSelectTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	
	if ((m_PAddress<8) || (m_PAddress>223))
	{
		MessageBox("Please input Address of Tag Data between 8 and 223!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT4)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
		m_ListSelectTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	ptr=m_PAddress;

	int CurSel=m_TagID.GetCurSel();
	for(int i=0;i<8;i++)
	{
		IDTemp[i]=ISO6B_IDBuffer[CurSel][i];
	}

	CString str;
	str.Format("Do you determine to protect address %d of the tag?",ptr);
	int k=MessageBox(str,"Notice",MB_OKCANCEL|MB_ICONWARNING);
	if (k!=1) 
		return;

	m_antenna_sel=0;
	if(m_Antenna1)
	m_antenna_sel += 1;
	if(m_Antenna2)
	m_antenna_sel += 2;
	if(m_Antenna3)
	m_antenna_sel += 4;
	if(m_Antenna4)
	m_antenna_sel += 8;
	switch(m_antenna_sel)
	{
	case 1:
	case 2:
	case 4:
	case 8:
		if (m_HardVersion!=0x140B)
		{
			switch(ConnectMode)
			{
			case 0://网口
				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
				break;
			case 1://RS232
				res = SetAntenna(m_hScanner, m_antenna_sel,0);
				break;
			case 2://RS485
				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
				break;
			}
			if (res!=_OK)
			{
				MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				return;
			}
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	switch(ConnectMode)
	{
	case 0:
		res=Net_ISO6B_WriteProtect(m_hSocket,IDTemp,ptr);
		break;
	case 1:
		res=ISO6B_WriteProtect(m_hScanner,IDTemp,ptr,0);
		break;
	case 2:
		res=ISO6B_WriteProtect(m_hScanner,IDTemp,ptr,RS485Address);
		break;
	}
	if (res==_OK)
	{
		MessageBox("WriteProtect Successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("WriteProtect Fail!Please Try Again!","Notice",MB_ICONERROR);
	}
}

void CISO6BTest::OnButton2() 
{
	apiReturn res;
	BYTE protect;
	int i;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first than choose a tag!","Warning",MB_ICONWARNING);
		m_ListSelectTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	
	if ((m_PAddress<0) || (m_PAddress>223))
	{
		MessageBox("Please input Address of Tag Data between 0 and 223!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT4)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
		m_ListSelectTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	ptr=m_PAddress;

	int CurSel=m_TagID.GetCurSel();
	for(i=0;i<8;i++)
	{
		IDTemp[i]=ISO6B_IDBuffer[CurSel][i];
	}

	m_antenna_sel=0;
	if(m_Antenna1)
	m_antenna_sel += 1;
	if(m_Antenna2)
	m_antenna_sel += 2;
	if(m_Antenna3)
	m_antenna_sel += 4;
	if(m_Antenna4)
	m_antenna_sel += 8;
	switch(m_antenna_sel)
	{
	case 1:
	case 2:
	case 4:
	case 8:
		if (m_HardVersion!=0x140B)
		{
			switch(ConnectMode)
			{
			case 0://网口
				res = Net_SetAntenna(m_hSocket, m_antenna_sel);
				break;
			case 1://RS232
				res = SetAntenna(m_hScanner, m_antenna_sel,0);
				break;
			case 2://RS485
				res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
				break;
			}
			if (res!=_OK)
			{
				MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				return;
			}
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	for(i=0;i<5;i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_ISO6B_ReadWriteProtect(m_hSocket,IDTemp,ptr,&protect);
			break;
		case 1:
			res=ISO6B_ReadWriteProtect(m_hScanner,IDTemp,ptr,&protect,0);
			break;
		case 2:
			res=ISO6B_ReadWriteProtect(m_hScanner,IDTemp,ptr,&protect,RS485Address);
			break;
		}
		if (res==_OK)
			break;
	}
	if (res==_OK)
	{
		CString str;
		switch (protect)
		{
		case 0:
			str.Format("The address %d has not been written protection!",ptr);
			break;
		case 1:
			str.Format("The address %d has been written protection!",ptr);
			break;
		}
		MessageBox(str,"Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Check Protect Fail!Please Try Again!","Notice",MB_ICONERROR);
	}
}

void CISO6BTest::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	UpdateStatus();
	
}


//自定义消息 WM_USERTIMERDATATRan
afx_msg LRESULT CISO6BTest::OnUsertimerdatatran(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 0 == iwParam )
	{
		//右键
		//导出写TXT文件
			int nRow	=	m_ListID.GetItemCount();	//取得有多少行
			if ( nRow <= 0 )
			{
				if ( 0 == ilParam )
				{
					//MessageBox("List is empty!","VI-720", MB_ICONERROR|MB_OK );
					MessageBox(theApp.g_LoadString("IDWQB_E0039"),theApp.g_LoadString("IDWQB_E0036"), MB_ICONERROR|MB_OK );
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

				*(chRecv + chCnt++)	= '\x09';	//"\x27";
				strT	=	m_ListID.GetItemText(i,1);//ID
				memcpy(chRecv+chCnt, strT, strT.GetLength());
				chCnt	+=	strT.GetLength();

				//*(chRecv + chCnt++)	=	',';

				//strT	=	m_ListID.GetItemText(i,2);//Success
				//memcpy(chRecv+chCnt, strT, strT.GetLength());
				//chCnt	+=	strT.GetLength();

				//*(chRecv + chCnt++)	=	',';

				//strT	=	m_ListID.GetItemText(i,3);//Times
				//memcpy(chRecv+chCnt, strT, strT.GetLength());
				//chCnt	+=	strT.GetLength();

				//*(chRecv + chCnt++)	=	',';

				//strT	=	m_ListID.GetItemText(i,4);//Length
				//memcpy(chRecv+chCnt, strT, strT.GetLength());
				//chCnt	+=	strT.GetLength();
				
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
				MessageBox(theApp.g_LoadString("IDWQB_E0038"),theApp.g_LoadString("IDWQB_E0038"), MB_ICONINFORMATION|MB_OK );
				ShellExecute(NULL,"open",filename,NULL,NULL,SW_SHOWNORMAL);
			

			}


		
	}
	else if ( 1 == iwParam )
	{
		
	}
	else if ( 2 == iwParam )
	{
		OnInitUIText();	//更新语言
	}

	return 0;
}


BOOL CISO6BTest::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//如果在列表中点右键
	if(WM_RBUTTONDOWN == pMsg->message )
	{
		if ( pMsg->hwnd == GetDlgItem(IDC_LIST1)->m_hWnd )
		{
			PopupMenu();
			return TRUE;
		}
	}

	return CPropertyPage::PreTranslateMessage(pMsg);
}
