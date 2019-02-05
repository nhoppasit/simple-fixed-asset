// TK900Test.cpp : implementation file
//

#include "stdafx.h"
#include "ReaderDemo.h"
#include "TK900Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BYTE IDBuffer[MAX_LABELS][ID_MAX_SIZE_64BIT];
/////////////////////////////////////////////////////////////////////////////
// CTK900Test property page

IMPLEMENT_DYNCREATE(CTK900Test, CPropertyPage)

CTK900Test::CTK900Test() : CPropertyPage(CTK900Test::IDD)
{
	//{{AFX_DATA_INIT(CTK900Test)
	m_Antenna1 = TRUE;
	m_Antenna2 = FALSE;
	m_Antenna3 = FALSE;
	m_Antenna4 = FALSE;
	m_ListTagID = FALSE;
	m_Address = 0;
	m_Len = 1;
	m_Data = _T("");
	m_ReadDataBlock = FALSE;
	m_WriteDataBlock = FALSE;
	m_SAddress = 0;
	m_SLen = 1;
	m_AddressPage = 1;
	m_NumPage = 0;
	m_ListIDPage = FALSE;
	//}}AFX_DATA_INIT
}

CTK900Test::~CTK900Test()
{
}

void CTK900Test::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTK900Test)
	DDX_Control(pDX, IDC_LIST2, m_ListData);
	DDX_Control(pDX, IDC_LIST1, m_ListID);
	DDX_Control(pDX, IDC_COMBO2, m_TagID);
	DDX_Control(pDX, IDC_COMBO1, m_Interval);
	DDX_Check(pDX, IDC_CHECK1, m_Antenna1);
	DDX_Check(pDX, IDC_CHECK2, m_Antenna2);
	DDX_Check(pDX, IDC_CHECK3, m_Antenna3);
	DDX_Check(pDX, IDC_CHECK4, m_Antenna4);
	DDX_Check(pDX, IDC_CHECK5, m_ListTagID);
	DDX_Text(pDX, IDC_EDIT1, m_Address);
	DDX_Text(pDX, IDC_EDIT2, m_Len);
	DDX_Text(pDX, IDC_EDIT3, m_Data);
	DDV_MaxChars(pDX, m_Data, 8);
	DDX_Check(pDX, IDC_CHECK6, m_ReadDataBlock);
	DDX_Check(pDX, IDC_CHECK7, m_WriteDataBlock);
	DDX_Text(pDX, IDC_EDIT4, m_SAddress);
	DDX_Text(pDX, IDC_EDIT5, m_SLen);
	DDX_Text(pDX, IDC_EDIT6, m_AddressPage);
	DDX_Text(pDX, IDC_EDIT7, m_NumPage);
	DDX_Check(pDX, IDC_CHECK8, m_ListIDPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTK900Test, CPropertyPage)
	//{{AFX_MSG_MAP(CTK900Test)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTK900Test message handlers

void CTK900Test::UpdateStatus()
{
	switch(m_HardVersion & 0xFF)
	{
	case 0x0B:
		GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		break;
	case 0x0C:
		GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
		GetDlgItem(IDC_CHECK2)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		break;
	case 0x0E:
		GetDlgItem(IDC_CHECK1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
		GetDlgItem(IDC_CHECK2)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
		GetDlgItem(IDC_CHECK3)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
		GetDlgItem(IDC_CHECK4)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
		break;
	default:
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_BUTTON1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);

	GetDlgItem(IDC_CHECK5)->EnableWindow(ifConnectReader && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_CHECK6)->EnableWindow(ifConnectReader && !m_ListTagID && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_CHECK7)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_CHECK8)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock);

	GetDlgItem(IDC_COMBO1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_COMBO2)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);

	GetDlgItem(IDC_EDIT1)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_EDIT2)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_EDIT3)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_EDIT4)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_EDIT5)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_EDIT6)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
	GetDlgItem(IDC_EDIT7)->EnableWindow(ifConnectReader && !m_ListTagID && !m_ReadDataBlock && !m_WriteDataBlock && !m_ListIDPage);
}

