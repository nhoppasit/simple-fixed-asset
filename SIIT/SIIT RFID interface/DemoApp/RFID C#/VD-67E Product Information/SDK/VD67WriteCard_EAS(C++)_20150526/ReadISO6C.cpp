// ReadISO6C.cpp : implementation file
//

#include "stdafx.h"
#include "WriteCard.h"
#include "ReadISO6C.h"

#include <io.h>
#include <odbcinst.h>
#include <afxdb.h>
#pragma comment(lib, "shlwapi")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////�������涨ʱ��//////////////////////////////////////////
//���嶨ʱ����ID
//ʱ��
#define					TIME_IDENTIFIER_PARAM			(300)			//ʱ��ID��
#define					INTERVALTIME_PARAM				(100)			//�೤ʱ��ִ��һ��
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
HWND	g6CReadHwnd	=	NULL;	//��д��6C��������
DWORD   g6CReadTheardID = 0;

/////////////////////////////////////////////////////////////////////////////
// CReadISO6C property page

IMPLEMENT_DYNCREATE(CReadISO6C, CPropertyPage)

CReadISO6C::CReadISO6C() : CPropertyPage(CReadISO6C::IDD)
, m_Time(0)
, m_CheckTID(FALSE)
, m_CheckPass(FALSE)
, m_CheckUser(FALSE)
, m_TIDB(0)
, m_PassB(0)
, m_UserB(0)
, m_TIDL(0)
, m_PassL(0)
, m_UserL(0)
{
	//{{AFX_DATA_INIT(CReadISO6C)
		// NOTE: the ClassWizard will add member initialization here
	m_EasState = 0;
	m_AAccessPassword = _T("");
	m_EasAlarm = FALSE;
	//}}AFX_DATA_INIT

	m_ScanExitThreadEvent	=	INVALID_HANDLE_VALUE;
	m_ReadEpcHandle			=	INVALID_HANDLE_VALUE;
}

CReadISO6C::~CReadISO6C()
{
}

void CReadISO6C::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadISO6C)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST_SHOW, m_ListShowData);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Time);
	DDX_Control(pDX, IDC_STATIC_DIS, m_Dis);
	DDX_Check(pDX, IDC_CHECK_TID, m_CheckTID);
	DDX_Check(pDX, IDC_CHECK_PASS, m_CheckPass);
	DDX_Check(pDX, IDC_CHECK_USER, m_CheckUser);
	DDX_Text(pDX, IDC_EDIT_TIDB, m_TIDB);
	DDX_Text(pDX, IDC_EDIT_PASSB, m_PassB);
	DDX_Text(pDX, IDC_EDIT_USERB, m_UserB);
	DDX_Text(pDX, IDC_EDIT_TIDL, m_TIDL);
	DDX_Text(pDX, IDC_EDIT_PASSL, m_PassL);
	DDX_Text(pDX, IDC_EDIT_USERL, m_UserL);
	DDX_Control(pDX, IDC_STATIC_OUT, m_Out);
	DDX_Radio(pDX, IDC_RADIO23_NoAlarm_6C, m_EasState);
	DDX_Text(pDX, IDC_EDIT12, m_AAccessPassword);
	DDX_Check(pDX, IDC_CHECK7_EasAlarm_6C, m_EasAlarm);
	DDX_Control(pDX, IDC_EASALARM_STATIC, m_APic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadISO6C, CPropertyPage)
	//{{AFX_MSG_MAP(CReadISO6C)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedButtonStop)
	ON_MESSAGE(WM_READISO6C,ReadMsg)
	ON_BN_CLICKED(IDC_BUTTON_DELALL, OnBnClickedButtonDelall)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DELONE, OnBnClickedButtonDelone)
	ON_BN_CLICKED(IDC_BUTTON_SAVE2, OnBnClickedButtonSave2)
	ON_BN_CLICKED(IDC_BUTTON5_SetAlarm_6C, OnBnClickedButton5SetAlarm6C)
	ON_BN_CLICKED(IDC_CHECK7_EasAlarm_6C, OnBnClickedCheck7EasAlarm6C)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_6CREADDATAMSG, On6cReaddatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadISO6C message handlers
