
// ExamView.cpp: CExamView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Exam.h"
#endif

#include "ExamDoc.h"
#include "ExamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamView

IMPLEMENT_DYNCREATE(CExamView, CView)

BEGIN_MESSAGE_MAP(CExamView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_REVERSE, &CExamView::OnReverse)
	ON_COMMAND(IDM_BRIGHT, &CExamView::OnBright)
	ON_COMMAND(IDM_FRM_ADD, &CExamView::OnFrmAdd)
	ON_COMMAND(IDM_FRM_SUB, &CExamView::OnFrmSub)
	ON_COMMAND(IDM_HISTO, &CExamView::OnHisto)
	ON_COMMAND(IDM_HISTO_STRETCH, &CExamView::OnHistoStretch)
	ON_COMMAND(IDM_HISTO_EQUAL, &CExamView::OnHistoEqual)
	ON_COMMAND(IDM_TRANS, &CExamView::OnTrans)
	ON_COMMAND(IDM_ZOOM, &CExamView::OnZoom)
	ON_COMMAND(IDM_ROTATION, &CExamView::OnRotation)
	ON_COMMAND(IDM_MIR_X, &CExamView::OnMirX)
	ON_COMMAND(IDM_MIR_Y, &CExamView::OnMirY)
	ON_COMMAND(IDM_MIR_O, &CExamView::OnMirO)
	ON_COMMAND(IDM_MIR_D, &CExamView::OnMirD)
	ON_COMMAND(IDM_MIR_RD, &CExamView::OnMirRd)
	ON_COMMAND(IDM_COMPOUND, &CExamView::OnCompound)
	ON_COMMAND(IDM_AFFINE, &CExamView::OnAffine)
	ON_COMMAND(IDM_LOWPASS, &CExamView::OnLowpass)
	ON_COMMAND(IDM_MEDIAN, &CExamView::OnMedian)
	ON_COMMAND(IDM_MAX, &CExamView::OnMax)
	ON_COMMAND(IDM_MIN, &CExamView::OnMin)
	ON_COMMAND(IDM_MAX_ORI, &CExamView::OnMaxOri)

	ON_COMMAND(IDM_ORI_MIN, &CExamView::OnOriMin)
	ON_COMMAND(IDM_MAX_MIN, &CExamView::OnMaxMin)
	ON_COMMAND(IDM_HIGHPASS, &CExamView::OnHighpass)
	ON_COMMAND(IDM_3FILTER, &CExamView::On3filter)
	ON_COMMAND(IDM_PREWITT, &CExamView::OnPrewitt)
	ON_COMMAND(IDM_SOBEL, &CExamView::OnSobel)
	ON_COMMAND(IDM_ROBINSON3, &CExamView::OnRobinson3)
END_MESSAGE_MAP()

// CExamView 생성/소멸

CExamView::CExamView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	pbmi = (PBITMAPINFO)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
	pbmi->bmiHeader.biSize = (LONG)sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biPlanes = 1;
	pbmi->bmiHeader.biCompression = 0;
	pbmi->bmiHeader.biSizeImage = 0;
	pbmi->bmiHeader.biXPelsPerMeter = 0;
	pbmi->bmiHeader.biYPelsPerMeter = 0;
	pbmi->bmiHeader.biClrUsed = 256;
	pbmi->bmiHeader.biClrImportant = 0;
	pbmi->bmiHeader.biBitCount = 8;
	pbmi->bmiHeader.biWidth = 256;
	pbmi->bmiHeader.biHeight = 256;

	for (int i = 0; i < 256; i++) {
		pbmi->bmiColors[i].rgbBlue = i;
		pbmi->bmiColors[i].rgbGreen = i;
		pbmi->bmiColors[i].rgbRed = i;
	}

}

CExamView::~CExamView()
{
}

BOOL CExamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CExamView 그리기

void CExamView::OnDraw(CDC* pDC)
{
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	/*
	unsigned char Inval;
	int i, j, index, sizex, sizey;

	 sizex = pDoc->m_SizeX;
	 sizey = pDoc->m_SizeY;

	for(index=0; index<pDoc->m_NoInImg; index++){
	  for(i=0; i<sizey; i++)
		for(j=0; j<sizex ; j++)
		{
		   Inval = pDoc->m_InImg[index][i][j];
		   pDC->SetPixel(j+index*(sizex+5), i, RGB(Inval, Inval, Inval));
		}
	}
	for(index=0; index<pDoc->m_NoOutImg; index++){
	  for(i=0; i<sizey; i++)
		for(j=0; j<sizex ; j++)
		{
		   Inval = pDoc->m_OutImg[index][i][j];
		   pDC->SetPixel(j+index*(sizex+5), i+(sizey+5), RGB(Inval, Inval, Inval));
		}
	}
	 */

	 //BMP 출력하기 위하여 추가
	unsigned char Inval[256][256];
	int i, j, index, sizex, sizey;

	sizex = pDoc->m_SizeX;
	sizey = pDoc->m_SizeY;

	CClientDC dc(this);

	for (index = 0; index < pDoc->m_NoInImg; index++) {
		for (i = 0; i < sizey; i++)
			for (j = 0; j < sizex; j++)
			{
				Inval[sizey - i - 1][j] = pDoc->m_InImg[index][i][j];
			}
		SetDIBitsToDevice(dc, index * (sizex + 5), 0, sizex, sizey, 0, 0, 0, sizey,
			Inval, pbmi, DIB_RGB_COLORS);

	}
	for (index = 0; index < pDoc->m_NoOutImg; index++) {
		for (i = 0; i < sizey; i++)
			for (j = 0; j < sizex; j++)
			{
				Inval[sizey - i - 1][j] = pDoc->m_OutImg[index][i][j];
			}
		SetDIBitsToDevice(dc, index * (sizex + 5), (sizey + 5), sizex, sizey, 0, 0, 0,
			sizey, Inval, pbmi, DIB_RGB_COLORS);
	}
}


