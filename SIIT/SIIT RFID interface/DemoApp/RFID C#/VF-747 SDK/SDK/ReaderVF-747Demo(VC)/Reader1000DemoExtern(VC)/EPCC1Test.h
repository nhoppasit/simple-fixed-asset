#if !defined(AFX_EPCC1TEST_H__F3E26948_02A6_47E3_B73F_12BCF6E9B461__INCLUDED_)
#define AFX_EPCC1TEST_H__F3E26948_02A6_47E3_B73F_12BCF6E9B461__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EPCC1Test.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEPCC1Test dialog

class CEPCC1Test : public CPropertyPage
{
	DECLARE_DYNCREATE(CEPCC1Test)

// Construction
public:
	CEPCC1Test();
	~CEPCC1Test();

	void UpdateStatus();

	BYTE m_antenna_sel;
	unsigned int Read_times;
	int ptr,len;
	unsigned char pValue[96];

// Dialog Data
	//{{AFX_DATA(CEPCC1Test)
	enum { IDD = IDD_EPCC1_DIALOG };
	CComboBox	m_Interval;
	CListCtrl	m_ListID;
	BOOL	m_Antenna1;
	BOOL	m_Antenna2;
	BOOL	m_Antenna3;
	BOOL	m_Antenna4;
	int		m_ReadSelectTag;
	int		m_LAddress;
	int		m_LLen;
	CString	m_LData;
	BOOL	m_ListTagID;
	CString	m_TagID;
	int		m_ASAddress;
	int		m_ASLen;
	CString	m_ASData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEPCC1Test)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEPCC1Test)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnCheck5();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EPCC1TEST_H__F3E26948_02A6_47E3_B73F_12BCF6E9B461__INCLUDED_)
