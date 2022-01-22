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
UI_Font::UI_Font(std::string filePath)
{
	this->fontCharsHeight = 110;
	UI_Font::SetupFontHeader(this->charDatas);
	std::shared_ptr<Surface> tempSurface = std::make_shared<Surface>(Surface::FromFile(filePath));
	list_Characters.reserve(26);
	for (int i = 0; i < 26; i++)
	{
		list_Characters.emplace_back(std::make_shared<Surface>(charDatas[i].width, fontCharsHeight));
		for (int j = 0; j < charDatas[i].width; j++)
		{
			for (int k = 0; k < fontCharsHeight; k++)
			{
				auto color = tempSurface->GetPixel(charDatas[i].startingX + j, charDatas[i].startingY + k);
				color.SetA(UI_Font::SetTransparencyWhiteFading(color.GetR(), color.GetG(), color.GetB()));
				list_Characters.back()->PutPixel(j, k, color);
			}
		}
	}
	testValueStrValue = "not yet defined";
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
	for (unsigned int i = 0; i < value.length(); i++)
	{
		if (isAlpha(value.at(i)))
			textWidth += charDatas[getIndex(value.at(i))].width;
		else if (value.at(i) == 32)
			textWidth += spaceWidth;
		else if (value.at(i) == 9)
			textWidth += getTabWidth();
	}
	result = std::make_shared<Surface>(textWidth, fontCharsHeight);
	result->Clear({ 0, 255, 255, 255 });

	for (unsigned int i = 0; i < value.length(); i++)
	{
		if (isAlpha(value.at(i)))
		{
			for (int j = 0; j < charDatas[getIndex(value.at(i))].width; j++)
			{
				for (int k = 0; k < fontCharsHeight; k++)
				{
					result->PutPixel(cursorPos + j, k, list_Characters[getIndex(value.at(i))]->GetPixel(j, k));
				}
			}
			cursorPos += charDatas[getIndex(value.at(i))].width;
		}
		else if (value.at(i) == 32)
			cursorPos += spaceWidth;
		else if (value.at(i) == 9)
			cursorPos += getTabWidth();
	}
	return result;
}

std::shared_ptr<Surface> UI_Font::getSurfaceFromChar(unsigned char value)
{
	if(isAlpha(value))
	{
		value = ::toupper(value);
		return list_Characters[value - 65];
	}
	else if(isSpaceChar(value))
	{
		std::shared_ptr<Surface> result = nullptr;
		unsigned int width = 1;
		if (value == 32)
			width = spaceWidth;
		else if (value == 9)
			width = getTabWidth();
		result = std::make_shared<Surface>(width, fontCharsHeight);
		result->Clear({ 0, 255, 255, 255 });
		return result;
	}
	else
	{
		std::shared_ptr<Surface> result = nullptr;
		result = std::make_shared<Surface>(10, fontCharsHeight);
		result->Clear({ 0, 255, 255, 255 });
		return result;
	}
}


unsigned int UI_Font::getCharWidth(unsigned char value)
{
	if (isAlpha(value))
		return charDatas[getIndex(value)].width;
	else if (value == 32)
		return spaceWidth;
	else if (value == 9)
		return this->getTabWidth();
	else
		return 0;
}

unsigned int UI_Font::getCharHeight()
{
	return fontCharsHeight;
}

unsigned int UI_Font::getSpaceWidth()
{
	return spaceWidth;
}

unsigned int UI_Font::getTabWidth()
{
	return spaceWidth * 5;
}

void UI_Font::drawTextOnSurface(const txtFragment& text, std::shared_ptr<Surface> surface, surfaceCursor& cursor)
{
	// TODO : add a warning if you get out of bound
	for (unsigned int i = 0; i < text.text.length(); i++)
	{
		unsigned int horizontalLooper = 0;
		unsigned int nextCharWidth = 0;
		// get next char width
		if (isAlpha(text.text.at(i)))
			nextCharWidth = charDatas[getIndex(text.text.at(i))].width;
		else if (text.text.at(i) == 32)
			nextCharWidth = spaceWidth;
		while (horizontalLooper + cursor.begX < cursor.maxX && horizontalLooper < nextCharWidth)
		{
			for (unsigned int verticalLooper = 0; verticalLooper < fontCharsHeight; verticalLooper++)
			{
				Surface::Color pixelColor = { 0, 255, 255, 255 };
				if(isAlpha(text.text.at(i)))
					pixelColor = list_Characters[getIndex(text.text.at(i))]->GetPixel(horizontalLooper, verticalLooper);
				if (text.tintEffect.GetA() > 0 && pixelColor.GetA() > 0)
				{
					pixelColor.SetR(UI_Font::baseColorAddition(text.tintEffect.GetR(), pixelColor.GetR()));
					pixelColor.SetG(UI_Font::baseColorAddition(text.tintEffect.GetG(), pixelColor.GetG()));
					pixelColor.SetB(UI_Font::baseColorAddition(text.tintEffect.GetB(), pixelColor.GetB()));
				}
				surface->PutPixel(horizontalLooper + cursor.begX, verticalLooper + cursor.begY, pixelColor);
			}
			horizontalLooper++;
		}
		cursor.begX = horizontalLooper + cursor.begX;
	}
}



