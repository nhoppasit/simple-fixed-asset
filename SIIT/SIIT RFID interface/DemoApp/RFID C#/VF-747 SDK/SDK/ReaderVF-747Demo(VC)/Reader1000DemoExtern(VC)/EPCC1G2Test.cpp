// EPCC1G2Test.cpp : implementation file
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "EPCC1G2Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
HWND	gEcpISO6C	=	NULL;//6c窗体的句柄
BYTE EPCC1G2_IDBuffer[MAX_LABELS][ID_MAX_SIZE_96BIT]={0};
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//定义定时器的ID
//时间
#define					TIME_IDENTIFIER_OUTPUTTEST	(3000)		//时间ID号,检测有无标签
#define					INTERVALTIME_OUTPUT			(100)		//多长时间执行一次(1s跑一次)


//////////////////////////////////////////////////////////////////////////
static void PopupMenu()
{
	CPoint point;
	GetCursorPos( & point );
	CMenu menuPopup;
	menuPopup.CreatePopupMenu();
	
	//menuPopup.AppendMenu( MF_STRING, 100, _T("Export"));
	menuPopup.AppendMenu( MF_STRING, 100, theApp.g_LoadString("IDWQB_D0157"));
	
	//menuPopup.AppendMenu( MF_SEPARATOR );
	//menuPopup.AppendMenu( MF_STRING, 101, _T("Exit"));
	
	int nCmd = (int) menuPopup.TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, AfxGetMainWnd() );
	switch( nCmd )
	{
	case	100:
		//AfxMessageBox(_T("退出"));
		//CMainFrame::OnEditComm ();
		//::SendMessage(FrameHwnd, WM_CLOSE, 0, 0);
		::PostMessage(gEcpISO6C,WM_EPC6CTRANDATAMSG,0,0);	//导出TXT
		break;
		//case	101:
		//	::PostMessage(gEcpISO6C,WM_CLOSE,0,0);
		//	break;
		
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////////


// CEPCC1G2Test property page

IMPLEMENT_DYNCREATE(CEPCC1G2Test, CPropertyPage)

CEPCC1G2Test::CEPCC1G2Test() : CPropertyPage(CEPCC1G2Test::IDD)
{
	//{{AFX_DATA_INIT(CEPCC1G2Test)
	m_Antenna1 = TRUE;
	m_Antenna2 = FALSE;
	m_Antenna3 = FALSE;
	m_Antenna4 = FALSE;
	m_mem = 1;
	m_LAddress = 0;
	m_LLen = 0;
	m_LData = _T("");
	m_ListTagID = FALSE;
	m_RWAddress = 0;
	m_RWLen = 1;
	m_ReadDataBlock = FALSE;
	m_Password = 0;
	m_LAccessPassword = _T("");
	m_RWAccessPassword = _T("");
	m_Condition = 0;
	m_Condition2 = 0;
	m_RWmem = 1;
	m_Lmem = 1;
	m_Data = _T("");
	m_KillPassword = _T("");
	m_LBAddress = 0;
	m_LBAccessPassword = _T("");
	m_EasState = 0;
	m_AAccessPassword = _T("");
	m_EasAlarm = FALSE;
	m_RProtectPassword = _T("");
	m_KPassword = _T("");
	m_Kword = FALSE;
	m_DetectTag = FALSE;
	//}}AFX_DATA_INIT
}

CEPCC1G2Test::~CEPCC1G2Test()
{
}

void CEPCC1G2Test::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEPCC1G2Test)
	DDX_Control(pDX, IDC_COMBO7, m_PTagID);
	DDX_Control(pDX, IDC_EASALARM_STATIC, m_APic);
	DDX_Control(pDX, IDC_COMBO6, m_ATagID);
	DDX_Control(pDX, IDC_COMBO5, m_LBTagID);
	DDX_Control(pDX, IDC_COMBO4, m_KTagID);
	DDX_Control(pDX, IDC_COMBO3, m_LTagID);
	DDX_Control(pDX, IDC_LIST2, m_ListData);
	DDX_Control(pDX, IDC_COMBO1, m_TagID);
	DDX_Control(pDX, IDC_COMBO2, m_Interval);
	DDX_Control(pDX, IDC_LIST1, m_ListID);
	DDX_Check(pDX, IDC_CHECK1_6C, m_Antenna1);
	DDX_Check(pDX, IDC_CHECK2_6C, m_Antenna2);
	DDX_Check(pDX, IDC_CHECK3_6C, m_Antenna3);
	DDX_Check(pDX, IDC_CHECK4_6C, m_Antenna4);
	DDX_Radio(pDX, IDC_RADIO1_PassWord_6C, m_mem);
	DDX_Text(pDX, IDC_EDIT1, m_LAddress);
	DDX_Text(pDX, IDC_EDIT2, m_LLen);
	DDX_Text(pDX, IDC_EDIT3, m_LData);
	DDX_Check(pDX, IDC_CHECK5_ListEpcofTag_6C, m_ListTagID);
	DDX_Text(pDX, IDC_EDIT4, m_RWAddress);
	DDX_Text(pDX, IDC_EDIT5, m_RWLen);
	DDX_Check(pDX, IDC_CHECK6_ReadD_6C, m_ReadDataBlock);
	DDX_Radio(pDX, IDC_RADIO9_KillPsdAB_6C, m_Password);
	DDX_Text(pDX, IDC_EDIT10, m_LAccessPassword);
	DDV_MaxChars(pDX, m_LAccessPassword, 8);
	DDX_Text(pDX, IDC_EDIT11, m_RWAccessPassword);
	DDV_MaxChars(pDX, m_RWAccessPassword, 8);
	DDX_Radio(pDX, IDC_RADIO6_AnyReadWrite_6C, m_Condition);
	DDX_Radio(pDX, IDC_RADIO11_WriteFormandState_6C, m_Condition2);
	DDX_Radio(pDX, IDC_RADIO15_PasswordB_6C, m_RWmem);
	DDX_Radio(pDX, IDC_RADIO19, m_Lmem);
	DDX_Text(pDX, IDC_EDIT6, m_Data);
	DDX_Text(pDX, IDC_EDIT9, m_KillPassword);
	DDV_MaxChars(pDX, m_KillPassword, 8);
	DDX_Text(pDX, IDC_EDIT7, m_LBAddress);
	DDX_Text(pDX, IDC_EDIT8, m_LBAccessPassword);
	DDV_MaxChars(pDX, m_LBAccessPassword, 8);
	DDX_Radio(pDX, IDC_RADIO23_NoAlarm_6C, m_EasState);
	DDX_Text(pDX, IDC_EDIT12, m_AAccessPassword);
	DDV_MaxChars(pDX, m_AAccessPassword, 8);
	DDX_Check(pDX, IDC_CHECK7_EasAlarm_6C, m_EasAlarm);
	DDX_Text(pDX, IDC_EDIT13, m_RProtectPassword);
	DDV_MaxChars(pDX, m_RProtectPassword, 8);
	DDX_Text(pDX, IDC_EDIT14, m_KPassword);
	DDV_MaxChars(pDX, m_KPassword, 8);
	DDX_Check(pDX, IDC_CHECK9_CalibrateB_6C, m_Kword);
	DDX_Check(pDX, IDC_CHECK10_DetectTag_6C, m_DetectTag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEPCC1G2Test, CPropertyPage)
	//{{AFX_MSG_MAP(CEPCC1G2Test)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK5_ListEpcofTag_6C, OnCHECK5ListEpcofTag6C)
	ON_BN_CLICKED(IDC_CHECK6_ReadD_6C, OnCHECK6ReadD6C)
	ON_BN_CLICKED(IDC_BUTTON4_WrtieD_6C, OnBUTTON4WrtieD6C)
	ON_BN_CLICKED(IDC_BUTTON1_SetProtectAG_6C, OnButton1)
	ON_BN_CLICKED(IDC_RADIO19, OnRadio19)
	ON_BN_CLICKED(IDC_RADIO20, OnRadio20)
	ON_BN_CLICKED(IDC_RADIO21, OnRadio21)
	ON_BN_CLICKED(IDC_RADIO22, OnRadio22)
	ON_BN_CLICKED(IDC_BUTTON2_KillTag_6C, OnBUTTON2KillTag6C)
	ON_BN_CLICKED(IDC_BUTTON3_SetProtectBB_6C, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON5_SetAlarm_6C, OnButton5)
	ON_BN_CLICKED(IDC_CHECK7_EasAlarm_6C, OnCheck7)
	ON_BN_CLICKED(IDC_BUTTON6_LockRead_6C, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7_UnlockRaed_6C, OnButton7)
	ON_BN_CLICKED(IDC_CHECK9_CalibrateB_6C, OnCheck9)
	ON_BN_CLICKED(IDC_CHECK10_DetectTag_6C, OnCHECK10DetectTag6C)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_EPC6CTRANDATAMSG, OnEpc6ctrandatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEPCC1G2Test message handlers
