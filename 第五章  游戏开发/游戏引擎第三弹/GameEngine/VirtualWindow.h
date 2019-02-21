#ifndef VIRTUAL_WINDOW_HEAD_FILE
#define VIRTUAL_WINDOW_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////

//���ⴰ��
class GAME_ENGINE_CLASS CVirtualWindow : public CMsgEvent
{
	//��Ԫ����
	friend class CVirtualEngine;
	friend class CVirtualButton;

	//��������
protected:
	bool							m_bActive;							//�����־
	bool							m_bEnable;							//���ñ�־
	bool							m_bVisible;							//��ʾ��־

	//���Ա���
protected:
	UINT							m_uWindowID;						//���ڱ�ʶ
	BOOL							m_bCaption;							//�����϶�
	BOOL							m_bDrag;							//�����϶�

	//λ�ñ���
protected:
	cCSize							m_WindowSize;						//���ڴ�С
	cCPoint							m_BenchmarkPos;						//��׼λ��

	//�ں˱���
protected:
	CVirtualWindow *				m_pParentWindow;					//�ϲ㴰��
	CVirtualEngine *				m_pVirtualEngine;					//������
	CVirtualWindowPtrArray			m_VirtualWindowPtrArray;			//��������

	//��������
public:
	//���캯��
	CVirtualWindow();
	//��������
	virtual ~CVirtualWindow();

	//���ڱ�ʶ
public:
	//��ȡ��ʶ
	UINT GetWindowID() { return m_uWindowID; }
	//���ñ�ʶ
	VOID SetWindowID(UINT uWindowID) { m_uWindowID=uWindowID; }

	//���Զ���
public:
	//�ϲ㴰��
	CVirtualWindow * GetParentWindow() { return m_pParentWindow; }
	//������
	CVirtualEngine * GetVirtualEngine() { return m_pVirtualEngine; }
	//
	HWND GetSafeHwnd();

	//������
public:
	//ɾ������
	VOID DeleteWindow();
	//�����
	bool ActiveWindow(cCRect & rcWindow, DWORD dwStyle, UINT uWindowID, CVirtualEngine * pVirtualEngine, CVirtualWindow * pParentWindow);

	//��������
public:
	//��������
	bool IsWindowActive() { return m_bActive; }
	//��������
	bool IsWindowEnable() { return m_bEnable; }
	//��ʾ����
	bool IsWindowVisible() { return m_bVisible; }

	//���ڿ���
public:
	//��ʾ����
	VOID ShowWindow(bool bVisible);
	//��ֹ����
	VOID EnableWindow(bool bEnable);
	//�����
	VOID ActiveWindow(bool bActive);
	//���´���
	VOID InvalidWindow(bool bCoerce);
	//���ý���
	VOID SetFocus();
	//���ٽ���
	VOID KillFocus();
	//��ֹ����
	VOID SetCaption(bool bCaption=true){ m_bCaption = bCaption;}

	//����λ��
public:
	//���ڴ�С
	VOID GetClientRect(cCRect & rcClient);
	//���ڴ�С
	VOID GetWindowRect(cCRect & rcWindow);
	//����λ��
	VOID SetWindowPos(INT nXPos, INT nYPos, INT nWidth, INT nHeight, UINT uFlags);
	//�϶�����
	BOOL DragWindows( UINT uMessage, INT nXMousePos, INT nYMousePos, UINT nFlags );

	//���ܺ���
public:
	//��������
	bool IsChildWindow(CVirtualWindow * pVirtualWindow);
	BOOL ContainsPoint( POINT pt );

	//ϵͳ�¼�
protected:
	//������Ϣ
	virtual VOID OnWindowMovie() { return; }
	//������Ϣ
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice) { return; }
	//������Ϣ
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice) { return; }
	//λ����Ϣ
	virtual VOID OnWindowPosition(CD3DDevice * pD3DDevice){ return; }
	//����¼�
	virtual BOOL OnWindowMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);

	//���غ���
protected:
	//����¼�
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos)=NULL;
	//�����¼�
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam)=NULL;
	//�滭����
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos)=NULL;

	//�ڲ�����
private:
	//���ô���
	VOID ResetWindow();
	//�滭����
	VOID OnEventDrawChildWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);
};

//////////////////////////////////////////////////////////////////////////////////

#endif