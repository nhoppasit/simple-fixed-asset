#if !defined(AFX_READERDPARAM_H__6692B50F_55E7_44C9_817F_E3171FAA84B7__INCLUDED_)
#define AFX_READERDPARAM_H__6692B50F_55E7_44C9_817F_E3171FAA84B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReaderDParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReaderDParam dialog

class CReaderDParam : public CPropertyPage
{
	DECLARE_DYNCREATE(CReaderDParam)

// Construction
public:
	CReaderDParam();
	~CReaderDParam();

	int tagType,currentTagType;
	void UpdateStatus();
	CString ReportError(USHORT res);
	BOOL ReadParameter();
	BOOL ReadConnParameter();
	int nFrequencyRange;

// Dialog Data
	//{{AFX_DATA(CReaderDParam)
	enum { IDD = IDD_DIALOG_PARAMETER };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	CComboBox	m_ISO6BCondition;
	CIPAddressCtrl	m_HostIPAddress;
	CListBox	m_Info;
	CComboBox	m_PauseTimeofRead;
	CIPAddressCtrl	m_Gateway;
	CIPAddressCtrl	m_Mask;
	CIPAddressCtrl	m_IPAddress;
	CComboBox	m_MaxFrequency;
	CComboBox	m_MinFrequency;
	CComboBox	m_BaudRate;
	int		m_WorkMode;
	int		m_Power;
	int		m_NumofCard;
	BOOL	m_ISO6B;
	BOOL	m_EPCC1;
	BOOL	m_EPCC1G2;
	BOOL	m_EM4442;
	BOOL	m_Antenna1;
	BOOL	m_Antenna2;
	BOOL	m_Antenna3;
	BOOL	m_Antenna4;
	int		m_Port;
	CString	m_MAC;
	int		m_AutoMode;
	int		m_OutputPort;
	int		m_OutputManner;
	int		m_ReportCondition;
	int		m_PersistenceTime;
	int		m_LenofList;
	int		m_PauseTimeofReport;
	int		m_TriggerMode;
	int		m_FilterAddress;
	int		m_FilterLength;
	CString	m_FilterMask;
	CString	m_HardVer;
	CString	m_SoftVer;
	CString	m_ReaderID;
	BOOL	m_Relay1;
	BOOL	m_ifTestAlarm;
	int		m_HostPort;
	BOOL	m_EnableBuzzer;
	BOOL	m_RS485;
	int		m_AddressReader;
	BOOL	m_ReportOutput;
	int		m_WiegandWidth;
	int		m_WiegandInterval;
	int		m_IDStart;
	BOOL	m_EnableRelay;
	int		m_IDPosition;
	BOOL	m_Relay2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReaderDParam)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnInitUIText();	//更新语言
	void OnCbnSetFrT(int sel, int imin, int imax);//sel为国家频率下标,imin为最小频率下标,imax为最大频率下标(针对218)

protected:
	// Generated message map functions
	//{{AFX_MSG(CReaderDParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton5();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	afx_msg void OnButton15();
	afx_msg void OnCheck1();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnButton4();
	afx_msg void OnButton6();
	afx_msg void OnButtonGetModuleVer();
	//}}AFX_MSG
	afx_msg LRESULT OnReaderparmdatamsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERDPARAM_H__6692B50F_55E7_44C9_817F_E3171FAA84B7__INCLUDED_)
