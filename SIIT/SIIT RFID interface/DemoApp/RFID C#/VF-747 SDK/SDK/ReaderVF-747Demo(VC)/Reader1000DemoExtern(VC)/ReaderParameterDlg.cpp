// ReaderParameterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "readerdemo.h"
#include "ReaderParameterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////�������涨ʱ��//////////////////////////////////////////
//���嶨ʱ����ID
//ʱ��
#define					TIME_IDENTIFIER_PARAM			(300)			//ʱ��ID��
#define					INTERVALTIME_PARAM				(1000)			//�೤ʱ��ִ��һ��
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
HWND	gReaderParamHwnd	=	NULL;	//��д������������


int StrtimetoDecimal(CString Command,BYTE *CmdBuffer)
{
	int hexlen=0,CmdLen=0,strlen;
	CString str="";
	BYTE buffer[240];
	
	strlen=Command.GetLength();
	
	str+=(CString)Command[0];
	str+=(CString)Command[1];
	buffer[0]=(BYTE)strtol(str,NULL,16);
	
	str="";
	str+=(CString)Command[2];
	str+=(CString)Command[3];
	buffer[1]=(BYTE)strtol(str,NULL,16);
	
	str="";
	str+=(CString)Command[4];
	str+=(CString)Command[5];
	buffer[2]=(BYTE)strtol(str,NULL,16);
	
	str="";
	str+=(CString)Command[6];
	str+=(CString)Command[7];
	buffer[3]=(BYTE)strtol(str,NULL,16);
	
	str="";
	str+=(CString)Command[8];
	str+=(CString)Command[9];
	buffer[4]=(BYTE)strtol(str,NULL,16);
	
	str="";
	str+=(CString)Command[10];
	str+=(CString)Command[11];
	buffer[5]=(BYTE)strtol(str,NULL,16);
	
	memcpy(CmdBuffer, buffer, 6);
	return 6;
}

/////////////////////////////////////////////////////////////////////////////
// CReaderParameterDlg property page

IMPLEMENT_DYNCREATE(CReaderParameterDlg, CPropertyPage)

CReaderParameterDlg::CReaderParameterDlg()	: CPropertyPage(CReaderParameterDlg::IDD)
{
	//{{AFX_DATA_INIT(CReaderParameterDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_IsAutocmd			=	-1;	//0-����,1-����,2-Command
	m_IsoChoose			=	-1;	//0-6B,1-6C
	m_OutputPortMode	=	-1;	//0-RS232,1-RS485,2-RJ45,3-Wiegand26,4-Wiegand34
	m_OutputFormata		=	-1;	//0-��,1-��׼
	m_TriggerModea		=	-1;	//0-�͵�ƽ��1-�ߵ�ƽ
	m_FromTaga			=	-1;	//0-��ǩ����ID��1-�û��Զ���
	m_Condiona			=	-1;	//0-����֪ͨ,1-��ʱ֪ͨ,2-�����±�ǩ,3-���ٱ�ǩ,4-��ǩ���仯
	m_OutputInteTimems	=	-1;	//0-10ms��1-20ms��2-30ms��3-50ms��4-100ms��ȱʡֵΪ2��ÿ���趨ʱ��������ȡһ�α�ǩ��
	m_AutoWorkMode		=	-1;	//0-��ʱ��1-����
	//}}AFX_DATA_INIT
}

CReaderParameterDlg::~CReaderParameterDlg()
{

}

void CReaderParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReaderParameterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Radio(pDX, IDC_RADIOA_Auto, m_IsAutocmd);
	DDX_Radio(pDX, IDC_RADIO1_6B, m_IsoChoose);
	DDX_Radio(pDX, IDC_RADIO1_RS232, m_OutputPortMode);
	DDX_Radio(pDX, IDC_RADIO2_Simplified, m_OutputFormata);
	DDX_Radio(pDX, IDC_RADIO3_LowLevel, m_TriggerModea);
	DDX_Radio(pDX, IDC_RADIO4_IDofTAG, m_FromTaga);
	DDX_Radio(pDX, IDC_RADIO7_Immediately, m_Condiona);
	DDX_Radio(pDX, IDC_RADIO6_10MS, m_OutputInteTimems);
	DDX_Radio(pDX, IDC_RADIOB_CONTINUING, m_AutoWorkMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReaderParameterDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CReaderParameterDlg)
	ON_BN_CLICKED(IDC_BUTTON_SETBASIC, OnButtonSetbasic)
	ON_BN_CLICKED(IDC_BUTTON_SETAUTO, OnButtonSetauto)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVEFACTORY, OnButtonActivefactory)
	ON_BN_CLICKED(IDC_BUTTON_READFILTER, OnButtonReadfilter)
	ON_BN_CLICKED(IDC_BUTTON_SETFILTER, OnButtonSetfilter)
	ON_BN_CLICKED(IDC_BUTTON_GETRELAY, OnButtonGetrelay)
	ON_BN_CLICKED(IDC_BUTTON_SETRELAY, OnButtonSetrelay)
	ON_BN_CLICKED(IDC_BUTTON1_READTIME, OnButton1Readtime)
	ON_BN_CLICKED(IDC_BUTTON1_SETTIME, OnButton1Settime)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_WORKAUTOSTART, OnButtonWorkautostart)
	ON_BN_CLICKED(IDC_BUTTON_WORKAUTOSTOP, OnButtonWorkautostop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_READERPARMDATAMSG, OnReaderparmdatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderParameterDlg message handlers
void CReaderParameterDlg::OnInitUIText()	//��������
{
	SetWindowText(theApp.g_LoadString("IDWQB_C0001"));//��������

	GetDlgItem(IDC_BUTTON_SETAUTO)->SetWindowText(theApp.g_LoadString("IDWQB_C0002"));//Update Auto Parameter
	GetDlgItem(IDC_RADIOA_Auto)->SetWindowText(theApp.g_LoadString("IDWQB_C0003"));//�Զ�ģʽ
	GetDlgItem(IDC_RADIOA_COMMANE)->SetWindowText(theApp.g_LoadString("IDWQB_C0004"));//����ģʽ

	GetDlgItem(IDC_STATIC_WORKMODEB)->SetWindowText(theApp.g_LoadString("IDWQB_C0071"));//auto workmode
	GetDlgItem(IDC_RADIOB_CONTINUING)->SetWindowText(theApp.g_LoadString("IDWQB_C0085"));//����
	GetDlgItem(IDC_RADIOB_TRIGGER)->SetWindowText(theApp.g_LoadString("IDWQB_C0086"));//����
	

	GetDlgItem(IDC_STATIC_READERID)->SetWindowText(theApp.g_LoadString("IDWQB_C0088"));//��д��ID:
	GetDlgItem(IDC_STATIC_SetBuzzer)->SetWindowText(theApp.g_LoadString("IDWQB_C0089"));//������
	GetDlgItem(IDC_STATIC_HOSTRelated)->SetWindowText(theApp.g_LoadString("IDWQB_C0090"));//֪ͨ������ַ����
	GetDlgItem(IDC_STATIC_DetAlarmA)->SetWindowText(theApp.g_LoadString("IDWQB_C0091"));//����

	GetDlgItem(IDC_CHECK_BUZZER)->SetWindowText(theApp.g_LoadString("IDWQB_C0005"));//Buzzer
	GetDlgItem(IDC_BUTTON_SETBASIC)->SetWindowText(theApp.g_LoadString("IDWQB_C0006"));//Update Basic Paramter
	GetDlgItem(IDC_CHECK_ANT1)->SetWindowText(theApp.g_LoadString("IDWQB_C0007"));//ANT1
	GetDlgItem(IDC_CHECK_ANT2)->SetWindowText(theApp.g_LoadString("IDWQB_C0008"));//ANT2
	GetDlgItem(IDC_CHECK_ANT3)->SetWindowText(theApp.g_LoadString("IDWQB_C0009"));//ANT3
	GetDlgItem(IDC_CHECK_ANT4)->SetWindowText(theApp.g_LoadString("IDWQB_C0010"));//ANT4
	GetDlgItem(IDC_CHECK_TESTALARM)->SetWindowText(theApp.g_LoadString("IDWQB_C0011"));//DetectAlarm
	GetDlgItem(IDC_CHECK_ENABLERELAY)->SetWindowText(theApp.g_LoadString("IDWQB_C0012"));//controlRelay
	GetDlgItem(IDC_CHECK_REPORTOUTPUT)->SetWindowText(theApp.g_LoadString("IDWQB_C0013"));//Inform host whether
	GetDlgItem(IDC_STATIC_RS232485BPS)->SetWindowText(theApp.g_LoadString("IDWQB_C0014"));//BaudRate of RS232/RS485 Port:
	GetDlgItem(IDC_STATIC_MINFrequency)->SetWindowText(theApp.g_LoadString("IDWQB_C0015"));//Min Frequency of Carrier(MHz)
	GetDlgItem(IDC_STATIC_MaxFrequency)->SetWindowText(theApp.g_LoadString("IDWQB_C0016"));//Max Frequency of Carrier(MHz)
	GetDlgItem(IDC_STATIC_RFPOWER)->SetWindowText(theApp.g_LoadString("IDWQB_C0017"));//RF Power Output(0-63)
	GetDlgItem(IDC_STATIC_RS485PORTA)->SetWindowText(theApp.g_LoadString("IDWQB_C0018"));//Address of Reader (1-254)
	GetDlgItem(IDC_STATIC_MAXTAGSREADING)->SetWindowText(theApp.g_LoadString("IDWQB_C0019"));//Max Tags of once Reading(1-100)
	GetDlgItem(IDC_STATIC_AutoParameter)->SetWindowText(theApp.g_LoadString("IDWQB_C0020"));//Parameters for Continuing and Trigger Mode
	GetDlgItem(IDC_STATIC_ADDRESSIPREADER)->SetWindowText(theApp.g_LoadString("IDWQB_C0021"));//Address of IP Reader
	GetDlgItem(IDC_STATIC_READERMASK)->SetWindowText(theApp.g_LoadString("IDWQB_C0022"));//Mask of Reader
	GetDlgItem(IDC_STATIC_READERGateway)->SetWindowText(theApp.g_LoadString("IDWQB_C0023"));//Gateway of Reader
	GetDlgItem(IDC_STATIC_READERMAC)->SetWindowText(theApp.g_LoadString("IDWQB_C0024"));//MAC of Reader
	GetDlgItem(IDC_STATIC_ReaderPort)->SetWindowText(theApp.g_LoadString("IDWQB_C0025"));//Port of Reader
	GetDlgItem(IDC_STATIC_Reserved)->SetWindowText(theApp.g_LoadString("IDWQB_C0026"));//Reserved
	GetDlgItem(IDC_STATIC_ReserveTime)->SetWindowText(theApp.g_LoadString("IDWQB_C0027"));//ReserveTime(s)
	GetDlgItem(IDC_STATIC_IntervalTime)->SetWindowText(theApp.g_LoadString("IDWQB_C0028"));//IntervalTime(s)
	GetDlgItem(IDC_STATIC_FilterAddr)->SetWindowText(theApp.g_LoadString("IDWQB_C0029"));//FilterAddr
	GetDlgItem(IDC_STATIC_FilterLen)->SetWindowText(theApp.g_LoadString("IDWQB_C0030"));//FilterLen
	GetDlgItem(IDC_STATIC_FilterMask)->SetWindowText(theApp.g_LoadString("IDWQB_C0031"));//FilterMask
	GetDlgItem(IDC_STATIC_HOSTIP)->SetWindowText(theApp.g_LoadString("IDWQB_C0032"));//Host IP
	GetDlgItem(IDC_STATIC_HostPort)->SetWindowText(theApp.g_LoadString("IDWQB_C0033"));//Host Port
	GetDlgItem(IDC_STATIC_WiegandWidth)->SetWindowText(theApp.g_LoadString("IDWQB_C0034"));//Pulse Width(*10us)
	GetDlgItem(IDC_STATIC_WiegandBetween)->SetWindowText(theApp.g_LoadString("IDWQB_C0035"));//Pulse Interval(*10us)
	GetDlgItem(IDC_STATIC_IDStartAddr)->SetWindowText(theApp.g_LoadString("IDWQB_C0036"));//Start Address of ID:
	GetDlgItem(IDC_BUTTON_READFILTER)->SetWindowText(theApp.g_LoadString("IDWQB_C0037"));//GetFilter
	GetDlgItem(IDC_BUTTON_SETFILTER)->SetWindowText(theApp.g_LoadString("IDWQB_C0038"));//SetFilter
	GetDlgItem(IDC_BUTTON_ACTIVEFACTORY)->SetWindowText(theApp.g_LoadString("IDWQB_C0039"));//Restore to factory default parameters
	GetDlgItem(IDC_RADIO1_6B)->SetWindowText(theApp.g_LoadString("IDWQB_C0040"));//ISO18000-6B
	//GetDlgItem(IDC_CHECK_C1)->SetWindowText(theApp.g_LoadString("IDWQB_C0041"));//EPCC1
	GetDlgItem(IDC_RADIO1_6C)->SetWindowText(theApp.g_LoadString("IDWQB_C0042"));//ISO18000-6C
	//GetDlgItem(IDC_CHECK_6D)->SetWindowText(theApp.g_LoadString("IDWQB_C0043"));//ISO18000-6D
	GetDlgItem(IDC_STATIC_CARDREADDURATION)->SetWindowText(theApp.g_LoadString("IDWQB_C0044"));//Card read duration(ms)
	GetDlgItem(IDC_STATIC_CMDEXECTIMES)->SetWindowText(theApp.g_LoadString("IDWQB_C0045"));//Command execution times
	GetDlgItem(IDC_BUTTON_GETRELAY)->SetWindowText(theApp.g_LoadString("IDWQB_C0046"));//GetRelayStat
	GetDlgItem(IDC_BUTTON_SETRELAY)->SetWindowText(theApp.g_LoadString("IDWQB_C0047"));//SetRelayStat
	GetDlgItem(IDC_CHECK_RELAY)->SetWindowText(theApp.g_LoadString("IDWQB_C0048"));//Relay1
	GetDlgItem(IDC_CHECK_RELAY1)->SetWindowText(theApp.g_LoadString("IDWQB_C0049"));//Relay2
	GetDlgItem(IDC_STATIC_BASICWORDPRARM)->SetWindowText(theApp.g_LoadString("IDWQB_C0050"));//Basic Parameter
	GetDlgItem(IDC_STATIC_HardVer)->SetWindowText(theApp.g_LoadString("IDWQB_C0051"));//HardVersion:
	GetDlgItem(IDC_STATIC_SoftVer)->SetWindowText(theApp.g_LoadString("IDWQB_C0052"));//SoftVersion:
	GetDlgItem(IDC_STATIC_WorkModeA)->SetWindowText(theApp.g_LoadString("IDWQB_C0053"));//Work Mode
	GetDlgItem(IDC_STATIC_ReadFromWhickAnt)->SetWindowText(theApp.g_LoadString("IDWQB_C0054"));//Read from which Antenna
	GetDlgItem(IDC_STATIC_WiegandPortF)->SetWindowText(theApp.g_LoadString("IDWQB_C0055"));//Wiegand Port Format
	GetDlgItem(IDC_STATIC_PortAndFOutput)->SetWindowText(theApp.g_LoadString("IDWQB_C0056"));//Port for Output
	GetDlgItem(IDC_RADIO1_RS232)->SetWindowText(theApp.g_LoadString("IDWQB_C0057"));//RS232
	GetDlgItem(IDC_RADIO1_RS485)->SetWindowText(theApp.g_LoadString("IDWQB_C0058"));//RS485
	GetDlgItem(IDC_RADIO1_RJ45)->SetWindowText(theApp.g_LoadString("IDWQB_C0059"));//RJ45
	GetDlgItem(IDC_RADIO1_Wiegand26)->SetWindowText(theApp.g_LoadString("IDWQB_C0060"));//Wiegand26
	GetDlgItem(IDC_RADIO1_Wiegand34)->SetWindowText(theApp.g_LoadString("IDWQB_C0061"));//Wiegand34
	GetDlgItem(IDC_STATIC_PortofOutputA)->SetWindowText(theApp.g_LoadString("IDWQB_C0062"));//Format for Output
	GetDlgItem(IDC_RADIO2_Simplified)->SetWindowText(theApp.g_LoadString("IDWQB_C0063"));//Simplified
	GetDlgItem(IDC_RADIO2_Standard)->SetWindowText(theApp.g_LoadString("IDWQB_C0064"));//Standard
	GetDlgItem(IDC_STATIC_TriggerModeA)->SetWindowText(theApp.g_LoadString("IDWQB_C0065"));//Trigger Mode
	GetDlgItem(IDC_RADIO3_LowLevel)->SetWindowText(theApp.g_LoadString("IDWQB_C0066"));//Low Level
	GetDlgItem(IDC_RADIO3_HightLevel)->SetWindowText(theApp.g_LoadString("IDWQB_C0067"));//High Level
	GetDlgItem(IDC_STATIC_WhatBeReadTag)->SetWindowText(theApp.g_LoadString("IDWQB_C0068"));//What be read from tag
	GetDlgItem(IDC_RADIO4_IDofTAG)->SetWindowText(theApp.g_LoadString("IDWQB_C0069"));//ID of the Tag
	GetDlgItem(IDC_RADIO4_SNSelByUser)->SetWindowText(theApp.g_LoadString("IDWQB_C0070"));//SN Selected by User
	
	GetDlgItem(IDC_STATIC_Timing)->SetWindowText(theApp.g_LoadString("IDWQB_C0074"));//Timing Interval(ms)
	GetDlgItem(IDC_STATIC_CondionA)->SetWindowText(theApp.g_LoadString("IDWQB_C0075"));//Condion
	GetDlgItem(IDC_RADIO7_Immediately)->SetWindowText(theApp.g_LoadString("IDWQB_C0076"));//Immediately notify the
	GetDlgItem(IDC_RADIO7_Timingnotice)->SetWindowText(theApp.g_LoadString("IDWQB_C0077"));//Timing notice
	GetDlgItem(IDC_RADIO7_Addnewlabels)->SetWindowText(theApp.g_LoadString("IDWQB_C0078"));//Add new labels
	GetDlgItem(IDC_RADIO7_Reducelabel)->SetWindowText(theApp.g_LoadString("IDWQB_C0079"));//Reduce label
	GetDlgItem(IDC_RADIO7_Changesinthenumberoflabels)->SetWindowText(theApp.g_LoadString("IDWQB_C0080"));//Changes in the number of labels

	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(theApp.g_LoadString("IDWQB_C0095"));//��д��ʱ��
	GetDlgItem(IDC_BUTTON1_READTIME)->SetWindowText(theApp.g_LoadString("IDWQB_C0096"));//��ȡʱ��
	GetDlgItem(IDC_BUTTON1_SETTIME)->SetWindowText(theApp.g_LoadString("IDWQB_C0097"));//����ʱ��

	GetDlgItem(IDC_BUTTON_WORKAUTOSTART)->SetWindowText(theApp.g_LoadString("IDWQB_C0119"));//�����Զ�����
	GetDlgItem(IDC_BUTTON_WORKAUTOSTOP)->SetWindowText(theApp.g_LoadString("IDWQB_C0120"));//ֹͣ�Զ�����

	if ( theApp.iantennaIndex == 0 )
	{
		GetDlgItem(IDC_RADIO7_Immediately)->SetWindowText(theApp.g_LoadString("IDWQB_C0092"));//Immediately notify the
		GetDlgItem(IDC_RADIO7_Timingnotice)->SetWindowText(theApp.g_LoadString("IDWQB_C0093"));//Timing notice
		GetDlgItem(IDC_RADIO7_Addnewlabels)->SetWindowText(theApp.g_LoadString("IDWQB_C0094"));//Add new labels

		//һ�ڲ�Ҫ������ʱ������
		GetDlgItem(IDC_STATIC_ReserveTime)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PERTIME)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_STATIC_Reserved)->SetWindowText(theApp.g_LoadString("IDWQB_C0116"));//Reserved
		GetDlgItem(IDC_STATIC_ReserveTime)->SetWindowText(theApp.g_LoadString("IDWQB_C0117"));//ReserveTime(s)
		GetDlgItem(IDC_STATIC_IntervalTime)->SetWindowText(theApp.g_LoadString("IDWQB_C0118"));//IntervalTime(s)

	}
	else
	{
		//�Ŀڰ�Ҫ������ʱ������
		GetDlgItem(IDC_STATIC_ReserveTime)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PERTIME)->ShowWindow(SW_SHOW);

	}

	GetDlgItem(IDC_STATIC_SETRELAYA)->SetWindowText(theApp.g_LoadString("IDWQB_C0081"));//Set Relay
	GetDlgItem(IDC_STATIC_SETFILTERA)->SetWindowText(theApp.g_LoadString("IDWQB_C0082"));//Set Filter
	GetDlgItem(IDC_STATIC_IPReaderParam)->SetWindowText(theApp.g_LoadString("IDWQB_C0083"));//IP Paramters of Reader
	GetDlgItem(IDC_STATIC_ISO)->SetWindowText(theApp.g_LoadString("IDWQB_C0084"));//����ȡ��ǩ����
	


	#if defined (ENABLEBPA9PROCTOL)//BPAЭ����������ַ������ǰ����ǩ��ռ��
	GetDlgItem(IDC_STATIC_RS485PORTA)->SetWindowText(theApp.g_LoadString("IDWQB_C0121"));//Address of Reader (1-254)
	GetDlgItem(IDC_STATIC_MAXTAGSREADING)->SetWindowText(theApp.g_LoadString("IDWQB_C0122"));//Max Tags of once Reading(1-100)
	#endif

}

