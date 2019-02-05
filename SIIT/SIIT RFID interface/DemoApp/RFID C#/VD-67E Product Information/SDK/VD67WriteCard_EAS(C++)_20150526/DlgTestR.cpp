// DlgTestR.cpp : implementation file
//

#include "stdafx.h"
#include "writecard.h"
#include "DlgTestR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL    nReadThread		=	FALSE;
HANDLE	m_RecvThreadEvent;		//ͨѶ�߳��˳��¼����
/////////////////////////////////////////////////////////////////////////////
// DlgTestR property page

IMPLEMENT_DYNCREATE(DlgTestR, CPropertyPage)

DlgTestR::DlgTestR() : CPropertyPage(DlgTestR::IDD)
{
	//{{AFX_DATA_INIT(DlgTestR)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

DlgTestR::~DlgTestR()
{
}

void DlgTestR::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgTestR)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgTestR, CPropertyPage)
	//{{AFX_MSG_MAP(DlgTestR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgTestR message handlers

BOOL DlgTestR::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_PASST)->SetWindowText("00000000");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgTestR::OnOK() 
{
	// TODO: Add extra validation here
	nReadThread	=	FALSE;
	//�����߳��˳��¼����
	m_RecvThreadEvent	=	CreateEvent(NULL,FALSE,FALSE,NULL);
	hReadThread	=	CreateThread(NULL,0,ReadThreadFuncTag,this,0,NULL);
	if( hReadThread != NULL )
	{		
		nReadThread	=	TRUE;
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
		
	}
	else
	{
		MessageBox("Create ReadThread Error!","Notice",MB_ICONERROR);
		//MessageBox(theApp.g_LoadString("IDWQB_F0038"), theApp.g_LoadString("IDWQB_F0039"),MB_ICONERROR);
		
	}
	//CPropertyPage::OnOK();
}

void DlgTestR::OnCancel() 
{
	// TODO: Add extra cleanup here
	nReadThread	=	FALSE;
	if ( hReadThread != NULL )
	{
		
		//����ͨѶ�߳�
		SetEvent(m_RecvThreadEvent);
		Sleep(100);
		//�ر��߳��˳��¼����
		CloseHandle(m_RecvThreadEvent);
		
		CloseHandle(hReadThread);
		hReadThread   =   NULL;

		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_STATUS_VALUE)->SetWindowText("DisconnectReader");
		
	}

	//CPropertyPage::OnCancel();
}

//�Զ�ģʽ�¶��̺߳���
DWORD WINAPI DlgTestR::ReadThreadFuncTag(LPVOID pParam)
{
	int t;
	DlgTestR *DlgR = (DlgTestR*)pParam;
	apiReturn res	=	_no_scanner;
	int i,j,k,nCounter=0,ID_len=0,ID_len_temp=0;
	CString str,str_temp;
	BYTE temp[512];
	BYTE IDBuffer[30*256];
	
	BYTE mask[512],IDTemp[512];
	int mem,ptr,len,EPC_Word; 
	BYTE AccessPassword[32]={0};

	CString tmp;

	while (nReadThread)
	{
		if (WaitForSingleObject(m_RecvThreadEvent, 0) == WAIT_OBJECT_0)
		{
			nReadThread = FALSE;
			break;
		}
		if(!ifConnectReader)
		{
			DlgR->GetDlgItem(IDC_STATIC_STATUS_VALUE)->SetWindowText("DisconnectReader");//��д�������ѶϿ��Ͽ�������������
			
			break;
		}


		if(1)
		{
			len=0;	//���볤��LEN
			ptr=0;	//������ʼ��ַaddr
			mem=1;	//0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User
			ID_len=0;  
			j=0;
			memset(mask,0,512);
			
			while(nReadThread)
			{
				if (WaitForSingleObject(m_RecvThreadEvent, 0) == WAIT_OBJECT_0)
				{
					nReadThread = FALSE;
					break;
				}
				Sleep(30);
				switch(ConnectMode)
				{
				case 0:		
					break;
				case 1:
					//��EPC��,nCounterΪ���ĸ��������������ݷ���IDBuffer��
					res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,RS485Address);	
					break;
				case 3://usb
					//��EPC��,nCounterΪ���ĸ��������������ݷ���IDBuffer��
					res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,0);
					break;
				}
				if(res==_OK)
				{
					VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_ReadLabelID:OK(%d)\r\n", nCounter);
					if(nCounter==1)
					{
						ID_len=(int)IDBuffer[0];  //IDBuffer[0]ΪWord����;1word=2Byte
						
						memcpy(temp,&IDBuffer[1],ID_len*2);
						
						char chTemp[512]={0};
						Bcd2AscEx(chTemp, (char*)temp, ID_len*2*2);
						
						VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_ReadLabelVl:(%s)\r\n", chTemp);
						
						break;
						
					}
					else
					{
						//SendMessage(epcDlg->m_hWnd,WM_MSG,3,1);//�ж��ſ����ڣ������һ�ſ�
						DlgR->GetDlgItem(IDC_STATIC_STATUS_VALUE)->SetWindowText(theApp.g_LoadString("IDWQF_D0104"));
						Sleep(1000);
					}
				}
				else
				{
					j++;
					t=res*1000+j;
					
					//SendMessage(epcDlg->m_hWnd,WM_MSG,101,t);//�ȴ�д��������뿨:tָ����
					tmp.Format(theApp.g_LoadString("IDWQF_D0108"),t/1000,t%1000); 
					DlgR->GetDlgItem(IDC_STATIC_STATUS_VALUE)->SetWindowText(tmp);
					Sleep(500);
				}
			}



			
			memset(temp,0,512);
			memset(mask,0,512);	
			
			//����д�������
			//WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1,(char *)temp,str.GetLength()*2,NULL,NULL );
			str = "0000000000000000";
			len=str.GetLength();
			memcpy(temp, str, len);
			
			len=str.GetLength()/4;
			k=0;
			i=0;
			
			memcpy(IDTemp,&IDBuffer[1],ID_len*2);//tempΪ���������ݣ�
			EPC_Word=ID_len;  mem=0; ptr=0; j=0;
			memset(AccessPassword,0,4);
			
			//while(nReadThread)
			{
				if (WaitForSingleObject(m_RecvThreadEvent, 0) == WAIT_OBJECT_0)
				{
					nReadThread = FALSE;
					break;
				}
				Sleep(30);
				switch(ConnectMode)
				{
				case 0:		
					break;
				case 1:
					res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,RS485Address);
					break;
				case 3://usb
					res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,0);
					break;
				}
				
				if(res==_OK)
				{
					DlgR->GetDlgItem(IDC_STATIC_STATUS_VALUE)->SetWindowText("Write OK!");
					//break;
				}
				else
				{
					j++;
					t=res*1000+j;
					//SendMessage(epcDlg->m_hWnd,WM_MSG,104,t);//����������д��ʧ�ܣ�����뿨:%d-%d
					tmp.Format(theApp.g_LoadString("IDWQF_D0111"),t/1000,t%1000); 
					DlgR->GetDlgItem(IDC_STATIC_STATUS_VALUE)->SetWindowText(tmp);
					Sleep(1000);
				}
			}

			
		}

	}

	return 0;
}