#if !defined(AFX_OUTPUTTEST_H__AFC915C8_815A_47A9_99A1_A1DEDA57289B__INCLUDED_)
#define AFX_OUTPUTTEST_H__AFC915C8_815A_47A9_99A1_A1DEDA57289B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputTest.h : header file
//

#include "containers.h"

/////////////////////////////////////////////////////////////////////////////
// COutputTest dialog

class COutputTest : public CPropertyPage
{
	DECLARE_DYNCREATE(COutputTest)

// Construction
public:
	COutputTest();
	~COutputTest();

// Dialog Data
	//{{AFX_DATA(COutputTest)
	enum { IDD = IDD_PROPPAGE_OUTPUT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COutputTest)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	//自动模式下读线程函数
	static DWORD WINAPI ReadThreadFuncTag(LPVOID pParam);
	HANDLE hReadThread;

	static void WINAPI CallBack_DataOutput(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime);

	apiReturn TranAutoStopMode();
	int		ConnecCom(HANDLE *hScanner, char *szPort, int nBaudRate);
	int		DisconnectCom(HANDLE hScanner);
	int		ConnectRj45();
    void	DisconnectRj45();

	//得到解析的数据
	BOOL	GetAutoModeRecvTran(char *chInBuf, int iInSize, char **chOutBuf, int &iOutSize);

	void OnInitUIText();//界面和文本更新

	CFont	*m_TagNumsFont;	//标签数字体
	RECT rectListInfo;
	RECT rectEditOutput;
	

	

protected:
	// Generated message map functions
	//{{AFX_MSG(COutputTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonWeg26start();
	afx_msg void OnButtonWeg26stop();
	afx_msg void OnButtonWeg34start();
	afx_msg void OnButtonWeg34stop();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnCheckOne();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonClearscreen();
	afx_msg void OnCheck1Output();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBUTTONClearMemory();
	afx_msg void OnBUTTONReportNow();
	afx_msg void OnBUTTONGetTagInfo();
	//}}AFX_MSG
	afx_msg LRESULT OnOutputtestdatamsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTTEST_H__AFC915C8_815A_47A9_99A1_A1DEDA57289B__INCLUDED_)
