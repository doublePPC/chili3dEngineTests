#include "UI_Maths.h"

DirectX::XMFLOAT3 UI_Math::camFacing;
DirectX::XMFLOAT3 UI_Math::camPosition;
DirectX::XMFLOAT3 UI_Math::centerPoint;

void UI_Math::Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos)
{
	UI_Math::camFacing = camFace;
	UI_Math::camPosition = camPos;
	CalculateCenterPoint();
}

DirectX::XMFLOAT3 UI_Math::CalculatePosRelativeToScreen(DirectX::XMFLOAT4 elemData)
{
	DirectX::XMFLOAT3 position;
	// evaluate boundaries according to element's size
	float Xboundary = (1.0f - elemData.w) / 2.0f + 1.0f;
	float Xtranslation = elemData.x * Xboundary;
	float Yboundary = (1.0f - elemData.w) / 2.0f + (2.0f - elemData.w);
	float Ytranslation = elemData.y * Yboundary;

	// pitch angle modifiers
	float hypothenuse = sin(UI_Math::camFacing.y) * Ytranslation;
	float pitchYmod = cos(UI_Math::camFacing.y) * Ytranslation;
	float pitchXmod = sin(UI_Math::camFacing.z) * hypothenuse;
	float pitchZmod = cos(UI_Math::camFacing.z) * hypothenuse;

	// yaw angle modifiers
	float xFactor = Xtranslation * cos(UI_Math::camFacing.z);
	float zFactor = Xtranslation * sin(UI_Math::camFacing.z);

	position.x = UI_Math::centerPoint.x + xFactor + pitchXmod;
	position.y = UI_Math::centerPoint.y + pitchYmod;
	position.z = UI_Math::centerPoint.z - zFactor + pitchZmod;
	return position;
}

void UI_Math::CalculateCenterPoint()
{
	float hypothenuse = cos(UI_Math::camFacing.y);
	float xFactor = sin(UI_Math::camFacing.z) * hypothenuse;
	float zFactor = cos(UI_Math::camFacing.z) * hypothenuse;

	UI_Math::centerPoint.x = UI_Math::camPosition.x + xFactor;
	UI_Math::centerPoint.y = UI_Math::camPosition.y - sin(UI_Math::camFacing.y);
	UI_Math::centerPoint.z = UI_Math::camPosition.z + zFactor;
}
