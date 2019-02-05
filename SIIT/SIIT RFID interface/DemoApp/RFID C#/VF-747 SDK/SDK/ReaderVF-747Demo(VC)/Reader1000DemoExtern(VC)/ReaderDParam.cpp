// ReaderDParam.cpp : implementation file
//

#include "stdafx.h"
#include "readerdemo.h"
#include "ReaderDParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
HWND	gReaderDParaHwnd	=	NULL;	//218读写器参数窗体句柄

/////////////////////////////////////////////////////////////////////////////
// CReaderDParam property page

IMPLEMENT_DYNCREATE(CReaderDParam, CPropertyPage)

CReaderDParam::CReaderDParam() : CPropertyPage(CReaderDParam::IDD)
{
	//{{AFX_DATA_INIT(CReaderDParam)
		// NOTE: the ClassWizard will add member initialization here
	m_WorkMode = -1;
	m_Power = 0;
	m_NumofCard = 0;
	m_ISO6B = FALSE;
	m_EPCC1 = FALSE;
	m_EPCC1G2 = FALSE;
	m_EM4442 = FALSE;
	m_Antenna1 = FALSE;
	m_Antenna2 = FALSE;
	m_Antenna3 = FALSE;
	m_Antenna4 = FALSE;
	m_Port = 0;
	m_MAC = _T("");
	m_AutoMode = -1;
	m_OutputPort = -1;
	m_OutputManner = -1;
	m_ReportCondition = -1;
	m_PersistenceTime = 0;
	m_LenofList = 0;
	m_PauseTimeofReport = 0;
	m_TriggerMode = -1;
	m_FilterAddress = 0;
	m_FilterLength = 0;
	m_FilterMask = _T("");
	m_HardVer = _T("");
	m_SoftVer = _T("");
	m_ReaderID = _T("");
	m_Relay1 = FALSE;
	m_ifTestAlarm = FALSE;
	m_HostPort = 0;
	m_EnableBuzzer = FALSE;
	//m_RS485 = FALSE;
	m_AddressReader = 0;
	m_ReportOutput = FALSE;
	m_WiegandWidth = 0;
	m_WiegandInterval = 0;
	m_IDStart = 0;
	m_EnableRelay = FALSE;
	m_IDPosition = -1;
	m_Relay2 = FALSE;
	//}}AFX_DATA_INIT
}

CReaderDParam::~CReaderDParam()
{
}

void CReaderDParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReaderDParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COMBO5, m_ISO6BCondition);
	DDX_Control(pDX, IDC_IPADDRESS4, m_HostIPAddress);
	DDX_Control(pDX, IDC_LIST1, m_Info);
	DDX_Control(pDX, IDC_COMBO4, m_PauseTimeofRead);
	DDX_Control(pDX, IDC_IPADDRESS3, m_Gateway);
	DDX_Control(pDX, IDC_IPADDRESS2, m_Mask);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddress);
	DDX_Control(pDX, IDC_COMBO3, m_MaxFrequency);
	DDX_Control(pDX, IDC_COMBO2, m_MinFrequency);
	DDX_Control(pDX, IDC_COMBO1, m_BaudRate);
	DDX_Radio(pDX, IDC_RADIO1, m_WorkMode);
	DDX_Text(pDX, IDC_EDIT1, m_Power);
	DDX_Text(pDX, IDC_EDIT3, m_NumofCard);
	DDX_Check(pDX, IDC_CHECK1, m_ISO6B);
	DDX_Check(pDX, IDC_CHECK2, m_EPCC1);
	DDX_Check(pDX, IDC_CHECK3, m_EPCC1G2);
	DDX_Check(pDX, IDC_CHECK4, m_EM4442);
	DDX_Check(pDX, IDC_CHECK5, m_Antenna1);
	DDX_Check(pDX, IDC_CHECK6, m_Antenna2);
	DDX_Check(pDX, IDC_CHECK7, m_Antenna3);
	DDX_Check(pDX, IDC_CHECK8, m_Antenna4);
	DDX_Text(pDX, IDC_EDIT4, m_Port);
	DDX_Text(pDX, IDC_EDIT5, m_MAC);
	DDV_MaxChars(pDX, m_MAC, 12);
	DDX_Radio(pDX, IDC_RADIO3, m_AutoMode);
	DDX_Radio(pDX, IDC_RADIO8, m_OutputPort);
	DDX_Radio(pDX, IDC_RADIO5, m_OutputManner);
	DDX_Radio(pDX, IDC_RADIO11, m_ReportCondition);
	DDX_Text(pDX, IDC_EDIT6, m_PersistenceTime);
	DDX_Text(pDX, IDC_EDIT7, m_LenofList);
	DDX_Text(pDX, IDC_EDIT8, m_PauseTimeofReport);
	DDX_Radio(pDX, IDC_RADIO16, m_TriggerMode);
	DDX_Text(pDX, IDC_EDIT9, m_FilterAddress);
	DDX_Text(pDX, IDC_EDIT10, m_FilterLength);
	DDX_Text(pDX, IDC_EDIT11, m_FilterMask);
	DDX_Text(pDX, IDC_EDIT12, m_HardVer);
	DDX_Text(pDX, IDC_EDIT13, m_SoftVer);
	DDX_Text(pDX, IDC_EDIT14, m_ReaderID);
	DDV_MaxChars(pDX, m_ReaderID, 12);
	DDX_Check(pDX, IDC_CHECK25, m_Relay1);
	DDX_Check(pDX, IDC_CHECK26, m_ifTestAlarm);
	DDX_Text(pDX, IDC_EDIT20, m_HostPort);
	DDX_Check(pDX, IDC_CHECK27, m_EnableBuzzer);
	DDX_Check(pDX, IDC_CHECK17, m_RS485);
	DDX_Text(pDX, IDC_EDIT2, m_AddressReader);
	DDX_Check(pDX, IDC_CHECK20, m_ReportOutput);
	DDX_Text(pDX, IDC_EDIT15, m_WiegandWidth);
	DDX_Text(pDX, IDC_EDIT16, m_WiegandInterval);
	DDX_Text(pDX, IDC_EDIT17, m_IDStart);
	DDX_Check(pDX, IDC_CHECK19, m_EnableRelay);
	DDX_Radio(pDX, IDC_RADIO21, m_IDPosition);
	DDX_Check(pDX, IDC_CHECK18, m_Relay2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReaderDParam, CPropertyPage)
	//{{AFX_MSG_MAP(CReaderDParam)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTONGetModule, OnButtonGetModuleVer)	
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_READERPARMDATAMSG, OnReaderparmdatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderDParam message handlers

