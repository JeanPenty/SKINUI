#ifndef D3D_DIRECT_HEAD_FILE
#define D3D_DIRECT_HEAD_FILE

#include "TraceDebug.h"
//////////////////////////////////////////////////////////////////////////////////

//��˵��
class CD3DDirect;
class CD3DDevice;
// class CD3DTexture;

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_ENGINE_CLASS CD3DDirect
{
	//�ӿڱ���
public:
	IDirect3D9 *					m_pIDirect3D;						//��������
	
	//��̬����
public:
	static CD3DDirect *				m_pD3DDirect;						//����ָ��
	
	//��������
public:
	//���캯��
	CD3DDirect();
	//��������
	virtual ~CD3DDirect();

	//���ܺ���
public:
	//��������
	bool CreateD3DDirect();

	//��Ϣ����
public:
	//�豸����
	bool GetDeviceCaps(D3DCAPS9 & D3DCaps);
	//��ʾģʽ
	bool GetDisplayMode(D3DDISPLAYMODE & DisplayMode);

	//��̬����
public:
	//��ȡ����
	static CD3DDirect * GetInstance() { return m_pD3DDirect; }
};

//////////////////////////////////////////////////////////////////////////////////

#endif