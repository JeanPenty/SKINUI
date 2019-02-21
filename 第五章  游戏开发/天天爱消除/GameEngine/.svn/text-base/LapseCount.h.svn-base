#ifndef LAPSE_COUNT_HEAD_FILE
#define LAPSE_COUNT_HEAD_FILE

#pragma once

#include "GameEngineHead.h"

//////////////////////////////////////////////////////////////////////////////////

//流逝计数
class GAME_ENGINE_CLASS CLapseCount
{
	//变量定义
protected:
	DWORD							m_dwQueryTickCount;					//查询时间

	//变量定义
protected:
	static DWORD					m_dwCurrentTickCount;				//当前时间

	//函数定义
public:
	//构造函数
	CLapseCount();
	//析构函数
	virtual ~CLapseCount();

	//功能函数
public:
	//流逝配置
	VOID Initialization();
	//流逝判断
	DWORD GetLapseCount(DWORD dwPulseCount);

	//功能函数
public:
	//更新时间
	static VOID PerformLapseCount();
};

//////////////////////////////////////////////////////////////////////////////////

#endif