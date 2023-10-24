
// ExamDoc.cpp: CExamDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Exam.h"
#endif

#include "ExamDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExamDoc

IMPLEMENT_DYNCREATE(CExamDoc, CDocument)

BEGIN_MESSAGE_MAP(CExamDoc, CDocument)
END_MESSAGE_MAP()


// CExamDoc 생성/소멸

CExamDoc::CExamDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_SizeX = 256;
	m_SizeY = 256;
	m_NoInImg = 1;
	m_NoOutImg = 1;
}

CExamDoc::~CExamDoc()
{
}

BOOL CExamDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CExamDoc serialization

void CExamDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar.Write(m_OutImg[0], m_SizeX * m_SizeY);//처리된 영상 m_OutImg를 파일로 저장 
	}
	else
	{
		CFile* infile = ar.GetFile();//입력할 파일의 포인트를 가져옴 
		if (infile->GetLength() != m_SizeX * m_SizeY) //파일 사이즈의 크기를 검사함 
		{
			AfxMessageBox(_T("파일의 크기가 맞지 않습니다."));
			return;
		}
		ar.Read(m_InImg[0], infile->GetLength());//영상파일을 읽어 m_InImg에 저장
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CExamDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CExamDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CExamDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CExamDoc 진단

#ifdef _DEBUG
void CExamDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExamDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CExamDoc 명령
void CExamDoc::m_Bright(int height, int width)
{
	int input;
	int temp;
	int i, j;

	if (m_BrightDlg.DoModal() == IDOK)
	{
		input = m_BrightDlg.m_brightvalue;
	}

	for (i = 0; i < height; i++)//0으로 초기화
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[0][i][j] = 0;
		}
	}

	/*
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			int temp = m_InImg[0][i][j] + input;
			temp = temp > 255 ? 255 : temp;
			temp = temp < 0 ? 0 : temp;
			m_OutImg[0][i][j] = (unsigned char)temp;
		}
	}
	*/
	unsigned char LUT[256]; // LUT로 사용할 메모리를 선언 
	// LUT값을 계산 
	for (i = 0; i < 256; i++) {
		int temp = (int)(i + input);
		LUT[i] = temp > 255 ? 255 : temp;
		LUT[i] = temp < 0 ? 0 : temp;
	}
	// LUT를 통하여 영상을 처리
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) m_OutImg[0][i][j] = LUT[m_InImg[0][i][j]];
	} // 곱 연산, if연산 횟수: 256번, 대입연산 width*height 번

}

void CExamDoc::m_TwoImgLoad()
{
	CFileDialog opendlg1(TRUE);
	CFile file;

	if (opendlg1.DoModal() == IDOK)
	{
		file.Open(opendlg1.GetPathName(), CFile::modeRead);
		file.Read(m_InImg[0], sizeof(m_InImg[0]));
		file.Close();
	}

	CFileDialog opendlg2(TRUE);
	if (opendlg2.DoModal() == IDOK)
	{
		file.Open(opendlg2.GetPathName(), CFile::modeRead);
		file.Read(m_InImg[1], sizeof(m_InImg[1]));
		file.Close();
	}
}

void CExamDoc::m_Histo(int height, int width)
{
	int i, j, vmax, vmin;
	for (i = 0; i < 256; i++)
		m_HistoArr[i] = 0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			int gv = (int)m_InImg[0][i][j];
			m_HistoArr[gv]++;
		}
	}
	// 여기서부터 ***까지는 히스토그램을 화면에 표시하기 위한 부분임
	vmin = 1000000; vmax = 0;
	for (i = 0; i < 256; i++)
	{
		if (m_HistoArr[i] <= vmin) vmin = m_HistoArr[i];
		if (m_HistoArr[i] >= vmax) vmax = m_HistoArr[i];
	}
	if (vmax == vmin) return;

	float vd = (float)(vmax - vmin);
	for (i = 0; i < 256; i++)
	{
		m_HistoArr[i] = (int)(((float)m_HistoArr[i] - vmin) * 255.0 / vd);
	}

	// 출력영상의 모든 화소 값을 255로 초기화
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++) m_OutImgTemp[i][j] = 255;

	// 화소의 빈도수를 막대그래프로 만들어 출력영상에 저장
	for (j = 0; j < width; j++)
	{
		for (i = 0; i < m_HistoArr[j]; i++) m_OutImgTemp[255 - i][j] = 0;
	}
	//*** 히스토그램 출력부분 끝
}

