
// ExamView.h: CExamView 클래스의 인터페이스
//

#pragma once


class CExamView : public CView
{
protected: // serialization에서만 만들어집니다.
	CExamView() noexcept;
	DECLARE_DYNCREATE(CExamView)

// 특성입니다.
public:
	CExamDoc* GetDocument() const;

// 작업입니다.
public:
	PBITMAPINFO pbmi;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CExamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReverse();
	afx_msg void OnBright();
	afx_msg void OnFrmAdd();
	afx_msg void OnFrmSub();
	afx_msg void OnHisto();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistoEqual();
	afx_msg void OnTrans();
	afx_msg void OnZoom();
	afx_msg void OnRotation();
	afx_msg void OnMirX();
	afx_msg void OnMirY();
	afx_msg void OnMirO();
	afx_msg void OnMirD();
	afx_msg void OnMirRd();
	afx_msg void OnCompound();
	afx_msg void OnAffine();
	afx_msg void OnLowpass();
	afx_msg void OnMedian();
	afx_msg void OnMax();
	afx_msg void OnMin();
	afx_msg void OnMaxOri();
	afx_msg void OnOriMin();
	afx_msg void OnMaxMin();
	afx_msg void OnHighpass();
	afx_msg void On3filter();
	afx_msg void OnPrewitt();
	afx_msg void OnSobel();
};

#ifndef _DEBUG  // ExamView.cpp의 디버그 버전
inline CExamDoc* CExamView::GetDocument() const
   { return reinterpret_cast<CExamDoc*>(m_pDocument); }
#endif

