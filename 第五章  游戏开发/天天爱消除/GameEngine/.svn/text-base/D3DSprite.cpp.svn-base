#include "stdafx.h"
#include "D3DSprite.h"

CD3DSpritePtrArray CD3DSprite::m_D3DSpritePtrArray;

CD3DSprite::CD3DSprite()
{
	m_fAngle = 0.0f;
	m_fRotationX = 0.0f;
	m_fRotationY = 0.0f;

	m_fScalingCenterX = 0.0f;	
	m_fScalingCenterY = 0.0f;	
	m_fScalingX = 1.0f;	
	m_fScalingY = 1.0f;	

	m_ImageSize.SetSize(0,0);
	m_MemorySize.SetSize(0,0);

	m_pISprite = NULL;
	m_pITexture = NULL;
}

CD3DSprite::~CD3DSprite()
{
	Destory();
}

bool CD3DSprite::IsNull()
{
	return m_pITexture ? false : true;
}

VOID CD3DSprite::SetRotation( FLOAT fRotationX, FLOAT fRotationY, FLOAT fAngle )
{
	m_fAngle = fAngle;		
	m_fRotationX = fRotationX;	
	m_fRotationY = fRotationY;	
}

VOID CD3DSprite::SetScaling( FLOAT fScalingCenterX,FLOAT fScalingCenterY,FLOAT fScalingX, FLOAT fScalingY )
{
	m_fScalingCenterX = fScalingCenterX;	
	m_fScalingCenterY = fScalingCenterY;	
	m_fScalingX = fScalingX;	
	m_fScalingY = fScalingY;	
}

bool CD3DSprite::Destory()
{
	SafeRelease(m_pISprite);
	SafeRelease(m_pITexture);

	for (INT_PTR i=0;i<m_D3DSpritePtrArray.GetCount();i++)
	{
		if ( m_D3DSpritePtrArray.GetAt(i) == this )
		{
			m_D3DSpritePtrArray.RemoveAt(i);
			break;
		}
	}

	return true;
}

bool CD3DSprite::CreateImage( CD3DDevice * pD3DDevice, INT nWidth, INT nHeight )
{
	D3DXCreateTexture(pD3DDevice->GetDirect3DDevice(),nWidth,nHeight,0,0,D3DFMT_A8B8G8R8,D3DPOOL_MANAGED,&m_pITexture);

	return true;
}

bool CD3DSprite::LoadImage( CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, DWORD dwColorKey )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pITexture==NULL);
	if (m_pITexture!=NULL) return false;

	//ªÒ»°–≈œ¢
	D3DXIMAGE_INFO ImageInfo; 

	//¥¥Ω®æ´¡È
	D3DXCreateSprite( pD3DDevice->GetDirect3DDevice(), &m_pISprite);

	HRESULT hResult = D3DXCreateTextureFromResourceEx(pD3DDevice->GetDirect3DDevice(), hInstance, pszResource,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,
		D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,dwColorKey,&ImageInfo,NULL,&m_pITexture);

	if(FAILED(hResult)) 
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("[Sprite] load Resource [ %s ] failed"),pszResource);

		SafeRelease(m_pISprite);
		SafeRelease(m_pITexture);

		return false;
	}

	if(m_pISprite==NULL||m_pITexture==NULL)
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("[Sprite] load Resource [ %s ] failed"),pszResource);

		SafeRelease(m_pISprite);
		SafeRelease(m_pITexture);

		return false;
	}

	m_ImageSize.SetSize(ImageInfo.Width,ImageInfo.Height);
	m_D3DSpritePtrArray.Add(this);

	TraceService->TraceString(TraceLevel_Normal,TEXT("[Sprite] load Resource [ %s ] success"),pszResource);

	return true;
}