//////////////////////////////////////////////////////////////////////////
//��;:		��ģ�����Ϣ��̬��Ա����,�ص�����
//������:	CallBack_MyTimeParam
//����:		
//�������:	hWnd--handle of CWnd that called SetTimer
//			nMsg--WM_TIMER
//			nIDEvent--timer identification
//			dwTime--system time 
//�������:	��
//����ֵ:	��
//��ע:TIME_IDENTIFIER_PARAM, INTERVALTIME_PARAM
//////////////////////////////////////////////////////////////////////////
void WINAPI CReaderParameterDlg::CallBack_MyTimeParam(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime)
{
	//Debug_Printf("r:%s\r\n","hello");
	if ( TIME_IDENTIFIER_PARAM == nIDEvent )
	{
		::PostMessage(gReaderParamHwnd, WM_READERPARMDATAMSG, 0, 0);
	}
}

BOOL CReaderParameterDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	gReaderParamHwnd	=	this->GetSafeHwnd();

	GetDlgItem(IDC_STATIC_CMDEXECTIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_READTIMES)->ShowWindow(SW_HIDE);
	
	//CMenu menuPopup;
	//menuPopup.AppendMenu( MF_STRING, 101, _T("�˳�"));

	//bps
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->AddString("9600");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->AddString("19200");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->AddString("38400");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->AddString("57600");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->AddString("115200");
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->SetCurSel(4);
	
	//�����ĳ���ʱ��
	((CComboBox*)GetDlgItem(IDC_COMBO_READDUR))->AddString("10ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READDUR))->AddString("20ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READDUR))->AddString("30ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READDUR))->AddString("40ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READDUR))->SetCurSel(0);
	
	
	//������ʽ,0-��ʱ��ʽ;1-������ʽ;
	//((CComboBox*)GetDlgItem(IDC_COMBO_AUTOWORDMOD))->AddString("0-Timer Mode");
	//((CComboBox*)GetDlgItem(IDC_COMBO_AUTOWORDMOD))->AddString("1-Trigger Mode");
	//((CComboBox*)GetDlgItem(IDC_COMBO_AUTOWORDMOD))->SetCurSel(0);
	
	//��ʱ���,0-10ms;1-20ms;2-30ms;3-50ms;4-100ms;
	//((CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL))->AddString("10ms");
	//((CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL))->AddString("20ms");
	//((CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL))->AddString("30ms");
	//((CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL))->AddString("40ms");
	//((CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL))->AddString("100ms");
	//((CComboBox*)GetDlgItem(IDC_COMBO_INTERVAL))->SetCurSel(0);
	
	//֪ͨ����,0-����֪ͨ;1-��ʱ֪ͨ;2-�����±�ǩ;3-���ٱ�ǩ;4-��ǩ���仯;
	//((CComboBox*)GetDlgItem(IDC_COMBO_CONDITION))->AddString("0-Immediately notify the");
	//((CComboBox*)GetDlgItem(IDC_COMBO_CONDITION))->AddString("1-Timing notice");
	//((CComboBox*)GetDlgItem(IDC_COMBO_CONDITION))->AddString("2-Add new labels");
	//((CComboBox*)GetDlgItem(IDC_COMBO_CONDITION))->AddString("3-Reduce label");
	//((CComboBox*)GetDlgItem(IDC_COMBO_CONDITION))->AddString("4-Changes in the number of labels");
	//((CComboBox*)GetDlgItem(IDC_COMBO_CONDITION))->SetCurSel(0);
	
	//�����ʽ��0-�򻯸�ʽ;1-��׼��ʽ;2-XML��ʽ;
	//((CComboBox*)GetDlgItem(IDC_COMBO_FORMATOUTPUT))->AddString("0-Simplified Format");
	//((CComboBox*)GetDlgItem(IDC_COMBO_FORMATOUTPUT))->AddString("1-Standard Format");
	//((CComboBox*)GetDlgItem(IDC_COMBO_FORMATOUTPUT))->AddString("2-XML Format");
	//((CComboBox*)GetDlgItem(IDC_COMBO_FORMATOUTPUT))->SetCurSel(0);
	
	//����˿�	0-RS232;1-RS485;2-RJ45;3-Wiegand26;4-Wiegand34;
	//((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUTPORT))->AddString("0-RS232");
	//((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUTPORT))->AddString("1-RS485");
	//((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUTPORT))->AddString("2-RJ45");
	//((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUTPORT))->AddString("3-Wiegand26");
	//((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUTPORT))->AddString("4-Wiegand34");
	//((CComboBox*)GetDlgItem(IDC_COMBO_OUTPUTPORT))->SetCurSel(0);
	
	//����ģʽ �͵�ƽ;�ߵ�ƽ;
	//((CComboBox*)GetDlgItem(IDC_COMBO_TRIGMODE))->AddString("�͵�ƽ");
	//((CComboBox*)GetDlgItem(IDC_COMBO_TRIGMODE))->AddString("�ߵ�ƽ");
	//((CComboBox*)GetDlgItem(IDC_COMBO_TRIGMODE))->SetCurSel(0);
	
	
	//��������	0-��ǩ����ID;1-�û��Զ���;
	//((CComboBox*)GetDlgItem(IDC_COMBO_IDPOS))->AddString("0-��ǩ����ID");
	//((CComboBox*)GetDlgItem(IDC_COMBO_IDPOS))->AddString("1-�û��Զ���");
	//((CComboBox*)GetDlgItem(IDC_COMBO_IDPOS))->SetCurSel(0);
	


	::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,0,0);	//time

	//����ҳ
	::SendMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,2,0);	//convert language

	//����ʱ��
	::SetTimer(gReaderParamHwnd,TIME_IDENTIFIER_PARAM, INTERVALTIME_PARAM, CallBack_MyTimeParam);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReaderParameterDlg::UpdateStatus()
{

	//���������Ĺ���ģʽ
	GetDlgItem(IDC_RADIOA_Auto)->EnableWindow(ifConnectReader);//�Զ�ģʽ
	GetDlgItem(IDC_RADIOA_COMMANE)->EnableWindow(ifConnectReader);//����ģʽ


	//����������ť
	GetDlgItem(IDC_BUTTON_SETBASIC)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_COMBO_BAUDRATE)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_COMBO_MAINFREQ)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_COMBO_MAXFREQ)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_POWER)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_RS485ADDR)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_NUMOFCARD)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_READTIMES)->EnableWindow(ifConnectReader);
	
	//������
	GetDlgItem(IDC_CHECK_BUZZER)->EnableWindow(ifConnectReader);

	//6B,6C
	GetDlgItem(IDC_RADIO1_6B)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO1_6C)->EnableWindow(ifConnectReader);
	
	GetDlgItem(IDC_COMBO_READDUR)->EnableWindow(ifConnectReader);
	
	GetDlgItem(IDC_IPADDRESS_READERIP)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_READPORT)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_IPADDRESS_READERMASK)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_IPADDRESS_READERGW)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDITREADERMAC)->EnableWindow(ifConnectReader);
	

	
	//�������
	//GetDlgItem(IDC_STATIC_BASICWORDPRARM)->EnableWindow(FALSE);


	//�Զ����
	//����
	GetDlgItem(IDC_CHECK_ANT1)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK_ANT2)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK_ANT3)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK_ANT4)->EnableWindow(ifConnectReader);

	//����˿�
	GetDlgItem(IDC_RADIO1_RS232)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO1_RS485)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO1_RJ45)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO1_Wiegand26)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO1_Wiegand34)->EnableWindow(ifConnectReader);


	//���������ʼ��ַ
	GetDlgItem(IDC_EDIT_IDSART)->EnableWindow(ifConnectReader);

	//wiegand
	GetDlgItem(IDC_EDIT_WIEGANDWIDTH)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_WIEGANDINTERVALl)->EnableWindow(ifConnectReader);

	//����ĸ�ʽ
	GetDlgItem(IDC_RADIO2_Simplified)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO2_Standard)->EnableWindow(ifConnectReader);

	//������ģʽ
	GetDlgItem(IDC_RADIO3_LowLevel)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO3_HightLevel)->EnableWindow(ifConnectReader);


	//form to tag
	GetDlgItem(IDC_RADIO4_IDofTAG)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO4_SNSelByUser)->EnableWindow(ifConnectReader);
	
	
	//�Զ�����ģʽ
	GetDlgItem(IDC_RADIOB_CONTINUING)->EnableWindow(ifConnectReader);//����
	GetDlgItem(IDC_RADIOB_TRIGGER)->EnableWindow(ifConnectReader);//����

	GetDlgItem(IDC_IPADDRESS_HOSTIP)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_HOSTPORT)->EnableWindow(ifConnectReader);

	GetDlgItem(IDC_EDIT_LENOFLIST)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_REPORTINTERVAL)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK_REPORTOUTPUT)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_PERTIME)->EnableWindow(ifConnectReader);



	GetDlgItem(IDC_RADIO6_10MS)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO6_20MS)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO6_30MS)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO6_50MS)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO6_100MS)->EnableWindow(ifConnectReader);
	


	GetDlgItem(IDC_CHECK_TESTALARM)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK_ENABLERELAY)->EnableWindow(ifConnectReader);
	


	//����
	GetDlgItem(IDC_RADIO7_Immediately)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO7_Timingnotice)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO7_Addnewlabels)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO7_Reducelabel)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_RADIO7_Changesinthenumberoflabels)->EnableWindow(ifConnectReader);


	//�̵���
	GetDlgItem(IDC_CHECK_RELAY)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_CHECK_RELAY1)->EnableWindow(ifConnectReader);


	//������
	GetDlgItem(IDC_EDIT_FILTERADD)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_FILTERLEN)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_EDIT_FILTERMASK)->EnableWindow(ifConnectReader);
	

	//�Զ���������
	GetDlgItem(IDC_BUTTON_SETAUTO)->EnableWindow(ifConnectReader);

	
	//������
	GetDlgItem(IDC_BUTTON_READFILTER)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(ifConnectReader);
	
	
	//�̵���
	GetDlgItem(IDC_BUTTON_GETRELAY)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON_SETRELAY)->EnableWindow(ifConnectReader);


	//�ָ���������
	GetDlgItem(IDC_BUTTON_ACTIVEFACTORY)->EnableWindow(ifConnectReader);
		

	//��ȡ������ʱ��
	GetDlgItem(IDC_BUTTON1_READTIME)->EnableWindow(ifConnectReader);
	GetDlgItem(IDC_BUTTON1_SETTIME)->EnableWindow(ifConnectReader);



	GetDlgItem(IDC_BUTTON_WORKAUTOSTART)->EnableWindow(ifConnectReader);//�����Զ�����
	GetDlgItem(IDC_BUTTON_WORKAUTOSTOP)->EnableWindow(ifConnectReader);//ֹͣ�Զ�����


	//add by martrin ����ʱ�䲻Ҫ
	GetDlgItem(IDC_COMBO_READDUR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CARDREADDURATION)->ShowWindow(SW_HIDE);

}

