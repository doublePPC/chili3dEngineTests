#pragma once
#include "UI_Generics.h"

class UI_Math
{
public:
	static void Update(DirectX::XMFLOAT3 camFace, DirectX::XMFLOAT3 camPos);
	static void SaveScreenSizeValues(float width, float height);

	// these evaluate relative positions to point (ranging from -1.0f to +1.0f)
	static DirectX::XMFLOAT2 CalculatePosRelativeToScreen(PosAndSize elemData);
	static DirectX::XMFLOAT2 CalculatePosRelativeToParent(PosAndSize parentData, PosAndSize elemData);
	// these evaluate space positions  
	static DirectX::XMFLOAT3 CalculatePtCoordFromCenter(DirectX::XMFLOAT2 distance);
	static DirectX::XMFLOAT3 CalculatePtCoordFromPoint(DirectX::XMFLOAT3 pointCoord, DirectX::XMFLOAT2 distance);

	static DirectX::XMFLOAT3 GetUI_Facing();

	// for mouse inputs management
	static std::pair<float, float> MousePos2ScreenPos(float X, float Y);
	static std::pair<float, float> CalculateTopLeft(float centerX, float centerY, float actualXsize, float actualYsize);
	static std::pair<float, float> CalculateBotRight(float centerX, float centerY, float actualXsize, float actualYsize);
private:
	static void CalculateCenterPoint();
	static void CalculateUI_Facing();
private:
	static DirectX::XMFLOAT3 camFacing;
	static DirectX::XMFLOAT3 camPosition;
	static DirectX::XMFLOAT3 centerPoint;
	static DirectX::XMFLOAT3 ui_facing;
	static float screenWidth;
	static float screenHeight;
};