// WriteISO6C.cpp : implementation file
//

#include "stdafx.h"
#include "WriteCard.h"
#include "WriteISO6C.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////�ۺϲ�ѯ���涨ʱ��/////////////////////////////////////
//���嶨ʱ����ID
//ʱ��
#define					TIME_IDENTIFIER_WRITE6C		(500)			//ʱ��ID��
#define					INTERVALTIME____WRITE6C		(1000)			//�೤ʱ��ִ��һ��
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
HWND	g6CWriteHwnd	=	NULL;	//��д��6Cд������
extern char *big_num_add(char *ans, char *first, char *second);


/////////////////////////////////////////////////////////////////////////////
// CWriteISO6C property page

IMPLEMENT_DYNCREATE(CWriteISO6C, CPropertyPage)

CWriteISO6C::CWriteISO6C() : CPropertyPage(CWriteISO6C::IDD)
	, m_BeginData(0)
	, m_Count(1)
	, m_Sum(1)
	, m_DisStr(_T(""))
	, m_Word(0)
	, m_SetEPC(FALSE)
	, m_SetUse(FALSE)
	, m_SetPass(FALSE)
	, m_Time(0)
	, m_Total(0)
	, m_Falsh(0)
	, m_Mod(0)
	, m_True(0)
	, m_False(0)
	, m_End(_T(""))
	, m_Befro(_T(""))
	, m_CBefor(FALSE)
	, m_CEnd(FALSE)
	, m_WriteMode(0)
{
	//{{AFX_DATA_INIT(CWriteISO6C)
	//}}AFX_DATA_INIT

	iFlagProtectOpt	=	0;//0---������(����), 1---ʹ����������2---��Զ��ס(����), 3---EAS����(add by martrin20140514)
	strcpy((char*)AccessPassword, "12341234");


}

CWriteISO6C::~CWriteISO6C()
{
}

void CWriteISO6C::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriteISO6C)
	DDX_Control(pDX, IDC_LIST_INDATA, m_ListInData);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_Count);
	DDX_Text(pDX, IDC_EDIT_SUM, m_Sum);
	DDX_Text(pDX, IDC_EDIT_XXXX, m_DisStr);
	DDX_CBIndex(pDX, IDC_COMBO_WORD, m_Word);
	DDX_Check(pDX, IDC_CHECK_EPC, m_SetEPC);
	DDX_Check(pDX, IDC_CHECK_USE, m_SetUse);
	DDX_Check(pDX, IDC_CHECK_PASS, m_SetPass);
	DDX_Control(pDX, IDC_LIST_OUTDATA, m_ListOutData);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Time);
	DDV_MinMaxUInt(pDX, m_Time, 1, 1000);
	DDX_Control(pDX, IDC_STATIC_PIC, m_MsgImg);
	DDX_Control(pDX, IDC_STATIC_DIS, m_MsgDis);
	DDX_Control(pDX, IDC_STATIC_OUT, m_MsgOut);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_Total);
	DDX_Text(pDX, IDC_EDIT_FALSH, m_Falsh);
	DDX_Text(pDX, IDC_EDIT_MOD, m_Mod);
	DDX_Text(pDX, IDC_EDIT_TRUE, m_True);
	DDX_Text(pDX, IDC_EDIT_FALSE, m_False);
	DDX_Text(pDX, IDC_EDIT_END, m_End);
	DDX_Text(pDX, IDC_EDIT_BEFOR, m_Befro);
	DDX_Check(pDX, IDC_CHECK_BEFOR, m_CBefor);
	DDX_Check(pDX, IDC_CHECK_END, m_CEnd);
	DDX_Control(pDX, IDC_STATIC_IN, m_MsgIn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWriteISO6C, CPropertyPage)
	//{{AFX_MSG_MAP(CWriteISO6C)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_DATA, OnBnClickedButtonData)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnBnClickedButtonFile)
	ON_CBN_SELENDOK(IDC_COMBO_WORD, OnCbnSelendokComboWord)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, OnBnClickedButtonMove)
	ON_CBN_KILLFOCUS(IDC_COMBO_WORD, OnCbnKillfocusComboWord)
	ON_MESSAGE(WM_MSG,WriteMsg)
	ON_BN_CLICKED(IDC_BUTTON_DELALL, OnBnClickedButtonDelall)
	ON_BN_CLICKED(IDC_BUTTON_DELOUT, OnBnClickedButtonDelout)
	ON_BN_CLICKED(IDC_RADIO_EPC, OnBnClickedRadioEpc)
	ON_BN_CLICKED(IDC_RADIO_USER, OnBnClickedRadioUser)
	ON_BN_CLICKED(IDC_RADIO_PASS, OnBnClickedRadioPass)
	ON_BN_CLICKED(IDC_BUTTON_INDATA, OnBnClickedButtonIndata)
	ON_BN_CLICKED(IDC_CHECK_EPC, OnBnClickedCheckEpc)
	ON_BN_CLICKED(IDC_CHECK_USE, OnBnClickedCheckUse)
	ON_BN_CLICKED(IDC_CHECK_PASS, OnBnClickedCheckPass)
	ON_BN_CLICKED(IDC_BUTTON_SUCCESS, OnBnClickedButtonSuccess)
	ON_BN_CLICKED(IDC_BUTTON_ERROR, OnBnClickedButtonError)
	ON_BN_CLICKED(IDC_CHECK_LOCKEPC_PASS, OnBnClickedCheckLockepcPass)
	ON_BN_CLICKED(IDC_CHECK_LOCKEPC_Neverwriteable, OnBnClickedCheckLockepcNeverwriteable)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_6CWRITEDATAMSG, On6cWritedatamsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteISO6C message handlers
void CWriteISO6C::OnInitUIText()//������ı�����
{
	SetWindowText(theApp.g_LoadString("IDWQF_D0001"));//дISO18000-6C���͵��ӱ�ǩ
	
	
	GetDlgItem(IDC_STATIC_DATABIT)->SetWindowText(theApp.g_LoadString("IDWQF_D0002"));//����λ��(Word)
	GetDlgItem(IDC_STATIC_XUHAO)->SetWindowText(theApp.g_LoadString("IDWQF_D0003"));//��ʼ���
	GetDlgItem(IDC_STATIC_BUCHANG)->SetWindowText(theApp.g_LoadString("IDWQF_D0004"));//�ۼӲ���
	GetDlgItem(IDC_BUTTON_DATA)->SetWindowText(theApp.g_LoadString("IDWQF_D0005"));//��������������
	GetDlgItem(IDC_STATIC_MAKENUM)->SetWindowText(theApp.g_LoadString("IDWQF_D0006"));//��������
	GetDlgItem(IDC_STATIC_LISTD)->SetWindowText(theApp.g_LoadString("IDWQF_D0007"));//��д�������б�
	GetDlgItem(IDC_STATIC_CODESET)->SetWindowText(theApp.g_LoadString("IDWQF_D0008"));//�����������
	GetDlgItem(IDC_BUTTON_FILE)->SetWindowText(theApp.g_LoadString("IDWQF_D0009"));//�����������ɹ���
	GetDlgItem(IDC_STATIC_SAVEOPT)->SetWindowText(theApp.g_LoadString("IDWQF_D0010"));//������
	GetDlgItem(IDC_STATIC_NUMT)->SetWindowText(theApp.g_LoadString("IDWQF_D0011"));//��������
	GetDlgItem(IDC_STATIC_SHENGNUM)->SetWindowText(theApp.g_LoadString("IDWQF_D0012"));//ʣ����
	GetDlgItem(IDC_STATIC_SUCCESSNUM)->SetWindowText(theApp.g_LoadString("IDWQF_D0013"));//�ɹ���
	GetDlgItem(IDC_STATIC_FINISHNUM)->SetWindowText(theApp.g_LoadString("IDWQF_D0014"));//�����
	GetDlgItem(IDC_STATIC_FAILNUM)->SetWindowText(theApp.g_LoadString("IDWQF_D0015"));//ʧ����
	GetDlgItem(IDC_STATIC_W6CEXAMPLE)->SetWindowText(theApp.g_LoadString("IDWQF_D0016"));//ʾ��
	GetDlgItem(IDC_CHECK_BEFOR)->SetWindowText(theApp.g_LoadString("IDWQF_D0017"));//ǰ׺
	GetDlgItem(IDC_CHECK_END)->SetWindowText(theApp.g_LoadString("IDWQF_D0018"));//��׺
	GetDlgItem(IDC_STATIC_BETT)->SetWindowText(theApp.g_LoadString("IDWQF_D0019"));//���ʱ��:��
	GetDlgItem(IDC_BUTTON_WRITE)->SetWindowText(theApp.g_LoadString("IDWQF_D0020"));//��ʼд��
	GetDlgItem(IDC_BUTTON_STOP)->SetWindowText(theApp.g_LoadString("IDWQF_D0021"));//��ͣд��
	GetDlgItem(IDC_BUTTON_MOVE)->SetWindowText(theApp.g_LoadString("IDWQF_D0022"));//�Ƴ���ǰ����
	GetDlgItem(IDC_STATIC_WRITEOP)->SetWindowText(theApp.g_LoadString("IDWQF_D0023"));//д������
	GetDlgItem(IDC_CHECK_USE)->SetWindowText(theApp.g_LoadString("IDWQF_D0024"));//�û���
	GetDlgItem(IDC_CHECK_PASS)->SetWindowText(theApp.g_LoadString("IDWQF_D0025"));//������
	GetDlgItem(IDC_STATIC_FINLIST)->SetWindowText(theApp.g_LoadString("IDWQF_D0026"));//��������б�
	GetDlgItem(IDC_BUTTON_SUCCESS)->SetWindowText(theApp.g_LoadString("IDWQF_D0027"));//���ɳɹ�����TXT
	GetDlgItem(IDC_BUTTON_ERROR)->SetWindowText(theApp.g_LoadString("IDWQF_D0028"));//����ʧ������TXT
	GetDlgItem(IDC_BUTTON_DELOUT)->SetWindowText(theApp.g_LoadString("IDWQF_D0029"));//�����������б�
	GetDlgItem(IDC_STATIC_DIS)->SetWindowText(theApp.g_LoadString("IDWQF_D0030"));//״̬
	GetDlgItem(IDC_STATIC_OUT)->SetWindowText(theApp.g_LoadString("IDWQF_D0031"));//����
	GetDlgItem(IDC_BUTTON_DELALL)->SetWindowText(theApp.g_LoadString("IDWQF_D0032"));//���д�������б�
	GetDlgItem(IDC_STATIC_WWriteDATA)->SetWindowText(theApp.g_LoadString("IDWQF_D0033"));//��д������
	GetDlgItem(IDC_STATIC_IN)->SetWindowText(theApp.g_LoadString("IDWQF_D0034"));//����
	GetDlgItem(IDC_STATIC_WWriteSTAT)->SetWindowText(theApp.g_LoadString("IDWQF_D0035"));//д��״̬
	GetDlgItem(IDC_STATIC_FWriteData)->SetWindowText(theApp.g_LoadString("IDWQF_D0036"));//д������
	GetDlgItem(IDC_STATIC_STATTIP)->SetWindowText(theApp.g_LoadString("IDWQF_D0037"));//״̬��ʾ
	GetDlgItem(IDC_RADIO_USER)->SetWindowText(theApp.g_LoadString("IDWQF_D0038"));//�û���
	GetDlgItem(IDC_RADIO_PASS)->SetWindowText(theApp.g_LoadString("IDWQF_D0039"));//������
	GetDlgItem(IDC_BUTTON_INDATA)->SetWindowText(theApp.g_LoadString("IDWQF_D0040"));//��������
	GetDlgItem(IDC_CHECK_LOCKEPC_PASS)->SetWindowText(theApp.g_LoadString("IDWQF_D0041"));//ʹ������д
	GetDlgItem(IDC_STATIC_ProtectEPCA)->SetWindowText(theApp.g_LoadString("IDWQF_D0042"));//EPC����
	GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable)->SetWindowText(theApp.g_LoadString("IDWQF_D0043"));//��Զ����д
	GetDlgItem(IDC_STATIC_USERPASS)->SetWindowText(theApp.g_LoadString("IDWQF_D0044"));//����:
	GetDlgItem(IDC_STATIC_PASSFR)->SetWindowText(theApp.g_LoadString("IDWQF_D0045"));//����
	GetDlgItem(IDC_CHECK_LOCKEPC_EAS_ALARM)->SetWindowText(theApp.g_LoadString("IDWQF_D0121"));//EAS����
	
	
	int nS=m_ListInData.GetItemCount();
	if ( nS == 0 )
	{
		m_ListInData.DeleteColumn(0);
		m_ListInData.DeleteColumn(0);
		m_ListInData.DeleteColumn(0);
		m_ListInData.DeleteColumn(0);
		m_ListInData.InsertColumn( 0, theApp.g_LoadString("IDWQF_D0046"), LVCFMT_LEFT, 40 );
		m_ListInData.InsertColumn( 1, theApp.g_LoadString("IDWQF_D0047"), LVCFMT_LEFT, 220 );
		m_ListInData.InsertColumn( 2, theApp.g_LoadString("IDWQF_D0048"), LVCFMT_LEFT, 220 );
		m_ListInData.InsertColumn( 3, theApp.g_LoadString("IDWQF_D0049"), LVCFMT_LEFT, 120 );
	}

	nS=m_ListOutData.GetItemCount();
	if ( nS ==  0 )
	{
		m_ListOutData.DeleteColumn(0);
		m_ListOutData.DeleteColumn(0);
		m_ListOutData.DeleteColumn(0);
		m_ListOutData.DeleteColumn(0);
		m_ListOutData.DeleteColumn(0);
		m_ListOutData.InsertColumn( 0, theApp.g_LoadString("IDWQF_D0050"), LVCFMT_LEFT, 40 );
		m_ListOutData.InsertColumn( 1, theApp.g_LoadString("IDWQF_D0051"), LVCFMT_LEFT, 200 );
		m_ListOutData.InsertColumn( 2, theApp.g_LoadString("IDWQF_D0052"), LVCFMT_LEFT, 200 );
		m_ListOutData.InsertColumn( 3, theApp.g_LoadString("IDWQF_D0053"), LVCFMT_LEFT, 120 );
		m_ListOutData.InsertColumn( 4, theApp.g_LoadString("IDWQF_D0054"), LVCFMT_LEFT, 80 );
	}
	
}

