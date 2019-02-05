#if !defined(AFX_READERMODES_H__563B02DC_04F0_489E_9E12_3094471FC81E__INCLUDED_)
#define AFX_READERMODES_H__563B02DC_04F0_489E_9E12_3094471FC81E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReaderModeS.h : header file
//

#include "containers.h"

/////////////////////////////////////////////////////////////////////////////
// ReaderModeS dialog

class ReaderModeS : public CPropertyPage
{
	DECLARE_DYNCREATE(ReaderModeS)

// Construction
public:
	ReaderModeS();
	~ReaderModeS();

// Dialog Data
	//{{AFX_DATA(ReaderModeS)
	enum { IDD = IDD_PROPPAGE_SMALLMODE };
	int		m_DataFormat;//0-16进制,1-10进制
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReaderModeS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	public:
		//自动模式下读线程函数
		static DWORD WINAPI ReadThreadS(LPVOID pParam);
		HANDLE hReadThread;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ReaderModeS)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButton1Msget();
	afx_msg void OnButton1Msupdate();
	afx_msg void OnButton1Msstartrecv();
	afx_msg void OnButton1Msstoprecv();
	//}}AFX_MSG
	afx_msg LRESULT OnRSModedatamsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERMODES_H__563B02DC_04F0_489E_9E12_3094471FC81E__INCLUDED_)
