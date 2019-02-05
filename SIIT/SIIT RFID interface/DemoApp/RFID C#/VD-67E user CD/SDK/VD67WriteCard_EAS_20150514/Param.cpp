// Param.cpp : implementation file
//

#include "stdafx.h"
#include "WriteCard.h"
#include "Param.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//////////////////////////////////////////////////////////////////////////
HWND	gReaderParamHwnd	=	NULL;	//��д������������


/////////////////////////////////////////////////////////////////////////////
// CParam property page

//IMPLEMENT_DYNCREATE(CParam, CPropertyPage)

CParam::CParam() : CPropertyPage(CParam::IDD)
{
	//{{AFX_DATA_INIT(CParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CParam::~CParam()
{
}

void CParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//ClxDialogCProp::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParam, CPropertyPage)
	//{{AFX_MSG_MAP(CParam)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1_MSGET, OnButton1Msget)
	ON_BN_CLICKED(IDC_BUTTON1_MSUPDATE, OnButton1Msupdate)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_READERPARMDATAMSG, OnReaderparmdatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParam message handlers
void CParam::OnInitUIText()//������ı�����
{
	SetWindowText(theApp.g_LoadString("IDWQF_C0001"));//����������
	
	GetDlgItem(IDC_STATIC_HANDVER)->SetWindowText(theApp.g_LoadString("IDWQF_C0002"));//Ӳ���汾��:
	GetDlgItem(IDC_STATIC_SOFTVER)->SetWindowText(theApp.g_LoadString("IDWQF_C0003"));//����汾��:    
	GetDlgItem(IDC_STATIC_BASICPARAM)->SetWindowText(theApp.g_LoadString("IDWQF_C0004"));//��������
	GetDlgItem(IDC_STATIC_MINFREQ)->SetWindowText(theApp.g_LoadString("IDWQF_C0005"));//��С�ز�Ƶ��(MHz):
	GetDlgItem(IDC_STATIC_MAXFREQ)->SetWindowText(theApp.g_LoadString("IDWQF_C0006"));//����ز�Ƶ��(MHz):
	GetDlgItem(IDC_STATIC_OUTPOWER)->SetWindowText(theApp.g_LoadString("IDWQF_C0007"));//��Ƶ�������:
	GetDlgItem(IDC_STATIC_TAGOPT)->SetWindowText(theApp.g_LoadString("IDWQF_C0008"));//����ȡ��ǩ����
	GetDlgItem(IDC_STATIC_MSDATAF)->SetWindowText(theApp.g_LoadString("IDWQF_C0009"));//���ݸ�ʽ
	GetDlgItem(IDC_RADIO1_Hex16)->SetWindowText(theApp.g_LoadString("IDWQF_C0010"));//ʮ������
	GetDlgItem(IDC_RADIO1_Hex10)->SetWindowText(theApp.g_LoadString("IDWQF_C0011"));//ʮ����
	GetDlgItem(IDC_STATIC_MSDATABANK)->SetWindowText(theApp.g_LoadString("IDWQF_C0012"));//������
	GetDlgItem(IDC_RADIO_DATAID)->SetWindowText(theApp.g_LoadString("IDWQF_C0013"));//EPC��
	GetDlgItem(IDC_RADIO_DATAUSER)->SetWindowText(theApp.g_LoadString("IDWQF_C0014"));//�û���
	GetDlgItem(IDC_CHECK1_PERFIX)->SetWindowText(theApp.g_LoadString("IDWQF_C0015"));//ǰ׺
	GetDlgItem(IDC_STATIC_PERFIXT)->SetWindowText(theApp.g_LoadString("IDWQF_C0016"));//ǰ׺ֵ:
	GetDlgItem(IDC_CHECK1_LF)->SetWindowText(theApp.g_LoadString("IDWQF_C0017"));//���س�����
	GetDlgItem(IDC_STATIC_MSDATAB)->SetWindowText(theApp.g_LoadString("IDWQF_C0018"));//���ݵ�ַ
	GetDlgItem(IDC_STATIC_MSDATAStart)->SetWindowText(theApp.g_LoadString("IDWQF_C0019"));//������ʼ��ַ:
	GetDlgItem(IDC_STATIC_MSDATALEN)->SetWindowText(theApp.g_LoadString("IDWQF_C0020"));//����:
	GetDlgItem(IDC_BUTTON1_MSUPDATE)->SetWindowText(theApp.g_LoadString("IDWQF_C0021"));//���²���
	GetDlgItem(IDC_BUTTON1_MSGET)->SetWindowText(theApp.g_LoadString("IDWQF_C0022"));//��ȡ����
	GetDlgItem(IDC_STATIC_HARDID)->SetWindowText(theApp.g_LoadString("IDWQF_C0023"));//Ӳ��ID:
	GetDlgItem(IDC_STATIC_READBET)->SetWindowText(theApp.g_LoadString("IDWQF_C0024"));//�������ʱ��
	GetDlgItem(IDC_STATIC_OUTPUTBET)->SetWindowText(theApp.g_LoadString("IDWQF_C0025"));//��׼������(1-255):

	
	
	
}

void CParam::UpdateStatus()//����ʹ���벻ʹ��
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

BOOL CParam::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//////////////////////////////////////////////////////////////////////////
	UpdateStatus();//����ʹ���벻ʹ��

	if ( ifConnectReader )
	{
		//�����˵�
		//��������
		OnGetParameter();
	}

	//����ҳ
	::PostMessage(gReaderParamHwnd,WM_READERPARMDATAMSG,2,0);	//convert language

	return CPropertyPage::OnSetActive();
}