void CReadISO6C::OnInitUIText()//������ı�����
{
	SetWindowText(theApp.g_LoadString("IDWQF_E0001"));//��ISO18000-6C���͵��ӱ�ǩ
	
	
	GetDlgItem(IDC_BUTTON1)->SetWindowText(theApp.g_LoadString("IDWQF_E0002"));//��ʼ��ȡ
	GetDlgItem(IDC_STATIC_R6ReadList)->SetWindowText(theApp.g_LoadString("IDWQF_E0003"));//��ȡ�����б�
	GetDlgItem(IDC_CHECK_TID)->SetWindowText(theApp.g_LoadString("IDWQF_E0004"));//TID��
	GetDlgItem(IDC_CHECK_PASS)->SetWindowText(theApp.g_LoadString("IDWQF_E0005"));//������
	GetDlgItem(IDC_CHECK_USER)->SetWindowText(theApp.g_LoadString("IDWQF_E0006"));//�û���
	GetDlgItem(IDC_STATIC_TIDSTARTPOS)->SetWindowText(theApp.g_LoadString("IDWQF_E0007"));//��ʼλ��(Word)
	GetDlgItem(IDC_STATIC_PASSSTARTPOS)->SetWindowText(theApp.g_LoadString("IDWQF_E0008"));//��ʼλ��(Word)
	GetDlgItem(IDC_STATIC_USERSTARTPOS)->SetWindowText(theApp.g_LoadString("IDWQF_E0009"));//��ʼλ��(Word)
	GetDlgItem(IDC_STATIC_R6DATAPART)->SetWindowText(theApp.g_LoadString("IDWQF_E0010"));//����������
	GetDlgItem(IDC_STATIC_TIDLEN)->SetWindowText(theApp.g_LoadString("IDWQF_E0011"));//����(Word)
	GetDlgItem(IDC_STATIC_PASSLEN)->SetWindowText(theApp.g_LoadString("IDWQF_E0012"));//����(Word)
	GetDlgItem(IDC_STATIC_USERLEN)->SetWindowText(theApp.g_LoadString("IDWQF_E0013"));//����(Word)
	GetDlgItem(IDC_BUTTON_STOP)->SetWindowText(theApp.g_LoadString("IDWQF_E0014"));//ֹͣ��ȡ
	GetDlgItem(IDC_STATIC_R6BETTIME)->SetWindowText(theApp.g_LoadString("IDWQF_E0015"));//���ʱ��:��
	GetDlgItem(IDC_STATIC_DIS)->SetWindowText(theApp.g_LoadString("IDWQF_E0016"));//״̬
	GetDlgItem(IDC_STATIC_R6ReadStat)->SetWindowText(theApp.g_LoadString("IDWQF_E0017"));//��ȡ״̬
	GetDlgItem(IDC_STATIC_R6ReadData)->SetWindowText(theApp.g_LoadString("IDWQF_E0018"));//��ȡ����
	GetDlgItem(IDC_STATIC_OUT)->SetWindowText(theApp.g_LoadString("IDWQF_E0019"));//����
	GetDlgItem(IDC_BUTTON_DELONE)->SetWindowText(theApp.g_LoadString("IDWQF_E0020"));//ɾ��ѡ�м�¼
	GetDlgItem(IDC_BUTTON_SAVE)->SetWindowText(theApp.g_LoadString("IDWQF_E0021"));//���浽TXT�ļ�
	GetDlgItem(IDC_BUTTON_DELALL)->SetWindowText(theApp.g_LoadString("IDWQF_E0022"));//��������б�
	GetDlgItem(IDC_BUTTON_SAVE2)->SetWindowText(theApp.g_LoadString("IDWQF_E0023"));//���浽Excel�ļ�

	GetDlgItem(IDC_STATIC_AlarmCC_6C)->SetWindowText(theApp.g_LoadString("IDWQB_E0045"));//����
	GetDlgItem(IDC_STATIC_SelectaTagAE_6C)->SetWindowText(theApp.g_LoadString("IDWQB_E0046"));//ѡ��һ����ǩ
	//GetDlgItem(IDC_BUTTON_SAVE2)->SetWindowText(theApp.g_LoadString("IDWQB_E0047"));//Eas״̬
	GetDlgItem(IDC_RADIO23_NoAlarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_E0048"));//������
	GetDlgItem(IDC_RADIO24_Alarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_E0049"));//����
	GetDlgItem(IDC_STATIC_AccessPSDDA_6C)->SetWindowText(theApp.g_LoadString("IDWQB_E0050"));//��������(8HEX):
	GetDlgItem(IDC_BUTTON5_SetAlarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_E0051"));//���ñ���
	GetDlgItem(IDC_CHECK7_EasAlarm_6C)->SetWindowText(theApp.g_LoadString("IDWQB_E0052"));//��ⱨ��
	
	GetDlgItem(IDC_STATIC_GroupREAD)->SetWindowText(theApp.g_LoadString("IDWQB_E0053"));//��ȡ����
	



	m_ListShowData.DeleteColumn(0);
	m_ListShowData.DeleteColumn(0);
	m_ListShowData.DeleteColumn(0);
	m_ListShowData.DeleteColumn(0);
	m_ListShowData.DeleteColumn(0);
	m_ListShowData.InsertColumn( 0, theApp.g_LoadString("IDWQF_E0024"), LVCFMT_LEFT, 40 );
    m_ListShowData.InsertColumn( 1, theApp.g_LoadString("IDWQF_E0025"), LVCFMT_LEFT, 200);
    m_ListShowData.InsertColumn( 2, theApp.g_LoadString("IDWQF_E0026"), LVCFMT_LEFT, 200);
	m_ListShowData.InsertColumn( 3, theApp.g_LoadString("IDWQF_E0027"), LVCFMT_LEFT, 120);
	m_ListShowData.InsertColumn( 4, theApp.g_LoadString("IDWQF_E0028"), LVCFMT_LEFT, 120);

	
}

void CReadISO6C::UpdateStatus()//����ʹ���벻ʹ��
{
	UpdateData(TRUE);
	
	// 	GetDlgItem(IDC_RADIO_ConnectRS232)->EnableWindow(!ifConnectReader);
	// 	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(!ifConnectReader);
	// 	GetDlgItem(IDC_COMBO1)->EnableWindow(!ifConnectReader);
	// 	GetDlgItem(IDC_BUTTON_CONNECTDIS)->EnableWindow(ifConnectReader);
	// 	
	// 	if ( 1 == m_ConnectMode )
	// 	{
	// 		//���USBѡ��
	// 		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	// 	}
	
	UpdateData(FALSE);
}

BOOL CReadISO6C::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	g6CReadHwnd	=	this->GetSafeHwnd();
	
	DWORD dwStyle = m_ListShowData.GetExtendedStyle(); 
	
    //ѡ��ĳ��ʹ���и߶�
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;//������
	
    m_ListShowData.SetExtendedStyle(dwStyle); //������չ���
	
	
	
	
    //m_ListInData.SetBkColor(RGB(200, 200, 200)); //���ñ�����ɫ
    //m_ListInData.SetTextBkColor(RGB(200, 200, 200)); //�����ı�������ɫ
    //m_ListInData.SetTextColor(RGB(10, 10, 80)); //�����ı���ɫ
	
	
    //�����еı���
    //m_ListShowData.InsertColumn( 0, _T("���"), LVCFMT_LEFT, 40 );
    //m_ListShowData.InsertColumn( 1, _T("EPC��"), LVCFMT_LEFT, 200);
    //m_ListShowData.InsertColumn( 2, _T("�û���"), LVCFMT_LEFT, 200);
	//m_ListShowData.InsertColumn( 3, _T("TID��"), LVCFMT_LEFT, 120);
	//m_ListShowData.InsertColumn( 4, _T("������"), LVCFMT_LEFT, 120);
	
	m_ListShowData.InsertColumn( 0, theApp.g_LoadString("IDWQF_E0024"), LVCFMT_LEFT, 40 );
    m_ListShowData.InsertColumn( 1, theApp.g_LoadString("IDWQF_E0025"), LVCFMT_LEFT, 200);
    m_ListShowData.InsertColumn( 2, theApp.g_LoadString("IDWQF_E0026"), LVCFMT_LEFT, 200);
	m_ListShowData.InsertColumn( 3, theApp.g_LoadString("IDWQF_E0027"), LVCFMT_LEFT, 120);
	m_ListShowData.InsertColumn( 4, theApp.g_LoadString("IDWQF_E0028"), LVCFMT_LEFT, 120);

	m_Time=1;
	
	nStop=0;
	
	m_TIDL=4;
	m_PassL=4;
	m_UserL=6;
	
	UpdateData(FALSE);
	

	GetDlgItem(IDC_BUTTON5_SetAlarm_6C)->EnableWindow(FALSE);//���ñ���
	GetDlgItem(IDC_CHECK7_EasAlarm_6C)->EnableWindow(FALSE);//��ⱨ��
	GetDlgItem(IDC_EDIT12)->SetWindowText(_T("11112222"));

	//BOOL b=m_menuMain.LoadMenu(IDR_MENU2);
	//b=this->SetMenu(&m_menuMain);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CReadISO6C::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//6C��ҳ
	::PostMessage(g6CReadHwnd,WM_6CREADDATAMSG,2,0);	//convert language

	return CPropertyPage::OnSetActive();
}

BOOL CReadISO6C::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( INVALID_HANDLE_VALUE != m_ScanExitThreadEvent )
	{
		SetEvent(m_ScanExitThreadEvent);
		Sleep(1000);
		CloseHandle(m_ScanExitThreadEvent);
		m_ScanExitThreadEvent	=	INVALID_HANDLE_VALUE;
	}
	
	if ( INVALID_HANDLE_VALUE != m_ReadEpcHandle )
	{
		TerminateThread(m_ReadEpcHandle,0);
		CloseHandle(m_ReadEpcHandle);
		m_ReadEpcHandle = INVALID_HANDLE_VALUE;
	}

	return CPropertyPage::OnKillActive();
}


//WM_6CREADDATAMSG
LRESULT CReadISO6C::On6cReaddatamsg(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 2 == iwParam )
	{
		OnInitUIText();	//��������
	}
	else if( 1 == iwParam )
	{
		OnEasAlarmTest();//��ⱨ������
	}

	
	return 0;
}

