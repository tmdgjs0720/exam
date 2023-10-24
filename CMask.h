#pragma once
#include "afxdialogex.h"


// CMask 대화 상자

class CMask : public CDialog
{
	DECLARE_DYNAMIC(CMask)

public:
	CMask(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMask();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_w1;
	int m_w1;
	int m_w1;
	int m_w1;
	int m_w1;
	int m_w1;
};
