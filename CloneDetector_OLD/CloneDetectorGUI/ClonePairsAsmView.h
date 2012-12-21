#pragma once

#include "..\..\CloneDetector\CloneDetectorLib\CDController.h"
#include "CloneFiles.h"
#include "ClonePairsAsmDoc.h"


// ClonePairsAsmView view

class ClonePairsAsmView : public CRichEditView
{
	DECLARE_DYNCREATE(ClonePairsAsmView)

protected:
	ClonePairsAsmView();           // protected constructor used by dynamic creation
	virtual ~ClonePairsAsmView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	ClonePairsAsmDoc* GetDocument() const;

protected:
	bool    m_isListView;
	bool    m_binit;
	CString m_filename;
	int     m_beginLine;
	int     m_endLine;
	int     m_beginPos;
	int     m_endPos;
	int     m_fileId;

	DECLARE_MESSAGE_MAP()


public:
	int getFileId() {return m_fileId; }
	virtual void OnInitialUpdate();
	void highLightLines(int p_begin, int p_end);
	void initView(const CString & p_filename, const CString & p_str, int p_fileId=-1);
	void initCloneFile( CloneFile & p_cloneFile);
	void SetProtected(void);
	void SetWordWrap(const bool bOn=true, const int iLineWidth=0);
	void SetColour(COLORREF color);

	LRESULT OnCopy(WPARAM, LPARAM);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnViewClose32780();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTokenViewClose();
};

