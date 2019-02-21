#include "StdAfx.h"
#include "ImageEx.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

//���캯��
CImageEx::CImageEx()
{
	ZeroMemory(m_strImageName, sizeof(m_strImageName) );
}

//��������
CImageEx::~CImageEx()
{
}

//����ͼƬ
bool CImageEx::LoadImage( HINSTANCE hInstance, LPCTSTR pszResourceName )
{
	if (IsNull()==false) return false;

	//��������
	HRSRC hResource=NULL;
	HGLOBAL hGlobal=NULL;
	IStream * pIStream=NULL;

	//����λͼ
	try
	{
		//������Դ
		hResource=FindResource(hInstance,pszResourceName,TEXT("IMAGE"));
		if (hResource==NULL) throw 0;

		//������Դ
		hGlobal=LoadResource(hInstance,hResource);
		if (hGlobal==NULL) throw 0;

		//��ȡ��Դ
		LPVOID pImageBuffer=LockResource(hGlobal);
		DWORD dwImageSize=SizeofResource(hInstance,hResource);

		//��������
		CreateStreamOnHGlobal(NULL,TRUE,&pIStream);
		if (pIStream==NULL) throw 0;

		//д������
		pIStream->Write(pImageBuffer,dwImageSize,NULL);

		//����λͼ
		CImage::Load(pIStream);

		//�ͷ���Դ
		if (pIStream!=NULL) pIStream->Release();

		//�Ƿ���Դ
		if (hGlobal!=NULL)
		{
			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}

		return true;
	}
	catch (...)
	{
		//�ͷ���Դ
		if (pIStream!=NULL) pIStream->Release();

		//�Ƿ���Դ
		if (hGlobal!=NULL)
		{
			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}

		return false;
	}

	return true;
}

//����ͼƬ
bool CImageEx::LoadImage( void * pDate ,DWORD dwSize )
{
	if (IsNull()==false) return false;
	if ( pDate == NULL ) return false;

	//��������
	IStream * pIStream=NULL;

	//����λͼ
	try
	{
		//��������
		CreateStreamOnHGlobal(NULL,TRUE,&pIStream);
		if (pIStream==NULL) throw 0;

		//д������
		pIStream->Write(pDate,dwSize,NULL);

		//����λͼ
		if ( CImage::Load(pIStream) == S_FALSE ) throw 0;

		//�ͷ���Դ
		if (pIStream!=NULL) pIStream->Release();

		return true;
	}
	catch (...)
	{
		//�ͷ���Դ
		if (pIStream!=NULL) pIStream->Release();

		return false;
	}

	return true;
}

//��������
bool CImageEx::CreateImageRegion(CRgn & ImageRgn, COLORREF crTransColor)
{
	//��������
	CreateImageRegion(ImageRgn,0,0,GetWidth(),GetHeight(),crTransColor);

	return true;
}

