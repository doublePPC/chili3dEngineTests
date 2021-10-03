#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx);
	~UI_Component();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale);
	void SubmitToChannel();

	void SpawnControlWindow(Graphics& gfx, int index);
	PosAndSize GetPosSizeData();
	std::shared_ptr<TestSquare> getImage();
	std::pair<float, float> getTopLeft();
	std::pair<float, float> getBotRight();

	// command methods
	void manageLeftClick();
	void manageRightClick();
private:
	void evaluateCornersPosition(DirectX::XMFLOAT2 relPos);
private:
	std::shared_ptr<TestSquare> image;
	std::shared_ptr<TestSquare> image2;
	PosAndSize datas;
	std::pair<float, float> relTopLeft;
	std::pair<float, float> relBotRight;
	bool state = false;
};