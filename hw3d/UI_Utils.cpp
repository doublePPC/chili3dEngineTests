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

void UI_Utils::spawnFontControlWindow(Graphics& gfx)
{
	textFont->spawnControlWindow(gfx);
}


