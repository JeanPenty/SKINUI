#include "StdAfx.h"
#include "GdiPlusImage.h"

//构造函数
CGdiPlusImage::CGdiPlusImage(void)
{
	//设置变量
	m_pImage=NULL;
	m_szZoom.cx = m_szZoom.cy = 1.0f;
	m_nRotateAngle = 0;
	m_cbAlphaDepth = 255;
}

//析构函数
CGdiPlusImage::~CGdiPlusImage(void)
{
	//销毁图片
	DestroyImage(); 
}

//是否加载
bool CGdiPlusImage::IsNull()
{
	//加载判断
	if (m_pImage==NULL) return true;
	if (m_pImage->GetLastStatus()!=Ok) return true;

	return false;
}

//获取宽度
INT CGdiPlusImage::GetWidth()
{
	//加载判断
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//获取宽度
	return m_pImage->GetWidth();
}

//获取高度
INT CGdiPlusImage::GetHeight()
{
	//加载判断
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//获取高度
	return m_pImage->GetHeight();
}

//销毁图片
bool CGdiPlusImage::DestroyImage()
{
	//删除对象
	if (m_pImage!=NULL) SafeDelete(m_pImage);

	return true;
}

//加载图片
bool CGdiPlusImage::LoadImage(LPCTSTR pszFileName)
{
	//加载判断
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//加载文件
	CT2CW strFileName(pszFileName);
	m_pImage=Image::FromFile((LPCWSTR)strFileName);

	//错误判断
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok)) 
	{
		DestroyImage();
		return false;
	}

	return true;
}

//绘画图像
bool CGdiPlusImage::DrawImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	GraphicsContainer Containter = graphics.BeginContainer();
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	//获取属性
	INT nImageWidth=m_pImage->GetWidth();
	INT nImageHeight=m_pImage->GetHeight();

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=0;//(REAL)nXPos;
	rcDrawRect.Y=0;//(REAL)nYPos;
	rcDrawRect.Width=(REAL)nImageWidth;
	rcDrawRect.Height=(REAL)nImageHeight;

	Matrix matrix;

	CPoint pt((nXPos+nImageWidth/2), (nYPos+nImageHeight/2));
	PointF ptBase((float)pt.x,(float)pt.y);

	//矩阵变换要注意顺序，先平移在缩放后旋转
	matrix.Translate((REAL)nXPos,(REAL)nYPos,MatrixOrderAppend);
	
	//缩放
	if ( m_szZoom.cx != 1.0f || m_szZoom.cy != 1.0f )
	{
		ptBase.X += m_szZoom.cx;
		ptBase.Y += m_szZoom.cy;

		matrix.Translate(-ptBase.X,-ptBase.Y,MatrixOrderAppend);
		matrix.Scale(m_szZoom.cx,m_szZoom.cy,MatrixOrderAppend);
		matrix.Translate(ptBase.X,ptBase.Y,MatrixOrderAppend);
	}

	//旋转
	if (m_nRotateAngle)
	{
		matrix.RotateAt((REAL)m_nRotateAngle,ptBase,MatrixOrderAppend);
	}

	graphics.SetTransform(&matrix);

	//透明矩阵
	ColorMatrix Matrix=
	{
		1.0f,0.0f,0.0f,0.0f,0.0f, 
		0.0f,1.0f,0.0f,0.0f,0.0f, 
		0.0f,0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,m_cbAlphaDepth/255.0f,0.0f, 
		0.0f,0.0f,0.0f,0.0f,1.0f
	};

	//设置属性
	ImageAttributes Attributes; 
	Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap); 

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel,&Attributes);

	graphics.ResetTransform();

	graphics.EndContainer(Containter);

	return true;
}

void CGdiPlusImage::SetRotation( int nAngle)
{
	m_nRotateAngle = nAngle;
}

void CGdiPlusImage::SetScale(float cx,float cy)
{
	m_szZoom.cx = cx;
	m_szZoom.cy = cy;
}

void CGdiPlusImage::SetAlpha( BYTE cbAlphaDepth )
{
	if ( cbAlphaDepth < 0 ) m_cbAlphaDepth = 0;
	if ( cbAlphaDepth > 255 ) m_cbAlphaDepth = 255;
	
	m_cbAlphaDepth = cbAlphaDepth;
}

int CGdiPlusImage::GetEncoderClsid(LPCTSTR format, CLSID* pClsid)
{
	UINT  num = 0;          
	UINT  size = 0;        

	ImageCodecInfo* pImageCodecInfo = NULL;   

	GetImageEncodersSize(&num, &size);   
	if(size == 0)   
		return -1;  

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));   
	if(pImageCodecInfo == NULL)   
		return -1;  

	GetImageEncoders(num, size, pImageCodecInfo);   

	for(UINT j = 0; j < num; ++j)   
	{   
		if( StrCmp(pImageCodecInfo[j].MimeType, format) == 0 )   
		{   
			*pClsid = pImageCodecInfo[j].Clsid;   
			free(pImageCodecInfo);   
			return j; 
		}       
	}   

	free(pImageCodecInfo);   
	return -1;  
}

bool CGdiPlusImage::Save(LPCTSTR pszFileName,LPCTSTR format)
{
	//加载文件
	CT2CW strFileName(pszFileName);

	//图像保存
	CLSID Clsid;
	GetEncoderClsid(format, &Clsid);
	if( m_pImage->Save((LPCWSTR)strFileName, &Clsid) == Ok )
		return true;

	return false;
}

