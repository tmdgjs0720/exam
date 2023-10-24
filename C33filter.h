#pragma once
#include "afxdialogex.h"


// C33filter 대화 상자

class C33filter : public CDialog
{
	DECLARE_DYNAMIC(C33filter)

public:
	C33filter(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~C33filter();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_w1;
	int m_w2;
	int m_w3;
	int m_w4;
	int m_w5;
	int m_w6;
	int m_w7;
	int m_w8;
	int m_w9;
	int m_t;
}; 