void UI_Font::spawnControlWindow(Graphics& gfx)
{
	if (ImGui::Begin("Text Font"))
	{
		std::string value = "Amount of Characters : " + std::to_string(list_Characters.size());
		ImGui::Text(value.c_str());
		value = "Detail vector size : " + std::to_string(charDatas.size());
		ImGui::Text(value.c_str());
		/*value = "String Length : " + std::to_string(testValueStrLength);
		ImGui::Text(value.c_str());
		ImGui::Text(testValueStrValue.c_str());
		value = "Char 1 as int : " + std::to_string(testValuesStr2Int[0]);
		ImGui::Text(value.c_str());
		value = "Char 2 as int : " + std::to_string(testValuesStr2Int[1]);
		ImGui::Text(value.c_str());
		value = "Char 3 as int : " + std::to_string(testValuesStr2Int[2]);
		ImGui::Text(value.c_str());
		value = "Char 4 as int : " + std::to_string(testValuesStr2Int[3]);
		ImGui::Text(value.c_str());
		value = "Text Width : " + std::to_string(testValueTextWidth);
		ImGui::Text(value.c_str());*/
	}
	ImGui::End();
}

// ** private instances method **

unsigned int UI_Font::getIndex(unsigned char value)
{
	assert(isAlpha(value));
	if (value >= 65 && value <= 90)
		return value - 65;
	else
		return value - 97;
}

// ** font file loading static methods **
void UI_Font::SetupFontHeader(std::vector<characterData>& container)
{
	// creation of the data blocks
	container.reserve(26);
	for (int i = 0; i < 26; i++)
		container.push_back({});
	// these datas should be read from a file... to be done later
	//Letter A
	container[0].width = 80;
	container[0].startingX = 0;
	container[0].startingY = 0;
	//Letter B
	container[1].width = 67;
	container[1].startingX = 81;
	container[1].startingY = 0;
	//Letter C
	container[2].width = 78;
	container[2].startingX = 149;
	container[2].startingY = 0;
	//Letter D
	container[3].width = 76;
	container[3].startingX = 228;
	container[3].startingY = 0;
	//Letter E
	container[4].width = 69;
	container[4].startingX = 305;
	container[4].startingY = 0;
	//Letter F
	container[5].width = 79;
	container[5].startingX = 375;
	container[5].startingY = 0;
	//Letter G
	container[6].width = 103;
	container[6].startingX = 455;
	container[6].startingY = 0;
	//Letter H
	container[7].width = 73;
	container[7].startingX = 559;
	container[7].startingY = 0;
	//Letter I
	container[8].width = 42;
	container[8].startingX = 633;
	container[8].startingY = 0;
	//Letter J
	container[9].width = 81;
	container[9].startingX = 0;
	container[9].startingY = 111;
	//Letter K
	container[10].width = 89;
	container[10].startingX = 82;
	container[10].startingY = 111;
	//Letter L
	container[11].width = 87;
	container[11].startingX = 172;
	container[11].startingY = 111;
	//Letter M
	container[12].width = 87;
	container[12].startingX = 260;
	container[12].startingY = 111;
	//Letter N
	container[13].width = 73;
	container[13].startingX = 348;
	container[13].startingY = 111;
	//Letter O
	container[14].width = 88;
	container[14].startingX = 422;
	container[14].startingY = 111;
	//Letter P
	container[15].width = 76;
	container[15].startingX = 511;
	container[15].startingY = 111;
	//Letter Q
	container[16].width = 108;
	container[16].startingX = 588;
	container[16].startingY = 111;
	//Letter R
	container[17].width = 86;
	container[17].startingX = 0;
	container[17].startingY = 222;
	//Letter S
	container[18].width = 88;
	container[18].startingX = 87;
	container[18].startingY = 222;
	//Letter T
	container[19].width = 86;
	container[19].startingX = 176;
	container[19].startingY = 222;
	//Letter U
	container[20].width = 96;
	container[20].startingX = 263;
	container[20].startingY = 222;
	//Letter V
	container[21].width = 82;
	container[21].startingX = 360;
	container[21].startingY = 222;
	//Letter W
	container[22].width = 91;
	container[22].startingX = 443;
	container[22].startingY = 222;
	//Letter X
	container[23].width = 82;
	container[23].startingX = 535;
	container[23].startingY = 222;
	//Letter Y
	container[24].width = 72;
	container[24].startingX = 618;
	container[24].startingY = 222;
	//LetterZ
	container[25].width = 91;
	container[25].startingX = 0;
	container[25].startingY = 333;
}

unsigned int UI_Font::SetTransparencyWhiteFading(unsigned int red, unsigned green, unsigned blue)
{
	unsigned int average = (red + green + blue) / 3;
	unsigned int result = 255 - average;
	if (result <= 20)
		result = 0;
	return result;
}


