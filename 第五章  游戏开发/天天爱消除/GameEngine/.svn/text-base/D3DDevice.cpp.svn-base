#include "stdafx.h"
#include "D3DDevice.h"
#include "D3DDirect.h"
#include "D3DTexture.h"
#include "D3DSprite.h"
#include "D3DFont.h"

CD3DDevice::CD3DDevice()
{
	//窗口属性
	m_hWndDevice = NULL;					
	m_SizeWindow.SetSize(0,0);					

	//接口变量
	m_pID3DDeviceSink=NULL;				
	m_pIDirect3DDevice=NULL;

	//帧数统计
	m_dwDrawBenchmark=0;
	m_dwDrawLastCount=0;
	m_dwDrawCurrentCount=0L;
}

CD3DDevice::~CD3DDevice()
{

}

bool CD3DDevice::ResetD3DDevice()
{
	CD3DSprite::OnDeviceLost(this);
	CD3DFont::OnDeviceLost(this);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof d3dpp);

	CRect rcClient;
	::GetClientRect(m_hWndDevice,&rcClient);
	InitPresentParameters(d3dpp,m_hWndDevice,rcClient.Width(),rcClient.Height(),D3DFMT_A8R8G8B8/*DisplayMode.Format*/);

	HRESULT hResult = m_pIDirect3DDevice->Reset(&d3dpp);

	if( FAILED( hResult ) ) 
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("Reset D3D failed"));
		return false;
	}
	
	CD3DSprite::OnDeviceReset(this);
	CD3DFont::OnDeviceReset(this);

	m_pIDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	TraceService->TraceString(TraceLevel_Normal,TEXT("Reset D3D success"));

	return true;
}

bool CD3DDevice::RenderD3DDevice()
{
	ASSERT(m_pIDirect3DDevice != NULL);
	if ( m_pIDirect3DDevice == NULL ) return false;

	ASSERT(m_pID3DDeviceSink != NULL);
	if ( m_pID3DDeviceSink == NULL ) return false;

	m_pIDirect3DDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(100,100,100),1.0f,0);
	
	//注意这里，当窗口最小化后，设备会发生丢失，像字体，精灵这种类型的会因为设备丢失产生异常，所以在绘制前需要进行判断
	if( SUCCEEDED( m_pIDirect3DDevice->BeginScene() ) )
	{
		m_pID3DDeviceSink->OnRenderWindow(this,m_SizeWindow.cx,m_SizeWindow.cy);

		m_pIDirect3DDevice->EndScene();
	}
	
	HRESULT hResult = m_pIDirect3DDevice->Present(NULL,NULL,NULL,NULL);
	
	if(hResult == D3DERR_DEVICELOST)
	{
		if(m_pIDirect3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ResetD3DDevice();
		}
	}

	return true;
}

bool CD3DDevice::CreateD3DDevice( HWND hWndDevice, ID3DDeviceSink * pID3DDeviceSink )
{
	m_pID3DDeviceSink = pID3DDeviceSink;
	m_hWndDevice = hWndDevice;

	CD3DDirect *pD3DDirect = CD3DDirect::GetInstance();

	D3DDISPLAYMODE DisplayMode;
	ZeroMemory(&DisplayMode,sizeof DisplayMode);
	pD3DDirect->GetDisplayMode(DisplayMode);

	TraceService->TraceString(TraceLevel_Normal,TEXT("Current mode:%d*%d"),DisplayMode.Width,DisplayMode.Height);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Refresh Rate:%d"),DisplayMode.RefreshRate);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Format:%d\n"),DisplayMode.Format);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof d3dpp);

	CRect rcClient;
	::GetClientRect(hWndDevice,&rcClient);
	InitPresentParameters(d3dpp,hWndDevice,rcClient.Width(),rcClient.Height(),D3DFMT_A8R8G8B8/*DisplayMode.Format*/);

	if( FAILED( pD3DDirect->m_pIDirect3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWndDevice,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &m_pIDirect3DDevice ) ) )
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("CreateDevice 【D3DDEVTYPE_HAL】 failed"));

		if( FAILED( pD3DDirect->m_pIDirect3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWndDevice,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &m_pIDirect3DDevice ) ) )
		{
			TraceService->TraceString(TraceLevel_Warning,TEXT("CreateDevice 【D3DDEVTYPE_REF】 failed"));

			return false;
		}
	}

	TraceService->TraceString(TraceLevel_Normal,TEXT("Device successfully created"));

	InitD3DDevice();

	return true;
}

