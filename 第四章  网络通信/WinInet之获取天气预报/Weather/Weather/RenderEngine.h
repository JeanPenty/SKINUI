#ifndef RENDERENGINE_HEAD_FILE
#define RENDERENGINE_HEAD_FILE

#pragma once

class CRenderEngine
{
	//变量定义
public:
	static short 					m_cxSpacing;	//字符间隔
	static short 					m_cwBlank;		//空格键的宽度

public:
	CRenderEngine(void);
	~CRenderEngine(void);

	//功能函数
public:
	//获取文字尺寸大小
	static SIZE GetDrawSize(HDC hDC,LPTSTR lpszText,UINT uFormat,bool& bHaveOffsety,short& yOffset);
	//对齐字符
	static short CalcOffsety(HDC hDC);
	//偏移量
	static bool IsYOffset(UINT uChar);
	//是否中文
	static bool IsDoubleByteChar(UINT uChar);
};

#endif