//��������
bool CImageEx::CreateImageRegion(CRgn & ImageRgn, INT nXSrcPos, INT nYSrcPos, INT nSrcWidth, INT nSrcHeight, COLORREF crTransColor)
{
	//�ж�״̬
	ASSERT(IsNull()==false);
	if (IsNull()==true) return false;

	//��������
	INT nImageWidht=GetWidth();
	INT nImageHeight=GetHeight();
	if ((nXSrcPos+nSrcWidth)>nImageWidht) nSrcWidth=nImageWidht-nXSrcPos;
	if ((nYSrcPos+nSrcHeight)>nImageHeight) nSrcHeight=nImageHeight-nYSrcPos;

	//��������
	CDC MemDC;
	MemDC.CreateCompatibleDC(NULL);
	ImageRgn.CreateRectRgn(0,0,0,0);

	//����λͼ
	CImage ImageConsult;
	ImageConsult.Create(nSrcWidth,nSrcHeight,32);

	//����λͼ
	BITMAP ImageInfo;
	GetObject(ImageConsult,sizeof(ImageInfo),&ImageInfo);
	while ((ImageInfo.bmWidthBytes%4)!=0) ImageInfo.bmWidthBytes++;

	//�滭λͼ
	BitBlt(ImageConsult.GetDC(),0,0,nSrcWidth,nSrcHeight,nXSrcPos,nYSrcPos);
	ImageConsult.ReleaseDC();

	//��ȡ����
	BYTE cbRTranColor=GetRValue(crTransColor);
	BYTE cbGTranColor=GetGValue(crTransColor);
	BYTE cbBTranColor=GetBValue(crTransColor);
	BYTE * pcbImageBitIndex=(BYTE *)ImageInfo.bmBits+(ImageInfo.bmHeight-1)*ImageInfo.bmWidthBytes;

	//��������
	for (INT nYPos=0;nYPos<ImageInfo.bmHeight;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageInfo.bmWidth;nXPos++)
		{
			//��������
			INT nXStartPos=nXPos;

			//͸���ж�
			do
			{
				COLORREF crImageColor=*(((LONG *)pcbImageBitIndex)+nXPos);
				if ((cbRTranColor==GetRValue(crImageColor))&&(cbGTranColor==GetGValue(crImageColor))&&(cbBTranColor==GetBValue(crImageColor))) break;
			} while ((++nXPos)<ImageInfo.bmWidth);

			//��������
			if ((nXPos-nXStartPos)>0)
			{
				//��������
				CRgn RgnUnite;
				RgnUnite.CreateRectRgn(nXStartPos,nYPos,nXPos,nYPos+1);

				//�ϲ�����
				CombineRgn(ImageRgn,RgnUnite,ImageRgn,RGN_OR);
			}
		}

		//����λ��
		pcbImageBitIndex-=ImageInfo.bmWidthBytes;
	}

	return true;
}

//ƽ�̻滭
bool CImageEx::DrawImageTile(CDC * pDC, CRect & rcDestRect)
{
	//ƽ�̻滭
	DrawImageTile(pDC,rcDestRect.left,rcDestRect.top,rcDestRect.Width(),rcDestRect.Height());

	return true;
}

//ƽ�̻滭
bool CImageEx::DrawImageTile(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight)
{
	//Ч��״̬
	ASSERT(IsNull()==false);
	if (IsNull()==true) return false;

	//��Ч����
	CRect rcDirty;
	pDC->GetClipBox(&rcDirty);

	//��������
	INT nImageWidth=GetWidth();
	INT nImageHeight=GetHeight();

	//ƽ�̻滭
	for (INT nXDrawPos=0;nXDrawPos<nWidth;nXDrawPos+=nImageWidth)
	{
		for (INT nYDrawPos=0;nYDrawPos<nHeight;nYDrawPos+=nImageHeight)
		{
			//����λ��
			INT nDrawWidth=__min(nWidth-nXDrawPos,nImageWidth);
			INT nDrawHeight=__min(nHeight-nYDrawPos,nImageHeight);

			//�滭ͼ��
			bool bIntersect=IsRectIntersect(rcDirty,nXDrawPos+nXPos,nYDrawPos+nYPos,nDrawWidth,nDrawHeight);
			if (bIntersect==true) BitBlt(pDC->m_hDC,nXDrawPos+nXPos,nYDrawPos+nYPos,nDrawWidth,nDrawHeight,0,0);
		}
	}

	return true;
}

//һ��滭
BOOL CImageEx::BitBlt( HDC hDestDC, int xDest, int yDest, DWORD dwROP /*= SRCCOPY*/ )
{
	return BitBlt(hDestDC, xDest, yDest, GetWidth(), GetHeight(), 0, 0);
}

//һ��滭
BOOL CImageEx::BitBlt( HDC hDestDC, const POINT& pointDest, DWORD dwROP /*= SRCCOPY*/ )
{
	return BitBlt(hDestDC, pointDest.x, pointDest.y, GetWidth(), GetHeight(), 0, 0);
}

