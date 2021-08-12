#pragma once

#include "UI_Generics.h"

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx);
	~UI_Component();

	DirectX::XMFLOAT4 GetImgPosSizeData();
	std::shared_ptr<TestSquare> getImage();
private:
	std::shared_ptr<TestSquare> image;
	float size;
	float pctXpos;
	float pctYpos;
};