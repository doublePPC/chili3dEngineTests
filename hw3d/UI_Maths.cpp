#include "UI_Maths.h"

DirectX::XMFLOAT3 UI_Math::camFacing;
DirectX::XMFLOAT3 UI_Math::camPosition;
DirectX::XMFLOAT3 UI_Math::centerPoint;
DirectX::XMFLOAT3 UI_Math::ui_facing;
DirectX::XMFLOAT3 UI_Math::horizontalGap;
DirectX::XMFLOAT3 UI_Math::verticalGap;
float UI_Math::screenWidth;
float UI_Math::screenHeight;

void UI_Math::Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos)
{
	UI_Math::camFacing = camFace;
	UI_Math::camPosition = camPos;
	CalculateCenterPoint();
	CalculateUI_Facing();
	DirectX::XMFLOAT3 leftPos = UI_Math::CalculatePtCoordFromPoint(UI_Math::centerPoint, { -1.0f, 0.0f });
	UI_Math::horizontalGap = { UI_Math::centerPoint.x - leftPos.x,  UI_Math::centerPoint.y - leftPos.y, UI_Math::centerPoint.z - leftPos.z };
	DirectX::XMFLOAT3 bottomPos = UI_Math::CalculatePtCoordFromPoint(UI_Math::centerPoint, { 0.0f, -1.0f });
	UI_Math::verticalGap = { UI_Math::centerPoint.x - bottomPos.x,  UI_Math::centerPoint.y - bottomPos.y, UI_Math::centerPoint.z - bottomPos.z };
}

void UI_Math::SaveScreenSizeValues(float width, float height)
{
	screenWidth = width;
	screenHeight = height;
}

DirectX::XMFLOAT3 UI_Math::getHorizontalGap()
{
	return UI_Math::horizontalGap;
}

DirectX::XMFLOAT3 UI_Math::getVerticalGap()
{
	return UI_Math::verticalGap;
}

DirectX::XMFLOAT2 UI_Math::CalculatePosRelativeToScreen(RelativePosition elemPos, Size elemSize)
{
	DirectX::XMFLOAT2 result;
	// evaluate boundaries according to element's size
	// I suspect the 1.0f constant for X and the 0.565f constant for Y are the screen proportion... I have yet to test it.
	float Xboundary = 1.0f - elemSize.size * elemSize.scaleX / 4.0f;
	float Xtranslation = elemPos.x * Xboundary;
	float Yboundary = 0.565f - elemSize.size * elemSize.scaleY / 4.0f;
	float Ytranslation = elemPos.y * Yboundary;

	result = { Xtranslation, Ytranslation };
	return result;
}

DirectX::XMFLOAT2 UI_Math::CalculatePosRelativeToParent(Size parentSize, RelativePosition elemPos, Size elemSize)
{
	DirectX::XMFLOAT2 result;
	// evaluate relative distance from parent center
	float XscrollRange = parentSize.size * parentSize.scaleX / 4.0f - elemSize.size * elemSize.scaleX / 4.0f;
	float YscrollRange = parentSize.size * parentSize.scaleY / 4.0f - elemSize.size * elemSize.scaleY / 4.0f;
	float Xdistance = elemPos.x * XscrollRange;
	float Ydistance = elemPos.y * YscrollRange;

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

float UI_Math::CalculateWidth(float size, float factor)
{
	// the 0.5f is a constant with unknown origin (probably related to screen size somehow)
	return 0.5f * size * factor;
}

float UI_Math::CalculateHeight(float size, float factor)
{
	// the 0.88f is a constant with unknown origin (probably related to screen size somehow)
	return 0.88f * size * factor;
}

float UI_Math::CalculateTextLignScreenHeight(unsigned int letterSize)
{
	return (float)letterSize / UI_Math::screenHeight;
}

float UI_Math::CalculateInterlignHeight(float textLignHeight, lignSpace interlign)
{
	if (interlign == lignSpace::half)
		return textLignHeight / 2.0f;
	else if (interlign == lignSpace::doubled)
		return textLignHeight;
	else
		return 0.0f;
}

unsigned int UI_Math::CalculateTextLignPixelWidth(float textLignHeight, unsigned int fontBaseHeight, float xSize)
{
	float result = xSize / textLignHeight * (float)fontBaseHeight;
	return (unsigned int)result;
}

std::pair<float, float> UI_Math::MousePos2ScreenPos(float X, float Y)
{
	float xValue = X * 2.0f / UI_Math::screenWidth - 1.0f;
	float yValue = Y * 2.0f / UI_Math::screenHeight - 1.0f;
	return std::pair<float, float>(xValue, yValue);
}

std::pair<float, float> UI_Math::CalculateTopLeft(float centerX, float centerY, float halfWidth, float halfHeight)
{
	// this method uses constants that are probably relative to screen proportions
	std::pair<float, float> result;
	result.first = centerX - halfWidth;
	result.second = 1.769f * centerY + halfHeight;
	result.second = result.second * -1.0f;
	return result;
}

std::pair<float, float> UI_Math::CalculateBotRight(float centerX, float centerY, float halfWidth, float halfHeight)
{
	// this method uses constants that are probably relative to screen proportions
	std::pair<float, float> result;
	result.first = centerX + halfWidth;
	result.second = 1.769f * centerY - halfHeight;
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
	//UI_Math::ui_facing.z = 3.1415f;
	UI_Math::ui_facing.z = 0.0f;
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
