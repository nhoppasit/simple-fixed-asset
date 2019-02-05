#if !defined(AFX_READERPARAMETERDLG_H__280A996D_C555_49EC_B3B5_31AD2BE8A513__INCLUDED_)
#define AFX_READERPARAMETERDLG_H__280A996D_C555_49EC_B3B5_31AD2BE8A513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReaderParameterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReaderParameterDlg dialog

class CReaderParameterDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CReaderParameterDlg)

// Construction
public:
	CReaderParameterDlg();   // standard constructor
	~CReaderParameterDlg();

// Dialog Data
	//{{AFX_DATA(CReaderParameterDlg)
	enum { IDD = IDD_PROPPAGE_PARAMETER };
	int		m_IsAutocmd;//0-Auto,1-Command
	int		m_IsoChoose;//0-6B,1-6C
	int		m_OutputPortMode;	//0-RS232,1-RS485,2-RJ45,3-Wiegand26,4-Wiegand34
	int		m_OutputFormata;	//0-��,1-��׼
	int		m_TriggerModea;		//0-�͵�ƽ��1-�ߵ�ƽ
	int		m_FromTaga;			//0-��ǩ����ID��1-�û��Զ���
	int		m_Condiona;			//0-����֪ͨ,1-��ʱ֪ͨ,2-�����±�ǩ,3-���ٱ�ǩ,4-��ǩ���仯
	int		m_OutputInteTimems;	//0-10ms��1-20ms��2-30ms��3-50ms��4-100ms��ȱʡֵΪ2��ÿ���趨ʱ��������ȡһ�α�ǩ��
	int		m_AutoWorkMode;		//0-��ʱ��1-����
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReaderParameterDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	//selΪ����Ƶ���±�,iminΪ��СƵ���±�,imaxΪ���Ƶ���±�, -1Ϊ��СΪ��С�����Ϊ���
	void OnCbnSetFre(int sel, int imin, int imax);
	BOOL OnReadParameter(int iOpt);	//iOpt,0--����������1--�Զ�����
	BOOL OnUpdateParameter(void *pParam, int iOpt);	//iOpt,0--����������1--�Զ�����, 2--����ֵ

	void UpdateStatus();
	void OnInitUIText();	//��������
	static void WINAPI CallBack_MyTimeParam(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime);

protected:

	// Generated message map functions
	//{{AFX_MSG(CReaderParameterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetbasic();
	afx_msg void OnButtonSetauto();
	afx_msg void OnButtonActivefactory();
	afx_msg void OnButtonReadfilter();
	afx_msg void OnButtonSetfilter();
	afx_msg void OnButtonGetrelay();
	afx_msg void OnButtonSetrelay();
	afx_msg void OnButton1Readtime();
	afx_msg void OnButton1Settime();
	afx_msg void OnDestroy();
	afx_msg void OnButtonWorkautostart();
	afx_msg void OnButtonWorkautostop();
	//}}AFX_MSG
	afx_msg LRESULT OnReaderparmdatamsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERPARAMETERDLG_H__280A996D_C555_49EC_B3B5_31AD2BE8A513__INCLUDED_)
