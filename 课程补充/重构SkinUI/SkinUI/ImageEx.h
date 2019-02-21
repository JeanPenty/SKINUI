#ifndef IMAGE_HEAD_FILE
#define IMAGE_HEAD_FILE

#pragma once

#include "SkinUI.h"

//////////////////////////////////////////////////////////////////////////////////

struct IMAGEPARAMENT 
{          
	int     nWidth;   
	int     nHeight;   
	int     nBitCount;   
	int     nBytesPerLine;   
	int     nBytesPerPixel;   
	int     nNumColors;   
	int     nSize;   
};   

//ͼƬ����
class SKINUI_CLASS CImageEx: public CImage
{
	//��������
protected:
	RECT							m_rcNinePart;
	CImage							m_ImageClone;
	BYTE							m_cbAlpha;

	//��������
public:
	//���캯��
	CImageEx();
	//��������
	virtual ~CImageEx();

	//���ú���
public:
	//�Ź����ͼ
	void SetNinePart(CONST LPRECT lprcNinePart);
	//Alpha����
	bool SetAlphaBit();
	//תHBITMAP
	HBITMAP ImageToBitmap();
	//�Ҷȴ���
	bool SetGray();
	//
	inline void SetAlpha(BYTE cbAlpha){ m_cbAlpha = cbAlpha; }
	void SetRotation(int nAngle);

	//������
public:
	//����ͼƬ
	bool DestroyImage();
	//����ͼƬ
	bool LoadImage(LPCTSTR pszFileName);
	//����ͼƬ
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName,LPCTSTR pszResourceType=TEXT("IMAGE"));

	//�滭����
public:
	//�滭ͼ��
	BOOL DrawImage(CDC * pDC, INT nXPos, INT nYPos);
	//�滭ͼ��
	BOOL DrawImage(CDC * pDC, INT nXPos, INT nYPos, INT nDestWidth, INT nDestHeight);
	//�滭ͼ��
	BOOL DrawImage(CDC * pDC, RECT &rc);
	//�滭ͼ��
	BOOL DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc);
	//�滭ͼ��
	BOOL DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight);

	//�������
public:
	//�滭ͼ��
	bool Draw( CDC * pDC, INT x, INT y, INT cx, INT cy,INT nLeft,INT nTop,INT nRight,INT nBottom );
	//�滭ͼ��
	bool Draw( CDC * pDC, const RECT& rectDest, const RECT& rectSrc );
	//�滭ͼ��
	bool Draw( CDC * pDC, const RECT& rectDest );
	//�滭ͼ��
	bool DrawFrame( CDC * pDC, const RECT& rectDest );

	//�������
public:
	//
	bool DrawExtrude(CDC*pDC,const RECT& rectDest,bool bLeft=false,int nPixel=1);

protected:
	//
	void  GetImageParament(CImage *pImg,IMAGEPARAMENT *ppImgParam); 
	int   InImage(CImage *pImg,int x,int y);   
	void  SetRectValue(CImage *pImg,int x,int y,int Dx,int Dy,BYTE *buf);   
	void  GetAllPalette(CImage *pImg,RGBQUAD *ColorTab);   
	void  SetAllPalette(CImage *pImg,RGBQUAD *ColorTab);  
	int   PaletteType(RGBQUAD   *ColorTab); 
	int   ImageType();   
	void RotateCimage(CImage *Imgn, int nAngle);  
};

//////////////////////////////////////////////////////////////////////////////////

#endif