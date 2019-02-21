#ifndef GAME_FRAME_VIEW_HEAD_FILE
#define GAME_FRAME_VIEW_HEAD_FILE

#pragma once

#include "GameEngineHead.h"
#include "D3DDevice.h"
#include "D3DDirect.h"
#include "VirtualEngine.h"
#include "VirtualWindow.h"
#include "Tracedialog.h"
// CGameFrameView

class GAME_ENGINE_CLASS CGameFrameView : public CDialog,public CMsgEvent, public ID3DDeviceSink
{
	DECLARE_DYNAMIC(CGameFrameView)
	
	//״̬����
protected:
	bool							m_bInitD3D;							//������־
	HANDLE 							m_hRenderThread;					//��Ⱦ�߳�

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
	CGameFrameView(UINT nIDTemplate,CWnd* pParent = NULL);
	//��������
	virtual ~CGameFrameView();

	//���溯��
private:
	//�����ؼ�
	virtual VOID RectifyControl(INT nWidth, INT nHeight)=NULL;
	//��������
	virtual VOID CartoonMovie()=NULL;
	//���ý���
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//�滭����
	virtual VOID DrawGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;

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
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//Ĭ�ϻص�
	virtual LRESULT DefWindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam);

	//���ܺ���
public:
	//��Ⱦ�߳�
	VOID StartRenderThread();
	//
	VOID SetLogFile(LPCTSTR lpszNameFile);

	//��Ϣӳ��
protected:
	//�滭����
	VOID OnPaint();
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	//�Զ���Ϣ
protected:
	//������Ϣ
	LRESULT OnMessageD3DStatus(WPARAM wParam, LPARAM lParam);
	//��Ⱦ��Ϣ
	LRESULT OnMessageD3DRender(WPARAM wParam, LPARAM lParam);

	//��̬����
private:
	//��Ⱦ�߳�
	static VOID D3DRenderThread(LPVOID pThreadData);

protected:
	DECLARE_MESSAGE_MAP()
};

#endif
