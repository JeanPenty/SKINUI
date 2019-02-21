#ifndef GAME_FRAME_VIEW_HEAD_FILE
#define GAME_FRAME_VIEW_HEAD_FILE

#pragma once

#include "Tracedialog.h"
// CWindowImpl

class GAME_ENGINE_CLASS CWindowImpl : public CMsgEvent, public ID3DDeviceSink, public cCWnd
{
	//״̬����
protected:
	bool							m_bInitD3D;							//������־
	HANDLE 							m_hRenderThread;					//��Ⱦ�߳�
	HWND							m_hOwnWnd;

	//֡��ͳ��
protected:
	DWORD							m_dwDrawBenchmark;					//��׼���
	DWORD							m_dwDrawLastCount;					//�滭����
	DWORD							m_dwDrawCurrentCount;				//�滭����

	//�������
public:
	CD3DDirect						m_D3DDirect;						//��������
	CD3DDevice						m_D3DDevice;						//�豸����
	CVirtualEngine					m_VirtualEngine;					//��������
	CTraceDialog					m_TraceDialog;

	//��������
public:
	//���캯��
	CWindowImpl();
	//��������
	virtual ~CWindowImpl();

	//���溯��
private:
	//�����ؼ�
	virtual VOID RectifyControl(INT nWidth, INT nHeight){}
	//��������
	virtual VOID CartoonMovie(){}
	//���ý���
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight){}
	//�滭����
	virtual VOID DrawGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight){}

	//�豸�ӿ�
protected:
	//�����豸
	virtual VOID OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//��ʧ�豸
	virtual VOID OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//�����豸
	virtual VOID OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//��Ⱦ����
	virtual VOID OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//���غ���
protected:
	//Ĭ�ϻص�
	virtual LRESULT WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );

	//���ܺ���
public:
	//��Ⱦ�߳�
	VOID StartRenderThread();
	//
	VOID SetLogFile(LPCTSTR lpszNameFile);
	//
	INT InitInstance(HINSTANCE hInstance,LPCTSTR lpszWindowName);

	//�Զ���Ϣ
protected:
	//��Ⱦ��Ϣ
	void OnMessageD3DRender();

	//��̬����
private:
	//��Ⱦ�߳�
	static VOID D3DRenderThread(LPVOID pThreadData);
};

#endif
