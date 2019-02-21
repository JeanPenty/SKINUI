#ifndef D3D_SOUND_HEAD_FILE
#define D3D_SOUND_HEAD_FILE

#include "GameEngineHead.h"
#include "bass.h"
#include <map>
using namespace std;

struct tagMusicStream
{
	HSTREAM		hStream;
	bool		bLoop;
};

//////////////////////////////////////////////////////////////////////////////////
typedef map<HSTREAM,tagMusicStream>				CMusicStreamMap;

//声音对象
class GAME_ENGINE_CLASS CD3DSound
{
	//接口变量
protected:
	INT								m_nSampleRate;
	CMusicStreamMap					m_MusicStreamMap;

	//函数定义
public:
	//构造函数
	CD3DSound();
	//析构函数
	virtual ~CD3DSound();

	//功能函数
public:
	//创建环境
	bool CreateD3DSound(HWND hWnd);

	//声音函数
public:
	//加载声音
	HSTREAM LoadSound(LPCTSTR pszFileName, bool bRepetition);
	//加载声音
	HSTREAM LoadSound(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, bool bRepetition);
	//播放声音
	HCHANNEL PlaySound(HSTREAM hStream);
	//播放声音
	HCHANNEL StopSound(HSTREAM hStream);
	//删除声音
	void FreeSound(HSTREAM hStream);
	//设置音量 0~100
	void SetMusVolume(DWORD dwVolume);
	//获取音量
	DWORD GetMusVolume();

	//通道函数
public:
	//暂停声音
	void Channel_Pause(HCHANNEL hChannel);
	//苏醒声音
	void Channel_Resume(HCHANNEL hChannel);
	//停止声音
	void Channel_Stop(HCHANNEL hChannel);
	//正在播放
	bool Channel_IsPlaying(HCHANNEL hChannel);
	//获取大小
	double Channel_GetLength(HCHANNEL hChannel);
	//获取位置
	double Channel_GetPos(HCHANNEL hChannel);
	//设置位置
	void Channel_SetPos(HCHANNEL hChannel, double dSeconds);
	//暂停所有
	void Channel_PauseAll();
	//苏醒所有
	void Channel_ResumeAll();
	//停止所有
	void Channel_StopAll();

	//静态函数
public:
	//获取对象
	static CD3DSound * GetInstance();
};

#define D3DSound	CD3DSound::GetInstance()
//////////////////////////////////////////////////////////////////////////////////

#endif