void CReaderDParam::OnInitUIText()	//更新语言
{
	//SetWindowText(theApp.g_LoadString("IDWQC_C0001"));//参数设置

	GetDlgItem(IDC_RADIO8)->SetWindowText(theApp.g_LoadString("IDWQC_C0002"));//RS232
	GetDlgItem(IDC_RADIO9)->SetWindowText(theApp.g_LoadString("IDWQC_C0003"));//RS485
	GetDlgItem(IDC_RADIO10)->SetWindowText(theApp.g_LoadString("IDWQC_C0004"));//RJ45
	GetDlgItem(IDC_RADIO19)->SetWindowText(theApp.g_LoadString("IDWQC_C0005"));//Wiegand26
	GetDlgItem(IDC_RADIO20)->SetWindowText(theApp.g_LoadString("IDWQC_C0006"));//Wiegand34
	GetDlgItem(IDC_STATIC_workmode)->SetWindowText(theApp.g_LoadString("IDWQC_C0007"));//Work Mode
	GetDlgItem(IDC_STATIC_basic_Param)->SetWindowText(theApp.g_LoadString("IDWQC_C0008"));//Basic Parameters
	GetDlgItem(IDC_STATIC_baudrate)->SetWindowText(theApp.g_LoadString("IDWQC_C0009"));//BaudRate of RS232/RS485 Port:
	GetDlgItem(IDC_STATIC_RFPOWER)->SetWindowText(theApp.g_LoadString("IDWQC_C0010"));//RF Power Output(0dBm-33dBm):
	GetDlgItem(IDC_STATIC_minfreq)->SetWindowText(theApp.g_LoadString("IDWQC_C0011"));//Min.Frequency of Carrier:
	GetDlgItem(IDC_STATIC_maxfreq)->SetWindowText(theApp.g_LoadString("IDWQC_C0012"));//Max.Frequency of Carrier:
	GetDlgItem(IDC_STATIC_IPReader)->SetWindowText(theApp.g_LoadString("IDWQC_C0013"));//IP Parameters for Reader 
	GetDlgItem(IDC_STATIC_workantenna)->SetWindowText(theApp.g_LoadString("IDWQC_C0014"));//Working Antenna
	GetDlgItem(IDC_STATIC_MaxTags)->SetWindowText(theApp.g_LoadString("IDWQC_C0015"));//Max Tags of once Reading(1～100):
	GetDlgItem(IDC_STATIC_typeoftag)->SetWindowText(theApp.g_LoadString("IDWQC_C0016"));//Type of Tag
	GetDlgItem(IDC_STATIC_addrreader)->SetWindowText(theApp.g_LoadString("IDWQC_C0017"));//Address of Reader(1-254):
	GetDlgItem(IDC_STATIC_ipaddressreader)->SetWindowText(theApp.g_LoadString("IDWQC_C0018"));//IP Address:
	GetDlgItem(IDC_STATIC_READERMAC)->SetWindowText(theApp.g_LoadString("IDWQC_C0019"));//MAC:
	GetDlgItem(IDC_RADIO1)->SetWindowText(theApp.g_LoadString("IDWQC_C0020"));//Auto
	GetDlgItem(IDC_RADIO2)->SetWindowText(theApp.g_LoadString("IDWQC_C0021"));//Command
	GetDlgItem(IDC_CHECK1)->SetWindowText(theApp.g_LoadString("IDWQC_C0022"));//ISO18000-6B
	GetDlgItem(IDC_CHECK2)->SetWindowText(theApp.g_LoadString("IDWQC_C0023"));//EPCC1
	GetDlgItem(IDC_CHECK3)->SetWindowText(theApp.g_LoadString("IDWQC_C0024"));//ISO18000-6C
	GetDlgItem(IDC_CHECK4)->SetWindowText(theApp.g_LoadString("IDWQC_C0025"));//ISO18000-6D
	GetDlgItem(IDC_CHECK5)->SetWindowText(theApp.g_LoadString("IDWQC_C0026"));//ANT1
	GetDlgItem(IDC_CHECK6)->SetWindowText(theApp.g_LoadString("IDWQC_C0027"));//ANT2
	GetDlgItem(IDC_CHECK7)->SetWindowText(theApp.g_LoadString("IDWQC_C0028"));//ANT3
	GetDlgItem(IDC_CHECK8)->SetWindowText(theApp.g_LoadString("IDWQC_C0029"));//ANT4
	GetDlgItem(IDC_BUTTON1)->SetWindowText(theApp.g_LoadString("IDWQC_C0030"));//Update Parameter
	GetDlgItem(IDC_STATIC_READERMASK)->SetWindowText(theApp.g_LoadString("IDWQC_C0031"));//Mask:
	GetDlgItem(IDC_STATIC_readergetway)->SetWindowText(theApp.g_LoadString("IDWQC_C0032"));//Gateway:
	GetDlgItem(IDC_STATIC_ReaderPort)->SetWindowText(theApp.g_LoadString("IDWQC_C0033"));//Port:
	GetDlgItem(IDC_BUTTON2)->SetWindowText(theApp.g_LoadString("IDWQC_C0034"));//Set Network Parameter
	GetDlgItem(IDC_STATIC_autoparam)->SetWindowText(theApp.g_LoadString("IDWQC_C0035"));//AutoParameters
	GetDlgItem(IDC_STATIC_automodee)->SetWindowText(theApp.g_LoadString("IDWQC_C0036"));//Auto Mode
	GetDlgItem(IDC_RADIO3)->SetWindowText(theApp.g_LoadString("IDWQC_C0037"));//Continuing
	GetDlgItem(IDC_RADIO4)->SetWindowText(theApp.g_LoadString("IDWQC_C0038"));//Trigger
	GetDlgItem(IDC_STATIC_storetime)->SetWindowText(theApp.g_LoadString("IDWQC_C0039"));//Storing Time(s):
	GetDlgItem(IDC_STATIC_numberoftags)->SetWindowText(theApp.g_LoadString("IDWQC_C0040"));//Number of Tags:
	GetDlgItem(IDC_STATIC_DiapauseofReader)->SetWindowText(theApp.g_LoadString("IDWQC_C0041"));//Diapause of Reading:
	GetDlgItem(IDC_STATIC_formatoutput)->SetWindowText(theApp.g_LoadString("IDWQC_C0042"));//Format of Output
	GetDlgItem(IDC_STATIC_portoutput)->SetWindowText(theApp.g_LoadString("IDWQC_C0043"));//Port for Output
	GetDlgItem(IDC_STATIC_DiapauseofReport)->SetWindowText(theApp.g_LoadString("IDWQC_C0044"));//Diapause of Report(s):
	GetDlgItem(IDC_STATIC_confiReport)->SetWindowText(theApp.g_LoadString("IDWQC_C0045"));//Condition of Report
	GetDlgItem(IDC_RADIO5)->SetWindowText(theApp.g_LoadString("IDWQC_C0046"));//Terse
	GetDlgItem(IDC_RADIO6)->SetWindowText(theApp.g_LoadString("IDWQC_C0047"));//Standard
	GetDlgItem(IDC_RADIO7)->SetWindowText(theApp.g_LoadString("IDWQC_C0048"));//XML
	GetDlgItem(IDC_RADIO11)->SetWindowText(theApp.g_LoadString("IDWQC_C0049"));//Notify Now
	GetDlgItem(IDC_RADIO12)->SetWindowText(theApp.g_LoadString("IDWQC_C0050"));//Timing Notify
	GetDlgItem(IDC_RADIO13)->SetWindowText(theApp.g_LoadString("IDWQC_C0051"));//Add
	GetDlgItem(IDC_RADIO14)->SetWindowText(theApp.g_LoadString("IDWQC_C0052"));//Remove
	GetDlgItem(IDC_RADIO15)->SetWindowText(theApp.g_LoadString("IDWQC_C0053"));//Change
	GetDlgItem(IDC_STATIC_triggerlevel)->SetWindowText(theApp.g_LoadString("IDWQC_C0054"));//Trigger Level
	GetDlgItem(IDC_RADIO16)->SetWindowText(theApp.g_LoadString("IDWQC_C0055"));//Low
	GetDlgItem(IDC_RADIO17)->SetWindowText(theApp.g_LoadString("IDWQC_C0056"));//High
	GetDlgItem(IDC_EPCC1G2_STATIC)->SetWindowText(theApp.g_LoadString("IDWQC_C0057"));//ReportFilter
	GetDlgItem(IDC_STATIC_ADDR)->SetWindowText(theApp.g_LoadString("IDWQC_C0058"));//Address of Tag EPC (bit):
	GetDlgItem(IDC_STATIC_LEN)->SetWindowText(theApp.g_LoadString("IDWQC_C0059"));//Length of Tag EPC(bit):
	GetDlgItem(IDC_EPC_STATIC)->SetWindowText(theApp.g_LoadString("IDWQC_C0060"));//Tag Data(HEX):
	GetDlgItem(IDC_BUTTON3)->SetWindowText(theApp.g_LoadString("IDWQC_C0061"));//Factory Parameter
	GetDlgItem(IDC_STATIC_HardVer)->SetWindowText(theApp.g_LoadString("IDWQC_C0062"));//Hard Version:
	GetDlgItem(IDC_STATIC_SoftVer)->SetWindowText(theApp.g_LoadString("IDWQC_C0063"));//Soft Version:
	GetDlgItem(IDC_STATIC_information)->SetWindowText(theApp.g_LoadString("IDWQC_C0064"));//Information
	GetDlgItem(IDC_BUTTON5)->SetWindowText(theApp.g_LoadString("IDWQC_C0065"));//SetReaderID
	GetDlgItem(IDC_BUTTON8)->SetWindowText(theApp.g_LoadString("IDWQC_C0066"));//SetTime
	GetDlgItem(IDC_BUTTON9)->SetWindowText(theApp.g_LoadString("IDWQC_C0067"));//GetTime
	GetDlgItem(IDC_BUTTON10)->SetWindowText(theApp.g_LoadString("IDWQC_C0068"));//GetInputPin
	GetDlgItem(IDC_STATIC_setRelay)->SetWindowText(theApp.g_LoadString("IDWQC_C0069"));//SetRelay
	GetDlgItem(IDC_CHECK25)->SetWindowText(theApp.g_LoadString("IDWQC_C0070"));//Relay1
	GetDlgItem(IDC_BUTTON11)->SetWindowText(theApp.g_LoadString("IDWQC_C0071"));//Set Relay
	GetDlgItem(IDC_BUTTON12)->SetWindowText(theApp.g_LoadString("IDWQC_C0072"));//Get Relay
	GetDlgItem(IDC_STATIC_IPHost)->SetWindowText(theApp.g_LoadString("IDWQC_C0073"));//IP Parameters for Host
	GetDlgItem(IDC_STATIC_Ipaddr)->SetWindowText(theApp.g_LoadString("IDWQC_C0074"));//IP Address:
	GetDlgItem(IDC_CHECK26)->SetWindowText(theApp.g_LoadString("IDWQC_C0075"));//Check Alarm
	GetDlgItem(IDC_STATIC_hostportt)->SetWindowText(theApp.g_LoadString("IDWQC_C0076"));//Port:
	GetDlgItem(IDC_BUTTON15)->SetWindowText(theApp.g_LoadString("IDWQC_C0077"));//Stop Auto
	GetDlgItem(IDC_CHECK27)->SetWindowText(theApp.g_LoadString("IDWQC_C0078"));//Enable Buzzer
	GetDlgItem(IDC_STATIC_Readeridd)->SetWindowText(theApp.g_LoadString("IDWQC_C0079"));//Reader ID:
	GetDlgItem(IDC_CHECK17)->SetWindowText(theApp.g_LoadString("IDWQC_C0080"));//RS485
	GetDlgItem(IDC_CHECK18)->SetWindowText(theApp.g_LoadString("IDWQC_C0081"));//Relay2
	GetDlgItem(IDC_BUTTON4)->SetWindowText(theApp.g_LoadString("IDWQC_C0082"));//Set Filter
	GetDlgItem(IDC_BUTTON6)->SetWindowText(theApp.g_LoadString("IDWQC_C0083"));//Get Filter
	GetDlgItem(IDC_CHECK19)->SetWindowText(theApp.g_LoadString("IDWQC_C0084"));//Ctrl Relay
	GetDlgItem(IDC_STATIC_wiegandoutput)->SetWindowText(theApp.g_LoadString("IDWQC_C0085"));//Wiegand Output
	GetDlgItem(IDC_STATIC_pulsewidth)->SetWindowText(theApp.g_LoadString("IDWQC_C0086"));//Pulse Width (*10us):
	GetDlgItem(IDC_STATIC_pulseinterval)->SetWindowText(theApp.g_LoadString("IDWQC_C0087"));//Pulse Interval (*10us):
	GetDlgItem(IDC_RADIO21)->SetWindowText(theApp.g_LoadString("IDWQC_C0088"));//ID of the Tag
	GetDlgItem(IDC_RADIO22)->SetWindowText(theApp.g_LoadString("IDWQC_C0089"));//SN Selected by User
	GetDlgItem(IDC_STATIC_startaddrid)->SetWindowText(theApp.g_LoadString("IDWQC_C0090"));//Start Address of ID:
	GetDlgItem(IDC_CHECK20)->SetWindowText(theApp.g_LoadString("IDWQC_C0091"));//Report Output
	GetDlgItem(IDC_BUTTONGetModule)->SetWindowText(theApp.g_LoadString("IDWQC_C0092"));//Get Moudle ver
	GetDlgItem(IDC_STATIC_GETMODULE)->SetWindowText(theApp.g_LoadString("IDWQC_C0093"));//Module Version:
	GetDlgItem(IDC_STATIC_AntSleepTime)->SetWindowText(theApp.g_LoadString("IDWQC_C0265"));//天线睡眠时间:

}


void CReaderDParam::UpdateStatus()
{

	GetDlgItem(IDC_BUTTON1)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON15)->EnableWindow(ifConnectReader);

	GetDlgItem(IDC_COMBO1)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_COMBO2)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_COMBO3)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_COMBO4)->EnableWindow(ifConnectReader);

	GetDlgItem(IDC_CHECK5)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK6)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK7)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK8)->EnableWindow(ifConnectReader);
	//GetDlgItem(IDC_CHECK17)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK18)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK19)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK20)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK25)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK26)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK27)->EnableWindow(ifConnectReader);

	GetDlgItem(IDC_EDIT1)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT2)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT3)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT4)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT5)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT6)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT7)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT8)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT9)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT10)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT11)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT12)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT13)->EnableWindow(ifConnectReader);
	//GetDlgItem(IDC_EDIT14)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT15)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT16)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT17)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT20)->EnableWindow(ifConnectReader);

	GetDlgItem(IDC_RADIO1)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO2)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO3)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO4)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO5)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO6)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO8)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO9)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO10)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO11)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO12)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO13)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO14)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO15)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO16)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO17)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO19)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO20)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO21)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO22)->EnableWindow(ifConnectReader);

	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_IPADDRESS2)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_IPADDRESS3)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_IPADDRESS4)->EnableWindow(ifConnectReader);


	GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader);//6B
	GetDlgItem(IDC_CHECK3)->EnableWindow(ifConnectReader);//6C

	//GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);//屏掉设ID
	

}

BOOL CReaderDParam::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//218为了提高读标签速度，不用切换天线，加一个命令，下面自动切换天线，编译   否则无，用宏控制,add by mqs 20130910
	#if defined (ENABLE218TXNOAntenna)
	//天线睡眠时间	AnSleepTime;		//(29)//天线睡眠时间，单位：ms,(1-255)
	
	#else	
	GetDlgItem(IDC_STATIC_AntSleepTime)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_AntSleepTime)->ShowWindow(SW_HIDE);
	#endif

	//add by martrin 去掉RS485使能
	GetDlgItem(IDC_CHECK17)->ShowWindow(SW_HIDE);

	return CPropertyPage::OnSetActive();
}


