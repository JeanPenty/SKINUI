#include "stdafx.h"
#include "D3DTexture.h"

CD3DTexture::CD3DTexture()
{
	m_ImageSize.SetSize(0,0);
	m_MemorySize.SetSize(0,0);

	m_pITexture = NULL;
	m_pIVertexBuffer = NULL;
}

CD3DTexture::~CD3DTexture()
{
	Destory();
}

bool CD3DTexture::IsNull()
{
	return m_pITexture ? false : true;
}

bool CD3DTexture::Destory()
{
	SafeRelease(m_pITexture);
	SafeRelease(m_pIVertexBuffer);
	
	return true;
}

bool CD3DTexture::CreateImage( CD3DDevice * pD3DDevice, INT nWidth, INT nHeight )
{
	HRESULT hResult = D3DXCreateTexture(pD3DDevice->GetDirect3DDevice(),nWidth,nHeight,0,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&m_pITexture);

	if ( FAILED(hResult) ) 
	{
		return false;
	}

	return true;
}

bool CD3DTexture::LoadImage( CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName,DWORD dwColorKey/*=0*/ )
{
	//加载判断
	ASSERT(m_pITexture==NULL);
	if (m_pITexture!=NULL) return false;

	tagResourceInfo ResourceInfo;
	ZeroMemory(&ResourceInfo,sizeof ResourceInfo);

	GetResourceInfo(hInstance,pszResource,pszTypeName,ResourceInfo);
	
	D3DXIMAGE_INFO ImageInfo;  

	D3DFORMAT fmt1, fmt2;

	if(*(DWORD*)ResourceInfo.pcbBuffer == 0x20534444) 
	{
		fmt1=D3DFMT_UNKNOWN;
		fmt2=D3DFMT_A8R8G8B8;
	}
	else
	{
		fmt1=D3DFMT_A8R8G8B8;
		fmt2=D3DFMT_UNKNOWN;
	}

 	if( FAILED( D3DXCreateTextureFromFileInMemoryEx(pD3DDevice->GetDirect3DDevice(), ResourceInfo.pcbBuffer, ResourceInfo.dwSize,D3DX_DEFAULT,D3DX_DEFAULT,1,0,
 		fmt1,D3DPOOL_MANAGED,D3DX_FILTER_NONE,D3DX_DEFAULT,dwColorKey,&ImageInfo,NULL,&m_pITexture) ) )
	{
		if( FAILED( D3DXCreateTextureFromFileInMemoryEx(pD3DDevice->GetDirect3DDevice(), ResourceInfo.pcbBuffer, ResourceInfo.dwSize,D3DX_DEFAULT,D3DX_DEFAULT,1,0,
			fmt2,D3DPOOL_MANAGED,D3DX_FILTER_NONE,D3DX_DEFAULT,dwColorKey,&ImageInfo,NULL,&m_pITexture) ) )
		{		
			TraceService->TraceString(TraceLevel_Warning,TEXT("[Texture] load Resource [ %s ] failed"),pszResource);

			return false;
		}
	}

	D3DSURFACE_DESC Desc;
	if(FAILED(m_pITexture->GetLevelDesc(0, &Desc))) return false;

	m_MemorySize.SetSize(Desc.Width,Desc.Height);
	m_ImageSize.SetSize(ImageInfo.Width,ImageInfo.Height);

	TraceService->TraceString(TraceLevel_Normal,TEXT("[Texture] load Resource [ %s ] success"),pszResource);

	return true;
}

