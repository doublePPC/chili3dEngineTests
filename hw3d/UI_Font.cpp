#include "UI_Font.h"
#include "Surface.h"

UI_Font::UI_Font(std::string filePath)
{
	UI_Font::SetupFontHeader(this->charDatas);
	std::shared_ptr<Surface> tempSurface = std::make_shared<Surface>(Surface::FromFile(filePath));
	list_Characters.reserve(26);
	for (int i = 0; i < 26; i++)
	{
		list_Characters.emplace_back(std::make_shared<Surface>(charDatas[i].width, charDatas[i].height));
		for (int j = 0; j < charDatas[i].width; j++)
		{
			for (int k = 0; k < charDatas[i].height; k++)
			{
				list_Characters.back()->PutPixel(j, k, tempSurface->GetPixel(charDatas[i].startingX + j, charDatas[i].startingY + k));
			}
		}
	}
	testValueStrValue = "not yet defined";
}

UI_Font::~UI_Font()
{
}

std::shared_ptr<Surface> UI_Font::getSurfaceFromString(std::string value)
{
	// creates a single surface that contains all the content of the string in a lign
	// not to be used for text zones where it is possible to write and erase characters
	std::shared_ptr<Surface> result = nullptr;

	std::vector<char> charValue;
	int textLength = value.length();
	charValue.reserve(textLength);
	for (int i = 0; i < textLength; i++)
	{
		charValue[i] = value.at(i);
	}
	testValueStrLength = textLength;
	testValueStrValue = value.c_str();

	std::vector<int> charIdx;
	charIdx.reserve(textLength);
	for (int i = 0; i < textLength; i++)
	{
		charIdx[i] = (int)charValue[i] - 65;
		testValuesStr2Int[i] = charIdx[i];
	}

	int textWidth = 0;
	for (int i = 0; i < textLength; i++)
	{
		if(charIdx[i] >= 0 && charIdx[i] < 26)
			textWidth += charDatas[charIdx[i]].width;
	}
	testValueTextWidth = textWidth;
	result = std::make_shared<Surface>(textWidth, 109);
	result->Clear({ 0, 255, 255, 255 });

	int cursorPos = 0;
	for (int i = 0; i < textLength; i++)
	{
		if (charIdx[i] >= 0 && charIdx[i] < 26)
		{
			for (int j = 0; j < charDatas[charIdx[i]].width; j++)
			{
				for (int k = 0; k < charDatas[charIdx[i]].height; k++)
				{
					result->PutPixel(cursorPos + j, k, list_Characters[charIdx[i]]->GetPixel(j, k));
				}
			}
			cursorPos += charDatas[charIdx[i]].width;
		}
	}
	return result;
}

std::shared_ptr<Surface> UI_Font::getSurfaceFromChar(int asciiCharCode)
{
	int charIdx = asciiCharCode - 65;
	return list_Characters[charIdx];
}

void UI_Font::spawnControlWindow(Graphics& gfx)
{
	if (ImGui::Begin("Text Font"))
	{
		std::string value = "Amount of Characters : " + std::to_string(list_Characters.size());
		ImGui::Text(value.c_str());
		value = "Detail vector size : " + std::to_string(charDatas.size());
		ImGui::Text(value.c_str());
		value = "String Length : " + std::to_string(testValueStrLength);
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
		ImGui::Text(value.c_str());
	}
	ImGui::End();
}

void UI_Font::SetupFontHeader(std::vector<characterData>& container)
{
	// creation of the data blocks
	container.reserve(26);
	for (int i = 0; i < 26; i++)
		container.push_back({});
	// these datas should be read from a file... to be done later
	//Letter A
	container[0].width = 80;
	container[0].height = 84;
	container[0].startingX = 0;
	container[0].startingY = 0;
	//Letter B
	container[1].width = 67;
	container[1].height = 84;
	container[1].startingX = 81;
	container[1].startingY = 0;
	//Letter C
	container[2].width = 78;
	container[2].height = 84;
	container[2].startingX = 149;
	container[2].startingY = 0;
	//Letter D
	container[3].width = 76;
	container[3].height = 84;
	container[3].startingX = 228;
	container[3].startingY = 0;
	//Letter E
	container[4].width = 69;
	container[4].height = 84;
	container[4].startingX = 305;
	container[4].startingY = 0;
	//Letter F
	container[5].width = 79;
	container[5].height = 87;
	container[5].startingX = 375;
	container[5].startingY = 0;
	//Letter G
	container[6].width = 103;
	container[6].height = 91;
	container[6].startingX = 0;
	container[6].startingY = 88;
	//Letter H
	container[7].width = 73;
	container[7].height = 107;
	container[7].startingX = 104;
	container[7].startingY = 88;
	//Letter I
	container[8].width = 42;
	container[8].height = 107;
	container[8].startingX = 178;
	container[8].startingY = 88;
	//Letter J
	container[9].width = 81;
	container[9].height = 109;
	container[9].startingX = 221;
	container[9].startingY = 88;
	//Letter K
	container[10].width = 89;
	container[10].height = 91;
	container[10].startingX = 303;
	container[10].startingY = 88;
	//Letter L
	container[11].width = 87;
	container[11].height = 98;
	container[11].startingX = 0;
	container[11].startingY = 198;
	//Letter M
	container[12].width = 88;
	container[12].height = 98;
	container[12].startingX = 88;
	container[12].startingY = 198;
	//Letter N
	container[13].width = 73;
	container[13].height = 98;
	container[13].startingX = 177;
	container[13].startingY = 198;
	//Letter O
	container[14].width = 88;
	container[14].height = 98;
	container[14].startingX = 251;
	container[14].startingY = 198;
	//Letter P
	container[15].width = 76;
	container[15].height = 101;
	container[15].startingX = 340;
	container[15].startingY = 198;
	//Letter Q
	container[16].width = 109;
	container[16].height = 101;
	container[16].startingX = 0;
	container[16].startingY = 300;
	//Letter R
	container[17].width = 86;
	container[17].height = 101;
	container[17].startingX = 110;
	container[17].startingY = 300;
	//Letter S
	container[18].width = 88;
	container[18].height = 101;
	container[18].startingX = 197;
	container[18].startingY = 300;
	//Letter T
	container[19].width = 86;
	container[19].height = 101;
	container[19].startingX = 286;
	container[19].startingY = 300;
	//Letter U
	container[20].width = 96;
	container[20].height = 90;
	container[20].startingX = 373;
	container[20].startingY = 300;
	//Letter V
	container[21].width = 82;
	container[21].height = 92;
	container[21].startingX = 0;
	container[21].startingY = 402;
	//Letter W
	container[22].width = 91;
	container[22].height = 93;
	container[22].startingX = 83;
	container[22].startingY = 402;
	//Letter X
	container[23].width = 82;
	container[23].height = 83;
	container[23].startingX = 175;
	container[23].startingY = 402;
	//Letter Y
	container[24].width = 71;
	container[24].height = 88;
	container[24].startingX = 258;
	container[24].startingY = 402;
	//LetterZ
	container[25].width = 91;
	container[25].height = 95;
	container[25].startingX = 330;
	container[25].startingY = 402;
}