bool CD3DSprite::LoadImage( CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pITexture==NULL);
	if (m_pITexture!=NULL) return false;

	tagResourceInfo ResourceInfo;
	ZeroMemory(&ResourceInfo,sizeof ResourceInfo);

	GetResourceInfo(hInstance,pszResource,pszTypeName,ResourceInfo);

	//ªÒ»°–≈œ¢
	D3DXIMAGE_INFO ImageInfo;  

	//¥¥Ω®æ´¡È
	D3DXCreateSprite( pD3DDevice->GetDirect3DDevice(), &m_pISprite);

	HRESULT hResult = D3DXCreateTextureFromFileInMemoryEx(pD3DDevice->GetDirect3DDevice(), ResourceInfo.pcbBuffer, ResourceInfo.dwSize,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,
		D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,0,&ImageInfo,NULL,&m_pITexture);

	if(FAILED(hResult)) 
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("[Sprite] load Memory [ %s ] failed"),pszResource);
		SafeRelease(m_pISprite);
		SafeRelease(m_pITexture);

		return false;
	}

	if(m_pISprite==NULL||m_pITexture==NULL)
	{
		TraceService->TraceString(TraceLevel_Warning,TEXT("[Sprite] load Memory [ %s ] failed"),pszResource);
		SafeRelease(m_pISprite);
		SafeRelease(m_pITexture);

		return false;
	}

	m_ImageSize.SetSize(ImageInfo.Width,ImageInfo.Height);
	m_D3DSpritePtrArray.Add(this);

	TraceService->TraceString(TraceLevel_Normal,TEXT("[Sprite] load Memory [ %s ] success"),pszResource);

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pISprite!=NULL);
	ASSERT(m_pITexture!=NULL);

	if (m_pISprite==NULL) return false;
	if (m_pITexture==NULL) return false;

	//…Ë÷√æÿ’Û
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTransformation2D(	&matWorld,&D3DXVECTOR2(m_fScalingCenterX,m_fScalingCenterY),0,&D3DXVECTOR2(m_fScalingX,m_fScalingY),&D3DXVECTOR2((float)m_fRotationX,(float)m_fRotationY),m_fAngle,&D3DXVECTOR2((float)nXDest,(float)nYDest));
	m_pISprite->SetTransform(&matWorld);

	//ªÊª≠Œª÷√
	m_pISprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pISprite->Draw(m_pITexture, CRect(0,0,m_ImageSize.cx,m_ImageSize.cy), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),0xFFFFFFFF);
	m_pISprite->Flush();
	m_pISprite->End();

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pISprite!=NULL);
	ASSERT(m_pITexture!=NULL);

	if (m_pISprite==NULL) return false;
	if (m_pITexture==NULL) return false;

	//…Ë÷√æÿ’Û
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTransformation2D(	&matWorld,&D3DXVECTOR2(m_fScalingCenterX,m_fScalingCenterY),0,&D3DXVECTOR2(m_fScalingX,m_fScalingY),&D3DXVECTOR2((float)m_fRotationX,(float)m_fRotationY),m_fAngle,&D3DXVECTOR2((float)nXDest,(float)nYDest));
	m_pISprite->SetTransform(&matWorld);

	//ªÊª≠Œª÷√
	m_pISprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pISprite->Draw(m_pITexture, CRect(nXSource,nYSource,nXSource+nDestWidth,nYSource+nDestHeight), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),0xFFFFFFFF);
	m_pISprite->Flush();
	m_pISprite->End();

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pISprite!=NULL);
	ASSERT(m_pITexture!=NULL);

	if (m_pISprite==NULL) return false;
	if (m_pITexture==NULL) return false;

	//…Ë÷√æÿ’Û
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTransformation2D(	&matWorld,&D3DXVECTOR2(m_fScalingCenterX,m_fScalingCenterY),0,&D3DXVECTOR2(m_fScalingX,m_fScalingY),&D3DXVECTOR2((float)m_fRotationX,(float)m_fRotationY),m_fAngle,&D3DXVECTOR2((float)nXDest,(float)nYDest));
	m_pISprite->SetTransform(&matWorld);

	//ªÊª≠Œª÷√
	m_pISprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pISprite->Draw(m_pITexture, CRect(nXSource,nYSource,nXSource+nSourceWidth,nYSource+nSourceHeight), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),0xFFFFFFFF);
	m_pISprite->Flush();
	m_pISprite->End();

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, D3DCOLOR Color )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pISprite!=NULL);
	ASSERT(m_pITexture!=NULL);

	if (m_pISprite==NULL) return false;
	if (m_pITexture==NULL) return false;

	//…Ë÷√æÿ’Û
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTransformation2D(	&matWorld,&D3DXVECTOR2(m_fScalingCenterX,m_fScalingCenterY),0,&D3DXVECTOR2(m_fScalingX,m_fScalingY),&D3DXVECTOR2((float)m_fRotationX,(float)m_fRotationY),m_fAngle,&D3DXVECTOR2((float)nXDest,(float)nYDest));
	m_pISprite->SetTransform(&matWorld);

	//ªÊª≠Œª÷√
	m_pISprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pISprite->Draw(m_pITexture, CRect(nXDest,nYDest,nXDest+m_ImageSize.cx,nYDest+m_ImageSize.cy), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),Color);
	m_pISprite->Flush();
	m_pISprite->End();

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, D3DCOLOR Color )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pISprite!=NULL);
	ASSERT(m_pITexture!=NULL);

	if (m_pISprite==NULL) return false;
	if (m_pITexture==NULL) return false;

	//…Ë÷√æÿ’Û
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTransformation2D(	&matWorld,&D3DXVECTOR2(m_fScalingCenterX,m_fScalingCenterY),0,&D3DXVECTOR2(m_fScalingX,m_fScalingY),&D3DXVECTOR2((float)m_fRotationX,(float)m_fRotationY),m_fAngle,&D3DXVECTOR2((float)nXDest,(float)nYDest));
	m_pISprite->SetTransform(&matWorld);

	//ªÊª≠Œª÷√
	m_pISprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pISprite->Draw(m_pITexture, CRect(nXSource,nYSource,nXSource+nDestWidth,nYSource+nDestHeight), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),Color);
	m_pISprite->Flush();
	m_pISprite->End();

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, D3DCOLOR Color )
{
	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, BYTE cbAlpha )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pISprite!=NULL);
	ASSERT(m_pITexture!=NULL);

	if (m_pISprite==NULL) return false;
	if (m_pITexture==NULL) return false;

	//…Ë÷√æÿ’Û
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTransformation2D(	&matWorld,&D3DXVECTOR2(m_fScalingCenterX,m_fScalingCenterY),0,&D3DXVECTOR2(m_fScalingX,m_fScalingY),&D3DXVECTOR2((float)m_fRotationX,(float)m_fRotationY),m_fAngle,&D3DXVECTOR2((float)nXDest,(float)nYDest));
	m_pISprite->SetTransform(&matWorld);

	//ªÊª≠Œª÷√
	m_pISprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pISprite->Draw(m_pITexture, CRect(0,0,m_ImageSize.cx,m_ImageSize.cy), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),D3DCOLOR_ARGB(cbAlpha,255,255,255));
	m_pISprite->Flush();
	m_pISprite->End();

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, BYTE cbAlpha )
{
	//º”‘ÿ≈–∂œ
	ASSERT(m_pISprite!=NULL);
	ASSERT(m_pITexture!=NULL);

	if (m_pISprite==NULL) return false;
	if (m_pITexture==NULL) return false;

	//…Ë÷√æÿ’Û
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTransformation2D(	&matWorld,&D3DXVECTOR2(m_fScalingCenterX,m_fScalingCenterY),0,&D3DXVECTOR2(m_fScalingX,m_fScalingY),&D3DXVECTOR2((float)m_fRotationX,(float)m_fRotationY),m_fAngle,&D3DXVECTOR2((float)nXDest,(float)nYDest));
	m_pISprite->SetTransform(&matWorld);

	//ªÊª≠Œª÷√
	m_pISprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pISprite->Draw(m_pITexture, CRect(nXSource,nYSource,nXSource+nDestWidth,nYSource+nDestHeight), &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),D3DCOLOR_ARGB(cbAlpha,255,255,255));
	m_pISprite->Flush();
	m_pISprite->End();

	return true;
}

