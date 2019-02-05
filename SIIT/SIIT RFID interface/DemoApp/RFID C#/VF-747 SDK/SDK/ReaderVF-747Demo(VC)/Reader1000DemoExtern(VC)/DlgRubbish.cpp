// DlgRubbish.cpp : implementation file
//

#include "stdafx.h"
#include "readerdemo.h"
#include "DlgRubbish.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRubbish property page

IMPLEMENT_DYNCREATE(DlgRubbish, CPropertyPage)

DlgRubbish::DlgRubbish() : CPropertyPage(DlgRubbish::IDD)
{
	//{{AFX_DATA_INIT(DlgRubbish)
	m_nSID = -1;
	//}}AFX_DATA_INIT
}

DlgRubbish::~DlgRubbish()
{
}

void DlgRubbish::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRubbish)
	DDX_Radio(pDX, IDC_RADIO0_RU1, m_nSID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRubbish, CPropertyPage)
	//{{AFX_MSG_MAP(DlgRubbish)
	ON_BN_CLICKED(IDC_BUTTON_DELRURECORD, OnButtonDelrurecord)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_GETRUID, OnButtonGetruid)
	ON_BN_CLICKED(IDC_BUTTON_SETRUID, OnButtonSetruid)
	ON_BN_CLICKED(IDC_BUTTON_SETRURECORD, OnButtonSetrurecord)
	ON_BN_CLICKED(IDC_BUTTON_GETRUALLRECORD, OnButtonGetruallrecord)
	ON_BN_CLICKED(IDC_RADIO0_RU1, OnRadio0Ru1)
	ON_BN_CLICKED(IDC_RADIO0_RU2, OnRadio0Ru2)
	ON_BN_CLICKED(IDC_RADIO0_RU3, OnRadio0Ru3)
	ON_BN_CLICKED(IDC_RADIO0_RU4, OnRadio0Ru4)
	ON_BN_CLICKED(IDC_RADIO0_RU5, OnRadio0Ru5)
	ON_BN_CLICKED(IDC_RADIO2_RU6, OnRadio2Ru6)
	ON_BN_CLICKED(IDC_RADIO2_RU7, OnRadio2Ru7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRubbish message handlers

BOOL DlgRubbish::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_RUID)->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgRubbish::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void DlgRubbish::OnButtonDelrurecord() 
{
	// TODO: Add your control notification handler code here
	//初始化
	apiReturn res	=	_no_scanner;
	int i = 0;
	int k = 0;

	k=MessageBox("Are you sure to initializes the device?","Warning",MB_OKCANCEL|MB_ICONWARNING);
	if (k!=1) 
		return;

	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res = RU_DeleteAllRecordNet(m_hSocket);
			break;
		case 1://RS232
			res = RU_DeleteAllRecord(m_hScanner, 0);
			break;
		case 2://RS485
			res = RU_DeleteAllRecord(m_hScanner, RS485Address);
			break;
		}
		if (res==_OK)
		{
			break;
		}
			
	}

	if ( _OK == res )
	{
		MessageBox("Initializes successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Initializes Fail!Please try again!","Warning",MB_ICONWARNING);
	}

	return;
}

void DlgRubbish::OnButtonGetruid() 
{
	// TODO: Add your control notification handler code here
	//得到ID
	UpdateData(TRUE);

	apiReturn res	=	_no_scanner;
	int i = 0;
	BYTE lpGetBuf[2] = {0};
	CString strTemp;
	
	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res = RU_GetReaderIDNet(m_hSocket, lpGetBuf);
			break;
		case 1://RS232
			res = RU_GetReaderID(m_hScanner, lpGetBuf, 0);
			break;
		case 2://RS485
			res = RU_GetReaderID(m_hScanner, lpGetBuf, RS485Address);
			break;
		}
		if (res==_OK)
		{
			break;
		}
		
	}
	
	if ( _OK == res )
	{
		strTemp.Format("%d", lpGetBuf[0]);
		GetDlgItem(IDC_EDIT_RUID)->SetWindowText(strTemp);


		if ( 1 <= lpGetBuf[0] && lpGetBuf[0] <= 7 )
		{
			m_nSID = lpGetBuf[0] - 1;
		}
		

		MessageBox("Get id successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Get is Fail!Please try again!","Warning",MB_ICONWARNING);
	}
	
	UpdateData(FALSE);
	return;
}

void DlgRubbish::OnButtonSetruid() 
{
	// TODO: Add your control notification handler code here
	//设置ID
	UpdateData(TRUE);

	apiReturn res	=	_no_scanner;
	int i = 0;
	BYTE lpGetBuf[2] = {0};
	CString strTemp;
	
	GetDlgItem(IDC_EDIT_RUID)->GetWindowText(strTemp);
	//strTemp.Format("%d", lpGetBuf[0]);
	//sscanf(strTemp, "%d", &lpGetBuf[0]);
	lpGetBuf[0] = (BYTE)atoi(strTemp);

	if ( 0 <= m_nSID && m_nSID <= 6 )
	{
		lpGetBuf[0] = m_nSID + 1;
	}

	//lpGetBuf[0]	=	

	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res = RU_SetReaderIDNet(m_hSocket, lpGetBuf);
			break;
		case 1://RS232
			res = RU_SetReaderID(m_hScanner, lpGetBuf, 0);
			break;
		case 2://RS485
			res = RU_SetReaderID(m_hScanner, lpGetBuf, RS485Address);
			break;
		}
		if (res==_OK)
		{
			break;
		}
		
	}
	
	if ( _OK == res )
	{
		
		MessageBox("Set id successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Set is Fail!Please try again!","Warning",MB_ICONWARNING);
	}

	UpdateData(FALSE);
	return;
}

