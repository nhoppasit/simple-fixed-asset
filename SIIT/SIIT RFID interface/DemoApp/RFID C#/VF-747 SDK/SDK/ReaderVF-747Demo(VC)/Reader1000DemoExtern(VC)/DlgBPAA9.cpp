// DlgBPAA9.cpp : implementation file
//

#include "stdafx.h"
#include "readerdemo.h"
#include "DlgBPAA9.h"

#include	<list>
using namespace std;

#include <afxmt.h>
#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//���嶨ʱ����ID
//ʱ��
#define					TIME_IDENTIFIER_DLGBPA9			(4000)		//ʱ��ID��,������ޱ�ǩ
#define					INTERVALTIME_DLGBPA9			(1000)		//�೤ʱ��ִ��һ��(1s��һ��)

//////////////////////////////////////////////////////////////////////////
HWND	gDlgBpa9			=	NULL;//Bpa9����ľ��
BOOL    nTagBpaThread		=	FALSE;

int iDlgBpaCount	=	0;

int iTimesCi		=	0;// ����

struct DataPacketDPA
{
	int len;				//buffer length
	char chbuf[512];	//actual buffer
};

CTList <DataPacketDPA> m_RdlgBpa;
CCriticalSection m_readBpaLock;

static CRITICAL_SECTION lpCriticalSection	=	{0};
/////////////////////////////////////////////////////////////////////////////
// CDlgBPAA9 property page

IMPLEMENT_DYNCREATE(CDlgBPAA9, CPropertyPage)

CDlgBPAA9::CDlgBPAA9() : CPropertyPage(CDlgBPAA9::IDD)
{
	//{{AFX_DATA_INIT(CDlgBPAA9)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	iDpCount	=	0;

	m_Bpa9Opt	=	0;//0-Granted,1-Denied

}

CDlgBPAA9::~CDlgBPAA9()
{
}

void CDlgBPAA9::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBPAA9)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Radio(pDX, IDC_RADIOA_BPA9Granted, m_Bpa9Opt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBPAA9, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgBPAA9)
	ON_BN_CLICKED(IDC_CHECK5_BPA9, OnCheck5Bpa9)
	ON_BN_CLICKED(IDC_BUTTON1_CMD1, OnButton1Cmd1)
	ON_BN_CLICKED(IDC_BUTTON1_CMD2, OnButton1Cmd2)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DLGBPA9DATAMSG, OnDlgBPA9Data)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBPAA9 message handlers

void CDlgBPAA9::OnInitUIText()//������ı�����
{
	SetWindowText(theApp.g_LoadString("IDWQB_G0001"));//6C Test
	


	CListCtrl *mIPlist = (CListCtrl*)GetDlgItem(IDC_LIST_BPA9);
	LVCOLUMN listColumnTemp;
	CString	strText;
	
	strText	=	theApp.g_LoadString("IDWQB_G0002");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(0, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_G0003");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(1, &listColumnTemp);
	strText.ReleaseBuffer();
	
	strText	=	theApp.g_LoadString("IDWQB_G0004");
	listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	mIPlist->SetColumn(2, &listColumnTemp);
	strText.ReleaseBuffer();
	
	//strText	=	theApp.g_LoadString("IDWQB_G0005");
	//listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	//mIPlist->SetColumn(3, &listColumnTemp);
	//strText.ReleaseBuffer();
	
	//strText	=	theApp.g_LoadString("IDWQB_G0006");
	//listColumnTemp.pszText	=	strText.GetBuffer(MAX_PATH);
	//mIPlist->SetColumn(4, &listColumnTemp);
	//strText.ReleaseBuffer();

 

	GetDlgItem(IDC_STATIC_RInterval_BPA9)->SetWindowText(theApp.g_LoadString("IDWQB_G0007"));//���ʱ��
	GetDlgItem(IDC_CHECK5_BPA9)->SetWindowText(theApp.g_LoadString("IDWQB_G0008"));//�г���ǩ
	GetDlgItem(IDC_BUTTON1_CMD1)->SetWindowText(theApp.g_LoadString("IDWQB_G0009"));//����1
	GetDlgItem(IDC_BUTTON1_CMD2)->SetWindowText(theApp.g_LoadString("IDWQB_G0010"));//����2
	

	GetDlgItem(IDC_STATIC_BPA9Opt)->SetWindowText(theApp.g_LoadString("IDWQB_G0011"));//Opt
	GetDlgItem(IDC_RADIOA_BPA9Granted)->SetWindowText(theApp.g_LoadString("IDWQB_G0012"));//Granted
	GetDlgItem(IDC_RADIOA_BPA9Denied)->SetWindowText(theApp.g_LoadString("IDWQB_G0013"));//Denied

}

BOOL CDlgBPAA9::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	gDlgBpa9	=	this->GetSafeHwnd();
	InitializeCriticalSection(&lpCriticalSection);

	Debug_SetEditHwnd(GetDlgItem(IDC_EDIT_BPA9Cmdd)->m_hWnd);

	CListCtrl	*m_ListID	=	(CListCtrl*)GetDlgItem(IDC_LIST_BPA9);
	DWORD dwStyle = m_ListID->SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	m_ListID->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);
	
	m_ListID->InsertColumn(0, "No.", LVCFMT_LEFT, 50);
	m_ListID->InsertColumn(1, "ID", LVCFMT_LEFT, 300);
	m_ListID->InsertColumn(2, "Success", LVCFMT_LEFT, 75);
	//m_ListID->InsertColumn(3, "Times", LVCFMT_LEFT, 75);
	//m_ListID->InsertColumn(4, "EPC Length", LVCFMT_LEFT, 75);


	//���ʱ��
	//((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("10");
	//((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("20");
	//((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("50");
	//((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("100");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("200");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("500");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("1000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("2000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("5000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("10000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("20000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->AddString("50000");
	((CComboBox*)GetDlgItem(IDC_COMBO_BPA9))->SetCurSel(1);

	((CComboBox*)GetDlgItem(IDC_BUTTON1_CMD1))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_BUTTON1_CMD2))->ShowWindow(SW_HIDE);
	//BPA9 test
	::SendMessage(gDlgBpa9,WM_DLGBPA9DATAMSG,2,0);	//convert language
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgBPAA9::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgBPAA9::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}


