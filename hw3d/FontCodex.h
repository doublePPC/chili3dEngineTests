#pragma once
#include "UI_Generics.h"

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

	static void SetupFunky(std::shared_ptr<Surface> fontImage, std::map<unsigned char, std::shared_ptr<Surface>>& charImage, std::vector<CharacterData>& charData, FontData& fntData)
	{
		// setting up the font generic datas
		fntData.lignHeight = 110;
		fntData.drawingLignPos = 109;
		fntData.spaceWidth = 75;
		fntData.hasLowerCase = false;
		fntData.hasUpperCase = true;
		fntData.is256bits = false;
		// setting up de specific characters datas
		charData.reserve(256);
		for (unsigned int i = 0; i < 256; i++)
			charData.push_back({});
		for (unsigned int i = 65; i < 91; i++)
		{
			charData[i].isCharDrawable = true;
			charData[i].distFromDrawLine = 0;
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

	}
private:
	static unsigned int ApplyWhiteFadingTransparency(Surface::Color color)
	{
		unsigned int average = (color.GetR() + color.GetG() + color.GetB()) / 3;
		unsigned int result = 255 - average;
		if (result <= 20)
			result = 0;
		return result;
	}
};