CString CReaderDParam::ReportError(USHORT res)
{
	CString str;
	switch (res)
	{
	case 0x01:
		//str="Connect antenna fail!";
		str = theApp.g_LoadString("IDWQC_C0094");
		break;
	case 0x02:
		//str="No Tag!";
		str = theApp.g_LoadString("IDWQC_C0095");
		break;
	case 0x03:
		//str="Nonlicet Tag!";
		str = theApp.g_LoadString("IDWQC_C0096");
		break;
	case 0x04:
		//str="Power is not enough!";
		str = theApp.g_LoadString("IDWQC_C0097");
		break;
	case 0x05:
		//str="The memory has been protected!";
		str = theApp.g_LoadString("IDWQC_C0098");
		break;
	case 0x06:
		//str="Check sum error!";
		str = theApp.g_LoadString("IDWQC_C0099");
		break;
	case 0x07:
		//str="Parameter error!";
		str = theApp.g_LoadString("IDWQC_C0100");
		break;
	case 0x08:
		//str="The memory don't exist!";
		str = theApp.g_LoadString("IDWQC_C0101");
		break;
	case 0x09:
		//str="The Password is error!";
		str = theApp.g_LoadString("IDWQC_C0102");
		break;
	case 0x0A:
		//str="The Kill Password cannot be 000000!";
		str = theApp.g_LoadString("IDWQC_C0103");
		break;
	case 0x0B:
		//str="Illegal operation command!";
		str = theApp.g_LoadString("IDWQC_C0104");
		break;
	case 0x0C:
		//str="Illegal operation user!";
		str = theApp.g_LoadString("IDWQC_C0105");
		break;
	case 0x1E:
		//str="Invalid Command!";
		str = theApp.g_LoadString("IDWQC_C0106");
		break;
	case 0x1F:
		//str="Other Error!";
		str = theApp.g_LoadString("IDWQC_C0107");
		break;
	default:
		//str="Unbeknown Error!";
		str = theApp.g_LoadString("IDWQC_C0108");
	}

	return str;
}

BOOL CReaderDParam::ReadParameter()
{
	apiReturn res;
	ReaderBasicParam ReaderParam;
	ReaderAutoParam ReaderAutoParam;
	int i=0,l=0,ModDepth=0,Port=0,FilterAddress=0,FilterLength=0;
	BYTE IP_Address[4],Mask[4],Gateway[4],MAC[6],FilterMask[64],ReaderID[12];
	CString str="",str_temp="";

	str.Format("%02d%02d",(m_HardVersion>>8) & 0xFF,m_HardVersion & 0xFF);
	m_HardVer=str;
	str.Format("%02d%02d",(m_SoftVersion>>8) & 0xFF,m_SoftVersion & 0xFF);
	m_SoftVer=str;

	UpdateData(FALSE);
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for(i=0;i<3;i++)
	{	
		
		switch(ConnectMode)
		{
		case 0:
			res=Net_ReadBasicParam(m_hSocket,&ReaderParam);
			break;
		case 1:
			res=ReadBasicParam(m_hScanner,&ReaderParam,0);
			break;
		case 2:
			res=ReadBasicParam(m_hScanner,&ReaderParam,RS485Address);
			break;
		}
		if (res==_OK)
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
		//MessageBox("Read Basic Parameter Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0109"), theApp.g_LoadString("IDWQC_C0110"), MB_ICONERROR);
		return FALSE;
	}


	nFrequencyRange=1;
	if((ReaderParam.Min_Frequence<7)&&(ReaderParam.Max_Frequence<7))//对应R2000协议中的青绿色部分
	{
		nFrequencyRange=2;
	}

	//if((ReaderParam.Min_Frequence<54)&&(ReaderParam.Max_Frequence<54)&&(ReaderParam.Min_Frequence>42)&&(ReaderParam.Max_Frequence>42))
	//{
	//	nFrequencyRange=3;
	//}

	m_BaudRate.SetCurSel(ReaderParam.BaudRate-4);
    m_Power = ReaderParam.Power;
	m_MinFrequency.SetCurSel(ReaderParam.Min_Frequence);
	m_MaxFrequency.SetCurSel(ReaderParam.Max_Frequence);
	m_WorkMode = ReaderParam.WorkMode;
	m_AddressReader=ReaderParam.ReaderAddress;
	m_NumofCard = ReaderParam.NumofCard;

	m_ISO6B = ReaderParam.TagType & 0x01;
	m_EPCC1 = (ReaderParam.TagType>>1) & 0x01;
	m_EPCC1G2 = (ReaderParam.TagType>>2) & 0x01;
	m_EM4442 = (ReaderParam.TagType>>3) & 0x01;

	m_EnableBuzzer=ReaderParam.EnableBuzzer & 0x01;
	//m_RS485=(ReaderParam.EnableBuzzer>>3) & 0x01;

	tagType=ReaderParam.TagType;
	currentTagType=ReaderParam.TagType;

	UpdateData(FALSE);
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for(i=0;i<3;i++)
	{
		
		switch(ConnectMode)
		{
		case 0:
			res=Net_GetReaderNetwork(m_hSocket,IP_Address,&Port,Mask,Gateway);
			break;
		case 1:
			res=GetReaderNetwork(m_hScanner,IP_Address,&Port,Mask,Gateway,0);
			break;
		case 2:
			res=GetReaderNetwork(m_hScanner,IP_Address,&Port,Mask,Gateway,RS485Address);
			break;
		}
		if (res==_OK)
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
		//MessageBox("Read Net Parameter Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0111"), theApp.g_LoadString("IDWQC_C0112"), MB_ICONERROR);
		return FALSE;
	}
	m_IPAddress.SetAddress(IP_Address[0],IP_Address[1],IP_Address[2],IP_Address[3]);
	m_Mask.SetAddress(Mask[0],Mask[1],Mask[2],Mask[3]);
	m_Gateway.SetAddress(Gateway[0],Gateway[1],Gateway[2],Gateway[3]);
	m_Port=Port;


	UpdateData(FALSE);
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for(i=0;i<3;i++)
	{
		
		switch(ConnectMode)
		{
		case 0:
			res=Net_GetReaderMAC(m_hSocket,MAC);
			break;
		case 1:
			res=GetReaderMAC(m_hScanner,MAC,0);
			break;
		case 2:
			res=GetReaderMAC(m_hScanner,MAC,RS485Address);
			break;
		}
		if (res==_OK)
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
		//MessageBox("Read MAC Parameter Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0113"), theApp.g_LoadString("IDWQC_C0114"), MB_ICONERROR);
		return FALSE;
	}

	str="";
	for(i=0;i<6;i++)
	{
		str_temp.Format("%02X",MAC[i]);
		str+=str_temp;
	}
	m_MAC=str;

	UpdateData(FALSE);
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for(i=0;i<3;i++)
	{	
		
		switch(ConnectMode)
		{
		case 0:
			res=Net_ReadAutoParam(m_hSocket,&ReaderAutoParam);
			break;
		case 1:
			res=ReadAutoParam(m_hScanner,&ReaderAutoParam,0);
			break;
		case 2:
			res=ReadAutoParam(m_hScanner,&ReaderAutoParam,RS485Address);
			break;
		}
		if (res==_OK)
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
		//MessageBox("Read Auto Parameter Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0115"), theApp.g_LoadString("IDWQC_C0116"), MB_ICONERROR);
		return FALSE;
	}
	m_AutoMode=ReaderAutoParam.AutoMode;
	m_PersistenceTime=ReaderAutoParam.TimeH;
	m_PersistenceTime=(m_PersistenceTime<<8)+ReaderAutoParam.TimeL;
	m_PauseTimeofRead.SetCurSel(ReaderAutoParam.Interval);
	m_LenofList=ReaderAutoParam.NumH;
	m_LenofList=(m_LenofList<<8)+ReaderAutoParam.NumL;
	m_OutputManner=ReaderAutoParam.OutputManner;
	m_OutputPort=ReaderAutoParam.OutInterface;
	m_WiegandWidth=ReaderAutoParam.WiegandWidth;
	m_WiegandInterval=ReaderAutoParam.WiegandInterval; 
	m_IDStart=ReaderAutoParam.ID_Start;
	m_IDPosition=ReaderAutoParam.IDPosition;
	m_PauseTimeofReport=ReaderAutoParam.Report_Interval;
	m_ReportCondition=ReaderAutoParam.Report_Condition;
    m_ReportOutput=ReaderAutoParam.Report_Output & 0x01;
	m_Antenna1 = ReaderAutoParam.Antenna & 0x01;
	m_Antenna2 = (ReaderAutoParam.Antenna>>1) & 0x01;
	m_Antenna3 = (ReaderAutoParam.Antenna>>2) & 0x01;
	m_Antenna4 = (ReaderAutoParam.Antenna>>3) & 0x01;
	m_TriggerMode=ReaderAutoParam.TriggerMode;
	m_HostIPAddress.SetAddress(ReaderAutoParam.HostIP1,ReaderAutoParam.HostIP2,ReaderAutoParam.HostIP3,ReaderAutoParam.HostIP4);
	m_HostPort=(((int)ReaderAutoParam.Port1)<<8)+(int)ReaderAutoParam.Port2;
	m_ifTestAlarm=ReaderAutoParam.Alarm;
	m_EnableRelay=ReaderAutoParam.EnableRelay;

	nHostPort=m_HostPort;
	sprintf(nHostNetAddr, "%d.%d.%d.%d", ReaderAutoParam.HostIP1,ReaderAutoParam.HostIP2,ReaderAutoParam.HostIP3,ReaderAutoParam.HostIP4);

	

	UpdateData(FALSE);


	FilterAddress	=	0;
	FilterLength	=	0;
	memset(FilterMask, 0x00, sizeof(FilterMask));
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for(i=0;i<3;i++)
	{	
		
		switch(ConnectMode)
		{
		case 0:
			res=Net_GetReportFilter(m_hSocket,&FilterAddress,&FilterLength,&FilterMask[0]);
			break;
		case 1:
			res=GetReportFilter(m_hScanner,&FilterAddress,&FilterLength,&FilterMask[0],0);
			break;
		case 2:
			res=GetReportFilter(m_hScanner,&FilterAddress,&FilterLength,&FilterMask[0],RS485Address);
			break;
		}
		if (res==_OK)
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
		//MessageBox("Read ReportFilter Parameter Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0117"), theApp.g_LoadString("IDWQC_C0118"), MB_ICONERROR);
		return FALSE;
	}

  	m_FilterAddress=FilterAddress;
	m_FilterLength=FilterLength;

	if (FilterLength%8==0)
	{
		l=FilterLength/8;
	}
	else
	{
		l=FilterLength/8+1;
	}

	str="";
	for(i=0;i<l;i++)
	{
		str_temp.Format("%02X",FilterMask[i]);
		str+=str_temp;
	}
	m_FilterMask=str;

	UpdateData(FALSE);
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for(i=0;i<3;i++)
	{	
		
		switch(ConnectMode)
		{
		case 0:
			res=Net_GetReaderID(m_hSocket,ReaderID);
			break;
		case 1:
			res=GetReaderID(m_hScanner,ReaderID,0);
			break;
		case 2:
			res=GetReaderID(m_hScanner,ReaderID,RS485Address);
			break;
		}
		if (res==_OK)
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
		//MessageBox("Read ReaderID Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0119"), theApp.g_LoadString("IDWQC_C0120"), MB_ICONERROR);
		return FALSE;
	}

    str.Empty(); 
	for(i=0;i<10;i++)
	{
		str+=ReaderID[i];
	}
	m_ReaderID=str;

	UpdateData(FALSE);

	
	CString strText;
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for(i=0;i<5;i++)
	{	
		
		switch(ConnectMode)
		{
		case 0:
			res=Net_GetModuleVer(m_hSocket,bModuleVer);
			break;
		case 1:
			res=GetModuleVer(m_hScanner,bModuleVer,0);
			break;
		case 2:
			res=GetModuleVer(m_hScanner,bModuleVer,RS485Address);	
			break;
		}
		if (res==_OK)
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
		//MessageBox("Read Module Version Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0121"), theApp.g_LoadString("IDWQC_C0122"), MB_ICONERROR);
		return FALSE;
	}

	strText.Format("%d.%d", bModuleVer[0], bModuleVer[1]);
	GetDlgItem(IDC_EDIT_ModuleVer)->SetWindowText(strText);



	UpdateStatus();

	return TRUE;
}

