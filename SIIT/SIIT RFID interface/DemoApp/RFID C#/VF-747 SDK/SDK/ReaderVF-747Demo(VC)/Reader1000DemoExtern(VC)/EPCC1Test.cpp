// EPCC1Test.cpp : implementation file
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "EPCC1Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BYTE EPCC1_IDBuffer[MAX_LABELS][ID_MAX_SIZE_96BIT];
/////////////////////////////////////////////////////////////////////////////
// CEPCC1Test property page

IMPLEMENT_DYNCREATE(CEPCC1Test, CPropertyPage)

CEPCC1Test::CEPCC1Test() : CPropertyPage(CEPCC1Test::IDD)
{
	//{{AFX_DATA_INIT(CEPCC1Test)
	m_Antenna1 = TRUE;
	m_Antenna2 = FALSE;
	m_Antenna3 = FALSE;
	m_Antenna4 = FALSE;
	m_ReadSelectTag = 0;
	m_LAddress = 0;
	m_LLen = 0;
	m_LData = _T("");
	m_ListTagID = FALSE;
	m_TagID = _T("");
	m_ASAddress = 0;
	m_ASLen = 0;
	m_ASData = _T("");
	//}}AFX_DATA_INIT
}

CEPCC1Test::~CEPCC1Test()
{
}

void CEPCC1Test::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEPCC1Test)
	DDX_Control(pDX, IDC_COMBO1, m_Interval);
	DDX_Control(pDX, IDC_LIST1, m_ListID);
	DDX_Check(pDX, IDC_CHECK1, m_Antenna1);
	DDX_Check(pDX, IDC_CHECK2, m_Antenna2);
	DDX_Check(pDX, IDC_CHECK3, m_Antenna3);
	DDX_Check(pDX, IDC_CHECK4, m_Antenna4);
	DDX_Radio(pDX, IDC_RADIO1, m_ReadSelectTag);
	DDX_Text(pDX, IDC_EDIT1, m_LAddress);
	DDX_Text(pDX, IDC_EDIT2, m_LLen);
	DDX_Text(pDX, IDC_EDIT3, m_LData);
	DDX_Check(pDX, IDC_CHECK5, m_ListTagID);
	DDX_Text(pDX, IDC_EDIT7, m_TagID);
	DDV_MaxChars(pDX, m_TagID, 24);
	DDX_Text(pDX, IDC_EDIT4, m_ASAddress);
	DDX_Text(pDX, IDC_EDIT5, m_ASLen);
	DDX_Text(pDX, IDC_EDIT6, m_ASData);
	DDV_MaxChars(pDX, m_ASData, 24);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEPCC1Test, CPropertyPage)
	//{{AFX_MSG_MAP(CEPCC1Test)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEPCC1Test message handlers

void CEPCC1Test::UpdateStatus()
{
	switch(m_HardVersion & 0xFF)
	{
	case 0x0B:
		GetDlgItem(IDC_CHECK1)->EnableWindow(!m_ListTagID);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		break;
	case 0x0C:
		GetDlgItem(IDC_CHECK1)->EnableWindow(!m_ListTagID);
		GetDlgItem(IDC_CHECK2)->EnableWindow(!m_ListTagID);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		break;
	case 0x0E:
		GetDlgItem(IDC_CHECK1)->EnableWindow(!m_ListTagID);
		GetDlgItem(IDC_CHECK2)->EnableWindow(!m_ListTagID);
		GetDlgItem(IDC_CHECK3)->EnableWindow(!m_ListTagID);
		GetDlgItem(IDC_CHECK4)->EnableWindow(!m_ListTagID);
		break;
	}

	GetDlgItem(IDC_BUTTON1)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_COMBO1)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_EDIT1)->EnableWindow(!m_ListTagID && m_ReadSelectTag);
	GetDlgItem(IDC_EDIT2)->EnableWindow(!m_ListTagID && m_ReadSelectTag);
	GetDlgItem(IDC_EDIT3)->EnableWindow(!m_ListTagID && m_ReadSelectTag);
	GetDlgItem(IDC_EDIT4)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_EDIT5)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_EDIT6)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_EDIT7)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_RADIO1)->EnableWindow(!m_ListTagID);
	GetDlgItem(IDC_RADIO2)->EnableWindow(!m_ListTagID);
}

