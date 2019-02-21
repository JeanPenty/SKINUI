#ifndef D3D_TEXTURE_HEAD_FILE
#define D3D_TEXTURE_HEAD_FILE

#pragma once

#include "D3DDevice.h"
#include "GameEngineHead.h"

//////////////////////////////////////////////////////////////////////////////////

//颜色定义
#define COLOR_INVALID				D3DCOLOR_XRGB(0,0,0)				//无效颜色
#define COLOR_TRANSPARENT			D3DCOLOR_XRGB(255,0,255)			//透明颜色

//////////////////////////////////////////////////////////////////////////////////
//像素结构
struct tagD3DXCOLORVertex
{
	FLOAT							x,y,z,h;								//坐标
	DWORD							color;								//颜色
};

//顶点结构
struct tagD3DTextureVertex
{
	D3DXVECTOR3						Position;							//顶点坐标
	FLOAT							tu,tv;								//纹理顶点
};

//顶点格式
#define D3DFVF_TEXTURE				(D3DFVF_XYZ|D3DFVF_TEX1)			//顶点格式
#define D3DFVF_COLOR				(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)			//顶点格式

//////////////////////////////////////////////////////////////////////////////////

//纹理对象
class GAME_ENGINE_CLASS CD3DTexture
{
	//图片信息
public:
	CSize							m_ImageSize;						//图片大小
	CSize							m_MemorySize;						//内存大小

	//接口变量
protected:
	IDirect3DTexture9 *				m_pITexture;						//纹理接口
	IDirect3DVertexBuffer9 *		m_pIVertexBuffer;					//顶点缓冲

	//函数定义
public:
	//构造函数
	CD3DTexture();
	//析构函数
	virtual ~CD3DTexture();

	//获取对象
public:
	//纹理对象
	IDirect3DTexture9 * GetTexture() { return m_pITexture; }
	//顶点对象
	IDirect3DVertexBuffer9 * GetVertexBuffer() { return m_pIVertexBuffer; }

	//图片信息
public:
	//加载判断
	bool IsNull();
	//纹理宽度
	INT GetWidth() { return m_ImageSize.cx; }
	//纹理高度
	INT GetHeight() { return m_ImageSize.cy; }

	//纹理管理
public:
	//销毁纹理
	bool Destory();
	//创建纹理
	bool CreateImage(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//功能函数
public:
	//加载纹理
	bool LoadImage(CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName,DWORD dwColorKey=0);
	//加载纹理
	bool LoadImage(CD3DDevice * pD3DDevice, LPCTSTR pszFileName,DWORD dwColorKey=0);

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
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, BYTE cbAlpha);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, BYTE cbAlpha);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, BYTE cbAlpha);

	//绘画函数
public:
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight);


	//绘画函数
public:
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, BYTE cbAlpha);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, BYTE cbAlpha);
	//绘画图片
	bool DrawImage(CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, BYTE cbAlpha);


	//绘画函数
public:
	//绘画图片
	static bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, DWORD* dwData, INT nImageWidth, INT nImageHeight);

	//内部函数
protected:
	//获取资源
	bool GetResourceInfo(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, tagResourceInfo & ResourceInfo);

	//辅助函数
protected:
	//设置矩阵
	void SetProjectionMatrix( CD3DDevice * pD3DDevice );
	//设置矩阵
	VOID SetMatrix(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight);
	//输出位置
	VOID SetWindowPos(tagD3DTextureVertex * pTextureVertex, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight);
	//设置贴图
	VOID SetTexturePos(CD3DDevice * pD3DDevice, tagD3DTextureVertex * pTextureVertex, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight);
};

//////////////////////////////////////////////////////////////////////////////////

#endif