static DWORD WINAPI ThreadReadEPC(LPVOID lpParameter)
{
	CReadISO6C *epcDlg = (CReadISO6C *)lpParameter;

	int t;
	apiReturn res;
	int i,j,nCounter=0,ID_len=0,ID_len_temp=0;
	CString str,str_temp;
	BYTE temp[512];
	BYTE IDBuffer[30*256];
    BYTE DB[128];
	BYTE mask[512],IDTemp[512];
	int mem,ptr,len,EPC_Word;
	BYTE AccessPassword[4];

	int nRow;
	int iCheckTid = epcDlg->m_CheckTID;//
	apiReturn resTid = _no_scanner;

	int iCheckUsr = epcDlg->m_CheckUser;//
	apiReturn resUsr = _no_scanner;

	int iCheckPas = epcDlg->m_CheckPass;//
	apiReturn resPas = _no_scanner;

	while(epcDlg->nStop)
	{
	
		resTid = _no_scanner;
		resUsr = _no_scanner;
		resPas = _no_scanner;

		if (WaitForSingleObject(epcDlg->m_ScanExitThreadEvent, 0) == WAIT_OBJECT_0)
		{
			epcDlg->nStop = FALSE;
			break;
		}

		if(!ifConnectReader)
		{
			SendMessage(epcDlg->m_hWnd,WM_READISO6C,0,1);
			epcDlg->nStop=0;
			break;
		}

		len=0;	ptr=0;	mem=1;	ID_len=0;  j=0;   nRow=0;
		memset(mask,0,512);
		
		for (i = 0; i < 3; i++)
		{
			Sleep(300);
			switch(ConnectMode)
			{
			case 0:		
				break;
			case 1:
			case 3://usb,��EPC��
				res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,RS485Address);	
				break;
			}
			if ( _OK == res )
			{
				break;
			}
		}

		if(res==_OK)
		{
			str.Empty(); 
			ID_len=(int)IDBuffer[0];  //IDBuffer[0]ΪWord����;1word=2Byte
			memcpy(temp,&IDBuffer[1],ID_len*2);
			for(i=0;i<ID_len*2;i++)
			{
				str_temp.Format(_T("%02X"),temp[i]);
				str=str+str_temp;
			}
			epcDlg->stEpc=str;


			
			//���ѡ��TID���֮
			if(epcDlg->m_CheckTID)
			{

				memset(AccessPassword,0,4);
				EPC_Word=ID_len;
				memcpy(IDTemp,&IDBuffer[1],ID_len*2);
				mem=2;
				ptr=epcDlg->m_TIDB;
				len=epcDlg->m_TIDL;

				for (i = 0; i < 3; i++)
				{
					Sleep(300);
					switch(ConnectMode)
					{
					case 0:		
						break;
					case 1:
					case 3://usb
						res=EPC1G2_ReadWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,&DB[0],AccessPassword,RS485Address);	
						break;
					}
					if ( _OK == res )
					{
						resTid = _OK;
						break;
					}
				}
				if(res==_OK)
				{
					str.Empty(); 
					memset(temp,0,512);
					memcpy(temp,DB,len*2);
					for(i=0;i<len*2;i++)
					{
						str_temp.Format(_T("%02X"),temp[i]);
						str=str+str_temp;

					}
					epcDlg->stTid=str;
				}
				else
				{
					//epcDlg->stTid=_T("����");
					//epcDlg->stTid=theApp.g_LoadString("IDWQF_E0029");

					//epcDlg->stTid=_T("");//modify by martrin 20140512
				}
			}

			//���ѡ��USER���֮
			if(epcDlg->m_CheckUser)
			{
				memset(AccessPassword,0,4);
				EPC_Word=ID_len;
				memcpy(IDTemp,&IDBuffer[1],ID_len*2);
				mem=3;
				ptr=epcDlg->m_UserB;
				len=epcDlg->m_UserL;

				for (i = 0; i < 3; i++)
				{
					Sleep(300);
					switch(ConnectMode)
					{
					case 0:		
						break;
					case 1:
					case 3://usb
						res=EPC1G2_ReadWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,&DB[0],AccessPassword,RS485Address);	
						break;
					}
					if ( _OK == res )
					{
						resUsr = _OK;
						break;
					}
				}

				if(res==_OK)
				{
					str.Empty(); 
					memset(temp,0,512);
					memcpy(temp,DB,len*2);
					for(i=0;i<len*2;i++)
					{
						str_temp.Format(_T("%02X"),temp[i]);
						str=str+str_temp;
					}
					epcDlg->stUsr=str;
				}
				else
				{
					//epcDlg->stUsr=_T("����");
					//epcDlg->stUsr=theApp.g_LoadString("IDWQF_E0030");
					//epcDlg->stUsr=_T("");//modify by martrin 20140512
				}

			}

			//���ѡ��PASSWORD���֮
			if(epcDlg->m_CheckPass)
			{
				memset(AccessPassword,0,4);
				EPC_Word=ID_len;
				memcpy(IDTemp,&IDBuffer[1],ID_len*2);
				mem=0;
				ptr=epcDlg->m_PassB;
				len=epcDlg->m_PassL;

				memset(DB,0,128);

				for (i = 0; i < 3; i++)
				{
					Sleep(300);
					switch(ConnectMode)
					{
					case 0:		
						break;
					case 1:
					case 3://usb
						res=EPC1G2_ReadWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,&DB[0],AccessPassword,RS485Address);	
						break;
					}
					if ( _OK == res )
					{
						resPas = _OK;
						break;
					}
				}
				if(res==_OK)
				{
					str.Empty(); 
					memset(temp,0,512);
					memcpy(temp,DB,len*2);
					for(i=0;i<len*2;i++)
					{
						str_temp.Format(_T("%02X"),temp[i]);
						str=str+str_temp;
					}
					epcDlg->stPass=str;
				}
				else
				{
					//epcDlg->stPass=_T("����");
					//epcDlg->stPass=theApp.g_LoadString("IDWQF_E0030");
					//epcDlg->stPass=_T("");//modify by martrin 20140512
				}
			}

			SendMessage(epcDlg->m_hWnd,WM_READISO6C,1,0);

			int ichFlag = 0;
			if ( iCheckTid && iCheckUsr && iCheckPas ) //ȫѡ
			{
				if ( resTid == _OK && resPas == _OK && resUsr == _OK )
				{
					ichFlag = 1;
				}
			}
			else if ( iCheckTid && iCheckUsr )
			{
				if ( resTid == _OK && resUsr == _OK )
				{
					ichFlag = 1;
				}
			}
			else if ( iCheckTid && iCheckPas )
			{
				if ( resTid == _OK && resPas == _OK )
				{
					ichFlag = 1;
				}
			}
			else if ( iCheckUsr && iCheckPas )
			{
				if ( resUsr == _OK && resPas == _OK )
				{
					ichFlag = 1;
				}
			}
			else if ( iCheckTid )
			{
				if ( resTid == _OK )
				{
					ichFlag = 1;
				}
			}
			else if ( iCheckUsr )
			{
				if ( resUsr == _OK )
				{
					ichFlag = 1;
				}
			}
			else if ( iCheckPas )
			{
				if ( resPas == _OK )
				{
					ichFlag = 1;
				}
			}
			else
			{
				ichFlag = 1;
			
			}


			if ( 1 == ichFlag )
			{
				//��ʼ����
				TRACE("x:Buzzer\n");
				if ( 3 == ConnectMode )
				{
					BuzzerAlarm(m_hScanner, 1);
				}
				
				Sleep(100);
				
				//ֹͣ����
				if ( 3 == ConnectMode )
				{
					BuzzerAlarm(m_hScanner, 0);
				}
			}
			

		}
		else
		{
			j++;
			t=res*1000+j;
			SendMessage(epcDlg->m_hWnd,WM_READISO6C,101,t);
			Sleep(500);
		}

		for(i=0;i<(int)epcDlg->m_Time;i++)
		{
			 //Sleep(1000);
			Sleep(100);
			SendMessage(epcDlg->m_hWnd,WM_READISO6C,2,i);
		}
	}

	return 0;
}

