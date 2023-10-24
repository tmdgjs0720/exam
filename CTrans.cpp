// CTrans.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "CTrans.h"


// CTrans 대화 상자

IMPLEMENT_DYNAMIC(CTrans, CDialog)

CTrans::CTrans(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TRANS, pParent)
	, m_transx(0)
	, m_transy(0)
{

}

CTrans::~CTrans()
{
}

void CTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TRANSX, m_transx);
	DDX_Text(pDX, IDC_TRANSY, m_transy);
}


BEGIN_MESSAGE_MAP(CTrans, CDialog)
END_MESSAGE_MAP()


// CTrans 메시지 처리기
