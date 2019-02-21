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

//��������
class GAME_ENGINE_CLASS CD3DSound
{
	//�ӿڱ���
protected:
	INT								m_nSampleRate;
	CMusicStreamMap					m_MusicStreamMap;

	//��������
public:
	//���캯��
	CD3DSound();
	//��������
	virtual ~CD3DSound();

	//���ܺ���
public:
	//��������
	bool CreateD3DSound(HWND hWnd);

	//��������
public:
	//��������
	HSTREAM LoadSound(LPCTSTR pszFileName, bool bRepetition);
	//��������
	HSTREAM LoadSound(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, bool bRepetition);
	//��������
	HCHANNEL PlaySound(HSTREAM hStream);
	//��������
	HCHANNEL StopSound(HSTREAM hStream);
	//ɾ������
	void FreeSound(HSTREAM hStream);
	//�������� 0~100
	void SetMusVolume(DWORD dwVolume);
	//��ȡ����
	DWORD GetMusVolume();

	//ͨ������
public:
	//��ͣ����
	void Channel_Pause(HCHANNEL hChannel);
	//��������
	void Channel_Resume(HCHANNEL hChannel);
	//ֹͣ����
	void Channel_Stop(HCHANNEL hChannel);
	//���ڲ���
	bool Channel_IsPlaying(HCHANNEL hChannel);
	//��ȡ��С
	double Channel_GetLength(HCHANNEL hChannel);
	//��ȡλ��
	double Channel_GetPos(HCHANNEL hChannel);
	//����λ��
	void Channel_SetPos(HCHANNEL hChannel, double dSeconds);
	//��ͣ����
	void Channel_PauseAll();
	//��������
	void Channel_ResumeAll();
	//ֹͣ����
	void Channel_StopAll();

	//��̬����
public:
	//��ȡ����
	static CD3DSound * GetInstance();
};

#define D3DSound	CD3DSound::GetInstance()
//////////////////////////////////////////////////////////////////////////////////

#endif