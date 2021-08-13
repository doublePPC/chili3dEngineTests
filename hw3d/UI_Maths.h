#pragma once
#include "UI_Generics.h"

class UI_Math
{
public:
	static void Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos);
	static DirectX::XMFLOAT3 CalculatePosRelativeToScreen(DirectX::XMFLOAT4 elemData);
private:
	static void CalculateCenterPoint();
private:
	static DirectX::XMFLOAT3 camFacing;
	static DirectX::XMFLOAT3 camPosition;
	static DirectX::XMFLOAT3 centerPoint;
};