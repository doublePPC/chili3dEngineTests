#include "FontCodex.h"


void FontCodex::SetupDefault(std::shared_ptr<Surface> fontImage, std::map<unsigned char, std::shared_ptr<Surface>>& charImage, std::map<unsigned char, int>& charData, FontData& fntData)
{
	using json = nlohmann::json;
	std::ifstream file;
	file.open("Images\\DefaultFontData.json");
	if (file.is_open())
	{
		// check if file contains something
		file.seekg(0, file.end);
		unsigned int length = file.tellg();
		file.seekg(0, file.beg);
		if (length > 0)
		{
			json jFile = json::parse(file);
			// generic datas
			fntData.drawingLignPos = jFile["Generic"]["DrawingLignPos"];
			fntData.lignHeight = jFile["Generic"]["LignHeight"];
			fntData.spaceWidth = jFile["Generic"]["SpaceWidth"];
			fntData.hasUpperCase = jFile["Generic"]["HasUpper"];
			fntData.hasLowerCase = jFile["Generic"]["HasLower"];
			fntData.hasAccents = jFile["Generic"]["HasAccent"];
			// specific datas
			unsigned int startX, startY,  width, height;
			for (unsigned int i = 0; i < jFile["SpecificSize"]; i++)
			{
				startX = jFile[std::to_string(i)]["StartX"];
				startY = jFile[std::to_string(i)]["StartY"];
				width = jFile[std::to_string(i)]["Width"];
				height = jFile[std::to_string(i)]["Height"];
				if(width > 0)
					charData.emplace(unsigned char(i), jFile[std::to_string(i)]["DistanceFromDrawingLign"]);
				// storing the surface data for the char
				if (width != 0 && height != 0)
				{
					charImage.emplace(i, std::make_shared<Surface>(width, height));
					for (int j = 0; j < width; j++)
					{
						for (int k = 0; k < height; k++)
						{
							auto color = fontImage->GetPixel(startX + j, startY + k);
							color.SetA(FontCodex::ApplyWhiteFadingTransparency(color));
							charImage.at(i)->PutPixel(j, k, color);
						}
					}
				}
			}
		}
		else
		{
			// TODO : send error message that system tried to open an empty file 
		}
	}
	else
	{
		// TODO : send error message that the file couldn't be opened
	}
	file.close();
}