// CExamView 인쇄

BOOL CExamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CExamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CExamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CExamView 진단

#ifdef _DEBUG
void CExamView::AssertValid() const
{
	CView::AssertValid();
}

void CExamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExamDoc* CExamView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExamDoc)));
	return (CExamDoc*)m_pDocument;
}
#endif //_DEBUG


// CExamView 메시지 처리기


void CExamView::OnReverse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			pDoc->m_OutImg[0][i][j] = 255 - pDoc->m_InImg[0][i][j];
		}
	}
	Invalidate(FALSE);  //OnDraw 호출
}


void CExamView::OnBright()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument(); //도큐멘터 클래스를 참조하기 위해
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	pDoc->m_Bright(pDoc->m_SizeY, pDoc->m_SizeX);
	Invalidate(FALSE);
}


void CExamView::OnFrmAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 2;
	pDoc->m_NoOutImg = 1;

	pDoc->m_TwoImgLoad();
	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			int temp = pDoc->m_InImg[0][i][j] + pDoc->m_InImg[1][i][j];
			temp = temp > 255 ? 255 : temp;
			temp = temp < 0 ? 0 : temp;

			pDoc->m_OutImg[0][i][j] = temp;
		}
	}
	Invalidate(FALSE);
}


void CExamView::OnFrmSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 2;
	pDoc->m_NoOutImg = 1;

	pDoc->m_TwoImgLoad();
	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			int temp = abs(pDoc->m_InImg[0][i][j] - pDoc->m_InImg[1][i][j]);
			temp = temp > 255 ? 255 : temp;
			temp = temp < 0 ? 0 : temp;

			pDoc->m_OutImg[0][i][j] = temp;
		}
	}
	Invalidate(FALSE);
}


void CExamView::OnHisto()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	pDoc->m_Histo(pDoc->m_SizeY, pDoc->m_SizeX);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, (pDoc->m_SizeY) * (pDoc->m_SizeX));

	Invalidate(FALSE);
}


void CExamView::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	pDoc->m_HistoStretch(pDoc->m_SizeY, pDoc->m_SizeX);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, (pDoc->m_SizeY) * (pDoc->m_SizeX));

	Invalidate(FALSE);
}


void CExamView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	pDoc->m_HistoEqual(pDoc->m_SizeY, pDoc->m_SizeX);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, (pDoc->m_SizeY) * (pDoc->m_SizeX));

	Invalidate(FALSE);
}


void CExamView::OnTrans()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument(); //도큐멘터 클래스를 참조하기 위해 
	ASSERT_VALID(pDoc);// 주소를 가져옴 
	int transx, transy;
	if (pDoc->m_TransDlg.DoModal() == IDOK)
	{
		transx = pDoc->m_TransDlg.m_transx; //수평방향 이동 
		transy = pDoc->m_TransDlg.m_transy; //수직방향 이동
	}

	memset(pDoc->m_OutImg[0], 128, (pDoc->m_SizeY) * (pDoc->m_SizeX));

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			int y = i - transy;
			int x = j - transx;
			if ((x >= 0 && x < pDoc->m_SizeX) && (y >= 0 && y < pDoc->m_SizeY))
			{
				pDoc->m_OutImg[0][i][j] = pDoc->m_InImg[0][y][x];
			}
		}
	}
	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	Invalidate(FALSE); //화면갱신 
}


void CExamView::OnZoom()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	pDoc->m_Zoom(pDoc->m_SizeY, pDoc->m_SizeX, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, (pDoc->m_SizeY) * (pDoc->m_SizeX));

	Invalidate(FALSE); //OnDraw()함수 호출
}


void CExamView::OnRotation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Rotation(height, width, (height / 2), (width / 2), pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	Invalidate(FALSE);
}


void CExamView::OnMirX()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument(); //도큐멘터 클래스를 참조하기 위해 
	ASSERT_VALID(pDoc);// 주소를 가져옴 
	int x, y;

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			y = pDoc->m_SizeY - 1 - i;
			x = j;
			pDoc->m_OutImg[0][i][j] = pDoc->m_InImg[0][y][x];
		}
	}
	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	Invalidate(FALSE); //화면갱신 
}


