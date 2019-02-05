// ReaderParameter.cpp : implementation file
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "ReaderParameter.h"
#include "Progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReaderParameter property page

IMPLEMENT_DYNCREATE(CReaderParameter, CPropertyPage)

CReaderParameter::CReaderParameter() : CPropertyPage(CReaderParameter::IDD)
{
	//{{AFX_DATA_INIT(CReaderParameter)
	m_WorkMode = -1;
	m_Power1 = 0;
	m_Power2 = 0;
	m_Relay1 = FALSE;
	m_Relay2 = FALSE;
	m_NumofCard = 0;
	m_Antenna1 = FALSE;
	m_Antenna2 = FALSE;
	m_Antenna3 = FALSE;
	m_Antenna4 = FALSE;
	m_OutInterface = -1;
	m_WiegandWidth = 0;
	m_WiegandInterval = 0;
	m_IDStart = 0;
	m_OutMode = -1;
	m_HardVer = _T("");
	m_SoftVer = _T("");
	m_Modulation = FALSE;
	m_TXMode = FALSE;
	m_TagType = -1;
	m_StandardTime = 0;
	m_EnableBuzzer = FALSE;
	m_IDPosition = -1;
	m_AddressReader = 0;
	m_RS485 = FALSE;
	m_ReaderPort = 0;
	m_HostPort = 0;
	m_CheckAuthorization = FALSE;
	m_ReaderMAC = _T("");
	//}}AFX_DATA_INIT
}

CReaderParameter::~CReaderParameter()
{
}

void CReaderParameter::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReaderParameter)
	DDX_Control(pDX, IDC_LIST2, m_ReaderTime);
	DDX_Control(pDX, IDC_IPADDRESS4, m_HostIPAddress);
	DDX_Control(pDX, IDC_IPADDRESS3, m_ReaderGateway);
	DDX_Control(pDX, IDC_IPADDRESS2, m_ReaderIPMask);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ReaderIPAddress);
	DDX_Control(pDX, IDC_COMBO6, m_ReadCycle);
	DDX_Control(pDX, IDC_COMBO5, m_ReadDuration);
	DDX_Control(pDX, IDC_COMBO4, m_ReadInterval);
	DDX_Control(pDX, IDC_COMBO3, m_MaxFrequency);
	DDX_Control(pDX, IDC_COMBO2, m_MinFrequency);
	DDX_Control(pDX, IDC_COMBO1, m_BaudRate);
	DDX_Radio(pDX, IDC_RADIO1, m_WorkMode);
	DDX_Text(pDX, IDC_EDIT1, m_Power1);
	DDX_Text(pDX, IDC_EDIT2, m_Power2);
	DDX_Check(pDX, IDC_CHECK10, m_Relay1);
	DDX_Check(pDX, IDC_CHECK11, m_Relay2);
	DDX_Text(pDX, IDC_EDIT6, m_NumofCard);
	DDX_Check(pDX, IDC_CHECK5, m_Antenna1);
	DDX_Check(pDX, IDC_CHECK6, m_Antenna2);
	DDX_Check(pDX, IDC_CHECK7, m_Antenna3);
	DDX_Check(pDX, IDC_CHECK8, m_Antenna4);
	DDX_Radio(pDX, IDC_RADIO6, m_OutInterface);
	DDX_Text(pDX, IDC_EDIT3, m_WiegandWidth);
	DDX_Text(pDX, IDC_EDIT4, m_WiegandInterval);
	DDX_Text(pDX, IDC_EDIT5, m_IDStart);
	DDX_Radio(pDX, IDC_RADIO13, m_OutMode);
	DDX_Text(pDX, IDC_EDIT7, m_HardVer);
	DDX_Text(pDX, IDC_EDIT8, m_SoftVer);
	DDX_Check(pDX, IDC_CHECK9, m_Modulation);
	DDX_Check(pDX, IDC_CHECK12, m_TXMode);
	DDX_Radio(pDX, IDC_RADIO11, m_TagType);
	DDX_Text(pDX, IDC_EDIT9, m_StandardTime);
	DDX_Check(pDX, IDC_CHECK13, m_EnableBuzzer);
	DDX_Radio(pDX, IDC_RADIO17, m_IDPosition);
	DDX_Text(pDX, IDC_EDIT10, m_AddressReader);
	DDX_Check(pDX, IDC_CHECK14, m_RS485);
	DDX_Text(pDX, IDC_EDIT11, m_ReaderPort);
	DDX_Text(pDX, IDC_EDIT12, m_HostPort);
	DDX_Check(pDX, IDC_CHECK1, m_CheckAuthorization);
	DDX_Text(pDX, IDC_EDIT13, m_ReaderMAC);
	DDV_MaxChars(pDX, m_ReaderMAC, 12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReaderParameter, CPropertyPage)
	//{{AFX_MSG_MAP(CReaderParameter)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
	ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderParameter message handlers

