#include "UI_Utils.h"
#include "Surface.h"

std::unordered_map<std::string, std::unique_ptr<UI_Font>> UI_Utils::textFonts;
std::vector<UIEventData> UI_Utils::eventDatas;

void UI_Utils::loadFontFile(const std::string& fontName, const std::string& fileName)
{
	textFonts.emplace(fontName, std::make_unique<UI_Font>(fontName, fileName));
}

std::shared_ptr<Surface> UI_Utils::stringToSurface(const std::string& value, const std::string& fontName)
{
	if (textFonts.contains(fontName))
	{
		if (value.length() == 1)
			return textFonts.at(fontName)->getSurfaceFromChar(*value.c_str());
		else
			return textFonts.at(fontName)->getSurfaceFromString(value);
	}
	else
	{
		// TODO : send warning that an attempt to access an unexisting font has been made
		if (value.length() == 1)
			return textFonts.at(FONT_FUNKY)->getSurfaceFromChar(*value.c_str());
		else
			return textFonts.at(FONT_FUNKY)->getSurfaceFromString(value);
	}
}

std::shared_ptr<Surface> UI_Utils::charToSurface(unsigned char value, const std::string& fontName)
{
	if(textFonts.contains(fontName))
		return textFonts.at(fontName)->getSurfaceFromChar(value);
	else
		return textFonts.at(FONT_FUNKY)->getSurfaceFromChar(value);
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

void UI_Utils::applyWhiteFadingTransparency(std::shared_ptr<Surface> image)
{
	unsigned int average = 0;
	unsigned int result = 0;
	for (int i = 0; i < image->GetWidth(); i++)
	{
		for (int j = 0; j < image->GetHeight(); j++)
		{
			auto color = image->GetPixel(i, j);
			average = (color.GetR() + color.GetG() + color.GetB()) / 3;
			result = 255 - average;
			color.SetA(result);
			image->PutPixel(i, j, color);
		}
	}
}

void UI_Utils::spawnFontControlWindow(Graphics& gfx)
{
	textFonts.at(FONT_FUNKY)->spawnControlWindow(gfx);
}

unsigned int UI_Utils::getTextPixelWidth(const std::string& text, const std::string& fontName)
{
	unsigned int result = 0;
	if (textFonts.contains(fontName))
	{
		for (unsigned int i = 0; i < text.length(); i++)
		{
			result += textFonts.at(fontName)->getCharWidth(text.at(i));
		}
	}
	else
	{
		for (unsigned int i = 0; i < text.length(); i++)
		{
			result += textFonts.at(FONT_FUNKY)->getCharWidth(text.at(i));
		}
	}
	return result;
}

unsigned int UI_Utils::getTextPixelWidth(std::shared_ptr<std::string> text, const std::string& fontName)
{
	unsigned int result = 0;
	if (textFonts.contains(fontName))
	{
		for (unsigned int i = 0; i < text->length(); i++)
		{
			result += textFonts.at(fontName)->getCharWidth(text->at(i));
		}
	}
	else
	{
		for (unsigned int i = 0; i < text->length(); i++)
		{
			result += textFonts.at(FONT_FUNKY)->getCharWidth(text->at(i));
		}
	}
	return result;
}

unsigned int UI_Utils::getCharPixelWidth(unsigned char c, const std::string& fontName)
{
	if (textFonts.contains(fontName))
		return textFonts.at(fontName)->getCharWidth(c);
	else
		return textFonts.at(FONT_FUNKY)->getCharWidth(c);
}

unsigned int UI_Utils::getFontBaseTextHeight(const std::string& fontName)
{
	if (textFonts.contains(fontName))
		return textFonts.at(fontName)->getLignHeight();
	else
		return textFonts.at(FONT_FUNKY)->getLignHeight();
}

unsigned int UI_Utils::getFontSpaceWidth(const std::string& fontName)
{
	if (textFonts.contains(fontName))
		return textFonts.at(fontName)->getSpaceWidth();
	else
		return textFonts.at(FONT_FUNKY)->getSpaceWidth();
}

void UI_Utils::drawTextOnSurface(const TextLign& lign, std::shared_ptr<Surface> surface, const Police& police)
{
	if (textFonts.contains(police.font))
		textFonts.at(police.font)->drawTextOnSurface(lign, surface, police);
	else
		textFonts.at(FONT_FUNKY)->drawTextOnSurface(lign, surface, police);
}

void UI_Utils::storeUIEvent(UIEventData uiEvent)
{
	eventDatas.push_back(uiEvent);
}

UIEventData UI_Utils::popLastEventData()
{
	UIEventData value = eventDatas.back();
	eventDatas.pop_back();
	return value;
}

std::shared_ptr<std::vector<UIEventData>> UI_Utils::retrieveUIEvents()
{
	std::vector<UIEventData> values = eventDatas;
	std::shared_ptr<std::vector<UIEventData>> values_ptr = std::make_shared<std::vector<UIEventData>>(values);
	eventDatas.clear();
	return values_ptr;
}

bool UI_Utils::checkForUIEventsToManage()
{
	return !eventDatas.empty();
}

// ** private methods **
