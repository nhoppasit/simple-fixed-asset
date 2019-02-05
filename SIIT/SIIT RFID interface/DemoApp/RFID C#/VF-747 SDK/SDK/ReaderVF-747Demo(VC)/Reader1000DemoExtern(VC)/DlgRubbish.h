#if !defined(AFX_DLGRUBBISH_H__E4F78BC1_C52C_4DBE_BF23_096A61CC53CE__INCLUDED_)
#define AFX_DLGRUBBISH_H__E4F78BC1_C52C_4DBE_BF23_096A61CC53CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRubbish.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRubbish dialog

class DlgRubbish : public CPropertyPage
{
	DECLARE_DYNCREATE(DlgRubbish)

// Construction
public:
	DlgRubbish();
	~DlgRubbish();

// Dialog Data
	//{{AFX_DATA(DlgRubbish)
	enum { IDD = IDD_PROPPAGE_rubbish };
	int		m_nSID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(DlgRubbish)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DlgRubbish)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDelrurecord();
	afx_msg void OnDestroy();
	afx_msg void OnButtonGetruid();
	afx_msg void OnButtonSetruid();
	afx_msg void OnButtonSetrurecord();
	afx_msg void OnButtonGetruallrecord();
	afx_msg void OnRadio0Ru1();
	afx_msg void OnRadio0Ru2();
	afx_msg void OnRadio0Ru3();
	afx_msg void OnRadio0Ru4();
	afx_msg void OnRadio0Ru5();
	afx_msg void OnRadio2Ru6();
	afx_msg void OnRadio2Ru7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRUBBISH_H__E4F78BC1_C52C_4DBE_BF23_096A61CC53CE__INCLUDED_)
