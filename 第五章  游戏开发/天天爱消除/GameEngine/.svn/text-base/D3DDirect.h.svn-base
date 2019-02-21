#ifndef D3D_DIRECT_HEAD_FILE
#define D3D_DIRECT_HEAD_FILE

#include "GameEngineHead.h"
#include "TraceDebug.h"
//////////////////////////////////////////////////////////////////////////////////

//类说明
class CD3DDirect;
class CD3DDevice;
// class CD3DTexture;

//////////////////////////////////////////////////////////////////////////////////

//环境对象
class GAME_ENGINE_CLASS CD3DDirect
{
	//接口变量
public:
	IDirect3D9 *					m_pIDirect3D;						//环境对象
	
	//静态变量
public:
	static CD3DDirect *				m_pD3DDirect;						//对象指针
	
	//函数定义
public:
	//构造函数
	CD3DDirect();
	//析构函数
	virtual ~CD3DDirect();

	//功能函数
public:
	//创建环境
	bool CreateD3DDirect();

	//信息函数
public:
	//设备能力
	bool GetDeviceCaps(D3DCAPS9 & D3DCaps);
	//显示模式
	bool GetDisplayMode(D3DDISPLAYMODE & DisplayMode);

	//静态函数
public:
	//获取对象
	static CD3DDirect * GetInstance() { return m_pD3DDirect; }
};

//////////////////////////////////////////////////////////////////////////////////

#endif