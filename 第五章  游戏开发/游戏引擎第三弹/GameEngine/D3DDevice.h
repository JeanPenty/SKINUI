#ifndef D3D_DEVICE_HEAD_FILE
#define D3D_DEVICE_HEAD_FILE

#pragma once
#include "type.h"
//////////////////////////////////////////////////////////////////////////////////

//��˵��
class CD3DDirect;
class CD3DDevice;
class CD3DTexture;

//////////////////////////////////////////////////////////////////////////////////

//�豸�ӿ�
interface ID3DDeviceSink
{
	//�豸�¼�
public:
	//�����豸
	virtual VOID OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//��ʧ�豸
	virtual VOID OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//�����豸
	virtual VOID OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//��Ⱦ����
	virtual VOID OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

//�豸����
class GAME_ENGINE_CLASS CD3DDevice
{
	//��������
public:
	HWND 							m_hWndDevice;						//�豸����
	cCSize							m_SizeWindow;						//���ڴ�С

	//֡��ͳ��
protected:
	DWORD							m_dwDrawBenchmark;					//��׼���
	DWORD							m_dwDrawLastCount;					//�滭����
	DWORD							m_dwDrawCurrentCount;				//�滭����

	//�ӿڱ���
protected:
	ID3DDeviceSink *				m_pID3DDeviceSink;					//�ص��ӿ�
	IDirect3DDevice9 *				m_pIDirect3DDevice;					//�豸����

	//��������
public:
	//���캯��
	CD3DDevice();
	//��������
	virtual ~CD3DDevice();

	//��Ϣ����
public:
	//��ȡ����
	HWND GetWndDevice() { return m_hWndDevice; }
	//��ȡ��С
	cCSize GetSizeWindow() { return m_SizeWindow; }

	//��ȡ�ӿ�
public:
	//�ص��ӿ�
	ID3DDeviceSink * GetD3DDeviceSink() { return m_pID3DDeviceSink; }
	//�豸�ӿ�
	IDirect3DDevice9 * GetDirect3DDevice() { return m_pIDirect3DDevice; }

	//���ƺ���
public:
	//�����豸
	bool ResetD3DDevice();
	//��Ⱦ�豸
	bool RenderD3DDevice();
	//����֡��
	DWORD CalcFPS();
	//�����豸
	bool CreateD3DDevice(HWND hWndDevice, ID3DDeviceSink * pID3DDeviceSink);

	//��Ⱦ����
public:
	//��Ⱦ����
	HRESULT SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
	//��Ⱦ����
	HRESULT GetRenderState(D3DRENDERSTATETYPE State, DWORD & Value);

	//��亯��
public:
	//�����ɫ
	VOID FillRect(cCRect rcRect, D3DCOLOR D3DColor);
	//�����ɫ
	VOID FillRect(INT nXPos, INT nYPos, INT nWidth, INT nHeigth, D3DCOLOR D3DColor);

	//�滭����
public:
	//�滭����
	VOID DrawRect(cCRect rcRect, D3DCOLOR D3DColor);
	//�滭����
	VOID DrawPolyLine(POINT* apPoints, UINT nNumPoints, D3DCOLOR D3DColor);
	//�滭����
	VOID DrawLine(INT nXPos1, INT nYPos1, INT nXPos2, INT nYPos2, D3DCOLOR D3DColor);

	//�ڲ�����
private:
	//���û���
	VOID InitD3DDevice();
	//��������
	VOID InitPresentParameters(D3DPRESENT_PARAMETERS & PresentParameters, HWND hWnd, INT nWidth, INT nHeight, D3DFORMAT BufferFormat);
};

//////////////////////////////////////////////////////////////////////////////////

#endif