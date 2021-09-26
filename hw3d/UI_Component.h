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

	// command methods
	bool manageLeftClick(int clicX, int clicY);
private:
	bool mouseClickCheckup(int clicX, int clicY);
private:
	std::shared_ptr<TestSquare> image;
	PosAndSize datas;
};