bool CD3DSprite::DrawImage( CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, BYTE cbAlpha )
{
	return true;
}

bool CD3DSprite::GetResourceInfo( HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, tagResourceInfo & ResourceInfo )
{
	//≤È’“◊ ‘¥
	HRSRC hResource=FindResource(hInstance,pszResource,pszTypeName);
	if (hResource==NULL) return false;

	//∂¡»°◊ ‘¥
	ResourceInfo.dwSize=SizeofResource(hInstance,hResource);
	ResourceInfo.pcbBuffer=LoadResource(hInstance,hResource);

	return true;
}

VOID CD3DSprite::OnDeviceLost( CD3DDevice * pD3DDevice )
{
 	//º”‘ÿ≈–∂œ
 	ASSERT(pD3DDevice!=NULL);
 	if (pD3DDevice==NULL) return;
 
	for (INT_PTR i=0;i<m_D3DSpritePtrArray.GetCount();i++)
	{
		m_D3DSpritePtrArray.GetAt(i)->m_pISprite->OnLostDevice();
	}
}

VOID CD3DSprite::OnDeviceReset( CD3DDevice * pD3DDevice )
{
 	//º”‘ÿ≈–∂œ
 	ASSERT(pD3DDevice!=NULL);
 	if (pD3DDevice==NULL) return;
 
	for (INT_PTR i=0;i<m_D3DSpritePtrArray.GetCount();i++)
	{
		m_D3DSpritePtrArray.GetAt(i)->m_pISprite->OnResetDevice();
	}
}