BOOL CReaderDParam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	gReaderDParaHwnd	=	this->GetSafeHwnd();

    double Freq,jumpFreq;
	int i;
	CString temp;
	Freq=865.00;
	jumpFreq=0.500;
    for(i=0;i<7;i++)
	{
		temp.Format("%d:%7.3f",i, Freq+i*jumpFreq); 
		m_MinFrequency.AddString(temp);
		m_MaxFrequency.AddString(temp);
	}

	Freq=902.00;
	jumpFreq=0.500;

	for(i=0;i<53;i++)
	{
		temp.Format("%d:%7.3f",i+7, Freq+i*jumpFreq); 
		m_MinFrequency.AddString(temp);
		m_MaxFrequency.AddString(temp);
	}

	m_MinFrequency.SetCurSel(0);
	m_MaxFrequency.SetCurSel(i-1);

	//218专用
	OnCbnSetFrT(4, -1, -1);//1-FCC,2-ETSI,3-CHN,4-Custom

	UpdateData(FALSE);

	GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);//设置机器ID号
	((CEdit*)GetDlgItem(IDC_EDIT14))->SetReadOnly(TRUE);//禁止用
	GetDlgItem(IDC_BUTTONGetModule)->ShowWindow(SW_HIDE);//得到模块版本号
	
	//参数页
	::SendMessage(gReaderDParaHwnd,WM_READERPARMDATAMSG,2,0);	//convert language

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReaderDParam::OnCbnSetFrT(int sel, int imin, int imax)//sel为国家频率下标,imin为最小频率下标,imax为最大频率下标(针对218)
{
	CComboBox *m_MinFrequency = (CComboBox*)GetDlgItem(IDC_COMBO2);
	CComboBox *m_MaxFrequency = (CComboBox*)GetDlgItem(IDC_COMBO3);
	m_MinFrequency->ResetContent();//复位
	m_MaxFrequency->ResetContent();//复位
	
	double Freq,jumpFreq;
	int i=0;
	int j=0;
	CString temp;
	
	if ( 1 <= sel && sel <= 4 )
	{
		//三个频都要
		Freq=865.00;
		jumpFreq=0.500;
		j = 0;
		for(i=0;i<7;i++)
		{
			temp.Format("%d:%7.3f",i, Freq+i*jumpFreq);
			m_MinFrequency->AddString(temp);
			m_MaxFrequency->AddString(temp);
			j++;
		}
		
		if ( 1 == sel )//FCC
		{	
			m_MinFrequency->ResetContent();
			m_MaxFrequency->ResetContent();
			
			Freq=902.00;
			jumpFreq=0.500;
			
			i=0;
			j=i;
			for(i=0;i<53;i++)
			{
				temp.Format("%d:%7.3f",i+7, Freq+i*jumpFreq);
				m_MinFrequency->AddString(temp);
				m_MaxFrequency->AddString(temp);
				j++;
			}
		}
		else if ( 3 == sel ) //China
		{
			
			m_MinFrequency->ResetContent();
			m_MaxFrequency->ResetContent();
			
			Freq=920.000;
			jumpFreq=0.500;
			
			i=0;
			j=i;
			for(i=0;i<11;i++)
			{
				temp.Format("%d:%7.3f",i+0x2B, Freq+i*jumpFreq);
				m_MinFrequency->AddString(temp);
				m_MaxFrequency->AddString(temp);
				j++;
			}
			
			
		}
		else if ( 4 == sel ) //Custom
		{
			//测试，假若 频点间隔:50; 频点数量:10; 起始：928000
			//FreT[1] = 0x32;
			//FreT[2] = 0x0A;
			//FreT[3] = 0x00;
			//FreT[4] = 0x29;
			//FreT[5] = 0x0E;
			
			m_MinFrequency->ResetContent();
			m_MaxFrequency->ResetContent();

			int iBet = FreT[1]*10;//频点间隔, jumpFreq=0.500;
			int iNum = FreT[2];//频点数量
			long lxStart = 0;//起始频点, Freq=920.000;
			memcpy(&lxStart, &FreT[3], 3);

			j = 0;
			for( i=0; i < iNum; i++)
			{
				//928000 + i*(50*10)
				//temp.Format("%d:%ld",i, lxStart+i*iBet);//Freq+i*jumpFreq
				temp.Format("%d:%7.3f",i, (lxStart+i*iBet)/1000.000f);//Freq+i*jumpFreq

				m_MinFrequency->AddString(temp);
				m_MaxFrequency->AddString(temp);

				j++;
			}



		}

		if ( i > 0 )
		{
			if ( imin == -1 && imax == -1 )
			{
				m_MinFrequency->SetCurSel(0);
				m_MaxFrequency->SetCurSel(j-1);
			}
			else
			{
				m_MinFrequency->SetCurSel(imin); 
				m_MaxFrequency->SetCurSel(imax); 
			}
			
		}
	}
	
}