//һ��滭
BOOL CImageEx::BitBlt( HDC hDestDC, const RECT& rectDest, const POINT& pointSrc, DWORD dwROP /*= SRCCOPY*/ )
{
	return BitBlt(hDestDC, rectDest.left, rectDest.top, rectDest.right - rectDest.left, rectDest.bottom - rectDest.top, pointSrc.x, pointSrc.y);
}

BOOL CImageEx::BitBlt( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, DWORD dwROP /*= SRCCOPY */ )
{
	return CImage::BitBlt(hDestDC, xDest, yDest, nDestWidth, nDestHeight, xSrc, ySrc, dwROP);
}

//͸���滭
bool CImageEx::TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor)
{
	//�滭ͼƬ
	TransDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTransColor);

	return true;
}

//͸���滭
bool CImageEx::TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor)
{
	//��Ч����
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//�滭�ж�
	if (IsNull()==true) return false;
	if (IsRectIntersect(rcDirty,xDest,yDest,cxDest,cyDest)==false) return true;

	//λ�õ���
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//��ɫ����
	COLORREF crTextColor=pDestDC->SetTextColor(RGB(0,0,0));
	COLORREF crBackColor=pDestDC->SetBkColor(RGB(255,255,255));

	//�������
	CDC MaskDC;
	CBitmap MaskImage;
	MaskDC.CreateCompatibleDC(pDestDC);
	MaskImage.CreateBitmap(ImageRender.cxRender,ImageRender.cyRender,1,1,NULL);

	//λͼ DC
	CDC * pDCImage=CDC::FromHandle(GetDC());
	COLORREF crImageBkColor=pDCImage->SetBkColor(crTransColor);

	//��������
	MaskDC.SelectObject(&MaskImage);
	MaskDC.BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);

	//�滭����
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		&MaskDC,0,0,SRCAND);
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);

	//��ɫ��ԭ
	pDestDC->SetBkColor(crBackColor);
	pDestDC->SetTextColor(crTextColor);

	//�ͷ���Դ
	ReleaseDC();
	MaskDC.DeleteDC();
	MaskImage.DeleteObject();

	return true;
}

//��ϻ滭
bool CImageEx::TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor)
{
	//��������
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//����λͼ
		CImageEx ImageStretch;
		ImageStretch.Create(cxDest,cyDest,32);

		//����λͼ
		HDC hStretchDC=ImageStretch.GetDC();
		StretchBlt(hStretchDC,0,0,cxDest,cyDest,xSrc,ySrc,cxSrc,cySrc,SRCCOPY);
		ImageStretch.TransDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,0,0,crTransColor);

		//�ͷ���Դ
		ImageStretch.ReleaseDC();
	}
	else
	{
		//��ͨ����
		TransDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,crTransColor);
	}

	return true;
}

//��ϻ滭
bool CImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth)
{
	//͸���滭
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,cbAlphaDepth);

	return true;
}

