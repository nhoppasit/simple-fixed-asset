#if !defined(AFX_DLGBPAA9_H__B9D7F912_A3D2_4F83_BCCA_523A1D5497ED__INCLUDED_)
#define AFX_DLGBPAA9_H__B9D7F912_A3D2_4F83_BCCA_523A1D5497ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBPAA9.h : header file
//
#include	<list>
using namespace std;

#include "containers.h"



//////////////////////////////////////////////////////////////////////////
#if 0 
//list cList; //声明了list模板类 的一个实例 


//typedef list<int> arraylist;
//arraylist mylist;

CList <void*, void*> vet;//ok
//CList <DataTest*,DataTest*> test;
//CList<SSerInfo,SSerInfo&> asi;
//list <void*> Milkshakes;//ok


dpack	=	new DataPacket;
dpack->len	=	iDpCount;
sprintf(dpack->chbuf, _T("a%db%dc%d"), iDpCount, iDpCount, iDpCount);

Milkshakes.push_back((void*)dpack);

vet.AddTail((void*)dpack);

m_ReadBuffer.AddTail(*dpack);

#if 0
for (MilkshakeIterator=Milkshakes.begin();

MilkshakeIterator!=Milkshakes.end();

++MilkshakeIterator)

{
	
	// dereference the iterator to get the element
	
	//cout << *MilkshakeIterator << endl;
	DataPacket *tt	=	(DataPacket*)(void*)(*MilkshakeIterator);
	TRACE("%d:%s\n", tt->len, tt->chbuf);
	
}
#endif


if ( FALSE == vet.IsEmpty() )
{
	dpack	=	(DataPacket*)vet.GetHead();
	vet.RemoveHead();
	
	*dpack = m_ReadBuffer.GetHead();
	//m_ReadBuffer.RemoveHead();
}	
#endif
//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CDlgBPAA9 dialog

class CDlgBPAA9 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgBPAA9)

// Construction
public:
	CDlgBPAA9();
	~CDlgBPAA9();

// Dialog Data
	//{{AFX_DATA(CDlgBPAA9)
	enum { IDD = IDD_PROPPAGE_BPA9 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	int		m_Bpa9Opt;//0-Granted,1-Denied
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgBPAA9)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	
	//线程函数扫描
	static DWORD WINAPI ScanTagThread(LPVOID pParam);
	HANDLE hScanTagThread;

	void OnInitUIText();//界面和文本更新

	static void WINAPI CallBack_MyDlgBpa9(HWND   hWnd,UINT   nMsg,UINT   nIDEvent,DWORD   dwTime);

	int intervalTime;	//间隔时间

// Implementation
protected:

	struct DataPacket
	{
		int len;	//buffer length
		char chbuf[MAX_PATH];	//actual buffer
		//char *buf;
		//char *pos;	//position in the buffer (avoids buffer resizing)
	};
	//DataPacket *dpack;
	int iDpCount;

	//list <void*> Milkshakes;
	//list <void*>::iterator MilkshakeIterator;
	
	//struct a1{
	//	int  curIndex: 3;
	//	
	//}m_alarm={0};

	//CTList<DataPacket> m_ReadBuffer;

protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgBPAA9)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck5Bpa9();
	afx_msg void OnButton1Cmd1();
	afx_msg void OnButton1Cmd2();
	//}}AFX_MSG
	afx_msg LRESULT OnDlgBPA9Data(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBPAA9_H__B9D7F912_A3D2_4F83_BCCA_523A1D5497ED__INCLUDED_)