void CWriteISO6C::UpdateStatus()//����ʹ���벻ʹ��
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

BOOL CWriteISO6C::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	g6CWriteHwnd	=	this->GetSafeHwnd();
	
	int i = 0;
	CString strTemp	=	_T("");
	DWORD dwStyle = m_ListInData.GetExtendedStyle(); 
	
    //ѡ��ĳ��ʹ���и߶�
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;//������
	
    m_ListInData.SetExtendedStyle(dwStyle); //������չ���
	
	
	
    //m_ListInData.SetBkColor(RGB(200, 200, 200)); //���ñ�����ɫ
    //m_ListInData.SetTextBkColor(RGB(200, 200, 200)); //�����ı�������ɫ
    //m_ListInData.SetTextColor(RGB(10, 10, 80)); //�����ı���ɫ

	
    //�����еı���
    //m_ListInData.InsertColumn( 0, _T("���"), LVCFMT_LEFT, 40 );
    //m_ListInData.InsertColumn( 1, _T("EPC��"), LVCFMT_LEFT, 220 );
    //m_ListInData.InsertColumn( 2, _T("�û���"), LVCFMT_LEFT, 220 );
	//m_ListInData.InsertColumn( 3, _T("������"), LVCFMT_LEFT, 120 );
	m_ListInData.DeleteColumn(0);
	m_ListInData.DeleteColumn(0);
	m_ListInData.DeleteColumn(0);
	m_ListInData.DeleteColumn(0);
	m_ListInData.InsertColumn( 0, theApp.g_LoadString("IDWQF_D0046"), LVCFMT_LEFT, 40 );
    m_ListInData.InsertColumn( 1, theApp.g_LoadString("IDWQF_D0047"), LVCFMT_LEFT, 220 );
    m_ListInData.InsertColumn( 2, theApp.g_LoadString("IDWQF_D0048"), LVCFMT_LEFT, 220 );
	m_ListInData.InsertColumn( 3, theApp.g_LoadString("IDWQF_D0049"), LVCFMT_LEFT, 120 );
	
	
	dwStyle = m_ListOutData.GetExtendedStyle(); 
	
    //ѡ��ĳ��ʹ���и߶�
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;//������
	
    m_ListOutData.SetExtendedStyle(dwStyle); //������չ���
	
	
	
    //m_ListInData.SetBkColor(RGB(200, 200, 200)); //���ñ�����ɫ
    //m_ListInData.SetTextBkColor(RGB(200, 200, 200)); //�����ı�������ɫ
    //m_ListInData.SetTextColor(RGB(10, 10, 80)); //�����ı���ɫ
	
	
    //�����еı���
    //m_ListOutData.InsertColumn( 0, _T("���"), LVCFMT_LEFT, 40 );
    //m_ListOutData.InsertColumn( 1, _T("EPC��"), LVCFMT_LEFT, 200 );
    //m_ListOutData.InsertColumn( 2, _T("�û���"), LVCFMT_LEFT, 200 );
	//m_ListOutData.InsertColumn( 3, _T("������"), LVCFMT_LEFT, 120 );
	//m_ListOutData.InsertColumn( 4, _T("״̬"), LVCFMT_LEFT, 80 );
	m_ListOutData.InsertColumn( 0, theApp.g_LoadString("IDWQF_D0050"), LVCFMT_LEFT, 40 );
    m_ListOutData.InsertColumn( 1, theApp.g_LoadString("IDWQF_D0051"), LVCFMT_LEFT, 200 );
    m_ListOutData.InsertColumn( 2, theApp.g_LoadString("IDWQF_D0052"), LVCFMT_LEFT, 200 );
	m_ListOutData.InsertColumn( 3, theApp.g_LoadString("IDWQF_D0053"), LVCFMT_LEFT, 120 );
	m_ListOutData.InsertColumn( 4, theApp.g_LoadString("IDWQF_D0054"), LVCFMT_LEFT, 80 );

	
	strEpc="0054100B";
	
	stInData.nLog=0; 
	
	m_SetEPC=TRUE;
	
	m_Time=1;
	
	nStop=0;
	
	nWord=0;
	
	((CButton *)GetDlgItem(IDC_RADIO_EPC))->SetCheck(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_USERPASS))->SetLimitText(8);//����Ϊ8���ַ�
	((CEdit*)GetDlgItem(IDC_EDIT_USERPASS))->SetWindowText(_T("11112222"));//ϵͳĬ��
	
	
	//default
	((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_USERPASS)->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable))->EnableWindow(TRUE);
	
	UpdateData(FALSE);
	
	for (i = 0; i < 9; i++)
	{
		strTemp.Format(_T("%d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->AddString(strTemp);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->SetCurSel(0);


	//������
	//int nRow=m_ListOutData.InsertItem(0,_T("2"));
	//m_ListOutData.SetItemText(nRow, 1, _T("ABCD"));
	//m_ListOutData.SetItemText(nRow, 2, _T("ABCE"));
	//m_ListOutData.SetItemText(nRow, 3, _T("ABCF"));
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWriteISO6C::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CPropertyPage::OnCancel();
}

//WM_6CWRITEDATAMSG
LRESULT CWriteISO6C::On6cWritedatamsg(WPARAM wParam, LPARAM lParam)
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

BOOL CWriteISO6C::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}

BOOL CWriteISO6C::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//6Cдҳ
	::PostMessage(g6CWriteHwnd,WM_6CWRITEDATAMSG,2,0);	//convert language

	return CPropertyPage::OnSetActive();
}

