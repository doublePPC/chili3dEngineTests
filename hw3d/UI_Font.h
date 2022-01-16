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

	std::shared_ptr<Surface> getSurfaceFromString(const std::string& value);
	std::shared_ptr<Surface> getSurfaceFromChar(unsigned char value);

	unsigned int getCharWidth(unsigned char value);
	unsigned int getCharHeight();
	unsigned int getSpaceWidth();
	void drawTextOnSurface(const txtFragment& text, std::shared_ptr<Surface> surface, surfaceCursor& cursor);

	void spawnControlWindow(Graphics& gfx);
private:
	bool isAlpha(unsigned char value);
	unsigned int getIndex(unsigned char value);
private:
	static void SetupFontHeader(std::vector<characterData>& container);
	static unsigned int SetTransparencyWhiteFading(unsigned int red, unsigned green, unsigned blue);
private:
	std::vector<std::shared_ptr<Surface>> list_Characters;
	std::vector<characterData> charDatas;
	unsigned int fontCharsHeight;
	unsigned int spaceWidth = 25;
	// test attributes
	int testValueStrLength = 0;
	std::string testValueStrValue;
	int testValuesStr2Int[4] = {0,0,0,0};
	int testValueTextWidth = 0;
};