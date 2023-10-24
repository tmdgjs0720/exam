#pragma once
#include "afxdialogex.h"


// CMaske 대화 상자

class CMaske : public CDialog
{
	DECLARE_DYNAMIC(CMaske)

public:
	CMaske(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMaske();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MASK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_masksize;
};