BOOL CParam::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}

BOOL CParam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	gReaderParamHwnd	=	this->GetSafeHwnd();

	//�����ĳ���ʱ��
	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->AddString("10ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->AddString("20ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->AddString("30ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->AddString("50ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->AddString("100ms");
	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->SetCurSel(0);


	//�汾ֻ��
	GetDlgItem(IDC_EDIT_HANDVER)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_HANDVER2)->EnableWindow(FALSE);

	//��д��ID
	GetDlgItem(IDC_EDIT_HARDID)->EnableWindow(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//selΪ����Ƶ���±�,iminΪ��СƵ���±�,imaxΪ���Ƶ���±�, -1Ϊ��СΪ��С�����Ϊ���
void CParam::OnCbnSetFre(int sel, int imin, int imax)
{
	int i = 0;
	int k = 0;
	int iCount = 0;
	long iValue = 0;
	CString strFreqTmp;
	tagReaderFreq tmpFreq;
	
	CComboBox *m_MinFrequency	=	(CComboBox*)GetDlgItem(IDC_COMBO_MINFREQ);
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

//�����˵�
//��������
void CParam::OnGetParameter()
{
	CString strText;

	UpdateData(TRUE);

	//������������
	strText.Format("%04x", m_HardVersion);
	GetDlgItem(IDC_EDIT_HANDVER)->SetWindowText(strText);
	strText.Format("%04x", m_SoftVersion);
	GetDlgItem(IDC_EDIT_HANDVER2)->SetWindowText(strText);


	//��д��ID
	strText.Format("%s", gReaderID);
	GetDlgItem(IDC_EDIT_HARDID)->SetWindowText(strText);


	//��СƵ��
	//���Ƶ��
	BYTE imin	=	gBasicParam->Min_Frequence-1;
	BYTE imax	=	gBasicParam->Max_Frequence-1;
	OnCbnSetFre(gFre, imin, imax);//��Ϊͨ����������ÿ�����ҵ�Ƶ����Щ��һ����


	//RF power
	strText.Format("%d", gBasicParam->Power);
	GetDlgItem(IDC_EDIT_OUTPOWER)->SetWindowText(strText);


	//���ֱ�ǩ
	//0-6B,1-6C
	((CButton*)GetDlgItem(IDC_RADIO_ISO180006B))->SetCheck((int)(gBasicParam->TagType & 0x01));
	((CButton*)GetDlgItem(IDC_RADIO_ISO180006C))->SetCheck((int)(gBasicParam->TagType & 0x04));
	

	//��ʱ���
	//0-10ms��1-20ms��2-30ms��3-50ms��4-100ms��ȱʡֵΪ2��ÿ���趨ʱ��������ȡһ�α�ǩ��
	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->SetCurSel(gAutoParam->Interval);

	//////////////////////////////////////////////////////////////////////////
	//16�������������10�������
	//0-16��,1-10��
	if ( 0 == Param.DataFormat )
	{
		((CButton*)GetDlgItem(IDC_RADIO1_Hex16))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO1_Hex10))->SetCheck(0);
	}
	else if ( 1 == Param.DataFormat )
	{
		((CButton*)GetDlgItem(IDC_RADIO1_Hex16))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO1_Hex10))->SetCheck(1);
	}


	//������
	//(1)EPC��--0, USER��--1��TID��--2,add by mqs20131216�ĳ���ȡ�Զ�ģʽ�µĲ���
	//if ( Param.DataBank == 0 )
	if ( gAutoParam->IDPosition == 0 )
	{
		((CButton*)GetDlgItem(IDC_RADIO_DATAID))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO_DATAUSER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_DATATID))->SetCheck(0);
	}
	//else if ( Param.DataBank == 1 )
	else if ( gAutoParam->IDPosition == 1 )
	{
		((CButton*)GetDlgItem(IDC_RADIO_DATAID))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_DATAUSER))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO_DATATID))->SetCheck(0);
	}
	//else if ( Param.DataBank == 2 )
	else if ( gAutoParam->IDPosition == 2 )
	{
		((CButton*)GetDlgItem(IDC_RADIO_DATAID))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_DATAUSER))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_DATATID))->SetCheck(1);
	}
	
	//�Ƿ�ǰ׺��1--��,0--����		
	((CButton*)GetDlgItem(IDC_CHECK1_PERFIX))->SetCheck(Param.IsPerfix);

	//ǰ׺ֵ,����0x00���		
	strText.Format("%s", Param.PerfixCode);
	GetDlgItem(IDC_EDIT2_PERFIXVALUE)->SetWindowText(strText);
	
	//�Ƿ�س�����, 1--��,0--����	
	((CButton*)GetDlgItem(IDC_CHECK1_LF))->SetCheck(Param.IsEnter);

	//������ʼ��ַ
	strText.Format("%d", Param.StartAddress);
	GetDlgItem(IDC_EDIT2_MSDATAStart)->SetWindowText(strText);

	//���ݳ���
	strText.Format("%d", Param.DataLen);
	GetDlgItem(IDC_EDIT2_MSDATALEN)->SetWindowText(strText);

	//��׼������(0-255)(0--���ID֮���޼��)
	strText.Format("%d", Param.OutputInterval);
	GetDlgItem(IDC_EDIT_OUTPUTBET)->SetWindowText(strText);

	//////////////////////////////////////////////////////////////////////////

	UpdateData(FALSE);

	return;
}