void DlgRubbish::OnButtonSetrurecord() 
{
	// TODO: Add your control notification handler code here
	//设置记录
	apiReturn res	=	_no_scanner;
	int i = 0;
	BYTE lpGetBuf[20] = {0};
	CString strTemp;
	
	//1字节ID+6字节时间年月日时分秒

	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res = RU_GetReaderIDNet(m_hSocket, lpGetBuf);
			break;
		case 1://RS232
			res = RU_GetReaderID(m_hScanner, lpGetBuf, 0);
			break;
		case 2://RS485
			res = RU_GetReaderID(m_hScanner, lpGetBuf, RS485Address);
			break;
		}
		if (res==_OK)
		{
			break;
		}
		
	}
	
	if ( _OK == res )
	{
	
	}
	else
	{
		MessageBox("Get is Fail!Please try again!","Warning",MB_ICONWARNING);
		return;
	}
	
	ReaderDate time;
	BYTE time1[6]	=	{0};
	
	CTime m_NowTime= CTime::GetCurrentTime();
	
	time.Year=m_NowTime.GetYear()%100;
	time.Month=m_NowTime.GetMonth();
	time.Day=m_NowTime.GetDay();
	time.Hour=m_NowTime.GetHour();
	time.Minute=m_NowTime.GetMinute();
	time.Second=m_NowTime.GetSecond();
	//strtmp.Format("%02d-%02d-%02d %02d:%02d:%02d",time.Year,time.Month,time.Day,time.Hour,time.Minute,time.Second);
	//str.Format("%02x%02x%02x%02x%02x%02x",time.Year,time.Month,time.Day,time.Hour,time.Minute,time.Second);
	//StrtimetoDecimal(str,time1);
	memcpy(&lpGetBuf[1], &time, 6);

	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res = RU_SetReaderRecordNet(m_hSocket, lpGetBuf);
			break;
		case 1://RS232
			res = RU_SetReaderRecord(m_hScanner, lpGetBuf, 0);
			break;
		case 2://RS485
			res = RU_SetReaderRecord(m_hScanner, lpGetBuf, RS485Address);
			break;
		}
		if (res==_OK)
		{
			break;
		}
		
	}
	
	if ( _OK == res )
	{
		
		MessageBox("Set Record successfully!","Notice",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("Set Record Fail!Please try again!","Warning",MB_ICONWARNING);
	}
}

void DlgRubbish::OnButtonGetruallrecord() 
{
	// TODO: Add your control notification handler code here
	//取所有记录
	apiReturn res	=	_no_scanner;
	int i = 0;
	BYTE lpGetBuf[MAX_PATH] = {0};
	CString strTemp;
	CString strText;
	
	//1字节ID+6字节时间年月日时分秒
	
	for (i = 0; i < 3; i++)
	{
		switch(ConnectMode)
		{
		case 0://网口
			res = RU_GetExportRecordNet(m_hSocket, lpGetBuf);
			break;
		case 1://RS232
			res = RU_GetExportRecord(m_hScanner, lpGetBuf, 0);
			break;
		case 2://RS485
			res = RU_GetExportRecord(m_hScanner, lpGetBuf, RS485Address);
			break;
		}
		if (res==_OK)
		{
			break;
		}
		
	}
	
	if ( _OK == res )
	{
		for (i = 0; i < 28; i+=7)
		{
			GetDlgItem(IDC_EDIT_RECORD)->GetWindowText(strText);
			strTemp.Format("ID:%d---[%04d-%02d-%02d %02d:%02d:%02d]\r\n", lpGetBuf[i+0], lpGetBuf[i+1], lpGetBuf[i+2], lpGetBuf[i+3], lpGetBuf[i+4], lpGetBuf[i+5], lpGetBuf[i+6]);
			strText += strTemp;
			GetDlgItem(IDC_EDIT_RECORD)->SetWindowText(strText);
		}
	}
	else
	{
		MessageBox("Get Info!Please try again!","Warning",MB_ICONWARNING);
		return;
	}
	
}

void DlgRubbish::OnRadio0Ru1() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_DELRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUALLRECORD)->EnableWindow(TRUE);

}

void DlgRubbish::OnRadio0Ru2() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_DELRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUALLRECORD)->EnableWindow(TRUE);
}

void DlgRubbish::OnRadio0Ru3() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_DELRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUALLRECORD)->EnableWindow(TRUE);
}

void DlgRubbish::OnRadio0Ru4() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_DELRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUALLRECORD)->EnableWindow(TRUE);
}

void DlgRubbish::OnRadio0Ru5() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_DELRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRURECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUALLRECORD)->EnableWindow(TRUE);
}

void DlgRubbish::OnRadio2Ru6() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_DELRURECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRURECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GETRUALLRECORD)->EnableWindow(FALSE);
}

void DlgRubbish::OnRadio2Ru7() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_DELRURECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETRUID)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SETRURECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GETRUALLRECORD)->EnableWindow(FALSE);
}
