#pragma once

class CNumberString
{
public:
	CNumberString(void);
	~CNumberString(void);

	//���ܺ���
public:
	//�滭����
	VOID DrawNumberString(CD3DDevice * pD3DDevice, CD3DTexture * pD3DTexture, LONG lNumber, INT nXPos, INT nYPos);
};