void CExamView::OnMirY()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument(); //도큐멘터 클래스를 참조하기 위해 
	ASSERT_VALID(pDoc);// 주소를 가져옴 
	int x, y;

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			y =  i;
			x = pDoc->m_SizeX - 1 -j;
			pDoc->m_OutImg[0][i][j] = pDoc->m_InImg[0][y][x];
		}
	}
	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	Invalidate(FALSE); //화면갱신 
}


void CExamView::OnMirO()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument(); //도큐멘터 클래스를 참조하기 위해 
	ASSERT_VALID(pDoc);// 주소를 가져옴 
	int x, y;

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			y = pDoc->m_SizeY - 1 - i;
			x = pDoc->m_SizeX - 1 - j;
			pDoc->m_OutImg[0][i][j] = pDoc->m_InImg[0][y][x];
		}
	}
	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	Invalidate(FALSE); //화면갱신 
}


void CExamView::OnMirD()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument(); //도큐멘터 클래스를 참조하기 위해 
	ASSERT_VALID(pDoc);// 주소를 가져옴 
	int x, y;

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			y = j;
			x = i;
			pDoc->m_OutImg[0][i][j] = pDoc->m_InImg[0][y][x];
		}
	}
	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	Invalidate(FALSE); //화면갱신 
}


void CExamView::OnMirRd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument(); //도큐멘터 클래스를 참조하기 위해 
	ASSERT_VALID(pDoc);// 주소를 가져옴 
	int x, y;

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			y = pDoc->m_SizeX - 1 - j;
			x = pDoc->m_SizeY - 1 - i;
			pDoc->m_OutImg[0][i][j] = pDoc->m_InImg[0][y][x];
		}
	}
	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;

	Invalidate(FALSE); //화면갱신 
}


void CExamView::OnCompound()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	OnTrans();

	memcpy(pDoc->m_InImg[0], pDoc->m_OutImg[0], height * width);

	OnZoom();

	memcpy(pDoc->m_InImg[0], pDoc->m_OutImg[0], height * width);

	OnRotation();
}


void CExamView::OnAffine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//Doc에 m_Affine 함수호출

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Affine(height, width);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);
	Invalidate(FALSE);
}


void CExamView::OnLowpass()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Lowpass(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	Invalidate(FALSE);  //OnDraw()함수 호출	
}


void CExamView::OnMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Median(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	Invalidate(FALSE);  //OnDraw()함수 호출		
}




void CExamView::OnMax()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Max(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	Invalidate(FALSE);  //OnDraw()함수 호출	
}


void CExamView::OnMin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Min(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	Invalidate(FALSE);  //OnDraw()함수 호출	
}


void CExamView::OnMaxOri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 2;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Max(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			
			pDoc->m_OutImg[1][i][j] 
				= pDoc->m_OutImg[0][i][j] - pDoc->m_InImg[0][i][j];
		}
	}
	Invalidate(FALSE);  //OnDraw()함수 호출	
}


void CExamView::OnOriMin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 2;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Min(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{

			pDoc->m_OutImg[1][i][j]
				= pDoc->m_InImg[0][i][j] - pDoc->m_OutImg[0][i][j];
		}
	}
	Invalidate(FALSE);  //OnDraw()함수 호출	

}


void CExamView::OnMaxMin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 3;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Max(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);
	pDoc->m_Min(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[1], pDoc->m_OutImgTemp, height * width);

	for (int i = 0; i < pDoc->m_SizeY; i++)
	{
		for (int j = 0; j < pDoc->m_SizeX; j++)
		{
			pDoc->m_OutImg[2][i][j]
				= pDoc->m_OutImg[0][i][j] - pDoc->m_OutImg[1][i][j];
		}
	}
	Invalidate(FALSE);  //OnDraw()함수 호출	

}


void CExamView::OnHighpass()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Highpass(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	Invalidate(FALSE);  //OnDraw()함수 호출	
}



void CExamView::On3filter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 1;
	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_3filter(height, width, pDoc->m_InImg[0]);
	memcpy(pDoc->m_OutImg[0], pDoc->m_OutImgTemp, height * width);

	Invalidate(FALSE);  //OnDraw()함수 호출		
}


void CExamView::OnPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 3;

	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Prewitt(height, width, pDoc->m_InImg[0]);
	Invalidate(FALSE);  //OnDraw()함수 호출			
}


void CExamView::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 3;

	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Sobel(height, width, pDoc->m_InImg[0]);
	Invalidate(FALSE);  //OnDraw()함수 호출			

}


void CExamView::OnRobinson3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CExamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_NoInImg = 1;
	pDoc->m_NoOutImg = 4;

	int height = pDoc->m_SizeY;
	int width = pDoc->m_SizeX;

	pDoc->m_Robinson3(height, width, pDoc->m_InImg[0]);
	Invalidate(FALSE);  //OnDraw()함수 호출	
}