void CParam::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CParam::OnButton1Msget() 
{
	// TODO: Add your control notification handler code here
	//��ȡ����
	int				i			=	0;
	apiReturn		res			=	_no_scanner;

	UpdateData(TRUE);

	
	for ( i = 0; i < 3; i++ )
	{
		//����������
		res=ReadBasicParam(m_hScanner,gBasicParam);
		if ( _OK == res )
		{
			break;
		}
	}

	if ( _OK == res )
	{
	
		
	}
	else
	{
		//MessageBox("Get fail0!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_C0026"), theApp.g_LoadString("IDWQF_C0027"), MB_ICONWARNING);
		return;
	}
	//////////////////////////////////////////////////////////////////////////


	for ( i = 0; i < 3; i++ )
	{
		//��auto����
		res=ReadAutoParam(m_hScanner,gAutoParam);
		if ( _OK == res )
		{
			break;
		}
	}
	
	if ( _OK == res )
	{
		
		
	}
	else
	{
		//MessageBox("Get fail1!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_C0028"), theApp.g_LoadString("IDWQF_C0029"), MB_ICONWARNING);
		return;
	}
	//////////////////////////////////////////////////////////////////////////


	for ( i = 0; i < 3; i++ )
	{
		//���������
		res=ReadSimParam(m_hScanner,&Param);
		if ( _OK == res )
		{
			break;
		}
	}
	
	if ( _OK == res )
	{
		
		
	}
	else
	{
		//MessageBox("Get fail2!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_C0030"), theApp.g_LoadString("IDWQF_C0031"), MB_ICONWARNING);
		return;
	}

	//�����˵�
	//��������
	OnGetParameter();

	UpdateData(FALSE);

	return;
}