BOOL CReaderParameterDlg::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CString strText;
	
	if ( ifConnectReader )
	{
		//�����˵�
		//������������
		OnReadParameter(0);
		
		//�Զ���������
		OnReadParameter(1);
		

		
// 		GetDlgItem(IDC_BUTTON_SETBASIC)->EnableWindow(TRUE);
// 		
// 		GetDlgItem(IDC_BUTTON_READFILTER)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_BUTTON_SETFILTER)->EnableWindow(TRUE);
// 		
// 		
// 		GetDlgItem(IDC_BUTTON_SETAUTO)->EnableWindow(TRUE);
// 		
// 		GetDlgItem(IDC_BUTTON_GETRELAY)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_BUTTON_SETRELAY)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_BUTTON_ACTIVEFACTORY)->EnableWindow(TRUE);

	}
	else
	{
		
		
	}	

	if ( theApp.iantennaIndex == 0 )
	{
		//һ������,����������Ҫ
		GetDlgItem(IDC_CHECK_ANT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ANT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ANT4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RADIO7_Reducelabel)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO7_Changesinthenumberoflabels)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_RELAY1)->ShowWindow(SW_HIDE);
		
	}
	else
	{
		//�ĸ�����,��������Ҫ
		GetDlgItem(IDC_CHECK_ANT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_ANT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_ANT4)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RADIO7_Reducelabel)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO7_Changesinthenumberoflabels)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK_RELAY1)->ShowWindow(SW_SHOW);

	}

	UpdateStatus();

	::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,2,0);	//convert language
	return CPropertyPage::OnSetActive();
}


//selΪ����Ƶ���±�,iminΪ��СƵ���±�,imaxΪ���Ƶ���±�, -1Ϊ��СΪ��С�����Ϊ���
void CReaderParameterDlg::OnCbnSetFre(int sel, int imin, int imax)
{
	int i = 0;
	int k = 0;
	int iCount = 0;
	long iValue = 0;
	CString strFreqTmp;
	tagReaderFreq tmpFreq;

	CComboBox *m_MinFrequency	=	(CComboBox*)GetDlgItem(IDC_COMBO_MAINFREQ);
	CComboBox *m_MaxFrequency	=	(CComboBox*)GetDlgItem(IDC_COMBO_MAXFREQ);
	
	//Ƶ�ʼ��㹫ʽ
	//���� = 50;
	//���� = 500KHz;
	//��ʼƵ�� = 902750;
	//902750 + ����*����;
	m_MinFrequency->ResetContent();
	m_MaxFrequency->ResetContent();
	switch(sel)
	{
	case 0://{"0---FCC��������", 50, 500, 902750},								//(0)
	case 1://{"1---ETSI EN 300-220��ŷ��300-220��", -1, -1, -1},				//(1)
	case 2://{"2---ETSI EN 302-208��ŷ��302-208��", 4, 600, 865700},			//(2)
	case 3://"3---HK920-925���", 10, 500, 920250},							//(3)
	case 4://{"4---TaiWan 922-928̨��", 12, 500, 922250},						//(4)
	case 5://{"5---Japan 952-954�ձ�", 0, 0, 0},								//(5)
	case 6://{"6---Japan 952-955�ձ�", 14,200, 952200},						//(6)
	case 7://{"7---ETSI EN 302-208ŷ��", 4, 600, 865700},						//(7)
	case 8://{"8---Korea 917-921����", 6, 600, 917300},						//(8)
	case 9://{"9---Malaysia 919-923��������", 8, 500, 919250},					//(9)
	case 10://{"10--China 920-925�й�", 16, 250, 920625},						//(10)
	case 11://{"11--Japan 952-956�ձ�", 4, 1200, 952400},						//(11)
	case 12://{"12--South Africa 915-919����", 17, 200, 915600},				//(12)
	case 13://{"13--Brazil 902-907/915-928����", 35, 500, 902750},				//(13)
	case 14://{"14--Thailand 920-925̩��", -1, -1, -1},						//(14)
	case 15://{"15--Singapore 920-925�¼���", 10, 500, 920250},				//(15)
	case 16://{"16--Australia 920-926����", 12, 500, 920250},					//(16)
	case 17://{"17--India 865-867ӡ��", 4, 600, 865100},						//(17)
	case 18://{"18--Uruguay 916-928������", 23, 500, 916250},					//(18)
	case 19://{"19--Vietnam 920-925Խ��", 10, 500, 920250},					//(19)
	case 20://{"20--Israel 915-917", 1, 0, 916250},							//(20)
	case 21://{"21--Philippines 918-920���ɱ�", 4, 500, 918250},				//(21)
	case 22://{"22--Canada 902-928���ô�", 42, 500, 902750},					//(22)
	case 23://{"23--Indonesia 923-925ӡ��������", 4, 500, 923250},				//(23)
	case 24://{"24--New Zealand 921.5-928������", 11, 500, 922250},			//(24)
		tmpFreq.iGrade	=	stuctFreqCountry[sel].iGrade;
		tmpFreq.iSkip	=	stuctFreqCountry[sel].iSkip;
		tmpFreq.dwFreq	=	stuctFreqCountry[sel].dwFreq;
		k = 0;
		iCount	=	tmpFreq.iGrade;
		
		if ( 22 == sel )
		{
			int iArray[3] = {902750, 903250, 905750};
			//���ô������
			for (i = 0; i < 3; i++)
			{
				strFreqTmp.Format("%02d--%d", i+1, iArray[i]);
				m_MinFrequency->AddString(strFreqTmp);
				m_MaxFrequency->AddString(strFreqTmp);
			}
			tmpFreq.dwFreq	=	iArray[i-1];
			iCount			=	tmpFreq.iGrade - 3;
			k = 3;
		}
		
		for (i = k; i < iCount + k; i++)
		{
			iValue	=	tmpFreq.dwFreq + i * tmpFreq.iSkip;
			strFreqTmp.Format("%02d--%d", i+1, iValue);
			m_MinFrequency->AddString(strFreqTmp);
			m_MaxFrequency->AddString(strFreqTmp);
		}
		
		iCount	=	tmpFreq.iGrade;
		if ( i > 0 )
		{
			if ( imin == -1 && imax == -1 )
			{
				m_MinFrequency->SetCurSel(0); 
				m_MaxFrequency->SetCurSel(iCount - 1); 
			}
			else
			{
				m_MinFrequency->SetCurSel(imin); 
				m_MaxFrequency->SetCurSel(imax); 
			}
		}
		
		break;
		
		
	default:;
	}
	
}