void CReadISO6C::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);

	if(!ifConnectReader)
	{
		//MessageBox(_T("��д��δ����"),_T("��ʾ"),0);
		MessageBox(theApp.g_LoadString("IDWQF_E0031"), theApp.g_LoadString("IDWQF_E0032"), 0);
		return;
	}

// 	if(nWRStatus!=1)
// 	{
// 		MessageBox(_T("��д������ʹ����"),_T("��ʾ"),0);
// 		return;
// 	}
// 	else
// 	{
// 		nWRStatus=2;
// 	}

	nStop=1;

	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON5_SetAlarm_6C)->EnableWindow(FALSE);//���ñ���
	GetDlgItem(IDC_CHECK7_EasAlarm_6C)->EnableWindow(FALSE);//��ⱨ��

	m_ScanExitThreadEvent	=	CreateEvent(NULL,FALSE,FALSE,NULL);
	m_ReadEpcHandle = CreateThread(NULL,0,ThreadReadEPC,this,0,&g6CReadTheardID);	
}

void CReadISO6C::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//nStop=0;
	//nWRStatus=1;

	SetEvent(m_ScanExitThreadEvent);
	Sleep(1000);
	CloseHandle(m_ScanExitThreadEvent);
	m_ScanExitThreadEvent	=	NULL;

	TerminateThread(m_ReadEpcHandle,0);
	CloseHandle(m_ReadEpcHandle);
	m_ReadEpcHandle = INVALID_HANDLE_VALUE;

	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON5_SetAlarm_6C)->EnableWindow(TRUE);//���ñ���
	GetDlgItem(IDC_CHECK7_EasAlarm_6C)->EnableWindow(TRUE);//��ⱨ��

	nStop=0;


	int nRow=m_ListShowData.GetItemCount();
	if(nRow<=0)
	{
		return;
	}
	
	
	CString sEpcTmp,sUseTmp,sPassTmp,strtmp,sTID;
	
	
    CString tmp=_T(",");
	
	BYTE str[1024];
	int len;
	
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent();

	for(int i=0;i<nRow;i++)
	{
		strtmp.Empty(); 
		sEpcTmp=m_ListShowData.GetItemText(i,1);
		
		
		strtmp=sEpcTmp;
		
		len=0;
		memset(str,0,1024);
		//WideCharToMultiByte( CP_ACP, 0, strtmp.GetBuffer(), -1,(char*)str,strtmp.GetLength()*2,NULL,NULL );
		len=strtmp.GetLength();
		memcpy(str, strtmp, len);
		
		((CComboBox*)GetDlgItem(IDC_COMBO6))->AddString((char*)str);
		
	}
	
	((CComboBox*)GetDlgItem(IDC_COMBO6))->SetCurSel(0);
	return;

}

