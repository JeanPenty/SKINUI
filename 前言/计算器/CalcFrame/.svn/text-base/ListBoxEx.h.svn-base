#pragma once


// CListBoxEx
#define  WM_RECTIFY			WM_USER+1000

class CListBoxEx : public CListBox
{
	DECLARE_DYNAMIC(CListBoxEx)

public:
	CListBoxEx();
	virtual ~CListBoxEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};