void CWriteISO6C::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
#if 1
void CWriteISO6C::OnBnClickedButtonData()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CString strTemp;
	CString epcData;
	UINT i=0;
	CString tmp;
	int nBLen;
	int nELen;

	GetDlgItem(IDC_EDIT_BEGIN)->GetWindowText(strTemp);

    if(m_Count<=0)
	{
		//MessageBox(_T("�ۼӲ�������С�ڵ���0"),_T("����"),MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_D0055"), theApp.g_LoadString("IDWQF_D0056"), MB_ICONWARNING);
		return;
	}

	if(m_Count<=0)
	{
		//MessageBox(_T("������������С�ڵ���0"),_T("����"),MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_D0057"), theApp.g_LoadString("IDWQF_D0058"), MB_ICONWARNING);
		return;
	}

	int j;

	j=m_WriteMode+1;

	if(nStatus)
	{
		CString str;
		if((m_CBefor)&&(!m_CEnd))
		{
			nBLen=m_Befro.GetLength(); 
			if((nBLen<4)||((nBLen%4)!=0)||(nBLen>=m_Word*4))
			{
				//MessageBox(_T("ǰ׺���ݴ���"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0059"), theApp.g_LoadString("IDWQF_D0060"), MB_ICONWARNING);
				return;
			}
			str=m_Befro.SpanIncluding(_T("0123456789ABCDEFabcdef"));

			if(str.GetLength()!=nBLen)
			{
				//MessageBox(_T("ǰ׺���ݴ���:0-9,A-F"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0061"), theApp.g_LoadString("IDWQF_D0062"), MB_ICONWARNING);
				return;
			}
			
			m_ListInData.DeleteAllItems();
			int nB=m_BeginData;

			for(i=0;i<m_Sum;i++)
			{
				switch((((m_Word*4)-nBLen)/4))
				{
				case 1:
					//epcData.Format(_T("%s%04X"),m_Befro,nB);
					epcData.Format(_T("%s%04s"),m_Befro,strTemp);
					break;
				case 2:
					//epcData.Format(_T("%s%08X"),m_Befro,nB);
					epcData.Format(_T("%s%08s"),m_Befro,strTemp);
					break;
				case 3:
					//epcData.Format(_T("%s%012X"),m_Befro,nB);
					epcData.Format(_T("%s%012s"),m_Befro,strTemp);
					break;
				case 4:
					//epcData.Format(_T("%s%016X"),m_Befro,nB);
					epcData.Format(_T("%s%016s"),m_Befro,strTemp);
					break;
				case 5:
					//epcData.Format(_T("%s%020X"),m_Befro,nB);
					epcData.Format(_T("%s%020s"),m_Befro,strTemp);
					break;
				case 6:
					//epcData.Format(_T("%s%020X"),m_Befro,nB);
					epcData.Format(_T("%s%024s"),m_Befro,strTemp);
					break;
				case 7:
					//epcData.Format(_T("%s%020X"),m_Befro,nB);
					epcData.Format(_T("%s%028s"),m_Befro,strTemp);
					break;
				default:
					//MessageBox(_T("ǰ׺�������ô���"),_T("����"),MB_ICONWARNING);
					MessageBox(theApp.g_LoadString("IDWQF_D0063"), theApp.g_LoadString("IDWQF_D0064"), MB_ICONWARNING);
					return;
					break;
				}
				nB=nB+m_Count;
				char chixA[255] = {0};
				char chixB[255] = {0};
				char chixC[255] = {0};
				strcpy(chixA, strTemp);
				sprintf(chixB, "%x", m_Count);
				big_num_add(chixC, chixA, chixB);
				strTemp = chixC;

				epcData.MakeUpper();

				int nS=m_ListInData.GetItemCount(); 

				tmp.Format(_T("%d"),nS+1);

				int nRow=m_ListInData.InsertItem(nS,tmp); 

				m_ListInData.SetItemText(nRow, j, epcData);
			}
		}

		if((m_CEnd)&&(!m_CBefor))
		{
			nELen=m_End.GetLength(); 
			if((nELen<4)||((nELen%4)!=0)||(nELen>=m_Word*4))
			{
				//MessageBox(_T("��׺���ݴ���"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0065"), theApp.g_LoadString("IDWQF_D0066"), MB_ICONWARNING);
				return;
			}
			str=m_End.SpanIncluding(_T("0123456789ABCDEFabcdef"));

			if(str.GetLength()!=nELen)
			{
				//MessageBox(_T("��׺���ݴ���:0-9,A-F"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0067"), theApp.g_LoadString("IDWQF_D0068"), MB_ICONWARNING);
				return;
			}

			m_ListInData.DeleteAllItems();
			int nB=m_BeginData;

			for(i=0;i<m_Sum;i++)
			{
				switch((((m_Word*4)-nELen)/4))
				{
				case 1:
					//epcData.Format(_T("%04X%s"),nB,m_End);
					epcData.Format(_T("%04s%s"),strTemp,m_End);
					break;
				case 2:
					//epcData.Format(_T("%08X%s"),nB,m_End);
					epcData.Format(_T("%08s%s"),strTemp,m_End);
					break;
				case 3:
					//epcData.Format(_T("%012X%s"),nB,m_End);
					epcData.Format(_T("%012s%s"),strTemp,m_End);
					break;
				case 4:
					//epcData.Format(_T("%016X%s"),nB,m_End);
					epcData.Format(_T("%016s%s"),strTemp,m_End);
					break;
				case 5:
					//epcData.Format(_T("%020X%s"),nB,m_End);
					epcData.Format(_T("%020s%s"),strTemp,m_End);
					break;
				case 6:
					//epcData.Format(_T("%024X%s"),nB,m_End);
					epcData.Format(_T("%024s%s"),strTemp,m_End);
					break;
				case 7:
					//epcData.Format(_T("%028X%s"),nB,m_End);
					epcData.Format(_T("%028s%s"),strTemp,m_End);
					break;
				default:
					//MessageBox(_T("���������ô���"),_T("����"),MB_ICONWARNING);
					MessageBox(theApp.g_LoadString("IDWQF_D0069"), theApp.g_LoadString("IDWQF_D0070"), MB_ICONWARNING);
					return;
					break;
				}
				nB=nB+m_Count;
				char chixA[255] = {0};
				char chixB[255] = {0};
				char chixC[255] = {0};
				strcpy(chixA, strTemp);
				sprintf(chixB, "%x", m_Count);
				big_num_add(chixC, chixA, chixB);
				strTemp = chixC;

				epcData.MakeUpper();

				int nS=m_ListInData.GetItemCount(); 

				tmp.Format(_T("%d"),nS+1);

				int nRow=m_ListInData.InsertItem(nS,tmp); 

				m_ListInData.SetItemText(nRow, j, epcData);
			}
		}

		if(m_CEnd&&m_CBefor)
		{
			nBLen=m_Befro.GetLength(); 
			if((nBLen<4)||((nBLen%4)!=0)||(nBLen>=m_Word*4))
			{
				//MessageBox(_T("ǰ׺���ݴ���"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0071"), theApp.g_LoadString("IDWQF_D0072"), MB_ICONWARNING);
				return;
			}
			str=m_Befro.SpanIncluding(_T("0123456789ABCDEFabcdef"));

			if(str.GetLength()!=nBLen)
			{
				//MessageBox(_T("ǰ׺���ݴ���:0-9,A-F"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0073"), theApp.g_LoadString("IDWQF_D0074"), MB_ICONWARNING);
				return;
			}

			nELen=m_End.GetLength(); 
			if((nELen<4)||((nELen%4)!=0)||(nELen>=m_Word*4))
			{
				//MessageBox(_T("��׺���ݴ���"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0075"), theApp.g_LoadString("IDWQF_D0076"), MB_ICONWARNING);
				return;
			}
			str=m_End.SpanIncluding(_T("0123456789ABCDEFabcdef"));

			if(str.GetLength()!=nELen)
			{
				//MessageBox(_T("��׺���ݴ���:0-9,A-F"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0077"), theApp.g_LoadString("IDWQF_D0078"), MB_ICONWARNING);
				return;
			}

			if((nBLen+nELen)>=m_Word*4)
			{
				//MessageBox(_T("ǰ׺�ͺ�׺���ݳ��ȴ���"),_T("����"),MB_ICONWARNING);
				MessageBox(theApp.g_LoadString("IDWQF_D0079"), theApp.g_LoadString("IDWQF_D0080"), MB_ICONWARNING);
				return;
			}

			m_ListInData.DeleteAllItems();
			int nB=m_BeginData;
			

			for(i=0;i<m_Sum;i++)
			{
				switch((((m_Word*4)-nBLen-nELen)/4))
				{
				case 1:
					//epcData.Format(_T("%s%04X%s"),m_Befro,nB,m_End);
					epcData.Format(_T("%s%04s%s"),m_Befro,strTemp,m_End);
					break;
				case 2:
					//epcData.Format(_T("%s%08X%s"),m_Befro,nB,m_End);
					epcData.Format(_T("%s%08s%s"),m_Befro,strTemp,m_End);
					break;
				case 3:
					//epcData.Format(_T("%s%012X%s"),m_Befro,nB,m_End);
					epcData.Format(_T("%s%012s%s"),m_Befro,strTemp,m_End);
					break;
				case 4:
					//epcData.Format(_T("%s%016X%s"),m_Befro,nB,m_End);
					epcData.Format(_T("%s%016s%s"),m_Befro,strTemp,m_End);
					break;
				case 5:
					//epcData.Format(_T("%s%020X%s"),m_Befro,nB,m_End);
					epcData.Format(_T("%s%020s%s"),m_Befro,strTemp,m_End);
					break;
				case 6:
					//epcData.Format(_T("%s%024X%s"),m_Befro,nB,m_End);
					epcData.Format(_T("%s%024s%s"),m_Befro,strTemp,m_End);
					break;
				default:
					//MessageBox(_T("���������ô���"),_T("����"),MB_ICONWARNING);
					MessageBox(theApp.g_LoadString("IDWQF_D0081"), theApp.g_LoadString("IDWQF_D0082"), MB_ICONWARNING);
					return;
					break;
				}
				nB=nB+m_Count;
				char chixA[255] = {0};
				char chixB[255] = {0};
				char chixC[255] = {0};
				strcpy(chixA, strTemp);
				sprintf(chixB, "%x", m_Count);
				big_num_add(chixC, chixA, chixB);
				strTemp = chixC;
				epcData.MakeUpper();

				int nS=m_ListInData.GetItemCount(); 

				tmp.Format(_T("%d"),nS+1);

				int nRow=m_ListInData.InsertItem(nS,tmp); 

				m_ListInData.SetItemText(nRow, j, epcData);
			}
		}

		if(!m_CEnd&&!m_CBefor)
		{
			m_ListInData.DeleteAllItems();

			int nB=m_BeginData;
			GetDlgItem(IDC_EDIT_BEGIN)->GetWindowText(strTemp);

			for(i=0;i<m_Sum;i++)
			{
				switch(m_Word)
				{
				case 1:
					//epcData.Format(_T("%04X"),nB);
					epcData.Format(_T("%04s"),strTemp);
					break;
				case 2:
					//epcData.Format(_T("%08X"),nB);
					epcData.Format(_T("%08s"),strTemp);
					break;
				case 3:
					//epcData.Format(_T("%012X"),nB);
					epcData.Format(_T("%012s"),strTemp);
					break;
				case 4:
					//epcData.Format(_T("%016X"),nB);
					epcData.Format(_T("%016s"),strTemp);
					break;
				case 5:
					//epcData.Format(_T("%020X"),nB);
					epcData.Format(_T("%020s"),strTemp);
					break;
				case 6:
					//epcData.Format(_T("%024X"),nB);
					epcData.Format(_T("%024s"),strTemp);
					break;
				case 7:
					//epcData.Format(_T("%028X"),nB);
					epcData.Format(_T("%028s"),strTemp);
					break;
				default:
					//epcData.Format(_T("%032X"),nB);
					epcData.Format(_T("%032s"),strTemp);
					break;
				}
				nB=nB+m_Count;
				char chixA[255] = {0};
				char chixB[255] = {0};
				char chixC[255] = {0};
				strcpy(chixA, strTemp);
				sprintf(chixB, "%x", m_Count);
				big_num_add(chixC, chixA, chixB);
				strTemp = chixC;

				epcData.MakeUpper();

				int nS=m_ListInData.GetItemCount(); 

				tmp.Format(_T("%d"),nS+1);

				int nRow=m_ListInData.InsertItem(nS,tmp); 

				m_ListInData.SetItemText(nRow, j, epcData);
			}
		}
	}
	else
	{
		//�������ļ����������б�
		int nB=stStartNo.nBegin;
		int nN=stStartNo.nNumber;
		int nO=stStartNo.nOne;

		m_ListInData.DeleteAllItems();

		for(i=0;i<(UINT)stStartNo.nTotal;i++)
		{
			epcData.Format(_T("%06d000000000000%06d"),nB,nN);
			nB=nB+stStartNo.nCount;
			nN=nN+stStartNo.nCount;
//			if((10000-nB)==0)
//			{
//				nB=0;
//				nO++;
//			}

			epcData.MakeUpper();

			int nS=m_ListInData.GetItemCount(); 

			tmp.Format(_T("%d"),nS+1);

			int nRow=m_ListInData.InsertItem(nS,tmp); 

			m_ListInData.SetItemText(nRow, 1, epcData);
		}

	/*	for(i=0;i<(UINT)stStartNo.nTotal;i++)
		{
			epcData.Format(_T("%04d%04X%s%08d"),nO,nB,strEpc,nN);
			nB=nB+stStartNo.nCount;
			nN=nN+stStartNo.nCount;
			if((10000-nB)==0)
			{
				nB=0;
				nO++;
			}

			epcData.MakeUpper();

			int nS=m_ListInData.GetItemCount(); 

			tmp.Format(_T("%d"),nS+1);

			int nRow=m_ListInData.InsertItem(nS,tmp); 

			m_ListInData.SetItemText(nRow, j, epcData);
		}*/
	}

	m_Total=m_Sum;
	m_Falsh=0;
	m_Mod=m_Sum;
	m_True=0;
	m_False=0;

	UpdateData(FALSE);
}