BOOL CReaderParameterDlg::OnReadParameter(int iOpt)	//iOpt,0--����������1--�Զ�����
{
	CString strText;
	int iBasicValue	=	0;
	int iAutoValue	=	0;

	UpdateData(TRUE);
	if ( 0 == iOpt )
	{
		
		//������������
		strText.Format("%04x", m_HardVersion);
		GetDlgItem(IDC_EDIT_HardVer)->SetWindowText(strText);
		strText.Format("%04x", m_SoftVersion);
		GetDlgItem(IDC_EDIT_SoftVer)->SetWindowText(strText);


		#if defined (ENABLETXVERCHANGE)
		GetDlgItem(IDC_EDIT_HardVer)->SetWindowText(_T("1000"));
		GetDlgItem(IDC_EDIT_SoftVer)->SetWindowText(_T("1000"));
		#endif


		//bps
		((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->SetCurSel(gBasicParam->BaudRate-4);
		//��СƵ��
		//���Ƶ��
		BYTE imin	=	gBasicParam->Min_Frequence-1;
		BYTE imax	=	gBasicParam->Max_Frequence-1;
		OnCbnSetFre(gFre, imin, imax);//��Ϊͨ����������ÿ�����ҵ�Ƶ����Щ��һ����
		
		//RF power
		strText.Format("%d", gBasicParam->Power);
		GetDlgItem(IDC_EDIT_POWER)->SetWindowText(strText);
		
		//Address of Reader (1-254)
		strText.Format("%d", gBasicParam->ReaderAddress);
		GetDlgItem(IDC_EDIT_RS485ADDR)->SetWindowText(strText);
		
		
		//Max Tags of once Reading(1-100)
		strText.Format("%d", gBasicParam->NumofCard);
		GetDlgItem(IDC_EDIT_NUMOFCARD)->SetWindowText(strText);
		
		//û���õ��������ݲ�Ҫ
		//Modulation Depth(0-100)
		//strText.Format("%d", gBasicParam->Reserve5);
		
		
		
		//Command execution times
		strText.Format("%d", gBasicParam->ReadTimes);
		GetDlgItem(IDC_EDIT_READTIMES)->SetWindowText(strText);
		
		
		//����ģʽ
		m_IsAutocmd	=	gBasicParam->WorkMode;//0-�Զ�,1-Command

		//��д��ID
		strText.Format("%s", gReaderID);
		GetDlgItem(IDC_EDIT_READERID)->SetWindowText(strText);
		#if defined (ENABLETXVERCHANGE)
		GetDlgItem(IDC_EDIT_READERID)->SetWindowText(_T("��д��1000"));
		#endif

		//buzzer
		((CButton*)GetDlgItem(IDC_CHECK_BUZZER))->SetCheck(gBasicParam->EnableBuzzer);
		
		//���ֱ�ǩ
		//0-6B,1-6C
		if ( gBasicParam->TagType & 0x01 )
		{
			m_IsoChoose	=	0;//6B
		}
		if ( gBasicParam->TagType & 0x04 )
		{
			m_IsoChoose	=	1;//6c
		}
		//((CButton*)GetDlgItem(IDC_CHECK_6B))->SetCheck((int)(gBasicParam->TagType & 0x01));
		//((CButton*)GetDlgItem(IDC_CHECK_C1))->SetCheck((int)(gBasicParam->TagType & 0x02));
		//((CButton*)GetDlgItem(IDC_CHECK_6C))->SetCheck((int)(gBasicParam->TagType & 0x04));
		//((CButton*)GetDlgItem(IDC_CHECK_6D))->SetCheck((int)(gBasicParam->TagType & 0x08));
		
		//�����ĳ���ʱ��
		((CComboBox*)GetDlgItem(IDC_COMBO_READDUR))->SetCurSel(gBasicParam->ReadDuration);
		
		//��д����IP
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_READERIP))->SetAddress(gBasicParam->IP1,gBasicParam->IP2,gBasicParam->IP3,gBasicParam->IP4);
		//��д���Ķ˿�
		int m_ReaderPort=(((int)gBasicParam->Port1)<<8)+(int)gBasicParam->Port2;
		strText.Format("%d", m_ReaderPort);
		GetDlgItem(IDC_EDIT_READPORT)->SetWindowText(strText);
		
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_READERMASK))->SetAddress(gBasicParam->Mask1,gBasicParam->Mask2,gBasicParam->Mask3,gBasicParam->Mask4);
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_READERGW))->SetAddress(gBasicParam->Gateway1,gBasicParam->Gateway2,gBasicParam->Gateway3,gBasicParam->Gateway4);
		
		strText.Format("%02X%02X%02X%02X%02X%02X",gBasicParam->MAC1,gBasicParam->MAC2,gBasicParam->MAC3,gBasicParam->MAC4,gBasicParam->MAC5,gBasicParam->MAC6);
		((CEdit*)GetDlgItem(IDC_EDITREADERMAC))->SetWindowText(strText);

		
	}
	else if ( 1 == iOpt )
	{
		//�Զ���������
		//����1-4
		((CButton*)GetDlgItem(IDC_CHECK_ANT1))->SetCheck((int)(gAutoParam->Antenna & 0x01));
		((CButton*)GetDlgItem(IDC_CHECK_ANT2))->SetCheck((int)(gAutoParam->Antenna & 0x02));
		((CButton*)GetDlgItem(IDC_CHECK_ANT3))->SetCheck((int)(gAutoParam->Antenna & 0x04));
		((CButton*)GetDlgItem(IDC_CHECK_ANT4))->SetCheck((int)(gAutoParam->Antenna & 0x08));
		
		//����ģʽ
		m_AutoWorkMode		=	gAutoParam->AutoMode;	//0-��ʱģʽ,1-����ģʽ
		//�����ʽ
		m_OutputFormata		=	gAutoParam->OutputManner;	//0-��,1-��׼
		//����˿�
		m_OutputPortMode	=	gAutoParam->OutInterface;	//0-RS232,1-RS485,2-RJ45,3-Wiegand26,4-Wiegand34
		//����ģʽ
		m_TriggerModea		=	gAutoParam->TriggerMode;	//0-�͵�ƽ��1-�ߵ�ƽ
		
		
		//��ʱ���
		m_OutputInteTimems	=	gAutoParam->Interval;	//0-10ms��1-20ms��2-30ms��3-50ms��4-100ms��ȱʡֵΪ2��ÿ���趨ʱ��������ȡһ�α�ǩ��
		//����IP
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_HOSTIP))->SetAddress(gAutoParam->HostIP1,gAutoParam->HostIP2,gAutoParam->HostIP3,gAutoParam->HostIP4); 
		//����PORT
		int m_HostPort	=	0;
		m_HostPort		=	gAutoParam->Port1;
		m_HostPort		=	(m_HostPort<<8)+gAutoParam->Port2;
		strText.Format("%d", m_HostPort);
		GetDlgItem(IDC_EDIT_HOSTPORT)->SetWindowText(strText);
		
		
		//��ⱨ��
		((CButton*)GetDlgItem(IDC_CHECK_TESTALARM))->SetCheck(gAutoParam->Alarm);
		//���Ƽ̵���
		((CButton*)GetDlgItem(IDC_CHECK_ENABLERELAY))->SetCheck(gAutoParam->EnableRelay);
		
		//֪ͨ����
		m_Condiona			=	gAutoParam->Report_Condition;	//0-����֪ͨ,1-��ʱ֪ͨ,2-�����±�ǩ,3-���ٱ�ǩ,4-��ǩ���仯		
		

		//////////////////////////////////////////////////////////////////////////
		//����ʱ��
		int m_PersistenceTime	=	0;
		m_PersistenceTime	=	gAutoParam->TimeH;
		m_PersistenceTime	=	(m_PersistenceTime<<8)+gAutoParam->TimeL;
		strText.Format("%d", m_PersistenceTime);
		GetDlgItem(IDC_EDIT_PERTIME)->SetWindowText(strText);
		//������Ŀ
		int m_LenofList	=	0;
		m_LenofList		=	gAutoParam->NumH;
		m_LenofList		=	(m_LenofList<<8)+gAutoParam->NumL;
		strText.Format("%d", m_LenofList);
		GetDlgItem(IDC_EDIT_LENOFLIST)->SetWindowText(strText);
		//���ʱ��, ֪ͨ���
		short shValue	=	0;////�����ܳ�ʱ1
		//*((char *)&shValue + 0)	=	gAutoParam->CardTime1;
		//*((char *)&shValue + 1)	=	gAutoParam->CardTime2;
		shValue =	gAutoParam->Report_Interval;
		strText.Format("%d", (unsigned short)shValue);
		GetDlgItem(IDC_EDIT_REPORTINTERVAL)->SetWindowText(strText);

		if ( theApp.iantennaIndex == 0 )
		{
			//ֱ��---0,����ʱ��Ϊ0, ֪ͨ���Ϊ �û��Զ���
			//��׼---1,����ʱ��Ϊ0, ֪ͨ���Ϊ �û��Զ���
			//��ʱ---2,����ʱ��Ϊ�û��Զ���, ֪ͨ���Ϊ0,��ʱ���׼����
			switch ( m_Condiona )
			{
			case 0:
				m_PersistenceTime	=	gAutoParam->TimeH;
				m_PersistenceTime	=	(m_PersistenceTime<<8)+gAutoParam->TimeL;
				strText.Format("%d", m_PersistenceTime);
				GetDlgItem(IDC_EDIT_PERTIME)->SetWindowText(strText);

				shValue =	gAutoParam->Report_Interval;
				strText.Format("%d", (unsigned short)shValue);
				GetDlgItem(IDC_EDIT_REPORTINTERVAL)->SetWindowText(strText);
				
				break;
			case 1:
				m_PersistenceTime	=	gAutoParam->TimeH;
				m_PersistenceTime	=	(m_PersistenceTime<<8)+gAutoParam->TimeL;
				strText.Format("%d", m_PersistenceTime);
				GetDlgItem(IDC_EDIT_PERTIME)->SetWindowText(strText);
				
				shValue =	gAutoParam->Report_Interval;
				strText.Format("%d", (unsigned short)shValue);
				GetDlgItem(IDC_EDIT_REPORTINTERVAL)->SetWindowText(strText);
				
				break;
			case 2:
				m_PersistenceTime	=	gAutoParam->TimeH;
				m_PersistenceTime	=	(m_PersistenceTime<<8)+gAutoParam->TimeL;
				strText.Format("%d", m_PersistenceTime);
				GetDlgItem(IDC_EDIT_REPORTINTERVAL)->SetWindowText(strText);				
				
				shValue =	gAutoParam->Report_Interval;
				strText.Format("%d", (unsigned short)shValue);
				GetDlgItem(IDC_EDIT_PERTIME)->SetWindowText(strText);
				break;
				
			}		
			
		}
		//////////////////////////////////////////////////////////////////////////




		//�Ƿ�֪ͨ����
		((CButton*)GetDlgItem(IDC_CHECK_REPORTOUTPUT))->SetCheck(gAutoParam->Report_Output);
		
		
		//WiegandWidth(*10us)
		strText.Format("%d", gAutoParam->WiegandWidth);
		GetDlgItem(IDC_EDIT_WIEGANDWIDTH)->SetWindowText(strText);
		//WiegandBetween(*10us)
		strText.Format("%d", gAutoParam->WiegandInterval);
		GetDlgItem(IDC_EDIT_WIEGANDINTERVALl)->SetWindowText(strText);
		
		
		//��������
		m_FromTaga			=	gAutoParam->IDPosition;	//0-��ǩ����ID��1-�û��Զ���
		//������ʼ��ַ
		strText.Format("%d", gAutoParam->ID_Start);
		GetDlgItem(IDC_EDIT_IDSART)->SetWindowText(strText);
		

	}

	UpdateData(FALSE);

	return TRUE;
}



