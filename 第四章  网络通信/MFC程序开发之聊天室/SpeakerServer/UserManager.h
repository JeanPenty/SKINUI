#pragma once

#include <map>
using namespace std;

typedef map<DWORD,tagUserData*>			CUserItemArray;

class CUserManager
{
protected:
	CUserItemArray						m_UserItemArray;

public:
	CUserManager(void);
	virtual ~CUserManager(void);

public:
	//��������
	static CUserManager*GetInstance();

	//���ܺ���
public:
	//��������
	void InsertUserItem(tagUserData*pUserData);
	//ɾ������
	void RemoveUserItem(DWORD dwUserID);
	
	//��ȡ����
public:
	//��ȡ�ǳ�
	LPCTSTR GetUserName(DWORD dwUserID);
	//��ȡ����
	LPCTSTR GetPassWord(DWORD dwUserID);
	//��ȡ����
	tagUserData *GetUserData(DWORD dwUserID);
	//��ȡ����
	int GetUserCount();
	//��ȡ����
	CUserItemArray *GetUserItemArray();
};
