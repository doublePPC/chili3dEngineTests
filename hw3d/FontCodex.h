#pragma once
#include "UI_Generics.h"
#include <fstream>

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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
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
			for (int k = 0; k < fntData.lignHeight; k++)
			{
				auto color = fontImage->GetPixel(startX + j, startY + k);
				color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
				charImage.at(value)->PutPixel(j, k, color);
			}
		}
		
	}

	static void SetupDefault(std::shared_ptr<Surface> fontImage, std::map<unsigned char, std::shared_ptr<Surface>>& charImage, std::vector<CharacterData>& charData, FontData& fntData)
	{
		std::string dataLine;
		std::ifstream fntHeadFile;
		int imgData[6];
		// setting up the font generic datas
		fntData.lignHeight = 28;
		fntData.drawingLignPos = 21;
		fntData.spaceWidth = 16;
		fntData.hasLowerCase = true;
		fntData.hasUpperCase = true;
		fntData.hasAccents = true;
		charData.reserve(256);
		for (unsigned int i = 0; i < 256; i++)
				charData.push_back({ false, 0 });
		// picking data from the header file
		fntHeadFile.open("Images\\DefaultFontHeader.txt");
		if (fntHeadFile.is_open())
		{
			while (fntHeadFile.eof() == false)
			{
				for (unsigned int i = 0; i < 6; i++)
				{
					std::getline(fntHeadFile, dataLine, ' ');
					imgData[i] = std::stoi(dataLine);
				}
				charData[imgData[0]].isCharDrawable = true;
				charData[imgData[0]].distFromDrawLine = imgData[3];
				charImage.emplace(imgData[0], std::make_shared<Surface>(imgData[4], imgData[5]));
				for (unsigned int j = 0; j < imgData[4]; j++)
				{
					for (int k = 0; k < imgData[5]; k++)
					{
						auto color = fontImage->GetPixel(imgData[1] + j, imgData[2] + k);
						color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
						charImage.at(imgData[0])->PutPixel(j, k, color);
					}
				}
			}
		}
		for (unsigned int i = 192; i < 256; i++)
		{
			// stating accentuated characters are actually drawable
			if (i != 197 && i != 198 && i != 208 && i != 215 && i != 216 && i != 222 && i != 223 && i != 229 &&
				i != 230 && i != 240 && i != 247 && i != 248 && i != 254)
				charData[i].isCharDrawable = true;
			// this condition reminds me I hate the unlogical order in the ascii table...
		}
		fntHeadFile.close();
		charData[9].isCharDrawable = true;
		charData[32].isCharDrawable = true;
	}

	static unsigned int ApplyWhiteFadingTransparency(Surface::Color color)
	{
		unsigned int average = (color.GetR() + color.GetG() + color.GetB()) / 3;
		unsigned int result = 255 - average;
		if (result <= 20)
			result = 0;
		return result;
	}

};
