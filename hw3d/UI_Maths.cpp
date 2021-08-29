#include "UI_Maths.h"

DirectX::XMFLOAT3 UI_Math::camFacing;
DirectX::XMFLOAT3 UI_Math::camPosition;
DirectX::XMFLOAT3 UI_Math::centerPoint;
DirectX::XMFLOAT3 UI_Math::ui_facing;

void UI_Math::Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos)
{
	UI_Math::camFacing = camFace;
	UI_Math::camPosition = camPos;
	CalculateCenterPoint();
	CalculateUI_Facing();
}

DirectX::XMFLOAT3 UI_Math::CalculatePosRelativeToScreen(PosAndSizeData elemData)
{
	// evaluate boundaries according to element's size
	//float Xboundary = (1.0f - elemData.w) / 2.0f + 0.75f ;
	float Xboundary = 1.0f - elemData.size.width / 4.0f;
	float Xtranslation = elemData.relPos.x * Xboundary;
	//float Yboundary = (1.0f - elemData.w) / 2.0f + (2.0f - elemData.w);
	float Yboundary = 2.0f - elemData.size.height;
	float Ytranslation = elemData.relPos.y * Yboundary;

	return CalculatePtCoordFromPtAndDist(UI_Math::centerPoint, {Xtranslation, Ytranslation});
}

DirectX::XMFLOAT3 UI_Math::CalculatePosRelativeToParent(PosAndSizeData parentData, PosAndSizeData elemData)
{
	// evaluate relative distance from parent center
	float XscrollRange = parentData.size.width / 4.0f - elemData.size.width / 4.0f;
	float YscrollRange = parentData.size.height / 4.0f - elemData.size.height / 4.0f;
	float Xdistance = elemData.relPos.x * XscrollRange;
	float Ydistance = elemData.relPos.y * YscrollRange;

	return CalculatePtCoordFromPtAndDist({ parentData.relPos.x, parentData.relPos.y, parentData.relPos.z }, {Xdistance, Ydistance});
}

DirectX::XMFLOAT3 UI_Math::GetUI_Facing()
{
	return UI_Math::ui_facing;
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

void UI_Math::CalculateUI_Facing()
{
	UI_Math::ui_facing.x = UI_Math::camFacing.y;
	UI_Math::ui_facing.y = UI_Math::camFacing.z + to_rad(45);
	UI_Math::ui_facing.z = 3.1415f;
}

DirectX::XMFLOAT3 UI_Math::CalculatePtCoordFromPtAndDist(DirectX::XMFLOAT3 pointCoord, DirectX::XMFLOAT2 distance)
{
	DirectX::XMFLOAT3 position;

	// pitch angle modifiers
	float hypothenuse = sin(UI_Math::camFacing.y) * distance.y;
	float pitchYmod = cos(UI_Math::camFacing.y) * distance.y;
	float pitchXmod = sin(UI_Math::camFacing.z) * hypothenuse;
	float pitchZmod = cos(UI_Math::camFacing.z) * hypothenuse;

	// yaw angle modifiers
	float xFactor = distance.x * cos(UI_Math::camFacing.z);
	float zFactor = distance.x * sin(UI_Math::camFacing.z);

	position.x = pointCoord.x + xFactor + pitchXmod;
	position.y = pointCoord.y + pitchYmod;
	position.z = pointCoord.z - zFactor + pitchZmod;

	return position;
}