void CReaderParameter::UpdateStatus()
{
	switch (m_HardVersion & 0xFF)
	{
	case 0x0B:
		GetDlgItem(IDC_CHECK5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK5)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK7)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK8)->EnableWindow(FALSE);
		break;
	case 0x0C:
		GetDlgItem(IDC_CHECK5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK5)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK6)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK7)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK8)->EnableWindow(FALSE);
		break;
	case 0x0E:
		GetDlgItem(IDC_CHECK5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK5)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK6)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK7)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK8)->EnableWindow(ifConnectReader);
		break;
	default:
		GetDlgItem(IDC_CHECK5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK5)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK6)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK7)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK8)->EnableWindow(ifConnectReader);
		break;
	}
	if(((m_SoftVersion >> 8) & 0xFF) > 59)
	{
		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_STATIC_READER_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_READER_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_READER_MASK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_READER_GATEWAY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_READER_MAC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_HOST_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_HOST_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT11)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT11)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT12)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT12)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT13)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT13)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_IPADDRESS1)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_IPADDRESS2)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_IPADDRESS3)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_IPADDRESS4)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_IPADDRESS1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON6)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO10)->EnableWindow(ifConnectReader);
	}
	else
	{
		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_READER_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_READER_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_READER_MASK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_READER_GATEWAY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_READER_MAC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_HOST_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_HOST_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT11)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT12)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT13)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_IPADDRESS1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_IPADDRESS2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_IPADDRESS3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_IPADDRESS4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO10)->ShowWindow(SW_HIDE);
}
		GetDlgItem(IDC_PARAMETER_FOR_EM_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PARAMETER_FOR_EM_STATIC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PARAMETER_FOR_EM_STATIC3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PARAMETER_FOR_EM_STATIC1)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_PARAMETER_FOR_EM_STATIC2)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_PARAMETER_FOR_EM_STATIC3)->EnableWindow(ifConnectReader);

		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO6)->ShowWindow(SW_SHOW);
		//GetDlgItem(IDC_COMBO1)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO2)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_COMBO3)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_COMBO4)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_COMBO5)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_COMBO6)->EnableWindow(ifConnectReader);

		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(ifConnectReader);

		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT1)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT3)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT5)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT6)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT7)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT8)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT9)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT10)->EnableWindow(ifConnectReader);

		GetDlgItem(IDC_Standard_STATIC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK11)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK12)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK13)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK14)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK9)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK10)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK11)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK12)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK13)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_CHECK14)->EnableWindow(ifConnectReader);

		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO1)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO2)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO3)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO6)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO7)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO8)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO9)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO11)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO11)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO12)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO12)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO13)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO13)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO14)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO14)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO15)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO15)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO17)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO17)->EnableWindow(ifConnectReader);
		GetDlgItem(IDC_RADIO18)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO18)->EnableWindow(ifConnectReader);

}

CString CReaderParameter::ReportError(USHORT res)
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
		str="Nonlicet Tag!";
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
		str="The Password is error!";
		break;
	case 0x0A:
		str="The Kill Password cannot be 000000!";
		break;
	case 0x0B:
		str="Illegal operation command!";
		break;
	case 0x0C:
		str="Illegal operation user!";
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

BOOL CReaderParameter::ReadParameter()
{
#if 0
	apiReturn res;
	Reader1000Param ReaderParam;
	int Port;
	BYTE IP_Address[4],Mask[4],Gateway[4],readerMAC[6];
	CString str="",str_temp="";

	str.Format("%02d%02d",(m_HardVersion>>8) & 0xFF,m_HardVersion & 0xFF);
	m_HardVer=str;
	str.Format("%02d%02d",(m_SoftVersion>>8) & 0xFF,m_SoftVersion & 0xFF);
	m_SoftVer=str;

	for(int i=0;i<3;i++)
	{
		switch(ConnectMode)
		{
		case 0:
			res=Net_ReadParam(m_hSocket,&ReaderParam);
			break;
		case 1:
			res=ReadParam(m_hScanner,&ReaderParam,0);
			break;
		}
		if (res==_OK)
			break;
	}
	if (res!=_OK)
		return FALSE;

	m_WorkMode = ReaderParam.WorkMode;
	m_Power1 = ReaderParam.Power;
	m_Power2 = ReaderParam.Power2;
	m_StandardTime=ReaderParam.StandardTime;

	switch(ReaderParam.TagType)
	{
	case 0x01:
		m_TagType=0;
		break;
	case 0x02:
		m_TagType=3;
		break;
	case 0x04:
		m_TagType=1;
		break;
	case 0x08:
		m_TagType=2;
		break;
	}
	switch(ReaderParam.OutMode)
	{
	case 0x00:
		GetDlgItem(IDC_Standard_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);
		break;
	case 0x01:
		GetDlgItem(IDC_Standard_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT9)->ShowWindow(SW_SHOW);
		break;
	}
	m_NumofCard = ReaderParam.NumofCard;
	m_Antenna1 = ReaderParam.Antenna & 0x01;
	m_Antenna2 = (ReaderParam.Antenna>>1) & 0x01;
	m_Antenna3 = (ReaderParam.Antenna>>2) & 0x01;
	m_Antenna4 = (ReaderParam.Antenna>>3) & 0x01;
	m_OutInterface = ReaderParam.OutInterface;
	m_WiegandWidth = ReaderParam.WiegandWidth;
	m_WiegandInterval = ReaderParam.WiegandInterval;
	m_IDStart = ReaderParam.ID_Start;
	m_IDPosition = ReaderParam.IDPosition;
	m_OutMode = ReaderParam.OutMode;
	m_BaudRate.SetCurSel(ReaderParam.BaudRate-4);
	m_MinFrequency.SetCurSel(ReaderParam.Min_Frequence-1);
	m_MaxFrequency.SetCurSel(ReaderParam.Max_Frequence-1);
	m_ReadInterval.SetCurSel(ReaderParam.ReadInterval);
	m_EnableBuzzer=ReaderParam.EnableBuzzer & 0x01;
	m_RS485=(ReaderParam.EnableBuzzer>>3) & 0x01;
	m_CheckAuthorization=ReaderParam.IfTestValidity & 0x01;
	ifAddress=m_RS485;
	m_AddressReader=ReaderParam.ReaderAddress;
	m_HostIPAddress.SetAddress(ReaderParam.HostIP1,ReaderParam.HostIP2,ReaderParam.HostIP3,ReaderParam.HostIP4);
	m_HostPort = (int)(ReaderParam.HostPort1<<8) + (int)ReaderParam.HostPort2;
	if(m_StandardTime==0)
	{
		m_StandardTime=120;
	}
	if (((m_HardVersion>>8) & 0xFF)==0x18 || ((m_HardVersion>>8) & 0xFF)==0x1A 
		|| ((m_HardVersion>>8) & 0xFF)==0x01|| ((m_HardVersion>>8) & 0xFF)==0x0A || ((m_HardVersion>>8) & 0xFF)==0x0B)
	{
		m_ReadDuration.SetCurSel(ReaderParam.ReadDuration & 0x0F);
		m_ReadCycle.SetCurSel((ReaderParam.ReadDuration & 0xF0)>>4);
	}

	if ((((m_HardVersion>>8) & 0xFF)==0x14) && (((m_SoftVersion>>8) & 0xFF)==0x50))
	{
		switch (ReaderParam.Modulation)
		{
		case 0x01:
			m_Modulation=TRUE;
			break;
		default:
			m_Modulation=FALSE;
		}
		switch (ReaderParam.TX_Mode)
		{
		case 0x01:
			m_TXMode=TRUE;
			ifTXMode=TRUE;
			break;
		default:
			m_TXMode=FALSE;
			ifTXMode=FALSE;
		}
	}

	if ((((m_HardVersion>>8) & 0xFF)==0x1A) && (((m_SoftVersion>>8) & 0xFF)==0x50))
	{
		switch (ReaderParam.TX_Mode)
		{
		case 0x01:
			m_TXMode=TRUE;
			ifTXMode=TRUE;
			break;
		default:
			m_TXMode=FALSE;
			ifTXMode=FALSE;
		}
	}

	if(((m_SoftVersion>>8) & 0xFF) > 59)
	{
		for(i=0;i<3;i++)
		{
			switch(ConnectMode)
			{
			case 0:
				res=Net_GetReaderNetwork(m_hSocket,IP_Address,&Port,Mask,Gateway);
				break;
			case 1:
				res=GetReaderNetwork(m_hScanner,IP_Address,&Port,Mask,Gateway);
				break;
			}
			if (res==_OK)
				break;
		}
		if (res!=_OK)
		{
			MessageBox("Failure read the IP address of reader !","Error",MB_ICONERROR);
			return FALSE;
		}
		m_ReaderIPAddress.SetAddress(IP_Address[0],IP_Address[1],IP_Address[2],IP_Address[3]);
		m_ReaderIPMask.SetAddress(Mask[0],Mask[1],Mask[2],Mask[3]);
		m_ReaderGateway.SetAddress(Gateway[0],Gateway[1],Gateway[2],Gateway[3]);
		m_ReaderPort=Port;

		for(i=0;i<3;i++)
		{
			switch(ConnectMode)
			{
			case 0:
				res=Net_GetReaderMAC(m_hSocket,readerMAC);
				break;
			case 1:
				res=GetReaderMAC(m_hScanner,readerMAC);
				break;
			}
			if (res==_OK)
				break;
		}
		if (res!=_OK)
		{
			MessageBox("Failure read the MAC address of reader !","Error",MB_ICONERROR);
			return FALSE;
		}
		str.Format("%02X%02X%02X%02X%02X%02X",readerMAC[0],readerMAC[1],readerMAC[2],readerMAC[3],readerMAC[4],readerMAC[5]);
		m_ReaderMAC=str;

	}

	if(ifAddress)
		RS485Address=ReaderParam.ReaderAddress ;
	else
		RS485Address=0;

	UpdateData(FALSE);
	UpdateStatus();
#endif

	return TRUE;
}

