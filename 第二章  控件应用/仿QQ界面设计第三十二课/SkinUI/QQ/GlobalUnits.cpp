#include "StdAfx.h"
#include "GlobalUnits.h"

CGlobalUnits::CGlobalUnits(void)
{
	m_szDefaultSkin[0]=0;
	m_bLeftDrawExtrude = false;
}

CGlobalUnits::~CGlobalUnits(void)
{
	for (int i=0;i<m_ChatArray.size();i++)
	{
		CChatDlg *pChatDlg = m_ChatArray.at(i);
		pChatDlg->DestroyWindow();

		SafeDelete(pChatDlg);
	}
}

CGlobalUnits* CGlobalUnits::GetInstance()
{
	static CGlobalUnits _Instance;

	return &_Instance;
}
