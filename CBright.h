#pragma once
#include "afxdialogex.h"


// CBright 대화 상자

class CBright : public CDialog
{
	DECLARE_DYNAMIC(CBright)

public:
	CBright(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBright();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BRIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_brightvalue;
};
