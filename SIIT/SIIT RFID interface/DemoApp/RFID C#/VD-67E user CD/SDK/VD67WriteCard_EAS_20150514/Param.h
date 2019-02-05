#if !defined(AFX_PARAM_H__A344D506_85BF_43D1_AFB4_7EBC464AF8DD__INCLUDED_)
#define AFX_PARAM_H__A344D506_85BF_43D1_AFB4_7EBC464AF8DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Param.h : header file
//

#include "lxDialogCProp.h"

/////////////////////////////////////////////////////////////////////////////
// CParam dialog

class CParam : public CPropertyPage
{
	//DECLARE_DYNCREATE(CParam)

// Construction
public:
	CParam();
	~CParam();

// Dialog Data
	//{{AFX_DATA(CParam)
	enum { IDD = IDD_PROPPAGE_PARAM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParam)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnInitUIText();//������ı�����
	void UpdateStatus();//����ʹ���벻ʹ��

	//selΪ����Ƶ���±�,iminΪ��СƵ���±�,imaxΪ���Ƶ���±�, -1Ϊ��СΪ��С�����Ϊ���
	void OnCbnSetFre(int sel, int imin, int imax);

	//��������
	void OnGetParameter();

protected:
	// Generated message map functions
	//{{AFX_MSG(CParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButton1Msget();
	afx_msg void OnButton1Msupdate();
	//}}AFX_MSG
	afx_msg LRESULT OnReaderparmdatamsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAM_H__A344D506_85BF_43D1_AFB4_7EBC464AF8DD__INCLUDED_)
