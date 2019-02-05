#if !defined(AFX_READERPARAMETER_H__EC1FCA15_5DE1_4C66_9770_8711F8144EE9__INCLUDED_)
#define AFX_READERPARAMETER_H__EC1FCA15_5DE1_4C66_9770_8711F8144EE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReaderParameter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReaderParameter dialog

class CReaderParameter : public CPropertyPage
{
	DECLARE_DYNCREATE(CReaderParameter)

// Construction
public:
	CReaderParameter();
	~CReaderParameter();

	void UpdateStatus();
	BOOL ReadParameter();
	CString ReportError(USHORT res);

	int Antenna,TagType,EnableBuzzer;

// Dialog Data
	//{{AFX_DATA(CReaderParameter)
	enum { IDD = IDD_PARAMETER_DIALOG };
	CListBox	m_ReaderTime;
	CIPAddressCtrl	m_HostIPAddress;
	CIPAddressCtrl	m_ReaderGateway;
	CIPAddressCtrl	m_ReaderIPMask;
	CIPAddressCtrl	m_ReaderIPAddress;
	CComboBox	m_ReadCycle;
	CComboBox	m_ReadDuration;
	CComboBox	m_ReadInterval;
	CComboBox	m_MaxFrequency;
	CComboBox	m_MinFrequency;
	CComboBox	m_BaudRate;
	int		m_WorkMode;
	int		m_Power1;
	int		m_Power2;
	BOOL	m_Relay1;
	BOOL	m_Relay2;
	int		m_NumofCard;
	BOOL	m_Antenna1;
	BOOL	m_Antenna2;
	BOOL	m_Antenna3;
	BOOL	m_Antenna4;
	int		m_OutInterface;
	int		m_WiegandWidth;
	int		m_WiegandInterval;
	int		m_IDStart;
	int		m_OutMode;
	CString	m_HardVer;
	CString	m_SoftVer;
	BOOL	m_Modulation;
	BOOL	m_TXMode;
	int		m_TagType;
	int		m_StandardTime;
	BOOL	m_EnableBuzzer;
	int		m_IDPosition;
	int		m_AddressReader;
	BOOL	m_RS485;
	int		m_ReaderPort;
	int		m_HostPort;
	BOOL	m_CheckAuthorization;
	CString	m_ReaderMAC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReaderParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CReaderParameter)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio13();
	afx_msg void OnRadio14();
	afx_msg void OnCheck14();
	afx_msg void OnButton6();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERPARAMETER_H__EC1FCA15_5DE1_4C66_9770_8711F8144EE9__INCLUDED_)
