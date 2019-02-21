#ifndef MSG_EVENT_HEAD_FILE
#define MSG_EVENT_HEAD_FILE

#pragma once

class cCObject
{
public:
	cCObject(){}
	virtual ~cCObject(){}
};

typedef void (cCObject::*ButtonHandler)();
typedef void (cCObject::*SliderHandler)(INT);

#define Button_selector(_SELECTOR) (ButtonHandler)(&_SELECTOR)
#define Slider_selector(_SELECTOR) (SliderHandler)(&_SELECTOR)

//�¼�����
//////////////////////////////////////////////////////////////////////////
class GAME_ENGINE_CLASS CMsgEvent : public cCObject
{
protected:
	ButtonHandler					m_pfnBtSelector;
	SliderHandler					m_pfnSdSelector;

	cCObject *						m_pListener;

public:
	CMsgEvent(void)
	{
		m_pfnBtSelector = NULL;
		m_pfnSdSelector = NULL;
		m_pListener = NULL;
	}

	~CMsgEvent(void){}

public:
	//�����¼�
	void SetEvent(cCObject *rec, ButtonHandler selector)
	{
		m_pListener = rec;
		m_pfnBtSelector = selector;
	}

	//�����¼�
	void SetEvent(cCObject *rec, SliderHandler selector)
	{
		m_pListener = rec;
		m_pfnSdSelector = selector;
	}

	//����¼�
	void OnEventClicked()
	{
		if (m_pListener && m_pfnBtSelector)
		{
			(m_pListener->*m_pfnBtSelector)();
		}
	}

	//�����¼�
	void OnEventSlider(INT nValue)
	{
		if (m_pListener && m_pfnSdSelector)
		{
			(m_pListener->*m_pfnSdSelector)(nValue);
		}
	}

};

#endif