void CParam::OnButton1Msupdate() 
{
	// TODO: Add your control notification handler code here
	//���²���
	int				i			=	0;
	apiReturn		res			=	_no_scanner;
	CString			strText		=	_T("");
	int				iValue		=	0;

	UpdateData(TRUE);
	//��СƵ��
	//���Ƶ��
	CComboBox *m_MinFrequency	=	(CComboBox*)GetDlgItem(IDC_COMBO_MINFREQ);
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
	gBasicParam->Min_Frequence = (BYTE)(imin+1);
	gBasicParam->Max_Frequence = (BYTE)(imax+1);
	
	//RF power
	GetDlgItem(IDC_EDIT_OUTPOWER)->GetWindowText(strText);
	iValue	=	atoi(strText);
	if ((iValue<0) || (iValue>63))
	{
		iValue	=	63;
	}
	gBasicParam->Power	=	(BYTE)iValue;
	
	
	//���ֱ�ǩ,//0-6B,1-6C
	gBasicParam->TagType	=	0x00;
	//6C
	if ( ((CButton*)GetDlgItem(IDC_RADIO_ISO180006C))->GetCheck() == 1 )
	{
		gBasicParam->TagType	= 0x04;
	}
	else
	{
		gBasicParam->TagType	= 0x01;
	}

	for ( i = 0; i < 3; i++ )
	{
		//д��������
		res=WriteBasicParam(m_hScanner,gBasicParam);
		if ( _OK == res )
		{
			break;
		}
	}
	
	if ( _OK == res )
	{
		
		
	}
	else
	{
		//MessageBox("Set fail0!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_C0032"), theApp.g_LoadString("IDWQF_C0033"), MB_ICONWARNING);
		return;
	}
	

	//////////////////////////////////////////////////////////////////////////

	//��ʱ���
	//0-10ms��1-20ms��2-30ms��3-50ms��4-100ms��ȱʡֵΪ2��ÿ���趨ʱ��������ȡһ�α�ǩ��
	gAutoParam->Interval	=	((CComboBox*)GetDlgItem(IDC_COMBO_READBET))->GetCurSel();

	//������
	//(1)EPC��--0, USER��--1��TID��--2,add by mqs20131216�ĳ���ȡ�Զ�ģʽ�µĲ���
	if ( ((CButton*)GetDlgItem(IDC_RADIO_DATAID))->GetCheck() == 1 )
	{
		//Param.DataBank	=	0;
		gAutoParam->IDPosition	=	0;
	}
	if ( ((CButton*)GetDlgItem(IDC_RADIO_DATAUSER))->GetCheck() == 1 )
	{
		//Param.DataBank	=	1;
		gAutoParam->IDPosition	=	1;
	}
	if ( ((CButton*)GetDlgItem(IDC_RADIO_DATATID))->GetCheck() == 1 )
	{
		//Param.DataBank	=	2;
		gAutoParam->IDPosition	=	2;
	}

	for ( i = 0; i < 3; i++ )
	{
		//дauto����
		res=WriteAutoParam(m_hScanner,gAutoParam);
		if ( _OK == res )
		{
			break;
		}
	}
	
	if ( _OK == res )
	{
		
		
	}
	else
	{
		//MessageBox("Set fail1!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_C0034"), theApp.g_LoadString("IDWQF_C0035"), MB_ICONWARNING);
		return;
	}
	


	//////////////////////////////////////////////////////////////////////////
	//16�������������10�������
	//0-16��,1-10��
	if ( ((CButton*)GetDlgItem(IDC_RADIO1_Hex16))->GetCheck() == 1 )
	{
		Param.DataFormat	=	0;
	}
	if ( ((CButton*)GetDlgItem(IDC_RADIO1_Hex10))->GetCheck() == 1 )
	{
		Param.DataFormat	=	1;
	}
	
	
	
	
	//�Ƿ�ǰ׺��1--��,0--����		
	Param.IsPerfix	=	((CButton*)GetDlgItem(IDC_CHECK1_PERFIX))->GetCheck();
	
	//ǰ׺ֵ,����0x00���		
	GetDlgItem(IDC_EDIT2_PERFIXVALUE)->GetWindowText(strText);
	sscanf(strText, "%s", Param.PerfixCode);
	
	//�Ƿ�س�����, 1--��,0--����	
	Param.IsEnter	=	((CButton*)GetDlgItem(IDC_CHECK1_LF))->GetCheck();
	
	//������ʼ��ַ
	GetDlgItem(IDC_EDIT2_MSDATAStart)->GetWindowText(strText);
	Param.StartAddress	=	atoi(strText);
	//sscanf(strText, "%d", Param.StartAddress);
	
	//���ݳ���
	GetDlgItem(IDC_EDIT2_MSDATALEN)->GetWindowText(strText);
	Param.DataLen	=	atoi(strText);
	//sscanf(strText, "%d", Param.DataLen);
	
	
	//��׼������(0-255)(0--���ID֮���޼��)
	GetDlgItem(IDC_EDIT_OUTPUTBET)->GetWindowText(strText);
	Param.OutputInterval	=	atoi(strText);
	//sscanf(strText, "%d", Param.OutputInterval);
	
	//////////////////////////////////////////////////////////////////////////

	for ( i = 0; i < 3; i++ )
	{
		//д�������
		res=WriteSimParam(m_hScanner,&Param);
		if ( _OK == res )
		{
			break;
		}
	}
	
	if ( _OK == res )
	{
		
		
	}
	else
	{
		//MessageBox("Set fail2!","Warning",MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_C0036"), theApp.g_LoadString("IDWQF_C0037"), MB_ICONWARNING);
		return;
	}
	
	UpdateData(FALSE);

	//MessageBox("Set paramter successful!","Info",MB_ICONINFORMATION);
	MessageBox(theApp.g_LoadString("IDWQF_C0038"), theApp.g_LoadString("IDWQF_C0039"), MB_ICONINFORMATION);
	
	return;

}

//WM_READERPARMDATAMSG
afx_msg LRESULT CParam::OnReaderparmdatamsg(WPARAM wParam, LPARAM lParam)
{
	int iwParam	=	(int)wParam;
	int ilParam	=	(int)lParam;
	
	if ( 2 == iwParam )
	{
		OnInitUIText();	//��������
	}
	else if( 0 == iwParam )
	{
		
	}
	
	return 0;
}