BOOL CReaderParameter::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
#if 0
	int NumofFreq;
	double Freq,jumpFreq;
	BOOL ischina=FALSE;
	BOOL AM=FALSE;

	switch((m_HardVersion>>8) & 0xFF)
	{
	case 0x14:
		switch((m_SoftVersion>>8) & 0xFF)
		{
		case 0x00:
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
			break;
		case 0x01:
			NumofFreq=125;
			Freq=902.6;
			jumpFreq=0.2;
			break;
		case 0x02:
			NumofFreq=11;
			Freq=865.6;
			jumpFreq=0.2;
			break;
		case 0x03:
			NumofFreq=8;
			Freq=902.6;
			jumpFreq=3.6;
			break;
		default:
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
		}

		m_ReadInterval.AddString("30ms");
		m_ReadInterval.AddString("50ms");
		m_ReadInterval.AddString("100ms");

		break;
	case 0x15:
		switch(m_SoftVersion & 0xFF)
		{
		case 0x00:
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
			break;
		case 0x01:
			NumofFreq=125;
			Freq=902.6;
			jumpFreq=0.2;
			break;
		case 0x02:
			NumofFreq=11;
			Freq=865.6;
			jumpFreq=0.2;
			break;
		case 0x03:
			NumofFreq=8;
			Freq=902.6;
			jumpFreq=3.6;
			break;
		default:
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
		}

		m_ReadInterval.AddString("10ms");
		m_ReadInterval.AddString("30ms");
		m_ReadInterval.AddString("50ms");	

		break;
	case 0x16:
		if (((m_SoftVersion>>8) & 0xFF) > 0x05)
		{
			switch(m_SoftVersion & 0xFF)
			{
			case 0x00:
				NumofFreq=63;
				Freq=902.6;
				jumpFreq=0.4;
				break;
			case 0x01:
				NumofFreq=125;
				Freq=902.6;
				jumpFreq=0.2;
				break;
			case 0x02:
				NumofFreq=11;
				Freq=865.6;
				jumpFreq=0.2;
				break;
			case 0x03:
				NumofFreq=8;
				Freq=902.6;
				jumpFreq=3.6;
				break;
			case 0x04:
				NumofFreq=10;
				Freq=952.2;
				jumpFreq=0.2;
			default:
				NumofFreq=63;
				Freq=902.6;
				jumpFreq=0.4;
			}
		}
		else
		{
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
		}

		m_ReadInterval.AddString("10ms");
		m_ReadInterval.AddString("30ms");
		m_ReadInterval.AddString("50ms");	

		break;
	case 0x18:
		switch(m_SoftVersion & 0xFF)
		{
		case 0x0A:
			NumofFreq=8;
			Freq=902.6;
			jumpFreq=3.6;
			break;
		default:
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
		}

		m_ReadInterval.AddString("30ms");
		m_ReadInterval.AddString("50ms");
		m_ReadInterval.AddString("100ms");
		break;
	case 0x1A:
	case 0x01:
	case 0x0A:
	case 0x0B:
		switch(m_SoftVersion & 0xFF)
		{
		case 0x00:
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
			break;
		case 0x01:
			NumofFreq=125;
			Freq=902.6;
			jumpFreq=0.2;
			break;
		case 0x02:
			NumofFreq=11;
			Freq=865.5;
			jumpFreq=0.2;
			break;
		case 0x03:
			NumofFreq=8;
			Freq=902.6;
			jumpFreq=3.6;
			break;
		case 0x04:
			NumofFreq=10;
			Freq=952.2;
			jumpFreq=0.2;
			break;
		case 0x05:
			NumofFreq=42;
			Freq=919.2;
			jumpFreq=0.2;
			break;
		case 0x06:
			NumofFreq=16;
			Freq=920.625;
			jumpFreq=0.25;
			ischina=TRUE;
			break;
//º«¹ú
		case 0x07:
			NumofFreq=16;
			Freq=910.5;
			jumpFreq=0.2;
			break;
		case 0x08:
			NumofFreq=50;
			Freq=902.75;
			jumpFreq=0.5;
			AM=TRUE;
			break;
		case 0x09:
			NumofFreq=16;
			Freq=840.625;
			jumpFreq=0.25;
			ischina=TRUE;
			break;
		default:
			NumofFreq=63;
			Freq=902.6;
			jumpFreq=0.4;
		}

		m_ReadInterval.AddString("10ms");
		m_ReadInterval.AddString("30ms");
		m_ReadInterval.AddString("50ms");	

		break;
	}
	for(int i=0; i<NumofFreq; i++)
	{
		char temp[32];
		if (ischina)
		{
			sprintf(temp, "%d:%7.3f",i+1, Freq+i*jumpFreq);
		
		}
		else
		{
			if(AM==TRUE)
			{
				sprintf(temp, "%d:%5.2f",i+1, Freq+i*jumpFreq);
			}
			else
			{
				sprintf(temp, "%d:%5.1f",i+1, Freq+i*jumpFreq);
			}
		
		}
		m_MinFrequency.AddString(temp);
		m_MaxFrequency.AddString(temp);
	}
	UpdateStatus();