//iOpt,0--����������1--�Զ�����, 2--����ֵ
BOOL CReaderParameterDlg::OnUpdateParameter(void *pParam, int iOpt)
{
	apiReturn res	=	_no_scanner;

	if ( 0 == iOpt )
	{
		ReaderBasicParam	*BasicParamTmp	=	(ReaderBasicParam*)pParam;
		//0--����������������
		switch(ConnectMode)
		{
		case 0://����
			res=Net_WriteBasicParam(m_hSocket, BasicParamTmp);
			break;
		case 1://RS232
			res=WriteBasicParam(m_hScanner, BasicParamTmp, 0);
			break;
		case 2://RS485
			res=WriteBasicParam(m_hScanner, BasicParamTmp, RS485Address);
			break;
		}
		if (res!=_OK)
		{
			//MessageBox("Write Fail!(BasicParam)","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_C0098"), theApp.g_LoadString("IDWQB_C0099"), MB_ICONWARNING);
			return	FALSE;
		}

		//�ɹ���Ҫ����ȫ��
		*gBasicParam	=	*BasicParamTmp;

	}
	else if ( 1 == iOpt )
	{
		ReaderAutoParam	*AutoParamTmp	=	(ReaderAutoParam*)pParam;

		//1--�Զ�������������
		switch(ConnectMode)
		{
		case 0://����
			res=Net_WriteAutoParam(m_hSocket, AutoParamTmp);
			break;
		case 1://RS232
			res=WriteAutoParam(m_hScanner, AutoParamTmp, 0);
			break;
		case 2://RS485
			res=WriteAutoParam(m_hScanner, AutoParamTmp, RS485Address);
			break;
		}
		if (res!=_OK)
		{
			//MessageBox("Write Fail!(AutoParam)","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_C0102"), theApp.g_LoadString("IDWQB_C0103"), MB_ICONWARNING);
			return FALSE;
		}

		//�ɹ���Ҫ����ȫ��
		*gAutoParam	=	*AutoParamTmp;

	}
	else if ( 2 == iOpt )
	{
		//2--����ֵ
		switch(ConnectMode)
		{
		case 0://����
			res=Net_ReadFactoryParameter(m_hSocket);
			break;
		case 1://RS232
			res=ReadFactoryParameter(m_hScanner, 0);
			break;
		case 2://RS485
			res=ReadFactoryParameter(m_hScanner, RS485Address);
			break;
		}
		if (res!=_OK)
		{
			//MessageBox("FactoryParameter Fail!(FactoryParameter)","Warring",MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQB_C0104"), theApp.g_LoadString("IDWQB_C0105"), MB_ICONWARNING);
			return FALSE;
		}

	}
	else
	{
		return FALSE;
	}

	if ( res == _OK )
	{
		//MessageBox("Write Success!","info",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_C0100"), theApp.g_LoadString("IDWQB_C0101"), MB_ICONINFORMATION);
	}

	return TRUE;
}


void CReaderParameterDlg::OnButtonSetbasic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//д��������
	CString strText;
	CString strTemp;
	int iValue	=	0;
	ReaderBasicParam	BasicParam;
	BasicParam = *gBasicParam;

	//bps
	BasicParam.BaudRate	=	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->GetCurSel()+4;
	//��СƵ��
	//���Ƶ��
	CComboBox *m_MinFrequency	=	(CComboBox*)GetDlgItem(IDC_COMBO_MAINFREQ);
	CComboBox *m_MaxFrequency	=	(CComboBox*)GetDlgItem(IDC_COMBO_MAXFREQ);
	int imin	=	m_MinFrequency->GetCurSel();
	int imax	=	m_MaxFrequency->GetCurSel();
	if ( imin < 0 )
	{
		imin	=	0;
	}
	if ( imax < 0 )
	{
		imax	=	0;
	}
	//��Ϊͨ����������ÿ�����ҵ�Ƶ����Щ��һ����
	BasicParam.Min_Frequence = (BYTE)(imin+1);
	BasicParam.Max_Frequence = (BYTE)(imax+1);
	
	//RF power
	GetDlgItem(IDC_EDIT_POWER)->GetWindowText(strText);
	iValue	=	atoi(strText);
	if ((iValue<0) || (iValue>63))
	{
		iValue	=	63;
	}
	BasicParam.Power	=	(BYTE)iValue;
	
	
	//Address of Reader (1-254)
	GetDlgItem(IDC_EDIT_RS485ADDR)->GetWindowText(strText);
	iValue	=	atoi(strText);
	if ((iValue<0) || (iValue>254))
	{
		iValue	=	254;
	}
	BasicParam.ReaderAddress	=	(BYTE)iValue;

	//RS485�򲻴�
	
	
	//Max Tags of once Reading(1-100)
	GetDlgItem(IDC_EDIT_NUMOFCARD)->GetWindowText(strText);
	iValue	=	atoi(strText);
	if ((iValue<1) || (iValue>100))
	{
		iValue	=	100;
	}
	BasicParam.NumofCard	=	(BYTE)iValue;

	//��������ݲ��ã������ݲ�Ҫ
	//Modulation Depth(0-100)

	//Command execution times
	GetDlgItem(IDC_EDIT_READTIMES)->GetWindowText(strText);
	iValue	=	atoi(strText);
	if ((iValue<0) || (iValue>100))
	{
		iValue	=	100;
	}
	BasicParam.ReadTimes	=	(BYTE)iValue;
	
	//����ģʽ
	BasicParam.WorkMode		=	m_IsAutocmd;	//0-auto,1-command
	
	
	//buzzer
	BasicParam.EnableBuzzer	=	((CButton*)GetDlgItem(IDC_CHECK_BUZZER))->GetCheck();
	
	//���ֱ�ǩ,m_IsoChoose			=	-1;	//0-6B,1-6C
	BasicParam.TagType	=	0x00;
	if ( m_IsoChoose == 1 )//6C
	{
		BasicParam.TagType	= 0x04;
	}
	else
	{
		BasicParam.TagType	= 0x01;
	}
	//BasicParam.TagType	|=	(((CButton*)GetDlgItem(IDC_CHECK_6B))->GetCheck() << 0 & 0x01);
	//BasicParam.TagType	|=	(((CButton*)GetDlgItem(IDC_CHECK_C1))->GetCheck() << 1 & 0x02);
	//BasicParam.TagType	|=	(((CButton*)GetDlgItem(IDC_CHECK_6C))->GetCheck() << 2 & 0x04);
	//BasicParam.TagType	|=	(((CButton*)GetDlgItem(IDC_CHECK_6D))->GetCheck() << 3 & 0x08);
	
	
	//�����ĳ���ʱ��
	BasicParam.ReadDuration	=	((CComboBox*)GetDlgItem(IDC_COMBO_READDUR))->GetCurSel();
	
	//��д����IP
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_READERIP))->GetAddress(BasicParam.IP1,BasicParam.IP2,BasicParam.IP3,BasicParam.IP4);
	//��д���Ķ˿�
	int m_ReaderPort=0;
	GetDlgItem(IDC_EDIT_READPORT)->GetWindowText(strText);
	m_ReaderPort	=	atoi(strText);
	BasicParam.Port1=(m_ReaderPort>>8) & 0xFF;
	BasicParam.Port2=m_ReaderPort & 0xFF;

	
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_READERMASK))->GetAddress(BasicParam.Mask1,BasicParam.Mask2,BasicParam.Mask3,BasicParam.Mask4);
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_READERGW))->GetAddress(BasicParam.Gateway1,BasicParam.Gateway2,BasicParam.Gateway3,BasicParam.Gateway4);
	
	
	BYTE readerMAC[6];
	((CEdit*)GetDlgItem(IDC_EDITREADERMAC))->GetWindowText(strText);
	
	if (strText.GetLength()<12)
	{
		//MessageBox("Please input unabridged MAC!","Error",MB_ICONERROR);
		MessageBox(theApp.g_LoadString("IDWQB_C0106"), theApp.g_LoadString("IDWQB_C0107"), MB_ICONERROR);
		return;
	}
	strTemp=strText.SpanIncluding("0123456789ABCDEFabcdef");
	if(strTemp.GetLength()!=strText.GetLength())
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0108"), theApp.g_LoadString("IDWQB_C0109"), MB_ICONWARNING);
		return;
	}
	strTemp=strText;
	
	for(int i=0;i<6;i++)
	{
		readerMAC[i]=(BYTE)strtol((CString)strTemp[i*2]+(CString)strTemp[2*i+1],NULL,16);
	}
	
	BasicParam.MAC1 =readerMAC[0];
	BasicParam.MAC2 =readerMAC[1];
	BasicParam.MAC3 =readerMAC[2];
	BasicParam.MAC4 =readerMAC[3];
	BasicParam.MAC5 =readerMAC[4];
	BasicParam.MAC6 =readerMAC[5];

	
	UpdateData(FALSE);

	OnUpdateParameter(&BasicParam, 0);

}

