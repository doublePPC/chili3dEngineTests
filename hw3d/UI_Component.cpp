#include "UI_Component.h"

UI_Component::UI_Component(ComponentData data, Graphics& gfx)
{
	size = data.compBaseData.size;
	pctXpos = data.compBaseData.posX;
	pctYpos = data.compBaseData.posY;
	image = std::make_shared<TestSquare>(gfx, size, data.texturePath);
}

UI_Component::~UI_Component()
{
}

DirectX::XMFLOAT4 UI_Component::GetImgPosSizeData()
{
	return {pctXpos, pctYpos, 0.0f, size};
}

std::shared_ptr<TestSquare> UI_Component::getImage()
{
	return image;
}

