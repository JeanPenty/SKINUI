#ifndef D3D_DEVICE_HEAD_FILE
#define D3D_DEVICE_HEAD_FILE

#include "GameEngineHead.h"
#include "TraceDebug.h"
//////////////////////////////////////////////////////////////////////////////////

//类说明
class CD3DDirect;
class CD3DDevice;
class CD3DTexture;

//////////////////////////////////////////////////////////////////////////////////

//设备接口
interface ID3DDeviceSink
{
	//设备事件
public:
	//配置设备
	virtual VOID OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//丢失设备
	virtual VOID OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//重置设备
	virtual VOID OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//渲染窗口
	virtual VOID OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

//设备对象
class GAME_ENGINE_CLASS CD3DDevice
{
	//窗口属性
public:
	HWND 							m_hWndDevice;						//设备窗口
	CSize							m_SizeWindow;						//窗口大小

	//帧数统计
protected:
	DWORD							m_dwDrawBenchmark;					//基准起点
	DWORD							m_dwDrawLastCount;					//绘画次数
	DWORD							m_dwDrawCurrentCount;				//绘画次数

	//接口变量
protected:
	ID3DDeviceSink *				m_pID3DDeviceSink;					//回调接口
	IDirect3DDevice9 *				m_pIDirect3DDevice;					//设备对象

	//函数定义
public:
	//构造函数
	CD3DDevice();
	//析构函数
	virtual ~CD3DDevice();

	//信息函数
public:
	//获取窗口
	HWND GetWndDevice() { return m_hWndDevice; }
	//获取大小
	CSize GetSizeWindow() { return m_SizeWindow; }

	//获取接口
public:
	//回调接口
	ID3DDeviceSink * GetD3DDeviceSink() { return m_pID3DDeviceSink; }
	//设备接口
	IDirect3DDevice9 * GetDirect3DDevice() { return m_pIDirect3DDevice; }

	//控制函数
public:
	//重置设备
	bool ResetD3DDevice();
	//渲染设备
	bool RenderD3DDevice();
	//计算帧数
	DWORD CalcFPS();
	//创建设备
	bool CreateD3DDevice(HWND hWndDevice, ID3DDeviceSink * pID3DDeviceSink);

	//渲染属性
public:
	//渲染属性
	HRESULT SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
	//渲染属性
	HRESULT GetRenderState(D3DRENDERSTATETYPE State, DWORD & Value);

	//填充函数
public:
	//填充颜色
	VOID FillRect(CRect rcRect, D3DCOLOR D3DColor);
	//填充颜色
	VOID FillRect(INT nXPos, INT nYPos, INT nWidth, INT nHeigth, D3DCOLOR D3DColor);

	//绘画函数
public:
	//绘画矩形
	VOID DrawRect(CRect rcRect, D3DCOLOR D3DColor);
	//绘画矩形
	VOID DrawPolyLine(POINT* apPoints, UINT nNumPoints, D3DCOLOR D3DColor);
	//绘画线条
	VOID DrawLine(INT nXPos1, INT nYPos1, INT nXPos2, INT nYPos2, D3DCOLOR D3DColor);

	//内部函数
private:
	//设置环境
	VOID InitD3DDevice();
	//设置数据
	VOID InitPresentParameters(D3DPRESENT_PARAMETERS & PresentParameters, HWND hWnd, INT nWidth, INT nHeight, D3DFORMAT BufferFormat);
};

//////////////////////////////////////////////////////////////////////////////////

#endif