LRESULT CReadISO6C::ReadMsg(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	CString tmp;
	int nS,nRow,i;
	switch(wParam)
	{
	case 0:
		nStop=0;
		//nWRStatus=1;
		if(lParam)
		{
			//MessageBox(_T("��д�������ѶϿ��Ͽ�������������"),_T("����"),MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_E0033"), theApp.g_LoadString("IDWQF_E0034"), MB_ICONWARNING);
		}
		break;
	case 1: 
		nS=m_ListShowData.GetItemCount();
		for(i=0;i<nS;i++)
		{
			strTemp	=	m_ListShowData.GetItemText(i,1);
			if(stEpc==strTemp)
			{
				break;
			}
		}
		if(i==nS)
		{
			//����
			tmp.Format(_T("%d"),nS+1);
			//nRow=m_ListShowData.InsertItem(0,tmp); 
			nRow=m_ListShowData.InsertItem(nS+1,tmp); 
			m_ListShowData.SetItemText(nRow, 1,stEpc);
			if(m_CheckUser)
				m_ListShowData.SetItemText(nRow, 2,stUsr);
			if(m_CheckTID)
			{
				m_ListShowData.SetItemText(nRow, 3,stTid);
				
			}
			if(m_CheckPass)
				m_ListShowData.SetItemText(nRow, 4,stPass);

			m_ListShowData.EnsureVisible(nRow, FALSE);

		}
		else
		{
			if(m_CheckUser)
				m_ListShowData.SetItemText(i, 2,stUsr);
			if(m_CheckTID)
			{
				if ( FALSE == stTid.IsEmpty() )
				{
					//��Ϊ�ո�ֵ
					m_ListShowData.SetItemText(i, 3,stTid);
					stTid	=	_T("");
				}
			}
			if(m_CheckPass)
				m_ListShowData.SetItemText(i, 4,stPass);

			m_ListShowData.EnsureVisible(i, FALSE);
		}

		
		tmp=stEpc;
		m_Out.SetWindowText(tmp);
		break;
	case 2:
		//tmp.Format(_T("�ȴ�����������뿨:%d"),lParam); 
		tmp.Format(theApp.g_LoadString("IDWQF_E0035"),lParam); 
		m_Dis.SetWindowText(tmp);
		break;
	case 101:
		//tmp.Format(_T("�ȴ�����������뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_E0036"),lParam/1000,lParam%1000); 
		m_Dis.SetWindowText(tmp);
		break;

	}

	return 0;
}

void CReadISO6C::OnBnClickedButtonDelall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListShowData.DeleteAllItems(); 
}

void CReadISO6C::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRow=m_ListShowData.GetItemCount();
	if(nRow<=0)
	{
		//AfxMessageBox(_T("û��������Ҫ����!"));
		AfxMessageBox(theApp.g_LoadString("IDWQF_E0037"));
		return;
	}

	SYSTEMTIME sysTime;
	char	chCurr[62];
	GetLocalTime(&sysTime);
	memset(chCurr, 0x00, sizeof(chCurr));
	sprintf(chCurr, "%04d%02d%02d%02d%02d%02d.txt",sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour,sysTime.wMinute,sysTime.wSecond);

	CString filename;
	CFileDialog dlg(FALSE, NULL, chCurr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER ,_T("TXT files(*.txt)|*.TXT|")); 
    if(dlg.DoModal()==IDOK)
	{
		filename=dlg.GetPathName();

	}
	else
	{
		return;
	}

	CString sEpcTmp,sUseTmp,sPassTmp,strtmp,sTID;
	
	CFile f;

	f.Open(filename,CFile::modeCreate|CFile::modeReadWrite);
	
    CString tmp=_T(",");

	BYTE str[1024];
	int len;

	for(int i=0;i<nRow;i++)
	{
		strtmp.Empty(); 
		sEpcTmp=m_ListShowData.GetItemText(i,1);
		sUseTmp=m_ListShowData.GetItemText(i,2);
		sTID=m_ListShowData.GetItemText(i,3);
		sPassTmp=m_ListShowData.GetItemText(i,4);
		
		strtmp=sEpcTmp;
		if(m_CheckUser||m_CheckTID||m_CheckPass)
		{
			strtmp=strtmp+tmp;
		}
		if(m_CheckUser)
		{
			strtmp=strtmp+sUseTmp;
			if(m_CheckTID||m_CheckPass)
			{
				strtmp=strtmp+tmp;
			}
		}
		if(m_CheckTID)
		{
			strtmp=strtmp+sTID;
			if(m_CheckPass)
			{
				strtmp=strtmp+tmp;
			}
		}
		if(m_CheckPass)
		{
			strtmp=strtmp+sPassTmp;
		}

		strtmp=strtmp+_T("\r\n");
		len=0;
		memset(str,0,1024);
		//WideCharToMultiByte( CP_ACP, 0, strtmp.GetBuffer(), -1,(char*)str,strtmp.GetLength()*2,NULL,NULL );
		len=strtmp.GetLength();
		memcpy(str, strtmp, len);

		f.Write(str,len); 

	}

	f.Close(); 
}

