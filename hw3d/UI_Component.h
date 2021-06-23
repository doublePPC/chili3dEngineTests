#pragma once

#include "UI_Generics.h"

class UI_Component
{
public:
	UI_Component(std::string filePath, unsigned int width, unsigned height, unsigned int Xpos, unsigned int Ypos);
	~UI_Component();

	DirectX::XMFLOAT4 GetImgPosSizeData(DirectX::XMFLOAT2 elemPos, DirectX::XMFLOAT2 elemDimensions);
	std::string getImgFilepath();
private:
	std::string imgFile;
	unsigned int pctWidth;
	unsigned int pctHeight;
	unsigned int pctXpos;
	unsigned int pctYpos;
};