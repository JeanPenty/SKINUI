#ifndef VIRTUAL_LIST_HEAD_FILE
#define VIRTUAL_LIST_HEAD_FILE

#pragma once

#include "VirtualWindow.h"
#include "D3DTexture.h"

struct tagListBoxItem
{
	TCHAR		strText[MAX_PATH];
	void		* pData;

	INT			nItemHeight;
	bool		bSelected;
	D3DCOLOR	D3DColor;
};
//////////////////////////////////////////////////////////////////////////
typedef CArray<tagListBoxItem*,tagListBoxItem*>			CListBoxItemArray;

class GAME_ENGINE_CLASS CVirtualListBox : public CVirtualWindow
{
protected:
	CListBoxItemArray					m_ListBoxItemArray;
	CD3DTexture							* m_pTextureBack;
	CRect								m_rcActive;

	//��������
public:
	//���캯��
	CVirtualListBox(void);
	//��������
	virtual ~CVirtualListBox(void);

	//ϵͳ�¼�
protected:
	//������Ϣ
	virtual VOID OnWindowMovie();
	//������Ϣ
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice);
	//������Ϣ
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice);
	//λ����Ϣ
	virtual VOID OnWindowPosition(CD3DDevice * pD3DDevice);

	//���غ���
protected:
	//����¼�
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);
	//�����¼�
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam);
	//�滭����
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);

public:
	int AddString(LPCTSTR lpszItem);

	void ResetContent();

	void SetTexture(CD3DTexture *pBack);
};

#endif