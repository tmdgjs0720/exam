// C3filter.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "C3filter.h"


// C3filter 대화 상자

IMPLEMENT_DYNAMIC(C3filter, CDialog)

C3filter::C3filter(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_w1(0)
	, m_w2(0)
	, m_w3(0)
	, m_w4(0)
	, m_w5(0)
	, m_w6(0)
	, m_w7(0)
	, m_w8(0)
	, m_w9(0)
	, m_t(0)
{

}

C3filter::~C3filter()
{
}

void C3filter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_W1, m_w1);
	DDX_Text(pDX, IDC_W2, m_w2);
	DDX_Text(pDX, IDC_W3, m_w3);
	DDX_Text(pDX, IDC_W4, m_w4);
	DDX_Text(pDX, IDC_W5, m_w5);
	DDX_Text(pDX, IDC_W6, m_w6);
	DDX_Text(pDX, IDC_W7, m_w7);
	DDX_Text(pDX, IDC_W8, m_w8);
	DDX_Text(pDX, IDC_W9, m_w9);
	DDX_Text(pDX, IDC_T, m_t);
}


BEGIN_MESSAGE_MAP(C3filter, CDialog)
END_MESSAGE_MAP()


// C3filter 메시지 처리기
