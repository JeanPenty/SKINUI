#ifndef D3D_TEXTURE_MANAGER_HEAD_FILE
#define D3D_TEXTURE_MANAGER_HEAD_FILE

#pragma once

#include "GameEngineHead.h"
#include "D3DTexture.h"

//资源结构
struct tagImageInfo
{
	CD3DTexture		*pImage;
	int				nRef;
};


typedef map<LPCTSTR,tagImageInfo*>				CTextureMap;

//////////////////////////////////////////////////////////////////////////
class GAME_ENGINE_CLASS CTextureManager
{
protected:
	CTextureMap					m_CTextureMap;

public:
	CTextureManager(void);
	virtual ~CTextureManager(void);

	static CTextureManager*GetInstance();

public:
	CD3DTexture* InitWithTexture(CD3DDevice * pD3DDevice, LPCTSTR lpszFileName,DWORD dwColorKey=0);

	CD3DTexture* InitWithTexture(CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName,DWORD dwColorKey=0);
	//删除图片
	void RemoveTexture(CD3DTexture *&pImage);
	//删除所有
	void RemoveAllTexture();

public:
	//进程目录
	bool GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount);
};

//////////////////////////////////////////////////////////////////////////
#define TextureManager	CTextureManager::GetInstance()

#endif