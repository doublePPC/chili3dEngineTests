#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"

struct baseTechsCBuf
{
	DirectX::XMFLOAT4 tintColor;
	DirectX::XMFLOAT3 discardColor;
	float discardRange;
	DirectX::XMINT3 techCode;
	float globalTransparency;
};

struct tintTechCBuf
{
	DirectX::XMFLOAT4 color;
	int techCode;
	float globalTransparency;
	DirectX::XMFLOAT2 padding;
};

struct fadingTechCBuf
{
	DirectX::XMFLOAT3 backgroundColor;
	float globalTransparency;
};