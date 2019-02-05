#if !defined(AFX_TK900TEST_H__36031326_0B1D_49EA_84D6_000A398B5B41__INCLUDED_)
#define AFX_TK900TEST_H__36031326_0B1D_49EA_84D6_000A398B5B41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TK900Test.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTK900Test dialog

class CTK900Test : public CPropertyPage
{
	DECLARE_DYNCREATE(CTK900Test)

// Construction
public:
	CTK900Test();
	~CTK900Test();

	void UpdateStatus();

	BYTE m_antenna_sel;
	unsigned int Read_times;
	int ptr,len;
	unsigned char IDTemp[8],DB[8];

// Dialog Data
	//{{AFX_DATA(CTK900Test)
	enum { IDD = IDD_TK900_DIALOG };
	CListBox	m_ListData;
	CListCtrl	m_ListID;
	CComboBox	m_TagID;
	CComboBox	m_Interval;
	BOOL	m_Antenna1;
	BOOL	m_Antenna2;
	BOOL	m_Antenna3;
	BOOL	m_Antenna4;
	BOOL	m_ListTagID;
	int		m_Address;
	int		m_Len;
	CString	m_Data;
	BOOL	m_ReadDataBlock;
	BOOL	m_WriteDataBlock;
	int		m_SAddress;
	int		m_SLen;
	int		m_AddressPage;
	int		m_NumPage;
	BOOL	m_ListIDPage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTK900Test)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTK900Test)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnCheck8();
	afx_msg void OnButton4();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TK900TEST_H__36031326_0B1D_49EA_84D6_000A398B5B41__INCLUDED_)
