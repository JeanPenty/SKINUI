#include "StdAfx.h"
#include "ImageEx.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

//构造函数
CImageEx::CImageEx()
{
	ZeroMemory(m_strImageName, sizeof(m_strImageName) );
}

//析构函数
CImageEx::~CImageEx()
{
}

//加载图片
bool CImageEx::LoadImage( HINSTANCE hInstance, LPCTSTR pszResourceName )
{
	if (IsNull()==false) return false;

	//变量定义
	HRSRC hResource=NULL;
	HGLOBAL hGlobal=NULL;
	IStream * pIStream=NULL;

	//加载位图
	try
	{
		//查找资源
		hResource=FindResource(hInstance,pszResourceName,TEXT("IMAGE"));
		if (hResource==NULL) throw 0;

		//加载资源
		hGlobal=LoadResource(hInstance,hResource);
		if (hGlobal==NULL) throw 0;

		//读取资源
		LPVOID pImageBuffer=LockResource(hGlobal);
		DWORD dwImageSize=SizeofResource(hInstance,hResource);

		//创建数据
		CreateStreamOnHGlobal(NULL,TRUE,&pIStream);
		if (pIStream==NULL) throw 0;

		//写入数据
		pIStream->Write(pImageBuffer,dwImageSize,NULL);

		//创建位图
		CImage::Load(pIStream);

		//释放资源
		if (pIStream!=NULL) pIStream->Release();

		//是否资源
		if (hGlobal!=NULL)
		{
			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}

		return true;
	}
	catch (...)
	{
		//释放资源
		if (pIStream!=NULL) pIStream->Release();

		//是否资源
		if (hGlobal!=NULL)
		{
			UnlockResource(hGlobal);
			FreeResource(hGlobal);
		}

		return false;
	}

	return true;
}

//加载图片
bool CImageEx::LoadImage( void * pDate ,DWORD dwSize )
{
	if (IsNull()==false) return false;
	if ( pDate == NULL ) return false;

	//变量定义
	IStream * pIStream=NULL;

	//加载位图
	try
	{
		//创建数据
		CreateStreamOnHGlobal(NULL,TRUE,&pIStream);
		if (pIStream==NULL) throw 0;

		//写入数据
		pIStream->Write(pDate,dwSize,NULL);

		//创建位图
		if ( CImage::Load(pIStream) == S_FALSE ) throw 0;

		//释放资源
		if (pIStream!=NULL) pIStream->Release();

		return true;
	}
	catch (...)
	{
		//释放资源
		if (pIStream!=NULL) pIStream->Release();

		return false;
	}

	return true;
}

//创建区域
bool CImageEx::CreateImageRegion(CRgn & ImageRgn, COLORREF crTransColor)
{
	//创建区域
	CreateImageRegion(ImageRgn,0,0,GetWidth(),GetHeight(),crTransColor);

	return true;
}

