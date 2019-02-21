#ifndef IMAGE_HEAD_FILE
#define IMAGE_HEAD_FILE

#pragma once

#include "SkinUI.h"

//////////////////////////////////////////////////////////////////////////////////

//ͼƬ����
class SKINUI_CLASS CImageEx
{
	//��������
protected:
	Bitmap *						m_pImage;							//ͼƬ����
	TCHAR							m_strImageName[MAX_PATH];			//ͼƬ����
	RECT							m_rcNinePart;
	HBITMAP							m_hBitmap;

	//��������
public:
	//���캯��
	CImageEx();
	//��������
	virtual ~CImageEx();

	//״̬����
public:
	//�Ƿ����
	bool IsNull();
	//��ȡ���
	INT GetWidth();
	//��ȡ�߶�
	INT GetHeight();

	//���ú���
public:
	void SetNinePart(CONST LPRECT lprcNinePart);

	HBITMAP ImageToBitmap(/*HDC hDC*/);

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
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos, INT nDestWidth, INT nDestHeight);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, RECT &rc);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight);

	//͸���滭
public:
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth);

	//�������
public:
	//�滭ͼ��
	bool Draw( CDC * pDC, INT x, INT y, INT cx, INT cy,INT nLeft,INT nTop,INT nRight,INT nBottom );
	//�滭ͼ��
	bool Draw( CDC * pDC, const RECT& rectDest, const RECT& rectSrc );
	//�滭ͼ��
	bool Draw( CDC * pDC, const RECT& rectDest );
};

//////////////////////////////////////////////////////////////////////////////////

#endif