//��ϻ滭
bool CImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth)
{
	//��Ч����
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//�滭�ж�
	if (IsNull()==true) return false;
	if (IsRectIntersect(rcDirty,xDest,yDest,cxDest,cyDest)==false) return true;

	//λ�õ���
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//����λͼ
	CImage ImageResult;
	CImage ImageSource;
	ImageResult.Create(ImageRender.cxRender,ImageRender.cyRender,32);
	ImageSource.Create(ImageRender.cxRender,ImageRender.cyRender,32);

	//�滭λͼ
	CDC * pDCImage=CDC::FromHandle(GetDC());
	CDC * pDCResult=CDC::FromHandle(ImageResult.GetDC());
	CDC * pDCSource=CDC::FromHandle(ImageSource.GetDC());
	pDCSource->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCCOPY);
	pDCResult->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDestDC,ImageRender.nXScreen,ImageRender.nYScreen,SRCCOPY);

	//��ȡ����
	FLOAT fAlpha=(FLOAT)(cbAlphaDepth/255.0);
	INT nPitchResult=ImageResult.GetPitch();
	INT nPitchSource=ImageSource.GetPitch();

	//��ȡ����
	LPBYTE cbBitResult=(LPBYTE)ImageResult.GetBits();
	LPBYTE cbBitSource=(LPBYTE)ImageSource.GetBits();

	//��������
	for (INT nYPos=0;nYPos<ImageRender.cyRender;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageRender.cxRender;nXPos++)
		{
			//��ȡ��ɫ
			COLORREF * pcrResult=(COLORREF *)(cbBitResult+nYPos*nPitchResult+nXPos*4);
			COLORREF * pcrSource=(COLORREF *)(cbBitSource+nYPos*nPitchSource+nXPos*4);

			//�����ɫ
			BYTE cbResultR=GetRValue(*pcrResult);
			BYTE cbResultG=GetGValue(*pcrResult);
			BYTE cbResultB=GetBValue(*pcrResult);

			//ԭͼ��ɫ
			BYTE cbSourceR=GetRValue(*pcrSource);
			BYTE cbSourceG=GetGValue(*pcrSource);
			BYTE cbSourceB=GetBValue(*pcrSource);

			//��ɫ���
			cbResultR=(BYTE)(cbSourceR*fAlpha+cbResultR*(1.0-fAlpha));
			cbResultG=(BYTE)(cbSourceG*fAlpha+cbResultG*(1.0-fAlpha));
			cbResultB=(BYTE)(cbSourceB*fAlpha+cbResultB*(1.0-fAlpha));

			//��ɫ���
			*pcrResult=RGB(cbResultR,cbResultG,cbResultB);
		}
	}

	//�滭����
	ImageResult.BitBlt(pDestDC->m_hDC,ImageRender.nXScreen,ImageRender.nYScreen);

	//�ͷŶ���
	ReleaseDC();
	ImageSource.ReleaseDC();
	ImageResult.ReleaseDC();

	return true;
}

//��ϻ滭
bool CImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth)
{
	//��������
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//����λͼ
		CImageEx ImageStretch;
		ImageStretch.Create(cxDest,cyDest,32);

		//����λͼ
		CImageDC ImageDC(ImageStretch);
		StretchBlt(ImageDC,0,0,cxDest,cyDest,xSrc,ySrc,cxSrc,cySrc,SRCCOPY);

		//��ϻ滭
		ImageStretch.AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,0,0,cbAlphaDepth);
	}
	else
	{
		//��ͨ����
		AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,cbAlphaDepth);
	}

	return true;
}

//��ϻ滭
bool CImageEx::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//͸���滭
	BlendDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTransColor,cbAlphaDepth);

	return true;
}

