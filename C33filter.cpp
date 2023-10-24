// C33filter.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "C33filter.h"


// C33filter 대화 상자

IMPLEMENT_DYNAMIC(C33filter, CDialog)

C33filter::C33filter(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

C33filter::~C33filter()
{
}

void C33filter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C33filter, CDialog)
END_MESSAGE_MAP()


// C33filter 메시지 처리기
