#include "UI_Font.h"
#include "Surface.h"


// ** static methods **
unsigned char UI_Font::baseColorAddition(unsigned char first, unsigned char second)
{
	unsigned char difference;
	unsigned char result;
	if (first > second)
	{
		difference = (first - second) / 2;
		result = first - difference;
	}
	else if (first < second)
	{
		difference = (second - first) / 2;
		result = second - difference;
	}
	else
	{
		result = first;
	}
	return result;
}

bool UI_Font::isAlpha(unsigned char value)
{
	return value >= 65 && value <= 90 || value >= 97 && value <= 122;
}

bool UI_Font::isNumerical(unsigned char value)
{
	return value >= 48 && value <= 57;
}

bool UI_Font::isSpaceChar(unsigned char value)
{
	//    horizontal tab    space bar
	return value == 9 || value == 32;
}

bool UI_Font::isAlphaNumerical(unsigned char value)
{
	return UI_Font::isAlpha(value) || UI_Font::isNumerical(value);
}

bool UI_Font::isPunctuationSymbol(unsigned char value)
{
	return value >= 33 && value <= 47 || value >= 58 && value <= 64 || value >= 91 && value <= 96 || value >= 123 && value <= 126;
}

// ** public instances methods **
UI_Font::UI_Font(const std::string& fontName, const std::string& filePath)
{
	std::shared_ptr<Surface> tempSurface = std::make_shared<Surface>(Surface::FromFile(filePath));
	FontCodex::SetupFont(fontName, tempSurface, drawable_Characters, charDatas, fntData);
}

UI_Font::~UI_Font()
{
}


std::shared_ptr<Surface> UI_Font::getSurfaceFromString(const std::string& value)
{
	// creates a single surface that contains all the content of the string in a lign
	std::shared_ptr<Surface> result = nullptr;

	unsigned int cursorPos = 0;
	unsigned int textWidth = 0;
	unsigned char charToDraw;
	for (unsigned int i = 0; i < value.length(); i++)
		textWidth += getCharWidth(value.at(i));
	result = std::make_shared<Surface>(textWidth, fntData.lignHeight);
	result->Clear({ 0, 255, 255, 255 });

	for (unsigned int i = 0; i < value.length(); i++)
	{
		charToDraw = convertAlphaCase(value.at(i));
		if (charDatas[charToDraw].isCharDrawable)
		{
			if (charToDraw == 32)
				cursorPos += fntData.spaceWidth;
			else if (charToDraw == 9)
				cursorPos += getTabWidth();
			else
			{
				for (int j = 0; j < drawable_Characters.at(charToDraw)->GetWidth(); j++)
				{
					for (int k = 0; k < fntData.lignHeight; k++)
					{
						result->PutPixel(cursorPos + j, k, drawable_Characters.at(charToDraw)->GetPixel(j, k));
					}
				}
				cursorPos += drawable_Characters.at(charToDraw)->GetWidth();
			}
		}	
	}
	return result;
}

std::shared_ptr<Surface> UI_Font::getSurfaceFromChar(unsigned char value)
{
	value = convertAlphaCase(value);
	if (charDatas[value].isCharDrawable)
	{
		if (isSpaceChar(value))
		{
			std::shared_ptr<Surface> result = nullptr;
			unsigned int width = 1;
			if (value == 32)
				width = fntData.spaceWidth;
			else if (value == 9)
				width = getTabWidth();
			result = std::make_shared<Surface>(width, fntData.lignHeight);
			result->Clear({ 0, 255, 255, 255 });
			return result;
		}
		else
		{
			value = convertAlphaCase(value);
			return drawable_Characters.at(value);
		}
	}
	else
	{
		std::shared_ptr<Surface> result = nullptr;
		result = std::make_shared<Surface>(10, fntData.lignHeight);
		result->Clear({ 50, 64, 64, 64 });
		return result;
	}
}

