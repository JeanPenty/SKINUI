#include "StdAfx.h"
#include "NumberString.h"

CNumberString::CNumberString(void)
{
}

CNumberString::~CNumberString(void)
{
}

//�滭����
VOID CNumberString::DrawNumberString(CD3DDevice * pD3DDevice, CD3DTexture * pD3DTexture, LONG lNumber, INT nXPos, INT nYPos)
{
	if ( !Check_Image(pD3DTexture) ) return;

	//��ȡ��С
	CSize SizeNumber;
	SizeNumber.SetSize(pD3DTexture->GetWidth()/10,pD3DTexture->GetHeight());

	//��������
	LONG lNumberCount=0;
	LONG lNumberTemp=lNumber;

	//������Ŀ
	do
	{
		lNumberCount++;
		lNumberTemp/=10L;
	} while (lNumberTemp>0);

	//λ�ö���
	INT nYDrawPos=nYPos-SizeNumber.cy/2;
	INT nXDrawPos=nXPos+lNumberCount*SizeNumber.cx/2-SizeNumber.cx;

	//�滭����
	for (LONG i=0;i<lNumberCount;i++)
	{
		//�滭����
		LONG lCellNumber=lNumber%10L;
		pD3DTexture->DrawImage(pD3DDevice,nXDrawPos,nYDrawPos,SizeNumber.cx,SizeNumber.cy,lCellNumber*SizeNumber.cx,0);

		//���ñ���
		lNumber/=10;
		nXDrawPos-=SizeNumber.cx;
	};

	return;
}