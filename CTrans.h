#pragma once
#include "afxdialogex.h"


// CTrans 대화 상자

class CTrans : public CDialog
{
	DECLARE_DYNAMIC(CTrans)

public:
	CTrans(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTrans();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_transx;
	int m_transy;
};