void CReaderDParam::OnButton1() 
{
	UpdateData(TRUE);

	apiReturn res;
	ReaderBasicParam ReaderParam;
	ReaderAutoParam ReaderAutoParam;
	int Antenna,TagType,i,m=0,str_len=0,filterLength=0,EnableBuzzer;
	CString str;
	BYTE FilterMask[64]={0},MAC[6];
	DWORD dwIPAddress;//,dwHostMask,dwHostGateway;

	BYTE IP_Address[4],Mask[4],Gateway[4];
	int Port;

	//新调整,新方法 add by mqs 20131118
	#if 0
	if (m_MinFrequency.GetCurSel()>m_MaxFrequency.GetCurSel())
	{
		//MessageBox("The Min of Frequency cannot be greater than the Max of Frequency!!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0123"), theApp.g_LoadString("IDWQC_C0124"), MB_ICONERROR);
		return;
	}

	//if (m_MaxFrequency.GetCurSel()-m_MinFrequency.GetCurSel()<4)
	if (m_MaxFrequency.GetCurSel()-m_MinFrequency.GetCurSel()<0)
	{
		//MessageBox("Max of Frequency - Min of Frequency >4!!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0125"), theApp.g_LoadString("IDWQC_C0126"), MB_ICONERROR);
		return;
	}

	switch(nFrequencyRange)
	{
	case 1:
		if((m_MinFrequency.GetCurSel()<7)||(m_MinFrequency.GetCurSel()>59))
		{
			//MessageBox("Set Min of Frequency error!!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0127"), theApp.g_LoadString("IDWQC_C0128"), MB_ICONERROR);
		    return;
		}

		if((m_MaxFrequency.GetCurSel()<7)||(m_MaxFrequency.GetCurSel()>59))
		{
			//MessageBox("Set Max of Frequency error!!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0129"), theApp.g_LoadString("IDWQC_C0130"), MB_ICONERROR);
		    return;
		}
		break;
	case 2:
		if((m_MinFrequency.GetCurSel()<0)||(m_MinFrequency.GetCurSel()>6))
		{
			//MessageBox("Set Min of Frequency error!!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0131"), theApp.g_LoadString("IDWQC_C0132"), MB_ICONERROR);
		    return;
		}

		if((m_MaxFrequency.GetCurSel()<0)||(m_MaxFrequency.GetCurSel()>6))
		{
			//MessageBox("Set Max of Frequency error!!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0133"), theApp.g_LoadString("IDWQC_C0134"), MB_ICONERROR);
		    return;
		}
		break;

	//20120420作修改,去掉这个判断,见R2000协议紫色部分
	#if 0
	case 3:
		if((m_MinFrequency.GetCurSel()<43)||(m_MinFrequency.GetCurSel()>53))
		{
			//MessageBox("Set Min of Frequency error!!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0135"), theApp.g_LoadString("IDWQC_C0136"), MB_ICONERROR);
		    return;
		}

		if((m_MaxFrequency.GetCurSel()<43)||(m_MaxFrequency.GetCurSel()>53))
		{
			//MessageBox("Set Max of Frequency error!!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0137"), theApp.g_LoadString("IDWQC_C0138"), MB_ICONERROR);
		    return;
		}
		break;
	#endif

	default:
		//MessageBox("Set Frequency error!!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0139"), theApp.g_LoadString("IDWQC_C0140"), MB_ICONERROR);
		return;
		break;
	}
	#endif


	//if ((m_Power<20) || (m_Power>33))
	if ((m_Power<0) || (m_Power>33))
	{
		//MessageBox("Please input Power between 20dBm and 33dBm!","Error",MB_ICONERROR);
		//MessageBox("Please input Power between 0dBm and 33dBm!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0141"), theApp.g_LoadString("IDWQC_C0142"), MB_ICONERROR);
		return;
	}

	if ((m_AddressReader<1) || (m_AddressReader>254))
	{
		//MessageBox("Please input  RS485 Address between 1 and 254!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0143"), theApp.g_LoadString("IDWQC_C0144"), MB_ICONERROR);
		return;
	}

	if ((m_NumofCard<1) || (m_NumofCard>100))
	{
		//MessageBox("Please input Max Tags of once Reading between 1 and 100 !","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0145"), theApp.g_LoadString("IDWQC_C0146"), MB_ICONERROR);
		return;
	}

	if ((m_PersistenceTime<5) || (m_PersistenceTime>65535))
	{
		//MessageBox("Please input Persistence Time between 5 and 65535 !","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0147"), theApp.g_LoadString("IDWQC_C0148"), MB_ICONERROR);
		return;
	}

	if ((m_LenofList<1) || (m_LenofList>500))
	{
		//MessageBox("Please input length of List between 1 and 500 !","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0149"), theApp.g_LoadString("IDWQC_C0150"), MB_ICONERROR);
		return;
	}

	if ((m_PauseTimeofReport<1) || (m_PauseTimeofReport>255))
	{
		//MessageBox("Please input Pause time of Report between 1 and 255 !","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0151"), theApp.g_LoadString("IDWQC_C0152"), MB_ICONERROR);
		return;
	}

	switch(tagType)
	{
	case 0x01:
		if ((m_FilterAddress<0) || (m_FilterAddress>7))
		{
			//MessageBox("Please input Address of Tag between 0 and 7 !","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0153"), theApp.g_LoadString("IDWQC_C0154"), MB_ICONERROR);
			return;
		}
		break;
	case 0x04:
		if ((m_FilterAddress<0) || (m_FilterAddress>95))
		{
			//MessageBox("Please input Address of Tag EPC between 0 and 95 !","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0155"), theApp.g_LoadString("IDWQC_C0156"), MB_ICONERROR);
			return;
		}
		if ((m_FilterLength<0) || (m_FilterLength>96))
		{
			//MessageBox("Please input Address of Tag EPC between 0 and 96 !","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0157"), theApp.g_LoadString("IDWQC_C0158"), MB_ICONERROR);
			return;
		}

		if ((m_IDStart<0) || (m_IDStart>8))
		{
			//MessageBox("Please input Start Address of ID between 0 and 8 !","Notice",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0159"), theApp.g_LoadString("IDWQC_C0160"), MB_ICONERROR);
			GetDlgItem(IDC_EDIT17)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT17))->SetSel(0,-1);
			return;
		}

		break;
	}

	str="";
	str=m_FilterMask.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_FilterMask))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQC_C0161"), theApp.g_LoadString("IDWQC_C0162"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT11)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT11))->SetSel(0,-1);
		UpdateData(FALSE);
		return;
	}

	if ((m_HostPort<1024) || (m_HostPort>65535))
	{
		//MessageBox("Please input HostPort between 1024 and 65535!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0163"), theApp.g_LoadString("IDWQC_C0164"), MB_ICONERROR);
		return;
	}

	if ((m_WiegandWidth<1) || (m_WiegandWidth>255))
	{
		//MessageBox("Please input Pulse Width between 1 and 255 !","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0165"), theApp.g_LoadString("IDWQC_C0166"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT15)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT15))->SetSel(0,-1);
		return;
	}

	if ((m_WiegandInterval<1) || (m_WiegandInterval>255))
	{
		//MessageBox("Please input Pulse Interval between 1 and 255 !","Notice",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0167"), theApp.g_LoadString("IDWQC_C0168"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT16)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT16))->SetSel(0,-1);
		return;
	}

	Antenna = 0;
	if(m_Antenna1)
		Antenna += 1;
	if(m_Antenna2)
		Antenna += 2;
	if(m_Antenna3)
		Antenna += 4;
	if(m_Antenna4)
		Antenna += 8;
	if (Antenna == 0)
	{
		//MessageBox("Please choose Antenna!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0169"), theApp.g_LoadString("IDWQC_C0170"), MB_ICONERROR);
		return;
	}

	TagType = 0;
	if(m_ISO6B)
		TagType += 1;
	if(m_EPCC1)
		TagType += 2;
	if(m_EPCC1G2)
		TagType += 4;
	if(m_EM4442)
		TagType += 8;
	if (TagType == 0)
	{
		//MessageBox("Please choose TagType!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0171"), theApp.g_LoadString("IDWQC_C0172"), MB_ICONERROR);
		return;
	}

	m_HostIPAddress.GetAddress(dwIPAddress);

	if ((m_Port<1024) || (m_Port>65535))
	{
		//MessageBox("Please input Port between 1024 and 65535!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0173"), theApp.g_LoadString("IDWQC_C0174"), MB_ICONERROR);
		return;
	}

	if (strlen(m_MAC)<12)
	{
		//MessageBox("Please input unabridged MAC!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0175"), theApp.g_LoadString("IDWQC_C0176"), MB_ICONERROR);
		return;
	}
	str=m_MAC.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_MAC))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQC_C0177"), theApp.g_LoadString("IDWQC_C0178"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT5)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
		UpdateData(FALSE);
		return;
	}

	m_IPAddress.GetAddress(IP_Address[0],IP_Address[1],IP_Address[2],IP_Address[3]);
	m_Mask.GetAddress(Mask[0],Mask[1],Mask[2],Mask[3]);
	m_Gateway.GetAddress(Gateway[0],Gateway[1],Gateway[2],Gateway[3]);
	Port=m_Port;

	str=m_MAC;
	for(i=0;i<6;i++)
	{
		MAC[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	EnableBuzzer=1;
	if(!m_EnableBuzzer)
	{
		EnableBuzzer=0;
	}
// 	if(m_RS485)
// 	{
// 		EnableBuzzer+=8;
// 	}

	ReaderParam.WorkMode = m_WorkMode;
	ReaderParam.Power = m_Power;
	ReaderParam.TagType = TagType;
	ReaderParam.NumofCard = m_NumofCard;
	ReaderParam.BaudRate = m_BaudRate.GetCurSel()+4;
	ReaderParam.Min_Frequence = m_MinFrequency.GetCurSel();
	ReaderParam.Max_Frequence = m_MaxFrequency.GetCurSel();
	ReaderParam.EnableBuzzer = EnableBuzzer;
	ReaderParam.ReaderAddress =m_AddressReader;
	ReaderParam.ReadTimes=1;

	ReaderParam.IP1=IP_Address[0]; 
	ReaderParam.IP2=IP_Address[1]; 
	ReaderParam.IP3=IP_Address[2]; 
	ReaderParam.IP4=IP_Address[3]; 

	ReaderParam.Port1=(Port>>8) & 0xFF;; 
	ReaderParam.Port2=Port & 0xFF; 

	ReaderParam.Mask1=Mask[0];
	ReaderParam.Mask2=Mask[1];
	ReaderParam.Mask3=Mask[2];
	ReaderParam.Mask4=Mask[3];
	ReaderParam.Gateway1=Gateway[0];
	ReaderParam.Gateway2=Gateway[1];
	ReaderParam.Gateway3=Gateway[2];
	ReaderParam.Gateway4=Gateway[3];

	ReaderParam.MAC1=MAC[0];
	ReaderParam.MAC2=MAC[1];
	ReaderParam.MAC3=MAC[2];
	ReaderParam.MAC4=MAC[3];
	ReaderParam.MAC5=MAC[4];
	ReaderParam.MAC6=MAC[5];

	ReaderParam.Reserve5=0;
	ReaderParam.ReadDuration=0; 


	//add by mqs 20131118设频
	//////////////////////////////////////////////////////////////////////////
	//40H  08H  05H  reg starF endF  NULL  Check
	//reg	01	   FCC/02	   ETSI/03	   CHN
	//Fmin	1个字节，表示起始频率
	//Fmax	1个字节，表示终止频率
	//NULL	默认为0
	
	//如果下面这种情况：
	//reg	频率规范	  此处只能取值04
	//Fspace	频点间隔	  频点间隔*10kHz
	//Fnum	频点数量	包含起始频率的频点数量，1为以起始频率定频发射。此参数必须大于0
	//starF	起始频率	单位为KHz。16进制数高位在前。例如915000KHz则发送 0D F6 38。占3bytes
	BYTE FreS[6] = {0};
	BYTE Min_Frequence = 0;
	BYTE Max_Frequence = 0;
	Min_Frequence = m_MinFrequency.GetCurSel();
	Max_Frequence = m_MaxFrequency.GetCurSel();

	BYTE Fre=FreT[0]-1;//218下标从1开始算
	if ( 1 <= Fre+1 && Fre+1 <= 3 )
	{
		if ( 1 == Fre + 1 ) //FCC
		{
			//if ( Min_Frequence < 0x07 )
			//{
			//	MessageBox("Min_Frequence < 0x07!","Notice",MB_ICONINFORMATION);
			//	return;
			//}
			FreS[0] = 1;
			FreS[1] = Min_Frequence+7;
			FreS[2] = Max_Frequence+7;
		}
		else if ( 2 == Fre + 1)//
		{
			FreS[0] = 2;
			FreS[1] = Min_Frequence;
			FreS[2] = Max_Frequence;
		}
		else
		{
			FreS[0] = 3;
			FreS[1] = Min_Frequence+0x2B;
			FreS[2] = Max_Frequence+0x2B;
		}
		
	}
	else
	{
		FreS[0] = 0;
		FreS[1] = Min_Frequence;
		FreS[2] = Max_Frequence;
	}
	ReaderParam.Min_Frequence = FreS[1];
	ReaderParam.Max_Frequence = FreS[2];
	//////////////////////////////////////////////////////////////////////////

	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_WriteBasicParam(m_hSocket,&ReaderParam);
			break;
		case 1:
			res=WriteBasicParam(m_hScanner,&ReaderParam,0);
			break;
		case 2:
			res=WriteBasicParam(m_hScanner,&ReaderParam,RS485Address);
			break;
		}
		if (res==_OK)
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
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0179"))
		{
			//str="Error of Update Reader Parameter!";
			str=theApp.g_LoadString("IDWQC_C0180");
		}
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0181"),MB_ICONERROR);
		return;
	}

	tagType=ReaderParam.TagType;
	currentTagType=ReaderParam.TagType;

	#if 0 //add by mqs 20120425, 因为测到下位机运行不正常，所以这个屏了
	Sleep(50);
	if (ConnectMode==1)
	{
		int br[]={9600,19200,38400,57600,115200};
		int baud=br[ReaderParam.BaudRate-4];

		res=SetBaudRate(m_hScanner,baud,RS485Address);
		if (res!=_OK)
		{
			str=ReportError(res);
			//if (str=="Unbeknown Error!")
			if (str==theApp.g_LoadString("IDWQC_C0182"))
			{
				//str="Error of Set BaudRate!";
				str=theApp.g_LoadString("IDWQC_C0183");
			}
			//MessageBox(str,"Error",MB_ICONERROR);
			MessageBox(str,theApp.g_LoadString("IDWQC_C0184"),MB_ICONERROR);
			return;
		}

		DCB dcb;
		GetCommState(m_hScanner, &dcb);
		dcb.BaudRate = baud;
		SetCommState(m_hScanner, &dcb);

		PurgeComm(m_hScanner, PURGE_TXCLEAR);	// flush transimition queue
		PurgeComm(m_hScanner, PURGE_RXCLEAR);	// flush receiveing queue
	}
	#endif

	//Sleep(50);
	ReaderAutoParam.AutoMode=m_AutoMode;
	ReaderAutoParam.TimeH=(BYTE)(m_PersistenceTime>>8);
	ReaderAutoParam.TimeL=(BYTE)m_PersistenceTime;
	ReaderAutoParam.Interval=m_PauseTimeofRead.GetCurSel();
	ReaderAutoParam.NumH=(BYTE)(m_LenofList>>8);
	ReaderAutoParam.NumL=(BYTE)m_LenofList;
	ReaderAutoParam.OutputManner=m_OutputManner;
	ReaderAutoParam.OutInterface=m_OutputPort;
	ReaderAutoParam.Report_Interval=m_PauseTimeofReport;
	ReaderAutoParam.Report_Condition=m_ReportCondition;
	ReaderAutoParam.Antenna=Antenna;
	ReaderAutoParam.TriggerMode=m_TriggerMode;
	ReaderAutoParam.HostIP1=HIBYTE(HIWORD(dwIPAddress));
	ReaderAutoParam.HostIP2=LOBYTE(HIWORD(dwIPAddress));
	ReaderAutoParam.HostIP3=HIBYTE(LOWORD(dwIPAddress));
	ReaderAutoParam.HostIP4=LOBYTE(LOWORD(dwIPAddress));

	ReaderAutoParam.Port1=(m_HostPort>>8) & 0xFF;
	ReaderAutoParam.Port2=m_HostPort & 0xFF;

	if(m_EnableRelay)
	{
		ReaderAutoParam.EnableRelay=1;
	}
	else
	{
		ReaderAutoParam.EnableRelay=0;
	}

	ReaderAutoParam.WiegandInterval =m_WiegandInterval;
	ReaderAutoParam.WiegandWidth =m_WiegandWidth;
	ReaderAutoParam.ID_Start =m_IDStart;
	ReaderAutoParam.IDPosition =m_IDPosition;
	
	if(m_ReportOutput)
	{
		ReaderAutoParam.Report_Output=1;
	}
	else
	{
		ReaderAutoParam.Report_Output=0;
	}

	if (m_ifTestAlarm)
		ReaderAutoParam.Alarm=1;
	else
		ReaderAutoParam.Alarm=0;


	//218为了提高读标签速度，不用切换天线，加一个命令，下面自动切换天线，编译   否则无，用宏控制,add by mqs 20130910
	#if defined (ENABLE218TXNOAntenna)
	//天线睡眠时间	AnSleepTime;		//(29)//天线睡眠时间，单位：ms,(1-255)
	GetDlgItem(IDC_EDIT_AntSleepTime)->GetWindowText(str);
	sscanf(str, "%d", &ReaderAutoParam.AnSleepTime);
	#else	
	
	#endif


	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for (i = 0; i < 3; i++)
	{
	
		switch(ConnectMode)
		{
		case 0:
			res=Net_WriteAutoParam(m_hSocket,&ReaderAutoParam);
			break;
		case 1:
			res=WriteAutoParam(m_hScanner,&ReaderAutoParam,0);
			break;
		case 2:
			res=WriteAutoParam(m_hScanner,&ReaderAutoParam,RS485Address);
			break;
		}
		if (res==_OK)
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
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0185"))
		{
			//str="Error of Update Reader Auto Parameter!";
			str=theApp.g_LoadString("IDWQC_C0186");
		}
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0187"),MB_ICONERROR);
		return;
	}

	
	//可以不要它 add by mqs 20120420,不用重启下位机,因为设IP,所以又要
	#if 1
	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_Reboot(m_hSocket);
			break;
		case 1:
			res=Reboot(m_hScanner, 0);
			break;
		case 2:
			res=Reboot(m_hScanner, RS485Address);
			break;
		}
		if (res==_OK)
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
	if(res == _OK)
	{
		//MessageBox("Success of Update Reader Parameter!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQC_C0191"),theApp.g_LoadString("IDWQC_C0192"),MB_ICONINFORMATION);
	}
	else
	{
		//MessageBox("Error of Reboot Reader!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0193"),theApp.g_LoadString("IDWQC_C0194"),MB_ICONERROR);
		return;
	}
	#endif

