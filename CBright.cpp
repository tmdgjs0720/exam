// CBright.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "CBright.h"


// CBright 대화 상자

IMPLEMENT_DYNAMIC(CBright, CDialog)

CBright::CBright(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BRIGHT, pParent)
	, m_brightvalue(0)
{

}

CBright::~CBright()
{
}

void CBright::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BRIGHTVALUE, m_brightvalue);
}


BEGIN_MESSAGE_MAP(CBright, CDialog)
END_MESSAGE_MAP()


// CBright 메시지 처리기
