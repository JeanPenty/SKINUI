#include "StdAfx.h"
#include "RenderEngine.h"

short CRenderEngine::m_cxSpacing=2;
short CRenderEngine::m_cwBlank=7;


CRenderEngine::CRenderEngine(void)
{
}

CRenderEngine::~CRenderEngine(void)
{
}

SIZE CRenderEngine::GetDrawSize(HDC hDc,LPTSTR lpszText,UINT uFormat,bool& bHaveOffsety,short& yOffset)
{
	SIZE size={0,0};
	if(lpszText==NULL)
		return size;

	long slen=_tcslen(lpszText);
	if(slen==0)
		return size;

	MAT2 mat2 = {{0,1}, {0,0}, {0,0}, {0,1}};
	GLYPHMETRICS gm={0};
	UINT nChar;
	for(int n=0; n<slen; n++)
	{
		nChar=*(lpszText+n);
		//·ÇÓ¢ÎÄ
		if(nChar >= 0xa0)
		{
			nChar = (((nChar<<8)&0xff00) | (*(lpszText+ ++n) & 0x00ff)); 
		}
		if(GetGlyphOutline(hDc,nChar,GGO_GRAY8_BITMAP,&gm,0,NULL,&mat2)!=GDI_ERROR)
		{
			size.cx+=gm.gmBlackBoxX+m_cxSpacing;
			size.cy=max(size.cy,gm.gmBlackBoxY);
		}
		if(nChar == _T(' '))
		{
			size.cx+=m_cwBlank;
		}
		else
		{
			switch(nChar)
			{
			case _T('j'):
			case _T('J'):
			case _T('y'):
			case _T('g'):
				bHaveOffsety=true;
				break;
			}
		}
	}

	if(bHaveOffsety)
	{
		yOffset=CalcOffsety(hDc);
		size.cy+=yOffset;
	}
	else
		yOffset=0;

	return size;
}

short CRenderEngine::CalcOffsety(HDC hDc)
{
	MAT2 mat2 = {{0,1}, {0,0}, {0,0}, {0,1}};
	GLYPHMETRICS gm={0};
	if(GetGlyphOutline(hDc,_T('j'),GGO_GRAY8_BITMAP,&gm,0,NULL,&mat2)!=GDI_ERROR)
	{
		short y=gm.gmBlackBoxY;
		if(GetGlyphOutline(hDc,_T('b'),GGO_GRAY8_BITMAP,&gm,0,NULL,&mat2)!=GDI_ERROR)
		{
			return (y-gm.gmBlackBoxY);
		}
	}

	return 0;
}

bool CRenderEngine::IsYOffset(UINT uChar)
{
	switch(uChar)
	{
	case _T('j'):
	case _T('J'):
	case _T('y'):
	case _T('g'):
		return false;
	}

	return true;
}

bool CRenderEngine::IsDoubleByteChar(UINT uChar)
{
	return uChar >= 0xa0;
}