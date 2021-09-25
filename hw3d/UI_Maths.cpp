#include "UI_Maths.h"

DirectX::XMFLOAT3 UI_Math::camFacing;
DirectX::XMFLOAT3 UI_Math::camPosition;
DirectX::XMFLOAT3 UI_Math::centerPoint;
DirectX::XMFLOAT3 UI_Math::ui_facing;
float UI_Math::screenWidth;
float UI_Math::screenHeight;

void UI_Math::Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos)
{
	UI_Math::camFacing = camFace;
	UI_Math::camPosition = camPos;
	CalculateCenterPoint();
	CalculateUI_Facing();
}

void UI_Math::SaveScreenSizeValues(float width, float height)
{
	screenWidth = width;
	screenHeight = height;
}

DirectX::XMFLOAT2 UI_Math::CalculatePosRelativeToScreen(PosAndSize elemData)
{
	DirectX::XMFLOAT2 result;
	// evaluate boundaries according to element's size
	// I suspect the 1.0f constant for X and the 0.565f constant for Y are the screen proportion... I have yet to test it.
	float Xboundary = 1.0f - elemData.size * elemData.scaleX / 4.0f;
	float Xtranslation = elemData.relPos.x * Xboundary;
	float Yboundary = 0.565f - elemData.size * elemData.scaleY / 4.0f;
	float Ytranslation = elemData.relPos.y * Yboundary;

	result = { Xtranslation, Ytranslation };
	return result;
}

DirectX::XMFLOAT2 UI_Math::CalculatePosRelativeToParent(PosAndSize parentData, PosAndSize elemData)
{
	DirectX::XMFLOAT2 result;
	// evaluate relative distance from parent center
	float XscrollRange = parentData.size * parentData.scaleX / 4.0f - elemData.size * elemData.scaleX / 4.0f;
	float YscrollRange = parentData.size * parentData.scaleY / 4.0f - elemData.size * elemData.scaleY / 4.0f;
	float Xdistance = elemData.relPos.x * XscrollRange;
	float Ydistance = elemData.relPos.y * YscrollRange;

	result = { Xdistance, Ydistance };
	return result;
}

DirectX::XMFLOAT3 UI_Math::CalculatePtCoordFromCenter(DirectX::XMFLOAT2 distance)
{
	DirectX::XMFLOAT3 result;
	result = CalculatePtCoordFromPoint(UI_Math::centerPoint, distance);
	return result;
}

DirectX::XMFLOAT3 UI_Math::GetUI_Facing()
{
	return UI_Math::ui_facing;
}

std::pair<float, float> UI_Math::MousePos2ScreenPos(float X, float Y)
{
	float xValue = X * 2.0f / UI_Math::screenWidth - 1.0f;
	float yValue = Y * 2.0f / UI_Math::screenHeight - 1.0f;
	return std::pair<float, float>(xValue, yValue);
}

std::pair<float, float> UI_Math::CalculateTopLeft(float centerX, float centerY, float sizeX, float sizeY)
{
	// this method uses constants that are probably relative to screen proportions
	std::pair<float, float> result;
	result.first = centerX - 0.5f * sizeX / 2.0f;
	result.second = 1.769f * centerY + 0.88f * sizeY / 2.0f;
	result.second = result.second * -1.0f;
	return result;
}

std::pair<float, float> UI_Math::CalculateBotRight(float centerX, float centerY, float sizeX, float sizeY)
{
	// this method uses constants that are probably relative to screen proportions
	std::pair<float, float> result;
	result.first = centerX + 0.5f * sizeX / 2.0f;
	result.second = 1.769f * centerY - 0.88f * sizeY / 2.0f;
	result.second = result.second * -1.0f;
	return result;
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

DirectX::XMFLOAT3 UI_Math::CalculatePtCoordFromPoint(DirectX::XMFLOAT3 pointCoord, DirectX::XMFLOAT2 distance)
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