void CExamDoc::m_HistoStretch(int height, int width)
{
	int i, j;
	int lowvalue = 255, highvalue = 0;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (m_InImg[0][i][j] < lowvalue)
			{
				lowvalue = m_InImg[0][i][j];
			}
			if (m_InImg[0][i][j] > highvalue)
			{
				highvalue = m_InImg[0][i][j];
			}
		}
	}

	float mult = 255.0f / (float)(highvalue - lowvalue);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImgTemp[i][j] = (unsigned char)((m_InImg[0][i][j] - lowvalue) * mult);
		}
	}
}

void CExamDoc::m_HistoEqual(int height, int width)
{
	int i, j;

	unsigned int* histogram = new unsigned int[256];
	unsigned int* sum_hist = new unsigned int[256];

	for (i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			histogram[m_InImg[0][i][j]]++;
		}
	}

	int sum = 0;
	float scale_factor = 255.0f / (float)(height * width);

	for (i = 0; i < 256; i++)
	{
		sum += histogram[i];
		sum_hist[i] = (int)((sum * scale_factor) + 0.5);
	}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			m_OutImgTemp[i][j] = sum_hist[m_InImg[0][i][j]];

	delete[] histogram;
	delete[] sum_hist;
}

void CExamDoc::m_Zoom(int height, int width, unsigned char InImg[][256])
{
	float input;
	int i, j, temp_height, temp_width;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImgTemp[i][j] = 0;
		}
	}

	if (m_ZoomDlg.DoModal() == IDOK)
	{
		input = m_ZoomDlg.m_zoomsize;
	}

	BYTE* pZoomImg;
	BYTE newValue;

	int new_height = (int)(height * input); //새로운 이미지의 높이 계산 
	int new_width = (int)(width * input); //새로운 이미지의 폭 계산 
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int where, org_where;
	int r, c; //타겟 이미지 좌표 
	float r_orgr, r_orgc; //원 이미지 상의 해당 좌표 (실수값) 
	int i_orgr, i_orgc; //원 이미지 상의 해당 좌표 (정수값) 
	float sr, sc; // 예 1.15-1=0.15 
	float I1, I2, I3, I4;


	//Zoom Image를 위한 동적 메모리 할당 
	pZoomImg = new BYTE[new_height * new_width];

	for (r = 0; r < new_height; r++) //r 출력 수직좌표
		for (c = 0; c < new_width; c++) //c 출력 수평좌표
		{
			r_orgr = r / input; //r_orgr 입력 수직좌표
			r_orgc = c / input; //r_orgc 입력 수평좌표
			i_orgr = int(r_orgr);
			i_orgc = int(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;
			//범위 조사 
			//원이미지의 범위를 벗어나는 경우 0값 할당 
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				where = r * new_width + c;
				pZoomImg[where] = 0;
			}
			//원 이미지의 범위 내에 존재 이중 선형 보간 수행 
			else
			{
				I1 = (float)InImg[i_orgr][i_orgc]; //(org_r,org_c) 
				I2 = (float)InImg[i_orgr][i_orgc + 1]; //(org_r,org_c+1) 
				I3 = (float)InImg[i_orgr + 1][i_orgc + 1]; //(org_r+1,org_c+1) 
				I4 = (float)InImg[i_orgr + 1][i_orgc]; //(org_r+1,org_c) 

				//이중 선형 보간을 통한 새로운 밝기값 계산 
				newValue = (BYTE)(I1 * (1 - sc) * (1 - sr) + I2 * sc * (1 - sr) + I3 * sc * sr
					+ I4 * (1 - sc) * sr);
				where = r * new_width + c;
				pZoomImg[where] = newValue;
			}
		}


	if (input > 1) { temp_height = height; temp_width = width; }  //확대인 경우
	else { temp_height = new_height; temp_width = new_width; } //축소인 경우

	//일단 영상의 일부만 복사하는 것으로 함. 
	for (r = 0; r < temp_height; r++)
		for (c = 0; c < temp_width; c++)
		{
			m_OutImgTemp[r][c] = pZoomImg[r * new_width + c];
		}
	//동적 할당 메모리 해제 
	delete[] pZoomImg;
}

