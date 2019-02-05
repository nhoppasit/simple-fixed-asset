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
	int		m_OutputFormata;	//0-简化,1-标准
	int		m_TriggerModea;		//0-低电平，1-高电平
	int		m_FromTaga;			//0-标签本身ID，1-用户自定义
	int		m_Condiona;			//0-立即通知,1-定时通知,2-增加新标签,3-减少标签,4-标签数变化
	int		m_OutputInteTimems;	//0-10ms，1-20ms，2-30ms，3-50ms，4-100ms。缺省值为2。每隔设定时间主动读取一次标签。
	int		m_AutoWorkMode;		//0-定时，1-触发
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
	//sel为国家频率下标,imin为最小频率下标,imax为最大频率下标, -1为最小为最小，最大为最大
	void OnCbnSetFre(int sel, int imin, int imax);
	BOOL OnReadParameter(int iOpt);	//iOpt,0--基本参数，1--自动参数
	BOOL OnUpdateParameter(void *pParam, int iOpt);	//iOpt,0--基本参数，1--自动参数, 2--出厂值

	void UpdateStatus();
	void OnInitUIText();	//更新语言
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