unsigned int UI_Font::getCharWidth(unsigned char value)
{
	if (value == 32)
		return fntData.spaceWidth;
	else if (value == 9)
		return this->getTabWidth();
	else
		value = convertAlphaCase(value);
	if (charDatas[value].isCharDrawable)
			return drawable_Characters.at(value)->GetWidth();
	else
		return 0;
}

unsigned int UI_Font::getCharHeight(unsigned char value)
{
	if (value == 32 || value == 9)
		return fntData.lignHeight;
	else
		value = convertAlphaCase(value);
	if (charDatas[value].isCharDrawable)
		return drawable_Characters.at(value)->GetHeight();
	else
		return 0;
}

unsigned int UI_Font::getLignHeight()
{
	return fntData.lignHeight;
}

unsigned int UI_Font::getSpaceWidth()
{
	return fntData.spaceWidth;
}

unsigned int UI_Font::getTabWidth()
{
	return fntData.spaceWidth * 5;
}

void UI_Font::drawTextOnSurface(const TextLign& lign, std::shared_ptr<Surface> surface, const Police& police)
{
	unsigned int totWidth = surface->GetWidth();
	unsigned int xCursor = 0;
	unsigned int jump = 0;
	Surface::Color currentColor;
	// adjust xCursor according to text alignment
	if (police.alignment == textAlignment::right)
	{
		xCursor = lign.remainingWidth;
	}
	else if (police.alignment == textAlignment::center)
	{
		xCursor = lign.remainingWidth / 2;
	}
	else if (police.alignment == textAlignment::justified)
	{
		if(lign.content.size() >= 2)
			jump = lign.remainingWidth / (lign.content.size() -1);
	}
	// draw the content
	for (unsigned int i = 0; i < lign.content.size(); i++)
	{
		currentColor = lign.content[i].tintEffect;
		for (unsigned int j = 0; j < lign.content[i].text.length(); j++)
		{
			drawCharOnSurface(i + xCursor, surface, lign.content[i].text.at(j), currentColor);
			xCursor += getCharWidth(lign.content[i].text.at(j));
		}
		xCursor += jump;
	}
}

void UI_Font::spawnControlWindow(Graphics& gfx)
{
	if (ImGui::Begin("UI_FunkyFont"))
	{
		std::string value = "Size of Drawable Characters : " + std::to_string(drawable_Characters.size());
		ImGui::Text(value.c_str());
		value = "Size of Characters Datas : " + std::to_string(charDatas.size());
		ImGui::Text(value.c_str());
	}
	ImGui::End();
}


// ** private instances method **

void UI_Font::drawCharOnSurface(unsigned int start, std::shared_ptr<Surface> surface, unsigned char letter, Surface::Color color)
{
	unsigned int yOffset = fntData.drawingLignPos + 1 - charDatas[letter].distFromDrawLine - getCharHeight(letter);
	for (unsigned int i = 0; i < getCharWidth(letter); i++)
	{
		for (unsigned int j = 0; j < getCharHeight(letter); j++)
		{
			if (i + start < surface->GetWidth() && j + yOffset < surface->GetHeight())
			{
				Surface::Color pixelColor = { 0, 255, 255, 255 };
				if (isSpaceChar(letter) == false)
					pixelColor = drawable_Characters.at(convertAlphaCase(letter))->GetPixel(i, j);
				if (color.GetA() > 0 && pixelColor.GetA() > 0)
				{
					pixelColor.SetR(UI_Font::baseColorAddition(color.GetR(), pixelColor.GetR()));
					pixelColor.SetG(UI_Font::baseColorAddition(color.GetG(), pixelColor.GetG()));
					pixelColor.SetB(UI_Font::baseColorAddition(color.GetB(), pixelColor.GetB()));
				}
				surface->PutPixel(i + start, j + yOffset, pixelColor);
			}
		}
	}
}

unsigned char UI_Font::convertAlphaCase(unsigned char value)
{
	if (isAlpha(value))
	{
		if (fntData.hasLowerCase && fntData.hasUpperCase)
			return value;
		else if (fntData.hasUpperCase)
			return ::toupper(value);
		else
			return ::tolower(value);
	}
	else
		return value;
}