BOOL CEPCC1Test::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD dwStyle = m_ListID.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_ListID.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);

	m_ListID.InsertColumn(0, "No.", LVCFMT_LEFT, 50);
	m_ListID.InsertColumn(1, "EPC", LVCFMT_LEFT, 250);
	m_ListID.InsertColumn(2, "Success", LVCFMT_LEFT, 75);
	m_ListID.InsertColumn(3, "Times", LVCFMT_LEFT, 75);

	m_Interval.SetCurSel(3);

	UpdateData(FALSE);
	UpdateStatus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEPCC1Test::OnTimer(UINT nIDEvent) 
{
	apiReturn res;
	BYTE be_antenna;
	int i,j,k,nCounter=0;
	CString str,str_temp;
	char temp[64];

	Read_times++;
	switch(m_antenna_sel)
	{
	case 1:
	case 2:
	case 4:
	case 8:
		break;
	case 3:
	case 5:
	case 9:
		switch (Read_times%2)
		{
		case 0:
			be_antenna=m_antenna_sel-1;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=1;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;
	
	case 6:
	case 10:
		switch (Read_times%2)
		{
		case 0:
			be_antenna=m_antenna_sel-2;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=2;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;

	case 12:
		switch (Read_times%2)
		{
		case 0:
			be_antenna=m_antenna_sel-4;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=4;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;
	
	case 7:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=4;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=1;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 2:
			be_antenna=2;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;

	case 11:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=8;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=1;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 2:
			be_antenna=2;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;

	case 13:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=8;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=1;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 2:
			be_antenna=4;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;

	case 14:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=8;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=2;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 2:
			be_antenna=4;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;

	case 15:
		switch (Read_times%4)
		{
		case 0:
			be_antenna=8;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 1:
			be_antenna=1;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 2:
			be_antenna=2;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		case 3:
			be_antenna=4;
			SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
		break;
	}

	switch(nIDEvent)
	{
	case 1:
		switch(m_ReadSelectTag)
		{
		case 0:
			res = EPC1_ScrollAllID(m_hScanner,&(EPCC1_IDBuffer[0][0]),&nCounter);
			break;
		case 1:
			res = EPC1_ScrollID(m_hScanner,ptr,len,pValue,&(EPCC1_IDBuffer[0][0]),&nCounter);
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
				for(j=1;j<ID_MAX_SIZE_96BIT;j++)
				{
					wsprintf(temp, "%02X", *(BYTE *)&EPCC1_IDBuffer[i][j]);
					str += temp;
				}

				for(j=0;j<k;j++)
				{
					m_ListID.GetItemText(j,1,temp,25);
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
		break;
	}
	
	CPropertyPage::OnTimer(nIDEvent);
}

void CEPCC1Test::OnRadio1() 
{
	UpdateData(TRUE);
	UpdateStatus();
}

void CEPCC1Test::OnRadio2() 
{
	UpdateData(TRUE);
	UpdateStatus();
}

void CEPCC1Test::OnCheck5() 
{
	apiReturn res;
	UpdateData(TRUE);

	if ((m_LAddress<0) || (m_LAddress>95))
	{
		MessageBox("Please input Location of Tag Address between 0 and 95!","Warning",MB_ICONWARNING);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_LLen<0) || (m_LLen>96))
	{
		MessageBox("Please input Length of Tag Data between 0 and 96!","Warning",MB_ICONWARNING);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	int i;
	CString str;
	int str_len=strlen(m_LData);
	for (i=0;i<str_len;i++)
	{
		str=m_LData.SpanIncluding("0123456789ABCDEFabcdef");
		if(strlen(str) != strlen(m_LData) )
		{
			MessageBox("Please Input Hex number(0 ~ F) !","Warning",MB_ICONWARNING);
			GetDlgItem(IDC_EDIT3)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
			return;
		}
	}

	str=m_LData;
	
	if (str_len<(m_LLen*2))
	{
		for(i=0;i<(m_LLen*2-str_len);i++)
			str+="0";
	}

	ptr=m_LAddress;
	len=m_LLen;

	for(i=0;i<m_LLen;i++)
	{
		pValue[i]=(BYTE)strtol(((CString)str[i*2]+(CString)str[i*2+1]),NULL,16);
	}

	int interval[]={10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if (m_ListTagID)
	{
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
			res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			if (res!=_OK)
			{
				MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				return;
			}
			break;
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
	}	
}

void CEPCC1Test::OnButton1() 
{
	apiReturn res;
	UpdateData(TRUE);

	if ((m_ASAddress<0) || (m_ASAddress>95))
	{
		MessageBox("Please input Location of Tag Address between 0 and 95!","Warning",MB_ICONWARNING);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_ASLen<0) || (m_ASLen>96))
	{
		MessageBox("Please input Length of Tag Data between 0 and 96!","Warning",MB_ICONWARNING);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	int i;
	CString str;
	int str_len=strlen(m_ASData);
	for (i=0;i<str_len;i++)
	{
		str=m_ASData.SpanIncluding("0123456789ABCDEFabcdef");
		if(strlen(str) != strlen(m_ASData) )
		{
			MessageBox("Please Input Hex number(0 ~ F) !","Warning",MB_ICONWARNING);
			GetDlgItem(IDC_EDIT6)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
			return;
		}
	}

	str=m_ASData;
	
	if (str_len<(m_ASLen*2))
	{
		for(i=0;i<(m_ASLen*2-str_len);i++)
			str+="0";
	}

	ptr=m_ASAddress;
	len=m_ASLen;

	for(i=0;i<m_ASLen;i++)
	{
		pValue[i]=(BYTE)strtol(((CString)str[i*2]+(CString)str[i*2+1]),NULL,16);
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
		res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
		if (res!=_OK)
		{
			MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	res = EPC1_TalkID(m_hScanner,ptr,len,pValue);
	if (res==_OK)
	{
		MessageBox("Awoken Tag Successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Awoken Tag Fail!Please try again!","Warning",MB_ICONWARNING);
	}
}

void CEPCC1Test::OnButton2() 
{
	apiReturn res;
	UpdateData(TRUE);

	if ((m_ASAddress<0) || (m_ASAddress>95))
	{
		MessageBox("Please input Location of Tag Address between 0 and 95!","Warning",MB_ICONWARNING);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_ASLen<0) || (m_ASLen>96))
	{
		MessageBox("Please input Length of Tag Data between 0 and 96!","Warning",MB_ICONWARNING);
		m_ListTagID=FALSE;
		UpdateData(FALSE);
		return;
	}

	int i;
	CString str;
	int str_len=strlen(m_ASData);
	for (i=0;i<str_len;i++)
	{
		str=m_ASData.SpanIncluding("0123456789ABCDEFabcdef");
		if(strlen(str) != strlen(m_ASData) )
		{
			MessageBox("Please Input Hex number(0 ~ F) !","Warning",MB_ICONWARNING);
			GetDlgItem(IDC_EDIT6)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
			return;
		}
	}

	str=m_ASData;
	
	if (str_len<(m_ASLen*2))
	{
		for(i=0;i<(m_ASLen*2-str_len);i++)
			str+="0";
	}

	ptr=m_ASAddress;
	len=m_ASLen;

	for(i=0;i<m_ASLen;i++)
	{
		pValue[i]=(BYTE)strtol(((CString)str[i*2]+(CString)str[i*2+1]),NULL,16);
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
		res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
		if (res!=_OK)
		{
			MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	res = EPC1_QuietID(m_hScanner,ptr,len,pValue);
	if (res==_OK)
	{
		MessageBox("Sleep Tag Successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Sleep Tag Fail!Please try again!","Warning",MB_ICONWARNING);
	}
}

void CEPCC1Test::OnButton3() 
{
	apiReturn res;
	CString str;
	int i;
	UpdateData(TRUE);

	int str_len=strlen(m_TagID);
	if (str_len!=24)
	{
		MessageBox("The length of EPC is not enough!","Warning",MB_ICONWARNING);
		return;			
	}

	for (i=0;i<str_len;i++)
	{
		str=m_TagID.SpanIncluding("0123456789ABCDEFabcdef");
		if(strlen(str) != strlen(m_TagID) )
		{
			MessageBox("Please Input Hex number(0 ~ F) !","Warning",MB_ICONWARNING);
			GetDlgItem(IDC_EDIT7)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT7))->SetSel(0,-1);
			return;
		}
	}

	for (i=0;i<(str_len/2);i++)
	{
		str=(CString)m_TagID[i*2]+(CString)m_TagID[i*2+1];
		pValue[i]=(BYTE)strtol(str,NULL,16);
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
		res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
		if (res!=_OK)
		{
			MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	res = EPC1_WriteID(m_hScanner,0,96,pValue);
	if (res==_OK)
	{
		MessageBox("Write Successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Write Fail !Please Try Again!","Notice",MB_ICONERROR);
	} 
}

void CEPCC1Test::OnButton4() 
{
	UpdateData(TRUE);
	
	apiReturn res;
    int i,j,nCounter;

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
		res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
		if (res!=_OK)
		{
			MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}
	
	for(i=0;i<3;i++)
	{
		res = EPC1_ErasureID(m_hScanner);
		if (res==_OK)
		{
			res = EPC1_ScrollAllID(m_hScanner,&(EPCC1_IDBuffer[0][0]),&nCounter);
			if (res==_OK)
			{
				for(j=1;j<ID_MAX_SIZE_96BIT;j++)
				{
					if (EPCC1_IDBuffer[0][j]!=0)
					{
						MessageBox("Erase Fail!","Notice",MB_ICONERROR);
						return;
					}
				}
	
				MessageBox("Erase Successfully!","Notice",MB_ICONINFORMATION);
				return;
			}
		}
		Sleep(25);
	}

	MessageBox("Erase Fail!","Notice",MB_ICONERROR);
}

void CEPCC1Test::OnButton5() 
{
	UpdateData(TRUE);
	
	apiReturn res;
    int i,j,k,nCounter;
	CString str;
	BYTE IDTemp[MAX_LABELS][ID_MAX_SIZE_96BIT];

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
		res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
		if (res!=_OK)
		{
			MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	for (i=0;i<10;i++)
	{
		res = EPC1_ScrollAllID(m_hScanner,&(EPCC1_IDBuffer[0][0]),&nCounter);
		if (res==_OK) break;
		Sleep(25);
	}
	if (res!=_OK)
	{
		MessageBox("NO Tag !","Warning",MB_ICONWARNING);
		return;
	}
	
	k=MessageBox("Do you want to protect tag?","Notice",MB_OKCANCEL|MB_ICONWARNING);
	if (k!=1) return;

	res = EPC1_SetProtect(m_hScanner);
	if (res==_OK)
	{
		for(i=0;i<3;i++)
		{
			res = EPC1_ErasureID(m_hScanner);
			Sleep(25);
			if (res==_OK)
			{
				res = EPC1_ScrollAllID(m_hScanner,&(IDTemp[0][0]),&nCounter);
				if (res==_OK)
				{
					k=0;
					for(j=1;j<ID_MAX_SIZE_96BIT;j++)
					{
						if (IDTemp[0][j]==0)
						{
							k++;
						}
					}
	
					if (k==12)
					{
						MessageBox("WriteProtect Fail!Please Try Again!","Notice",MB_ICONINFORMATION);
						return;
					}
				}
			}
			Sleep(25);
		}
		if (res!=_OK)
		{
			MessageBox("WriteProtect Fail!Please Try Again!","Notice",MB_ICONERROR);
			return;
		}
		MessageBox("WriteProtect Successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("WriteProtect Fail!Please Try Again!","Notice",MB_ICONERROR);
	}	
}

void CEPCC1Test::OnButton6() 
{
	UpdateData(TRUE);
	
	apiReturn res;
    int i,j,k,nCounter;
	CString str;
	char temp[32];

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
		res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
		if (res!=_OK)
		{
			MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	for (i=0;i<10;i++)
	{
		res = EPC1_ScrollAllID(m_hScanner,&(EPCC1_IDBuffer[0][0]),&nCounter);
		if (res==_OK) break;
		Sleep(25);
	}
	if (res!=_OK)
	{
		MessageBox("NO Tag !","Warning",MB_ICONWARNING);
		return;
	}
	for(i=1;i<ID_MAX_SIZE_96BIT;i++)
	{
		wsprintf(temp, "%02X", *(BYTE *)&EPCC1_IDBuffer[0][i]);
		str += temp;
	}

	k=MessageBox("Do you Determine to delete tag ID?\nID:"+str,"Notice",MB_OKCANCEL|MB_ICONWARNING);
	if (k!=1) return;
	
	for(i=0;i<3;i++)
	{
		res = EPC1_KillID(m_hScanner,&(EPCC1_IDBuffer[0][1]));
		if (res==_OK)
		{
			res = EPC1_ScrollAllID(m_hScanner,&(EPCC1_IDBuffer[0][0]),&nCounter);
			if (res==_OK)
			{
				for(j=1;j<ID_MAX_SIZE_96BIT;j++)
				{
					if (EPCC1_IDBuffer[0][j]!=0)
					{
						MessageBox("Delete the Tag Fail!","Notice",MB_ICONERROR);
						return;
					}
				}
	
				MessageBox("Delete the Tag Successfully!","Notice",MB_ICONINFORMATION);
				return;
			}
		}
		Sleep(25);
	}

	MessageBox("Delete the Tag Fail!","Notice",MB_ICONERROR);
}

void CEPCC1Test::OnButton7() 
{
	apiReturn res;
	int i;
	int State;
	
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
		res = SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
		if (res!=_OK)
		{
			MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
			return;
		}
		break;
	default:
		MessageBox("Please choose only one antenna!","Warning",MB_ICONWARNING);
		return;
	}

	for (i=0;i<10;i++)
	{
		res = EPC1_GetProtect(m_hScanner,&State);
		if (res==_OK) break;
		Sleep(25);
	}
	if (res!=_OK)
	{
		MessageBox("NO Tag !","Warning",MB_ICONWARNING);
		return;
	}

	if (!State)
		MessageBox("The Tag has been written protection!","Notice",MB_ICONINFORMATION);
	else
		MessageBox("The Tag has not been written protection!","Notice",MB_ICONERROR);
}
