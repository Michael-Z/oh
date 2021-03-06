//*****************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//*****************************************************************************
//
// Purpose:
//
//*****************************************************************************

#ifndef INC_SIZERBAR_H
#define INC_SIZERBAR_H

#include "WinMgr.h"

class CSizerBar : public CStatic {
public:
	CSizerBar();
	virtual ~CSizerBar();
	BOOL Create(DWORD dwStyle,				 // window styles
		CWnd* pParentWnd,						 // parent window
		CWinMgr& wmgr,							 // window manger
		UINT nID,								 // ID of sizer bar
		const RECT& rc = CRect(0,0,0,0)); // initial rectangle

protected:
	CWinMgr* m_pWinMgr;			// window manager
	BOOL		m_bHorz;				// horizontal bar; else vertical
	BOOL		m_bDragging;		// in drag mode?
	CRect		m_rcBar;				// bar rect in screen coords
	CPoint	m_ptOriginal;		// original mouse pos at start of drag
	CPoint	m_ptPrevious;		// previous mouse pos while dragging
	CRect		m_rcConstrain;		// constrain mouse to this rect
	HWND		m_hwndPrevFocus;	// to restore after dragging

	// override this if you insist on painting differently
	virtual void OnDrawBar(CDC& dc, CRect& rc);

	// helpers
	void CancelDrag();					 // cancel drag mode
	void DrawBar();						 // draw sizer bar
	BOOL IsHorizontal();					 // is bar horizontal?
	void NotifyMoved(CPoint ptDelta); // send move notification to parent
	CPoint Constrain(CPoint pt);		 // constrain pt to m_rcConstrain
	CPoint Rectify(CPoint pt) {		 // make point vertical/horizontal
		return IsHorizontal() ? CPoint(0, pt.y) : CPoint(pt.x, 0);
	}

	// MFC overrides & message handlers
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT msg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnCancelMode(); // may not be necessary

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CSizerBar)
};

#endif //INC_SIZERBAR_H