//创建区域
bool CImageEx::CreateImageRegion(CRgn & ImageRgn, INT nXSrcPos, INT nYSrcPos, INT nSrcWidth, INT nSrcHeight, COLORREF crTransColor)
{
	//判断状态
	ASSERT(IsNull()==false);
	if (IsNull()==true) return false;

	//参数调整
	INT nImageWidht=GetWidth();
	INT nImageHeight=GetHeight();
	if ((nXSrcPos+nSrcWidth)>nImageWidht) nSrcWidth=nImageWidht-nXSrcPos;
	if ((nYSrcPos+nSrcHeight)>nImageHeight) nSrcHeight=nImageHeight-nYSrcPos;

	//创建对象
	CDC MemDC;
	MemDC.CreateCompatibleDC(NULL);
	ImageRgn.CreateRectRgn(0,0,0,0);

	//创建位图
	CImage ImageConsult;
	ImageConsult.Create(nSrcWidth,nSrcHeight,32);

	//调整位图
	BITMAP ImageInfo;
	GetObject(ImageConsult,sizeof(ImageInfo),&ImageInfo);
	while ((ImageInfo.bmWidthBytes%4)!=0) ImageInfo.bmWidthBytes++;

	//绘画位图
	BitBlt(ImageConsult.GetDC(),0,0,nSrcWidth,nSrcHeight,nXSrcPos,nYSrcPos);
	ImageConsult.ReleaseDC();

	//获取属性
	BYTE cbRTranColor=GetRValue(crTransColor);
	BYTE cbGTranColor=GetGValue(crTransColor);
	BYTE cbBTranColor=GetBValue(crTransColor);
	BYTE * pcbImageBitIndex=(BYTE *)ImageInfo.bmBits+(ImageInfo.bmHeight-1)*ImageInfo.bmWidthBytes;

	//创建区域
	for (INT nYPos=0;nYPos<ImageInfo.bmHeight;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageInfo.bmWidth;nXPos++)
		{
			//变量定义
			INT nXStartPos=nXPos;

			//透明判断
			do
			{
				COLORREF crImageColor=*(((LONG *)pcbImageBitIndex)+nXPos);
				if ((cbRTranColor==GetRValue(crImageColor))&&(cbGTranColor==GetGValue(crImageColor))&&(cbBTranColor==GetBValue(crImageColor))) break;
			} while ((++nXPos)<ImageInfo.bmWidth);

			//创建区域
			if ((nXPos-nXStartPos)>0)
			{
				//创建区域
				CRgn RgnUnite;
				RgnUnite.CreateRectRgn(nXStartPos,nYPos,nXPos,nYPos+1);

				//合并区域
				CombineRgn(ImageRgn,RgnUnite,ImageRgn,RGN_OR);
			}
		}

		//设置位置
		pcbImageBitIndex-=ImageInfo.bmWidthBytes;
	}

	return true;
}

//平铺绘画
bool CImageEx::DrawImageTile(CDC * pDC, CRect & rcDestRect)
{
	//平铺绘画
	DrawImageTile(pDC,rcDestRect.left,rcDestRect.top,rcDestRect.Width(),rcDestRect.Height());

	return true;
}

//平铺绘画
bool CImageEx::DrawImageTile(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight)
{
	//效验状态
	ASSERT(IsNull()==false);
	if (IsNull()==true) return false;

	//无效区域
	CRect rcDirty;
	pDC->GetClipBox(&rcDirty);

	//变量定义
	INT nImageWidth=GetWidth();
	INT nImageHeight=GetHeight();

	//平铺绘画
	for (INT nXDrawPos=0;nXDrawPos<nWidth;nXDrawPos+=nImageWidth)
	{
		for (INT nYDrawPos=0;nYDrawPos<nHeight;nYDrawPos+=nImageHeight)
		{
			//计算位置
			INT nDrawWidth=__min(nWidth-nXDrawPos,nImageWidth);
			INT nDrawHeight=__min(nHeight-nYDrawPos,nImageHeight);

			//绘画图形
			bool bIntersect=IsRectIntersect(rcDirty,nXDrawPos+nXPos,nYDrawPos+nYPos,nDrawWidth,nDrawHeight);
			if (bIntersect==true) BitBlt(pDC->m_hDC,nXDrawPos+nXPos,nYDrawPos+nYPos,nDrawWidth,nDrawHeight,0,0);
		}
	}

	return true;
}

//一般绘画
BOOL CImageEx::BitBlt( HDC hDestDC, int xDest, int yDest, DWORD dwROP /*= SRCCOPY*/ )
{
	return BitBlt(hDestDC, xDest, yDest, GetWidth(), GetHeight(), 0, 0);
}

//一般绘画
BOOL CImageEx::BitBlt( HDC hDestDC, const POINT& pointDest, DWORD dwROP /*= SRCCOPY*/ )
{
	return BitBlt(hDestDC, pointDest.x, pointDest.y, GetWidth(), GetHeight(), 0, 0);
}

