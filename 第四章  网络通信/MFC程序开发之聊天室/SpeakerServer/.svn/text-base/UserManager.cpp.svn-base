#include "StdAfx.h"
#include "UserManager.h"

CUserManager::CUserManager(void)
{
	m_UserItemArray.clear();
}

CUserManager::~CUserManager(void)
{
	CUserItemArray::iterator iter = m_UserItemArray.begin();

	for (;iter != m_UserItemArray.end(); ++iter )
	{
		SafeDelete(iter->second);
	}

	m_UserItemArray.clear();
}

CUserManager* CUserManager::GetInstance()
{
	static CUserManager _Instance;

	return &_Instance;
}

void CUserManager::InsertUserItem( tagUserData*pUserData )
{
	m_UserItemArray.insert(pair<DWORD,tagUserData*>(pUserData->dwUserID,pUserData));
}

LPCTSTR CUserManager::GetUserName( DWORD dwUserID )
{
	CUserItemArray::iterator iter = m_UserItemArray.find(dwUserID);
	if ( iter == m_UserItemArray.end() ) return 0;
	
	return iter->second->szUserName;
}

void CUserManager::RemoveUserItem( DWORD dwUserID )
{
	CUserItemArray::iterator iter = m_UserItemArray.find(dwUserID);
	if ( iter == m_UserItemArray.end() ) return;

	SafeDelete(iter->second);
	m_UserItemArray.erase(iter);
}

int CUserManager::GetUserCount()
{
	return m_UserItemArray.size();
}

tagUserData * CUserManager::GetUserData( DWORD dwUserID )
{
	CUserItemArray::iterator iter = m_UserItemArray.find(dwUserID);
	if ( iter == m_UserItemArray.end() ) return NULL;

	return iter->second;
}

LPCTSTR CUserManager::GetPassWord( DWORD dwUserID )
{
	CUserItemArray::iterator iter = m_UserItemArray.find(dwUserID);
	if ( iter == m_UserItemArray.end() ) return 0;

	return iter->second->szPassWord;
}

CUserItemArray * CUserManager::GetUserItemArray()
{
	return &m_UserItemArray;
}
