// ReaderDemoDlg.h : header file
//

#if !defined(AFX_READERDEMODLG_H__325AD4E6_6A56_46B9_86DD_7C6E576328FC__INCLUDED_)
#define AFX_READERDEMODLG_H__325AD4E6_6A56_46B9_86DD_7C6E576328FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReaderParameter.h"
#include "EPCC1G2Test.h"
#include "TK900Test.h"
#include "ISO6BTest.h"
#include "ConnectReader.h"
#include "ReaderDParam.h"
#include "ReaderParameterDlg.h"
#include "OutputTest.h"
//#include "DlgBPA.h"
#include "DlgBPAA9.h"
#include "ReaderModeS.h"
#include "DlgRubbish.h"

/////////////////////////////////////////////////////////////////////////////
// CReaderDemoDlg dialog

class CReaderDemoDlg : public CDialog
{
// Construction
public:
	CReaderDemoDlg(CWnd* pParent = NULL);	// standard constructor

	CPropertySheet			m_Sheet;
	//CReaderParameter m_ReaderParameterPage;
	CReaderParameterDlg		m_ReaderParameterPage;
	CReaderDParam			m_ReaderDParamePage;
	CEPCC1G2Test			m_EPCC1G2TestPage;
	//CTK900Test m_TK900TestPage;

	#if defined (ENABLEREADERMODES)
	ReaderModeS				m_ModesPage;//小模块界面
	#elif defined (ENABLErubbish)
	//垃圾处理界面
	DlgRubbish				m_Rubbish;
	#else
	COutputTest				m_OutputPage;
	#endif

	CISO6BTest				m_ISO6BTestPage;
	CConnectReader			m_ConnectReaderPage;
	#if defined (ENABLEBPA9PROCTOL)
	CDlgBPAA9				m_BPAA9Page;
	#endif

	void SetPageForm();
// Dialog Data
	//{{AFX_DATA(CReaderDemoDlg)
	enum { IDD = IDD_READERDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReaderDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL bDispFlag;	//SW_SHOW为显示，SW_HIDE为隐藏
	
	void ShowWindowEx(int iFlag);
	void Thide();
	void Tdehide();

	void OnInitUIText();//界面和文本更新
	
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReaderDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnListuserdata(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERDEMODLG_H__325AD4E6_6A56_46B9_86DD_7C6E576328FC__INCLUDED_)
