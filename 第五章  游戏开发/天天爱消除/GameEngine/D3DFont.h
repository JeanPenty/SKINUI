#ifndef D3D_FOUNT_HEAD_FILE
#define D3D_FOUNT_HEAD_FILE

#include "D3DDevice.h"
#include "D3DSprite.h"
#include "GameEngineHead.h"

//////////////////////////////////////////////////////////////////////////////////
class CD3DFont;

//类型定义
typedef CArray<CD3DFont *,CD3DFont *> CD3DFontItemPtrArray;

//////////////////////////////////////////////////////////////////////////////////

//字体管理
class GAME_ENGINE_CLASS CD3DFont
{
	//配置变量
protected:
	UINT							m_uGrayLevel;						//灰度等级
	UINT							m_uMaxBufferCount;					//缓冲数目

	//字体对象
protected:
	ID3DXFont						*m_pD3DXFont;
	CFont							m_Font;								//字体对象
	
	//内核对象
protected:
	static CD3DFontItemPtrArray		m_FontItemPtrActive;				//字体数组

	//函数定义
public:
	//构造函数
	CD3DFont();
	//析构函数
	virtual ~CD3DFont();

	//缓冲数目
public:
	//缓冲数目
	UINT GetMaxBufferCount() { return m_uMaxBufferCount; }
	//缓冲数目
	VOID SetMaxBufferCount(UINT uMaxBufferCount) { m_uMaxBufferCount=uMaxBufferCount; }

	//创建函数
public:
	//删除字体
	bool DeleteFont();
	//创建字体
	bool CreateFont(LOGFONT & LogFont, UINT uGrayLevel);
	//创建字体
	bool CreateFont(INT nPointSize, LPCTSTR lpszFaceName, UINT uGrayLevel);

	//输出字体
public:
	//输出字体
	bool DrawText(CD3DDevice * pD3DDevice, LPCTSTR pszString, CRect rcDraw, UINT uFormat, D3DCOLOR D3DColor);
	//输出字体
	bool DrawText(CD3DDevice * pD3DDevice, LPCTSTR pszString, INT nXPos, INT nYPos, UINT uFormat, D3DCOLOR D3DColor);

	//静态函数
public:
	//释放资源
	static VOID OnDeviceLost(CD3DDevice * pD3DDevice);
	//重置资源
	static VOID OnDeviceReset(CD3DDevice * pD3DDevice);
};

//////////////////////////////////////////////////////////////////////////////////

#endif