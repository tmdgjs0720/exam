// CAffine.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "CAffine.h"


// CAffine 대화 상자

IMPLEMENT_DYNAMIC(CAffine, CDialog)

CAffine::CAffine(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AFFINE, pParent)
	, m_affine_a(0)
	, m_affine_b(0)
	, m_affine_c(0)
	, m_affine_d(0)
	, m_affine_e(0)
	, m_affine_f(0)
{

}

CAffine::~CAffine()
{
}

void CAffine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_affine_a);
	DDX_Text(pDX, IDC_EDIT2, m_affine_b);
	DDX_Text(pDX, IDC_EDIT3, m_affine_c);
	DDX_Text(pDX, IDC_EDIT4, m_affine_d);
	DDX_Text(pDX, IDC_EDIT5, m_affine_e);
	DDX_Text(pDX, IDC_EDIT6, m_affine_f);
}


BEGIN_MESSAGE_MAP(CAffine, CDialog)
END_MESSAGE_MAP()


// CAffine 메시지 처리기