void CReaderParameterDlg::OnButtonSetauto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//д�Զ�����
	CString strText;
	CString strTemp;
	int iValue	=	0;
	ReaderAutoParam	AutoParam;

	//����1-4
	AutoParam.Antenna	=	0x00;
	AutoParam.Antenna	|=	(((CButton*)GetDlgItem(IDC_CHECK_ANT1))->GetCheck() << 0 & 0x01);
	AutoParam.Antenna	|=	(((CButton*)GetDlgItem(IDC_CHECK_ANT2))->GetCheck() << 1 & 0x02);
	AutoParam.Antenna	|=	(((CButton*)GetDlgItem(IDC_CHECK_ANT3))->GetCheck() << 2 & 0x04);
	AutoParam.Antenna	|=	(((CButton*)GetDlgItem(IDC_CHECK_ANT4))->GetCheck() << 3 & 0x08);

	
	//����ģʽ
	AutoParam.AutoMode			=	m_AutoWorkMode;//�Զ�����(0-����(��ʱ),1-����)

	//�����ʽ
	AutoParam.OutputManner		=	m_OutputFormata;	//0-��,1-��׼
	//����˿�
	AutoParam.OutInterface		=	m_OutputPortMode;	//0-RS232,1-RS485,2-RJ45,3-Wiegand26,4-Wiegand34
	//����ģʽ
	AutoParam.TriggerMode		=	m_TriggerModea;		//0-�͵�ƽ��1-�ߵ�ƽ
	
	
	
	//��ʱ���
	AutoParam.Interval			=	m_OutputInteTimems;	//0-10ms��1-20ms��2-30ms��3-50ms��4-100ms��ȱʡֵΪ2��ÿ���趨ʱ��������ȡһ�α�ǩ��

	//����IP
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_HOSTIP))->GetAddress(AutoParam.HostIP1,AutoParam.HostIP2,AutoParam.HostIP3,AutoParam.HostIP4); 
	//����PORT
	int m_HostPort	=	0;
	GetDlgItem(IDC_EDIT_HOSTPORT)->GetWindowText(strText);
	m_HostPort	=	atoi(strText);
	AutoParam.Port1=(m_HostPort>>8) & 0xFF;
	AutoParam.Port2=m_HostPort & 0xFF;
	
	
	//��ⱨ��
	AutoParam.Alarm	=	((CButton*)GetDlgItem(IDC_CHECK_TESTALARM))->GetCheck();
	//���Ƽ̵���
	AutoParam.EnableRelay	=	((CButton*)GetDlgItem(IDC_CHECK_ENABLERELAY))->GetCheck();
	
	//֪ͨ����
	AutoParam.Report_Condition	=	m_Condiona;	//0-����֪ͨ,1-��ʱ֪ͨ,2-�����±�ǩ,3-���ٱ�ǩ,4-��ǩ���仯
	
	
	//////////////////////////////////////////////////////////////////////////
	//����ע��һ������������
	//����ʱ��
	int m_PersistenceTime	=	0;
	GetDlgItem(IDC_EDIT_PERTIME)->GetWindowText(strText);
	m_PersistenceTime	=	atoi(strText);
	AutoParam.TimeH		=	(m_PersistenceTime>>8) & 0xFF;
	AutoParam.TimeL		=	m_PersistenceTime & 0xFF;
	
	
	//������Ŀ
	int m_LenofList	=	0;
	GetDlgItem(IDC_EDIT_LENOFLIST)->GetWindowText(strText);
	m_LenofList		=	atoi(strText);
	AutoParam.NumH=	(m_LenofList>>8) & 0xFF;
	AutoParam.NumL=	m_LenofList & 0xFF;
	
	
	//���ʱ��,��֪ͨ���
	short shValue	=	0;////�����ܳ�ʱ1
	GetDlgItem(IDC_EDIT_REPORTINTERVAL)->GetWindowText(strText);
	shValue	=	(short)atoi(strText);
	//AutoParam.CardTime2	=	(shValue>>8) & 0xFF;
	//AutoParam.CardTime1	=	shValue & 0xFF;
	AutoParam.Report_Interval	=	(char)shValue;

	if ( theApp.iantennaIndex == 0 )
	{
		//ֱ��---0,����ʱ��Ϊ0, ֪ͨ���Ϊ �û��Զ���
		//��׼---1,����ʱ��Ϊ0, ֪ͨ���Ϊ �û��Զ���
		//��ʱ---2,����ʱ��Ϊ�û��Զ���, ֪ͨ���Ϊ0,��ʱ���׼����
		switch ( m_Condiona )
		{
		case 0:
			AutoParam.TimeH		=	0;
			AutoParam.TimeL		=	0;
			AutoParam.Report_Interval	=	(char)shValue;
			break;
		case 1:
			AutoParam.TimeH		=	0;
			AutoParam.TimeL		=	0;
			AutoParam.Report_Interval	=	(char)shValue;
			break;
		case 2:
			AutoParam.TimeH		=	(shValue>>8) & 0xFF;;
			AutoParam.TimeL		=	shValue & 0xFF;
			AutoParam.Report_Interval	=	(char)0;
			break;

		}

	}
	//////////////////////////////////////////////////////////////////////////

	
	//�Ƿ�֪ͨ����
	AutoParam.Report_Output	=	((CButton*)GetDlgItem(IDC_CHECK_REPORTOUTPUT))->GetCheck();
	
	
	//WiegandWidth(*10us)
	GetDlgItem(IDC_EDIT_WIEGANDWIDTH)->GetWindowText(strText);
	AutoParam.WiegandWidth	=	atoi(strText);

	//WiegandBetween(*10us)
	GetDlgItem(IDC_EDIT_WIEGANDINTERVALl)->GetWindowText(strText);
	AutoParam.WiegandInterval	=	atoi(strText);	
	
	//��������
	AutoParam.IDPosition	=	m_FromTaga;	//0-��ǩ����ID��1-�û��Զ���
	//������ʼ��ַ
	GetDlgItem(IDC_EDIT_IDSART)->GetWindowText(strText);
	AutoParam.ID_Start	=	atoi(strText);

	OnUpdateParameter(&AutoParam, 1);

	UpdateData(FALSE);

	return;
}

void CReaderParameterDlg::OnButtonActivefactory() 
{
	// TODO: Add your control notification handler code here
	//�ָ�����
	OnUpdateParameter(NULL, 2);

}

void CReaderParameterDlg::OnButtonReadfilter() 
{
	// TODO: Add your control notification handler code here
	//��ȡ������
	apiReturn res	=	_no_scanner;
	int filterLength	=	0;
	int FilterAddress	=	0;
	int l = 0;
	int i = 0;
	CString str,str_temp;
	BYTE FilterMask[64]={0};

	//��ȡ������
	switch(ConnectMode)
	{
	case 0://����
		res=Net_GetReportFilter(m_hSocket, &FilterAddress, &filterLength, &FilterMask[0]);
		break;
	case 1://RS232
		res=GetReportFilter(m_hScanner, &FilterAddress, &filterLength, &FilterMask[0], 0);
		break;
	case 2://RS485
		res=GetReportFilter(m_hScanner, &FilterAddress, &filterLength, &FilterMask[0], RS485Address);
		break;
	}
	if (res==_OK)
	{
		str_temp.Format("%d", FilterAddress);
		GetDlgItem(IDC_EDIT_FILTERADD)->SetWindowText(str_temp);

		str_temp.Format("%d", filterLength);
		GetDlgItem(IDC_EDIT_FILTERLEN)->SetWindowText(str_temp);
		
		
		if(filterLength!=0)
		{
			if (filterLength%8==0)
			{
				l=filterLength/8;
			}
			else
			{
				l=filterLength/8+1;
			}
			
			str="";
			for(i=0;i<l;i++)
			{
				str_temp.Format("%02X",FilterMask[i]);
				str+=str_temp;
			}
		}

		str_temp	=	str;
		GetDlgItem(IDC_EDIT_FILTERMASK)->SetWindowText(str_temp);
		

		return;
	}
	else
	{
		//MessageBox("Reader Fail!(Readfilter)","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0110"), theApp.g_LoadString("IDWQB_C0111"), MB_ICONWARNING);

	}

	return;
}

