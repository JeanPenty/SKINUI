#ifndef VIRTUAL_BUTTON_HEAD_FILE
#define VIRTUAL_BUTTON_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////////////

//���ⰴť
class GAME_ENGINE_CLASS CVirtualButton : public CVirtualWindow
{
	//״̬����
protected:
	bool							m_bMouseDown;						//���±�־
	bool							m_bMouseMove;						//������־
	cCRect							m_rcButtonRect;						//��ť����

	//��������
protected:
	WORD							m_wImageIndex;						//��������
	CLapseCount						m_ImageLapseCount;					//���ż���

	//��Դ����
protected:
	CD3DTexture						*m_pD3DTextureButton;				//��ť����

	//��������
public:
	//���캯��
	CVirtualButton();
	//��������
	virtual ~CVirtualButton();

	//ϵͳ�¼�
protected:
	//������Ϣ
	virtual VOID OnWindowMovie();
	//������Ϣ
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice);
	//������Ϣ
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice);

	//���غ���
protected:
	//����¼�
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);
	//�����¼�
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam);
	//�滭����
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);

	//���ܺ���
public:
	//��������
	VOID SetButtonRect(cCRect rcButtonRect);
	//����λͼ
	VOID SetButtonImage( CD3DTexture *pD3DTextureButton );

	//�ڲ�����
protected:
	//�����ؼ�
	VOID RectifyControl(CD3DDevice * pD3DDevice);
};

//////////////////////////////////////////////////////////////////////////////////

#endif