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
	// generic methods
	static bool isAlpha(unsigned char value);
	static bool isNumerical(unsigned char value);
	static bool isSpaceChar(unsigned char value);
	static bool isAlphaNumerical(unsigned char value);
	static bool isPunctuationSymbol(unsigned char value);
public:
	UI_Font(std::string filePath);
	UI_Font() = delete;
	~UI_Font();

	std::shared_ptr<Surface> getSurfaceFromString(const std::string& value);
	std::shared_ptr<Surface> getSurfaceFromChar(unsigned char value);

	unsigned int getCharWidth(unsigned char value);
	unsigned int getCharHeight();
	unsigned int getSpaceWidth();
	unsigned int getTabWidth();
	void drawTextOnSurface(const TextLign& lign, std::shared_ptr<Surface> surface, const Police& police);

	void spawnControlWindow(Graphics& gfx);
private:
	unsigned int getIndex(unsigned char value);
	void drawCharOnSurface(unsigned int start, std::shared_ptr<Surface> surface, unsigned char letter, Surface::Color color);
private:
	static void SetupFontHeader(std::vector<characterData>& container);
	static unsigned int SetTransparencyWhiteFading(unsigned int red, unsigned green, unsigned blue);
private:
	std::vector<std::shared_ptr<Surface>> list_Characters;
	std::vector<characterData> charDatas;
	unsigned int fontCharsHeight;
	unsigned int spaceWidth = 75;
};