void CReadISO6C::OnBnClickedButtonDelone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRow=m_ListShowData.GetSelectedCount();

	if(nRow<=0)
	{
		return;
	}
	int  nItem = -1;
    nItem = m_ListShowData.GetNextItem(nItem, LVNI_SELECTED);

	m_ListShowData.DeleteItem(nItem); 

}

//////////////////////////////////////////////////////////////////////////////
//���ƣ�GetExcelDriver
//���ܣ���ȡODBC��Excel����
//���ߣ�
//��֯��δ��������(Future Studio)
//���ڣ�2002.9.1
/////////////////////////////////////////////////////////////////////////////
static CString GetExcelDriver()
{
	CHAR szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	CHAR *pszBuf = szBuf;
	CString sDriver;

	// ��ȡ�Ѱ�װ����������(������odbcinst.h��)
	if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
		return _T("");

	// �����Ѱ�װ�������Ƿ���Excel...
	do
	{
		if (strstr(pszBuf, _T("Excel")) != 0)
		{
			//���� !
			sDriver = CString(pszBuf);
			break;
		}
		pszBuf = strchr(pszBuf, _T('\0')) + 1;
	}
	while (pszBuf[1] != _T('\0'));

	return sDriver;
}

///////////////////////////////////////////////////////////////////////////////
//	BOOL MakeSurePathExists( CString &Path,bool FilenameIncluded)
//	������
//		Path				·��
//		FilenameIncluded	·���Ƿ�����ļ���
//	����ֵ:
//		�ļ��Ƿ����
//	˵��:
//		�ж�Path�ļ�(FilenameIncluded=true)�Ƿ����,���ڷ���TURE�������ڷ���FALSE
//		�Զ�����Ŀ¼
//
///////////////////////////////////////////////////////////////////////////////
static BOOL MakeSurePathExists( CString &Path,
						bool FilenameIncluded)
{
	int Pos=0;
	while((Pos=Path.Find('\\',Pos+1))!=-1)
		CreateDirectory(Path.Left(Pos),NULL);
	if(!FilenameIncluded)
		CreateDirectory(Path,NULL);
	//	return ((!FilenameIncluded)?!_access(Path,0):
	//	!_access(Path.Left(Path.ReverseFind('\\')),0));

	return !_access(Path,0);
}