//一般绘画
BOOL CImageEx::BitBlt( HDC hDestDC, const RECT& rectDest, const POINT& pointSrc, DWORD dwROP /*= SRCCOPY*/ )
{
	return BitBlt(hDestDC, rectDest.left, rectDest.top, rectDest.right - rectDest.left, rectDest.bottom - rectDest.top, pointSrc.x, pointSrc.y);
}

BOOL CImageEx::BitBlt( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, DWORD dwROP /*= SRCCOPY */ )
{
	return CImage::BitBlt(hDestDC, xDest, yDest, nDestWidth, nDestHeight, xSrc, ySrc, dwROP);
}

//透明绘画
bool CImageEx::TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor)
{
	//绘画图片
	TransDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTransColor);

	return true;
}

//透明绘画
bool CImageEx::TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor)
{
	//无效区域
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//绘画判断
	if (IsNull()==true) return false;
	if (IsRectIntersect(rcDirty,xDest,yDest,cxDest,cyDest)==false) return true;

	//位置调整
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//颜色保存
	COLORREF crTextColor=pDestDC->SetTextColor(RGB(0,0,0));
	COLORREF crBackColor=pDestDC->SetBkColor(RGB(255,255,255));

	//掩码对象
	CDC MaskDC;
	CBitmap MaskImage;
	MaskDC.CreateCompatibleDC(pDestDC);
	MaskImage.CreateBitmap(ImageRender.cxRender,ImageRender.cyRender,1,1,NULL);

	//位图 DC
	CDC * pDCImage=CDC::FromHandle(GetDC());
	COLORREF crImageBkColor=pDCImage->SetBkColor(crTransColor);

	//构造掩码
	MaskDC.SelectObject(&MaskImage);
	MaskDC.BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);

	//绘画对象
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		&MaskDC,0,0,SRCAND);
	pDestDC->BitBlt(ImageRender.nXScreen,ImageRender.nYScreen,ImageRender.cxRender,ImageRender.cyRender,
		pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCINVERT);

	//颜色还原
	pDestDC->SetBkColor(crBackColor);
	pDestDC->SetTextColor(crTextColor);

	//释放资源
	ReleaseDC();
	MaskDC.DeleteDC();
	MaskImage.DeleteObject();

	return true;
}

//混合绘画
bool CImageEx::TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor)
{
	//创建缓冲
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//创建位图
		CImageEx ImageStretch;
		ImageStretch.Create(cxDest,cyDest,32);

		//拉伸位图
		HDC hStretchDC=ImageStretch.GetDC();
		StretchBlt(hStretchDC,0,0,cxDest,cyDest,xSrc,ySrc,cxSrc,cySrc,SRCCOPY);
		ImageStretch.TransDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,0,0,crTransColor);

		//释放资源
		ImageStretch.ReleaseDC();
	}
	else
	{
		//普通调用
		TransDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,crTransColor);
	}

	return true;
}

//混合绘画
bool CImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth)
{
	//透明绘画
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,cbAlphaDepth);

	return true;
}