#if 1
	Sleep(100);
	if(res == _OK)
	{
		if (ConnectMode==1)
		{
			int br[]={9600,19200,38400,57600,115200};
			int baud=br[ReaderParam.BaudRate-4];

			

			DCB dcb;
			GetCommState(m_hScanner, &dcb);
			dcb.BaudRate = baud;
			SetCommState(m_hScanner, &dcb);

			PurgeComm(m_hScanner, PURGE_TXCLEAR);	// flush transimition queue
			PurgeComm(m_hScanner, PURGE_RXCLEAR);	// flush receiveing queue
		}
	}
#endif

	//成功后，要更新全局
	*gBasicParam	=	ReaderParam;
	*gAutoParam		=	ReaderAutoParam;
	return;

}

BOOL CReaderDParam::ReadConnParameter()
{
	ReaderBasicParam ReaderParam={0};
	ReaderAutoParam ReadeAutoParam={0};
	int i=0,l=0,ModDepth=0,Port=0,FilterAddress=0,FilterLength=0;
	BYTE IP_Address[4],Mask[4],Gateway[4],MAC[6],ReaderID[12];
	CString str="",str_temp="";
	
	UpdateData(TRUE);

	strcpy((char*)ReaderID, (char*)gReaderID);

	str.Format("%02d%02d",(m_HardVersion>>8) & 0xFF,m_HardVersion & 0xFF);
	m_HardVer=str;
	str.Format("%02d%02d",(m_SoftVersion>>8) & 0xFF,m_SoftVersion & 0xFF);
	m_SoftVer=str;

	ReaderParam		=	*gBasicParam;
	ReadeAutoParam	=	*gAutoParam;

	nFrequencyRange=1;
	if((ReaderParam.Min_Frequence<7)&&(ReaderParam.Max_Frequence<7))//对应R2000协议中的青绿色部分
	{
		nFrequencyRange=2;
	}
	
	//if((ReaderParam.Min_Frequence<54)&&(ReaderParam.Max_Frequence<54)&&(ReaderParam.Min_Frequence>42)&&(ReaderParam.Max_Frequence>42))
	//{
	//	nFrequencyRange=3;
	//}
	
	m_BaudRate.SetCurSel(ReaderParam.BaudRate-4);
    m_Power = ReaderParam.Power;
	m_MinFrequency.SetCurSel(ReaderParam.Min_Frequence);
	m_MaxFrequency.SetCurSel(ReaderParam.Max_Frequence);
	m_WorkMode = ReaderParam.WorkMode;
	m_AddressReader=ReaderParam.ReaderAddress;
	m_NumofCard = ReaderParam.NumofCard;
	
	m_ISO6B = ReaderParam.TagType & 0x01;
	m_EPCC1 = (ReaderParam.TagType>>1) & 0x01;
	m_EPCC1G2 = (ReaderParam.TagType>>2) & 0x01;
	m_EM4442 = (ReaderParam.TagType>>3) & 0x01;
	
	m_EnableBuzzer=ReaderParam.EnableBuzzer & 0x01;
	//m_RS485=(ReaderParam.EnableBuzzer>>3) & 0x01;
	
	tagType=ReaderParam.TagType;
	currentTagType=ReaderParam.TagType;
	

	//读写器IP
	IP_Address[0]	=	ReaderParam.IP1;
	IP_Address[1]	=	ReaderParam.IP2;
	IP_Address[2]	=	ReaderParam.IP3;
	IP_Address[3]	=	ReaderParam.IP4;
	
	Mask[0]	=	ReaderParam.Mask1;
	Mask[1]	=	ReaderParam.Mask2;
	Mask[2]	=	ReaderParam.Mask3;
	Mask[3]	=	ReaderParam.Mask4;

	Gateway[0]	=	ReaderParam.Gateway1;
	Gateway[1]	=	ReaderParam.Gateway2;
	Gateway[2]	=	ReaderParam.Gateway3;
	Gateway[3]	=	ReaderParam.Gateway4;

	Port=(((int)ReaderParam.Port1)<<8)+(int)ReaderParam.Port2;

	m_IPAddress.SetAddress(IP_Address[0],IP_Address[1],IP_Address[2],IP_Address[3]);
	m_Mask.SetAddress(Mask[0],Mask[1],Mask[2],Mask[3]);
	m_Gateway.SetAddress(Gateway[0],Gateway[1],Gateway[2],Gateway[3]);
	m_Port=Port;


	MAC[0]	=	ReaderParam.MAC1;
	MAC[1]	=	ReaderParam.MAC2;
	MAC[2]	=	ReaderParam.MAC3;
	MAC[3]	=	ReaderParam.MAC4;
	MAC[4]	=	ReaderParam.MAC5;
	MAC[5]	=	ReaderParam.MAC6;
	str="";
	for(i=0;i<6;i++)
	{
		str_temp.Format("%02X",MAC[i]);
		str+=str_temp;
	}
	m_MAC=str;


	m_AutoMode=ReadeAutoParam.AutoMode;
	m_PersistenceTime=ReadeAutoParam.TimeH;
	m_PersistenceTime=(m_PersistenceTime<<8)+ReadeAutoParam.TimeL;
	m_PauseTimeofRead.SetCurSel(ReadeAutoParam.Interval);
	m_LenofList=ReadeAutoParam.NumH;
	m_LenofList=(m_LenofList<<8)+ReadeAutoParam.NumL;
	m_OutputManner=ReadeAutoParam.OutputManner;
	m_OutputPort=ReadeAutoParam.OutInterface;
	m_WiegandWidth=ReadeAutoParam.WiegandWidth;
	m_WiegandInterval=ReadeAutoParam.WiegandInterval; 
	m_IDStart=ReadeAutoParam.ID_Start;
	m_IDPosition=ReadeAutoParam.IDPosition;
	m_PauseTimeofReport=ReadeAutoParam.Report_Interval;
	m_ReportCondition=ReadeAutoParam.Report_Condition;
    m_ReportOutput=ReadeAutoParam.Report_Output & 0x01;
	m_Antenna1 = ReadeAutoParam.Antenna & 0x01;
	m_Antenna2 = (ReadeAutoParam.Antenna>>1) & 0x01;
	m_Antenna3 = (ReadeAutoParam.Antenna>>2) & 0x01;
	m_Antenna4 = (ReadeAutoParam.Antenna>>3) & 0x01;
	m_TriggerMode=ReadeAutoParam.TriggerMode;
	m_HostIPAddress.SetAddress(ReadeAutoParam.HostIP1,ReadeAutoParam.HostIP2,ReadeAutoParam.HostIP3,ReadeAutoParam.HostIP4);
	m_HostPort=(((int)ReadeAutoParam.Port1)<<8)+(int)ReadeAutoParam.Port2;
	m_ifTestAlarm=ReadeAutoParam.Alarm;
	m_EnableRelay=ReadeAutoParam.EnableRelay;
	
	nHostPort=m_HostPort;
	sprintf(nHostNetAddr, "%d.%d.%d.%d", ReadeAutoParam.HostIP1,ReadeAutoParam.HostIP2,ReadeAutoParam.HostIP3,ReadeAutoParam.HostIP4);


	//218为了提高读标签速度，不用切换天线，加一个命令，下面自动切换天线，编译   否则无，用宏控制,add by mqs 20130910
	#if defined (ENABLE218TXNOAntenna)
	{
		//天线睡眠时间	AnSleepTime;		//(29)//天线睡眠时间，单位：ms,(1-255)
		char chTtemp[11]={0};
		sprintf((char*)chTtemp, "%d", ReadeAutoParam.AnSleepTime);
		str = chTtemp;
		GetDlgItem(IDC_EDIT_AntSleepTime)->SetWindowText(str);
	}
	#else	
	
	#endif

	str.Empty(); 
	for(i=0;i<10;i++)
	{
		str+=ReaderID[i];
	}
	m_ReaderID=str;

	str.Format("%d.%d", bModuleVer[0], bModuleVer[1]);
	GetDlgItem(IDC_EDIT_ModuleVer)->SetWindowText(str);



	//add by mqs 20131118改自定义频率
	BYTE sel = 0;
	int imin = ReaderParam.Min_Frequence;
	int imax = ReaderParam.Max_Frequence;
	//sel=Fre-0;
	sel=FreT[0]-0;//626下标从0开始算
	
	{

		sel=FreT[0]-1;//218下标从1开始算
		
		OnCbnSetFrT(sel+1, -1, -1);
		//218的频
		CComboBox *m_MinFrequency = (CComboBox*)GetDlgItem(IDC_COMBO2);
		CComboBox *m_MaxFrequency = (CComboBox*)GetDlgItem(IDC_COMBO3);
		
		if ( 1 <= sel+1 && sel+1 <= 3)
		{
			imin	=	ReaderParam.Min_Frequence;
			imax	=	ReaderParam.Max_Frequence;
			
			if ( 1 == sel+1 ) //FCC
			{
				m_MinFrequency->SetCurSel(imin-7);
				m_MaxFrequency->SetCurSel(imax-7);
			}
			else if ( 2 == sel+1 )
			{
				m_MinFrequency->SetCurSel(imin);
				m_MaxFrequency->SetCurSel(imax);
			}
			else
			{
				m_MinFrequency->SetCurSel(imin-0x2B);
				m_MaxFrequency->SetCurSel(imax-0x2B);
			}
			
		}
		else if ( 4 == sel+1 )
		{
			
			//注意：FreT[0]为1,2,3时间国家，4-为自定义,FreT[1]/[2]为最小频点和最大频点,其它无用
			//FreT[0]为4自定义时,FreT[1], 频点间隔(FreT[1]*10KHz);FreT[2],频点数量
			//FreT[3..5], 开始频点,占3字节
			
			m_MinFrequency->SetCurSel(imin);
			m_MaxFrequency->SetCurSel(imax);

		}
	}



	UpdateData(FALSE);

	return TRUE;
}

void CReaderDParam::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	if (NewConnect==1)
	{
		
		//ReadParameter();
		ReadConnParameter();
		NewConnect=0;
	}
	UpdateStatus();
	
}

