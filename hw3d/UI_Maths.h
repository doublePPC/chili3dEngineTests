#pragma once
#include "UI_Generics.h"

class UI_Math
{
public:
	static void Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos, float screenWidth, float screenHeight);
	static void SaveScreenSizeValues(float width, float height);
	static DirectX::XMFLOAT3 getHorizontalGap();
	static DirectX::XMFLOAT3 getVerticalGap();

	// these evaluate relative positions to point (ranging from -1.0f to +1.0f)
	static DirectX::XMFLOAT2 CalculatePosRelativeToScreen(RelativePosition elemPos, Size elemSize);
	static DirectX::XMFLOAT2 CalculatePosRelativeToParent(Size parentSize, RelativePosition elemPos, Size elemSize);
	// these evaluate space positions  
	static DirectX::XMFLOAT3 CalculatePtCoordFromCenter(DirectX::XMFLOAT2 distance);
	static DirectX::XMFLOAT3 CalculatePtCoordFromPoint(DirectX::XMFLOAT3 pointCoord, DirectX::XMFLOAT2 distance);

	// others
	static DirectX::XMFLOAT3 GetUI_Facing();
	static float CalculateWidth(float size, float factor);
	static float CalculateHeight(float size, float factor);

	// text/font calculations
	static float CalculateTextLignHeightFactor(unsigned int letterSize);
	static float CalculateInterlignHeight(float textLignHeight, lignSpace interlign);
	static unsigned int CalculateTextLignPixelWidth(float textLignHeight, unsigned int fontBaseHeight, float xSize);
	static float CalculateTextLignYScale(float textBoxYSize, float textLignHeight);


	// for mouse inputs management
	static std::pair<float, float> MousePos2ScreenPos(float X, float Y);
	static std::pair<float, float> CalculateTopLeft(float centerX, float centerY, float halfWidth, float halfHeight);
	static std::pair<float, float> CalculateBotRight(float centerX, float centerY, float halfWidth, float halfHeight);
	static std::pair<float, float> ConvertMousePos(float clicX, float clicY, float xTopL, float yTopL, float xBotR, float yBotR);
private:
	static void CalculateCenterPoint();
	static void CalculateUI_Facing();
private:
	static DirectX::XMFLOAT3 camFacing;
	static DirectX::XMFLOAT3 camPosition;
	static DirectX::XMFLOAT3 centerPoint;
	static DirectX::XMFLOAT3 ui_facing;
	static DirectX::XMFLOAT3 horizontalGap;
	static DirectX::XMFLOAT3 verticalGap;
	static float screenWidth;
	static float screenHeight;
};