HRESULT CD3DDevice::SetRenderState( D3DRENDERSTATETYPE State, DWORD Value )
{
	ASSERT(m_pIDirect3DDevice != NULL);
	if ( m_pIDirect3DDevice == NULL ) return S_FALSE;

	return m_pIDirect3DDevice->SetRenderState( State,  Value );
}

HRESULT CD3DDevice::GetRenderState( D3DRENDERSTATETYPE State, DWORD & Value )
{
	ASSERT(m_pIDirect3DDevice != NULL);
	if ( m_pIDirect3DDevice == NULL ) return S_FALSE;

	return m_pIDirect3DDevice->GetRenderState( State,  &Value );
}

VOID CD3DDevice::FillRect( CRect rcRect, D3DCOLOR D3DColor )
{
	tagD3DXCOLORVertex vertices[4] =
	{
		( float )rcRect.left  - 0.5f, ( float )rcRect.top - 0.5f,    0.5f,	1.0f, D3DColor,
		( float )rcRect.right - 0.5f, ( float )rcRect.top - 0.5f,    0.5f,	1.0f, D3DColor,
		( float )rcRect.right - 0.5f, ( float )rcRect.bottom - 0.5f, 0.5f,	1.0f, D3DColor,
		( float )rcRect.left  - 0.5f, ( float )rcRect.bottom - 0.5f, 0.5f,	1.0f, D3DColor
	};

	IDirect3DVertexDeclaration9* pDecl = NULL;
	m_pIDirect3DDevice->GetVertexDeclaration( &pDecl ); 
	m_pIDirect3DDevice->SetFVF( D3DFVF_COLOR );

	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

	m_pIDirect3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, vertices, sizeof( tagD3DXCOLORVertex ) );

	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	m_pIDirect3DDevice->SetVertexDeclaration( pDecl );

	SafeRelease(pDecl);
} 

VOID CD3DDevice::FillRect( INT nXPos, INT nYPos, INT nWidth, INT nHeigth, D3DCOLOR D3DColor )
{
	CRect rcRect(nXPos,nYPos,nXPos+nWidth,nYPos+nHeigth);

	FillRect(rcRect,D3DColor);
}

VOID CD3DDevice::DrawRect( CRect rcRect, D3DCOLOR D3DColor )
{
	tagD3DXCOLORVertex vertices[5] =
	{
		( float )rcRect.left  - 0.5f, ( float )rcRect.top - 0.5f,    0.5f,	1.0f,	D3DColor,
		( float )rcRect.right - 0.5f, ( float )rcRect.top - 0.5f,    0.5f,	1.0f,	D3DColor,
		( float )rcRect.right - 0.5f, ( float )rcRect.bottom - 0.5f, 0.5f,	1.0f,	D3DColor,
		( float )rcRect.left  - 0.5f, ( float )rcRect.bottom - 0.5f, 0.5f,	1.0f,	D3DColor,
		( float )rcRect.left  - 0.5f, ( float )rcRect.top - 0.5f,    0.5f,	1.0f,	D3DColor
	};

	IDirect3DVertexDeclaration9* pDecl = NULL;
	m_pIDirect3DDevice->GetVertexDeclaration( &pDecl ); 
	m_pIDirect3DDevice->SetFVF( D3DFVF_COLOR );

	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

	m_pIDirect3DDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, 4, vertices, sizeof( tagD3DXCOLORVertex ) );

	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	m_pIDirect3DDevice->SetVertexDeclaration( pDecl );

	SafeRelease(pDecl);

	return;
}