BOOL CTK900Test::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD dwStyle = m_ListID.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_ListID.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);

	m_ListID.InsertColumn(0, "No.", LVCFMT_LEFT, 50);
	m_ListID.InsertColumn(1, "ID", LVCFMT_LEFT, 200);
	m_ListID.InsertColumn(2, "Success", LVCFMT_LEFT, 75);
	m_ListID.InsertColumn(3, "Times", LVCFMT_LEFT, 75);

	m_Interval.SetCurSel(4);

	UpdateStatus();

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTK900Test::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}

void CTK900Test::OnTimer(UINT nIDEvent) 
{
	apiReturn res;
	BYTE be_antenna;
	int i,j,k,nCounter=0;
	CString str,str_temp,str_tem;
	char temp[64];
	BYTE TK900_DB[15][8],PageDate[14],PageBuffer[9];

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
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=1;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;
	
	case 6:
	case 10:
		switch (Read_times%2)
		{
		case 0:
			be_antenna=m_antenna_sel-2;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=2;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;

	case 12:
		switch (Read_times%2)
		{
		case 0:
			be_antenna=m_antenna_sel-4;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=4;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;
	
	case 7:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=4;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=1;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 2:
			be_antenna=2;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;

	case 11:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=8;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=1;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 2:
			be_antenna=2;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;

	case 13:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=8;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=1;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 2:
			be_antenna=4;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;

	case 14:
		switch (Read_times%3)
		{
		case 0:
			be_antenna=8;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=2;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 2:
			be_antenna=4;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;

	case 15:
		switch (Read_times%4)
		{
		case 0:
			be_antenna=8;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 1:
			be_antenna=1;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 2:
			be_antenna=2;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		case 3:
			be_antenna=4;
			switch(ConnectMode)
			{
			case 0:
				Net_SetAntenna(m_hSocket, be_antenna);
				break;
			case 1:
				SetAntenna(m_hScanner, be_antenna,RS485Address);
				break;
			}
			break;
		}
		break;
	}

	switch(nIDEvent)
	{
	case 1:
		switch(ConnectMode)
		{
		case 0:
			res=Net_TK900_ReadLabelID(m_hSocket,&(IDBuffer[0][0]),&nCounter);
			break;
		case 1:
			res=TK900_ReadLabelID(m_hScanner,&(IDBuffer[0][0]),&nCounter,RS485Address);
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
				for(j=0;j<ID_MAX_SIZE_64BIT;j++)
				{
					wsprintf(temp, "%02X", *(BYTE *)&IDBuffer[i][j]);
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
		break;
	case 2:
		switch(ConnectMode)
		{
		case 0:
			res=Net_TK900_ReadPageBlock(m_hSocket,IDTemp,ptr,len,&(TK900_DB[0][0]));
			break;
		case 1:
			res=TK900_ReadPageBlock(m_hScanner,IDTemp,ptr,len,&(TK900_DB[0][0]),RS485Address);
			break;
		}
		if (res==_OK)
		{
			for(i=0;i<len;i++)
			{
				str="No.";
				str_temp.Format("%02d",ptr+i);
				str+=str_temp;
				str+=" Page  HEX:";
				str_temp="str:";
				for(j=0;j<8;j++)
				{
					
					str_tem.Format("%02X",TK900_DB[i][j]);
					str+=str_tem;
					str_temp+=(char)TK900_DB[i][j];
					str+=" ";
				}
				str+=str_temp;
				m_ListData.AddString(str);
				m_ListData.AddString("------------------------------");
				m_ListData.SetCurSel(m_ListData.GetCount()-1);
			}
		}
		break;
	case 3:
		switch(ConnectMode)
		{
		case 0:
			res=Net_TK900_WritePageBlock(m_hSocket,IDTemp,ptr,DB);
			break;
		case 1:
			res=TK900_WritePageBlock(m_hScanner,IDTemp,ptr,DB,RS485Address);
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
		break;
	case 4://str_tem
		switch(ConnectMode)
		{
		case 0:
			res=Net_TK900_ListTagPage(m_hSocket, PageBuffer,PageDate);
			break;
		case 1:
			res=TK900_ListTagPage(m_hScanner, PageBuffer,PageDate,RS485Address);
			break;
		}
		k=m_ListID.GetItemCount();
		if(res==_OK)
		{
			str="";
			for(i=0;i<8;i++)
			{
				str_temp.Format("%02X",PageBuffer[i+1]);
				str+=str_temp;
			}
			str+="  ";
			for(i=0;i<PageBuffer[0]-10;i++)
			{
				str_temp=(char)PageDate[i];
				str+=str_temp;
				if(i==6)
					str+="  ";
			}
			for(j=0;j<k;j++)
			{
				m_ListID.GetItemText(j,1,temp,PageBuffer[0]*2+5);
				str_temp=temp;
				if(str == str_temp) break;
			}
			if(j==k)
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
		}
		for(i=0;i<k;i++)
			m_ListID.SetItemText(i,3,itoa(Read_times,temp,10));
		break;
	}
	
	CPropertyPage::OnTimer(nIDEvent);
}

void CTK900Test::OnCheck5() 
{
	apiReturn res;
	UpdateData(TRUE);

	int interval[]={0,10,20,30,50,100,200,500};
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
			switch(ConnectMode)
			{
			case 0:
				res=Net_SetAntenna(m_hSocket, m_antenna_sel);
				break;
			case 1:
				res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
				break;
			}
			if (res!=_OK)
			{
				MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				m_ListTagID=FALSE;
				UpdateData(FALSE);
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
//		if (ifTXMode)
//			TK900_StopTXListID(m_hScanner,RS485Address);
		
		KillTimer(1);

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
				IDBuffer[i][j]=(BYTE)strtol((CString)temp[j*2]+(CString)temp[j*2+1],NULL,16);
			}

			str.Format("%02d.",i+1);
			str+=temp;
			m_TagID.AddString(str);
		}

		m_TagID.SetCurSel(0);
	}
}

void CTK900Test::OnCheck6() 
{
	apiReturn res;
	int i;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_Address<0) || (m_Address>14))
	{
		MessageBox("Please input Location of Tag Address between 0 and 14!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_Len<1) || (m_Len>15))
	{
		MessageBox("Please input Length of Tag Data between 1 and 15!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if (m_Address+m_Len>15)
	{
		m_Len=15-m_Address;
		UpdateData(FALSE);
	}

	for(i=0;i<12;i++)
	{
		IDTemp[i]=IDBuffer[m_TagID.GetCurSel()][i];
	}

	if ((IDTemp[0] & 0x40)!=0x40)
	{
		MessageBox("The Tag can't be read and written!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}
		
	ptr=m_Address;
	len=m_Len;

	int interval[]={0,10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if (m_ReadDataBlock)
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
			case 0:
				res=Net_SetAntenna(m_hSocket, m_antenna_sel);
				break;
			case 1:
				res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
				break;
			}
			if (res!=_OK)
			{
				MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
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
	}
}

void CTK900Test::OnCheck7() 
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

	if ((m_Address<0) || (m_Address>14))
	{
		MessageBox("Please input Location of Tag Address between 0 and 14!","Warning",MB_ICONWARNING);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	int datalen=strlen(m_Data);
	if (datalen>8)
	{
		MessageBox("Please input Write Data not more than 8 BYTE!","Warning",MB_ICONWARNING);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	for(i=0;i<12;i++)
	{
		IDTemp[i]=IDBuffer[m_TagID.GetCurSel()][i];
	}

	if ((IDTemp[0] & 0x40)!=0x40)
	{
		MessageBox("The Tag can't be read and written!","Warning",MB_ICONWARNING);
		m_WriteDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	int interval[]={0,10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if (m_WriteDataBlock)
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
			m_WriteDataBlock=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			switch(ConnectMode)
			{
			case 0:
				res=Net_SetAntenna(m_hSocket, m_antenna_sel);
				break;
			case 1:
				res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
				break;
			}
			if (res!=_OK)
			{
				MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				m_WriteDataBlock=FALSE;
				UpdateData(FALSE);
				return;
			}
			break;
		}

		int protect;
		for(i=0;i<30;i++)
		{
			Sleep(50);
			switch(ConnectMode)
			{
			case 0:
				res=Net_TK900_GetProtect(m_hSocket,IDTemp,&DB[0]);
				break;
			case 1:
				res=TK900_GetProtect(m_hScanner,IDTemp,&DB[0],RS485Address);
				break;
			}
			if (res==_OK)
				break;
		}
		if (res==_OK)
		{
			if (m_Address<8)
			{
				protect=(DB[1]>>m_Address) & 0x01;
			}
			else
			{
				protect=(DB[0]>>(m_Address-8)) & 0x01;
			}

			if (protect)
			{
				str.Format("Page %d is locked!",m_Address);
				MessageBox(str,"Warning",MB_ICONWARNING);
				m_WriteDataBlock=FALSE;
				UpdateData(FALSE);
				return;	
			}
		}
		else
		{
			MessageBox("No tag!Please try again!","Warning",MB_ICONWARNING);
			m_WriteDataBlock=FALSE;
			UpdateData(FALSE);
			return;	
		}

		ptr=m_Address;
		str=m_Data;
		if (datalen<8)
		{
			for(i=0;i<(8-datalen);i++)
			{
				str+=" ";
			}
		}
		for(i=0;i<8;i++)
		{
			DB[i]=str[i];
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

void CTK900Test::OnButton1() 
{
	apiReturn res;
	CString str;
	int i;

	m_ListData.ResetContent();
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_SAddress<0) || (m_SAddress>15))
	{
		MessageBox("Please input Location of Tag Page between 0 and 15!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_SLen<1) || (m_SLen>15))
	{
		MessageBox("Please input Length of Tag Page between 1 and 15!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	for(i=0;i<12;i++)
	{
		IDTemp[i]=IDBuffer[m_TagID.GetCurSel()][i];
	}

	if ((IDTemp[0] & 0x40)!=0x40)
	{
		MessageBox("The Tag can't be sitten protection!","Warning",MB_ICONWARNING);
		return;
	}

	ptr=m_SAddress;
	len=m_SLen;

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
		case 0:
			res=Net_SetAntenna(m_hSocket, m_antenna_sel);
			break;
		case 1:
			res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
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

	int protect;
	for(i=0;i<30;i++)
	{
		Sleep(50);
		switch(ConnectMode)
		{
		case 0:
			res=Net_TK900_GetProtect(m_hSocket,IDTemp,&DB[0]);
			break;
		case 1:
			res=TK900_GetProtect(m_hScanner,IDTemp,&DB[0],RS485Address);
			break;
		}
		if (res==_OK)
			break;
	}
	if (res==_OK)
	{
		if (m_SAddress<8)
		{
			protect=(DB[1]>>m_SAddress) & 0x01;
		}
		else
		{
			protect=(DB[0]>>(m_SAddress-8)) & 0x01;
		}

		if (protect)
		{
			str.Format("Page %d is locked!",m_SAddress);
			MessageBox(str,"Warning",MB_ICONWARNING);
			return;
		}
	}
	else
	{
		MessageBox("No tag!Please try again!","Warning",MB_ICONWARNING);
		return;	
	}
	
	str.Format("Do you determine to set protecrt page %d?",m_SAddress);
	int k=MessageBox(str,"Notice",MB_OKCANCEL|MB_ICONWARNING);
	if (k!=1) 
		return;

	res=TK900_SetProtect(m_hScanner,IDTemp,ptr,len,RS485Address);
	if (res==_OK)
	{
		m_ListData.AddString("SetProtect Successfully!");
	}
	else
	{
		m_ListData.AddString("SetProtect Fail!");
	}
}

void CTK900Test::OnButton2() 
{
	apiReturn res;
	int i;

	m_ListData.ResetContent();
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	if ((m_SAddress<0) || (m_SAddress>15))
	{
		MessageBox("Please input Location of Tag Page between 0 and 15!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	for(i=0;i<12;i++)
	{
		IDTemp[i]=IDBuffer[m_TagID.GetCurSel()][i];
	}

	if ((IDTemp[0] & 0x40)!=0x40)
	{
		MessageBox("The Tag can't be gotten protection!","Warning",MB_ICONWARNING);
		return;
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
		case 0:
			res=Net_SetAntenna(m_hSocket, m_antenna_sel);
			break;
		case 1:
			res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
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
	
	int protect;
	for(i=0;i<30;i++)
	{
		Sleep(50);
		switch(ConnectMode)
		{
		case 0:
			res=Net_TK900_GetProtect(m_hSocket,IDTemp,&DB[0]);
			break;
		case 1:
			res=TK900_GetProtect(m_hScanner,IDTemp,&DB[0],RS485Address);
			break;
		}
		if (res==_OK)
			break;
	}
	if (res==_OK)
	{
		if (m_SAddress<8)
		{
			protect=(DB[1]>>m_SAddress) & 0x01;
		}
		else
		{
			protect=(DB[0]>>(m_SAddress-8)) & 0x01;
		}

		CString str;
		char temp[32];
		str="Page ";
		str+=itoa(m_SAddress,temp,10);
		if (protect)
		{
			str+=" is locked.";
		}
		else
		{
			str+=" is unlocked.";
		}

		m_ListData.AddString(str);
	}
	else
	{
		m_ListData.AddString("GetProtect Fail!");
	}
}

void CTK900Test::OnButton3() 
{
	// TODO: Add your control notification handler code here
	apiReturn res;
	int i;
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		return;
	}
	if(m_AddressPage>7 || m_AddressPage<1)
	{
		MessageBox("Please input Address of Page between 1 and 7!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT6)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT6))->SetSel(0,-1);
		UpdateData(FALSE);
		return;
	}
	if(m_NumPage>2 || m_AddressPage<0)
	{
		MessageBox("Please input Number of Page between 0 and 2!","Warning",MB_ICONWARNING);
		GetDlgItem(IDC_EDIT7)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT7))->SetSel(0,-1);
		UpdateData(FALSE);
		return;
	}
	ptr=m_AddressPage;
	len=m_NumPage;
	if((ptr+len)>7)
	{
		len=7-ptr;
	}
	for(i=0;i<12;i++)
	{
		IDTemp[i]=IDBuffer[m_TagID.GetCurSel()][i];
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
		case 0:
			res=Net_SetAntenna(m_hSocket, m_antenna_sel);
			break;
		case 1:
			res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
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

	for(i=0;i<5;i++)
	{
		res=TK900_SetTTO(m_hScanner,IDTemp,ptr,len,RS485Address);
		if(res==_OK)
			break;
	}
	if(res==_OK)
	{
		MessageBox("Set TTO State Success!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Set TTO State Fail!","Error",MB_ICONERROR);
	}

}

void CTK900Test::OnCheck8() 
{
	// TODO: Add your control notification handler code here
	//m_ListIDPage
	apiReturn res;
	UpdateData(TRUE);

	int interval[]={0,10,20,30,50,100,200,500};
	int timer_interval=interval[m_Interval.GetCurSel()];
	if (m_ListIDPage)
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
			m_ListIDPage=FALSE;
			UpdateData(FALSE);
			return;
			break;
		case 1:
		case 2:
		case 4:
		case 8:
			switch(ConnectMode)
			{
			case 0:
				res=Net_SetAntenna(m_hSocket, m_antenna_sel);
				break;
			case 1:
				res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
				break;
			}
			if (res!=_OK)
			{
				MessageBox("SetAntenna Fail!Please try again!","Warning",MB_ICONWARNING);
				m_ListIDPage=FALSE;
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
				IDBuffer[i][j]=(BYTE)strtol((CString)temp[j*2]+(CString)temp[j*2+1],NULL,16);
			}

			str.Format("%02d.",i+1);
			str+=temp;
			m_TagID.AddString(str);
		}
		m_TagID.SetCurSel(0);
				
	}
}

void CTK900Test::OnButton4() 
{
	// TODO: Add your control notification handler code here
	apiReturn res;
	int i;
	BYTE Address[2];
	CString str,strtemp;

	m_ListData.ResetContent();
	UpdateData(TRUE);

	if (m_TagID.GetCount()<1)
	{
		MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		m_ReadDataBlock=FALSE;
		UpdateData(FALSE);
		return;
	}

	for(i=0;i<12;i++)
	{
		IDTemp[i]=IDBuffer[m_TagID.GetCurSel()][i];
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
		case 0:
			res=Net_SetAntenna(m_hSocket, m_antenna_sel);
			break;
		case 1:
			res=SetAntenna(m_hScanner, m_antenna_sel,RS485Address);
			break;
		}
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

	for(i=0;i<5;i++)
	{
		res=TK900_GetTTOStartAdd(m_hScanner, IDTemp,Address,RS485Address);
		if(res==_OK)
			break;
	}
	if(res==_OK)
	{
		str.Format("TTO Tag Start Address is %02d ,",Address[0]);
		strtemp.Format("Length is %02d .",Address[1]);
		m_ListData.AddString(str+strtemp);

	}
	else
	{
		m_ListData.AddString("Get TTO Start Address and Length Fail!");
//		MessageBox("Get TTO Start Address and Length Fail!","Error",MB_ICONERROR);
	}



}

void CTK900Test::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	UpdateStatus();
	
}