/*	CString str;
	str.Format("%02d%02d",(m_HardVersion>>8) & 0xFF,m_HardVersion & 0xFF);
	m_HardVer=str;
	str.Format("%02d%02d",(m_SoftVersion>>8) & 0xFF,m_SoftVersion & 0xFF);
	m_SoftVer=str;

	BOOL rec;
	rec=ReadParameter();
	if (rec!=TRUE)
		MessageBox("Read Reader Parameter Fail!","Warning",MB_ICONWARNING);
	UpdateStatus();
*/


#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReaderParameter::OnButton1() 
{
#if 0
	UpdateData(TRUE);

	apiReturn res;
	Reader1000Param ReaderParam;
	int Port;
	BYTE IP_Address[4],Mask[4],Gateway[4],readerMAC[6];
	int i;
	CString str="";

	DWORD dwIPAddress;
	m_HostIPAddress.GetAddress(dwIPAddress);

	if (m_MinFrequency.GetCurSel()>m_MaxFrequency.GetCurSel())
	{
		MessageBox("The Min of Frequency cannot be greater than the Max of Frequency!!","Notice",MB_ICONERROR);
		return;
	}

	if ((m_Power1<0) || (m_Power1>160))
	{
		MessageBox("Please input Power between 0 and 160!","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT1))->SetSel(0,-1);
		return;
	}

	if ((m_Power2<0) || (m_Power2>160))
	{
		MessageBox("Please input Power between 0 and 160!","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT2))->SetSel(0,-1);
		return;
	}
	if((m_AddressReader<1) || (m_AddressReader>254))
	{
		MessageBox("Please input Reader Address between 1 and 254 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT10)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT10))->SetSel(0,-1);
		return;
	}

	if ((m_NumofCard<1) || (m_NumofCard>100))
	{
		MessageBox("Please input Max Tags of once Reading between 1 and 100 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT6)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
		return;
	}
	switch(m_TagType)
	{
	case 0:
	case 2:
		if ((m_IDStart<0) || (m_IDStart>4))
		{
			MessageBox("Please input Start Address of ID between 0 and 4 !","Notice",MB_ICONERROR);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			return;
		}
		break;
	case 1:
		if ((m_IDStart<0) || (m_IDStart>8))
		{
			MessageBox("Please input Start Address of ID between 0 and 8 !","Notice",MB_ICONERROR);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			return;
		}
		break;
	}
	if ((m_WiegandWidth<1) || (m_WiegandWidth>255))
	{
		MessageBox("Please input Pulse Width between 1 and 255 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		return;
	}
	if ((m_WiegandInterval<1) || (m_WiegandInterval>255))
	{
		MessageBox("Please input Pulse Interval between 1 and 255 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT4)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
		return;
	}
	if(m_OutMode==1)
	{
		if(m_StandardTime>255||m_StandardTime<1)
		{
			MessageBox("Please input Interval of Reading for Standard between 1 and 255 !","Error",MB_ICONERROR);
			GetDlgItem(IDC_EDIT9)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT9))->SetSel(0,-1);
			return;
		}
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
		MessageBox("Please choose Antenna!","Notice",MB_ICONERROR);
		return;
	}
//·äÃùÆ÷
	EnableBuzzer=1;
	if(!m_EnableBuzzer)
	{
		EnableBuzzer=0;
	}
	if(m_RS485)
	{
		EnableBuzzer+=8;
	}
	

	switch(m_TagType)
	{
	case 0:
		TagType=1;
		break;
	case 1:
		TagType=4;
		break;
	case 2:
		TagType=8;
		break;
	case 3:
		TagType=2;
		break;
	}
	/*TagType = 0;
	if(m_ISO6B)
		TagType += 1;
	if(m_EPCC1)
		TagType += 2;
	if(m_EPCC1G2)
		TagType += 4;
	if(m_TK900)
		TagType += 8;
	if (TagType == 0)
	{
		MessageBox("Please choose TagType!","Notice",MB_ICONERROR);
		return;
	}*/

	ReaderParam.WorkMode = m_WorkMode;
	ReaderParam.Power = m_Power1;
	ReaderParam.Power2 = m_Power2;
	ReaderParam.TagType = TagType;
	ReaderParam.NumofCard = m_NumofCard;
	ReaderParam.Antenna = Antenna;
	ReaderParam.OutInterface = m_OutInterface;
	ReaderParam.WiegandWidth = m_WiegandWidth;
	ReaderParam.WiegandInterval = m_WiegandInterval;
	ReaderParam.ID_Start = m_IDStart;
	ReaderParam.IDPosition = m_IDPosition;
	ReaderParam.StandardTime=m_StandardTime;
//	ReaderParam.IDPosition = 0;
	ReaderParam.OutMode = m_OutMode;
	ReaderParam.BaudRate = m_BaudRate.GetCurSel()+4;
	ReaderParam.Min_Frequence = m_MinFrequency.GetCurSel()+1;
	ReaderParam.Max_Frequence = m_MaxFrequency.GetCurSel()+1;
	ReaderParam.ReadInterval = m_ReadInterval.GetCurSel();
	ReaderParam.EnableBuzzer=EnableBuzzer;
	ReaderParam.ReaderAddress=m_AddressReader;
	ifAddress=m_RS485;

	if(ifAddress)
		RS485Address=ReaderParam.ReaderAddress ;
	else
		RS485Address=0;

	ReaderParam.HostIP1=HIBYTE(HIWORD(dwIPAddress));
	ReaderParam.HostIP2=LOBYTE(HIWORD(dwIPAddress));
	ReaderParam.HostIP3=HIBYTE(LOWORD(dwIPAddress));
	ReaderParam.HostIP4=LOBYTE(LOWORD(dwIPAddress));
	ReaderParam.HostPort1=(m_HostPort>>8) & 0xFF;
	ReaderParam.HostPort2=m_HostPort & 0xFF;
	ReaderParam.IfTestValidity=m_CheckAuthorization;

	if (((m_HardVersion>>8) & 0xFF)==0x18 || ((m_HardVersion>>8) & 0xFF)==0x1A)
	{
		ReaderParam.ReadDuration = (BYTE)(m_ReadCycle.GetCurSel()<<4)+(BYTE)m_ReadDuration.GetCurSel();
	}

	if ((((m_HardVersion>>8) & 0xFF)==0x14) && (((m_SoftVersion>>8) & 0xFF)==0x50))
	{
		if (m_Modulation)
			ReaderParam.Modulation = 0x01;
		else
			ReaderParam.Modulation = 0x00;

		if (m_TXMode)
		{
			ReaderParam.TX_Mode = 0x01;
			ifTXMode=TRUE;
		}
		else
		{
			ReaderParam.TX_Mode = 0x00;
			ifTXMode=FALSE;
		}
	}

	if ((((m_HardVersion>>8) & 0xFF)==0x1A) && (((m_SoftVersion>>8) & 0xFF)==0x50))
	{
		if (m_TXMode)
		{
			ReaderParam.TX_Mode = 0x01;
			ifTXMode=TRUE;
		}
		else
		{
			ReaderParam.TX_Mode = 0x00;
			ifTXMode=FALSE;
		}
	}

	for(i=0;i<3;i++)
	{
		Sleep(150);
		switch(ConnectMode)
		{
		case 0:
			res=Net_WriteParam(m_hSocket,&ReaderParam);
			break;
		case 1:
			res=WriteParam(m_hScanner,&ReaderParam,RS485Address);
			break;
		}
		if (res==_OK)
			break;
	}
	if (res!=_OK)
	{
		MessageBox("Error of Update Reader Parameter!","Notice",MB_ICONERROR);
		return;
	}

	int br[]={9600,19200,38400,57600,115200};
	int baud=br[ReaderParam.BaudRate-4];
	DCB dcb;
	GetCommState(m_hScanner, &dcb);
	dcb.BaudRate = baud;
	SetCommState(m_hScanner, &dcb);

	PurgeComm(m_hScanner, PURGE_TXCLEAR);	// flush transimition queue
	PurgeComm(m_hScanner, PURGE_RXCLEAR);	// flush receiveing queue

	Sleep(500);

	if(((m_SoftVersion>>8) & 0xFF) > 59)
	{
		m_ReaderIPAddress.GetAddress(IP_Address[0],IP_Address[1],IP_Address[2],IP_Address[3]);
		m_ReaderIPMask.GetAddress(Mask[0],Mask[1],Mask[2],Mask[3]);
		m_ReaderGateway.GetAddress(Gateway[0],Gateway[1],Gateway[2],Gateway[3]);
		Port=m_ReaderPort;
		
		for(i=0;i<3;i++)
		{
			Sleep(150);
			switch(ConnectMode)
			{
			case 0:
				res=Net_SetReaderNetwork(m_hSocket,IP_Address,Port,Mask,Gateway);
				break;
			case 1:
				res=SetReaderNetwork(m_hScanner,IP_Address,Port,Mask,Gateway);
				break;
			}
			if (res==_OK)
				break;
		}
		if (res!=_OK)
		{
			MessageBox("Set Net Parameter Fail!","Error",MB_ICONERROR);
			return;
		}

		str="";
		if (strlen(m_ReaderMAC)<12)
		{
			MessageBox("Please input unabridged MAC!","Error",MB_ICONERROR);
			return;
		}
		str=m_ReaderMAC.SpanIncluding("0123456789ABCDEFabcdef");
		if(strlen(str)!=strlen(m_ReaderMAC))
		{
			MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
			GetDlgItem(IDC_EDIT13)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT13))->SetSel(0,-1);
			UpdateData(FALSE);
			return;
		}
		str=m_ReaderMAC;

		for(i=0;i<6;i++)
		{
			readerMAC[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
		}

		for(i=0;i<3;i++)
		{
			Sleep(150);
			switch(ConnectMode)
			{
			case 0:
				res=Net_SetReaderMAC(m_hSocket,readerMAC);
				break;
			case 1:
				res=SetReaderMAC(m_hScanner,readerMAC);
				break;
			}
			if (res==_OK)
				break;
		}
		if (res!=_OK)
		{
			MessageBox("Set Net Parameter Fail!","Error",MB_ICONERROR);
			return;
		}
	}

	if (((m_HardVersion>>8) & 0xFF) == 0x14)
	{
		Sleep(50);
		switch(ConnectMode)
		{
		case 0:
			res=Net_SetBaudRate(m_hSocket,baud);
			break;
		case 1:
			res=SetBaudRate(m_hScanner,baud,RS485Address);
			break;
		}
		if (res!=_OK)
		{
			MessageBox("Set BaudRate unsuccessfully! Please try again!","Notice",MB_ICONERROR);
			return;
		}
	}

	switch(ConnectMode)
	{
	case 0:
		res=Net_Reboot(m_hSocket);
		break;
	case 1:
		res=Reboot(m_hScanner,RS485Address);
		break;
	}

	if(res == _OK)
	{
		MessageBox("Success of Update Reader Parameter!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Error of Reboot Reader!","Notice",MB_ICONERROR);
	}
#endif

}

void CReaderParameter::OnButton2() 
{
#if 0
	UpdateData(TRUE);

	apiReturn res	=	_no_scanner;
	Reader1000Param ReaderParam;
	DWORD dwIPAddress;
	m_HostIPAddress.GetAddress(dwIPAddress);

	if (m_MinFrequency.GetCurSel()>m_MaxFrequency.GetCurSel())
	{
		MessageBox("The Min of Frequency cannot be greater than the Max of Frequency!!","Notice",MB_ICONERROR);
		return;
	}

	if ((m_Power1<0) || (m_Power1>160))
	{
		MessageBox("Please input Power between 0 and 160!","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT1)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT1))->SetSel(0,-1);
		return;
	}

	if ((m_Power2<0) || (m_Power2>160))
	{
		MessageBox("Please input Power between 0 and 160!","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT2))->SetSel(0,-1);
		return;
	}

	if((m_AddressReader<1) || (m_AddressReader>254))
	{
		MessageBox("Please input Reader Address between 1 and 254 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT10)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT10))->SetSel(0,-1);
		return;
	}

	if ((m_NumofCard<1) || (m_NumofCard>100))
	{
		MessageBox("Please input Max Tags of once Reading between 1 and 100 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT6)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
		return;
	}
	switch(m_TagType)
	{
	case 0:
	case 2:
		if ((m_IDStart<0) || (m_IDStart>4))
		{
			MessageBox("Please input Start Address of ID between 0 and 4 !","Notice",MB_ICONERROR);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			return;
		}
		break;
	case 1:
		if ((m_IDStart<0) || (m_IDStart>8))
		{
			MessageBox("Please input Start Address of ID between 0 and 8 !","Notice",MB_ICONERROR);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT5))->SetSel(0,-1);
			return;
		}
		break;
	}
	if ((m_WiegandWidth<1) || (m_WiegandWidth>255))
	{
		MessageBox("Please input Pulse Width between 1 and 255 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT3)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
		return;
	}
	if ((m_WiegandInterval<1) || (m_WiegandInterval>255))
	{
		MessageBox("Please input Pulse Interval between 1 and 255 !","Notice",MB_ICONERROR);
		GetDlgItem(IDC_EDIT4)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT4))->SetSel(0,-1);
		return;
	}
	if(m_OutMode==1)
	{
		if(m_StandardTime>255||m_StandardTime<1)
		{
			MessageBox("Please input Interval of Reading for Standard between 1 and 255 !","Error",MB_ICONERROR);
			GetDlgItem(IDC_EDIT9)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT9))->SetSel(0,-1);
			return;
		}
	}
//·äÃùÆ÷
	EnableBuzzer=1;
	if(!m_EnableBuzzer)
	{
		EnableBuzzer=0;
	}

	if(m_RS485)
	{
		EnableBuzzer+=8;
	}

	ifAddress=m_RS485;

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
		MessageBox("Please choose Antenna!","Notice",MB_ICONERROR);
		return;
	}

	switch(m_TagType)
	{
	case 0:
		TagType=1;
		break;
	case 1:
		TagType=4;
		break;
	case 2:
		TagType=8;
		break;
	case 3:
		TagType=2;
		break;
	}
	/*TagType = 0;
	if(m_ISO6B)
		TagType += 1;
	if(m_EPCC1)
		TagType += 2;
	if(m_EPCC1G2)
		TagType += 4;
	if(m_TK900)
		TagType += 8;
	if (TagType == 0)
	{
		MessageBox("Please choose TagType!","Notice",MB_ICONERROR);
		return;
	}*/

	ReaderParam.WorkMode = m_WorkMode;
	ReaderParam.Power = m_Power1;
	ReaderParam.Power2 = m_Power2;
	ReaderParam.TagType = TagType;
	ReaderParam.NumofCard = m_NumofCard;
	ReaderParam.Antenna = Antenna;
	ReaderParam.OutInterface = m_OutInterface;
	ReaderParam.WiegandWidth = m_WiegandWidth;
	ReaderParam.WiegandInterval = m_WiegandInterval;
	ReaderParam.ID_Start = m_IDStart;
	ReaderParam.IDPosition = m_IDPosition;
	ReaderParam.StandardTime=m_StandardTime;
//	ReaderParam.IDPosition = 0;
	ReaderParam.OutMode = m_OutMode;
	ReaderParam.BaudRate = m_BaudRate.GetCurSel()+4;
	ReaderParam.Min_Frequence = m_MinFrequency.GetCurSel()+1;
	ReaderParam.Max_Frequence = m_MaxFrequency.GetCurSel()+1;
	ReaderParam.ReadInterval = m_ReadInterval.GetCurSel();
	ReaderParam.ReaderAddress=m_AddressReader;
	//ReaderParam.ReadDuration = (BYTE)(m_ReadCycle.GetCurSel()<<4)+(BYTE)m_ReadDuration.GetCurSel();
	ReaderParam.EnableBuzzer=EnableBuzzer;
	ReaderParam.HostIP1=HIBYTE(HIWORD(dwIPAddress));
	ReaderParam.HostIP2=LOBYTE(HIWORD(dwIPAddress));
	ReaderParam.HostIP3=HIBYTE(LOWORD(dwIPAddress));
	ReaderParam.HostIP4=LOBYTE(LOWORD(dwIPAddress));
	ReaderParam.HostPort1=(m_HostPort>>8) & 0xFF;
	ReaderParam.HostPort2=m_HostPort & 0xFF;
	ReaderParam.IfTestValidity=m_CheckAuthorization;

	if(ifAddress)
		RS485Address=m_AddressReader ;
	else
		RS485Address=0;

	if (((m_HardVersion>>8) & 0xFF)==0x18 || ((m_HardVersion>>8) & 0xFF)==0x1A)
	{
		ReaderParam.ReadDuration = (BYTE)(m_ReadCycle.GetCurSel()<<4)+(BYTE)m_ReadDuration.GetCurSel();
	}

	if ((((m_HardVersion>>8) & 0xFF)==0x14) && (((m_SoftVersion>>8) & 0xFF)==0x01))
	{
		if (m_Modulation)
			ReaderParam.Modulation = 0x01;
		else
			ReaderParam.Modulation = 0x00;

		if (m_TXMode)
			ReaderParam.TX_Mode = 0x01;
		else
			ReaderParam.TX_Mode = 0x00;
	}

	switch(ConnectMode)
	{
	case 0:
//		res=Net_WriteFactoryParameter(m_hSocket,&ReaderParam);
		break;
	case 1:
//		res=WriteFactoryParameter(m_hScanner,&ReaderParam);
		break;
	}
	if(res == _OK)
	{
		MessageBox("Success of Set Factory Parameter!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Error of Set Factory Parameter!","Notice",MB_ICONERROR);
	}
#endif

}

void CReaderParameter::OnButton3() 
{
	int i,j,k;
	int br[]={115200,57600,38400,19200,9600};
	COMMTIMEOUTS  cto;
	DCB dcb;
	WORD m_HardVer,m_SoftVer;
	
	k=MessageBox("Do you Determine to recover the factory parameter?","Notice",MB_OKCANCEL|MB_ICONWARNING);
	if (k!=1) 
		return;

	CProgress *dlg=new CProgress;
	dlg->Create(IDD_PROGRESS_DIALOG,this);
	dlg->m_Progress.SetRange(0,100);
	dlg->m_Progress.SetPos(5);

	apiReturn res;
	for(i=0;i<5;i++)
	{
		Sleep(150);
		PurgeComm(m_hScanner, PURGE_TXCLEAR);	// flush transimition queue
		PurgeComm(m_hScanner, PURGE_RXCLEAR);	// flush receiveing queue

		switch(ConnectMode)
		{
		case 0:
//			res=Net_ReadFactoryParameter(m_hSocket);
			break;
		case 1:
//			res=ReadFactoryParameter(m_hScanner);
			break;
		}
		if (res=_OK)
			break;
	}
	if (res!=_OK)
	{
		Sleep(200);
		dlg->DestroyWindow();
		MessageBox("Error of Read Factory Parameter!","Notice",MB_ICONERROR);
		return;
	}

	dlg->m_Progress.SetPos(10);

	Sleep(500);

	GetCommTimeouts(m_hScanner, &cto);
    cto.ReadIntervalTimeout = 100;
    cto.ReadTotalTimeoutMultiplier = 20 ;
    cto.ReadTotalTimeoutConstant = 200 ;
    cto.WriteTotalTimeoutMultiplier = 20 ;
    cto.WriteTotalTimeoutConstant = 200 ;
	SetCommTimeouts(m_hScanner, &cto);

	for (i=0; i<5; i++)
	{
		dlg->m_Progress.SetPos(10+5*(i+1));

		Sleep(100);

		GetCommState(m_hScanner, &dcb);
		dcb.BaudRate = br[i];
		SetCommState(m_hScanner, &dcb);
	
		PurgeComm(m_hScanner, PURGE_TXCLEAR);	// flush transimition queue
		PurgeComm(m_hScanner, PURGE_RXCLEAR);	// flush receiveing queue
		
		for(j=0;j<3;j++)
		{
			Sleep(30);
			switch(ConnectMode)
			{
			case 0:
				res=Net_GetReaderVersion(m_hSocket,&m_HardVer,&m_SoftVer);
				break;
			case 1:
				res=GetReaderVersion(m_hScanner,&m_HardVer,&m_SoftVer,RS485Address);
				break;
			}
			if (res == _OK)
				break;		
		}
		if (res==_OK)
			break;
	}

	dlg->m_Progress.SetPos(50);

	Sleep(100);
	switch(ConnectMode)
	{
	case 0:
		res=Net_Reboot(m_hSocket);
		break;
	case 1:
		res=Reboot(m_hScanner,RS485Address);
		break;
	}
	if (res!=_OK)
	{
		k=10;
	}

	Sleep(500);

	for (i=0; i<5; i++)
	{
		dlg->m_Progress.SetPos(50+5*(i+1));

		Sleep(200);
		
		GetCommState(m_hScanner, &dcb);
		dcb.BaudRate = br[i];
		SetCommState(m_hScanner, &dcb);
		
		for(j=0;j<3;j++)
		{
			Sleep(100);
			PurgeComm(m_hScanner, PURGE_TXCLEAR);	// flush transimition queue
			PurgeComm(m_hScanner, PURGE_RXCLEAR);	// flush receiveing queue

			switch(ConnectMode)
			{
			case 0:
				res=Net_GetReaderVersion(m_hSocket,&m_HardVer,&m_SoftVer);
				break;
			case 1:
				res=GetReaderVersion(m_hScanner,&m_HardVer,&m_SoftVer,RS485Address);
				break;
			}
			if (res == _OK)
				break;		
		}
		if (res==_OK)
			break;
	}

	if (k==10)
	{
		dlg->DestroyWindow();
		MessageBox("Error of Reboot Reader!","Notice",MB_ICONERROR);
		return;
	}

	dlg->m_Progress.SetPos(75);

	GetCommTimeouts(m_hScanner, &cto);
    cto.ReadIntervalTimeout = 500;
    cto.ReadTotalTimeoutMultiplier = 100 ;
    cto.ReadTotalTimeoutConstant = 1000 ;
    cto.WriteTotalTimeoutMultiplier = 100 ;
    cto.WriteTotalTimeoutConstant = 1000 ;
	SetCommTimeouts(m_hScanner, &cto);

	BOOL rec;
	rec=ReadParameter();
	if (rec!=TRUE)
	{
		dlg->DestroyWindow();
		MessageBox("Error of Read Reader Parameter!\nPlease Reboot Reader!","Warning",MB_ICONWARNING);
		return;
	}

	dlg->m_Progress.SetPos(90);

	Sleep(100);
	switch(ConnectMode)
	{
	case 0:
		res=Net_Reboot(m_hSocket);
		break;
	case 1:
		res=Reboot(m_hScanner,RS485Address);
		break;
	}
	dlg->m_Progress.SetPos(100);
	Sleep(200);
	UpdateStatus();
	dlg->DestroyWindow();
	if(res == _OK)
		MessageBox("Success of Read Factory Parameter!","Notice",MB_ICONINFORMATION);
	else
		MessageBox("Error of Reboot Reader!","Notice",MB_ICONERROR);
}

void CReaderParameter::OnButton4() 
{
	apiReturn res;

	UpdateData(TRUE);

	int Relay=0;
	if (m_Relay1==TRUE)
		Relay+=1;
    if (m_Relay2==TRUE)
		Relay+=2;
	switch(ConnectMode)
	{
	case 0:
	    res=Net_SetRelay(m_hSocket,Relay);	
		break;
	case 1:
	    res=SetRelay(m_hScanner,Relay,RS485Address);	
		break;
	}
	if(res == _OK)
	{
		MessageBox("Set Relay successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
        MessageBox("Set Relay unsuccessfully! Please try again!","Notice",MB_ICONERROR);
	}	
}

void CReaderParameter::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
/*	GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK8)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO13)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO14)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO10)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO11)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO12)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO15)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	switch(m_OutMode)
	{
	case 0:
		GetDlgItem(IDC_COMBO4)->EnableWindow(TRUE);
		break;
	case 1:
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		break;
	}
	UpdateStatus();
*/	
}

void CReaderParameter::OnRadio2() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);
	GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK8)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO10)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO11)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO12)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO15)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	UpdateStatus();
	GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO13)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
