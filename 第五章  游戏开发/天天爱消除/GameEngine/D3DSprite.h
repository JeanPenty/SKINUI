#ifndef D3D_SPRITE_HEAD_FILE
#define D3D_SPRITE_HEAD_FILE

#pragma once

#include "D3DDevice.h"
#include "GameEngineHead.h"

//////////////////////////////////////////////////////////////////////////////////

//类说明
class CD3DSprite;

//数组说明
typedef CArray<CD3DSprite *,CD3DSprite *>		CD3DSpritePtrArray;					//精灵数组

//////////////////////////////////////////////////////////////////////////////////

//精灵对象
class GAME_ENGINE_CLASS CD3DSprite
{
	//旋转信息
protected:
	FLOAT							m_fAngle;							//旋转变量
	FLOAT							m_fRotationX;						//旋转变量
	FLOAT							m_fRotationY;						//旋转变量

	//缩放信息
protected:
	FLOAT							m_fScalingCenterX;					//缩放变量
	FLOAT							m_fScalingCenterY;					//缩放变量
	FLOAT							m_fScalingX;						//缩放变量
	FLOAT							m_fScalingY;						//缩放变量

	//图片信息
public:
	CSize							m_ImageSize;						//图片大小
	CSize							m_MemorySize;						//内存大小

	//接口变量
protected:
	ID3DXSprite	*					m_pISprite;							//精灵接口
	IDirect3DTexture9 *				m_pITexture;						//精灵接口

	//静态变量
protected:
 	static CD3DSpritePtrArray		m_D3DSpritePtrArray;				//精灵数组

	//函数定义
public:
	//构造函数
	CD3DSprite();
	//析构函数
	virtual ~CD3DSprite();

	//获取对象
public:
	//精灵对象
	ID3DXSprite * GetSprite() { return m_pISprite; }
	//纹理对象
	IDirect3DTexture9 * GetTexture() { return m_pITexture; }

	//图片信息
public:
	//加载判断
	bool IsNull();
	//精灵宽度
	INT GetWidth() { return m_ImageSize.cx; }
	//精灵高度
	INT GetHeight() { return m_ImageSize.cy; }

	//控制函数
public:
	//设置旋转
	VOID SetRotation(FLOAT fRotationX, FLOAT fRotationY, FLOAT fAngle);
	//设置缩放
	VOID SetScaling(FLOAT fScalingCenterX,FLOAT fScalingCenterY,FLOAT fScalingX, FLOAT fScalingY);

	//精灵管理
public:
	//销毁精灵
	bool Destory();
	//创建精灵
	bool CreateImage(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//功能函数
public:
	//加载精灵
	bool LoadImage(CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, DWORD dwColorKey);
	//加载精灵
	bool LoadImage(CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName);

	//绘画函数
public:
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight);

	//绘画函数
public:
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, D3DCOLOR Color);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, D3DCOLOR Color);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, D3DCOLOR Color);

	//绘画函数
public:
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, BYTE cbAlpha);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, BYTE cbAlpha);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, BYTE cbAlpha);

	//内部函数
protected:
	//获取资源
	bool GetResourceInfo(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, tagResourceInfo & ResourceInfo);

	//静态函数
public:
	//释放资源
	static VOID OnDeviceLost(CD3DDevice * pD3DDevice);
	//重置资源
	static VOID OnDeviceReset(CD3DDevice * pD3DDevice);
};

//////////////////////////////////////////////////////////////////////////////////

#endif