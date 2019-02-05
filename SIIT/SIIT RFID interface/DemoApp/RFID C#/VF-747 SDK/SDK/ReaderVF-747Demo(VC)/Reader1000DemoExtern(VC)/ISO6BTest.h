#if !defined(AFX_ISO6BTEST_H__A329BB89_B7FB_4802_BAED_E787740BAFC3__INCLUDED_)
#define AFX_ISO6BTEST_H__A329BB89_B7FB_4802_BAED_E787740BAFC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISO6BTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CISO6BTest dialog

class CISO6BTest : public CPropertyPage
{
	DECLARE_DYNCREATE(CISO6BTest)

// Construction
public:
	CISO6BTest();
	~CISO6BTest();

	void UpdateStatus();

	BYTE m_antenna_sel;
	unsigned int Read_times;
	int ptr,len,cmd,mask;
	unsigned char IDTemp[8],DB[32];
	BYTE gAntenna[4];//add by mqs 20130710
	int iModAnt;	//选中的个数

	void OnInitUIText();//界面和文本更新

// Dialog Data
	//{{AFX_DATA(CISO6BTest)
	enum { IDD = IDD_ISO6B_DIALOG };
	CComboBox	m_TagID;
	CListBox	m_ListData;
	CComboBox	m_Interval;
	CListCtrl	m_ListID;
	BOOL	m_Antenna1;
	BOOL	m_Antenna2;
	BOOL	m_Antenna3;
	BOOL	m_Antenna4;
	BOOL	m_ListTag;
	BOOL	m_ListTagID;
	int		m_RWAddress;
	int		m_RWLen;
	CString	m_RWData;
	BOOL	m_ReadDataBlock;
	BOOL	m_WriteDataBlock;
	BOOL	m_ListSelectTagID;
	int		m_SCmd;
	int		m_SAddress;
	CString	m_SData;
	int		m_PAddress;
	BOOL	m_WriteAByteData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CISO6BTest)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CISO6BTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnCheck7();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheck10();
	//}}AFX_MSG
	afx_msg LRESULT OnUsertimerdatatran(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISO6BTEST_H__A329BB89_B7FB_4802_BAED_E787740BAFC3__INCLUDED_)
