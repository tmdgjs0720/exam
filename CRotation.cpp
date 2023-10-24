// CRotation.cpp: 구현 파일
//

#include "pch.h"
#include "Exam.h"
#include "afxdialogex.h"
#include "CRotation.h"


// CRotation 대화 상자

IMPLEMENT_DYNAMIC(CRotation, CDialog)

CRotation::CRotation(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ROTATION, pParent)
	, m_rotationangle(0)
{

}

CRotation::~CRotation()
{
}

void CRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROTATIONANGLE, m_rotationangle);
}


BEGIN_MESSAGE_MAP(CRotation, CDialog)
END_MESSAGE_MAP()


// CRotation 메시지 처리기
