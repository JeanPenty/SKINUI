#ifndef IMAGE_HEAD_FILE
#define IMAGE_HEAD_FILE

#pragma once
#include <atlimage.h>
//////////////////////////////////////////////////////////////////////////////////
//�ṹ����

//��Ⱦ��Ϣ
struct tagImageRender
{
	INT								nXImage;							//ͼƬλ��
	INT								nYImage;							//ͼƬλ��
	INT								nXScreen;							//��Ⱦλ��
	INT								nYScreen;							//��Ⱦλ��
	INT								cxRender;							//��Ⱦ�ߴ�
	INT								cyRender;							//��Ⱦ�ߴ�
};

//////////////////////////////////////////////////////////////////////////////////

//λͼ����
class CImageEx : public CImage
{
	//��������
protected:
	TCHAR							m_strImageName[MAX_PATH];			//ͼƬ����

	//��������
public:
	//���캯��
	CImageEx();
	//��������
	virtual ~CImageEx();

	//��������
public:
	//����ͼƬ
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName);
	//����ͼƬ
	bool LoadImage(void * pDate ,DWORD dwSize);

	//������
public:
	//��������
	bool CreateImageRegion(CRgn & ImageRgn, COLORREF crTransColor);
	//��������
	bool CreateImageRegion(CRgn & ImageRgn, INT nXSrcPos, INT nYSrcPos, INT nSrcWidth, INT nSrcHeight, COLORREF crTransColor);

	//һ��滭
public:
	//һ��滭
	BOOL BitBlt( HDC hDestDC, int xDest, int yDest, DWORD dwROP = SRCCOPY );
	//һ��滭
	BOOL BitBlt( HDC hDestDC, const POINT& pointDest, DWORD dwROP = SRCCOPY );
	//һ��滭
	BOOL BitBlt( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, DWORD dwROP = SRCCOPY );
	//һ��滭
	BOOL BitBlt( HDC hDestDC, const RECT& rectDest, const POINT& pointSrc, DWORD dwROP = SRCCOPY );

	//�滭ͼƬ
public:
	//ƽ�̻滭
	bool DrawImageTile(CDC * pDC, CRect & rcDestRect);
	//ƽ�̻滭
	bool DrawImageTile(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight);

	//͸���滭
public:
	//͸���滭
	bool TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor);
	//͸���滭
	bool TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor);
	//͸���滭
	bool TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor);

	//͸���滭
public:
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth);

	//��ϻ滭
public:
	//��ϻ滭
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor, BYTE cbAlphaDepth);
	//��ϻ滭
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor, BYTE cbAlphaDepth);
	//��ϻ滭
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor, BYTE cbAlphaDepth);

	//��������
public:
	//���μ��
	bool IsRectIntersect(const CRect & rcRect, INT nXPos, INT nYPos, INT nWidth, INT nHeight);
	//�������
	bool GetDrawImageArea(INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, CRect & rcDirty, tagImageRender & ImageRender);
};

//////////////////////////////////////////////////////////////////////////////////

#endif