#if !defined(AFX_CONNECTREADER_H__58554C27_E2A0_4921_A00C_D0FACEEFC177__INCLUDED_)
#define AFX_CONNECTREADER_H__58554C27_E2A0_4921_A00C_D0FACEEFC177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectReader.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnectReader dialog

class CConnectReader : public CPropertyPage
{
	DECLARE_DYNCREATE(CConnectReader)

// Construction
public:
	CConnectReader();
	~CConnectReader();

	void UpdateStatus();
	void Readini();

	CWnd * pMain;
	HANDLE m_ScanExitThreadEvent;

// Dialog Data
	//{{AFX_DATA(CConnectReader)
	enum { IDD = IDD_PROPPAGE_MEDIUM };
	CListCtrl	m_IPList;
	CIPAddressCtrl	m_HostIPAddress;
	CIPAddressCtrl	m_IPAddress;
	CComboBox	m_SerialPort;
	int		m_Port;
	int		m_HostPort;
	int		m_ConnectMode;//0-tcpip,1-rs232,2-485
	int		m_LanguageIndex;//0-English,1-chinese
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConnectReader)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	//线程函数扫描
	static DWORD WINAPI ScanPortIpThread(LPVOID pParam);
	HANDLE hScanThread;

	void OnInitUIText();//界面和文本更新

protected:
	// Generated message map functions
	//{{AFX_MSG(CConnectReader)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1Tcpip();
	afx_msg void OnRadio2Rs232();
	afx_msg void OnRadio3Rs485();
	afx_msg void OnBUTTON1ConnectScan();
	afx_msg void OnBUTTON1ScanStop();
	afx_msg void OnSelchangeCOMBOSelectAntNum();
	afx_msg void OnRADIOEnglish();
	afx_msg void OnRADIOChinese();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnConnectdatacustom(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTREADER_H__58554C27_E2A0_4921_A00C_D0FACEEFC177__INCLUDED_)
