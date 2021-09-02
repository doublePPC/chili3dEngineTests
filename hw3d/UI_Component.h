#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx);
	~UI_Component();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, Size parentSize);

	void SpawnControlWindow(Graphics& gfx, int index);
	PosAndSizeData GetPosSizeData();
	std::shared_ptr<TestSquare> getImage();
private:
	std::shared_ptr<TestSquare> image;
	PosAndSizeData datas;
};