void CReaderDParam::OnButton2() 
{
	apiReturn res;
	BYTE IP_Address[4],Mask[4],Gateway[4],MAC[6];
	int i,Port;
	CString str;

	UpdateData(TRUE);

	if ((m_Port<1024) || (m_Port>65535))
	{
		//MessageBox("Please input Port between 1024 and 65535!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0195"),theApp.g_LoadString("IDWQC_C0196"),MB_ICONERROR);
		return;
	}

	if (strlen(m_MAC)<12)
	{
		//MessageBox("Please input unabridged MAC!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0197"),theApp.g_LoadString("IDWQC_C0198"),MB_ICONERROR);
		return;
	}
	str=m_MAC.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_MAC))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQC_C0199"),theApp.g_LoadString("IDWQC_C0200"),MB_ICONWARNING);
		GetDlgItem(IDC_EDIT5)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
		UpdateData(FALSE);
		return;
	}

	m_IPAddress.GetAddress(IP_Address[0],IP_Address[1],IP_Address[2],IP_Address[3]);
	m_Mask.GetAddress(Mask[0],Mask[1],Mask[2],Mask[3]);
	m_Gateway.GetAddress(Gateway[0],Gateway[1],Gateway[2],Gateway[3]);
	Port=m_Port;
	
	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_SetReaderNetwork(m_hSocket,IP_Address,Port,Mask,Gateway);
			break;
		case 1:
			res=SetReaderNetwork(m_hScanner,IP_Address,Port,Mask,Gateway,0);
			break;
		case 2:
			res=SetReaderNetwork(m_hScanner,IP_Address,Port,Mask,Gateway,RS485Address);
			break;
		}
		if (res==_OK)
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
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0201"))
		{
			//str="Set Network Parameter Fail!";
			str=theApp.g_LoadString("IDWQC_C0202");
		}
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0203"),MB_ICONERROR);
		return;
	}

	
	str=m_MAC;
	for(i=0;i<6;i++)
	{
		MAC[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_SetReaderMAC(m_hSocket,MAC);
			break;
		case 1:
			res=SetReaderMAC(m_hScanner,MAC,0);
			break;
		case 2:
			res=SetReaderMAC(m_hScanner,MAC,RS485Address);
			break;
		}
		if (res==_OK)
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
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0204"))
		{
			//str="Set MAC Fail!";
			str=theApp.g_LoadString("IDWQC_C0205");
		}
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0206"),MB_ICONERROR);
		return;
	}

	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_Reboot(m_hSocket);
			break;
		case 1:
			res=Reboot(m_hScanner,0);
			break;
		case 2:
			res=Reboot(m_hScanner,RS485Address);
			break;
		}
		if (res==_OK)
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

	if(res == _OK)
	{
		//MessageBox("Set Network Parameter Successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQC_C0207"),theApp.g_LoadString("IDWQC_C0208"),MB_ICONINFORMATION);
	}
	else
	{
		//MessageBox("Error of Reboot Reader!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0209"),theApp.g_LoadString("IDWQC_C0210"),MB_ICONERROR);
	}
}

void CReaderDParam::OnButton3() 
{
	int iTmpRS485Address	=	RS485Address;
	int i,j,k;
	int br[]={115200,57600,38400,19200,9600};
	COMMTIMEOUTS  cto;
	DCB dcb;
	//WORD m_HardVer,m_SoftVer;

	//k=MessageBox("Do you Determine to recover the factory parameter?","Notice",MB_OKCANCEL|MB_ICONWARNING);
	k=MessageBox(theApp.g_LoadString("IDWQC_C0211"),theApp.g_LoadString("IDWQC_C0212"),MB_OKCANCEL|MB_ICONWARNING);
	if (k!=1) 
		return;


	apiReturn res	=	_no_scanner,ret	=	0;
	CString str;

	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_ReadFactoryParameter(m_hSocket);
			break;
		case 1:
			res=ReadFactoryParameter(m_hScanner,0);
			break;
		case 2:
			res=ReadFactoryParameter(m_hScanner,RS485Address);
			break;
		}
		if (res==_OK)
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
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0213"))
		{
			//str="Error of Read Factory Parameter!";
			str=theApp.g_LoadString("IDWQC_C0214");
		}
		Sleep(200);
		//dlg->DestroyWindow();
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0215"),MB_ICONERROR);
		return;
	}

	if ( 2 == ConnectMode )
	{
		Sleep(ReadRS485SleepTime);
	}
	switch(ConnectMode)
	{
	case 0:
		for (i = 0; i < 3; i++)
		{
			res=Net_Reboot(m_hSocket);
			if (res==_OK)
			{
				break;
			}
			
		}
		
		if(res != _OK)
		{
			//dlg->DestroyWindow();
			//MessageBox("Error of Reboot Reader!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0216"), theApp.g_LoadString("IDWQC_C0217"), MB_ICONERROR);
			return;
		}

		
		for (i = 0; i < 3; i++)
		{
			res=Net_AutoMode(m_hSocket,0);
			if (res==_OK)
			{
				break;
			}
			

		}
		if(res != _OK)
		{
			//dlg->DestroyWindow();
			//MessageBox("Stop Auto Mode fail!","Error",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0218"),theApp.g_LoadString("IDWQC_C0219"),MB_ICONERROR);
			return;
		}

			
		break;
	case 1:
		iTmpRS485Address	=	0;
	case 2:
		for (i = 0; i < 3; i++)
		{
			res=Reboot(m_hScanner,iTmpRS485Address);
			if (res==_OK)
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
			//dlg->DestroyWindow();
			//MessageBox("Error of Reboot Reader!","Notice",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0220"),theApp.g_LoadString("IDWQC_C0221"),MB_ICONERROR);
			return;
		}

		if ( 2 == ConnectMode )
		{
			Sleep(1000);
		}
		for (i=0; i<5; i++)
		{
			Sleep(50);
			
			GetCommState(m_hScanner, &dcb);
			dcb.BaudRate = br[i];
			SetCommState(m_hScanner, &dcb);
		
			PurgeComm(m_hScanner, PURGE_TXCLEAR);	// flush transimition queue
			PurgeComm(m_hScanner, PURGE_RXCLEAR);	// flush receiveing queue
			
			for(j=0;j<3;j++)
			{
				//dlg->m_Progress.SetPos(75+i*2+j);
				Sleep(30);
				res=AutoMode(m_hScanner,0,iTmpRS485Address);
				if (res == _OK)
				{
					break;		
				}
			}
			if (res==_OK)
				break;
		}

		if (res!=_OK)
		{
			//dlg->DestroyWindow();
			//MessageBox("Error of Connect Reader!","Notice",MB_ICONERROR);
			MessageBox(theApp.g_LoadString("IDWQC_C0222"),theApp.g_LoadString("IDWQC_C0223"),MB_ICONERROR);
			return;
		}

		//dlg->m_Progress.SetPos(85);

		GetCommTimeouts(m_hScanner, &cto);
		cto.ReadIntervalTimeout = 500;
		cto.ReadTotalTimeoutMultiplier = 100 ;
		cto.ReadTotalTimeoutConstant = 2000 ;
		cto.WriteTotalTimeoutMultiplier = 100 ;
		cto.WriteTotalTimeoutConstant = 1000 ;
		SetCommTimeouts(m_hScanner, &cto);

		break;
	}

	//dlg->m_Progress.SetPos(90);
	Sleep(100);

	BOOL rec;
	rec=ReadParameter();
	if (rec!=TRUE)
	{
		//dlg->DestroyWindow();
		//MessageBox("Error of Read Reader Parameter!\nPlease Reboot Reader!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQC_C0224"),theApp.g_LoadString("IDWQC_C0225"),MB_ICONWARNING);
		return;
	}

	//dlg->m_Progress.SetPos(100);
	Sleep(200);
	//dlg->DestroyWindow();
	if(res == _OK)
	{
		//MessageBox("Success of Default Reader Parameter!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQC_C0226"),theApp.g_LoadString("IDWQC_C0227"),MB_ICONINFORMATION);
	}


}

void CReaderDParam::OnButton5() 
{
	apiReturn res;
	CString str;
	BYTE ReaderID[12];

	UpdateData(TRUE);

	if((m_ReaderID.GetLength()<=0)||(m_ReaderID.GetLength()>10))
	{
		//MessageBox("Please input ID of Reader!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0228"),theApp.g_LoadString("IDWQC_C0229"),MB_ICONERROR);
		return;
	}

	memset(ReaderID,0,12);
	memcpy(ReaderID,m_ReaderID.GetBuffer(0),m_ReaderID.GetLength()); 
	
	switch(ConnectMode)
	{
	case 0:
		res=Net_SetReaderID(m_hSocket,ReaderID);
		break;
	case 1:
		res=SetReaderID(m_hScanner,ReaderID,0);
		break;
	case 2:
		res=SetReaderID(m_hScanner,ReaderID,RS485Address);
		break;
	}

	if(res == _OK)
	{
		//MessageBox("Set ReaderID Successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQC_C0230"),theApp.g_LoadString("IDWQC_C0231"),MB_ICONINFORMATION);
	}
	else
	{
		//MessageBox("Error of Set ReaderID!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0232"),theApp.g_LoadString("IDWQC_C0233"),MB_ICONERROR);
	}
	
}

void CReaderDParam::OnButton8() 
{
	apiReturn res;
	CString str;
	ReaderDate time;
	CTime m_NowTime = CTime::GetCurrentTime();
	
	m_Info.ResetContent();

	time.Year=m_NowTime.GetYear()%100;
	time.Month=m_NowTime.GetMonth();
	time.Day=m_NowTime.GetDay();
	time.Hour=m_NowTime.GetHour();
	time.Minute=m_NowTime.GetMinute();
	time.Second=m_NowTime.GetSecond();

	switch(ConnectMode)
	{
	case 0:
		res=Net_SetReaderTime(m_hSocket,&time);
		break;
	case 1:
		res=SetReaderTime(m_hScanner,&time,0);
		break;
	case 2:
		res=SetReaderTime(m_hScanner,&time,RS485Address);	
		break;
	}

	if(res == _OK)
	{
		//m_Info.AddString("Set Time successfully!");
		m_Info.AddString(theApp.g_LoadString("IDWQC_C0234"));
	}
	else
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0235"))
		{
			//str="Set Time Fail!";
			str=theApp.g_LoadString("IDWQC_C0236");
		}
		m_Info.AddString(str);
	}
}

void CReaderDParam::OnButton9() 
{
	apiReturn res;
	CString str;
	ReaderDate time;

	m_Info.ResetContent();

	switch(ConnectMode)
	{
	case 0:
		res=Net_GetReaderTime(m_hSocket,&time);
		break;
	case 1:
		res=GetReaderTime(m_hScanner,&time,0);
		break;
	case 2:
		res=GetReaderTime(m_hScanner,&time,RS485Address);	
		break;
	}
	
	if(res == _OK)
	{
		str.Format("20%02d-%02d-%02d %02d:%02d:%02d",time.Year,time.Month,time.Day,time.Hour,time.Minute,time.Second);
		m_Info.AddString(str);
	}
	else
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0237"))
		{
			//str="Get Time Fail!";
			str=theApp.g_LoadString("IDWQC_C0238");
		}
		m_Info.AddString(str);
	}
}

void CReaderDParam::OnButton10() 
{
/*
	apiReturn res;
	CString str;
	BYTE state;
	
	m_Info.ResetContent();

	switch(ConnectMode)
	{
	case 0:
		res=Net_GetInputPin(m_hSocket,&state);
		break;
	case 1:
		res=GetInputPin(m_hScanner,&state);	
		break;
	}
	
	if(res == _OK)
	{
		for(int i=0;i<8;i++)
		{
			str="";
			str.Format("InputPin%i:",i+1);
			if ((state>>i) & 0x01)
			{
				str+="High";
			}
			else
			{
				str+="Low";
			}
			m_Info.AddString(str);
		}
	}
	else
	{
		str=ReportError(res);
		if (str=="Unbeknown Error!")
			str="Get InputPin Fail!";
		m_Info.AddString(str);
	}

  */
}