*/
 }

void CReaderParameter::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
/*	GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK7)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK8)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO13)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO10)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO11)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO12)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO15)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);	
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

  */
  }

void CReaderParameter::OnRadio13() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
//	GetDlgItem(IDC_Standard_STATIC)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_COMBO4)->EnableWindow(TRUE);

}

void CReaderParameter::OnRadio14() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
//	GetDlgItem(IDC_Standard_STATIC)->ShowWindow(SW_SHOW);
//	GetDlgItem(IDC_EDIT9)->ShowWindow(SW_SHOW);
	
}

void CReaderParameter::OnCheck14() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(ifAddress)
		RS485Address=m_AddressReader ;
	else
		RS485Address=0;

	UpdateData(FALSE);
}

void CReaderParameter::OnButton5() 
{
	apiReturn res;
	CString str;
	ReaderDate time;

	m_ReaderTime.ResetContent();

	switch(ConnectMode)
	{
	case 0:
		res=Net_GetReaderTime(m_hSocket,&time);
		break;
	case 1:
		res=GetReaderTime(m_hScanner,&time,RS485Address);	
		break;
	}
	
	if(res == _OK)
	{
		str.Format("Reader Time:%02d-%02d-%02d %02d:%02d:%02d",time.Year,time.Month,time.Day,time.Hour,time.Minute,time.Second);
		m_ReaderTime.AddString(str);
	}
	else
	{
		str=ReportError(res);
		if (str=="Unbeknown Error!")
			str="Get Time Fail!";
		m_ReaderTime.AddString(str);
	}
}

void CReaderParameter::OnButton6() 
{
	apiReturn res;
	CString str;
	ReaderDate time;
	CTime m_NowTime = CTime::GetCurrentTime();
	
	m_ReaderTime.ResetContent();

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
		res=SetReaderTime(m_hScanner,&time,RS485Address);	
		break;
	}

	if(res == _OK)
	{
		m_ReaderTime.AddString("Set Time successfully!");
	}
	else
	{
		str=ReportError(res);
		if (str=="Unbeknown Error!")
			str="Set Time Fail!";
		m_ReaderTime.AddString(str);
	}
	
}

void CReaderParameter::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	if (NewConnect==1)
	{
		ReadParameter();
		NewConnect=0;
	}
	UpdateStatus();
	
}