bool CD3DTexture::LoadImage( CD3DDevice * pD3DDevice, LPCTSTR pszFileName,DWORD dwColorKey/*=0*/ )
{
	//加载判断
	ASSERT(m_pITexture==NULL);
	if (m_pITexture!=NULL) return false;

	D3DXIMAGE_INFO ImageInfo;  

	if( FAILED( D3DXCreateTextureFromFileEx(pD3DDevice->GetDirect3DDevice(),pszFileName,D3DX_DEFAULT,D3DX_DEFAULT,1,0,
		D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,D3DX_FILTER_NONE,D3DX_DEFAULT,dwColorKey,&ImageInfo,NULL,&m_pITexture) ) )
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("[Texture] load file [ %s ] failed"),pszFileName);
		return false;
	}

	D3DSURFACE_DESC Desc;
	if(FAILED(m_pITexture->GetLevelDesc(0, &Desc))) return false;

	m_MemorySize.SetSize(Desc.Width,Desc.Height);
	m_ImageSize.SetSize(ImageInfo.Width,ImageInfo.Height);

	TraceService->TraceString(TraceLevel_Normal,TEXT("[Texture] load file [ %s ] success"),pszFileName);

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
 	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
 	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
 	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE ); 

	SetProjectionMatrix(pD3DDevice);
	
	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,m_MemorySize.cx,m_MemorySize.cy);
	SetTexturePos(pD3DDevice,D3DTextureVertex,0,0,m_MemorySize.cx,m_MemorySize.cy);

	//创建顶点缓冲区---下方的DrawImage采用另外的方式进行图形绘制
	pDevice->CreateVertexBuffer( sizeof(D3DTextureVertex),
		D3DUSAGE_WRITEONLY, D3DFVF_TEXTURE,
		D3DPOOL_MANAGED, &m_pIVertexBuffer,NULL );
	
	//填充顶点缓冲区
	VOID* pVertices;
	m_pIVertexBuffer->Lock( 0, sizeof(D3DTextureVertex), (void**)&pVertices, 0 ) ;
	memcpy( pVertices, D3DTextureVertex, sizeof(D3DTextureVertex) );
	m_pIVertexBuffer->Unlock();
	
	pDevice->SetStreamSource( 0, m_pIVertexBuffer, 0, sizeof(tagD3DTextureVertex) );
	pDevice->SetFVF( D3DFVF_XYZ|D3DFVF_TEX1 );
	pDevice->SetTexture(0,m_pITexture);
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);
	
	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nDestWidth,nDestHeight);

	pDevice->SetTexture(0, m_pITexture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 /*_countof(D3DTextureVertex) - 2*/, D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();
	
	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

 	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
 	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nSourceWidth,nSourceHeight);

	pDevice->SetTexture(0, m_pITexture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 /*_countof(D3DTextureVertex) - 2*/, D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, BYTE cbAlpha )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, cbAlpha));

	pDevice->SetTextureStageState (0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState (0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState (0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,m_MemorySize.cx,m_MemorySize.cy);
	SetTexturePos(pD3DDevice,D3DTextureVertex,0,0,m_MemorySize.cx,m_MemorySize.cy);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	//恢复状态
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, 255));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, BYTE cbAlpha )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, cbAlpha));

	pDevice->SetTextureStageState (0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState (0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState (0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nDestWidth,nDestHeight);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	//恢复状态
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, 255));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, BYTE cbAlpha )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, cbAlpha));

	pDevice->SetTextureStageState (0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState (0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState (0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nSourceWidth,nSourceHeight);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	//恢复状态
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, 255));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE ); 

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,m_MemorySize.cx,m_MemorySize.cy);
	SetTexturePos(pD3DDevice,D3DTextureVertex,0,0,m_MemorySize.cx,m_MemorySize.cy);

	//设置参数
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);

	//最后的参数是图片的绘制位置
	D3DXMatrixTransformation2D(	&matView,NULL,1.0f,NULL,&D3DXVECTOR2((FLOAT)ptRotationOffset.x,(FLOAT)ptRotationOffset.y),fRadian*M_PI/180,NULL);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE ); 

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nDestWidth,nDestHeight);

	//设置参数
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);

	//最后的参数是图片的绘制位置
	D3DXMatrixTransformation2D(	&matView,NULL,1.0f,NULL,&D3DXVECTOR2((FLOAT)ptRotationOffset.x,(FLOAT)ptRotationOffset.y),fRadian*M_PI/180,NULL);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE ); 

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nSourceWidth,nSourceHeight);

	//设置参数
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);

	//最后的参数是图片的绘制位置
	D3DXMatrixTransformation2D(	&matView,NULL,1.0f,NULL,&D3DXVECTOR2((FLOAT)ptRotationOffset.x,(FLOAT)ptRotationOffset.y),fRadian*M_PI/180,NULL);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, BYTE cbAlpha )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, cbAlpha));

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,m_MemorySize.cx,m_MemorySize.cy);
	SetTexturePos(pD3DDevice,D3DTextureVertex,0,0,m_MemorySize.cx,m_MemorySize.cy);

	//设置参数
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);

	//最后的参数是图片的绘制位置
	D3DXMatrixTransformation2D(	&matView,NULL,1.0f,NULL,&D3DXVECTOR2((FLOAT)ptRotationOffset.x,(FLOAT)ptRotationOffset.y),fRadian*M_PI/180,NULL);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	//恢复状态
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, 255));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, BYTE cbAlpha )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, cbAlpha));

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nDestWidth,nDestHeight);

	//设置参数
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);

	//最后的参数是图片的绘制位置
	D3DXMatrixTransformation2D(	&matView,NULL,1.0f,NULL,&D3DXVECTOR2((FLOAT)ptRotationOffset.x,(FLOAT)ptRotationOffset.y),fRadian*M_PI/180,NULL);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	//恢复状态
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, 255));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, CPoint ptRotationOffset, FLOAT fRadian, CHAR chDirection, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, BYTE cbAlpha )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	//处理png透明色
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, cbAlpha));

	SetProjectionMatrix(pD3DDevice);

	pDevice->SetFVF(D3DFVF_TEXTURE);

	tagD3DTextureVertex D3DTextureVertex[4];
	ZeroMemory(&D3DTextureVertex,sizeof D3DTextureVertex);

	SetWindowPos(D3DTextureVertex,nXDest,nYDest,nDestWidth,nDestHeight);
	SetTexturePos(pD3DDevice,D3DTextureVertex,nXSource,nYSource,nSourceWidth,nSourceHeight);

	//设置参数
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);

	//最后的参数是图片的绘制位置
	D3DXMatrixTransformation2D(	&matView,NULL,1.0f,NULL,&D3DXVECTOR2((FLOAT)ptRotationOffset.x,(FLOAT)ptRotationOffset.y),fRadian*M_PI/180,NULL);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	pDevice->SetTexture(0, m_pITexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2 , D3DTextureVertex, sizeof(D3DTextureVertex[0]));

	//恢复状态
	pDevice->SetRenderState (D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA (255, 255, 255, 255));

	return true;
}

