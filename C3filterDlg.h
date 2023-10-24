#pragma once
#include "afxdialogex.h"


// C3filterDlg 대화 상자

class C3filterDlg : public CDialog
{
	DECLARE_DYNAMIC(C3filterDlg)

public:
	C3filterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~C3filterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