void CReaderDParam::OnButton11() 
{
	apiReturn res;
	CString str;
	int relay=0;

	UpdateData(TRUE);

	if (m_Relay1)
		relay += 1;
	if(m_Relay2)
		relay += 2;

	switch(ConnectMode)
	{
	case 0:
		res=Net_SetRelay(m_hSocket,relay);
		break;
	case 1:
		res=SetRelay(m_hScanner,relay,0);
		break;
	case 2:
		res=SetRelay(m_hScanner,relay,RS485Address);	
		break;
	}
    
	if(res == _OK)
	{
		//MessageBox("Set Relay successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQC_C0239"),theApp.g_LoadString("IDWQC_C0240"),MB_ICONINFORMATION);
	}
	else
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0241"))
		{
			//str="Set Relay Fail!";
			str=theApp.g_LoadString("IDWQC_C0242");
		}
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0243"),MB_ICONERROR);
	}
}

//得到模块版本
void CReaderDParam::OnButtonGetModuleVer() 
{
	apiReturn res	=	_no_scanner;
	
	CString strText;

	switch(ConnectMode)
	{
	case 0:
		res=Net_GetModuleVer(m_hSocket,bModuleVer);
		break;
	case 1:
		res=GetModuleVer(m_hScanner,bModuleVer,0);
		break;
	case 2:
		res=GetModuleVer(m_hScanner,bModuleVer,RS485Address);	
		break;
	}

	
	if (res!=_OK)
	{
		//MessageBox("Read Module Version Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0244"),theApp.g_LoadString("IDWQC_C0245"),MB_ICONERROR);
		return ;
	}

	strText.Format("%d.%d", bModuleVer[0], bModuleVer[1]);
	GetDlgItem(IDC_EDIT_ModuleVer)->SetWindowText(strText);

	return;
}

void CReaderDParam::OnButton12() 
{
	apiReturn res;
	CString str;
	int relay;

	switch(ConnectMode)
	{
	case 0:
		res=Net_GetRelay(m_hSocket,&relay);
		break;
	case 1:
		res=GetRelay(m_hScanner,&relay,0);	
		break;
	case 2:
		res=GetRelay(m_hScanner,&relay,RS485Address);
		break;
	}
    
	if (res!=_OK)
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0246"))
		{
			//str="Get Relay Fail!";
			str=theApp.g_LoadString("IDWQC_C0247");
		}
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0248"),MB_ICONERROR);
	}

	m_Relay1=relay & 0x01;
	m_Relay2=(relay>>1) & 0x01;


	UpdateData(FALSE);
}


void CReaderDParam::OnButton15() 
{
	apiReturn res;

	for(int i=0;i<5;i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_AutoMode(m_hSocket,0);
			break;
		case 1:
			res=AutoMode(m_hScanner,0,0);
			break;
		case 2:
			res=AutoMode(m_hScanner,0,RS485Address);	
			break;
		}
		if (res==_OK)
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
    
	if(res == _OK)
	{
		//MessageBox("Stop Auto Mode successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQC_C0249"),theApp.g_LoadString("IDWQC_C0250"),MB_ICONINFORMATION);
	}
	else
	{
		//MessageBox("Stop Auto Mode fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0251"),theApp.g_LoadString("IDWQC_C0252"),MB_ICONERROR);
	}
	
}

void CReaderDParam::OnButton4() 
{
	UpdateData(TRUE);

	apiReturn res;

	int i,m,str_len,filterLength=0;
	CString str;
	BYTE FilterMask[64]={0};

	if ((m_FilterAddress<0) || (m_FilterAddress>95))
	{
		//MessageBox("Please input Address of Tag EPC between 0 and 95 !","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0253"),theApp.g_LoadString("IDWQC_C0254"),MB_ICONERROR);
		return;
	}
	if ((m_FilterLength<0) || (m_FilterLength>96))
	{
		//MessageBox("Please input Address of Tag EPC between 0 and 96 !","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0255"),theApp.g_LoadString("IDWQC_C0256"),MB_ICONERROR);
		return;
	}

	str="";
	str=m_FilterMask.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_FilterMask))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQC_C0257"),theApp.g_LoadString("IDWQC_C0258"),MB_ICONWARNING);
		GetDlgItem(IDC_EDIT11)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT11))->SetSel(0,-1);
		UpdateData(FALSE);
		return;
	}

	str_len=strlen(m_FilterMask);
	str=m_FilterMask;

	if (m_FilterLength==0)
		m=0;
	else
	{
		m=m_FilterLength/8;
		if (m_FilterLength%8!=0)
		{
			for(i=0;i<((m+1)*2-str_len);i++)
				str+="0";
			m++;
		}
	}
	filterLength=m_FilterLength;


	for(i=0;i<m;i++)
	{
		FilterMask[i]=(BYTE)strtol(((CString)str[i*2]+(CString)str[i*2+1]),NULL,16);
	}

	if (m_FilterAddress+filterLength>96)
		filterLength=8-m_FilterAddress;

	if ( (int)filterLength < 0 )
	{
		filterLength = 0;
	}

	switch(ConnectMode)
	{
	case 0:
		res=Net_SetReportFilter(m_hSocket,m_FilterAddress,filterLength,FilterMask);
		break;
	case 1:
		res=SetReportFilter(m_hScanner,m_FilterAddress,filterLength,FilterMask,0);
		break;
	case 2:
		res=SetReportFilter(m_hScanner,m_FilterAddress,filterLength,FilterMask,RS485Address);
		break;
	}

	if (res!=_OK)
	{
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str==theApp.g_LoadString("IDWQC_C0259"))
		{
			//str="Error of Update Reader Auto Parameter!";
			str=theApp.g_LoadString("IDWQC_C0260");
		}
		//MessageBox(str,"Error",MB_ICONERROR);
		MessageBox(str,theApp.g_LoadString("IDWQC_C0261"),MB_ICONERROR);
		return;
	}
	
}

void CReaderDParam::OnButton6() 
{
	apiReturn res;

	int i,l,FilterAddress=0,FilterLength=0;;
	CString str,str_temp;
	BYTE FilterMask[64];

	for(i=0;i<3;i++)
	{		
		switch(ConnectMode)
		{
		case 0:
			res=Net_GetReportFilter(m_hSocket,&FilterAddress,&FilterLength,&FilterMask[0]);
			break;
		case 1:
			res=GetReportFilter(m_hScanner,&FilterAddress,&FilterLength,&FilterMask[0],0);
			break;
		case 2:
			res=GetReportFilter(m_hScanner,&FilterAddress,&FilterLength,&FilterMask[0],RS485Address);
			break;
		}
		if (res==_OK) break;
	}
	if (res!=_OK)
	{
		//MessageBox("Read ReportFilter Parameter Fail!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQC_C0262"),theApp.g_LoadString("IDWQC_C0263"),MB_ICONERROR);
		return ;
	}

  	m_FilterAddress=FilterAddress;
	m_FilterLength=FilterLength;

	if (FilterLength%8==0)
	{
		l=FilterLength/8;
	}
	else
	{
		l=FilterLength/8+1;
	}

	str="";
	for(i=0;i<l;i++)
	{
		str_temp.Format("%02X",FilterMask[i]);
		str+=str_temp;
	}
	m_FilterMask=str;

	UpdateData(FALSE);
	
}



void CReaderDParam::OnCheck1() 
{
	/*
	apiReturn res;
	int i;
	int FilterAddress=0,FilterLength=0;
	BYTE FilterMask[64];
	CString str,str_temp;

	UpdateData(TRUE);

	m_EPCC1G2=FALSE;
	m_ISO6B=TRUE;
	m_EM4442=FALSE;
	GetDlgItem(IDC_EM4442_STATIC1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EM4442_STATIC2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EM4442_STATIC3)->EnableWindow(FALSE);
//	GetDlgItem(IDC_COMBO6)->EnableWindow(FALSE);
//	GetDlgItem(IDC_COMBO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_ADDR)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_LEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EPC_STATIC)->EnableWindow(TRUE);
	GetDlgItem(IDC_EPCC1G2_STATIC)->EnableWindow(TRUE);
	UpdateData(FALSE);
	tagType=0x01;

	switch(m_HardVersion)
	{
	case 0x1A1F:
	case 0x1A20:
	case 0x1A22:
		UpdateStatus();
		UpdateData(TRUE);
		
		for(i=0;i<3;i++)
		{		
			switch(ConnectMode)
			{
			case 0:
				res=Net_GetReportFilter(m_hSocket,&FilterAddress,&FilterLength,&FilterMask[0]);
				break;
			case 1:
				res=GetReportFilter(m_hScanner,&FilterAddress,&FilterLength,&FilterMask[0],0);
				break;
			}
			if (res==_OK) break;
		}
		if (res!=_OK)
		{
			MessageBox("Read ReportFilter Parameter Fail!","Error",MB_ICONERROR);
			return;
		}
	}

	UpdateData(FALSE);
	*/
}

void CReaderDParam::OnCheck3() 
{
	/*
	apiReturn res;
	int i;
	int FilterAddress=0,FilterLength=0;
	BYTE FilterMask[64];
	CString str,str_temp;

	UpdateData(TRUE);
	m_ISO6B=FALSE;
	m_EPCC1G2=TRUE;
	m_EM4442=FALSE;
	GetDlgItem(IDC_EM4442_STATIC1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EM4442_STATIC2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EM4442_STATIC3)->EnableWindow(FALSE);
//	GetDlgItem(IDC_COMBO6)->EnableWindow(FALSE);
//	GetDlgItem(IDC_COMBO7)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_ADDR)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_LEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT11)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EPC_STATIC)->EnableWindow(TRUE);
	GetDlgItem(IDC_EPCC1G2_STATIC)->EnableWindow(TRUE);
	UpdateData(FALSE);
	tagType=0x04;
	
	switch(m_HardVersion)
	{
	case 0x1A1F:
	case 0x1A20:
	case 0x1A22:
	case 0x1A15:
	case 0x1A16:
	case 0x1A18:
		UpdateStatus();
		UpdateData(TRUE);

		for(i=0;i<3;i++)
		{		
			switch(ConnectMode)
			{
			case 0:
				res=Net_GetReportFilter(m_hSocket,&FilterAddress,&FilterLength,&FilterMask[0]);
				break;
			case 1:
				res=GetReportFilter(m_hScanner,&FilterAddress,&FilterLength,&FilterMask[0],0);
				break;
			}
			if (res==_OK) break;
		}
		if (res!=_OK)
		{
			MessageBox("Read ReportFilter Parameter Fail!","Error",MB_ICONERROR);
			return;
		}

	}

	UpdateData(FALSE);
	*/
}

void CReaderDParam::OnCheck4() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);
	m_ISO6B=FALSE;
	m_EPCC1G2=FALSE;
	m_EM4442=TRUE;
	GetDlgItem(IDC_STATIC_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_LEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EPC_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EPCC1G2_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EM4442_STATIC1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EM4442_STATIC2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EM4442_STATIC3)->EnableWindow(TRUE);
*/
//	GetDlgItem(IDC_COMBO6)->EnableWindow(TRUE);
//	GetDlgItem(IDC_COMBO7)->EnableWindow(TRUE);

//	UpdateData(FALSE);

/*	for(i=0;i<3;i++)
	{		
		switch(ConnectMode)
		{
		case 0:
			res=Net_SetTagType(m_hSocket,8);
			break;
		case 1:
			res=SetTagType(m_hScanner,8);
			break;
		}
		if (res==_OK) break;
	}
	if (res!=_OK)
	{
		MessageBox("Set TagType Fail!","Error",MB_ICONERROR);
		return;
	}
*/
//	UpdateData(FALSE);
}

//WM_READERPARMDATAMSG
afx_msg LRESULT CReaderDParam::OnReaderparmdatamsg(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;

	if ( 2 == iwParam )
	{
		OnInitUIText();	//更新语言
	}

	return 0;
}