void CWriteISO6C::OnBnClickedButtonFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

 	CFileDialog dlg(TRUE,NULL,NULL,OFN_EXPLORER ,_T("TXT files(*.TXT)|*.txt")); 
    if(dlg.DoModal()==IDOK)
	{
		stFileName=dlg.GetPathName();

		CFileFind tempFind; 
        BOOL IsFinded = tempFind.FindFile(stFileName);

		if(!IsFinded)
		{
			//AfxMessageBox(_T("�����ļ�ѡ�����!"));
			AfxMessageBox(theApp.g_LoadString("IDWQF_D0083"));
			return;
		}

		stStartNo.nOne    =GetPrivateProfileInt(_T("Data"),_T("One"),-1,stFileName);
		stStartNo.nBegin  =GetPrivateProfileInt(_T("Data"),_T("Begin"),-1,stFileName);
		stStartNo.nCount  =GetPrivateProfileInt(_T("Data"),_T("Count"),-1,stFileName);
		stStartNo.nNumber =GetPrivateProfileInt(_T("Data"),_T("Number"),-1,stFileName);
		stStartNo.nTotal  =GetPrivateProfileInt(_T("Data"),_T("Total"),-1,stFileName);

		if((stStartNo.nCount<=0)||(stStartNo.nOne<0)||(stStartNo.nBegin<0)||(stStartNo.nNumber<0)||(stStartNo.nTotal<=0))
		{
			//AfxMessageBox(_T("�����ļ�ѡ�����!"));
			AfxMessageBox(theApp.g_LoadString("IDWQF_D0084"));
			return;
		}

		CString tmp;
		m_BeginData=stStartNo.nBegin;
		m_Count=stStartNo.nCount;
		m_Sum=stStartNo.nTotal;
		tmp.Format(_T("%04d%04x%s%08d"),stStartNo.nOne,stStartNo.nBegin,strEpc,stStartNo.nNumber);
		tmp.MakeUpper(); 
		m_DisStr=tmp;
		m_Word=6;

		nStatus=0;

		GetDlgItem(IDC_BUTTON_DATA)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_BEFOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BEFOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BEGIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_COUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SUM)->EnableWindow(FALSE);

		UpdateData(FALSE);

	}

}

void CWriteISO6C::OnCbnSelendokComboWord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_DATA)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_BEFOR)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_BEFOR)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_BEGIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_END)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_END)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_COUNT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SUM)->EnableWindow(TRUE);

	nStatus=1;

	UpdateData(TRUE);
}

//////////////////////////////////////////////////////////////////////////
//��;:		��ģ�����Ϣ��̬��Ա����,�ص�����
//������:	CWriteISO6C
//����:		
//�������:	hWnd--handle of CWnd that called SetTimer
//			nMsg--WM_TIMER
//			nIDEvent--timer identification
//			dwTime--system time 
//�������:	��
//����ֵ:	��
//��ע:TIME_IDENTIFIER_WRITE6C, INTERVALTIME____WRITE6C
//////////////////////////////////////////////////////////////////////////
void WINAPI CWriteISO6C::CallBack_MyTimeWrite6C(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime)
{
	//Debug_Printf("r:%s\r\n","hello");
	if ( INTERVALTIME____WRITE6C == nIDEvent )
	{
		//::PostMessage(gConnectReaderHwnd, WM_CONNECTDATACUSTOM, 0, 0);
	}
}