//���Ĭ�ϵ��ļ���
static BOOL GetDefaultXlsFileName(CString& sExcelFile)
{
	///Ĭ���ļ�����yyyymmddhhmmss.xls
	CString timeStr;
	CTime day;
	day=CTime::GetCurrentTime();
	int filenameday,filenamemonth,filenameyear,filehour,filemin,filesec;
	filenameday=day.GetDay();//dd
	filenamemonth=day.GetMonth();//mm�·�
	filenameyear=day.GetYear();//yyyy
	filehour=day.GetHour();//hh
	filemin=day.GetMinute();//mm����
	filesec=day.GetSecond();//ss
	timeStr.Format(_T("%04d%02d%02d%02d%02d%02d"), filenameyear, filenamemonth, filenameday, filehour, filemin, filesec);

	sExcelFile =  timeStr + _T(".xls");
	// prompt the user (with all document templates)
	CFileDialog dlgFile(FALSE,_T(".xls"),sExcelFile);
	CString title;
	CString strFilter;

	title = _T("����");
	strFilter = _T("Excel�ļ�(*.xls)");
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.xls");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;
	dlgFile.m_ofn.nFilterIndex = 1;
	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;

	if (dlgFile.DoModal()==IDCANCEL)
		return FALSE; // open cancelled
	sExcelFile.ReleaseBuffer();
	if (MakeSurePathExists(sExcelFile,true)) {
		if(!DeleteFile(sExcelFile)) {    // delete the file
			//AfxMessageBox(_T("�����ļ�ʱ����"));
			AfxMessageBox(theApp.g_LoadString("IDWQF_E0038"));
			return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//	void GetExcelDriver(CListCtrl* pList, CString strTitle)
//	������
//		pList		��Ҫ������List�ؼ�ָ��
//		strTitle	���������ݱ����
//	˵��:
//		����CListCtrl�ؼ���ȫ�����ݵ�Excel�ļ���Excel�ļ������û�ͨ�������Ϊ��
//		�Ի�������ָ����������ΪstrTitle�Ĺ�������List�ؼ��ڵ��������ݣ�����
//		��������������ı�����ʽ���浽Excel�������С��������й�ϵ��
//	
//	
///////////////////////////////////////////////////////////////////////////////
static void ExportListToExcel(CListCtrl* pList, CString strTitle, CString sExcelFile)
{
	CString warningStr;
	if (pList->GetItemCount ()>0) {	
		CDatabase database;
		CString sDriver;
		//CString sExcelFile; 
		CString sSql;
		CString tableName = strTitle;

		// �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)" 
		sDriver = GetExcelDriver();
		if (sDriver.IsEmpty())
		{
			// û�з���Excel����
			//AfxMessageBox(_T("û�а�װExcel!\n���Ȱ�װExcel�������ʹ�õ�������!"));
			AfxMessageBox(theApp.g_LoadString("IDWQF_E0039"));
			return;
		}

		///Ĭ���ļ���
		//if (!GetDefaultXlsFileName(sExcelFile))
		//	return;

		// �������д�ȡ���ַ���
		sSql.Format(_T("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s"),sDriver, sExcelFile, sExcelFile);

		// �������ݿ� (��Excel����ļ�)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			// ������ṹ
			int i;
			LVCOLUMN columnData;
			CString columnName;
			int columnNum = 0;
			CString strH;
			CString strV;

			sSql = "";
			strH = "";
			columnData.mask = LVCF_TEXT;
			columnData.cchTextMax =100;
			columnData.pszText = columnName.GetBuffer (100);
			for(i=0;pList->GetColumn(i,&columnData);i++)
			{
				if (i!=0)
				{
					sSql = sSql + _T(", ") ;
					strH = strH + _T(", ") ;
				}
				sSql = sSql + _T(" ") + columnData.pszText +_T(" TEXT");
				strH = strH + _T(" ") + columnData.pszText +_T(" ");
			}
			columnName.ReleaseBuffer ();
			columnNum = i;

			sSql = _T("CREATE TABLE ") + tableName + _T(" ( ") + sSql +  _T(" ) ");
			database.ExecuteSQL(sSql);

			// ����������
			int nItemIndex;
			for (nItemIndex=0;nItemIndex<pList->GetItemCount ();nItemIndex++)
			{
				strV = "";
				for(i=0;i<columnNum;i++)
				{
					if (i!=0)
					{
						strV = strV + _T(", ");
					}
					strV = strV + _T(" '") + pList->GetItemText(nItemIndex,i) +_T("' ");
				}

				sSql = _T("INSERT INTO ")+ tableName 
					+_T(" (")+ strH + _T(")")
					+_T(" VALUES(")+ strV + _T(")");
				database.ExecuteSQL(sSql);
			}

		}      

		// �ر����ݿ�
		database.Close();

		//warningStr.Format(_T("�����ļ�������%s!"),sExcelFile);
		warningStr.Format(theApp.g_LoadString("IDWQF_E0040"),sExcelFile);
		AfxMessageBox(warningStr);
	}
}

//�����ﴦ�����Ǹ���Ȥ����Ϣ����Ҫ�ĸ������ĸ�! 47CΪ�༭��ID
static UINT_PTR CALLBACK OFNHookProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ( WM_NOTIFY == uMsg )
	{
		LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;
		if ( pofn->hdr.code == CDN_FILEOK )
		{
			// ����������Ϳ�����
			_AFX_THREAD_STATE*   pThreadState = AfxGetThreadState(); 
			pThreadState-> m_pAlternateWndInit = NULL;
		}
		else if ( pofn->hdr.code == CDN_TYPECHANGE )
		{
			int nIndex = pofn->lpOFN->nFilterIndex;
			HWND hwndDlg = ::GetParent(hDlg);
			HWND hwndFilter = ::GetDlgItem(hwndDlg, 0x470);
			//������COMBOBOX                 
			char strExt[MAX_PATH] = "";
			WCHAR* wstr = (WCHAR*)SendMessage(hwndFilter, CB_GETITEMDATA, nIndex - 1, 0);
			WideCharToMultiByte (CP_OEMCP, NULL, wstr, -1, strExt, sizeof(strExt), NULL, FALSE);
			if (strcmp(strExt + 1, "*.*") != 0)
			{
				char szFileName[MAX_PATH] = "";
				//::GetDlgItemTextA(hwndDlg, 0x480, szFileName, sizeof(szFileName));//�ļ���EDIT 
				::GetDlgItemTextA(hwndDlg, 0x47C, szFileName, sizeof(szFileName));//�ļ���EDIT 
				PathRemoveExtensionA(szFileName);
				PathAddExtensionA(szFileName, strExt + 1);
				::SetDlgItemTextA(hwndDlg, 0x47C, szFileName);//�ļ���EDIT 
			} 
		}
		
	}

	return 1;
}

void CReadISO6C::OnBnClickedButtonSave2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����EXCEL
	//ExportListToExcel(&m_ListShowData, _T("�žų˷��ھ���"));
	//return;

	//ȡ��ǰ���ڣ�ʱ��
	SYSTEMTIME sysTime;

	GetLocalTime(&sysTime);
	CString strTime;

	strTime.Format(_T("%04d%02d%02d.csv"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);

	int nRow=m_ListShowData.GetItemCount();
	if(nRow<=0)
	{
		//AfxMessageBox(_T("û��������Ҫ����!"));
		AfxMessageBox(theApp.g_LoadString("IDWQF_E0041"));
		return;
	}

	CString fileext;
	CString filename;
	CFileDialog dlg(FALSE,_T(""),strTime,OFN_EXPLORER | OFN_ENABLEHOOK, _T("CSV files(*.csv)|*.csv|Worksheet Files (*.xls)|*.xls||")); 
	dlg.m_ofn.lpfnHook =  (LPOFNHOOKPROC)OFNHookProc;
	dlg.m_ofn.hInstance = AfxGetInstanceHandle();
	
	if(dlg.DoModal()==IDOK)
	{
		filename=dlg.GetPathName();
		//filename=dlg.GetFileName();

	}
	else
	{
		return;
	}
	fileext = dlg.GetFileExt();
	fileext.MakeLower();
	if ( fileext.Find(_T("csv")) >= 0 )
	{
		CString sEpcTmp,sUseTmp,sPassTmp,strtmp,sTID;

		CFile f;

		f.Open(filename,CFile::modeCreate|CFile::modeReadWrite);

		CString tmp=_T(",");

		BYTE str[1024]={0};
		int len;

		CListCtrl* pList = &m_ListShowData;
		LVCOLUMN columnData;
		CString columnName;
		columnData.mask = LVCF_TEXT;
		columnData.cchTextMax =100;
		columnData.pszText = columnName.GetBuffer (100);
		strtmp = _T("");
		for(int i=0;pList->GetColumn(i,&columnData);i++)
		{
			strtmp	+=	columnData.pszText;
			strtmp	=	strtmp+tmp;
			
		}
		strtmp = strtmp.Left(strtmp.GetLength()-1);
		strtmp=strtmp+_T("\r\n");
		len=0;
		memset(str,0,1024);
		//WideCharToMultiByte( CP_ACP, 0, strtmp.GetBuffer(), -1,(char*)str,strtmp.GetLength()*2,NULL,NULL );
		len=strtmp.GetLength();
		memcpy(str, strtmp, len);

		len = strlen((char*)str);
		f.Write(str,len);

		strtmp = _T("");
		for(i=0;i<nRow;i++)
		{
			strtmp.Empty(); 
			strtmp=m_ListShowData.GetItemText(i,0);

			sEpcTmp=m_ListShowData.GetItemText(i,1);
			sUseTmp=m_ListShowData.GetItemText(i,2);
			sTID=m_ListShowData.GetItemText(i,3);
			sPassTmp=m_ListShowData.GetItemText(i,4);

			strtmp=strtmp+tmp;
			strtmp=strtmp+sEpcTmp;
			if(m_CheckUser||m_CheckTID||m_CheckPass)
			{
				strtmp=strtmp+tmp;
			}
			if(m_CheckUser)
			{
				strtmp=strtmp+sUseTmp;
				if(m_CheckTID||m_CheckPass)
				{
					strtmp=strtmp+tmp;
				}
			}
			if(m_CheckTID)
			{
				strtmp=strtmp+sTID;
				if(m_CheckPass)
				{
					strtmp=strtmp+tmp;
				}
			}
			if(m_CheckPass)
			{
				strtmp=strtmp+sPassTmp;
			}

			strtmp=strtmp+_T("\r\n");
			len=0;
			memset(str,0,1024);
			//WideCharToMultiByte( CP_ACP, 0, strtmp.GetBuffer(), -1,(char*)str,strtmp.GetLength()*2,NULL,NULL );
			len=strtmp.GetLength();
			memcpy(str, strtmp, len);

			f.Write(str,len); 

		}

		f.Close();
		//AfxMessageBox(_T("�������!"));
		AfxMessageBox(theApp.g_LoadString("IDWQF_E0042"));
	}
	else if ( fileext.Find(_T("xls")) >= 0 )
	{
		//ExportListToExcel(&m_ListShowData, _T("��ȡ�����б�"), filename);
		ExportListToExcel(&m_ListShowData, theApp.g_LoadString("IDWQF_E0043"), filename);
	}
	else
	{
		//AfxMessageBox(_T("����ʧ��!"));
		AfxMessageBox(theApp.g_LoadString("IDWQF_E0044"));
	}

	return;

}

CString CReadISO6C::ReportError(USHORT res)
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

void CReadISO6C::OnBnClickedButton5SetAlarm6C()
{
	apiReturn res;
	CString str;
	BYTE AccessPassword[4];
	int i;
	BYTE IDTemp[512]={0};
	UpdateData(TRUE);
	
	if (((CComboBox*)GetDlgItem(IDC_COMBO6))->GetCount()<1)
	{
		//MessageBox("Please read first then choose a tag!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_E0054"), theApp.g_LoadString("IDWQB_E0055"), MB_ICONWARNING);
		return;
	}

	str=m_AAccessPassword.SpanIncluding("0123456789ABCDEFabcdef");
	if(strlen(str)!=strlen(m_AAccessPassword))
	{
		//MessageBox("Please input HEX!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_E0056"), theApp.g_LoadString("IDWQB_E0057"), MB_ICONWARNING);
		GetDlgItem(IDC_EDIT12)->SetFocus();
		((CEdit *) GetDlgItem(IDC_EDIT12))->SetSel(0,-1);
		return;
	}
	str=m_AAccessPassword;
	int str_len=strlen(str);
	if (str_len!=8)
	{
		//MessageBox("Please input enough Length of AccessPassword!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQB_E0058"), theApp.g_LoadString("IDWQB_E0059"), MB_ICONWARNING);
		return;
	}
	for(i=0;i<4;i++)
	{
		AccessPassword[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	int CurSel=((CComboBox*)GetDlgItem(IDC_COMBO6))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO6))->GetLBText(CurSel, str);
	BYTE EPC_Word=(BYTE)str.GetLength()/2;

	for(i=0;i<EPC_Word;i++)
	{
		IDTemp[i]=(BYTE)strtol((CString)str[i*2]+(CString)str[2*i+1],NULL,16);
	}

	EPC_Word = EPC_Word / 2;
	for(i=0;i<5;i++)
	{
		Sleep(30);
		switch(ConnectMode)
		{
		case 0://����
			
			break;
		case 1://RS232
		case 3://USB
			res=EPC1G2_ChangeEas(m_hScanner,EPC_Word,IDTemp,m_EasState,AccessPassword,RS485Address);
			break;
		}
		if ((res==_OK) || (res==_password_error))
			break;
	}
	
	if (res==_OK)
	{
		//MessageBox("Set Eas Alarm successfully!","Notice",MB_ICONINFORMATION);
		MessageBox(theApp.g_LoadString("IDWQB_E0060"), theApp.g_LoadString("IDWQB_E0061"), MB_ICONINFORMATION);
	}
	else
	{
		
		str=ReportError(res);
		//if (str=="Unbeknown Error!")
		if (str== theApp.g_LoadString("IDWQB_E0062") )
		{
			//str="Set Eas Alarm Fail!";
			str=theApp.g_LoadString("IDWQB_E0063");
		}
		if (res==0x09)
		{
			//str="The access password is error!";
			str=theApp.g_LoadString("IDWQB_E0064");
		}


		MessageBox(str, theApp.g_LoadString("IDWQB_E0065"),MB_ICONERROR);
	}

	return;
}

void CReadISO6C::OnBnClickedCheck7EasAlarm6C()
{
	
	UpdateData(TRUE);

	int i = 0;
	
	if (m_EasAlarm)
	{
		
		UpdateStatus();
		::SetTimer(g6CReadHwnd, TIME_IDENTIFIER_PARAM, INTERVALTIME_PARAM, CallBack_MyTimeParam);
	}
	else
	{
		::KillTimer(g6CReadHwnd, TIME_IDENTIFIER_PARAM);
		UpdateStatus();
	}
	
	return;
}

void CReadISO6C::OnEasAlarmTest()
{
	apiReturn res;

	switch(ConnectMode)
	{
	case 0://����
		
		break;
	case 1://RS232
	case 3://usb
		res=EPC1G2_EasAlarm(m_hScanner,RS485Address);		
		break;
	}
	if(res==_OK)
	{
		MessageBeep(-1);
		m_APic.SetIcon(AfxGetApp()->LoadIcon(IDI_ICONRED));
	}
	
	Sleep(100);
	m_APic.SetIcon(AfxGetApp()->LoadIcon(IDI_ICONNone));

	return;
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
void WINAPI CReadISO6C::CallBack_MyTimeParam(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime)
{
	//Debug_Printf("r:%s\r\n","hello");
	if ( TIME_IDENTIFIER_PARAM == nIDEvent )
	{
		::PostMessage(g6CReadHwnd, WM_6CREADDATAMSG, 1, 0);
	}
}
