#include "UI_Font.h"
#include "Surface.h"

std::map<unsigned char, AccentData> UI_Font::accentData;
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
	if (UI_Font::accentData.contains(value))
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

void UI_Font::setupAccentData(std::map<unsigned char, AccentData>& mapRef)
{
	// Y
	mapRef.emplace(159, AccentData({89, 168}));
	// A
	mapRef.emplace(192, AccentData({ 65, 96 }));
	mapRef.emplace(193, AccentData({ 65, 180 }));
	mapRef.emplace(194, AccentData({ 65, 136 }));
	mapRef.emplace(195, AccentData({ 65, 152 }));
	mapRef.emplace(196, AccentData({ 65, 168 }));
	// C
	mapRef.emplace(199, AccentData({ 67, 184 }));
	// E
	mapRef.emplace(200, AccentData({ 69, 96 }));
	mapRef.emplace(201, AccentData({ 69, 180 }));
	mapRef.emplace(202, AccentData({ 69, 136 }));
	mapRef.emplace(203, AccentData({ 69, 168 }));
	// I
	mapRef.emplace(204, AccentData({ 73, 96 }));
	mapRef.emplace(205, AccentData({ 73, 180 }));
	mapRef.emplace(206, AccentData({ 73, 136 }));
	mapRef.emplace(207, AccentData({ 73, 168 }));
	// N
	mapRef.emplace(209, AccentData({ 78, 152 }));
	// O
	mapRef.emplace(210, AccentData({ 79, 96 }));
	mapRef.emplace(211, AccentData({ 79, 180 }));
	mapRef.emplace(212, AccentData({ 79, 136 }));
	mapRef.emplace(213, AccentData({ 79, 152 }));
	mapRef.emplace(214, AccentData({ 79, 168 }));
	// U
	mapRef.emplace(217, AccentData({ 85, 96 }));
	mapRef.emplace(218, AccentData({ 85, 180 }));
	mapRef.emplace(219, AccentData({ 85, 136 }));
	mapRef.emplace(220, AccentData({ 85, 168 }));
	// Y
	mapRef.emplace(221, AccentData({ 89, 180 }));
	// a
	mapRef.emplace(224, AccentData({ 97, 96 }));
	mapRef.emplace(225, AccentData({ 97, 180 }));
	mapRef.emplace(226, AccentData({ 97, 136 }));
	mapRef.emplace(227, AccentData({ 97, 152 }));
	mapRef.emplace(228, AccentData({ 97, 168 }));
	// c
	mapRef.emplace(231, AccentData({ 99, 184 }));
	// e
	mapRef.emplace(232, AccentData({ 101, 96 }));
	mapRef.emplace(233, AccentData({ 101, 180 }));
	mapRef.emplace(234, AccentData({ 101, 136 }));
	mapRef.emplace(235, AccentData({ 101, 168 }));
	// i
	mapRef.emplace(236, AccentData({ 129, 96 }));
	mapRef.emplace(237, AccentData({ 129, 180 }));
	mapRef.emplace(238, AccentData({ 129, 136 }));
	mapRef.emplace(239, AccentData({ 129, 168 }));
	// n
	mapRef.emplace(241, AccentData({ 110, 152 }));
	// o
	mapRef.emplace(242, AccentData({ 111, 96 }));
	mapRef.emplace(243, AccentData({ 111, 180 }));
	mapRef.emplace(244, AccentData({ 111, 136 }));
	mapRef.emplace(245, AccentData({ 111, 152 }));
	mapRef.emplace(246, AccentData({ 111, 168 }));
	// u
	mapRef.emplace(249, AccentData({ 117, 96 }));
	mapRef.emplace(250, AccentData({ 117, 180 }));
	mapRef.emplace(251, AccentData({ 117, 136 }));
	mapRef.emplace(252, AccentData({ 117, 168 }));
	// y
	mapRef.emplace(253, AccentData({ 121, 180 }));
	mapRef.emplace(255, AccentData({ 121, 168 }));
}

// ------------------------------