//WM_MSG
DWORD WINAPI ThreadEPC(LPVOID lpParameter)
{
	int t;
	CWriteISO6C *epcDlg = (CWriteISO6C *)lpParameter;

	apiReturn res	=	_no_scanner;
	int i,j,k,nCounter=0,ID_len=0,ID_len_temp=0;
	CString str,str_temp;
	BYTE temp[512];
	BYTE IDBuffer[30*256];

	BYTE mask[512],IDTemp[512];
	int mem,ptr,len,EPC_Word; 
	BYTE AccessPassword[32]={0};

	char p[3];

	BYTE lock	=	0;
	VH_WriteAppLogFile(__FILE__, __LINE__, "ThreadEPC\r\n");

	while(epcDlg->nStop)
	{
		int iCounter=epcDlg->m_ListInData.GetItemCount();
		if(iCounter==0)
		{
			SendMessage(epcDlg->m_hWnd,WM_MSG,0,0);//�б�������ɻ����ӶϿ�
			epcDlg->nStop=0;
			break;
		}

		if(!ifConnectReader)
		{
			SendMessage(epcDlg->m_hWnd,WM_MSG,0,1);//��д�������ѶϿ��Ͽ�������������
			epcDlg->nStop=0;
			break;
		}
		
		if(epcDlg->m_SetEPC) //���������ݼ���Ƿ����ϴ�д��������ͬ�������ظ�д��
		{
			//if(epcDlg->stInData.nLog),����д�ĳ�������ط�ΪʲôҪ�����???
			if(1)
			{
				len=0;	//���볤��LEN
				ptr=0;	//������ʼ��ַaddr
				mem=1;	//0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User
				ID_len=0;  
				j=0;
				memset(mask,0,512);
				
				while(epcDlg->nStop)
				{
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

							//ȥ����ͬID�ţ�Ȼ��д����modify by mqs 20121010
							if(memcmp(temp,IDTemp,ID_len*2)==0)
							{
								//�ظ�д���򱨾�
								//����ʱ��
								//::KillTimer(g6CWriteHwnd, TIME_IDENTIFIER_WRITE6C);
								//����ʱ��
								//::SetTimer(g6CWriteHwnd, TIME_IDENTIFIER_WRITE6C, INTERVALTIME____WRITE6C, epcDlg->CallBack_MyTimeWrite6C);
								SendMessage(epcDlg->m_hWnd,WM_MSG,3,0);

								//��ʼ����
								if ( 3 == ConnectMode )
								{
									BuzzerAlarm(m_hScanner, 1);
								}
								
								Sleep(1000);

								//ֹͣ����
								if ( 3 == ConnectMode )
								{
									BuzzerAlarm(m_hScanner, 0);
								}

							}
							else
							{
								SendMessage(epcDlg->m_hWnd,WM_MSG,101,0);//�ȴ�д��������뿨:
								break;
							}
						}
						else
						{
							SendMessage(epcDlg->m_hWnd,WM_MSG,3,1);//�ж��ſ����ڣ������һ�ſ�
							Sleep(1000);
						}
					}
					else
					{
						j++;
						t=res*1000+j;
						SendMessage(epcDlg->m_hWnd,WM_MSG,101,t);//�ȴ�д��������뿨:tָ����
						Sleep(500);
					}
				}
			}// end of if(epcDlg->stInData.nLog)
			
			//////////////////////////////////////////////////////////////////////////
			//�ⲿ���ж�׼��д��������Ƿ���ȷ
			//ȡ�б����ݣ����������
			str_temp=epcDlg->m_ListInData.GetItemText(0,1); 

			str=str_temp.SpanIncluding(_T("0123456789ABCDEFabcdef"));

			if(str.GetLength()!=str_temp.GetLength())
			{
				SendMessage(epcDlg->m_hWnd,WM_MSG,100,NULL);//��д�����ݴ���
				epcDlg->nStop=0;
				break;
			}
			//////////////////////////////////////////////////////////////////////////



			j=0;
			while(epcDlg->nStop) //д�����ݵ�ѭ��
			{
				memset(temp,0,512);
				memset(mask,0,512);
				memset(IDTemp,0,512);
				//����д�������
				//WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1,(char *)temp,str.GetLength()*2,NULL,NULL );
				len=str.GetLength();
				memcpy(temp, str, len);

				len=str.GetLength()/4;
				k=0;
				for(i=0;i<(len*2);i++)
				{
					memset(p,0,3);
					memcpy(p,&temp[k],2);
					k=k+2;
					mask[i]=(BYTE)strtol(&p[0],NULL,16);
				}
				memcpy(IDTemp,mask,len*2);//IDTempΪ׼��д������
				memset(AccessPassword,0,4);

				Sleep(30);
				switch(ConnectMode)
				{
				case 0:
	//				res = Net_EPC1G2_WriteEPC(m_hSocket,len,&mask[0],AccessPassword);		
					break;
				case 1:
					res = EPC1G2_WriteEPC(m_hScanner,len,&mask[0],AccessPassword,RS485Address);		
					break;
				case 3://usb
					res = EPC1G2_WriteEPC(m_hScanner,len,&mask[0],AccessPassword,0);		
					break;
				}

				if(res==_OK) //д���������ȡ���Ա���д�������Ƿ���ȷ
				{
					char chTemp[512]={0};
					Bcd2AscEx(chTemp, (char*)mask, len*2);
					
					VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_WriteEPC:OK(%s)\r\n", chTemp);

					len=0;	
					ptr=0;	
					mem=1;
					memset(mask,0,512);

					for (i = 0; i < 3; i++)
					{	
						Sleep(30);
						switch(ConnectMode)
						{
						case 0:
							break;
						case 1:
							res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,RS485Address);
							break;
						case 3://usb
							res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,0);
							break;
						}
						if ( _OK == res )
						{
							break;
						}
					}
					ID_len=(int)IDBuffer[0];  //IDBuffer[0]ΪWord����;1word=2Byte

					memcpy(temp,&IDBuffer[1],ID_len*2);//tempΪ���������ݣ�

					if(memcmp(temp,IDTemp,ID_len*2)==0)//����ǰ��IDTemp׼��д������ ���� �Ƚ�
					{
						//����������˵��д�ɹ���
						char chTemp[512]={0};
						Bcd2AscEx(chTemp, (char*)temp, ID_len*2);

						VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_ReadLabelIE:OK(%s)\r\n", chTemp);

						//////////////////////////////////////////////////////////////////////////
						if(epcDlg->m_SetUse)//д���û�������
						{
							//ȡ�б����ݣ����������
							str_temp=epcDlg->m_ListInData.GetItemText(0,2); 

							str=str_temp.SpanIncluding(_T("0123456789ABCDEFabcdef"));

							if(str.GetLength()!=str_temp.GetLength())
							{
								SendMessage(epcDlg->m_hWnd,WM_MSG,100,NULL);//��д�����ݴ���
								epcDlg->nStop=0;
								break;
							}

							memset(temp,0,512);	memset(mask,0,512);	

							//����д�������
							//WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1,(char *)temp,str.GetLength()*2,NULL,NULL );
							len=str.GetLength();
							memcpy(temp, str, len);

							len=str.GetLength()/4;
							k=0;
							for(i=0;i<(len*2);i++)
							{
								memset(p,0,3);
								memcpy(p,&temp[k],2);
								k=k+2;
								mask[i]=(BYTE)strtol(&p[0],NULL,16);
							}

							EPC_Word=ID_len;  mem=3; ptr=0; j=0;
							memset(AccessPassword,0,4);

							while(epcDlg->nStop)
							{
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
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,103,t);//�û�������д��ʧ�ܣ�����뿨:
									Sleep(1000);
								}
							}
						}

						if(epcDlg->m_SetPass)//д������������
						{
							//ȡ�б����ݣ����������
							str_temp=epcDlg->m_ListInData.GetItemText(0,3); 

							str=str_temp.SpanIncluding(_T("0123456789ABCDEFabcdef"));

							if(str.GetLength()!=str_temp.GetLength())
							{
								SendMessage(epcDlg->m_hWnd,WM_MSG,100,NULL);//��д�����ݴ���
								epcDlg->nStop=0;
								break;
							}

							memset(temp,0,512);	memset(mask,0,512);	

							//����д�������
							//WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1,(char *)temp,str.GetLength()*2,NULL,NULL );
							len=str.GetLength();
							memcpy(temp, str, len);

							len=str.GetLength()/4;
							k=0;
							for(i=0;i<(len*2);i++)
							{
								memset(p,0,3);
								memcpy(p,&temp[k],2);
								k=k+2;
								mask[i]=(BYTE)strtol(&p[0],NULL,16);
							}

							EPC_Word=ID_len;  mem=0; ptr=0; j=0;
							memset(AccessPassword,0,4);

							while(epcDlg->nStop)
							{
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
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,104,t);//����������д��ʧ�ܣ�����뿨:%d-%d
									Sleep(1000);
								}
							}
						}


						//////////////////////////////////////////////////////////////////////////
						//add by mqs 20130409 ����EPC��������:
						//1.ʹ������д����(������һ��Ҫ��ԭ�������һ�)
						//2.��Զ����д����������������ûɶ�����൱�ڹ���һ����ֻ���Ժ󻻱�ǩ��
						//iFlagProtectOpt	=	0;//0---������(����), 1---ʹ����������2---��Զ��ס(����), 3---EAS����(add by martrin20140514)
						int iSuccess = 0 ;//�ɹ�
						if ( epcDlg->iFlagProtectOpt == 1 || 2 == epcDlg->iFlagProtectOpt )
						{
							//1---ʹ��������
							len=4;	//��ȡ���ݵĳ���
							ptr=0;	//
							mem=0;	//0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User
							EPC_Word	=	ID_len;//ΪEPC�ĳ���1
							
							//////////////////////////////////////////////////////////////////////////
							//��һ���ȶ���ԭ������
							while(epcDlg->nStop)
							{
								
								memset(mask,0,512);
								Sleep(30);

								switch(ConnectMode)
								{
								case 0:		
									break;
								case 1:
								case 3://usb
									//EPC_Word ΪEPC�ĳ���
									//IDTemp �����EPC��
									//mem 0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User, ����Ϊ0
									//ptr ��ȡ���ݵ���ʼ��ַ, len ��ȡ���ݵĳ���
									//�����Ķ����������� mask, 
									//AccessPassword ԭ��������
									res=EPC1G2_ReadWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,RS485Address);
									break;
								}

								if(res==_OK)
								{
									//������ԭ����
									char chTemp[512]={0};
									Bcd2AscEx(chTemp, (char*)mask, len*2);
									
									VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_ReadWordBlock:ReadPassword(%s)\r\n", chTemp);
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,105,t);//��ԭ����ʧ�ܣ�����뿨������뿨:
									Sleep(300);
								}
							}
							if ( res != _OK )
							{
								iSuccess++;
							}
							//////////////////////////////////////////////////////////////////////////


							//////////////////////////////////////////////////////////////////////////
							//��2����д�����룬�ý����ϵ�����ֵepcDlg->AccessPassword
							while(epcDlg->nStop)
							{
								len=4;	//��ȡ���ݵĳ���
								ptr=0;	//������ʼ��ַaddr
								mem=0;	//0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User
								EPC_Word	=	ID_len;//ΪEPC�ĳ���
								
								memcpy(mask, epcDlg->AccessPassword, len);
								memcpy(mask+4, epcDlg->AccessPassword, len);

								Sleep(30);

								switch(ConnectMode)
								{
								case 0:		
									break;
								case 1:
								case 3://usb
									//EPC_Word ΪEPC�ĳ���
									//IDTemp �����EPC��
									//mem 0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User, ����Ϊ0
									//ptr ���������=0, len =4
									//�����Ǵ�������ֵ mask, 
									//AccessPassword ԭ��������
									res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,RS485Address);
									break;
								}

								if(res==_OK)
								{
									char chTemp[512]={0};
									Bcd2AscEx(chTemp, (char*)mask, len*2);

									VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_ReadWordBlock:New Password(%s)\r\n", chTemp);
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,106,t);//д������ʧ�ܣ�����뿨������뿨:
									Sleep(300);
								}
							}
							if ( res != _OK )
							{
								iSuccess++;
							}
							//////////////////////////////////////////////////////////////////////////


							//////////////////////////////////////////////////////////////////////////
							//��3����סEPC����ʹ������д����סEPC,ע�⴫���������
							while(epcDlg->nStop)
							{
								EPC_Word	=	ID_len;//ΪEPC�ĳ���
								ptr=0;	//������ʼ��ַaddr
								mem=2;	//0-- Kill Password 1--Access Password 2-- EPC�� 3-- TID��ǩID�� 4--�û���User

								//0--��д         1--���ÿ�д
								//2��������д     3--������д
								//4--�ɶ�д       5--���ÿɶ�д
								//6--�������д   7--�����ɶ�д
								//0��3ֻ����EPC��TID��User������������4��7ֻ����Kill Password��Access Password��
								if ( epcDlg->iFlagProtectOpt == 1 )////0---������(����), 1---ʹ����������2---��Զ��ס(����), 3---EAS����(add by martrin20140514)
								{
									lock	=	2;//2��������д
								}
								else if ( 2 == epcDlg->iFlagProtectOpt )
								{
									lock	=	3;//3-������д
								}
								
								

								memcpy(AccessPassword, mask, 8);
								
								Sleep(30);

								switch(ConnectMode)
								{
								case 0:		
									break;
								case 1:
								case 3://usb
									res=EPC1G2_SetLock(m_hScanner,EPC_Word,IDTemp,mem,lock,AccessPassword,RS485Address);
									break;
								}

								if(res==_OK)
								{
									VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_SetLock:EPC Lock(%d)\r\n", lock);
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,107,t);//��EPC����д��ʧ�ܣ�����뿨:
									Sleep(300);
								}
							}
							if ( res != _OK )
							{
								iSuccess++;
							}
							//////////////////////////////////////////////////////////////////////////



							//////////////////////////////////////////////////////////////////////////
							//��4��Ҫ�������뱣����ʹ������ɶ�д������
							while(epcDlg->nStop)
							{
								EPC_Word	=	ID_len;//ΪEPC�ĳ���
								ptr=0;	//������ʼ��ַaddr
								mem=1;	//0-- Kill Password 1--Access Password 2-- EPC�� 3-- TID��ǩID�� 4--�û���User

								//0--��д         1--���ÿ�д
								//2��������д     3--������д
								//4--�ɶ�д       5--���ÿɶ�д
								//6--�������д   7--�����ɶ�д
								//0��3ֻ����EPC��TID��User������������4��7ֻ����Kill Password��Access Password��
								if ( epcDlg->iFlagProtectOpt == 1 )////0---������(����), 1---ʹ����������2---��Զ��ס(����), 3---EAS����(add by martrin20140514)
								{
									lock	=	6;//6���������д
								}
								else if ( 2 == epcDlg->iFlagProtectOpt )
								{
									lock	=	7;//7--�����ɶ�д
								}


								Sleep(30);

								switch(ConnectMode)
								{
								case 0:		
									break;
								case 1:
								case 3://usb
									//EPC_Word ΪEPC�ĳ���
									//IDTemp �����EPC��
									//mem 0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User, ����Ϊ0
									//ptr ��ȡ���ݵ���ʼ��ַ, len ��ȡ���ݵĳ���
									//�����Ķ����������� mask, 
									//AccessPassword ԭ��������
									res=EPC1G2_SetLock(m_hScanner,EPC_Word,IDTemp,mem,lock,AccessPassword,RS485Address);
									break;
								}

								if(res==_OK)
								{
									VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_SetLock:PasswordLock(%d)\r\n", lock);
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,108,t);//������ʧ�ܣ�����뿨:
									Sleep(300);
								}
							}
							if ( res != _OK )
							{
								iSuccess++;
							}
							//////////////////////////////////////////////////////////////////////////
							//��ֹΪֹ������סEPC��Ҫ��⿪����֪�����롣
							//////////////////////////////////////////////////////////////////////////


						}//end of if ( epcDlg->iFlagProtectOpt == 1 )


						//////////////////////////////////////////////////////////////////////////
						//add by mqs 20140514 ����EAS����:
						//1.ʹ������д����(������һ��Ҫ��ԭ�������һ�)
						//2.��Զ����д����������������ûɶ�����൱�ڹ���һ����ֻ���Ժ󻻱�ǩ��
						//iFlagProtectOpt	=	0;//0---������(����), 1---ʹ����������2---��Զ��ס(����), 3---EAS����(add by martrin20140514)
						//int iSuccess = 0 ;//�ɹ�
						if ( epcDlg->iFlagProtectOpt == 3 )
						{
							//////////////////////////////////////////////////////////////////////////
							//����EAS������˵��һ�������������
							//��1����д�����룬�ý����ϵ�����ֵepcDlg->AccessPassword
							while(epcDlg->nStop)
							{
								len=4;	//��ȡ���ݵĳ���
								ptr=0;	//������ʼ��ַaddr
								mem=0;	//0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User
								EPC_Word	=	ID_len;//ΪEPC�ĳ���
								
								memcpy(mask, epcDlg->AccessPassword, len);
								memcpy(mask+4, epcDlg->AccessPassword, len);
								
								Sleep(30);
								
								switch(ConnectMode)
								{
								case 0:		
									break;
								case 1:
								case 3://usb
									//EPC_Word ΪEPC�ĳ���
									//IDTemp �����EPC��
									//mem 0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User, ����Ϊ0
									//ptr ���������=0, len =4
									//�����Ǵ�������ֵ mask, 
									//AccessPassword ԭ��������
									res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,RS485Address);
									break;
								}
								
								if(res==_OK)
								{
									char chTemp[512]={0};
									Bcd2AscEx(chTemp, (char*)mask, len*2*2);
									
									VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_WriteWordBlock:New Password(%s)\r\n", chTemp);
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,109,t);//д������ʧ�ܣ�����뿨������뿨:
									Sleep(300);
								}
							}
							if ( res != _OK )
							{
								iSuccess++;
							}
							//////////////////////////////////////////////////////////////////////////



							//////////////////////////////////////////////////////////////////////////
							//��2������EAS����λ
							while(epcDlg->nStop)
							{
								len=4;	//��ȡ���ݵĳ���
								ptr=0;	//������ʼ��ַaddr
								mem=0;	//0--������,1-- EPC��,2-- TID��ǩID��,3--�û���User
								EPC_Word	=	ID_len;//ΪEPC�ĳ���
								
								memcpy(mask, epcDlg->AccessPassword, len);
								memcpy(mask+4, epcDlg->AccessPassword, len);
								
								Sleep(30);
								
								switch(ConnectMode)
								{
								case 0:		
									break;
								case 1:
								case 3://usb
									//EPC_Word ΪEPC�ĳ���
									//IDTemp �����EPC��
									//EASstate	1���ֽ�	0-������ 1-����,����ָ1
									//AccessPassword ԭ�������� 
									//res=EPC1G2_ChangeEas(m_hScanner,EPC_Word,IDTemp, 1, AccessPassword, RS485Address);
									res=EPC1G2_ChangeEas(m_hScanner,EPC_Word,IDTemp, 1, mask, RS485Address);
									break;
								}
								
								if(res==_OK)
								{
									
									VH_WriteAppLogFile(__FILE__, __LINE__, "EPC1G2_ChangeEas is 1!\r\n");
									break;
								}
								else
								{
									j++;
									t=res*1000+j;
									SendMessage(epcDlg->m_hWnd,WM_MSG,110,t);//дEAS����λ������뿨������뿨:
									Sleep(300);
								}
							}
							if ( res != _OK )
							{
								iSuccess++;
							}
							//////////////////////////////////////////////////////////////////////////


						}
						//////////////////////////////////////////////////////////////////////////


						//��������д�ɹ���
						SendMessage(epcDlg->m_hWnd,WM_MSG,1,iSuccess);//��¼��ǰ��д������

						//��ʼ����
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

						break;
					}
					else
					{
						SendMessage(epcDlg->m_hWnd,WM_MSG,1,1);//�˿�δд��ɹ��������·���
						Sleep(1000);
					}
				}
				else
				{
					j++;
					t=res*1000+j;
					SendMessage(epcDlg->m_hWnd,WM_MSG,101,t);//�ȴ�д��������뿨:%d-%d
					Sleep(100);
				}
			}

	     }//end of if(epcDlg->m_SetEPC)

		 //д����ʱ��
		 for(i=0;i<(int)epcDlg->m_Time;i++)
		 {
			 Sleep(1000);
			 SendMessage(epcDlg->m_hWnd,WM_MSG,2,i);//�ȴ�д��������뿨,iָ����ʱ��
		 }

	}

	return 0;
}