//��ϻ滭
bool CImageEx::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//��Ч����
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//�滭�ж�
	if (IsNull()==true) return false;
	if (IsRectIntersect(rcDirty,xDest,yDest,cxDest,cyDest)==false) return true;

	//λ�õ���
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//����λͼ
	CImage ImageResult;
	CImage ImageSource;
	ImageResult.Create(ImageRender.cxRender,ImageRender.cyRender,32);
	ImageSource.Create(ImageRender.cxRender,ImageRender.cyRender,32);

	//�滭λͼ
	CDC * pDCImage=CDC::FromHandle(GetDC());
	CDC * pDCResult=CDC::FromHandle(ImageResult.GetDC());
	CDC * pDCSource=CDC::FromHandle(ImageSource.GetDC());
	pDCSource->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCCOPY);
	pDCResult->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDestDC,ImageRender.nXScreen,ImageRender.nYScreen,SRCCOPY);

	//��ȡ����
	FLOAT fAlpha=(FLOAT)(cbAlphaDepth/255.0);
	INT nPitchResult=ImageResult.GetPitch();
	INT nPitchSource=ImageSource.GetPitch();

	//��ȡ����
	LPBYTE cbBitResult=(LPBYTE)ImageResult.GetBits();
	LPBYTE cbBitSource=(LPBYTE)ImageSource.GetBits();

	//��������
	for (INT nYPos=0;nYPos<ImageRender.cyRender;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageRender.cxRender;nXPos++)
		{
			//��ȡ��ɫ
			COLORREF * pcrResult=(COLORREF *)(cbBitResult+nYPos*nPitchResult+nXPos*4);
			COLORREF * pcrSource=(COLORREF *)(cbBitSource+nYPos*nPitchSource+nXPos*4);

			//��ϴ���
			if (*pcrSource!=crTransColor)
			{
				//�����ɫ
				BYTE cbResultR=GetRValue(*pcrResult);
				BYTE cbResultG=GetGValue(*pcrResult);
				BYTE cbResultB=GetBValue(*pcrResult);

				//ԭͼ��ɫ
				BYTE cbSourceR=GetRValue(*pcrSource);
				BYTE cbSourceG=GetGValue(*pcrSource);
				BYTE cbSourceB=GetBValue(*pcrSource);

				//��ɫ���
				cbResultR=(BYTE)(cbSourceR*fAlpha+cbResultR*(1.0-fAlpha));
				cbResultG=(BYTE)(cbSourceG*fAlpha+cbResultG*(1.0-fAlpha));
				cbResultB=(BYTE)(cbSourceB*fAlpha+cbResultB*(1.0-fAlpha));

				//��ɫ���
				*pcrResult=RGB(cbResultR,cbResultG,cbResultB);
			}
		}
	}

	//�滭����
	ImageResult.BitBlt(pDestDC->m_hDC,ImageRender.nXScreen,ImageRender.nYScreen);

	//�ͷŶ���
	ReleaseDC();
	ImageSource.ReleaseDC();
	ImageResult.ReleaseDC();

	return true;
}

//��ϻ滭
bool CImageEx::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//��������
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//����λͼ
		CImageEx ImageStretch;
		ImageStretch.Create(cxDest,cyDest,32);

		//����λͼ
		HDC hStretchDC=ImageStretch.GetDC();
		StretchBlt(hStretchDC,0,0,cxDest,cyDest,xSrc,ySrc,cxSrc,cySrc,SRCCOPY);
		ImageStretch.BlendDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,0,0,crTransColor,cbAlphaDepth);

		//�ͷ���Դ
		ImageStretch.ReleaseDC();
	}
	else
	{
		//��ͨ����
		BlendDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,crTransColor,cbAlphaDepth);
	}

	return true;
}

//���μ��
bool CImageEx::IsRectIntersect(const CRect & rcRect, INT nXPos, INT nYPos, INT nWidth, INT nHeight)
{
	//��Χ���
	if ((nXPos>rcRect.right)||(nYPos>rcRect.bottom)) return false;
	if (((nXPos+nWidth)<rcRect.left)||((nYPos+nHeight)<rcRect.top)) return false;

	return true;
}

//�������
bool CImageEx::GetDrawImageArea(INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, CRect & rcDirty, tagImageRender & ImageRender)
{
	//�ཻ����
	CRect rcIntersect;
	rcIntersect.top=__max(yDest,rcDirty.top);
	rcIntersect.left=__max(xDest,rcDirty.left);
	rcIntersect.right=__min((xDest+cxDest),rcDirty.right);
	rcIntersect.bottom=__min((yDest+cyDest),rcDirty.bottom);

	//��Ⱦλ��
	ImageRender.nYScreen=rcIntersect.top;
	ImageRender.nXScreen=rcIntersect.left;

	//��Ⱦ��С
	ImageRender.cxRender=rcIntersect.Width();
	ImageRender.cyRender=rcIntersect.Height();

	//ͼ������
	ImageRender.nXImage=xSrc+ImageRender.nXScreen-xDest;
	ImageRender.nYImage=ySrc+ImageRender.nYScreen-yDest;

	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
