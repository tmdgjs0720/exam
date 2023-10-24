// CZoom.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "CZoom.h"


// CZoom 대화 상자

IMPLEMENT_DYNAMIC(CZoom, CDialog)

CZoom::CZoom(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ZOOM, pParent)
	, m_zoomsize(0)
{

}

CZoom::~CZoom()
{
}

void CZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZOOMSIZE, m_zoomsize);
}


BEGIN_MESSAGE_MAP(CZoom, CDialog)
END_MESSAGE_MAP()


// CZoom 메시지 처리기