//WM_MSG
DWORD WINAPI ThreadWrite(LPVOID lpParameter)
{
	CWriteISO6C *epcDlg = (CWriteISO6C *)lpParameter;

	int t;
	apiReturn res;
	int i,j,k,nCounter=0,ID_len=0,ID_len_temp=0;
	CString str,str_temp;
	BYTE temp[512];
	BYTE IDBuffer[30*256];
	BYTE mask[512],IDTemp[512];
	int mem,ptr,len,EPC_Word;
	BYTE AccessPassword[4];

	int nRow;
	char p[3];

	while(epcDlg->nStop)
	{
		int iCounter=epcDlg->m_ListInData.GetItemCount();
		if(iCounter==0)
		{
			SendMessage(epcDlg->m_hWnd,WM_MSG,0,0);//�б�������ɻ����ӶϿ�
			epcDlg->nStop=0;
			break;
		}

		if(!ifConnectReader)
		{
			SendMessage(epcDlg->m_hWnd,WM_MSG,0,1);//��д�������ѶϿ��Ͽ�������������
			epcDlg->nStop=0;
			break;
		}

		len=0;	ptr=0;	mem=1;	ID_len=0;  j=0;   nRow=0;
		memset(mask,0,512);
		memset(IDTemp,0,512);
		
		Sleep(30);
		switch(ConnectMode)
		{
		case 0:		
			break;
		case 1:
		case 3://usb
			res=EPC1G2_ReadLabelID(m_hScanner,mem,ptr,len,mask,IDBuffer,&nCounter,RS485Address);	
			break;
		}

		if(res==_OK)
		{
			str.Empty(); 
			ID_len=(int)IDBuffer[0];  //IDBuffer[0]ΪWord����;1word=2Byte
			memcpy(IDTemp,&IDBuffer[1],ID_len*2);
			for(i=0;i<ID_len*2;i++)
			{
				str_temp.Format(_T("%02X"),IDTemp[i]); 
				str=str+str_temp.Left(2);
			}
			str_temp=epcDlg->m_ListInData.GetItemText(0,1);

			if((str==str_temp)||(str_temp.GetLength()<=0))
			{
				if(epcDlg->m_SetUse)
				{
					//ȡ�б����ݣ����������
					str_temp=epcDlg->m_ListInData.GetItemText(0,2); 

					str=str_temp.SpanIncluding(_T("0123456789ABCDEFabcdef"));

					if(str.GetLength()!=str_temp.GetLength())
					{
						SendMessage(epcDlg->m_hWnd,WM_MSG,100,NULL);//��д�����ݴ���
						epcDlg->nStop=0;
						break;
					}

					memset(temp,0,512);	memset(mask,0,512);	

					//����д�������
					//WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1,(char *)temp,str.GetLength()*2,NULL,NULL );
					len=str.GetLength();
					memcpy(temp, str, len);

					len=str.GetLength()/4;
					k=0;
					for(i=0;i<(len*2);i++)
					{
						memset(p,0,3);
						memcpy(p,&temp[k],2);
						k=k+2;
						mask[i]=(BYTE)strtol(&p[0],NULL,16);
					}

					EPC_Word=ID_len;  mem=3; ptr=0; j=0;
					memset(AccessPassword,0,4);

					while(epcDlg->nStop)
					{
						Sleep(30);
						switch(ConnectMode)
						{
						case 0:		
							break;
						case 1:
						case 3://usb
							res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,RS485Address);
							break;
						}

						if(res==_OK)
						{
							break;
						}
						else
						{
							j++;
							t=res*1000+j;
							SendMessage(epcDlg->m_hWnd,WM_MSG,103,t);//�û�������д��ʧ�ܣ�����뿨:%d-%d
							Sleep(1000);
						}
					}
				}

				if(epcDlg->m_SetPass)
				{
					//ȡ�б����ݣ����������
					str_temp=epcDlg->m_ListInData.GetItemText(0,3); 

					str=str_temp.SpanIncluding(_T("0123456789ABCDEFabcdef"));

					if(str.GetLength()!=str_temp.GetLength())
					{
						SendMessage(epcDlg->m_hWnd,WM_MSG,100,NULL);//��д������ݴ���
						epcDlg->nStop=0;
						break;
					}

					memset(temp,0,512);	memset(mask,0,512);	

					//����д�������
					//WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1,(char *)temp,str.GetLength()*2,NULL,NULL );
					len=str.GetLength();
					memcpy(temp, str, len);

					len=str.GetLength()/4;
					k=0;
					for(i=0;i<(len*2);i++)
					{
						memset(p,0,3);
						memcpy(p,&temp[k],2);
						k=k+2;
						mask[i]=(BYTE)strtol(&p[0],NULL,16);
					}

					EPC_Word=ID_len;  mem=0; ptr=0; j=0;
					memset(AccessPassword,0,4);

					while(epcDlg->nStop)
					{
						Sleep(30);
						switch(ConnectMode)
						{
						case 0:		
							break;
						case 1:
						case 3://usb
							res=EPC1G2_WriteWordBlock(m_hScanner,EPC_Word,IDTemp,mem,ptr,len,mask,AccessPassword,RS485Address);
							break;
						}

						if(res==_OK)
						{
							break;
						}
						else
						{
							j++;
							t=res*1000+j;
							SendMessage(epcDlg->m_hWnd,WM_MSG,104,t);//����������д��ʧ�ܣ�����뿨:%d-%d,tָʱ��
							Sleep(1000);
						}
					}
				}

				SendMessage(epcDlg->m_hWnd,WM_MSG,1,0);//д��ɹ������ͳɹ���Ϣ
			}
			else
			{
				SendMessage(epcDlg->m_hWnd,WM_MSG,102,0);//�������������ȷ�Ŀ�
				Sleep(1000);
			}

		}
		else
		{
			j++;
			t=res*1000+j;
			SendMessage(epcDlg->m_hWnd,WM_MSG,101,t);//�ȴ�д��������뿨:%d-%d
			Sleep(100);
		}

		//д����ʱ��
		 for(i=0;i<(int)epcDlg->m_Time;i++)
		 {
			 Sleep(1000);
			 SendMessage(epcDlg->m_hWnd,WM_MSG,2,i);//�ȴ�д��������뿨:%d,iΪʱ��
		 }
	}

	return 0;
}


void CWriteISO6C::OnBnClickedButtonWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	UpdateData(TRUE);


	//////////////////////////////////////////////////////////////////////////
	iFlagProtectOpt	=	0;//0---������(����), 1---ʹ����������2---��Զ��ס(����), 3---EAS����(add by martrin20140514)
	if ( ((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->GetCheck() || ((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_EAS_ALARM))->GetCheck() )
	{
		char chTemp[33]={0};
		int i = 0;
		int str_len	=	0;
		CString m_RWAccessPassword;

		GetDlgItem(IDC_EDIT_USERPASS)->GetWindowText(m_RWAccessPassword);
		iFlagProtectOpt	=	1;//1---ʹ��������
		//��������
		str=m_RWAccessPassword.SpanIncluding(_T("0123456789ABCDEFabcdef"));
		if(lstrlen(str)!=lstrlen(m_RWAccessPassword))
		{
			MessageBox(_T("Please input HEX!"), _T("Warning"),MB_ICONWARNING);
			GetDlgItem(IDC_EDIT_USERPASS)->SetFocus();
			((CEdit *) GetDlgItem(IDC_EDIT_USERPASS))->SetSel(0,-1);
			return;
		}
		str=m_RWAccessPassword;
		str_len=lstrlen(str);
		if (str_len!=8)
		{
			//MessageBox(_T("Please input enough Length of AccessPassword!"), _T("Warning"),MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_D0085"), theApp.g_LoadString("IDWQF_D0086"), MB_ICONWARNING);
			return;
		}

		//WideCharToMultiByte( CP_ACP, 0, str.GetBuffer(), -1,(char*)chTemp,str.GetLength()*2,NULL,NULL );
		memcpy(chTemp, str, 8);

		Asc2Bcd((char*)AccessPassword, chTemp, 8);

		//str	=	_T("��ȷ��Ҫʹ������д������EPC��");
		str	=	theApp.g_LoadString("IDWQF_D0087");

	}

	if ( ((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable))->GetCheck() )
	{
		iFlagProtectOpt	=	2;//2---��Զ��ס(����)

		//str	=	_T("��ȷ��Ҫ��Զ����д������EPC��");
		str	=	theApp.g_LoadString("IDWQF_D0088");
	}

	if ( ((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_EAS_ALARM))->GetCheck() )
	{
		iFlagProtectOpt	=	3;//3---EAS����(add by martrin20140514)
		
		//str	=	_T("��ȷ��ҪEAS������");
		str	=	theApp.g_LoadString("IDWQF_D0122");
	}

	int k = 0;
	if ( 0 == iFlagProtectOpt )
	{
	}
	else
	{
		//k	=	MessageBox(str, _T("����"),MB_YESNO|MB_ICONWARNING);
		k	=	MessageBox(str, theApp.g_LoadString("IDWQF_D0089"),MB_YESNO|MB_ICONWARNING);
		if ( k != 6 )
		{
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////


	int iCount=m_ListInData.GetItemCount();
	if(iCount==0)
	{
		//MessageBox(_T("��д�������б���û������"),_T("��ʾ"),0);
		MessageBox(theApp.g_LoadString("IDWQF_D0090"), theApp.g_LoadString("IDWQF_D0091"), 0);
		return;
	}

	if(!ifConnectReader)
	{
		//MessageBox(_T("��д��δ����"),_T("��ʾ"),0);
		MessageBox(theApp.g_LoadString("IDWQF_D0092"), theApp.g_LoadString("IDWQF_D0093"), 0);
		return;
	}

// 	if(nWRStatus!=1)
// 	{
// 		//MessageBox(_T("��д������ʹ����"),_T("��ʾ"),0);
//		//MessageBox(theApp.g_LoadString("IDWQF_D0094"), theApp.g_LoadString("IDWQF_D0095"), 0);
// 		return;
// 	}
// 	else
// 	{
// 		nWRStatus=2;
// 	}

	nStop=1;

	nWord=m_Word;

	CString tmp;
	tmp  =m_ListInData.GetItemText(0,1);

	m_MsgIn.SetWindowText(tmp);  

	GetDlgItem(IDC_CHECK_EPC)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_USE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_PASS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MOVE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_DELALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DATA)->EnableWindow(FALSE);

	if(m_SetEPC)
	{
		//ʹ��EPCдҪ�䲻����
		((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERPASS)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable))->EnableWindow(FALSE);

		CreateThread(NULL,0,ThreadEPC,this,0,NULL);	
	}
	else
	{
		CreateThread(NULL,0,ThreadWrite,this,0,NULL);
	}
}

void CWriteISO6C::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	nStop=0;
	//nWRStatus=1;

	GetDlgItem(IDC_CHECK_EPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_USE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_PASS)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_TIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MOVE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_DELALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DATA)->EnableWindow(TRUE);

	//ʹ��EPCдҪ�䲻����
	((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_USERPASS)->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable))->EnableWindow(TRUE);
}



