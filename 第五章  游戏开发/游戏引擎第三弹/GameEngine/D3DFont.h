#ifndef D3D_FOUNT_HEAD_FILE
#define D3D_FOUNT_HEAD_FILE

#include "D3DDevice.h"
#include "D3DSprite.h"

//////////////////////////////////////////////////////////////////////////////////
class CD3DFont;

//���Ͷ���
typedef cCArray<CD3DFont *> CD3DFontItemPtrArray;

//////////////////////////////////////////////////////////////////////////////////

//�������
class GAME_ENGINE_CLASS CD3DFont
{
	//���ñ���
protected:
	UINT							m_uGrayLevel;						//�Ҷȵȼ�
	UINT							m_uMaxBufferCount;					//������Ŀ

	//�������
protected:
	ID3DXFont						*m_pD3DXFont;
	HFONT							m_Font;								//�������
	
	//��������
public:
	//���캯��
	CD3DFont();
	//��������
	virtual ~CD3DFont();

	//������Ŀ
public:
	//������Ŀ
	UINT GetMaxBufferCount() { return m_uMaxBufferCount; }
	//������Ŀ
	VOID SetMaxBufferCount(UINT uMaxBufferCount) { m_uMaxBufferCount=uMaxBufferCount; }

	//��������
public:
	//ɾ������
	bool DeleteFont();
	//��������
	bool CreateFont(LOGFONT & LogFont, UINT uGrayLevel);
	//��������
	bool CreateFont(INT nPointSize, LPCTSTR lpszFaceName, UINT uGrayLevel);

	//�������
public:
	//�������
	bool DrawText(CD3DDevice * pD3DDevice, LPCTSTR pszString, cCRect rcDraw, UINT uFormat, D3DCOLOR D3DColor);
	//�������
	bool DrawText(CD3DDevice * pD3DDevice, LPCTSTR pszString, INT nXPos, INT nYPos, UINT uFormat, D3DCOLOR D3DColor);

	//��̬����
public:
	//�ͷ���Դ
	static VOID OnDeviceLost(CD3DDevice * pD3DDevice);
	//������Դ
	static VOID OnDeviceReset(CD3DDevice * pD3DDevice);
};

//////////////////////////////////////////////////////////////////////////////////

#endif