VOID CD3DDevice::DrawPolyLine(POINT* apPoints, UINT nNumPoints, D3DCOLOR D3DColor)
{
	tagD3DXCOLORVertex* vertices = new tagD3DXCOLORVertex[ nNumPoints ];
	
	if( vertices == NULL ) return;

	tagD3DXCOLORVertex* pVertex = vertices;
	POINT* pt = apPoints;
	for( UINT i = 0; i < nNumPoints; i++ )
	{
		pVertex->x = ( float )pt->x;
		pVertex->y = ( float )pt->y;
		pVertex->z = 0.5f;
		pVertex->h = 1.0f;
		pVertex->color = D3DColor;

		pVertex++;
		pt++;
	}

	IDirect3DVertexDeclaration9* pDecl = NULL;
	m_pIDirect3DDevice->GetVertexDeclaration( &pDecl ); 
	m_pIDirect3DDevice->SetFVF( D3DFVF_COLOR );

	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

	m_pIDirect3DDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, nNumPoints - 1, vertices, sizeof( tagD3DXCOLORVertex ) );

	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	m_pIDirect3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	m_pIDirect3DDevice->SetVertexDeclaration( pDecl );

	SafeRelease(pDecl);

	SafeDeleteArray( vertices );
}

VOID CD3DDevice::DrawLine( INT nXPos1, INT nYPos1, INT nXPos2, INT nYPos2, D3DCOLOR D3DColor )
{
	POINT mVertPoly [] = { {nXPos1, nYPos1}, {nXPos2, nYPos2} };

	DrawPolyLine(mVertPoly,2,D3DColor);
}

VOID CD3DDevice::InitD3DDevice()
{
	ASSERT(m_pID3DDeviceSink != NULL);
	if ( m_pID3DDeviceSink == NULL ) return;

	m_pID3DDeviceSink->OnInitDevice(this,m_SizeWindow.cx,m_SizeWindow.cy);

	m_pIDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

VOID CD3DDevice::InitPresentParameters( D3DPRESENT_PARAMETERS & PresentParameters, HWND hWnd, INT nWidth, INT nHeight, D3DFORMAT BufferFormat )
{
	D3DDISPLAYMODE DisplayMode;
	CD3DDirect::GetInstance()->GetDisplayMode(DisplayMode);

	m_SizeWindow.SetSize(nWidth,nHeight);

	//if ( nWidth >0 ||  nHeight > 0)
	{
		PresentParameters.Windowed = TRUE;
// 		PresentParameters.BackBufferWidth = nWidth;
// 		PresentParameters.BackBufferHeight = nHeight;
	}
// 	else
// 	{
// 		PresentParameters.Windowed = FALSE;
// 		PresentParameters.BackBufferWidth=DisplayMode.Width;
// 		PresentParameters.BackBufferHeight=DisplayMode.Height;
// 	}

	PresentParameters.SwapEffect       = D3DSWAPEFFECT_COPY;
	PresentParameters.BackBufferFormat = BufferFormat;
	PresentParameters.BackBufferCount=1;
	PresentParameters.hDeviceWindow = hWnd; 	
	PresentParameters.PresentationInterval   = D3DPRESENT_INTERVAL_DEFAULT;
 	PresentParameters.Flags                  = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
}

DWORD CD3DDevice::CalcFPS()
{
	//设置变量
	m_dwDrawCurrentCount++;

	//累计判断
	if ((GetTickCount()-m_dwDrawBenchmark)>=1000L)
	{
		//设置变量
		m_dwDrawLastCount=m_dwDrawCurrentCount;

		//统计还原
		m_dwDrawCurrentCount=0L;
		m_dwDrawBenchmark=GetTickCount();
	}

	return m_dwDrawLastCount;
}

