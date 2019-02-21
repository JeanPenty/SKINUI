#ifndef VIRTUAL_SLIDER_HEAD_FILE
#define VIRTUAL_SLIDER_HEAD_FILE

#pragma once

//����ؼ�
//////////////////////////////////////////////////////////////////////////
class GAME_ENGINE_CLASS CVirtualSlider : public CVirtualWindow
{
protected:
	CD3DTexture					* m_pTextureBack;				//��������
	CD3DTexture					* m_pTextureChannel;			//�켣����
	CD3DTexture					* m_pTextureButton;				//��ť����

protected:
	INT 						m_nMin;							//��С��Χ
	INT 						m_nMax;							//���Χ
	INT							m_nPos;							//��ǰλ��
	INT							m_nButtonX;						//��ťλ��

	cCRect						m_rcButtonRect;					//��ť����
	bool						m_bMouseDown;					//���±�־

	//��������
public:
	//���캯��
	CVirtualSlider(void);
	//��������
	~CVirtualSlider(void);

	//ϵͳ�¼�
protected:
	//������Ϣ
	virtual VOID OnWindowMovie(){}
	//������Ϣ
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice){}
	//������Ϣ
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice);

	//���غ���
protected:
	//����¼�
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);
	//�����¼�
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam){ return FALSE;}
	//�滭����
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);

	//���ܺ���
public:
	//��������
	void SetTexture(CD3DTexture*,CD3DTexture*,CD3DTexture*);
	//���÷�Χ
	void SetRange( int nMin, int nMax );
	//����λ��
	void SetPos( int nPos );

	//��ȡ����
public:
	//��ȡ��Χ
	void GetRange( int& nMin, int& nMax ) const;
	//��ȡλ��
	INT GetPos();

	//��������
private:
	//���¾���
	void UpdateRects();
};

#endif