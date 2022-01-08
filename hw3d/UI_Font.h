#pragma once
#include  "UI_Generics.h"

struct characterData
{
	unsigned int width;
	unsigned int startingX;
	unsigned int startingY;
};

class UI_Font
{
public:
	// color related arithmetic
	static unsigned char baseColorAddition(unsigned char first, unsigned char second);
public:
	UI_Font(std::string filePath);
	UI_Font() = delete;
	~UI_Font();

	std::shared_ptr<Surface> getSurfaceFromString(std::string value);
	std::shared_ptr<Surface> getSurfaceFromChar(unsigned char value);

	unsigned int getCharWidth(unsigned char value);
	unsigned int getCharHeight();
	void drawTextOnSurface(const txtFragment& text, std::shared_ptr<Surface> surface, surfaceCursor& cursor);

	void spawnControlWindow(Graphics& gfx);
private:
	static void SetupFontHeader(std::vector<characterData>& container);
	static unsigned int SetTransparencyWhiteFading(unsigned int red, unsigned green, unsigned blue);
private:
	std::vector<std::shared_ptr<Surface>> list_Characters;
	std::vector<characterData> charDatas;
	int fontCharsHeight;
	// test attributes
	int testValueStrLength = 0;
	std::string testValueStrValue;
	int testValuesStr2Int[4] = {0,0,0,0};
	int testValueTextWidth = 0;
};