void CDlgBPAA9::OnCheck5Bpa9() 
{
	// TODO: Add your control notification handler code here
	//
	CString strTemp;
	CListCtrl	*m_ListID	=	(CListCtrl*)GetDlgItem(IDC_LIST_BPA9);
	int m_ListTagID	=	((CButton*)GetDlgItem(IDC_CHECK5_BPA9))->GetCheck();

	//���ʱ��
	CComboBox	*mTime	=	(CComboBox*)GetDlgItem(IDC_COMBO_BPA9);
	mTime->GetLBText(mTime->GetCurSel(),strTemp);
	intervalTime	=	atoi(strTemp);
//::PostMessage(gDlgBpa9, WM_DLGBPA9DATAMSG, 0, 2);
//return;
	if ( m_ListTagID )
	{
		//����
		m_ListID->DeleteAllItems();
		//Read_times=0;
		iTimesCi		=	0;// ����
		
		hScanTagThread	=	CreateThread(NULL,0,ScanTagThread,this,0,NULL);
		if( hScanTagThread != NULL )
		{		
			nTagBpaThread	=	TRUE;
			
		}
		else
		{
			nTagBpaThread	=	FALSE;
			MessageBox("Create OnDlgBPA9Data Error!","Notice",MB_ICONERROR);
			//MessageBox(theApp.g_LoadString("IDWQB_B0041"), theApp.g_LoadString("IDWQB_B0042"),MB_ICONERROR);
		}

	}
	else
	{
		//�ɿ�
		iDlgBpaCount	=	0;

		nTagBpaThread	=	FALSE;
		
		if ( hScanTagThread != NULL )
		{
			WaitForSingleObject(hScanTagThread,500);
			CloseHandle(hScanTagThread);
			hScanTagThread	=	NULL;
		}
	}

}

void CDlgBPAA9::OnButton1Cmd1() 
{
	// TODO: Add your control notification handler code here
	//DataPacket dt;
	//dt.len	=	iDpCount++;
	//sprintf(dt.chbuf, _T("a%db%dc%d"), iDpCount, iDpCount, iDpCount);
	
	//m_ReadBuffer.AddTail(dt);
	
}

void CDlgBPAA9::OnButton1Cmd2() 
{
	// TODO: Add your control notification handler code here
	//DataPacket dt;
	//if ( FALSE == m_ReadBuffer.IsEmpty() )
	//{
		
		
	//	dt = m_ReadBuffer.GetTail();
	//	m_ReadBuffer.RemoveTail();
		
	//	TRACE("%d:%s\n", dt.len, dt.chbuf);
	//}
	
}

