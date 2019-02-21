#ifndef IMAGE_HEAD_FILE
#define IMAGE_HEAD_FILE

#pragma once

#include "SkinUI.h"

//////////////////////////////////////////////////////////////////////////////////

//图片对象
class SKINUI_CLASS CImageEx
{
	//变量定义
protected:
	Bitmap *						m_pImage;							//图片对象
	TCHAR							m_strImageName[MAX_PATH];			//图片名称
	RECT							m_rcNinePart;
	HBITMAP							m_hBitmap;

	//函数定义
public:
	//构造函数
	CImageEx();
	//析构函数
	virtual ~CImageEx();

	//状态函数
public:
	//是否加载
	bool IsNull();
	//获取宽度
	INT GetWidth();
	//获取高度
	INT GetHeight();

	//设置函数
public:
	void SetNinePart(CONST LPRECT lprcNinePart);

	HBITMAP ImageToBitmap(/*HDC hDC*/);

	//管理函数
public:
	//销毁图片
	bool DestroyImage();
	//加载图片
	bool LoadImage(LPCTSTR pszFileName);
	//加载图片
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName,LPCTSTR pszResourceType=TEXT("IMAGE"));

	//绘画函数
public:
	//绘画图像
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos);
	//绘画图像
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos, INT nDestWidth, INT nDestHeight);
	//绘画图像
	bool DrawImage(CDC * pDC, RECT &rc);
	//绘画图像
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc);
	//绘画图像
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight);

	//透明绘画
public:
	//混合绘画
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth);
	//混合绘画
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth);
	//混合绘画
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth);

	//区域绘制
public:
	//绘画图像
	bool Draw( CDC * pDC, INT x, INT y, INT cx, INT cy,INT nLeft,INT nTop,INT nRight,INT nBottom );
	//绘画图像
	bool Draw( CDC * pDC, const RECT& rectDest, const RECT& rectSrc );
	//绘画图像
	bool Draw( CDC * pDC, const RECT& rectDest );
};

//////////////////////////////////////////////////////////////////////////////////

#endif