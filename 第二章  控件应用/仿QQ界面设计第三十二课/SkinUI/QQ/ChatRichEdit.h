#pragma once
#include "ScrollBarEx.h"

// CChatRichEdit

class CChatRichEdit : public CSkinRichEdit
{
	DECLARE_DYNAMIC(CChatRichEdit)

public:
	CChatRichEdit();
	virtual ~CChatRichEdit();

public:
	//�����ַ�
	bool TranslateInsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

protected:
	DECLARE_MESSAGE_MAP()
};