//////////////////////////////////////////////////////////////////////////
//��;:		��ģ�����Ϣ��̬��Ա����,�ص�����
//������:	CallBack_MyDlgBpa9
//����:		
//�������:	hWnd--handle of CWnd that called SetTimer
//			nMsg--WM_TIMER
//			nIDEvent--timer identification
//			dwTime--system time 
//�������:	��
//����ֵ:	��
//��ע:TIME_IDENTIFIER_DLGBPA9, INTERVALTIME_DLGBPA9
//////////////////////////////////////////////////////////////////////////
void WINAPI CDlgBPAA9::CallBack_MyDlgBpa9(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime)
{
	//Debug_Printf("r:%s\r\n","hello");
	if ( TIME_IDENTIFIER_DLGBPA9 == nIDEvent )
	{
		//ɨ����
		//::PostMessage(gDlgDataHwnd, WM_DLGDATAA, 0, 0);
	}
}

//WM_DLGBPA9DATAMSG
afx_msg LRESULT CDlgBPAA9::OnDlgBPA9Data(WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	CListCtrl	*m_ListID	=	(CListCtrl*)GetDlgItem(IDC_LIST_BPA9);

	CString strText;
	CString strTemp;

	UpdateData(TRUE);

	if ( 0 == iwParam )
	{
		if ( 1 == ilParam )	//�յ����ݣ�
		{
			EnterCriticalSection(&lpCriticalSection);//ok
			//CSingleLock csl(&m_readBpaLock);//Ҳok
			//csl.Lock();

			int iRet = 0;
			DataPacketDPA dpData;
			if ( FALSE == m_RdlgBpa.IsEmpty() )
			{
				
				char chTemp[MAX_PATH]	=	{0};
				dpData = m_RdlgBpa.GetHead();
				if ( dpData.len >= 0 )
				{
					if ( dpData.len == 1 )
					{
						strText	=	_T("No Tag:");
						Bcd2Asc(chTemp, (char*)dpData.chbuf, 2);
						strText	+=	chTemp;
					}
					else
					{
						BOOL bCheckFlag	= TRUE;
						if ( 34 == dpData.len )
						{
							BYTE chCheck = 0;
							for ( i = 1; i < dpData.len-1; i++)
							{
								chCheck ^= dpData.chbuf[i];
							}
							if ( chCheck == (byte)dpData.chbuf[dpData.len-1] )
							{

								//��ʾʱ�� 14 0D 00 05 00 0E 00 0A 00 29 
								CString strTime;
								if ( dpData.chbuf[6] == 0x31 )//˵��Ҫ��ʾʱ��
								{
									strTime.Format("%02d%02d-%02d-%02d %02d:%02d", dpData.chbuf[7], dpData.chbuf[8], dpData.chbuf[10],  dpData.chbuf[12]
										, dpData.chbuf[14], dpData.chbuf[16]);
									GetDlgItem(IDC_STATIC_BPATIME)->SetWindowText(strTime);
								}


								//У����ȷ
								dpData.chbuf[18+14]=0x00;
								strText = &dpData.chbuf[18];


								dpData.len	=	RS485Address;//���Ǵ�������������������,����485���ߵĶ˿�,

								if ( 0 == m_Bpa9Opt )
								{
									iRet	=	GetReaderBPAGranted(m_hScanner, (BYTE*)dpData.chbuf, &dpData.len);
								}
								else
								{
									iRet	=	GetReaderBPADenied(m_hScanner, (BYTE*)dpData.chbuf, &dpData.len);
								}
								
								
							}
							else
							{
								//У�����
								strText	=	_T("No Tag:01");
							}
							
						}
						else
						{
							strText	=	_T("No Tag:02");
						}
						
					}
					
					//Debug_Printf("o:%s\r\n", (char*)strText.GetBuffer(MAX_PATH));
					//strText.ReleaseBuffer();

					//�ڱ�����ʾ
					k = m_ListID->GetItemCount();	//��ǰ�ж�����
					for(j = 0; j < k; j++)
					{
						m_ListID->GetItemText(j, 1, chTemp, MAX_PATH);
						
						if( strText.Find(chTemp) >= 0 ) 
						{
							//�ҵ���
							break;
						}
					}

					if(j == k)
					{
						m_ListID->InsertItem(k,itoa(k+1,chTemp,10));
						m_ListID->SetItemText(k,1,strText);
						m_ListID->SetItemText(k,2,"1");
						k++;
					}
					else
					{
						strTemp=m_ListID->GetItemText(j,2);
						m_ListID->SetItemText(j,2,itoa(atoi(strTemp)+1,chTemp,10));
					}

				}
				
				
				m_RdlgBpa.RemoveHead();
				
				
				
				//Wq_WriteAppLogFile(__FILE__, __LINE__, "P:%d\r\n", dpData.len);
				//TRACE("P:%d:\n", dt.len);
			}
			//csl.Unlock();
			LeaveCriticalSection(&lpCriticalSection);//ok

		}
		else if ( 2 == ilParam )
		{
			DataPacketDPA	dpData;
			dpData.len	=	0;
			dpData.len	=	RS485Address;//���Ǵ�������������������,����485���ߵĶ˿�,
			GetReaderBPAEpc(m_hScanner, (BYTE*)dpData.chbuf, &dpData.len);//��д����ѯ

			if ( dpData.len	> 0 )
			{
				
				if ( dpData.len == 65 )
				{
					dpData.len = 65;
				}
				m_RdlgBpa.AddTail(dpData);
				
				
				//Wq_WriteAppLogFile(__FILE__, __LINE__, "o:%d\r\n", dpData.len);
				//TRACE("o:%d:\n", dpData.len);
				::PostMessage(gDlgBpa9, WM_DLGBPA9DATAMSG, 0, 1);//���ݳ����ж��Ƿ񷢽��ܻ�ܾ�ָ��
			}
		}
		else if( 3 == ilParam )	//�յ����ݣ�
		{
			int iAddress	=	RS485Address;
			char lpBuf[1024]	=	{0};

			SetReaderTimeStamp(m_hScanner, (BYTE*)lpBuf, &iAddress);

		}
		else if ( 4 == ilParam )
		{
			DataPacketDPA	dpData;
			dpData.len	=	0;
			dpData.len	=	RS485Address;//���Ǵ�������������������,����485���ߵĶ˿�,
			GetReaderGroupPolling(m_hScanner, (BYTE*)dpData.chbuf, &dpData.len);//����ѯ
			if ( dpData.len	> 0 )
			{
				//ʲôҲ����
			}

		}
	}

	if ( 2 == iwParam )
	{
		OnInitUIText();	//��������
	}
	

	UpdateData(FALSE);

	return 0;
}

