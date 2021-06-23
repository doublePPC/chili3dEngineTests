#include "UI_Component.h"

UI_Component::UI_Component(std::string filePath, unsigned int width, unsigned height, unsigned int Xpos, unsigned int Ypos)
{
	imgFile = filePath;
	pctWidth = width;
	pctHeight = height;
	pctXpos = Xpos;
	pctYpos = Ypos;
}

UI_Component::~UI_Component()
{
}

DirectX::XMFLOAT4 UI_Component::GetImgPosSizeData(DirectX::XMFLOAT2 elemPos, DirectX::XMFLOAT2 elemDimensions)
{
	float Xsize, Ysize, translationX, translationY;
	Xsize = float(this->pctWidth) / 255.0f * elemDimensions.x;
	Ysize = float(this->pctHeight) / 255.0f * elemDimensions.y;

	translationX = float(this->pctXpos) / 255.0f * elemDimensions.x + elemPos.x;
	translationY = float(this->pctYpos) / 255.0f * elemDimensions.y + elemPos.y;

	return {translationX, translationY, Xsize, Ysize};
}

std::string UI_Component::getImgFilepath()
{
	return imgFile;
}
