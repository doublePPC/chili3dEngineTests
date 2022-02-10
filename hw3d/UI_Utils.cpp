#include "UI_Utils.h"
#include "Surface.h"

std::unique_ptr<UI_Font> UI_Utils::textFont;

void UI_Utils::loadFontFile(std::string fileName)
{
	textFont = std::make_unique<UI_Font>(fileName);
}

std::shared_ptr<Surface> UI_Utils::stringToSurface(const std::string& value)
{
	if (value.length() == 1)
		return textFont->getSurfaceFromChar(*value.c_str());
	else
		return textFont->getSurfaceFromString(value);
}

std::shared_ptr<Surface> UI_Utils::charToSurface(unsigned char value)
{
	return textFont->getSurfaceFromChar(value);
}

void UI_Utils::applyColorFilterToSurface(std::shared_ptr<Surface> image, unsigned char red, unsigned char green, unsigned blue)
{
	for (int i = 0; i < image->GetWidth(); i++)
	{
		for (int j = 0; j < image->GetHeight(); j++)
		{
			auto color = image->GetPixel(i, j);
			color.SetR(UI_Font::baseColorAddition(red, color.GetR()));
			color.SetG(UI_Font::baseColorAddition(green, color.GetG()));
			color.SetB(UI_Font::baseColorAddition(blue, color.GetB()));
			image->PutPixel(i, j, color);
		}
	}
}

void UI_Utils::spawnFontControlWindow(Graphics& gfx)
{
	textFont->spawnControlWindow(gfx);
}

unsigned int UI_Utils::getTextPixelWidth(const std::string& text)
{
	unsigned int result = 0;

	for (unsigned int i = 0; i < text.length(); i++)
	{
		result += textFont->getCharWidth(text.at(i));
	}
	return result;
}

unsigned int UI_Utils::getTextPixelWidth(std::shared_ptr<std::string> text)
{
	unsigned int result = 0;

	for (unsigned int i = 0; i < text->length(); i++)
	{
		result += textFont->getCharWidth(text->at(i));
	}
	return result;
}

unsigned int UI_Utils::getCharPixelWidth(unsigned char c)
{
	return textFont->getCharWidth(c);
}

unsigned int UI_Utils::getFontBaseTextHeight()
{
	return textFont->getCharHeight();
}

unsigned int UI_Utils::getFontSpaceWidth()
{
	return textFont->getSpaceWidth();
}

void UI_Utils::drawTextOnSurface(const TextLign& lign, std::shared_ptr<Surface> surface, const Police& police)
{
	textFont->drawTextOnSurface(lign, surface, police);
}

// ** private methods **

