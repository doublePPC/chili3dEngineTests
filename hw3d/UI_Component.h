#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx);
	~UI_Component();

	void AdjustPosToParent(DirectX::XMFLOAT4 parentData);

	void SpawnControlWindow(Graphics& gfx);
	DirectX::XMFLOAT4 GetImgPosSizeData();
	std::shared_ptr<TestSquare> getImage();
private:
	std::shared_ptr<TestSquare> image;
	float size;
	float pctXpos;
	float pctYpos;
};