bool CD3DTexture::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, DWORD* dwData, INT nImageWidth, INT nImageHeight )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return false;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	tagD3DXCOLORVertex *pVertices = new tagD3DXCOLORVertex[nImageWidth*nImageHeight];

	for (int i=0;i<nImageWidth*nImageHeight;i++)
	{
		pVertices[i].color = D3DCOLOR_XRGB(GetRValue(dwData[i]),GetGValue(dwData[i]),GetBValue(dwData[i]));
		pVertices[i].x = nXDest+FLOAT(i%nImageWidth);
		pVertices[i].y = nYDest+FLOAT(i/nImageWidth);
		pVertices[i].z = 1.0f;
		pVertices[i].h = 1.0f;
	}

	IDirect3DVertexDeclaration9* pDecl = NULL;
	pDevice->GetVertexDeclaration( &pDecl ); 
	pDevice->SetFVF( D3DFVF_COLOR );

	pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );

	pDevice->DrawPrimitiveUP( D3DPT_POINTLIST, nImageWidth*nImageHeight, pVertices, sizeof( tagD3DXCOLORVertex ) );

	pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	pDevice->SetVertexDeclaration( pDecl );

	pDecl->Release();
	SafeDelete(pVertices);

	return true;
}

bool CD3DTexture::GetResourceInfo( HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, tagResourceInfo & ResourceInfo )
{
	//查找资源
	HRSRC hResource=FindResource(hInstance,pszResource,pszTypeName);
	if (hResource==NULL) return false;

	//读取资源
	ResourceInfo.dwSize=SizeofResource(hInstance,hResource);
	ResourceInfo.pcbBuffer=LoadResource(hInstance,hResource);

	return true;
}

