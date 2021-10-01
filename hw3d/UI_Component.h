#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx);
	~UI_Component();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale);

	void SpawnControlWindow(Graphics& gfx, int index);
	PosAndSize GetPosSizeData();
	std::shared_ptr<TestSquare> getImage();
	std::pair<float, float> getTopLeft();
	std::pair<float, float> getBotRight();

	// command methods
	bool manageLeftClick(float clicX, float clicY, std::pair<float, float> axisRanges);
private:
	void evaluateCornersPosition(DirectX::XMFLOAT2 relPos);
	bool mouseClickCheckup(float clicX, float clicY);
private:
	std::shared_ptr<TestSquare> image;
	PosAndSize datas;
	std::pair<float, float> relTopLeft;
	std::pair<float, float> relBotRight;
};