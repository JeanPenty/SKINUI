#pragma once


// CListBoxEx

class CListBoxEx : public CListBox
{
	DECLARE_DYNAMIC(CListBoxEx)

protected:
	INT						m_nItemHeight;			//节点高度
	
public:
	CListBoxEx();
	virtual ~CListBoxEx();

protected:
	DECLARE_MESSAGE_MAP()

public:
	//设置节点高度
	void SetItemHeight(int nItemHeight);
	
	//传统继承
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);
};