//混合绘画
bool CImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth)
{
	//无效区域
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//绘画判断
	if (IsNull()==true) return false;
	if (IsRectIntersect(rcDirty,xDest,yDest,cxDest,cyDest)==false) return true;

	//位置调整
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//创建位图
	CImage ImageResult;
	CImage ImageSource;
	ImageResult.Create(ImageRender.cxRender,ImageRender.cyRender,32);
	ImageSource.Create(ImageRender.cxRender,ImageRender.cyRender,32);

	//绘画位图
	CDC * pDCImage=CDC::FromHandle(GetDC());
	CDC * pDCResult=CDC::FromHandle(ImageResult.GetDC());
	CDC * pDCSource=CDC::FromHandle(ImageSource.GetDC());
	pDCSource->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCCOPY);
	pDCResult->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDestDC,ImageRender.nXScreen,ImageRender.nYScreen,SRCCOPY);

	//获取属性
	FLOAT fAlpha=(FLOAT)(cbAlphaDepth/255.0);
	INT nPitchResult=ImageResult.GetPitch();
	INT nPitchSource=ImageSource.GetPitch();

	//获取数据
	LPBYTE cbBitResult=(LPBYTE)ImageResult.GetBits();
	LPBYTE cbBitSource=(LPBYTE)ImageSource.GetBits();

	//创建区域
	for (INT nYPos=0;nYPos<ImageRender.cyRender;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageRender.cxRender;nXPos++)
		{
			//获取颜色
			COLORREF * pcrResult=(COLORREF *)(cbBitResult+nYPos*nPitchResult+nXPos*4);
			COLORREF * pcrSource=(COLORREF *)(cbBitSource+nYPos*nPitchSource+nXPos*4);

			//结果颜色
			BYTE cbResultR=GetRValue(*pcrResult);
			BYTE cbResultG=GetGValue(*pcrResult);
			BYTE cbResultB=GetBValue(*pcrResult);

			//原图颜色
			BYTE cbSourceR=GetRValue(*pcrSource);
			BYTE cbSourceG=GetGValue(*pcrSource);
			BYTE cbSourceB=GetBValue(*pcrSource);

			//颜色混合
			cbResultR=(BYTE)(cbSourceR*fAlpha+cbResultR*(1.0-fAlpha));
			cbResultG=(BYTE)(cbSourceG*fAlpha+cbResultG*(1.0-fAlpha));
			cbResultB=(BYTE)(cbSourceB*fAlpha+cbResultB*(1.0-fAlpha));

			//颜色混合
			*pcrResult=RGB(cbResultR,cbResultG,cbResultB);
		}
	}

	//绘画界面
	ImageResult.BitBlt(pDestDC->m_hDC,ImageRender.nXScreen,ImageRender.nYScreen);

	//释放对象
	ReleaseDC();
	ImageSource.ReleaseDC();
	ImageResult.ReleaseDC();

	return true;
}

//混合绘画
bool CImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth)
{
	//创建缓冲
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//创建位图
		CImageEx ImageStretch;
		ImageStretch.Create(cxDest,cyDest,32);

		//拉伸位图
		CImageDC ImageDC(ImageStretch);
		StretchBlt(ImageDC,0,0,cxDest,cyDest,xSrc,ySrc,cxSrc,cySrc,SRCCOPY);

		//混合绘画
		ImageStretch.AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,0,0,cbAlphaDepth);
	}
	else
	{
		//普通调用
		AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,cbAlphaDepth);
	}

	return true;
}

//混合绘画
bool CImageEx::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//透明绘画
	BlendDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTransColor,cbAlphaDepth);

	return true;
}

