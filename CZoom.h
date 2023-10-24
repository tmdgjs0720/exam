#pragma once
#include "afxdialogex.h"


// CZoom 대화 상자

class CZoom : public CDialog
{
	DECLARE_DYNAMIC(CZoom)

public:
	CZoom(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CZoom();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_zoomsize;
};
