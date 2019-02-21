#include "StdAfx.h"
#include "TextureManager.h"

CTextureManager::CTextureManager(void)
{
	m_CTextureMap.clear();
}

CTextureManager::~CTextureManager(void)
{
	RemoveAllTexture();
}

CD3DTexture* CTextureManager::InitWithTexture( CD3DDevice * pD3DDevice, LPCTSTR lpszFileName,DWORD dwColorKey/*=0*/ )
{
	map<LPCTSTR,tagImageInfo*>::iterator iter;
	pair<std::map<LPCTSTR, tagImageInfo *>::iterator, bool> pairInsert;

	tagImageInfo * pImageInfo = NULL;
	CD3DTexture * pImage=NULL;

	if (NULL == lpszFileName || NULL == *lpszFileName)
		return NULL;

	iter = m_CTextureMap.find(lpszFileName);
	if (iter != m_CTextureMap.end())
	{
		if ( iter->second != NULL )
		{
			iter->second->nRef++;
			return iter->second->pImage;
		}
		
		return NULL;
	}
	else
	{
		pImageInfo = new tagImageInfo;
		pImage = new CD3DTexture;
		
		if (NULL == pImageInfo || NULL == pImage)
		{
			SafeDelete(pImageInfo);
			SafeDelete(pImage);

			return NULL;
		}

		pairInsert = m_CTextureMap.insert(pair<LPCTSTR, tagImageInfo *>(lpszFileName, pImageInfo));
		if (!pairInsert.second)
		{
			SafeDelete(pImageInfo);
			SafeDelete(pImage);

			return NULL;
		}

		bool bReturn = false;

		TCHAR szWorkDirectory[MAX_PATH]={0};
		GetWorkDirectory(szWorkDirectory,MAX_PATH);
		StrCat(szWorkDirectory,TEXT("\\"));
		StrCat(szWorkDirectory,lpszFileName);

		CFileFind fileFind;

		//判断是否exe目录下的资源
		if ( fileFind.FindFile(szWorkDirectory) )
			bReturn = pImage->LoadImage(pD3DDevice,szWorkDirectory,dwColorKey);
		//lpszFileName为完整路径
		else 
			bReturn = pImage->LoadImage(pD3DDevice,lpszFileName,dwColorKey);

		if (!bReturn)
		{
			pImage->Destory();
			SafeDelete(pImageInfo);
			SafeDelete(pImage);
			m_CTextureMap.erase(pairInsert.first);
			
			return NULL;
		}

		pImageInfo->pImage = pImage;
		pImageInfo->nRef = 1;

		return pImage;
	}
}

CD3DTexture* CTextureManager::InitWithTexture( CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName,DWORD dwColorKey/*=0*/ )
{
	map<LPCTSTR,tagImageInfo*>::iterator iter;
	pair<std::map<LPCTSTR, tagImageInfo *>::iterator, bool> pairInsert;

	tagImageInfo * pImageInfo = NULL;
	CD3DTexture * pImage=NULL;

	if (NULL == pszResource || NULL == *pszResource)
		return NULL;

	iter = m_CTextureMap.find(pszResource);
	if (iter != m_CTextureMap.end())
	{
		if ( iter->second != NULL )
		{
			iter->second->nRef++;
			return iter->second->pImage;
		}

		return NULL;
	}
	else
	{
		pImageInfo = new tagImageInfo;
		pImage = new CD3DTexture;

		if (NULL == pImageInfo || NULL == pImage)
		{
			SafeDelete(pImageInfo);
			SafeDelete(pImage);

			return NULL;
		}

		pairInsert = m_CTextureMap.insert(pair<LPCTSTR, tagImageInfo *>(pszResource, pImageInfo));
		if (!pairInsert.second)
		{
			SafeDelete(pImageInfo);
			SafeDelete(pImage);

			return NULL;
		}
	
		bool bReturn = pImage->LoadImage(pD3DDevice,hInstance,pszResource,pszTypeName,dwColorKey);

		if (!bReturn)
		{
			pImage->Destory();
			SafeDelete(pImageInfo);
			SafeDelete(pImage);
			m_CTextureMap.erase(pairInsert.first);

			return NULL;
		}

		pImageInfo->pImage = pImage;
		pImageInfo->nRef = 1;

		return pImage;
	}
}

bool CTextureManager::GetWorkDirectory( TCHAR szWorkDirectory[], WORD wBufferCount )
{
	//模块路径
	TCHAR szModulePath[MAX_PATH]=TEXT("");
	GetModuleFileName(GetModuleHandle(GAME_ENGINE_DLL_NAME),szModulePath,CountArray(szModulePath));

	//分析文件
	for (INT i=lstrlen(szModulePath);i>=0;i--)
	{
		if (szModulePath[i]==TEXT('\\'))
		{
			szModulePath[i]=0;
			break;
		}
	}

	//设置结果
	ASSERT(szModulePath[0]!=0);
	lstrcpyn(szWorkDirectory,szModulePath,wBufferCount);

	return true;

}

void CTextureManager::RemoveTexture( CD3DTexture *&pImage )
{
	map<LPCTSTR, tagImageInfo *>::iterator iter;
	tagImageInfo * pImageInfo;

	if (NULL == pImage) return;

	for (iter = m_CTextureMap.begin(); iter != m_CTextureMap.end(); iter++)
	{
		pImageInfo = iter->second;
		if (pImageInfo != NULL)
		{
			if (pImageInfo->pImage == pImage)
			{
				pImageInfo->nRef--;
				if (pImageInfo->nRef <= 0)
				{
					pImageInfo->pImage->Destory();

					SafeDelete(pImageInfo->pImage);
					SafeDelete(pImageInfo);

					m_CTextureMap.erase(iter);
				}

				pImage = NULL;
				break;
			}
		}
	}
}

void CTextureManager::RemoveAllTexture()
{
	map<LPCTSTR, tagImageInfo *>::iterator iter;
	tagImageInfo * pImageInfo;

	for (iter = m_CTextureMap.begin(); iter != m_CTextureMap.end(); iter++)
	{
		pImageInfo = iter->second;
		if (pImageInfo != NULL)
		{
			if (pImageInfo->pImage != NULL)
			{
				pImageInfo->pImage->Destory();
				SafeDelete(pImageInfo->pImage);
			}

			SafeDelete(pImageInfo);
		}
	}

	m_CTextureMap.clear();
}

CTextureManager* CTextureManager::GetInstance()
{
	static CTextureManager _Instance;
	return &_Instance;
}