//混合绘画
bool CImageEx::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//无效区域
	CRect rcDirty;
	pDestDC->GetClipBox(&rcDirty);

	//绘画判断
	if (IsNull()==true) return false;
	if (IsRectIntersect(rcDirty,xDest,yDest,cxDest,cyDest)==false) return true;

	//位置调整
	tagImageRender ImageRender;
	GetDrawImageArea(xDest,yDest,cxDest,cyDest,xSrc,ySrc,rcDirty,ImageRender);

	//创建位图
	CImage ImageResult;
	CImage ImageSource;
	ImageResult.Create(ImageRender.cxRender,ImageRender.cyRender,32);
	ImageSource.Create(ImageRender.cxRender,ImageRender.cyRender,32);

	//绘画位图
	CDC * pDCImage=CDC::FromHandle(GetDC());
	CDC * pDCResult=CDC::FromHandle(ImageResult.GetDC());
	CDC * pDCSource=CDC::FromHandle(ImageSource.GetDC());
	pDCSource->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDCImage,ImageRender.nXImage,ImageRender.nYImage,SRCCOPY);
	pDCResult->BitBlt(0,0,ImageRender.cxRender,ImageRender.cyRender,pDestDC,ImageRender.nXScreen,ImageRender.nYScreen,SRCCOPY);

	//获取属性
	FLOAT fAlpha=(FLOAT)(cbAlphaDepth/255.0);
	INT nPitchResult=ImageResult.GetPitch();
	INT nPitchSource=ImageSource.GetPitch();

	//获取数据
	LPBYTE cbBitResult=(LPBYTE)ImageResult.GetBits();
	LPBYTE cbBitSource=(LPBYTE)ImageSource.GetBits();

	//创建区域
	for (INT nYPos=0;nYPos<ImageRender.cyRender;nYPos++)
	{
		for (INT nXPos=0;nXPos<ImageRender.cxRender;nXPos++)
		{
			//获取颜色
			COLORREF * pcrResult=(COLORREF *)(cbBitResult+nYPos*nPitchResult+nXPos*4);
			COLORREF * pcrSource=(COLORREF *)(cbBitSource+nYPos*nPitchSource+nXPos*4);

			//混合处理
			if (*pcrSource!=crTransColor)
			{
				//结果颜色
				BYTE cbResultR=GetRValue(*pcrResult);
				BYTE cbResultG=GetGValue(*pcrResult);
				BYTE cbResultB=GetBValue(*pcrResult);

				//原图颜色
				BYTE cbSourceR=GetRValue(*pcrSource);
				BYTE cbSourceG=GetGValue(*pcrSource);
				BYTE cbSourceB=GetBValue(*pcrSource);

				//颜色混合
				cbResultR=(BYTE)(cbSourceR*fAlpha+cbResultR*(1.0-fAlpha));
				cbResultG=(BYTE)(cbSourceG*fAlpha+cbResultG*(1.0-fAlpha));
				cbResultB=(BYTE)(cbSourceB*fAlpha+cbResultB*(1.0-fAlpha));

				//颜色混合
				*pcrResult=RGB(cbResultR,cbResultG,cbResultB);
			}
		}
	}

	//绘画界面
	ImageResult.BitBlt(pDestDC->m_hDC,ImageRender.nXScreen,ImageRender.nYScreen);

	//释放对象
	ReleaseDC();
	ImageSource.ReleaseDC();
	ImageResult.ReleaseDC();

	return true;
}

//混合绘画
bool CImageEx::BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor, BYTE cbAlphaDepth)
{
	//创建缓冲
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//创建位图
		CImageEx ImageStretch;
		ImageStretch.Create(cxDest,cyDest,32);

		//拉伸位图
		HDC hStretchDC=ImageStretch.GetDC();
		StretchBlt(hStretchDC,0,0,cxDest,cyDest,xSrc,ySrc,cxSrc,cySrc,SRCCOPY);
		ImageStretch.BlendDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,0,0,crTransColor,cbAlphaDepth);

		//释放资源
		ImageStretch.ReleaseDC();
	}
	else
	{
		//普通调用
		BlendDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,crTransColor,cbAlphaDepth);
	}

	return true;
}

//矩形检查
bool CImageEx::IsRectIntersect(const CRect & rcRect, INT nXPos, INT nYPos, INT nWidth, INT nHeight)
{
	//范围检测
	if ((nXPos>rcRect.right)||(nYPos>rcRect.bottom)) return false;
	if (((nXPos+nWidth)<rcRect.left)||((nYPos+nHeight)<rcRect.top)) return false;

	return true;
}

//区域计算
bool CImageEx::GetDrawImageArea(INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, CRect & rcDirty, tagImageRender & ImageRender)
{
	//相交矩形
	CRect rcIntersect;
	rcIntersect.top=__max(yDest,rcDirty.top);
	rcIntersect.left=__max(xDest,rcDirty.left);
	rcIntersect.right=__min((xDest+cxDest),rcDirty.right);
	rcIntersect.bottom=__min((yDest+cyDest),rcDirty.bottom);

	//渲染位置
	ImageRender.nYScreen=rcIntersect.top;
	ImageRender.nXScreen=rcIntersect.left;

	//渲染大小
	ImageRender.cxRender=rcIntersect.Width();
	ImageRender.cyRender=rcIntersect.Height();

	//图形索引
	ImageRender.nXImage=xSrc+ImageRender.nXScreen-xDest;
	ImageRender.nYImage=ySrc+ImageRender.nYScreen-yDest;

	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