void CExamDoc::m_Rotation(int height, int width, int center_r, int center_c, unsigned char InImg[][256])
{
	float input;
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImgTemp[i][j] = 0;
		}
	}

	if (m_RotationDlg.DoModal() == IDOK)
	{
		input = m_RotationDlg.m_rotationangle;
	}

	BYTE* pRotationImg;
	BYTE newValue;
	int heightm1 = height - 1;//계산의 중복을 피하기 위해 사용 
	int widthm1 = width - 1;//계산의 중복을 피하기 위해 사용 
	int where, org_where;
	int r, c;//타겟 이미지 좌표 
	float r_orgr, r_orgc;//원 이미지 상의 해당 좌표 (실수값) 
	int i_orgr, i_orgc;//원 이미지 상의 해당 좌표 (정수값) 
	float sr, sc;// 예 1.15-1=0.15 
	float I1, I2, I3, I4;
	float cosAngle, sinAngle;
	float rotationAngleRad = (float)(input * 3.14159265 / 180);//angle->radian으로 변환 

	//Rotation Image를 위한 동적 메모리 할당 
	pRotationImg = new BYTE[height * width];

	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
		{
			cosAngle = (float)cos(rotationAngleRad);
			sinAngle = (float)sin(rotationAngleRad);
			//회전전의 원 이미지상의 좌표 구함 
			r_orgr = -sinAngle * (c - center_c) + cosAngle * (r - center_r) + center_r;
			r_orgc = cosAngle * (c - center_c) + sinAngle * (r - center_r) + center_c;
			i_orgr = floor(r_orgr);
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;
			//범위 조사 
			//원이미지의 범위를 벗어나는 경우 0값 할당 
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				where = r * width + c;
				pRotationImg[where] = 0;
			}
			//원 이미지의 범위 내에 존재 이중 선형 보간 수행 
			else
			{
				I1 = (float)InImg[i_orgr][i_orgc];//(org_r,org_c) 
				I2 = (float)InImg[i_orgr][i_orgc + 1];//(org_r,org_c+1) 
				I3 = (float)InImg[i_orgr + 1][i_orgc + 1];//(org_r+1,org_c+1) 
				I4 = (float)InImg[i_orgr + 1][i_orgc];//(org_r+1,org_c) 

				//이중 선형 보간을 통한 새로운 밝기값 계산 
				newValue = (BYTE)(I1 * (1 - sc) * (1 - sr) + I2 * sc * (1 - sr) + I3 * sc * sr
					+ I4 * (1 - sc) * sr);
				where = r * width + c;
				pRotationImg[where] = newValue;
			}
		}
	//결과 이미지로 영상 복사 
	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
		{
			m_OutImgTemp[r][c] = pRotationImg[r * width + c];
		}
	//동적 할당 메모리 해제 
	delete[] pRotationImg;
}

void CExamDoc::m_Affine(int height, int width)
{
	float aa, ab, ac, ad, ae, af;
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImgTemp[i][j] = 0;
		}
	}

	if (m_AffineDlg.DoModal() == IDOK)
	{
		aa = m_AffineDlg.m_affine_a;
		ab = m_AffineDlg.m_affine_b;
		ac = m_AffineDlg.m_affine_c;
		ad = m_AffineDlg.m_affine_d;
		ae = m_AffineDlg.m_affine_e;
		af = m_AffineDlg.m_affine_f;
	}

	BYTE* pAffineImg;
	BYTE newValue;

	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int where, org_where;
	int r, c; //타겟 이미지 좌표 
	float r_orgr, r_orgc; //원 이미지 상의 해당 좌표 (실수값) 
	int i_orgr, i_orgc; //원 이미지 상의 해당 좌표 (정수값) 
	float sr, sc; // 예 1.24-1=0.24 
	float I1, I2, I3, I4;


	//동적 메모리 할당 
	pAffineImg = new BYTE[height * width];

	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
		{
			r_orgr = (ad * c - aa * r + aa * af - ad * ac) / (ab * ad - aa * ae);
			r_orgc = (ae * c - ab * r + ab * af - ae * ac) / (aa * ae - ab * ad);
			i_orgr = int(r_orgr); //예: floor(2.8)=2.0 
			i_orgc = int(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;
			//범위 조사 
			//원이미지의 범위를 벗어나는 경우 0값 할당 
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				where = r * width + c;
				pAffineImg[where] = 0;
			}
			//원 이미지의 범위 내에 존재 이중 선형 보간 수행 
			else
			{
				I1 = (float)m_InImg[0][i_orgr][i_orgc]; //(org_r,org_c) 
				I2 = (float)m_InImg[0][i_orgr][i_orgc + 1]; //(org_r,org_c+1) 
				I3 = (float)m_InImg[0][i_orgr + 1][i_orgc + 1]; //(org_r+1,org_c+1) 
				I4 = (float)m_InImg[0][i_orgr + 1][i_orgc]; //(org_r+1,org_c) 

				//이중 선형 보간을 통한 새로운 밝기값 계산 
				newValue = (BYTE)(I1 * (1 - sc) * (1 - sr) + I2 * sc * (1 - sr) + I3 * sc
					* sr + I4 * (1 - sc) * sr);
				where = r * width + c;
				pAffineImg[where] = newValue;
			}
		}

	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
		{
			m_OutImgTemp[r][c] = pAffineImg[r * width + c];
		}
	//동적 할당 메모리 해제 
	delete[] pAffineImg;

}
void CExamDoc::m_Lowpass(int height, int width, unsigned char InImg[][256])
{
	int masksize;
	int mr, mc, newValue, i, j;

	if (m_MaskDlg.DoModal() == IDOK)
		masksize = m_MaskDlg.m_masksize;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			m_OutImgTemp[i][j] = InImg[i][j];

	for (i = masksize / 2; i < height - masksize / 2; i++)
		for (j = masksize / 2; j < width - masksize / 2; j++)
		{
			newValue = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					newValue +=
					InImg[i + mr - masksize / 2][j + mc - masksize / 2];
			newValue /= (masksize * masksize);

			newValue = newValue < 0 ? 0 : (newValue > 255 ? 255 : newValue);
			m_OutImgTemp[i][j] = (BYTE)newValue;
		}
}
void CExamDoc::m_Median(int height, int width, unsigned char InImg[][256])
{
	int masksize, * temp;
	int mr, mc, i, j, ti, tj;

	if (m_MaskDlg.DoModal() == IDOK)
		masksize = m_MaskDlg.m_masksize;

	temp = new int[masksize * masksize];

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			m_OutImgTemp[i][j] = InImg[i][j];

	for (i = masksize / 2; i < height - masksize / 2; i++)
		for (j = masksize / 2; j < width - masksize / 2; j++)
		{
			int c = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					temp[c++] = InImg[i + mr - masksize / 2][j + mc - masksize / 2];

			for (tj = masksize * masksize - 1; tj >= (masksize * masksize - 1) / 2; tj--)
				//중간값을 찾기 위한 것이므로 버블소팅을 1/2만 수행 
				for (ti = 1; ti <= tj; ti++)
				{
					if (temp[ti] > temp[ti - 1])
					{
						int si = temp[ti];
						temp[ti] = temp[ti - 1];
						temp[ti - 1] = si;
					}
				}

			m_OutImgTemp[i][j] = (BYTE)temp[masksize * masksize / 2];
		}
	delete[] temp;
}