void CReaderParameterDlg::OnButtonSetfilter() 
{
	// TODO: Add your control notification handler code here
	//���ù�����
	apiReturn res;
	int str_len	=	0;
	int filterLength	=	0;
	int m	=	0;
	int i	=	0;
	CString str;
	CString m_FilterMask;
	BYTE FilterMask[64]	=	{0};
	int m_FilterAddress	=	0;
	int m_FilterLength	=	0;
	
	GetDlgItem(IDC_EDIT_FILTERADD)->GetWindowText(str);
	m_FilterAddress	=	atoi(str);

	if ((m_FilterAddress<0) || (m_FilterAddress>95))
	{
		m_FilterAddress	=	0;
		return;
	}
	

	GetDlgItem(IDC_EDIT_FILTERLEN)->GetWindowText(str);
	m_FilterLength	=	atoi(str);
	if ((m_FilterLength<0) || (m_FilterLength>96))
	{
		m_FilterLength	=	0;
		return;
	}
	
	str="";
	GetDlgItem(IDC_EDIT_FILTERMASK)->GetWindowText(m_FilterMask);
	str=m_FilterMask.SpanIncluding("0123456789ABCDEFabcdef");
	if(str.GetLength()!=m_FilterMask.GetLength())
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0108"), theApp.g_LoadString("IDWQB_C0109"), MB_ICONWARNING);
		return;
	}
	
	str_len=m_FilterMask.GetLength();
	str=m_FilterMask;
	
	if (m_FilterLength==0)
	{
		m=0;
	}
	else
	{
		m=m_FilterLength/8;
		if (m_FilterLength%8!=0)
		{
			for(i=0;i<((m+1)*2-str_len);i++)
			{
				str+="0";
			}
			m++;
		}
	}
	filterLength=m_FilterLength;
	
	for(i=0;i<m;i++)
	{
		FilterMask[i]=(BYTE)strtol(((CString)str[i*2]+(CString)str[i*2+1]),NULL,16);
	}
	
	switch(ConnectMode)
	{
	case 0://����
		res=Net_SetReportFilter(m_hSocket, m_FilterAddress,filterLength,FilterMask);
		break;
	case 1://RS232
		res=SetReportFilter(m_hScanner,m_FilterAddress,filterLength,FilterMask,0);
		break;
	case 2://RS485
		res=SetReportFilter(m_hScanner,m_FilterAddress,filterLength,FilterMask,RS485Address);
		break;
	}
	if (res==_OK)
	{
		//MessageBox("Write Success!","info",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_C0100"), theApp.g_LoadString("IDWQB_C0101"), MB_ICONINFORMATION);
	}
	else
	{
		//MessageBox("Write Fail!(Setfilter)","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0112"), theApp.g_LoadString("IDWQB_C0113"), MB_ICONWARNING);
	}

	return;
}

void CReaderParameterDlg::OnButtonGetrelay() 
{
	// TODO: Add your control notification handler code here
	//��ȡ�̵���
	apiReturn res;
	CString str;
	int Relay	=	0;
	BYTE m_Relay;
	BYTE m_Relay1;
	
	switch(ConnectMode)
	{
	case 0://����
		res=Net_GetRelay(m_hSocket, &Relay);
		break;
	case 1://RS232
		res=GetRelay(m_hScanner,&Relay,0);
		break;
	case 2://RS485
		res=GetRelay(m_hScanner,&Relay,RS485Address);
		break;
	}

	if(res==_OK)
	{
		m_Relay=Relay & 0x01;
		m_Relay1=(Relay>>1) & 0x01;
	
		((CButton*)GetDlgItem(IDC_CHECK_RELAY))->SetCheck(m_Relay);
		((CButton*)GetDlgItem(IDC_CHECK_RELAY1))->SetCheck(m_Relay1);

	}
	else
	{
		//MessageBox("Read Fail!(Getrelay)","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0114"), theApp.g_LoadString("IDWQB_C0115"), MB_ICONWARNING);
	}

	return;
}

void CReaderParameterDlg::OnButtonSetrelay() 
{
	// TODO: Add your control notification handler code here
	//���ü̵���
	apiReturn res;
	CString str;
	int Relay	=	0;

	if ( 1 == ((CButton*)GetDlgItem(IDC_CHECK_RELAY))->GetCheck() )
	{
		Relay	+=	1;
	}
	if ( 1 == ((CButton*)GetDlgItem(IDC_CHECK_RELAY1))->GetCheck() )
	{
		Relay	+=	2;
	}
	
	switch(ConnectMode)
	{
	case 0://����
		res=Net_SetRelay(m_hSocket, Relay);
		break;
	case 1://RS232
		res=SetRelay(m_hScanner,Relay,0);
		break;
	case 2://RS485
		res=SetRelay(m_hScanner,Relay,RS485Address);
		break;
	}
	
	if(res==_OK)
	{
		//MessageBox("Write Success!","info",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_C0100"), theApp.g_LoadString("IDWQB_C0101"), MB_ICONINFORMATION);
		
	}
	else
	{
		//MessageBox("Read Fail!(Getrelay)","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0114"), theApp.g_LoadString("IDWQB_C0115"), MB_ICONWARNING);
	}

	return;
}

void CReaderParameterDlg::OnButton1Readtime() 
{
	// TODO: Add your control notification handler code here
	//��ȡ��д��ʱ��
	apiReturn res	=	_no_scanner;
	CString strtmp;
	ReaderDate time;
	int nYear;
	
	switch(ConnectMode)
	{
	case 0://����
		res=Net_GetReaderTime(m_hSocket, &time);
		break;
	case 1://RS232
		res=GetReaderTime(m_hScanner, &time, 0);
		break;
	case 2://RS485
		res=GetReaderTime(m_hScanner, &time, RS485Address);
		break;
	}
	
	if(res==_OK)
	{
		nYear=(int)time.Year;
		nYear=nYear+2000;
		strtmp.Format("%02d-%02d-%02d %02d:%02d:%02d",nYear,time.Month,time.Day,time.Hour,time.Minute,time.Second); 
		GetDlgItem(IDC_EDIT1_TIME)->SetWindowText(strtmp);//ʱ��

		//MessageBox("Read Time success!","info",MB_ICONINFORMATION);
		
	}
	else
	{
		//MessageBox("Read Time fail!","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0114"), theApp.g_LoadString("IDWQB_C0115"), MB_ICONWARNING);
	}

	return;	
}

void CReaderParameterDlg::OnButton1Settime() 
{
	// TODO: Add your control notification handler code here
	//���ö�д��ʱ��
	apiReturn res	=	_no_scanner;
	CString strtmp;
	CString str;
	ReaderDate time;
	BYTE time1[6]	=	{0};
	
	CTime m_NowTime= CTime::GetCurrentTime();
	
	time.Year=m_NowTime.GetYear()%100;
	time.Month=m_NowTime.GetMonth();
	time.Day=m_NowTime.GetDay();
	time.Hour=m_NowTime.GetHour();
	time.Minute=m_NowTime.GetMinute();
	time.Second=m_NowTime.GetSecond();
	strtmp.Format("%02d-%02d-%02d %02d:%02d:%02d",time.Year,time.Month,time.Day,time.Hour,time.Minute,time.Second);
	str.Format("%02x%02x%02x%02x%02x%02x",time.Year,time.Month,time.Day,time.Hour,time.Minute,time.Second);
	StrtimetoDecimal(str,time1);
	time.Year=time1[0];
	time.Month=time1[1];
	time.Day=time1[2];
	time.Hour=time1[3];
	time.Minute=time1[4];
	time.Second=time1[5];
	
	switch(ConnectMode)
	{
	case 0://����
		res=Net_SetReaderTime(m_hSocket, &time);
		break;
	case 1://RS232
		res=SetReaderTime(m_hScanner, &time, 0);
		break;
	case 2://RS485
		res=SetReaderTime(m_hScanner, &time, RS485Address);
		break;
	}
	
	if(res==_OK)
	{
		
		//MessageBox("Set Time success!","info",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_C0100"), theApp.g_LoadString("IDWQB_C0101"), MB_ICONINFORMATION);
		
	}
	else
	{
		//MessageBox("Set Time fail!","Warring",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_C0112"), theApp.g_LoadString("IDWQB_C0113"), MB_ICONWARNING);
	}
	
	return;
}

void CReaderParameterDlg::OnButtonWorkautostart() 
{
	// TODO: Add your control notification handler code here
	//��ʼ�Զ�����
	apiReturn res	=	_no_scanner;

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
	
	if(res==_OK)
	{
		MessageBox(theApp.g_LoadString("IDWQB_C0100"), theApp.g_LoadString("IDWQB_C0101"), MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(theApp.g_LoadString("IDWQB_C0112"), theApp.g_LoadString("IDWQB_C0113"), MB_ICONWARNING);
	}
	
	return;
}

void CReaderParameterDlg::OnButtonWorkautostop() 
{
	// TODO: Add your control notification handler code here
	//ֹͣ�Զ�����
	apiReturn res	=	_no_scanner;
	
	switch(ConnectMode)
	{
	case 0://����
		res=Net_AutoMode(m_hSocket,0);
		break;
	case 1://RS232
		res=AutoMode(m_hScanner,0,0);
		break;
	case 2://RS485
		res=AutoMode(m_hScanner,0,RS485Address);
		break;
	}
	
	if(res==_OK)
	{
		MessageBox(theApp.g_LoadString("IDWQB_C0100"), theApp.g_LoadString("IDWQB_C0101"), MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(theApp.g_LoadString("IDWQB_C0112"), theApp.g_LoadString("IDWQB_C0113"), MB_ICONWARNING);
	}

	return;
}

void CReaderParameterDlg::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	::KillTimer(gReaderParamHwnd, TIME_IDENTIFIER_PARAM);
}

//WM_READERPARMDATAMSG
afx_msg LRESULT CReaderParameterDlg::OnReaderparmdatamsg(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 2 == iwParam )
	{
		OnInitUIText();	//��������
	}
	else if( 0 == iwParam )
	{
		if ( 0 == ilParam )
		{
			CString   strTime;
			//SYSTEMTIME   time;   
			//GetSystemTime(&time);GetCurrentTime() 
			//sprintf(strTime.GetBuffer(MAX_PATH),_T("%04d-%02d-%02d %02d:%02d:%02d"),time.wYear,time.wMonth,time.wDay,
			//	time.wHour,time.wMinute,time.wSecond);
			//strTime.ReleaseBuffer();

			
			
			CTime t = CTime::GetCurrentTime();
			
			
			
			strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", t.GetYear(), t.GetMonth(), t.GetDay(),
				t.GetHour(), t.GetMinute(), t.GetSecond() );

			//���費��Ҫ
			//GetDlgItem(IDC_STATIC_TIMEA)->SetWindowText(strTime);//����ʱ��

		}
	}
	
	return 0;
}