VOID CD3DTexture::SetMatrix( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight )
{

}

VOID CD3DTexture::SetWindowPos( tagD3DTextureVertex * pTextureVertex, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight )
{
	ASSERT( pTextureVertex!= NULL );
	if ( pTextureVertex == NULL ) return;

	pTextureVertex[0].Position.x = (float)nXDest;  
	pTextureVertex[0].Position.y = (float)(nYDest+nDestHeight);  
	pTextureVertex[0].Position.z = 1.f;  

	pTextureVertex[1].Position.x = (float)nXDest;  
	pTextureVertex[1].Position.y = (float)nYDest;  
	pTextureVertex[1].Position.z = 1.f;  

	pTextureVertex[2].Position.x = (float)(nXDest+nDestWidth);  
	pTextureVertex[2].Position.y = (float)(nYDest+nDestHeight);  
	pTextureVertex[2].Position.z= 1.f;  

	pTextureVertex[3].Position.x = (float)(nXDest+nDestWidth);  
	pTextureVertex[3].Position.y = (float)nYDest;  
	pTextureVertex[3].Position.z = 1.f;  
}

VOID CD3DTexture::SetTexturePos( CD3DDevice * pD3DDevice, tagD3DTextureVertex * pTextureVertex, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	pTextureVertex[0].tu = (float)(nXSource / (float)m_MemorySize.cx);  
	pTextureVertex[0].tv = (float)((nYSource+nSourceHeight) / (float)m_MemorySize.cy);  

	pTextureVertex[1].tu = (float)(nXSource / (float)m_MemorySize.cx);  
	pTextureVertex[1].tv = (float)(nYSource / (float)m_MemorySize.cy);  

	pTextureVertex[2].tu = (float)((nXSource+nSourceWidth) / (float)m_MemorySize.cx);  
	pTextureVertex[2].tv = (float)((nYSource+nSourceHeight) / (float)m_MemorySize.cy);  

	pTextureVertex[3].tu = (float)((nXSource+nSourceWidth) / (float)m_MemorySize.cx);  
	pTextureVertex[3].tv = (float)(nYSource / (float)m_MemorySize.cy);  
}

void CD3DTexture::SetProjectionMatrix(  CD3DDevice * pD3DDevice )
{
	ASSERT( pD3DDevice!= NULL );
	if ( pD3DDevice == NULL ) return;

	IDirect3DDevice9 *pDevice = pD3DDevice->GetDirect3DDevice();

	D3DXMATRIX tmp,matProj,matView;
	D3DXMatrixScaling(&matProj, 1.0f, -1.0f, 1.0f);
	D3DXMatrixTranslation(&tmp, -0.5f, pD3DDevice->GetSizeWindow().cy+0.5f, 0.0f);
	D3DXMatrixMultiply(&matProj, &matProj, &tmp);
	D3DXMatrixOrthoOffCenterLH(&tmp, 0, (float)pD3DDevice->GetSizeWindow().cx, 0, (float)pD3DDevice->GetSizeWindow().cy, 0.0f, 1.0f);
	D3DXMatrixMultiply(&matProj, &matProj, &tmp);

	pDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixIdentity(&matView);
	pDevice->SetTransform(D3DTS_VIEW, &matView);
}