//���̺߳���
DWORD WINAPI CDlgBPAA9::ScanTagThread(LPVOID pParam)
{
	int iRet = 0;
	
	DataPacketDPA	dpData;
	CDlgBPAA9* m_pStandard;
	
	m_pStandard=(CDlgBPAA9*)pParam;

	int intervalTime	=	m_pStandard->intervalTime;

	int iAddress	=	RS485Address;
	DWORD dwStart	=	GetTickCount();
	DWORD dwEndtt	=	GetTickCount();
	while (nTagBpaThread)
	{
		Sleep(intervalTime);

		//���ǲ���	
		//for (long i=0;i<5000;i++)
		//{
		//}

		//CSingleLock csl(&m_readBpaLock);
		//csl.Lock();
		EnterCriticalSection(&lpCriticalSection);//ok

		iTimesCi++;

		dwEndtt	=	GetTickCount();
		if ( dwEndtt - dwStart >= 500 )//1s(1000),�ʼ���0.5s��(500)
		{
			
			//SetReaderTimeStamp(m_hScanner, (BYTE*)lpBuf, &iAddress);
			::PostMessage(gDlgBpa9, WM_DLGBPA9DATAMSG, 0, 3);
			dwStart	=	GetTickCount();//���¼�ʱ
		}


		dpData.len = ++iDlgBpaCount;
		
		//test
		if ( iDlgBpaCount >= 5000 )
		{
			//break;
		}

		dpData.len	=	0;
		//dpData.len	=	RS485Address;//���Ǵ�������������������,����485���ߵĶ˿�,
		//iRet	=	GetReaderBPAEpc(m_hScanner, (BYTE*)dpData.chbuf, &dpData.len);
		if (iTimesCi % 2 == 1)
		{
			::PostMessage(gDlgBpa9, WM_DLGBPA9DATAMSG, 0, 2);//Reader ��ѯ
		}
		else
		{
			::PostMessage(gDlgBpa9, WM_DLGBPA9DATAMSG, 0, 4);//�� ��ѯ
		}
		
		

		//csl.Unlock();
		LeaveCriticalSection(&lpCriticalSection);//ok



	}


	return 0;
}

