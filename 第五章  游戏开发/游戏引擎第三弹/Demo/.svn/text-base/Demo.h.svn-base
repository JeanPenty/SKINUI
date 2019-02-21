#pragma once

class CGameEngine : public CWindowImpl
{
protected:
	CVirtualButton			m_btStart;

public:
	CGameEngine();

	//界面函数
private:
	//配置界面
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//重载函数
protected:
	//默认回调
	virtual LRESULT WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );

protected:
	//开始事件
	void OnStartGame();
};
