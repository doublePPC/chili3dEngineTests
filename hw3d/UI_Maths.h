#pragma once
#include "UI_Generics.h"

class UI_Math
{
public:
	static void Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos);
	static DirectX::XMFLOAT3 CalculatePosRelativeToScreen(DirectX::XMFLOAT4 elemData);
	static DirectX::XMFLOAT3 CalculatePosRelativeToParent(DirectX::XMFLOAT4 parentData, DirectX::XMFLOAT4 elemData);

	static DirectX::XMFLOAT3 GetUI_Facing();
private:
	static void CalculateCenterPoint();
	static void CalculateUI_Facing();
private:
	static DirectX::XMFLOAT3 camFacing;
	static DirectX::XMFLOAT3 camPosition;
	static DirectX::XMFLOAT3 centerPoint;
	static DirectX::XMFLOAT3 ui_facing;
};