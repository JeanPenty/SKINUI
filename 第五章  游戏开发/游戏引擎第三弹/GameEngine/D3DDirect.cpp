#include "stdafx.h"
#include "D3DDirect.h"

CD3DDirect * CD3DDirect::m_pD3DDirect = NULL;

CD3DDirect::CD3DDirect()
{
	m_pIDirect3D = NULL;

	m_pD3DDirect = this;
}

CD3DDirect::~CD3DDirect()
{
	SafeRelease(m_pIDirect3D);	
}

bool CD3DDirect::CreateD3DDirect()
{
	m_pIDirect3D = Direct3DCreate9( D3D_SDK_VERSION );

	if ( m_pIDirect3D == NULL ) 
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("Direct3DCreate9 failed"));
		return false;
	}
	
	D3DADAPTER_IDENTIFIER9 ident;
	m_pIDirect3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &ident);

	TraceService->TraceString(TraceLevel_Normal,TEXT("Device information"));

#ifdef _UNICODE
	TCHAR szBuffer[MAX_PATH];

	MultiByteToWideChar(CP_ACP,	0,ident.Description,-1,szBuffer,MAX_PATH);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Device:%s"),szBuffer);

	MultiByteToWideChar(CP_ACP,	0,ident.DeviceName,-1,szBuffer,MAX_PATH);
	TraceService->TraceString(TraceLevel_Normal,TEXT("DeviceName:%s"),szBuffer);

	MultiByteToWideChar(CP_ACP,	0,ident.Driver,-1,szBuffer,MAX_PATH);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Driver:%s"),szBuffer);
#else
	TraceService->TraceString(TraceLevel_Normal,TEXT("Device:%s"),ident.Description);
	TraceService->TraceString(TraceLevel_Normal,TEXT("DeviceName:%s"),ident.DeviceName);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Driver:%s"),ident.Driver);
#endif

	TraceService->TraceString(TraceLevel_Normal,TEXT("Revision:%ld"),ident.Revision);
	TraceService->TraceString(TraceLevel_Normal,TEXT("Device ID:%ld\n"),ident.DeviceId);

	TraceService->TraceString(TraceLevel_Normal,TEXT("Device capabilities"));

	return true;
}

bool CD3DDirect::GetDeviceCaps( D3DCAPS9 & D3DCaps )
{	
	assert( m_pIDirect3D!= NULL );
	if( m_pIDirect3D == NULL ) return false;

	HRESULT hResult = m_pIDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &D3DCaps);

	if ( hResult != D3D_OK )return false;

	return true;
}

bool CD3DDirect::GetDisplayMode( D3DDISPLAYMODE & DisplayMode )
{
	assert( m_pIDirect3D!= NULL );
	if( m_pIDirect3D == NULL ) return false;

	HRESULT hResult = m_pIDirect3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &DisplayMode );

	if(FAILED(hResult)) return false;

	return true;
}