void CEPCC1G2Test::OnInitUIText()//界面和文本更新
{
	SetWindowText(theApp.g_LoadString("IDWQA_D0001"));//6C Test

	GetDlgItem(IDC_STATIC_SelectAntTEst_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0002"));//Select Antenna for Test
	GetDlgItem(IDC_CHECK1_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0003"));//ANT1
	GetDlgItem(IDC_CHECK2_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0004"));//ANT2
	GetDlgItem(IDC_CHECK3_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0005"));//ANT3
	GetDlgItem(IDC_CHECK4_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0006"));//ANT4
	GetDlgItem(IDC_STATIC_SelMemBank_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0007"));//Select Memory Bank
	GetDlgItem(IDC_RADIO1_PassWord_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0008"));//Password
	GetDlgItem(IDC_RADIO2_EPC_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0009"));//EPC
	GetDlgItem(IDC_RADIO3_TID_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0010"));//TID

	GetDlgItem(IDC_STATIC_listSelectTag_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0011"));//List Selected Tag
	GetDlgItem(IDC_STATIC_AddressOfTag_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0012"));//Address of Tag Data(bit):
	GetDlgItem(IDC_STATIC_LengofDatab_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0013"));//Length of Tag Data(bit):
	GetDlgItem(IDC_STATIC_TagDataHex_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0014"));//Tag Data(HEX):
	GetDlgItem(IDC_BUTTON1_SetProtectAG_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0015"));//Set Protect
	GetDlgItem(IDC_STATIC_RWDataBlock_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0016"));//Read and Write Data Block
	GetDlgItem(IDC_STATIC_AddofDataC_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0017"));//Address of Tag Data(WORD):
	GetDlgItem(IDC_STATIC_LengofDataD_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0018"));//Length of Tag Data(WORD):
	GetDlgItem(IDC_STATIC_WriteDataHex_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0019"));//Written Data(HEX):
	GetDlgItem(IDC_STATIC_AlarmCC_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0020"));//Alarm

	GetDlgItem(IDC_STATIC_KillPass8Hex_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0021"));//Kill Password (8HEX):
	GetDlgItem(IDC_STATIC_LockBForUser_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0022"));//Lock Block for User
	GetDlgItem(IDC_STATIC_AddOFTAGBB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0023"));//Address of Tag Data(WORD):
	GetDlgItem(IDC_STATIC_ACCESSPSDAA_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0024"));//Access Password (8HEX):
	GetDlgItem(IDC_STATIC_SetProtectB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0025"));//Set protect for reading or writing
	GetDlgItem(IDC_BUTTON2_KillTag_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0026"));//Kill  Tag
	GetDlgItem(IDC_BUTTON3_SetProtectBB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0027"));//Set Protect
	GetDlgItem(IDC_CHECK5_ListEpcofTag_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0028"));//List EPC of Tag
	GetDlgItem(IDC_CHECK6_ReadD_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0029"));//Read
	GetDlgItem(IDC_STATIC_RInterval_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0030"));//Read Interval
	GetDlgItem(IDC_BUTTON4_WrtieD_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0031"));//Write
	GetDlgItem(IDC_STATIC_SelectAtagB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0032"));//Select a Tag
	GetDlgItem(IDC_RADIO6_PermRead_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0033"));//Permanently readable and writeable
	GetDlgItem(IDC_RADIO7_ReadandWdriteState_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0034"));//Readable and writeable from the secured state
	GetDlgItem(IDC_RADIO8_NeverReadAndWrite_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0035"));//Never readable and writeable
	GetDlgItem(IDC_STATIC_PasswordCC_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0036"));//Password
	GetDlgItem(IDC_RADIO9_KillPsdAB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0037"));//Kill Password
	GetDlgItem(IDC_RADIO10_AccessPsdAC_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0038"));//Access Password
	GetDlgItem(IDC_STATIC_AccessPassAF_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0039"));//Access Password(8HEX):
	GetDlgItem(IDC_STATIC_AccessPsdB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0040"));//Access Password(8HEX):
	GetDlgItem(IDC_STATIC_LockofPsdAA_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0041"));//Lock of Password

	GetDlgItem(IDC_STATIC_LockofEPCTIDandUser_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0042"));//Lock of EPC TID and User Bank
	GetDlgItem(IDC_RADIO11_WriteFormandState_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0043"));//Writeable from any state
	GetDlgItem(IDC_RADIO12_PerWriteable_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0044"));//Permanently writeable
	GetDlgItem(IDC_RADIO13_WriteformSecState_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0045"));//Writeable from the secured state
	GetDlgItem(IDC_RADIO14_Neverwriteable_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0046"));//Never writeable
	GetDlgItem(IDC_STATIC_SelectMemBankB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0047"));//Select Memory Bank
	GetDlgItem(IDC_RADIO15_PasswordB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0048"));//Password
	GetDlgItem(IDC_RADIO16_EPC_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0049"));//EPC
	GetDlgItem(IDC_RADIO17_TID_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0050"));//TID
	GetDlgItem(IDC_RADIO18_User_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0051"));//User
	GetDlgItem(IDC_STATIC_SelMemBankD_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0052"));//Select Memory Bank
	GetDlgItem(IDC_RADIO19)->SetWindowText(theApp.g_LoadString("IDWQB_D0053"));//Password
	GetDlgItem(IDC_RADIO20)->SetWindowText(theApp.g_LoadString("IDWQB_D0054"));//EPC
	GetDlgItem(IDC_RADIO21)->SetWindowText(theApp.g_LoadString("IDWQB_D0055"));//TID
	GetDlgItem(IDC_RADIO22)->SetWindowText(theApp.g_LoadString("IDWQB_D0056"));//User
	GetDlgItem(IDC_STATIC_SelATagE_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0057"));//Select a Tag
	GetDlgItem(IDC_STATIC_SelectaTagAE_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0058"));//Select a Tag
	GetDlgItem(IDC_STATIC_SelATagAA_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0059"));//Select a Tag
	GetDlgItem(IDC_STATIC_KillTag_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0060"));//Kill Tag
	GetDlgItem(IDC_STATIC_SelectaTag_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0061"));//Select a Tag
	GetDlgItem(IDC_STATIC_EASSTATE_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0062"));//Eas State
	GetDlgItem(IDC_STATIC_AccessPSDDA_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0063"));//Access Password(8HEX):
	GetDlgItem(IDC_RADIO23_NoAlarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0064"));//No Alarm
	GetDlgItem(IDC_RADIO24_Alarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0065"));//Alarm
	GetDlgItem(IDC_BUTTON5_SetAlarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0066"));//Set Alarm
	GetDlgItem(IDC_CHECK7_EasAlarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0067"));//EasAlarm
	GetDlgItem(IDC_BUTTON6_LockRead_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0068"));//Lock Read
	GetDlgItem(IDC_BUTTON7_UnlockRaed_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0069"));//Unlock Read
	GetDlgItem(IDC_STATIC_ReadProtect_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0070"));//Read Protect
	GetDlgItem(IDC_STATIC_SetATagAH_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0071"));//Select a Tag
	GetDlgItem(IDC_STATIC_AccessPsdBA_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0072"));//Access Password(8HEX):
	GetDlgItem(IDC_STATIC_Calibrate_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0073"));//Calibrate
	GetDlgItem(IDC_STATIC_AccessPsd8Hex_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0074"));//Access PassWord(8HEX):
	GetDlgItem(IDC_CHECK9_CalibrateB_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0075"));//Calibrate
	GetDlgItem(IDC_CHECK10_DetectTag_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0076"));//Detect Tag
	GetDlgItem(IDC_STATIC_LstEpcofTags_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0082"));//List ID of Tags
	GetDlgItem(IDC_RADIO6_AnyReadWrite_6C)->SetWindowText(theApp.g_LoadString("IDWQB_D0119"));//任意读写


	CListCtrl *mIPlist = (CListCtrl*)GetDlgItem(IDC_LIST1);
	LVCOLUMN listColumnTemp;
	CString	strText;
	
	strText	=	theApp.g_LoadString("IDWQB_D0077");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(0, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_D0078");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(1, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_D0079");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(2, &listColumnTemp);
	strText.ReleaseBuffer();

	strText	=	theApp.g_LoadString("IDWQB_D0080");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(3, &listColumnTemp);
	strText.ReleaseBuffer();

	strText	=	theApp.g_LoadString("IDWQB_D0081");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(4, &listColumnTemp);
	strText.ReleaseBuffer();
	


}

BOOL CEPCC1G2Test::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	gEcpISO6C	=	this->GetSafeHwnd();

	DWORD dwStyle = m_ListID.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_ListID.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);

	m_ListID.InsertColumn(0, "No.", LVCFMT_LEFT, 50);
	m_ListID.InsertColumn(1, "ID", LVCFMT_LEFT, 300);
	m_ListID.InsertColumn(2, "Success", LVCFMT_LEFT, 75);
	m_ListID.InsertColumn(3, "Times", LVCFMT_LEFT, 75);
	m_ListID.InsertColumn(4, "EPC Length", LVCFMT_LEFT, 75);

	m_Interval.SetCurSel(3);
	
	m_RWAccessPassword="00000000";
	m_LAccessPassword="00000000";
	m_LBAccessPassword="00000000";
	m_AAccessPassword="00000000";
	m_KillPassword="00000000";
	m_RProtectPassword="00000000";
	m_KPassword="00000000";

	UpdateData(FALSE);

	OpenPassword=FALSE;
	UpdateStatus();


	//因为没有此功能，这是原来的，所以去掉 modi by mqs 20121130
	GetDlgItem(IDC_STATIC_Calibrate_6C)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_AccessPsd8Hex_6C)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT14)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK9_CalibrateB_6C)->ShowWindow(SW_HIDE);	

	GetDlgItem(IDC_CHECK10_DetectTag_6C)->ShowWindow(SW_HIDE);

	//6C测试页
	::SendMessage(gEcpISO6C,WM_EPC6CTRANDATAMSG,2,0);	//convert language

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CEPCC1G2Test::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( theApp.iantennaIndex == 0 )
	{
		//一根天线,其它三根不要
		GetDlgItem(IDC_CHECK2_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK3_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK4_6C)->ShowWindow(SW_HIDE);

	}
	else
	{
		//四根天线,其它三根要
		GetDlgItem(IDC_CHECK2_6C)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK3_6C)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK4_6C)->ShowWindow(SW_SHOW);
		
	}

	UpdateData(TRUE);
	UpdateStatus();
	

	if ( 1 == iPlatform )	//0---626, 1---218
	{
		//用户锁定相关
		GetDlgItem(IDC_STATIC_LockBForUser_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SelATagAA_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_AddOFTAGBB_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ACCESSPSDAA_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON3_SetProtectBB_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO5)->ShowWindow(SW_HIDE);
		
		//EAS报警
		GetDlgItem(IDC_STATIC_AlarmCC_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SelectaTagAE_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_EASSTATE_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO23_NoAlarm_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO24_Alarm_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_AccessPSDDA_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON5_SetAlarm_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EASALARM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK7_EasAlarm_6C)->ShowWindow(SW_HIDE);

		//读保护
		GetDlgItem(IDC_STATIC_ReadProtect_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SetATagAH_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_AccessPsdBA_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT13)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON6_LockRead_6C)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON7_UnlockRaed_6C)->ShowWindow(SW_HIDE);
			
		
		//218为了提高读标签速度，不用切换天线，加一个命令，下面自动切换天线，编译   否则无，用宏控制,add by mqs 20130910
		#if defined (ENABLE218TXNOAntenna)

		#endif

	}

	


	UpdateData(FALSE);
	::PostMessage(gEcpISO6C,WM_EPC6CTRANDATAMSG,2,0);	//convert language
	return CPropertyPage::OnSetActive();
}

void CEPCC1G2Test::OnTimer(UINT nIDEvent) 
{
	apiReturn res;
	BYTE be_antenna	=	0;
	int i,j,k,nCounter=0,ID_len=0,ID_len_temp=0;
	CString str,str_temp;
	char temp[64*2];
	BYTE DB[128];
	BYTE IDBuffer[30*256];

	BOOL bFlag = FALSE;
	//////////////////////////////////////////////////////////////////////////
	//add by mqs 20130710 新方法
	int itmpAnt	=	0;
	
	itmpAnt	=	Read_times % iModAnt;
		
	itmpAnt = gAntenna[itmpAnt];

	Read_times++;

	if ( 1 == iPlatform )//0---626, 1---218
	{
		//218为了提高读标签速度，不用切换天线，加一个命令，下面自动切换天线，编译   否则无，用宏控制,add by mqs 20130910
		#if defined (ENABLE218TXNOAntenna)
		bFlag = FALSE;
		#else	
		bFlag = TRUE;
		#endif
	}
	else
	{
		bFlag = TRUE;
	}
	
	
	if ( bFlag )
	{	
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
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
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 1:
// 			be_antenna=1;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 2:
// 			be_antenna=2;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		case 3:
// 			be_antenna=4;
// 			switch(ConnectMode)
// 			{
// 			case 0://网口
// 				Net_SetAntenna(m_hSocket, be_antenna);
// 				break;
// 			case 1://RS232
// 				SetAntenna(m_hScanner, be_antenna,0);
// 				break;
// 			case 2://RS485
// 				SetAntenna(m_hScanner, be_antenna,RS485Address);
// 				break;
// 			}
// 			break;
// 		}
// 		break;
// 	}

	switch(nIDEvent)
	{
	case 1:
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_ReadLabelID(m_hSocket,mem,ptr,len,mask,IDBuffer,&nCounter);
			break;
		case 1://RS232
			res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,0);
			break;
		case 2://RS485
			res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,RS485Address);
			break;
		}
		k=m_ListID.GetItemCount();
		if (res==_OK)
		{
			if ( nCounter > 8 )
			{
				i = nCounter;
			}
			for(i=0;i<nCounter;i++)
			{
				if (IDBuffer[ID_len]>32)
				{
					nCounter=0;
					break;
				}
				ID_len_temp=IDBuffer[ID_len]*2+1;//1word=16bit
				memcpy(EPCC1G2_IDBuffer[i], &IDBuffer[ID_len], ID_len_temp);
				ID_len+=ID_len_temp;
			}
			if (nCounter>0)
			{
				MessageBeep(-1);
			}

			for(i=0;i<nCounter;i++)
			{
				char ch = 0;
				str="";
				ID_len=EPCC1G2_IDBuffer[i][0]*2;
				for(j=0;j<ID_len;j++)
				{
					ch = (char)*(BYTE *)&EPCC1G2_IDBuffer[i][j+1];
					//下面这是测试可以显示中文(前提是写中文进去)
					#if defined (EPCREADWRITEHEX)

					#else
					if ( ch >= 0x20 )
					{
						str += ch;
					}
					else if ( (BYTE)ch >= (BYTE)0xA0 )
					{
						str += ch;
						j++;
						ch = (char)*(BYTE *)&EPCC1G2_IDBuffer[i][j+1];
						str += ch;
					}
					else
					#endif
					{
						wsprintf(temp, "%02X", *(BYTE *)&EPCC1G2_IDBuffer[i][j+1]);
						str += temp;

						
					}
				}

				//;是否输出如这种格式的EPC,如:1234 5678 1122 3344,四位一组.1---是,0---不是(保持原来的)
				int iG = GetPrivateProfileInt("Setting","FormatG", 0, theApp.strConfigPath);
				if (iG)
				{	
					//输出EPC如：1234 5678 1122 3344
					//EPC
					str.Replace("\r\n", "");
					str.Replace(" ", "");
					int mm = str.GetLength();
					int mi = 0;
					CString strR = "";
					while (mi < mm)
					{
						if ( 0 != mi && mi % 4 == 0 )
						{
							strR += " ";
						}
						strR += str.Mid(mi,1);
						mi++;
					}
 					str = strR;
					
				}

				for(j=0;j<k;j++)
				{
					m_ListID.GetItemText(j,4,temp,3);
//					ID_len_temp=strtol(temp,NULL,10)*2;
					ID_len_temp=((BYTE)strtol(temp,NULL,16))*2;
					if (ID_len == ID_len_temp)
					{
						//m_ListID.GetItemText(j,1,temp,ID_len*2+1);
						m_ListID.GetItemText(j, 1, temp, 128);
						str_temp=temp;
						if(str == str_temp)
						{
							j = j;
							break;
						}
					}
				}
				if(j == k)
				{
					m_ListID.InsertItem(k,itoa(k+1,temp,10));
					m_ListID.SetItemText(k,1,str);
					m_ListID.SetItemText(k,2,"1");
					str_temp.Format("%02X",EPCC1G2_IDBuffer[i][0]);
					m_ListID.SetItemText(k,4,str_temp);
					m_ListID.EnsureVisible(k,TRUE);
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
		case 0://网口
			res=Net_EPC1G2_ReadWordBlock(m_hSocket,EPC_Word,IDTemp,mem,ptr,len,&DB[0],AccessPassword);
			break;
		case 1://RS232
			res=EPC1G2_ReadWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,&DB[0],AccessPassword,0);
			break;
		case 2://RS485
			res=EPC1G2_ReadWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,&DB[0],AccessPassword,RS485Address);
			break;
		}
		if (res==_OK)
		{
			str="";
			for(i=0;i<len*2;i++)
			{
				str_temp.Format("%02X",DB[i]);
				str+=str_temp;
			}
			m_ListData.AddString(str);
			//m_ListData.SetCurSel(m_ListData.GetCount()-1);
		}
		else
		{
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="Read Fail!";
			m_ListData.AddString(str);
		}

		m_ListData.SetCurSel(m_ListData.GetCount()-1);
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;

	case 3:
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_EasAlarm(m_hSocket);		
			break;
		case 1://RS232
			res=EPC1G2_EasAlarm(m_hScanner,0);
			break;
		case 2://RS485
			res=EPC1G2_EasAlarm(m_hScanner,RS485Address);		
			break;
		}
		if(res==_OK)
		{
			MessageBeep(-1);
			m_APic.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
		}

		Sleep(100);
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		m_APic.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
		break;
	case 4:
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_DetectTag(m_hSocket);
			break;
		case 1://RS232
			res=EPC1G2_DetectTag(m_hScanner,0);
			break;
		case 2://RS485
			res=EPC1G2_DetectTag(m_hScanner,RS485Address);
			break;
		}
		k=m_ListID.GetItemCount();
		switch(res)
		{
		case _OK:
			str="There are Tags in the field!";
			Detect++;
			break;
//		case 0x02:
//			str="There is none of Tag in the field!";
//			break;
		case 0x0E:
			str="There are Locked Tags in the field!";
			break;
		}
/*		for(j=0;j<k;j++)
		{
			str_temp=m_ListID.GetItemText(j,1);
		    if(str == str_temp) break;
		}
		if(j== k)
		{
			m_ListID.InsertItem(k,itoa(k+1,temp,10));
			m_ListID.SetItemText(k,1,str);
			m_ListID.SetItemText(k,2,"1");
			m_ListID.EnsureVisible(k,TRUE);
			k++;
		}
		else
		{
			str_temp=m_ListID.GetItemText(j,2);
			m_ListID.SetItemText(j,2,itoa(atoi(str_temp)+1,temp,10));
		}
		if(res==_OK||res==0x0E)
		{
			KillTimer(4);
			m_DetectTag=FALSE;
			UpdateData(FALSE);
		}
*/
//		str_temp=m_ListID.GetItemText(j,1);
		if(3000>=Read_times*timer_interval)
		{
			if(res==0x0E)
			{
				m_ListID.InsertItem(k,itoa(k+1,temp,10));
				m_ListID.SetItemText(k,1,str);
				m_ListID.EnsureVisible(k,TRUE);
				k++;
				KillTimer(4);
				m_DetectTag=FALSE;
				UpdateData(FALSE);
			}
		}
		else
		{
			m_ListID.InsertItem(k,itoa(k+1,temp,10));
			if(Detect==0)
			{
				m_ListID.SetItemText(k,1,"There is none of Tag in the field!");
				m_ListID.EnsureVisible(k,TRUE);
			}
			else
			{
				m_ListID.SetItemText(k,1,"There are Tags in the field!");
				m_ListID.EnsureVisible(k,TRUE);
			}
			k++;
			KillTimer(4);
			m_DetectTag=FALSE;
			UpdateData(FALSE);
		}
		UpdateStatus();
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}
		break;
	}
	
	CPropertyPage::OnTimer(nIDEvent);
}

void CEPCC1G2Test::UpdateStatus()
{
	switch(m_HardVersion & 0xFF)
	{
	case 0x0B:
		GetDlgItem(IDC_CHECK1_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm&& !m_DetectTag && !m_Kword);
		GetDlgItem(IDC_CHECK2_6C)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3_6C)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4_6C)->EnableWindow(FALSE);
		break;
	case 0x0C:
		GetDlgItem(IDC_CHECK1_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
		GetDlgItem(IDC_CHECK2_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
		GetDlgItem(IDC_CHECK3_6C)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4_6C)->EnableWindow(FALSE);
		break;
	case 0x0E:
		GetDlgItem(IDC_CHECK1_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
		GetDlgItem(IDC_CHECK2_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
		GetDlgItem(IDC_CHECK3_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
		GetDlgItem(IDC_CHECK4_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
		break;
	default:
		if ( ifConnectReader )
		{
			GetDlgItem(IDC_CHECK1_6C)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK2_6C)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK3_6C)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4_6C)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_CHECK1_6C)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK2_6C)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK3_6C)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK4_6C)->EnableWindow(FALSE);
		}
		
	}

	GetDlgItem(IDC_BUTTON1_SetProtectAG_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_BUTTON2_KillTag_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_BUTTON3_SetProtectBB_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_BUTTON4_WrtieD_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_BUTTON5_SetAlarm_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_BUTTON6_LockRead_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_BUTTON7_UnlockRaed_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);

	GetDlgItem(IDC_CHECK5_ListEpcofTag_6C)->EnableWindow(ifConnectReader && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_CHECK6_ReadD_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_CHECK7_EasAlarm_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_CHECK9_CalibrateB_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag);
	GetDlgItem(IDC_CHECK10_DetectTag_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_Kword);

	GetDlgItem(IDC_COMBO1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_COMBO2)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_COMBO3)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_COMBO4)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_COMBO5)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_COMBO6)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_COMBO7)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);

	GetDlgItem(IDC_EDIT1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT2)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT3)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT4)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT5)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT6)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT7)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT8)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT9)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT10)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT11)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT12)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT13)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_EDIT14)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);

	//GetDlgItem(IDC_RADIO1_PassWord_6C)->EnableWindow(!m_ListTagID && !m_ReadDataBlock && !m_EasAlarm);
	GetDlgItem(IDC_RADIO2_EPC_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO3_TID_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO6_AnyReadWrite_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO6_PermRead_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO7_ReadandWdriteState_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO8_NeverReadAndWrite_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO9_KillPsdAB_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO10_AccessPsdAC_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO11_WriteFormandState_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO12_PerWriteable_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO13_WriteformSecState_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO14_Neverwriteable_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !OpenPassword && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO15_PasswordB_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO16_EPC_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO17_TID_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO18_User_6C)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO19)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO20)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO21)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO22)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO23)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);
	GetDlgItem(IDC_RADIO24)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_EasAlarm && !m_DetectTag && !m_Kword);


	//看看RS485通信如何,下面要不要启用?
	#if 0
	if ( ConnectMode == 2 )
	{
		//RS485，则定为500ms----6,200ms----5, 100ms----4
		m_Interval.SetCurSel(5);
		m_Interval.EnableWindow(FALSE);
	}
	#endif

	GetDlgItem(IDC_RADIO3_TID_6C)->EnableWindow(FALSE);

}

CString CEPCC1G2Test::ReportError(USHORT res)
{
	CString str;
	switch (res)
	{
	case 0x01:
		str="Connect antenna fail!";
		break;
	case 0x02:
		str="No Tag!";
		break;
	case 0x03:
		str="Illegal Tag!";
		break;
	case 0x04:
		str="Power is not enough!";
		break;
	case 0x05:
		str="The memory has been protected!";
		break;
	case 0x06:
		str="Check sum error!";
		break;
	case 0x07:
		str="Parameter error!";
		break;
	case 0x08:
		str="The memory don't exist!";
		break;
	case 0x09:
		str="The Access Password is error!";
		break;
	case 0x0A:
		str="The Kill Password cannot be 000000!";
		break;
	case 0x0E:
		str="Locked Tags in the field!";
		break;
	case 0x1E:
		str="Invalid Command!";
		break;
	case 0x1F:
		str="Other Error!";
		break;
	default:
		str="Unbeknown Error!";
	}

	return str;
}

//List EPC of Tag,列出标签
void CEPCC1G2Test::OnCHECK5ListEpcofTag6C() 
{
	apiReturn res;
	UpdateData(TRUE);
	CString str;

	if ((m_LAddress<0) || (m_LAddress>2047))
	{
		//MessageBox("Please input Location of Tag Address between 0 and 2047!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0083"), theApp.g_LoadString("IDWQB_D0084"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT1))->SetSel(0,-1);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_LLen<0) || (m_LLen>2048))
	{
		//MessageBox("Please input Length of Tag Data between 0 and 2048!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0085"), theApp.g_LoadString("IDWQB_D0086"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT2))->SetSel(0,-1);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	str=m_LData.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_LData))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0087"), theApp.g_LoadString("IDWQB_D0088"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}
	int str_len=strlen(m_LData);
	str=m_LData;
	int i,m;

	if (m_LLen==0)
		m=0;
	else
	{
		m=m_LLen/8;
		if (m_LLen%8!=0)
		{
			for(i=0;i<((m+1)*2-str_len);i++)
				str+="0";
			m++;
		}
	}
	/*if ((str_len*4)<m_LLen)
	{
		for(i=0;i<(m_LLen*2-str_len);i++)
			str+="0";
		MessageBox("Please input enough length tag data!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}*/

	mem=m_mem;
	ptr=m_LAddress;
	len=m_LLen;

	for(i=0;i<m;i++)
	{
		mask[i]=(BYTE)strtol(((CString)str[i*2]+(CString)str[i*2+1]),NULL,16);
	}

	int interval[]={10,20,30,50,100,200,500};
	timer_interval=interval[m_Interval.GetCurSel()];
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
			//m_antenna_sel += 1;
			m_antenna_sel = 1;
		}
		
		if(m_Antenna2)
		{
			bTmpAnt[1] = 2;
			iModAnt++;
			m_antenna_sel = 2;
		}
		
		if(m_Antenna3)
		{
			bTmpAnt[2] = 4;
			iModAnt++;
			m_antenna_sel = 4;
		}
		
		if(m_Antenna4)
		{
			bTmpAnt[3] = 8;
			iModAnt++;
			m_antenna_sel = 8;
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
			//MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0089"), theApp.g_LoadString("IDWQB_D0090"), MB_ICONWARNING);
			m_ListTagID=FALSE;
			UpdateData(FALSE);
			return;
			break;
// 		case 1:
// 		case 2:
// 		case 4:
// 		case 8:
		default:
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
				//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
				m_ListTagID=FALSE;
				UpdateData(FALSE);
				return;
			}
			break;
		}
		if ( 2 == ConnectMode )
		{
			Sleep(ReadRS485SleepTime);
		}

		m_ListID.DeleteAllItems();
		Read_times=0;
		UpdateStatus();
		SetTimer(1,timer_interval,NULL);
	}
	else
	{
		KillTimer(1);
		UpdateStatus();

		m_TagID.ResetContent();
		m_LTagID.ResetContent();
		m_KTagID.ResetContent();
		m_LBTagID.ResetContent();
		m_ATagID.ResetContent();
		m_PTagID.ResetContent();

		int k=m_ListID.GetItemCount();
		CString str;
		CString strTemp;
		char temp[64];
		int ID_len;

		for(i=0;i<k;i++)
		{
			m_ListID.GetItemText(i,4,temp,3);
			EPCC1G2_IDBuffer[i][0]=(BYTE)strtol(temp,NULL,16);
			ID_len=EPCC1G2_IDBuffer[i][0]*2;

			str="";
			//m_ListID.GetItemText(i,1,temp,ID_len*2+1);
			m_ListID.GetItemText(i,1,temp,64);
			strTemp = temp;
			str = temp;
			str.Replace(" ", "");
			strcpy(temp , str);

			for(int j=0;j<ID_len;j++)
			{
				#if defined (EPCREADWRITEHEX)
				{
					EPCC1G2_IDBuffer[i][j+1]=(BYTE)strtol((CString)temp[j*2]+(CString)temp[j*2+1],NULL,16);
				}
				#endif
			}

			str.Format("%02d.",i+1);
			int iG = GetPrivateProfileInt("Setting","FormatG", 0, theApp.strConfigPath);
			if (iG)
			{	
				str+=strTemp;
			}
			else
			{
				str+=temp;
			}
			
			m_TagID.AddString(str);
			m_LTagID.AddString(str);
			m_KTagID.AddString(str);
			m_LBTagID.AddString(str);
			m_ATagID.AddString(str);
			m_PTagID.AddString(str);
		}

		m_TagID.SetCurSel(0);
		m_LTagID.SetCurSel(0);
		m_KTagID.SetCurSel(0);
		m_LBTagID.SetCurSel(0);
		m_ATagID.SetCurSel(0);
		m_PTagID.SetCurSel(0);


		//add by mqs 20130924
		//马工，明天帮我改一下那个DEMO  按下时发40 06 EE 01 00 00 00 + 校验  弹起的时候你发 40 06 EE 00 00 00 00 +加校验   你看这样做可以吗？ 
		//	你就帮我在弹起的时候 加发一条命令就好了
		if ( 1 == iPlatform )//0---626, 1---218
		{
			//218为了提高读标签速度，不用切换天线，加一个命令，下面自动切换天线，编译   否则无，用宏控制,add by mqs 20130910
			#if defined (ENABLE218TXNOAntenna)
			BYTE IDBuffer[30*256] = {0};
			int nCounter = 0;
			mem=0;
			for (i = 0; i < 1; i++)
			{
				switch(ConnectMode)
				{
				case 0://网口
					res=Net_EPC1G2_ReadLabelID(m_hSocket,mem,ptr,len,mask,IDBuffer,&nCounter);
					break;
				case 1://RS232
					res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,0);
					break;
				case 2://RS485
					res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,RS485Address);
					break;
				}
				if (_OK == res )
				{
					break;
				}
			}
			#else	
			
			#endif
		}

	}
}

void CEPCC1G2Test::OnCHECK6ReadD6C() 
{
	apiReturn res;
	CString str;
	int i,str_len;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		//MessageBox("Please read first than choose a tag!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0093"), theApp.g_LoadString("IDWQB_D0094"), MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	//m_RWAddress 指起始地址
	if (m_RWAddress<0)
	{
		//MessageBox("Please input Location of Tag Address more then 0!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0095"), theApp.g_LoadString("IDWQB_D0096"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT4)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	// m_RWLen 指长度
	if (m_RWLen<1)
	{
		//MessageBox("Please input Length of Tag Data more than 1!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0097"), theApp.g_LoadString("IDWQB_D0098"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT5)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	//0---密码， 1---EPC， 2---TID， 3---USER
	mem=m_RWmem;
	switch(mem)
	{
	case 0x00:
		if ((m_RWLen<1) || (m_RWLen>4))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 4 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0103"), theApp.g_LoadString("IDWQB_D0104"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	case 0x02:
		if ((m_RWLen<1) || (m_RWLen>64))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 8 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0105"), theApp.g_LoadString("IDWQB_D0106"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	case 0x01:
		if ((m_RWLen<1) || (m_RWLen>32))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 32 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0107"), theApp.g_LoadString("IDWQB_D0108"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	case 0x03:
		if ((m_RWLen<1) || (m_RWLen>128))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 128 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0109"), theApp.g_LoadString("IDWQB_D0110"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	}

	//访问密码
	str=m_RWAccessPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_RWAccessPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0099"), theApp.g_LoadString("IDWQB_D0100"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT11)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT11))->SetSel(0,-1);
		return;
	}
	str=m_RWAccessPassword;
	str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of AccessPassword!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0101"), theApp.g_LoadString("IDWQB_D0102"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}
	
	//m_RWmem 指0---密码，1---EPC，2---TID, 3---USER
	mem=m_RWmem;
	ptr=m_RWAddress;
	len=m_RWLen;

	int CurSel=m_TagID.GetCurSel();
	EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

	for(i=0;i<EPC_Word*2;i++)
	{
		IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
	}

	int interval[]={10,20,30,50,100,200,500};
	timer_interval=interval[m_Interval.GetCurSel()];
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
			//MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0089"), theApp.g_LoadString("IDWQB_D0090"), MB_ICONWARNING);
			m_ReadDataBlock=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
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
				//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
				m_ReadDataBlock=FALSE;
				UpdateData(FALSE);
				return;
			}
			break;
		}

		m_ListData.ResetContent();
		Read_times=0;
		UpdateStatus();
		SetTimer(2,timer_interval,NULL);
	}
	else
	{
		KillTimer(2);
		UpdateStatus();

		int dx=0;   
		CSize sz;    
		CDC*  pDC=m_ListData.GetDC();    
		for(i=0;i<m_ListData.GetCount();i++)   
		{   
			m_ListData.GetText(i,str);     
			sz=pDC->GetTextExtent(str);    
			if(sz.cx>dx)      
			dx=sz.cx;      
		}   
		m_ListData.ReleaseDC(pDC);   

		m_ListData.SetHorizontalExtent(dx);
	}
}

void CEPCC1G2Test::OnBUTTON4WrtieD6C() 
{
	apiReturn res;
	CString str;
	CString sTemp;
	int i,str_len;

	UpdateData(TRUE);
	m_ListData.ResetContent();

	//0---密码， 1---EPC， 2---TID， 3---USER
	mem=m_RWmem;
	switch(mem)
	{
	case 0x00:
		if ((m_RWLen<1) || (m_RWLen>4))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 4 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0103"), theApp.g_LoadString("IDWQB_D0104"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	case 0x02:
		if ((m_RWLen<1) || (m_RWLen>64))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 8 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0105"), theApp.g_LoadString("IDWQB_D0106"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	case 0x01:
		if ((m_RWLen<1) || (m_RWLen>32))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 32 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0107"), theApp.g_LoadString("IDWQB_D0108"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	case 0x03:
		if ((m_RWLen<1) || (m_RWLen>128))
		{
			//MessageBox("Please input Length of Tag Data between 1 and 128 Word!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0109"), theApp.g_LoadString("IDWQB_D0110"), MB_ICONWARNING);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		break;
	}
	len=m_RWLen;

	//sTemp	=	_T("007-2007-永久(1-2) ");
	str=m_Data;
#if defined (EPCREADWRITEHEX)
	str=m_Data.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_Data))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0111"), theApp.g_LoadString("IDWQB_D0112"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT6)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
		return;
	}
	str=m_Data;
	str_len=strlen(str);
	if ((str_len==0) || (str_len/4<len))
	{
		//MessageBox("Please input enough Length of Tag Data!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0113"), theApp.g_LoadString("IDWQB_D0114"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<(len*2);i++)
	{
		mask[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}
#else
	memset(mask, 0x00, sizeof(mask));
	memcpy(mask, str, len*2);
#endif

	str=m_RWAccessPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_RWAccessPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0115"), theApp.g_LoadString("IDWQB_D0116"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT11)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT11))->SetSel(0,-1);
		return;
	}
	str=m_RWAccessPassword;
	str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of AccessPassword!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0117"), theApp.g_LoadString("IDWQB_D0118"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
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
			//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0120"), theApp.g_LoadString("IDWQB_D0121"), MB_ICONWARNING);
		return;
	}

	#if 0//发卡机用这个接口，平时可以不用
	if (mem==1)
	{
		for(i=0;i<5;i++)
		{
			Sleep(30);
			switch(ConnectMode)
			{
			case 0://网口
				res = Net_EPC1G2_WriteEPC(m_hSocket,len,&mask[0],AccessPassword);		
				break;
			case 1://RS232
				res = EPC1G2_WriteEPC(m_hScanner,len,&mask[0],AccessPassword,0);		
				break;
			case 2://RS485
				res = EPC1G2_WriteEPC(m_hScanner,len,&mask[0],AccessPassword,RS485Address);		
				break;
			}
			if ((res==_OK) || (res==_write_prot_error) || (res==_memory_error) || (res==_password_error))
				break;
		}
	}
	else
	#endif
	{
		if (m_TagID.GetCount()<1)
		{
			//MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0122"), theApp.g_LoadString("IDWQB_D0123"), MB_ICONWARNING);
			UpdateData(FALSE);
			return;
		}

		switch(mem)
		{
		case 0x00:
			if ((m_RWAddress<0) || (m_RWAddress>3))
			{
				//MessageBox("Please input Location of Tag Address between 0 and 3!","Warning",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_D0124"), theApp.g_LoadString("IDWQB_D0125"), MB_ICONWARNING);
				GetDlgItem(IDC_EDIT4)->SetFocus();
				((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
				UpdateData(FALSE);
				return;
			}
			if ((m_RWAddress+m_RWLen)>4)
			{
				m_RWLen=4-m_RWAddress;
				UpdateData(FALSE);
				len=4-m_RWAddress;
			}
			break;
		case 0x02:
			if ((m_RWAddress<0) || (m_RWAddress>7))
			{
				//MessageBox("Please input Location of Tag Address between 0 and 7!","Warning",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_D0126"), theApp.g_LoadString("IDWQB_D0127"), MB_ICONWARNING);
				GetDlgItem(IDC_EDIT4)->SetFocus();
				((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
				UpdateData(FALSE);
				return;
			}
			//因为长标签，所以暂时去掉
// 			if ((m_RWAddress+m_RWLen)>8)
// 			{
// 				m_RWLen=8-m_RWAddress;
// 				UpdateData(FALSE);
// 				len=8-m_RWAddress;
// 			}
			break;
		case 0x03:
			if (m_RWAddress<0)
			{
				//MessageBox("Please input Location of Tag Address more than 0!","Warning",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_D0128"), theApp.g_LoadString("IDWQB_D0129"), MB_ICONWARNING);
				GetDlgItem(IDC_EDIT4)->SetFocus();
				((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
				UpdateData(FALSE);
				return;
			}
			break;
		}
		ptr=m_RWAddress;

		int CurSel=m_TagID.GetCurSel();
		EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

		for(int i=0;i<EPC_Word*2;i++)
		{
			IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
		}

		for(i=0;i<5;i++)
		{
			Sleep(30);
			switch(ConnectMode)
			{
			case 0://网口
				res=Net_EPC1G2_WriteWordBlock(m_hSocket,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword);			
				break;
			case 1://RS485
				res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,0);
				break;
			case 2://RS232
				res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,RS485Address);
				break;
			}
			if ((res==_OK) || (res==_write_prot_error) || (res==_memory_error) || (res==_password_error))
				break;
		}
	}

	if (res==_OK)
	{
		//m_ListData.AddString("Write Successfully!");
		m_ListData.AddString(theApp.g_LoadString("IDWQB_D0130"));
	}
	else
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str== theApp.g_LoadString("IDWQB_D0131") )
		{
			//str="Write Fail!";
			str=theApp.g_LoadString("IDWQB_D0132");
		}
		if (res==0x09)
		{
			//str="The access password is error!";
			str=theApp.g_LoadString("IDWQB_D0133");
		}
		m_ListData.AddString(str);
	}
}

void CEPCC1G2Test::OnButton1() 
{
	apiReturn res;
	CString str;
	BYTE AccessPassword[4];
	BYTE lock;
	int i,k;
	UpdateData(TRUE);

	if (m_LTagID.GetCount()<1)
	{
		//MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0122"), theApp.g_LoadString("IDWQB_D0123"), MB_ICONWARNING);
		UpdateData(FALSE);
		return;
	}

	str=m_LAccessPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_LAccessPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0087"), theApp.g_LoadString("IDWQB_D0088"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT10)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT10))->SetSel(0,-1);
		return;
	}
	str=m_LAccessPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of AccessPassword!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0101"), theApp.g_LoadString("IDWQB_D0102"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	int CurSel=m_TagID.GetCurSel();
	EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

	for(i=0;i<EPC_Word*2;i++)
	{
		IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
	}

	//k=MessageBox("Are you sure to protect this tag?","Notice",MB_YESNO|MB_ICONWARNING);
	k=MessageBox(theApp.g_LoadString("IDWQB_D0134"), theApp.g_LoadString("IDWQB_D0135"), MB_YESNO|MB_ICONWARNING);
	if (k!=6) 
		return;

	if (m_Lmem==0)//0为密码选中
	{
		mem=m_Password;
		lock=m_Condition+4;
	}
	else
	{
		mem=m_Lmem+1;
		lock=m_Condition2;
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
			//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0120"), theApp.g_LoadString("IDWQB_D0121"), MB_ICONWARNING);
		return;
	}

	for(i=0;i<5;i++)
	{
		Sleep(30);
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_SetLock(m_hSocket,EPC_Word,IDTemp,mem,lock,AccessPassword);
			break;
		case 1://RS232
			res=EPC1G2_SetLock(m_hScanner,EPC_Word,IDTemp,mem,lock,AccessPassword,0);
			break;
		case 2://RS485
			res=EPC1G2_SetLock(m_hScanner,EPC_Word,IDTemp,mem,lock,AccessPassword,RS485Address);
			break;
		}
		if ((res==_OK) || (res==_write_prot_error) || (res==_memory_error) || (res==_password_error))
			break;
	}

	if (res==_OK)
	{
		//MessageBox("Set Protect successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_D0136"), theApp.g_LoadString("IDWQB_D0137"), MB_ICONINFORMATION);
	}
	else
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str== theApp.g_LoadString("IDWQB_D0131") )
		{
			//str="Set Protect Fail!";
			str=theApp.g_LoadString("IDWQB_D0138");
		}
		if (res==0x09)
		{
			//str="The access password is error!";
			str=theApp.g_LoadString("IDWQB_D0133");
		}

		MessageBox(str,theApp.g_LoadString("IDWQB_D0137"),MB_ICONERROR);
	}
}

void CEPCC1G2Test::OnRadio19() 
{
	UpdateData(TRUE);
	OpenPassword=TRUE;
	UpdateStatus();
}

void CEPCC1G2Test::OnRadio20() 
{
	UpdateData(TRUE);
	OpenPassword=FALSE;
	UpdateStatus();
}

void CEPCC1G2Test::OnRadio21() 
{
	UpdateData(TRUE);
	OpenPassword=FALSE;
	UpdateStatus();
}

void CEPCC1G2Test::OnRadio22() 
{
	UpdateData(TRUE);
	OpenPassword=FALSE;
	UpdateStatus();
}


void CEPCC1G2Test::OnBUTTON2KillTag6C() 
{
	apiReturn res;
	CString str;
	BYTE KillPassword[4];
	int i,k;
	UpdateData(TRUE);

	if (m_KTagID.GetCount()<1)
	{
		//MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0093"), theApp.g_LoadString("IDWQB_D0094"), MB_ICONWARNING);
		UpdateData(FALSE);
		return;
	}

	str=m_KillPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_KillPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0099"), theApp.g_LoadString("IDWQB_D0100"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT9)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT9))->SetSel(0,-1);
		return;
	}
	str=m_KillPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of KillPassword!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0139"), theApp.g_LoadString("IDWQB_D0140"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		KillPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	int CurSel=m_KTagID.GetCurSel();
	EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

	for(i=0;i<EPC_Word*2;i++)
	{
		IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
	}

	//k=MessageBox("Are you sure to Kill the tag?","Notice",MB_OKCANCEL|MB_ICONWARNING);
	k=MessageBox(theApp.g_LoadString("IDWQB_D0141"), theApp.g_LoadString("IDWQB_D0142"), MB_OKCANCEL|MB_ICONWARNING);
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
			//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0120"), theApp.g_LoadString("IDWQB_D0121"), MB_ICONWARNING);
		return;
	}

	for(i=0;i<5;i++)
	{
		Sleep(30);
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_KillTag(m_hSocket,EPC_Word,IDTemp,KillPassword);
			break;
		case 1://RS232
			res=EPC1G2_KillTag(m_hScanner,EPC_Word,IDTemp,KillPassword,0);
			break;
		case 2://RS485
			res=EPC1G2_KillTag(m_hScanner,EPC_Word,IDTemp,KillPassword,RS485Address);
			break;
		}
		
		if ((res==_OK) || (res==_write_prot_error) || (res==_memory_error) || (res==_password_error))
			break;
	}
	
	if (res==_OK)
	{
		//MessageBox("Kill tag successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_D0143"), theApp.g_LoadString("IDWQB_D0144"), MB_ICONINFORMATION);
	}
	else
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str== theApp.g_LoadString("IDWQB_D0131") )
		{
			//str="Kill tag Fail!";
			str=theApp.g_LoadString("IDWQB_D0145");
		}
		if (res==0x09)
		{
			//str="The kill password is error!";
			str=theApp.g_LoadString("IDWQB_D0146");
		}

		MessageBox(str, theApp.g_LoadString("IDWQB_D0137"),MB_ICONERROR);
	}
}


void CEPCC1G2Test::OnButton3() 
{
	apiReturn res;
	CString str;
	BYTE AccessPassword[4];
	int i,k;
	UpdateData(TRUE);

	if (m_LBTagID.GetCount()<1)
	{
		//MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0093"), theApp.g_LoadString("IDWQB_D0094"), MB_ICONWARNING);
		return;
	}

	if (m_LBAddress<0)
	{
		//MessageBox("Please input Location of Tag Address more then 0!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0095"), theApp.g_LoadString("IDWQB_D0096"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT7)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT7))->SetSel(0,-1);
		return;
	}
	ptr=m_LBAddress;

	str=m_LBAccessPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_LBAccessPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0099"), theApp.g_LoadString("IDWQB_D0100"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT8)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT8))->SetSel(0,-1);
		return;
	}
	str=m_LBAccessPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of AccessPassword!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0101"), theApp.g_LoadString("IDWQB_D0102"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	int CurSel=m_LBTagID.GetCurSel();
	EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

	for(i=0;i<EPC_Word*2;i++)
	{
		IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
	}

	//str.Format("Are you sure to set protect address %d of User?",m_LBAddress);
	str.Format(theApp.g_LoadString("IDWQB_D0147"), m_LBAddress);
	k=MessageBox(str, theApp.g_LoadString("IDWQB_D0148"), MB_OKCANCEL|MB_ICONWARNING);
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
			//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0089"), theApp.g_LoadString("IDWQB_D0090"), MB_ICONWARNING);
		return;
	}

	for(i=0;i<5;i++)
	{
		Sleep(30);
		
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_BlockLock(m_hSocket,EPC_Word,IDTemp,ptr,AccessPassword);
			break;
		case 1://RS232
			res=EPC1G2_BlockLock(m_hScanner,EPC_Word,IDTemp,ptr,AccessPassword,0);
			break;
		case 2://RS485
			res=EPC1G2_BlockLock(m_hScanner,EPC_Word,IDTemp,ptr,AccessPassword,RS485Address);
			break;
		}
		if ((res==_OK) || (res==_write_prot_error) || (res==_memory_error) || (res==_password_error))
			break;
	}
	
	if (res==_OK)
	{
		//MessageBox("Set Protect successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_D0136"), theApp.g_LoadString("IDWQB_D0137"), MB_ICONINFORMATION);
	}
	else
	{
		
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str== theApp.g_LoadString("IDWQB_D0131") )
		{
			//str="Set Protect Fail!";
			str=theApp.g_LoadString("IDWQB_D0138");
		}
		if (res==0x09)
		{
			//str="The access password is error!";
			str=theApp.g_LoadString("IDWQB_D0133");
		}

		MessageBox(str,"Error",MB_ICONERROR);
	}
}

void CEPCC1G2Test::OnButton5() 
{
	apiReturn res;
	CString str;
	BYTE AccessPassword[4];
	int i;
	UpdateData(TRUE);

	if (m_ATagID.GetCount()<1)
	{
		//MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0093"), theApp.g_LoadString("IDWQB_D0094"), MB_ICONWARNING);
		return;
	}

	str=m_AAccessPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_AAccessPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0087"), theApp.g_LoadString("IDWQB_D0088"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT8)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT8))->SetSel(0,-1);
		return;
	}
	str=m_AAccessPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of AccessPassword!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0101"), theApp.g_LoadString("IDWQB_D0102"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	int CurSel=m_ATagID.GetCurSel();
	EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

	for(i=0;i<EPC_Word*2;i++)
	{
		IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
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
			//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0089"), theApp.g_LoadString("IDWQB_D0090"), MB_ICONWARNING);
		return;
	}

	for(i=0;i<5;i++)
	{
		Sleep(30);
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_ChangeEas(m_hSocket,EPC_Word,IDTemp,m_EasState,AccessPassword);
			break;
		case 1://RS232
			res=EPC1G2_ChangeEas(m_hScanner,EPC_Word,IDTemp,m_EasState,AccessPassword,0);
			break;
		case 2://RS485
			res=EPC1G2_ChangeEas(m_hScanner,EPC_Word,IDTemp,m_EasState,AccessPassword,RS485Address);
			break;
		}
		if ((res==_OK) || (res==_password_error))
			break;
	}
	
	if (res==_OK)
	{
		//MessageBox("Set Eas Alarm successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_D0149"), theApp.g_LoadString("IDWQB_D0150"), MB_ICONINFORMATION);
	}
	else
	{
		
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str== theApp.g_LoadString("IDWQB_D0131") )
		{
			//str="Set Eas Alarm Fail!";
			str=theApp.g_LoadString("IDWQB_D0151");
		}
		if (res==0x09)
		{
			//str="The access password is error!";
			str=theApp.g_LoadString("IDWQB_D0133");
		}


		MessageBox(str, theApp.g_LoadString("IDWQB_D0152"),MB_ICONERROR);
	}
}

void CEPCC1G2Test::OnCheck7() 
{
	apiReturn res;
	UpdateData(TRUE);

	int i = 0;
	int interval[]={10,20,30,50,100,200,500};
	timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_EasAlarm)
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
			//MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0089"), theApp.g_LoadString("IDWQB_D0090"), MB_ICONWARNING);
			m_EasAlarm=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
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
				//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
				m_EasAlarm=FALSE;
				UpdateData(FALSE);
				return;
			}
			break;
		}

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

//读保护设置
void CEPCC1G2Test::OnButton6() 
{
	// TODO: Add your control notification handler code here
	apiReturn res;
	CString str;
//	BYTE AccessPassword[4];
	int i;
	UpdateData(TRUE);

	if (m_PTagID.GetCount()<1)
	{
		//MessageBox("Please read first than choose a tag!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0093"), theApp.g_LoadString("IDWQB_D0094"), MB_ICONWARNING);
		return;
	}
	str=m_RProtectPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_RProtectPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0087"), theApp.g_LoadString("IDWQB_D0088"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT13)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT13))->SetSel(0,-1);
		return;
	}
	str=m_RProtectPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of RStreadProtect Password!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0133"), theApp.g_LoadString("IDWQB_D0135"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}
	
	int CurSel=m_PTagID.GetCurSel();
	EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

	for(i=0;i<EPC_Word*2;i++)
	{
		IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
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
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="SetAntenna Fail!Please try again!";
			MessageBox(str,"Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0120"), theApp.g_LoadString("IDWQB_D0121"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<5;i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_ReadProtect(m_hSocket,AccessPassword,EPC_Word,IDTemp);
			break;
		case 1://RS232
			res=EPC1G2_ReadProtect(m_hScanner,AccessPassword,EPC_Word,IDTemp,0);
			break;
		case 2://RS485
			res=EPC1G2_ReadProtect(m_hScanner,AccessPassword,EPC_Word,IDTemp,RS485Address);
			break;
		}
		if(res==_OK)
			break;
	}
	if(res!=_OK)
	{
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="Read Protect Fail!Please try again!";
			MessageBox(str,"Warning",MB_ICONWARNING);
			return;
	}
	else
	{
		//MessageBox("Read Protect successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_D0153"), theApp.g_LoadString("IDWQB_D0154"), MB_ICONINFORMATION);
	}

}

//复位读保护设置
void CEPCC1G2Test::OnButton7() 
{
	// TODO: Add your control notification handler code here
	apiReturn res;
	CString str;
//	BYTE AccessPassword[4];
	int i;
	UpdateData(TRUE);

/*	if (m_PTagID.GetCount()<1)
	{
		MessageBox("Please read first than choose a tag!","Warning",MB_ICONWARNING);
		return;
	}
*/	str=m_RProtectPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_RProtectPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0087"), theApp.g_LoadString("IDWQB_D0088"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT13)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT13))->SetSel(0,-1);
		return;
	}
	str=m_RProtectPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of RStreadProtect Password!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0133"), theApp.g_LoadString("IDWQB_D0135"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}
	
	int CurSel=m_PTagID.GetCurSel();
	EPC_Word=EPCC1G2_IDBuffer[CurSel][0];

	for(i=0;i<EPC_Word*2;i++)
	{
		IDTemp[i]=EPCC1G2_IDBuffer[CurSel][i+1];
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
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="SetAntenna Fail!Please try again!";
			MessageBox(str,"Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0120"), theApp.g_LoadString("IDWQB_D0121"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<5;i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res=Net_EPC1G2_RStreadProtect(m_hSocket,AccessPassword);
			break;
		case 1://RS232
			res=EPC1G2_RStreadProtect(m_hScanner,AccessPassword,0);
			break;
		case 2://RS485
			res=EPC1G2_RStreadProtect(m_hScanner,AccessPassword,RS485Address);
			break;
		}
		if(res==_OK)
			break;
	}
	if(res!=_OK)
	{
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="UnLockRead Fail!Please try again!";
			MessageBox(str,"Warning",MB_ICONWARNING);
			return;
	}
	else
	{
		//MessageBox("UnLockRead successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_D0155"), theApp.g_LoadString("IDWQB_D0156"), MB_ICONINFORMATION);
	}
}

void CEPCC1G2Test::OnCheck9() 
{
	// TODO: Add your control notification handler code here
	apiReturn res;
	CString str;
//	BYTE AccessPassword[4];
	int i;
	UpdateData(TRUE);

	str=m_KPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_KPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0115"), theApp.g_LoadString("IDWQB_D0116"), MB_ICONWARNING);
		m_Kword=FALSE;
		UpdateData(FALSE);
		GetDlgItem(IDC_EDIT14)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT14))->SetSel(0,-1);
		return;
	}
	str=m_KPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of RStreadProtect Password!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0117"), theApp.g_LoadString("IDWQB_D0118"), MB_ICONWARNING);
		m_Kword=FALSE;
		UpdateData(FALSE);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
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
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="SetAntenna Fail!Please try again!";
			MessageBox(str,"Warning",MB_ICONWARNING);
			m_Kword=FALSE;
			UpdateData(FALSE);
			return;
		}
		break;
	default:
		//MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_D0120"), theApp.g_LoadString("IDWQB_D0121"), MB_ICONWARNING);
		m_Kword=FALSE;
		UpdateData(FALSE);
		return;
	}
	if(m_Kword)
	{
		UpdateStatus();
		for(i=0;i<5;i++)
		{
//			res=EPC1G2_Calibrate(m_hScanner,AccessPassword,1);
			if(res==_OK)
				break;
		}
		if(res!=_OK)
		{
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="Open Calibrate Fail!Please try again!";
			MessageBox(str,"Warning",MB_ICONWARNING);
			m_Kword=FALSE;
			UpdateStatus();
			UpdateData(FALSE);
			return;
		}
	}
	else
	{
		UpdateStatus();
		for(i=0;i<5;i++)
		{
//			res=EPC1G2_Calibrate(m_hScanner,AccessPassword,0);
			if(res==_OK)
				break;
		}
		if(res!=_OK)
		{
			str=ReportError(res);
			if (str=="Unbeknown Error!")
				str="Close Calibrate Fail!Please try again!";
			MessageBox(str,"Warning",MB_ICONWARNING);
			m_Kword=TRUE;
			UpdateStatus();
			UpdateData(FALSE);
			return;
		}
	}
	
}
//侦测标签
void CEPCC1G2Test::OnCHECK10DetectTag6C() 
{
	// TODO: Add your control notification handler code here
	apiReturn res;
	UpdateData(TRUE);

	Detect=0;
	int i = 0;
	int interval[]={10,20,30,50,100,200,500};
	timer_interval=interval[m_Interval.GetCurSel()];
	if ( iPlatform	==	1 )	//0---626, 1---218)
	{
		timer_interval += 100;
	}
	if (m_DetectTag)
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
			//MessageBox("Please choose one antenna at least!","Warning",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_D0089"), theApp.g_LoadString("IDWQB_D0090"), MB_ICONWARNING);
			m_DetectTag=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
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
				//MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQB_D0091"), theApp.g_LoadString("IDWQB_D0092"), MB_ICONWARNING);
				m_DetectTag=FALSE;
				UpdateData(FALSE);
				return;
			}
			break;
		}

		m_ListID.DeleteAllItems();
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

BOOL CEPCC1G2Test::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString str,strtemp;
//	HWND hand;
	GetDlgItem(IDD_EPCC1G2_DIALOG)->m_hWnd;
	if(pMsg->message == WM_MOUSEMOVE )
	{
		POINT pt = pMsg->pt;
        ScreenToClient( &pt );

//		GetDlgItemText(m_hWnd,str);
	}
	else //如果在列表中点右键
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

void CEPCC1G2Test::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	UpdateStatus();
	
}

//EPC6CTRANDATAMSG
afx_msg LRESULT CEPCC1G2Test::OnEpc6ctrandatamsg(WPARAM wParam, LPARAM lParam)
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
					MessageBox(theApp.g_LoadString("IDWQB_D0159"),theApp.g_LoadString("IDWQB_D0142"), MB_ICONERROR|MB_OK );
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
				MessageBox(theApp.g_LoadString("IDWQB_D0158"),theApp.g_LoadString("IDWQB_D0158"), MB_ICONINFORMATION|MB_OK );
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


