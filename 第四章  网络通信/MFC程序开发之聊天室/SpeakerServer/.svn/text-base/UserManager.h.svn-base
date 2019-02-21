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
	//创建单件
	static CUserManager*GetInstance();

	//功能函数
public:
	//插入数据
	void InsertUserItem(tagUserData*pUserData);
	//删除数据
	void RemoveUserItem(DWORD dwUserID);
	
	//获取函数
public:
	//获取昵称
	LPCTSTR GetUserName(DWORD dwUserID);
	//获取密码
	LPCTSTR GetPassWord(DWORD dwUserID);
	//获取数据
	tagUserData *GetUserData(DWORD dwUserID);
	//获取数量
	int GetUserCount();
	//获取容器
	CUserItemArray *GetUserItemArray();
};
