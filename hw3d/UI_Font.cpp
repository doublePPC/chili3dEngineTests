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

bool UI_Font::isAccentuated(unsigned char value)
{
	if (value >= 192)
		return true;
	else
		return false;
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
	if (charDatas[value].isCharDrawable)
	{
		std::pair<unsigned char, unsigned char> prepValue = prepareChar(value);
		std::pair<unsigned char, unsigned char> widths = getPrepCharWidth(prepValue);
		unsigned int width;
		if (widths.first > widths.second)
			width = widths.first;
		else
			width = widths.second;
		std::shared_ptr<Surface> result = std::make_shared<Surface>(width, fntData.lignHeight);
		result->Clear({ 0, 255, 255, 255 });
		drawCharOnSurface(0, result, prepValue, { 0,0,0,0 });
		return result;
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
	if (charDatas[value].isCharDrawable)
	{
		std::pair<unsigned char, unsigned char> prepValue = prepareChar(value);
		if (prepValue.second != 0)
		{
			// char is accentuated
			if(drawable_Characters.at(prepValue.first)->GetWidth() > drawable_Characters.at(prepValue.second)->GetWidth())
				return drawable_Characters.at(prepValue.first)->GetWidth(); // char is larger than accent
			else
				return drawable_Characters.at(prepValue.second)->GetWidth(); // accent is larger than char
		}
		else if (isSpaceChar(prepValue.first))
		{
			// char is space character
			if (prepValue.first == 32)
				return getSpaceWidth();
			else
				return getTabWidth();
		}
		else
			return drawable_Characters.at(prepValue.first)->GetWidth();
	}
	else
		return 0;
}

unsigned int UI_Font::getCharHeight(unsigned char value)
{
	if (charDatas[value].isCharDrawable)
	{
		std::pair<unsigned char, unsigned char> prepValue = prepareChar(value);
		if (prepValue.second != 0)
			return drawable_Characters.at(prepValue.first)->GetHeight() + drawable_Characters.at(prepValue.second)->GetHeight();
		else if (isSpaceChar(prepValue.first))
			return fntData.lignHeight;
		else
			return drawable_Characters.at(prepValue.first)->GetHeight();
	}
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
	std::pair<unsigned char, unsigned char> charDetail;
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
			charDetail = prepareChar(lign.content[i].text.at(j));
			drawCharOnSurface(i + xCursor, surface, charDetail, currentColor);
			xCursor += getCharWidth(charDetail.first);
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

void UI_Font::drawCharOnSurface(unsigned int start, std::shared_ptr<Surface> surface, std::pair<unsigned char, unsigned char> prepValue, Surface::Color color)
{
	std::pair<unsigned int, unsigned int> heights = getPrepCharHeight(prepValue);
	std::pair<unsigned int, unsigned int> widths = getPrepCharWidth(prepValue);
	unsigned int yStart = fntData.drawingLignPos + 1 - charDatas[prepValue.first].distFromDrawLine - heights.first;
	unsigned int xOffset = 0;

	// drawing the char (letter)
	if (widths.second > widths.first)
		xOffset = (widths.second - widths.first) / 2;
	for (unsigned int i = 0; i < widths.first; i++)
	{
		for (unsigned int j = 0; j < heights.first; j++)
		{
			if (i + start + xOffset < surface->GetWidth() && i + start + xOffset >= 0 &&
				yStart + j < surface->GetHeight() && yStart + j >= 0)
			{
				drawPixelOnSurface(i + start + xOffset, yStart + j, i, j, surface, prepValue.first, color);
			}
		}
	}

	// drawing the accent (if there's any)
	if (prepValue.second > 0)
	{
		if (charDatas[prepValue.second].distFromDrawLine < 0)
			yStart = fntData.drawingLignPos + 1; // accent is a cedilla and has to be drawn below the letter
		else
			yStart = yStart - heights.second - 1; // it's a top accent and has to be drawn above the letter
		if (widths.first > widths.second)
			xOffset = (widths.first - widths.second) / 2;
		else
			xOffset = 0;
		for (unsigned int i = 0; i < widths.second; i++)
		{
			for (unsigned int j = 0; j < heights.second; j++)
			{
				if (i + start + xOffset < surface->GetWidth() && i + start + xOffset >= 0 &&
					yStart + j < surface->GetHeight() && yStart + j >= 0)
				{
					drawPixelOnSurface(i + start + xOffset, yStart + j, i, j, surface, prepValue.second, color);
				}
			}
		}
	}
}

void UI_Font::drawPixelOnSurface(unsigned int xPos, unsigned int yPos, unsigned int txCoordX, unsigned int txCoordY, std::shared_ptr<Surface> surface, unsigned char letter, Surface::Color color)
{
	Surface::Color pixelColor;
	if (isSpaceChar(letter))
		pixelColor = { 0, 255, 255, 255 };
	else
		pixelColor = drawable_Characters.at(letter)->GetPixel(txCoordX, txCoordY);
	if (color.GetA() > 0 && pixelColor.GetA() > 0)
	{
		pixelColor.SetR(UI_Font::baseColorAddition(color.GetR(), pixelColor.GetR()));
		pixelColor.SetG(UI_Font::baseColorAddition(color.GetG(), pixelColor.GetG()));
		pixelColor.SetB(UI_Font::baseColorAddition(color.GetB(), pixelColor.GetB()));
	}
	surface->PutPixel(xPos, yPos, pixelColor);
}

unsigned char UI_Font::convertAlphaCase(unsigned char value)
{
	// this method assumes you checked that "value" is actually an alpha character without accent
	if (fntData.hasLowerCase && fntData.hasUpperCase)
		return value;
	else if (fntData.hasUpperCase)
		return ::toupper(value);
	else
		return ::tolower(value);
}

std::pair<unsigned char, unsigned char> UI_Font::prepareChar(unsigned char value)
{
	// this method assumes you checked that "value" is actually a drawable character
	if (isAccentuated(value))
	{
		unsigned char letter = defineChar(value);
		unsigned char accent = defineAccent(value);
		return std::pair<unsigned char, unsigned char>(letter, accent);
	}
	else if (isAlpha(value))
	{
		value = convertAlphaCase(value);
		return std::pair<unsigned char, unsigned char>(value, 0);
	}
	else
		return std::pair<unsigned char, unsigned char>(value, 0);
}

unsigned char UI_Font::defineChar(unsigned char value)
{
	// determine the letter of an accentuated character
	unsigned char letter = 'a';

	if (value >= 192 && value <= 221)
		{
			// capital letters with accent
			if (value >= 192 && value <= 196)
				letter = 'A';
			else if (value == 199)
				letter = 'C';
			else if (value >= 200 && value <= 203)
				letter = 'E';
			else if (value >= 204 && value <= 207)
				letter = 'I';
			else if (value == 209)
				letter = 'N';
			else if (value >= 210 && value <= 214)
				letter = 'O';
			else if (value >= 217 && value <= 220)
				letter = 'U';
			else
				letter = 'Y';
			if (fntData.hasUpperCase == false)
				letter = ::tolower(letter);
		}
	else
		{
			// lower case letters with accent
			if (value >= 224 && value <= 228)
				letter = 'a';
			else if (value == 231)
				letter = 'c';
			else if (value >= 232 && value <= 235)
				letter = 'e';
			else if (value >= 236 && value <= 239)
				letter = 'i';
			else if (value == 241)
				letter = 'n';
			else if (value >= 242 && value <= 246)
				letter = 'o';
			else if (value >= 249 && value <= 252)
				letter = 'u';
			else
				letter = 'y';
			if (fntData.hasLowerCase == false)
				letter = ::toupper(letter);
		}

	return letter;
}

unsigned char UI_Font::defineAccent(unsigned char value)
{
	// determine the accent of an accentuated character
	unsigned char accent = '`';
	// grave, acute, circumflex, tilde, cedilla then diaresis
	if (value == 192 || value == 200 || value == 204 || value == 210 || value == 217 ||
		value == 224 || value == 232 || value == 236 || value == 242 || value == 249)
		accent = 96;
	else if (value == 193 || value == 201 || value == 205 || value == 211 || value == 218 || value == 221 ||
		value == 225 || value == 233 || value == 237 || value == 243 || value == 250 || value == 253)
		accent = 180;
	else if (value == 194 || value == 202 || value == 206 || value == 212 || value == 219 ||
		value == 226 || value == 234 || value == 238 || value == 244 || value == 251)
		accent = 136;
	else if (value == 195 || value == 209 || value == 213 ||
		value == 227 || value == 241 || value == 245)
		accent = 152;
	else if (value == 199 || value == 231)
		accent = 184;
	else
		accent = 168;
	return accent;
}

std::pair<unsigned int, unsigned int> UI_Font::getPrepCharWidth(std::pair<unsigned char, unsigned char> prepValue)
{
	if (prepValue.second != 0)
		return std::pair<unsigned int, unsigned int>(drawable_Characters.at(prepValue.first)->GetWidth(), drawable_Characters.at(prepValue.second)->GetWidth());
	else if (isSpaceChar(prepValue.first))
	{
		// char is space character
		if (prepValue.first == 32)
			return std::pair<unsigned int, unsigned int>(getSpaceWidth(), 0);
		else
			return std::pair<unsigned int, unsigned int>(getTabWidth(), 0);
	}
	else
		return std::pair<unsigned int, unsigned int>(drawable_Characters.at(prepValue.first)->GetWidth(), 0);
}

std::pair<unsigned int, unsigned int> UI_Font::getPrepCharHeight(std::pair<unsigned char, unsigned char> prepValue)
{
	if (prepValue.second != 0)
		return std::pair<unsigned int, unsigned int>(drawable_Characters.at(prepValue.first)->GetHeight(), drawable_Characters.at(prepValue.second)->GetHeight());
	else if (isSpaceChar(prepValue.first))
		return std::pair<unsigned int, unsigned int>(fntData.lignHeight, 0);
	else
		return std::pair<unsigned int, unsigned int>(drawable_Characters.at(prepValue.first)->GetHeight(), 0);
}