void CExamDoc::m_Max(int height, int width, unsigned char InImg[][256]) {
	int masksize, value, max;
	int mr, mc, i, j, ti, tj;
	if (m_MaskDlg.DoModal() == IDOK) masksize = m_MaskDlg.m_masksize;
	for (i = 0; i < height; i++) for (j = 0; j < width; j++) m_OutImgTemp[i][j] = InImg[i][j];
	for (i = masksize / 2; i < height - masksize / 2; i++) for (j = masksize / 2; j < width - masksize / 2; j++) {
		max = 0; for (mr = 0; mr < masksize; mr++) 
			for (mc = 0; mc < masksize; mc++) {
				value = InImg[i + mr - masksize / 2][j + mc - masksize / 2]; if (value > max) { max = value; }
		} m_OutImgTemp[i][j] = (BYTE)max;
	}
}

void CExamDoc::m_Min(int height, int width, unsigned char InImg[][256]) {
	int masksize, value, min;
	int mr, mc, i, j, ti, tj;
	if (m_MaskDlg.DoModal() == IDOK) masksize = m_MaskDlg.m_masksize;
	for (i = 0; i < height; i++) for (j = 0; j < width; j++) m_OutImgTemp[i][j] = InImg[i][j];
	for (i = masksize / 2; i < height - masksize / 2; i++) for (j = masksize / 2; j < width - masksize / 2; j++) {
		min = 255; for (mr = 0; mr < masksize; mr++)
			for (mc = 0; mc < masksize; mc++) {
				value = InImg[i + mr - masksize / 2][j + mc - masksize / 2]; if (value < min) { min = value; }
	} m_OutImgTemp[i][j] = (BYTE)min;
}
}

void CExamDoc::m_Highpass(int height, int width, unsigned char InImg[][256])
{
	int masksize, Mask[7][7];
	int mr, mc, newValue, i, j;

	if (m_MaskDlg.DoModal() == IDOK)
		masksize = m_MaskDlg.m_masksize;

	for (mr = 0; mr < masksize; mr++)
		for (mc = 0; mc < masksize; mc++)
			Mask[mr][mc] = -1;
	Mask[masksize / 2][masksize / 2] = masksize * masksize;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			m_OutImgTemp[i][j] = InImg[i][j];

	for (i = masksize / 2; i < height - masksize / 2; i++)
		for (j = masksize / 2; j < width - masksize / 2; j++)
		{
			newValue = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					newValue += (Mask[mr][mc] *
						InImg[i + mr - masksize / 2][j + mc - masksize / 2]);

			newValue = newValue < 0 ? 0 : (newValue > 255 ? 255 : newValue);
			m_OutImgTemp[i][j] = (BYTE)newValue;
		}
}