void CWriteISO6C::OnBnClickedButtonMove()
{
	//ȡд���б��ֵ�����ӵ�����б�

	int nTotal=m_ListInData.GetItemCount();
	if(nTotal<=0)
	{
		return;
	}

	CString sNo  =m_ListInData.GetItemText(0,0);
	CString sEPC =m_ListInData.GetItemText(0,1);
	CString sUse =m_ListInData.GetItemText(0,2);
	CString sPass=m_ListInData.GetItemText(0,3);

	int nRow=m_ListOutData.InsertItem(0,sNo);
	m_ListOutData.SetItemText(nRow, 1, sEPC);
	m_ListOutData.SetItemText(nRow, 2, sUse);
	m_ListOutData.SetItemText(nRow, 3, sPass);
	//m_ListOutData.SetItemText(nRow, 4, _T("ʧ��"));
	m_ListOutData.SetItemText(nRow, 4, theApp.g_LoadString("IDWQF_D0096"));

	m_ListInData.DeleteItem(0);

	//�������������ļ�
	CString tmp;
	stStartNo.nBegin++;
	if((10000-stStartNo.nBegin)==0)  //nBegin=10000ʱNo+1,nBegin=0
	{
		stStartNo.nOne++;
		stStartNo.nBegin=0; 
	}
	stStartNo.nNumber++;
	stStartNo.nTotal--; 
	if(stStartNo.nTotal<=0)
	{
		DeleteFile(stFileName); 
	}
	else
	{
		tmp.Format(_T("%d"),stStartNo.nOne);
		WritePrivateProfileString(_T("Data"),_T("One"),tmp,stFileName);
		tmp.Format(_T("%d"),stStartNo.nBegin);
		WritePrivateProfileString(_T("Data"),_T("Begin"),tmp,stFileName);
		tmp.Format(_T("%d"),stStartNo.nCount);
		WritePrivateProfileString(_T("Data"),_T("Count"),tmp,stFileName);
		tmp.Format(_T("%d"),stStartNo.nNumber);
		WritePrivateProfileString(_T("Data"),_T("Number"),tmp,stFileName);
		tmp.Format(_T("%d"),stStartNo.nTotal);
		WritePrivateProfileString(_T("Data"),_T("Total"),tmp,stFileName);
	}

	//����������ʾ
	m_Falsh++;
	m_Mod--;
	m_False++;


	UpdateData(FALSE);
	
}

void CWriteISO6C::OnCbnKillfocusComboWord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	switch(m_Word)
	{
	case 1:
		m_DisStr=_T("0000"); 
		break;
	case 2:
		m_DisStr=_T("0000-0000");
		break;
	case 3:
		m_DisStr=_T("0000-0000-0000");
		break;
	case 4:
		m_DisStr=_T("0000-0000-0000-0000");
		break;
	case 5:
		m_DisStr=_T("0000-0000-0000-0000-0000");
		break;
	case 6:
		m_DisStr=_T("0000-0000-0000-0000-0000-0000");
		break;
	case 7:
		m_DisStr=_T("0000-0000-0000-0000-0000-0000-0000");
		break;
	case 8:
		m_DisStr=_T("0000-0000-0000-0000-0000-0000-0000-0000");
		break;
	default:
		m_DisStr="";
		break;
	}

	UpdateData(FALSE);
}

LRESULT CWriteISO6C::WriteMsg(WPARAM wParam, LPARAM lParam)
{
	CString tmp;

	switch(wParam)
	{
	case 0:  //�б�������ɻ����ӶϿ�
		nStop=0;
		//nWRStatus=1;
		GetDlgItem(IDC_CHECK_EPC)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_USE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_PASS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MOVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DATA)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DELALL)->EnableWindow(TRUE);
		if(lParam)
		{
			//MessageBox(_T("��д�������ѶϿ��Ͽ�������������"),_T("����"),MB_ICONWARNING);
			MessageBox(theApp.g_LoadString("IDWQF_D0097"), theApp.g_LoadString("IDWQF_D0098"), MB_ICONWARNING);
		}
		break;
	case 1:  //����д�����
		if(lParam==0)
		{
			//��¼��ǰ��д������
			stInData.nLog=1;
			stInData.stNo  =m_ListInData.GetItemText(0,0);
			stInData.stEPC =m_ListInData.GetItemText(0,1);
			stInData.stUse =m_ListInData.GetItemText(0,2);
			stInData.stPass=m_ListInData.GetItemText(0,3);

			//��������б�
			int nRow=m_ListOutData.InsertItem(0,stInData.stNo);
			m_ListOutData.SetItemText(nRow, 1, stInData.stEPC);
			m_ListOutData.SetItemText(nRow, 2, stInData.stUse);
			m_ListOutData.SetItemText(nRow, 3, stInData.stPass);
			//m_ListOutData.SetItemText(nRow, 4, _T("�ɹ�"));
			m_ListOutData.SetItemText(nRow, 4, theApp.g_LoadString("IDWQF_D0099"));

			m_ListInData.DeleteItem(0); 

			//�������������ļ�
			stStartNo.nBegin++;
			if((10000-stStartNo.nBegin)==0)
			{
				stStartNo.nOne++;
				stStartNo.nBegin=0;
			}
			stStartNo.nNumber++;
			stStartNo.nTotal--; 
			if(stStartNo.nTotal<=0)
			{
				DeleteFile(stFileName); 
			}
			else
			{
				tmp.Format(_T("%d"),stStartNo.nOne);
				WritePrivateProfileString(_T("Data"),_T("One"),tmp,stFileName);
				tmp.Format(_T("%d"),stStartNo.nBegin);
				WritePrivateProfileString(_T("Data"),_T("Begin"),tmp,stFileName);
				tmp.Format(_T("%d"),stStartNo.nCount);
				WritePrivateProfileString(_T("Data"),_T("Count"),tmp,stFileName);
				tmp.Format(_T("%d"),stStartNo.nNumber);
				WritePrivateProfileString(_T("Data"),_T("Number"),tmp,stFileName);
				tmp.Format(_T("%d"),stStartNo.nTotal);
				WritePrivateProfileString(_T("Data"),_T("Total"),tmp,stFileName);
			}
            //������ʾ��Ϣ
			tmp = m_ListInData.GetItemText(0,1);
			m_MsgIn.SetWindowText(tmp); 
			m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_OK));
			//m_MsgDis.SetWindowText(_T("д���ɹ������ƿ��˿�"));
			m_MsgDis.SetWindowText(theApp.g_LoadString("IDWQF_D0100"));
			m_MsgOut.SetWindowText(stInData.stEPC);  

			m_Falsh++;
			m_Mod--;
			m_True++;
			UpdateData(FALSE);
		}
		else 
		{
			m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
			//m_MsgDis.SetWindowText(_T("�˿�δд��ɹ��������·���"));
			m_MsgDis.SetWindowText(theApp.g_LoadString("IDWQF_D0101"));
		}

		break;
	case 2:
		//tmp.Format(_T("�ȴ�д��������뿨:%d"),lParam); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0102"),lParam); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_WAIT));
		m_MsgDis.SetWindowText(tmp);
		break;
	case 3:
		if(lParam==0)
		{
			m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		    //m_MsgDis.SetWindowText(_T("�ظ�д�����������һ�ſ�"));
			m_MsgDis.SetWindowText(theApp.g_LoadString("IDWQF_D0103"));
		}
		else
		{
			m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		    //m_MsgDis.SetWindowText(_T("�ж��ſ����ڣ������һ�ſ�"));
			m_MsgDis.SetWindowText(theApp.g_LoadString("IDWQF_D0104"));
		}
		break;
	case 100://��д�����ݴ���
		nStop=0;
		//nWRStatus=1;
		GetDlgItem(IDC_CHECK_EPC)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_USE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_PASS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WRITE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MOVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DELALL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_DATA)->EnableWindow(TRUE);
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		//m_MsgDis.SetWindowText(_T("���󣬴�д������ݴ���"));
		m_MsgDis.SetWindowText(theApp.g_LoadString("IDWQF_D0105"));
		//MessageBox(_T("��д������ݴ���"),_T("����"),MB_ICONWARNING);
		MessageBox(theApp.g_LoadString("IDWQF_D0106"), theApp.g_LoadString("IDWQF_D0107"), MB_ICONWARNING);
		break;
	case 101:
		//tmp.Format(_T("�ȴ�д����д��ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0108"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_WAIT));
		m_MsgDis.SetWindowText(tmp);
		break;
	case 102:
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		//m_MsgDis.SetWindowText(_T("�������������ȷ�Ŀ�"));
		m_MsgDis.SetWindowText(theApp.g_LoadString("IDWQF_D0109"));
		break;
	case 103:
		//tmp.Format(_T("�û�������д��ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0110"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;
	case 104:
		//tmp.Format(_T("����������д��ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0111"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;

	case 105:
		//tmp.Format(_T("��ԭ����ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0112"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;

	case 106:
		//tmp.Format(_T("д������ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0113"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;
	
	case 107:
		//tmp.Format(_T("��EPCʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0114"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;

	case 108:
		//tmp.Format(_T("������ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0115"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;

	case 109:
		//tmp.Format(_T("д������ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0113"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;
		
	case 110:
		//tmp.Format(_T("����EAS����ʧ�ܣ�����뿨:%d-%d"),lParam/1000,lParam%1000); 
		tmp.Format(theApp.g_LoadString("IDWQF_D0123"),lParam/1000,lParam%1000); 
		m_MsgImg.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ERR));
		m_MsgDis.SetWindowText(tmp);
		break;

	}

	return 0;
}

void CWriteISO6C::OnBnClickedButtonDelall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListInData.DeleteAllItems(); 
}

void CWriteISO6C::OnBnClickedButtonDelout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListOutData.DeleteAllItems(); 
}

