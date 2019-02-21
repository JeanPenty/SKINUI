#include "stdafx.h"
#include "LapseCount.h"

DWORD CLapseCount::m_dwCurrentTickCount = 0;

CLapseCount::CLapseCount()
{
	m_dwQueryTickCount = 0;
}

CLapseCount::~CLapseCount()
{

}

VOID CLapseCount::Initialization()
{
	m_dwQueryTickCount = timeGetTime();
	m_dwCurrentTickCount = timeGetTime();
}

DWORD CLapseCount::GetLapseCount( DWORD dwPulseCount )
{
	DWORD dwElapseTime = timeGetTime()-m_dwQueryTickCount;

	if ( dwElapseTime > dwPulseCount) 
	{
		m_dwQueryTickCount = timeGetTime();
		return dwElapseTime;
	}

	return 0;
}

VOID CLapseCount::PerformLapseCount()
{
	
}