// ** public instances methods **
UI_Font::UI_Font(const std::string& fontName, const std::string& filePath)
{
	std::shared_ptr<Surface> tempSurface = std::make_shared<Surface>(Surface::FromFile(filePath));
	FontCodex::SetupFont(fontName, tempSurface, drawable_Characters, charDistance, fntData);
	//using json = nlohmann::json;
	//std::ifstream file;
	//file.open("Images\\DefaultFontData.json");
	//if (file.is_open())
	//{
	//	// check if file contains something
	//	file.seekg(0, file.end);
	//	unsigned int length = file.tellg();
	//	file.seekg(0, file.beg);
	//	if (length > 0)
	//	{
	//		json jFile = json::parse(file);
	//		fntData.drawingLignPos = jFile["Generic"]["DrawingLignPos"];
	//		fntData.lignHeight = jFile["Generic"]["LignHeight"];
	//		fntData.spaceWidth = jFile["Generic"]["SpaceWidth"];
	//		fntData.hasUpperCase = jFile["Generic"]["HasUpper"];
	//		fntData.hasLowerCase = jFile["Generic"]["HasLower"];
	//		fntData.hasAccents = jFile["Generic"]["HasAccent"];

	//		unsigned int startX, startY, width, height;
	//		for (unsigned int i = 0; i < jFile["SpecificSize"]; i++)
	//		{
	//			startX = jFile[std::to_string(i)]["StartX"];
	//			startY = jFile[std::to_string(i)]["StartY"];
	//			width = jFile[std::to_string(i)]["Width"];
	//			height = jFile[std::to_string(i)]["Height"];
	//			if (width > 0)
	//				charDistance.emplace(unsigned char(i), jFile[std::to_string(i)]["DistanceFromDrawingLign"]);
	//			// storing the surface data for the char
	//			if (width > 0)
	//			{
	//				drawable_Characters.emplace(unsigned char(i), std::make_shared<Surface>(width, height));
	//				for (int j = 0; j < width; j++)
	//				{
	//					for (int k = 0; k < height; k++)
	//					{
	//						auto color = tempSurface->GetPixel(startX + j, startY + k);
	//						color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
	//						drawable_Characters.at(i)->PutPixel(j, k, color);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//file.close();

	if(UI_Font::accentData.empty())
		UI_Font::setupAccentData(UI_Font::accentData);
}

UI_Font::~UI_Font()
{
}


std::shared_ptr<Surface> UI_Font::getSurfaceFromString(const std::string& value)
{
	// creates a single surface that contains all the content of the string in a lign
	std::shared_ptr<Surface> result = nullptr;

	if (drawable_Characters.empty() == false)
	{
		Surface::Color defaultColor = { 0, 255, 255, 255 };
		unsigned int cursorPos = 0;
		unsigned int textWidth = 0;
		std::pair<unsigned char, unsigned char> prepChar;
		for (unsigned int i = 0; i < value.length(); i++)
			textWidth += getCharWidth(value.at(i));
		result = std::make_shared<Surface>(textWidth, fntData.lignHeight);
		result->Clear(defaultColor);

		for (unsigned int i = 0; i < value.length(); i++)
		{
			if (drawable_Characters.contains(value.at(i)))     
			{
				if (value.at(i) == 32)
					cursorPos += fntData.spaceWidth;
				else if (value.at(i) == 9)
					cursorPos += getTabWidth();
				else
				{
					prepChar = prepareChar(value.at(i));
					drawCharOnSurface(cursorPos, result, prepChar.first, prepChar.second, defaultColor);
					cursorPos += drawable_Characters.at(value.at(i))->GetWidth();
				}
			}
		}
	}
	else
		result = getEmptySurface();
	
	return result;
}

std::shared_ptr<Surface> UI_Font::getSurfaceFromChar(unsigned char value)
{
	if (drawable_Characters.contains(value))
	{
		std::pair<unsigned char, unsigned char> prepValue = prepareChar(value);
		unsigned int width = getCharWidth(value);
		std::shared_ptr<Surface> result = std::make_shared<Surface>(width, fntData.lignHeight);
		result->Clear({ 0, 255, 255, 255 });
		drawCharOnSurface(0, result, prepValue.first, prepValue.second, { 0,0,0,0 });
		return result;
	}
	else
		return getEmptySurface();
}

unsigned int UI_Font::getCharWidth(unsigned char value)
{
	if (isSpaceChar(value))
	{
		if (value == 32)
			return getSpaceWidth();
		else
			return getTabWidth();
	}
	else if (drawable_Characters.contains(value))
		return drawable_Characters.at(value)->GetWidth();
	else if (isAccentuated(value))
	{
		if (fntData.hasAccents)
		{
			if (drawable_Characters.at(accentData.at(value).letter)->GetWidth() > drawable_Characters.at(accentData.at(value).accent)->GetWidth())
				return drawable_Characters.at(accentData.at(value).letter)->GetWidth(); // letter is larger than accent
			else
				return drawable_Characters.at(accentData.at(value).accent)->GetWidth(); // accent is larger than letter
		}
		else
			return drawable_Characters.at(accentData.at(value).letter)->GetWidth();
	}
	else
		return 0;
}

