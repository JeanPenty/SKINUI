#include "StdAfx.h"
#include "ScoreView.h"

CScoreView::CScoreView(void)
{
	m_lGameScore = 0;
	m_pTextureBack = 0;
}

CScoreView::~CScoreView(void)
{
	DeleteWindow();
}

VOID CScoreView::OnWindowMovie()
{

}

VOID CScoreView::OnWindowCreate( CD3DDevice * pD3DDevice )
{
	SetCaption();

	//�رհ�ť
	cCRect rcCreate(0,0,0,0);
	m_btOK.ActiveWindow(rcCreate,WS_VISIBLE,2000,GetVirtualEngine(),this);

	m_btOK.SetButtonImage(TextureManager->InitWithTexture(pD3DDevice,AfxGetInstanceHandle(),TEXT("BT_CLOSE"),TEXT("PNG")));
	m_btOK.SetEvent(this,Button_selector(CScoreView::OnBnClickClose));

// 	m_VirtualSlider.ActiveWindow(rcCreate,WS_VISIBLE,3000,GetVirtualEngine(),this);
// 
// 	m_VirtualSlider.SetTexture(
// 		TextureManager->InitWithTexture(pD3DDevice,AfxGetInstanceHandle(),TEXT("SLIDER_BACK"),TEXT("PNG")),
// 		TextureManager->InitWithTexture(pD3DDevice,AfxGetInstanceHandle(),TEXT("SLIDER_CHANNEL"),TEXT("PNG")),
// 		TextureManager->InitWithTexture(pD3DDevice,AfxGetInstanceHandle(),TEXT("SLIDER_THUM"),TEXT("PNG"))
// 		);
// 
// 	m_VirtualSlider.SetWindowPos(0,100,0,0,SWP_NOSIZE);
// 	m_VirtualSlider.SetRange(0,100);
// 	m_VirtualSlider.SetPos(10);

	//������Դ
	m_TextureBack.LoadImage(pD3DDevice,AfxGetInstanceHandle(),TEXT("GAME_SCORE"),TEXT("PNG"));
	
	//��ȡ��С
	CSize SizeGameScore;
	SizeGameScore.SetSize(m_TextureBack.GetWidth(),m_TextureBack.GetHeight());

	//�ƶ�����
	SetWindowPos(0,0,SizeGameScore.cx,SizeGameScore.cy,0);

	//��ťλ��
	cCRect rcButton;
	m_btOK.GetWindowRect(rcButton);
	m_btOK.SetWindowPos(115,240,0,0,SWP_NOSIZE);
}

VOID CScoreView::OnWindowDestory( CD3DDevice * pD3DDevice )
{
	//������Դ
	if (m_TextureBack.IsNull()==false) m_TextureBack.Destory();
}

BOOL CScoreView::OnEventMouse( UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos )
{	
	BOOL bReturn = DragWindows(uMessage, nXMousePos, nYMousePos, nFlags);

	return bReturn;
}

BOOL CScoreView::OnEventKeyboard( UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	return FALSE;
}

VOID CScoreView::OnEventDrawWindow( CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos )
{
	//�滭����
	m_TextureBack.DrawImage(pD3DDevice,nXOriginPos,nYOriginPos);

	DrawNumberString(pD3DDevice,m_pTextureBack,m_lGameScore,nXOriginPos+175,nYOriginPos+85);
}

void CScoreView::OnBnClickClose()
{
	//�رմ���
	//DeleteWindow();
	ShowWindow(false);
}

void CScoreView::SetGameScore( LONG lGameScore,CD3DTexture * pD3DTexture )
{
	m_lGameScore = lGameScore;
	m_pTextureBack = pD3DTexture;
}

