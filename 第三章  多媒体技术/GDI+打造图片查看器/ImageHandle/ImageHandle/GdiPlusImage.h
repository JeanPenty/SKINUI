#pragma once

typedef struct tagSize
{
	float        cx;
	float        cy;
} _SIZE, *_PSIZE, *_LPSIZE;


class CGdiPlusImage
{
	//变量定义
protected:
	Image *							m_pImage;							//图片对象

	tagSize							m_szZoom;							//缩放变量
	int								m_nRotateAngle;						//旋转角度
	BYTE							m_cbAlphaDepth;						//Alpha数值

	//函数定义
public:
	//构造函数
	CGdiPlusImage();
	//析构函数
	virtual ~CGdiPlusImage();
	
	//状态函数
public:
	//是否加载
	bool IsNull();
	//获取宽度
	INT GetWidth();
	//获取高度
	INT GetHeight();

	//管理函数
public:
	//销毁图片
	bool DestroyImage();
	//加载图片
	bool LoadImage(LPCTSTR pszFileName);

	//功能函数
public:
	//设置旋转
	void SetRotation(int nAngle);
	//设置缩放
	void SetScale(float cx,float cy);
	//设置Alpha
	void SetAlpha(BYTE cbAlphaDepth);
	//保存图像
	bool Save(LPCTSTR pszFileName,LPCTSTR format=TEXT("image/png"));
	//获取解码器
	int GetEncoderClsid(LPCTSTR format, CLSID* pClsid);

	//绘画函数
public:
	//绘画图像
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos);
};
