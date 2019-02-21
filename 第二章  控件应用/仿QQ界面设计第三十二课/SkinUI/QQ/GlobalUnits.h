#pragma once
#include "SkinManager.h"
#include "ChatDlg.h"

class CGlobalUnits
{
public:
	TCHAR							m_szDefaultSkin[MAX_PATH];		//ͼ��·��
	bool							m_bLeftDrawExtrude;				//�������
	vector<CSkinManager*>			m_WindowArray;
	vector<CChatDlg*>				m_ChatArray;

public:
	CGlobalUnits(void);
	~CGlobalUnits(void);

public:
	static CGlobalUnits*GetInstance();
};

#define GlobalUnits		CGlobalUnits::GetInstance()