void CWriteISO6C::OnBnClickedRadioEpc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ѡ��EPC
	m_WriteMode=0;

	int i = 0;
	CString strTemp;

	((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->ResetContent();
	for (i = 0; i < 9; i++)
	{
		strTemp.Format(_T("%d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->AddString(strTemp);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->SetCurSel(0);

}

void CWriteISO6C::OnBnClickedRadioUser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ѡ���û���
	m_WriteMode=1;

	int i = 0;
	CString strTemp;
	
	((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->ResetContent();
	for (i = 0; i < 9; i++)
	{
		strTemp.Format(_T("%d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->AddString(strTemp);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->SetCurSel(0);

}

void CWriteISO6C::OnBnClickedRadioPass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ѡ��������
	m_WriteMode=2;

	int i = 0;
	CString strTemp;

	((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->ResetContent();
	for (i = 0; i < 5; i++)
	{
		strTemp.Format(_T("%d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->AddString(strTemp);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_WORD))->SetCurSel(4);

}

void CWriteISO6C::OnBnClickedButtonIndata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString filename;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_EXPLORER ,_T("TXT files(*.csv)|*.*")); 
    if(dlg.DoModal()==IDOK)
	{
		filename=dlg.GetPathName();

		CFileFind tempFind; 
        BOOL IsFinded = tempFind.FindFile(filename);

		if(!IsFinded)
		{
			//AfxMessageBox(_T("�����ļ�ѡ�����!"));
			AfxMessageBox(theApp.g_LoadString("IDWQF_D0116"));
			return;
		}
	}
	else
	{
		return;
	}

	m_ListInData.DeleteAllItems(); 

	UpdateData(TRUE);

	CString strtmp,tmp,epcData;
	CStdioFile f;
	f.Open(filename,CFile::typeText);

	int nRow=0,nCol=0,nTotal=0;
    int nLen=0,strLen;
	while(f.ReadString(strtmp))
	{
		if(strtmp.GetLength()<=0)
		{
			continue;
		}
		nTotal=m_ListInData.GetItemCount(); 
		tmp.Format(_T("%d"),nTotal+1);
		nRow=m_ListInData.InsertItem(nTotal,tmp); 

		if(m_SetEPC)
		{
			nCol=1;
			strLen=strtmp.GetLength();
			if(strLen<=0)
			{
				continue;
			}
			nLen=strtmp.Find(',',0);
			if(nLen<=0)
			{
				epcData=strtmp;
				strtmp.Empty(); 
			}
			else
			{
				epcData=strtmp.Left(nLen);
				tmp=strtmp.Right(strLen-nLen-1);
				strtmp=tmp;
			}
			m_ListInData.SetItemText(nRow, nCol, epcData);
		}

		if(m_SetUse)
		{
			nCol=2;
			strLen=strtmp.GetLength();
			if(strLen<=0)
			{
				continue;
			}
			nLen=strtmp.Find(',',0);
			if(nLen<=0)
			{
				epcData=strtmp;
				strtmp.Empty(); 
			}
			else
			{
				epcData=strtmp.Left(nLen);
				tmp=strtmp.Right(strLen-nLen-1);
				strtmp=tmp;
			}
			m_ListInData.SetItemText(nRow, nCol, epcData);
		}

		if(m_SetPass)
		{
			nCol=3;
			strLen=strtmp.GetLength();
			if(strLen<=0)
			{
				continue;
			}
			nLen=strtmp.Find(',',0);
			if(nLen<=0)
			{
				epcData=strtmp;
				strtmp.Empty(); 
			}
			else
			{
				epcData=strtmp.Left(nLen);
				tmp=strtmp.Right(strLen-nLen-1);
				strtmp=tmp;
			}
			m_ListInData.SetItemText(nRow, nCol, epcData);
		}
	}
	f.Close(); 

	m_Total=m_ListInData.GetItemCount();
	m_Falsh=0;
	m_Mod=m_ListInData.GetItemCount();
	m_True=0;
	m_False=0;
	
	UpdateData(FALSE);
}

void CWriteISO6C::OnBnClickedCheckEpc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_SetEPC)
	{
		m_SetEPC=FALSE;
	}
	else
	{
		m_SetEPC=TRUE;
	}

	int iCheck = ((CButton*)GetDlgItem(IDC_CHECK_EPC))->GetCheck();
	if ( iCheck )
	{
		//ѡ��
		((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USERPASS)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable))->EnableWindow(TRUE);
	}
	else
	{
		//û��ѡ��
		((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERPASS)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable))->EnableWindow(FALSE);

	}

	return;

}

void CWriteISO6C::OnBnClickedCheckUse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_SetUse)
	{
		m_SetUse=FALSE;
	}
	else
	{
		m_SetUse=TRUE;
	}
}

void CWriteISO6C::OnBnClickedCheckPass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_SetPass)
	{
		m_SetPass=FALSE;
	}
	else
	{
		m_SetPass=TRUE;
	}
}

void CWriteISO6C::OnBnClickedButtonSuccess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nRow=m_ListOutData.GetItemCount();
	if(nRow<=0)
	{
		//AfxMessageBox(_T("û��������Ҫ����!"));
		AfxMessageBox(theApp.g_LoadString("IDWQF_D0117"));
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

	CString sEpcTmp,sUseTmp,sPassTmp,strtmp,sStatus;
	int nEpc=0,nUse=0,nPass=0;

	for(int i=0;i<nRow;i++)
	{
		sEpcTmp=m_ListOutData.GetItemText(i,1);
		sUseTmp=m_ListOutData.GetItemText(i,2);
		sPassTmp=m_ListOutData.GetItemText(i,3);
		if(sEpcTmp.GetLength()>0)
		{
			nEpc=1;
		}
		if(sUseTmp.GetLength()>0)
		{
			nUse=1;
		}
		if(sPassTmp.GetLength()>0)
		{
			nPass=1;
		}
	}

	CFile f;

	f.Open(filename,CFile::modeCreate|CFile::modeReadWrite);
	
    CString tmp=_T(",");

	BYTE str[1024];
	int len;

	for(i=0;i<=nRow;i++)
	{
		strtmp.Empty(); 
		sEpcTmp=m_ListOutData.GetItemText(nRow-i,1);
		sUseTmp=m_ListOutData.GetItemText(nRow-i,2);
		sPassTmp=m_ListOutData.GetItemText(nRow-i,3);
		sStatus=m_ListOutData.GetItemText(nRow-i,4);
		//if(sStatus==_T("�ɹ�"))
		if(sStatus==theApp.g_LoadString("IDWQF_D0118"))
		{
			if(nEpc==1)
			{
				strtmp=sEpcTmp;
				if((nUse==1)||(nPass==1))
				{
					strtmp=strtmp+tmp;
				}
			}

			if(nUse==1)
			{
				strtmp=strtmp+sUseTmp;
				if(nPass==1)
				{
					strtmp=strtmp+tmp;
				}
			}
			if(nPass==1)
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
	}

	f.Close(); 
}

void CWriteISO6C::OnBnClickedButtonError()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nRow=m_ListOutData.GetItemCount();
	if(nRow<=0)
	{
		//AfxMessageBox(_T("û��������Ҫ����!"));
		AfxMessageBox(theApp.g_LoadString("IDWQF_D0119"));
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

	CString sEpcTmp,sUseTmp,sPassTmp,strtmp,sStatus;
	int nEpc=0,nUse=0,nPass=0;

	for(int i=0;i<nRow;i++)
	{
		sEpcTmp=m_ListOutData.GetItemText(i,1);
		sUseTmp=m_ListOutData.GetItemText(i,2);
		sPassTmp=m_ListOutData.GetItemText(i,3);
		if(sEpcTmp.GetLength()>0)
		{
			nEpc=1;
		}
		if(sUseTmp.GetLength()>0)
		{
			nUse=1;
		}
		if(sPassTmp.GetLength()>0)
		{
			nPass=1;
		}
	}


	CFile f;

	f.Open(filename,CFile::modeCreate|CFile::modeReadWrite);
	
    CString tmp=_T(",");

	BYTE str[1024];
	int len;

	for(i=0;i<=nRow;i++)
	{
		strtmp.Empty(); 
		sEpcTmp=m_ListOutData.GetItemText(nRow-i,1);
		sUseTmp=m_ListOutData.GetItemText(nRow-i,2);
		sPassTmp=m_ListOutData.GetItemText(nRow-i,3);
		sStatus=m_ListOutData.GetItemText(nRow-i,4);
		//if(sStatus==_T("ʧ��"))
		if(sStatus==theApp.g_LoadString("IDWQF_D0120"))
		{
			if(nEpc==1)
			{
				strtmp=sEpcTmp;
				if((nUse==1)||(nPass==1))
				{
					strtmp=strtmp+tmp;
				}
			}

			if(nUse==1)
			{
				strtmp=strtmp+sUseTmp;
				if(nPass==1)
				{
					strtmp=strtmp+tmp;
				}
			}
			if(nPass==1)
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
	}

	f.Close(); 

}

void CWriteISO6C::OnBnClickedCheckLockepcPass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ʹ������д
	//���ʹ������д���򹴣���ô��Զ����дȥ���򹴣�

	((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_Neverwriteable))->SetCheck(FALSE);
	if ( ((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->GetCheck() )
	{
		GetDlgItem(IDC_EDIT_USERPASS)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_USERPASS)->SetFocus();
	}

}

void CWriteISO6C::OnBnClickedCheckLockepcNeverwriteable()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��Զ����д
	//���ʹ����Զ����д�����ˣ���ôʹ������дȥ���򹴡�

	((CButton*)GetDlgItem(IDC_CHECK_LOCKEPC_PASS))->SetCheck(FALSE);
	GetDlgItem(IDC_EDIT_USERPASS)->EnableWindow(FALSE);

}
#endif

BOOL CWriteISO6C::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	//����ֻ���������ֺ�ABCDEF
	if( (GetFocus()   ==   GetDlgItem(IDC_EDIT_BEFOR) || 
		GetFocus()   ==   GetDlgItem(IDC_EDIT_BEGIN) ||
		GetFocus()   ==   GetDlgItem(IDC_EDIT_END) 
		 ) &&     //EdIT�ؼ���ý�����   
		pMsg->message   ==   WM_CHAR)                               //��������   
	{   
		
		UCHAR uCh=(UCHAR)pMsg->wParam;
		switch(uCh)
		{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			uCh-=32;
			
		default:;
		}
		pMsg->wParam=uCh;
		if(
			(pMsg->wParam)   ==0x20   ||
			(pMsg->wParam)   =='1'   ||
			(pMsg->wParam)   =='2'   ||
			(pMsg->wParam)   =='3'   ||   
			(pMsg->wParam)   =='4'   ||   
			(pMsg->wParam)   =='5'   ||   
			(pMsg->wParam)   =='6'   ||   
			(pMsg->wParam)   =='7'   ||   
			(pMsg->wParam)   =='8'   ||   
			(pMsg->wParam)   =='9'   ||
			(pMsg->wParam)   =='0'   ||
			(pMsg->wParam)   =='A'   ||
			(pMsg->wParam)   =='B'   ||
			(pMsg->wParam)   =='C'   ||
			(pMsg->wParam)   =='D'   ||
			(pMsg->wParam)   =='E'   ||
			(pMsg->wParam)   =='F'	 ||
			(int)(pMsg->wParam)   ==0x08 //�˸��
			
			) 
			
			return	CDialog::PreTranslateMessage(pMsg);	
		else
			return TRUE;
		
	}
	
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}
