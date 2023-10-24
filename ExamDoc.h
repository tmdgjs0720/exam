
// ExamDoc.h: CExamDoc 클래스의 인터페이스
//
#include "CBright.h"
#include "CTrans.h"
#include "CZoom.h"
#include "CRotation.h"
#include "CAffine.h"
#include "CMaske.h"
#include "C3filter.h"

#pragma once


class CExamDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CExamDoc() noexcept;
	DECLARE_DYNCREATE(CExamDoc)

// 특성입니다.
public:
	unsigned char m_InImg[4][256][256]; //입력영상 저장
	unsigned char m_OutImg[4][256][256]; //
	unsigned int m_SizeX; //영상의 수평방향 화소수
	unsigned int m_SizeY; //영상의 수직방향 화소수
	unsigned int m_NoInImg; //입력영상의 개수
	unsigned int m_NoOutImg;//출력영상의 개수
	CBright m_BrightDlg;
	void m_Bright(int height, int width);
	void m_TwoImgLoad();
	int m_HistoArr[256];  //각 레벨의 히스토그램(빈도)를 저장
	unsigned char m_OutImgTemp[256][256]; //처리영상 임시저장
	void m_Histo(int height, int width);
	void m_HistoStretch(int height, int width);
	void m_HistoEqual(int height, int width);
	CTrans m_TransDlg;
	void m_Zoom(int height, int width, unsigned char InImg[][256]);
	CZoom m_ZoomDlg;
	void m_Rotation(int height, int width, int center_r, int center_c, unsigned char InImg[][256]);
	CRotation m_RotationDlg;
	CAffine m_AffineDlg;
	void m_Affine(int height, int width);
	void m_Lowpass(int height, int width, unsigned char InImg[][256]);
	CMaske m_MaskDlg;
	void m_Median(int height, int width, unsigned char InImg[][256]);
	void m_Max(int height, int width, unsigned char InImg[][256]);
	void m_Min(int height, int width, unsigned char InImg[][256]);
	void m_Highpass(int height, int width, unsigned char InImg[][256]);
	void m_3filter(int height, int width, unsigned char InImg[][256]);
	C3filter m_3filterdlg;
	void m_Prewitt(int height, int width, unsigned char InImg[][256]);
	void m_Sobel(int height, int width, unsigned char InImg[][256]);
	void m_Robinson3(int height, int width, unsigned char InImg[][256]);


	// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CExamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
