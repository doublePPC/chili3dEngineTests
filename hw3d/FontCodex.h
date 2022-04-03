#pragma once
#include "UI_Generics.h"
#include <fstream>
#include "Nlohmann/json.hpp"

class FontCodex
{
public:
	static void SetupFont(const std::string& fontName, std::shared_ptr<Surface> fontImage, std::map<unsigned char, std::shared_ptr<Surface>>& charImage, std::vector<CharacterData>& charData, FontData& fntData)
	{
		if (fontName == FONT_FUNKY)
			FontCodex::SetupFunky(fontImage, charImage, charData, fntData);
		else if (fontName == FONT_DEFAULT)
			FontCodex::SetupDefault(fontImage, charImage, charData, fntData);
	}
private:
	static void SetupFunky(std::shared_ptr<Surface> fontImage, std::map<unsigned char, std::shared_ptr<Surface>>& charImage, std::vector<CharacterData>& charData, FontData& fntData)
	{
		// setting up the font generic datas
		fntData.lignHeight = 110;
		fntData.drawingLignPos = 109;
		fntData.spaceWidth = 75;
		fntData.hasLowerCase = false;
		fntData.hasUpperCase = true;
		fntData.hasAccents = false;
		// setting up de specific characters datas
		charData.reserve(256);
		for (unsigned int i = 0; i < 256; i++)
		{
			charData.push_back({});
			charData[i].distFromDrawLine = 0;
			if (i >= 65 && i <= 90)
				charData[i].isCharDrawable = true; // capital letters
			else if (i >= 97 && i <= 122)
				charData[i].isCharDrawable = true; // lower case letters
			else if (i != 197 && i != 198 && i != 208 && i != 215 && i != 216 && i != 222 && i != 223 && i != 229 &&
				i != 230 && i != 240 && i != 247 && i != 248 && i != 254) // this condition reminds me I hate the unlogical order in the ascii table...
				charData[i].isCharDrawable = true; // accentuated letters
			else
				charData[i].isCharDrawable = false;
		}		
		// setting up the surfaces
		unsigned char value = 'A';
		unsigned int width = 80;
		unsigned int startX = 0;
		unsigned int startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter B
		value = 'B';
		width = 67;
		startX = 81;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter C
		value = 'C';
		width = 78;
		startX = 149;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter D
		value = 'D';
		width = 76;
		startX = 228;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter E
		value = 'E';
		width = 69;
		startX = 305;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter F
		value = 'F';
		width = 79;
		startX = 375;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter G
		value = 'G';
		width = 103;
		startX = 455;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter H
		value = 'H';
		width = 73;
		startX = 559;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter I
		value = 'I';
		width = 42;
		startX = 633;
		startY = 0;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter J
		value = 'J';
		width = 81;
		startX = 0;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter K
		value = 'K';
		width = 89;
		startX = 82;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter L
		value = 'L';
		width = 87;
		startX = 172;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter M
		value = 'M';
		width = 87;
		startX = 260;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter N
		value = 'N';
		width = 73;
		startX = 348;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter O
		value = 'O';
		width = 88;
		startX = 422;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter P
		value = 'P';
		width = 76;
		startX = 511;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter Q
		value = 'Q';
		width = 108;
		startX = 588;
		startY = 111;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter R
		value = 'R';
		width = 86;
		startX = 0;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter S
		value = 'S';
		width = 88;
		startX = 87;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter T
		value = 'T';
		width = 86;
		startX = 176;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter U
		value = 'U';
		width = 96;
		startX = 263;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter V
		value = 'V';
		width = 82;
		startX = 360;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter W
		value = 'W';
		width = 91;
		startX = 443;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter X
		value = 'X';
		width = 82;
		startX = 535;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//Letter Y
		value = 'Y';
		width = 72;
		startX = 618;
		startY = 222;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		//LetterZ
		value = 'Z';
		width = 91;
		startX = 0;
		startY = 333;
		charImage.emplace(value, std::make_shared<Surface>(width, fntData.lignHeight));
		for (unsigned int j = 0; j < width; j++)
		{
			for (unsigned int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		
	}

	static void SetupDefault(std::shared_ptr<Surface> fontImage, std::map<unsigned char, std::shared_ptr<Surface>>& charImage, std::vector<CharacterData>& charData, FontData& fntData);

	static unsigned int ApplyWhiteFadingTransparency(Surface::Color color)
	{
		unsigned int average = (color.GetR() + color.GetG() + color.GetB()) / 3;
		unsigned int result = 255 - average;
		if (result <= 20)
			result = 0;
		return result;
	}

	static std::pair<int, unsigned int> readInt(unsigned char* dataStream, unsigned int pos, unsigned int streamSize)
	{
		std::string dataToConvert = "";
		std::pair<int, unsigned int> result(0, 0);
		unsigned int i;
		int IsMinus = 1;
		for (i = pos; i < streamSize; i++)
		{
			if (dataStream[i] >= 48 && dataStream[i] <= 57)
				dataToConvert = dataToConvert + std::to_string(dataStream[i] - 48);
			else if (dataStream[i] == 45)
				IsMinus = -1;
			else if (dataToConvert != "")
				break;
		}
		result.first = std::stoi(dataToConvert) * IsMinus;
		result.second = i;
		return result;
	}
};

// *** deprecated file reading from txt format ***
//std::ifstream fntHeadFile;
//fntHeadFile.open("Images\\DefaultFontData.txt", std::ios::in);
//if (fntHeadFile)
//{
//	fntHeadFile.seekg(0, fntHeadFile.end);
//	auto length = fntHeadFile.tellg();
//	fntHeadFile.seekg(0, fntHeadFile.beg);
//	if (length > 0)
//	{
//		unsigned char* buffer;
//		buffer = new unsigned char[length];
//		fntHeadFile.read((char*)buffer, length);
//		std::pair<int, unsigned int> readResult(0, 0);
//
//		// read font data
//		readResult = FontCodex::readInt(buffer, readResult.second, length);
//		fntData.lignHeight = readResult.first;
//		readResult = FontCodex::readInt(buffer, readResult.second, length);
//		fntData.drawingLignPos = readResult.first;
//		readResult = FontCodex::readInt(buffer, readResult.second, length);
//		fntData.spaceWidth = readResult.first;
//		readResult = FontCodex::readInt(buffer, readResult.second, length);
//		fntData.hasUpperCase = (bool)readResult.first;
//		readResult = FontCodex::readInt(buffer, readResult.second, length);
//		fntData.hasLowerCase = (bool)readResult.first;
//		readResult = FontCodex::readInt(buffer, readResult.second, length);
//		fntData.hasAccents = (bool)readResult.first;
//		// specific charData
//		readResult = FontCodex::readInt(buffer, readResult.second, length);
//		charData.reserve(readResult.first);
//		int imgData[4];
//		for (unsigned int i = 0; i < 256; i++)
//		{
//			charData.push_back(CharacterData());
//			readResult = FontCodex::readInt(buffer, readResult.second, length);
//			imgData[0] = readResult.first;  // start X
//			readResult = FontCodex::readInt(buffer, readResult.second, length);
//			imgData[1] = readResult.first;  // start Y
//			readResult = FontCodex::readInt(buffer, readResult.second, length);
//			imgData[2] = readResult.first;  // width
//			readResult = FontCodex::readInt(buffer, readResult.second, length);
//			imgData[3] = readResult.first;  // height
//			readResult = FontCodex::readInt(buffer, readResult.second, length);
//			charData[i].distFromDrawLine = readResult.first;
//			readResult = FontCodex::readInt(buffer, readResult.second, length);
//			charData[i].isCharDrawable = readResult.first;
//			readResult = FontCodex::readInt(buffer, readResult.second, length);
//			charData[i].isAccentuated = readResult.first;
//			// acquiring the surface from the png file for the char
//			if (imgData[2] != 0 && imgData[3] != 0)
//			{
//				charImage.emplace(i, std::make_shared<Surface>(imgData[2], imgData[3]));
//				for (int j = 0; j < imgData[2]; j++)
//				{
//					for (int k = 0; k < imgData[3]; k++)
//					{
//						auto color = fontImage->GetPixel(imgData[0] + j, imgData[1] + k);
//						color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
//						charImage.at(i)->PutPixel(j, k, color);
//					}
//				}
//			}
//		}
//	}
//}