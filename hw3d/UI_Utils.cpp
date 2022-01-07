#include "UI_Utils.h"
#include "Surface.h"

std::unique_ptr<UI_Font> UI_Utils::textFont;

void UI_Utils::loadFontFile(std::string fileName)
{
	textFont = std::make_unique<UI_Font>(fileName);
}

std::shared_ptr<Surface> UI_Utils::stringToSurface(std::string value)
{
	std::for_each(value.begin(), value.end(), [](char& c) { c = ::toupper(c); });
	if (value.length() == 1)
		return textFont->getSurfaceFromChar((int)*value.c_str());
	else
		return textFont->getSurfaceFromString(value);
}

std::shared_ptr<Surface> UI_Utils::charToSurface(char value)
{
	value = ::toupper(value);
	return textFont->getSurfaceFromChar((int)value);
}

void UI_Utils::applyColorFilterToSurface(std::shared_ptr<Surface> image, unsigned char red, unsigned char green, unsigned blue)
{
	for (int i = 0; i < image->GetWidth(); i++)
	{
		for (int j = 0; j < image->GetHeight(); j++)
		{
			auto color = image->GetPixel(i, j);
			color.SetR(UI_Utils::baseColorAddition(red, color.GetR()));
			color.SetG(UI_Utils::baseColorAddition(green, color.GetG()));
			color.SetB(UI_Utils::baseColorAddition(blue, color.GetB()));
			image->PutPixel(i, j, color);
		}
	}
}

void UI_Utils::spawnFontControlWindow(Graphics& gfx)
{
	textFont->spawnControlWindow(gfx);
}

unsigned char UI_Utils::baseColorAddition(unsigned char first, unsigned char second)
{
	unsigned char difference;
	unsigned char result;
	if (first > second)
	{
		difference = (first - second)/ 2;
		result = first - difference;
	}
	else if (first < second)
	{
		difference = (second - first)/ 2;
		result = second - difference;
	}
	else
	{
		result = first;
	}
	return result;
}




