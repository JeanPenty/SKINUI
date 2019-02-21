#pragma once

#include "SkinUI.h"

struct tagString 
{
	UINT				uID;
	UINT				uFontIndex;
	COLORREF			colStatic;
	tagPositionData		*pPositionData;
	CString				strText;
	UINT				uFormat;
	bool				bVisible;
};

struct tagImage
{
	tagPositionData		*pPositionData;
	UINT				uID;
	CImageEx			*pImage;
	BYTE				cbAlpha;
	DWORD				dwMask;
	int					nType;
	int					nRotation;
	bool				bGray;
	bool				bVisible;
};

//////////////////////////////////////////////////////////////////////////

class SKINUI_CLASS CBuildDialog
{
	friend class CXmlManager;
	friend class ISkinControl;

protected:
	HWND						m_hOwnWnd;
	CXmlManager					*m_pXml;

public:
	vector<ISkinControl*>		m_ControlArray;
	vector<tagString*>			m_StringArray;
	vector<tagImage*>			m_ImageArray;

	//���ڱ���
public:
	CSize						m_szWindowSize;				//���ڴ�С
	CSize						m_szRcSize;					//Բ�Ǵ�С
	CSize						m_szMinSize;				//��С�ߴ�
	CSize						m_szMaxSize;				//���ߴ�
	bool						m_bExtrude;					//�Ƿ��������
	bool						m_bClip;
	COLORREF					m_colBK;
	bool						m_bDefaultSkin;
	
public:
	CBuildDialog(void);
	virtual ~CBuildDialog(void);

public:
	//���þ��
	inline void SetOwnHwnd(HWND hWnd){ m_hOwnWnd = hWnd; }
	//��������
	bool ParseWindow(LPCTSTR lpszFileName);
	//�����ؼ�
	bool ParseControl(CWnd* pParentWnd);
	//����ͼ��
	bool ParseGraphics();

	//Ĭ��Ƥ��
	void SetDefaultSkin(bool bDefault){ m_bDefaultSkin = bDefault; }

	//String����
public:
	int AddString(LPCTSTR lpszText,UINT uFontIndex,UINT uFormat,COLORREF col,bool bVisible,tagPositionData *pPositionData,UINT uID);
	tagPositionData *GetStringRect(UINT uID);
	tagString *GetString(UINT uID);

	//Image����
public:
	int AddImage(LPCTSTR lpszFileName,BYTE dwAlpha,DWORD dwMask,int nType,int nRotation,bool bGray,bool bVisible,tagPositionData *pPositionData,UINT uID);
	tagPositionData *GetImageRect(UINT uID);
	tagImage *GetImage(UINT uID);

	//���ƺ���
public:
	//��������
	void DrawString(CDC*pDC);
	//����ͼ��
	void DrawImage(CDC*pDC);

public:
	//�û��Զ���ؼ�
	virtual bool CreateUserControl(){ return false; }
};
