// CMaske.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "CMaske.h"


// CMaske 대화 상자

IMPLEMENT_DYNAMIC(CMaske, CDialog)

CMaske::CMaske(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MASK, pParent)
	, m_masksize(0)
{

}

CMaske::~CMaske()
{
}

void CMaske::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MASKSIZE, m_masksize);
}


BEGIN_MESSAGE_MAP(CMaske, CDialog)
END_MESSAGE_MAP()


// CMaske 메시지 처리기