void CExamDoc::m_3filter(int height, int width, unsigned char InImg[][256])
{
	int masksize = 3, Mask[3][3], weight;
	int mr, mc, newValue, i, j;

	if (m_3filterdlg.DoModal() == IDOK)
	{
		Mask[0][0] = m_3filterdlg.m_w1;
		Mask[0][1] = m_3filterdlg.m_w2;
		Mask[0][2] = m_3filterdlg.m_w3;
		Mask[1][0] = m_3filterdlg.m_w4;
		Mask[1][1] = m_3filterdlg.m_w5;
		Mask[1][2] = m_3filterdlg.m_w6;
		Mask[2][0] = m_3filterdlg.m_w7;
		Mask[2][1] = m_3filterdlg.m_w8;
		Mask[2][2] = m_3filterdlg.m_w9;
		weight = m_3filterdlg.m_t;
	}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			m_OutImgTemp[i][j] = InImg[i][j];

	for (i = masksize / 2; i < height - masksize / 2; i++)
		for (j = masksize / 2; j < width - masksize / 2; j++)
		{
			newValue = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					newValue += (Mask[mr][mc] *
						InImg[i + mr - masksize / 2][j + mc - masksize / 2]);
			newValue /= weight;
			newValue = newValue < 0 ? 0 : (newValue > 255 ? 255 : newValue);
			m_OutImgTemp[i][j] = (BYTE)newValue;
		}
}

void CExamDoc::m_Prewitt(int height, int width, unsigned char InImg[][256])
{
	int HMask[3][3] = { {1,0,-1},{1,0,-1},{1,0,-1} };
	int VMask[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1} };

	int mr, mc, newValue1, newValue2, i, j;
	double newValue;

	int masksize = 3;
	for (i = masksize / 2; i < height - masksize / 2; i++)
		for (j = masksize / 2; j < width - masksize / 2; j++)
		{
			newValue1 = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					newValue1 += (HMask[mr][mc] *
						InImg[i + mr - masksize / 2][j + mc - masksize / 2]);

			newValue2 = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					newValue2 += (VMask[mr][mc] *
						InImg[i + mr - masksize / 2][j + mc - masksize / 2]);

			newValue = sqrt((double)(newValue1 * newValue1
				+ newValue2 * newValue2));

			newValue1 = newValue1 < 0 ? 0 : (newValue1 > 255 ? 255 : newValue1);
			m_OutImg[0][i][j] = (BYTE)newValue1;
			newValue2 = newValue2 < 0 ? 0 : (newValue2 > 255 ? 255 : newValue2);
			m_OutImg[1][i][j] = (BYTE)newValue2;
			newValue = newValue < 0 ? 0 : (newValue > 255 ? 255 : newValue);
			m_OutImg[2][i][j] = (BYTE)newValue;
		}
}

void CExamDoc::m_Sobel(int height, int width, unsigned char InImg[][256])
{
	int HMask[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	int VMask[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };

	int mr, mc, newValue1, newValue2, i, j;
	double newValue;

	int masksize = 3;
	for (i = masksize / 2; i < height - masksize / 2; i++)
		for (j = masksize / 2; j < width - masksize / 2; j++)
		{
			newValue1 = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					newValue1 += (HMask[mr][mc] *
						InImg[i + mr - masksize / 2][j + mc - masksize / 2]);

			newValue2 = 0;
			for (mr = 0; mr < masksize; mr++)
				for (mc = 0; mc < masksize; mc++)
					newValue2 += (VMask[mr][mc] *
						InImg[i + mr - masksize / 2][j + mc - masksize / 2]);

			newValue = sqrt((double)(newValue1 * newValue1
				+ newValue2 * newValue2));

			newValue1 = newValue1 < 0 ? 0 : (newValue1 > 255 ? 255 : newValue1);
			m_OutImg[0][i][j] = (BYTE)newValue1;
			newValue2 = newValue2 < 0 ? 0 : (newValue2 > 255 ? 255 : newValue2);
			m_OutImg[1][i][j] = (BYTE)newValue2;
			newValue = newValue < 0 ? 0 : (newValue > 255 ? 255 : newValue);
			m_OutImg[2][i][j] = (BYTE)newValue;
		}
}
