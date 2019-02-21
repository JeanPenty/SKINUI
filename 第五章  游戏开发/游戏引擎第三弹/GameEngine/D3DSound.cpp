#include "Stdafx.h"
#include "D3DSound.h"

CD3DSound::CD3DSound()
{
	m_nSampleRate = 44100;
	m_MusicStreamMap.clear();
}

CD3DSound::~CD3DSound()
{
	//释放用户未被释放的资源
	CMusicStreamMap::iterator iter = m_MusicStreamMap.begin();

	for (;iter != m_MusicStreamMap.end(); ++iter )
	{
		BASS_SampleFree(iter->first);
	}

	m_MusicStreamMap.clear();
}

//创建环境
bool CD3DSound::CreateD3DSound(HWND hWnd)
{
	if (HIWORD(BASS_GetVersion()) != BASSVERSION)
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("Incorrect BASS.DLL version"));

		return false;
	}

	if (!BASS_Init(-1,m_nSampleRate,0,hWnd,NULL))
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("BASS Init failed, using no sound"));
		return false;
	}

	//获取声卡设备信息
	BASS_DEVICEINFO _DeviceInfo;
	BASS_GetDeviceInfo(1,&_DeviceInfo);

#ifdef _UNICODE
	TCHAR szBuffer[MAX_PATH];

	MultiByteToWideChar(CP_ACP,	0,_DeviceInfo.name,-1,szBuffer,MAX_PATH);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Sound Device: %s"),szBuffer);

	MultiByteToWideChar(CP_ACP,	0,_DeviceInfo.driver,-1,szBuffer,MAX_PATH);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Sound Device Driver: %s"),szBuffer);

#else
	TraceService->TraceString(TraceLevel_Normal,TEXT("Sound Device: %s"),_DeviceInfo.name);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Sound Device Driver: %s"),_DeviceInfo.driver);
#endif

	TraceService->TraceString(TraceLevel_Normal,TEXT("Sample rate: %ld\n"),m_nSampleRate);

	//将音量设到最大
	SetMusVolume(100);

	return true;
}

//加载声音
HSTREAM CD3DSound::LoadSound(LPCTSTR pszFileName, bool bRepetition)
{
	HSTREAM hStream;

	if(bRepetition)
		hStream = BASS_StreamCreateFile(FALSE, pszFileName, 0, 0, BASS_SAMPLE_LOOP|BASS_SAMPLE_FX|BASS_STREAM_PRESCAN);
	else
		hStream = BASS_StreamCreateFile(FALSE, pszFileName, 0, 0, BASS_STREAM_PRESCAN);

	if(hStream == 0)
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("[Sound] Can't load file %s,error code:%d"),pszFileName,BASS_ErrorGetCode());
		return 0;
	}

	//插入容器
	tagMusicStream tagMs;
	tagMs.hStream = hStream;
	tagMs.bLoop = bRepetition;

	m_MusicStreamMap.insert(pair<HSTREAM, tagMusicStream>(hStream,tagMs));

	TraceService->TraceString(TraceLevel_Normal,TEXT("[Sound] load file %s success"),pszFileName);

	return hStream;
}

//加载声音
HSTREAM CD3DSound::LoadSound(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, bool bRepetition)
{	
	//查找资源
	HRSRC hResource=FindResource(hInstance,pszResource,pszTypeName);
	if (hResource==NULL) return false;

	//读取资源
	DWORD dwSize=SizeofResource(hInstance,hResource);
	LPVOID pcbBuffer=LoadResource(hInstance,hResource);

	HSTREAM hStream;

	if(bRepetition)
		hStream = BASS_StreamCreateFile(TRUE, pcbBuffer, 0, dwSize, BASS_SAMPLE_LOOP|BASS_SAMPLE_FX|BASS_STREAM_PRESCAN);
	else
		hStream = BASS_StreamCreateFile(TRUE, pcbBuffer, 0, dwSize, BASS_STREAM_PRESCAN);


	if(hStream == 0)
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("[Sound] Can't load Resource %s,error code:%d"),pszResource,BASS_ErrorGetCode());
		return 0;
	}

	//插入容器
	tagMusicStream tagMs;
	tagMs.hStream = hStream;
	tagMs.bLoop = bRepetition;

	m_MusicStreamMap.insert(pair<HSTREAM, tagMusicStream>(hStream,tagMs));

	TraceService->TraceString(TraceLevel_Normal,TEXT("[Sound] load Resource %s success"),pszResource);

	return hStream;
}

//获取对象
CD3DSound * CD3DSound::GetInstance()
{
	static CD3DSound _Instance;

	return &_Instance;
}

//设置音量
void CD3DSound::SetMusVolume( DWORD dwVolume )
{
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, dwVolume*100);
}

//获取音量
DWORD CD3DSound::GetMusVolume()
{
	return BASS_GetConfig(BASS_CONFIG_GVOL_STREAM)/100;
}

//播放声音
HCHANNEL CD3DSound::PlaySound( HSTREAM hStream )
{
	HCHANNEL hChannel;

	hChannel=BASS_SampleGetChannel(hStream, FALSE);
	BASS_ChannelPlay(hStream, TRUE);
	
	return hChannel;
}

//删除声音
void CD3DSound::FreeSound( HSTREAM hStream )
{
	CMusicStreamMap::iterator iter = m_MusicStreamMap.find(hStream);
	if ( iter != m_MusicStreamMap.end() )
	{
		m_MusicStreamMap.erase(iter);
	}

	BASS_SampleFree(hStream);
}

//暂停声音
void CD3DSound::Channel_Pause( HCHANNEL hChannel )
{
	BASS_ChannelPause(hChannel);
}

//苏醒声音
void CD3DSound::Channel_Resume( HCHANNEL hChannel )
{
	BASS_ChannelPlay(hChannel, FALSE);
}	

//停止声音
void CD3DSound::Channel_Stop( HCHANNEL hChannel )
{
	BASS_ChannelStop(hChannel);
}

//暂停所有
void CD3DSound::Channel_PauseAll()
{
	BASS_Pause();
}

//苏醒所有
void CD3DSound::Channel_ResumeAll()
{
	BASS_Start();
}

//停止所有
void CD3DSound::Channel_StopAll()
{
	BASS_Stop();
	BASS_Start();
}

//正在播放
bool CD3DSound::Channel_IsPlaying( HCHANNEL hChannel )
{
	if(BASS_ChannelIsActive(hChannel)==BASS_ACTIVE_PLAYING) return true;
	else return false;
}

//获取大小
double CD3DSound::Channel_GetLength( HCHANNEL hChannel )
{
	return BASS_ChannelBytes2Seconds(hChannel, BASS_ChannelGetLength(hChannel,BASS_POS_BYTE));
}

//获取位置
double CD3DSound::Channel_GetPos( HCHANNEL hChannel )
{
	return BASS_ChannelBytes2Seconds(hChannel, BASS_ChannelGetPosition(hChannel,BASS_POS_BYTE));
}

//设置位置
void CD3DSound::Channel_SetPos( HCHANNEL hChannel, double dSeconds )
{
	BASS_ChannelSetPosition(hChannel, BASS_ChannelSeconds2Bytes(hChannel, dSeconds),BASS_POS_BYTE);
}