unsigned int UI_Font::getCharHeight(unsigned char value)
{
	if (isSpaceChar(value))
		return fntData.lignHeight;
	else if (drawable_Characters.contains(value))
		return drawable_Characters.at(value)->GetHeight();
	else if (isAccentuated(value))
	{
		if (fntData.hasAccents)
			return drawable_Characters.at(accentData.at(value).letter)->GetHeight() + drawable_Characters.at(accentData.at(value).accent)->GetHeight();
		else
			return drawable_Characters.at(accentData.at(value).letter)->GetHeight();			
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
		for (unsigned int j = 0; j < lign.content[i].text.length(); j++)
		{
			charDetail = prepareChar(lign.content[i].text.at(j));
			drawCharOnSurface(xCursor, surface, charDetail.first, charDetail.second, lign.content[i].tintEffect);
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
		value = "Size of Characters Distance : " + std::to_string(charDistance.size());
		ImGui::Text(value.c_str());
	}
	ImGui::End();
}


// ** private instances method **

void UI_Font::drawCharOnSurface(unsigned int start, std::shared_ptr<Surface> surface, unsigned char charToDraw, unsigned char accent, Surface::Color color)
{
	if(!isSpaceChar(charToDraw) && charToDraw > 0)
	{
		unsigned int charHeight = getCharHeight(charToDraw);
		unsigned int accentHeight = 0;
		unsigned int charWidth = getCharWidth(charToDraw);
		unsigned int accentWidth = 0;
		if (accent > 0)
		{
			accentHeight = getCharHeight(accent);
			accentWidth = getCharWidth(accent);
		}
		unsigned int yStart = fntData.drawingLignPos + 1 - charDistance.at(charToDraw) - charHeight;
		unsigned int xOffset = 0;
		// drawing the char (letter)
		if (accentWidth > charWidth)
			xOffset = (accentWidth - charWidth) / 2;
		for (unsigned int i = 0; i < charWidth; i++)
		{
			for (unsigned int j = 0; j < charHeight; j++)
			{
				if (i + start + xOffset < surface->GetWidth() && i + start + xOffset >= 0 &&
					yStart + j < surface->GetHeight() && yStart + j >= 0)
				{
					drawPixelOnSurface(i + start + xOffset, yStart + j, i, j, surface, charToDraw, color);
				}
			}
		}
		// drawing the accent (if there's any)
		if (accent > 0)
		{
			if (charDistance.at(accent) < 0)
				yStart = fntData.drawingLignPos + 1; // accent is a cedilla and has to be drawn below the letter
			else
				yStart = yStart - accentHeight - 1; // it's a top accent and has to be drawn above the letter
			if (charWidth > accentWidth)
				xOffset = (charWidth - accentWidth) / 2;
			else
				xOffset = 0;
			for (unsigned int i = 0; i < accentWidth; i++)
			{
				for (unsigned int j = 0; j < accentHeight; j++)
				{
					if (i + start + xOffset < surface->GetWidth() && i + start + xOffset >= 0 &&
						yStart + j < surface->GetHeight() && yStart + j >= 0)
					{
						drawPixelOnSurface(i + start + xOffset, yStart + j, i, j, surface, accent, color);
					}
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
	else if (fntData.hasLowerCase)
		return ::tolower(value);
	else
		return 0; // font doesn't have any alpha values
}

std::pair<unsigned char, unsigned char> UI_Font::prepareChar(unsigned char value)
{
	// this method assumes you checked that "value" is actually a drawable character
	if (isAccentuated(value))
	{
		unsigned char letter = accentData.at(value).letter;
		unsigned char accent = accentData.at(value).accent;
		letter = convertAlphaCase(letter);
		if (fntData.hasAccents == false)
			accent = 0;
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

std::shared_ptr<Surface> UI_Font::getEmptySurface()
{
	// used if the font instance failed to load its data from the json file
	// getSurfaceFromString and getSurfaceFromChar will return this default surface
	std::shared_ptr<Surface> result = nullptr;
	result = std::make_shared<Surface>(10, fntData.lignHeight);
	result->Clear({ 50, 64, 64, 64 });
	return result;
}
