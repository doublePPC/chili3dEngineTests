#pragma once
#include "UI_Generics.h"
#include "FontCodex.h"

class UI_Font
{
public:
	// color related arithmetic
	static unsigned char baseColorAddition(unsigned char first, unsigned char second);
	// generic methods
	static bool isAccentuated(unsigned char value);
	static bool isAlpha(unsigned char value);
	static bool isNumerical(unsigned char value);
	static bool isSpaceChar(unsigned char value);
	static bool isAlphaNumerical(unsigned char value);
	static bool isPunctuationSymbol(unsigned char value);
public:
	UI_Font(const std::string& fontName, const std::string& filePath);
	UI_Font() = delete;
	~UI_Font();

	std::shared_ptr<Surface> getSurfaceFromString(const std::string& value);
	std::shared_ptr<Surface> getSurfaceFromChar(unsigned char value);

	unsigned int getCharWidth(unsigned char value);
	unsigned int getCharHeight(unsigned char value);
	unsigned int getLignHeight();
	unsigned int getSpaceWidth();
	unsigned int getTabWidth();
	void drawTextOnSurface(const TextLign& lign, std::shared_ptr<Surface> surface, const Police& police);

	void spawnControlWindow(Graphics& gfx);
private:
	void drawCharOnSurface(unsigned int start, std::shared_ptr<Surface> surface, std::pair<unsigned char, unsigned char> prepValue, Surface::Color color);
	void drawPixelOnSurface(unsigned int xPos, unsigned int yPos, unsigned int txCoordX, unsigned int txCoordY, std::shared_ptr<Surface> surface, unsigned char letter, Surface::Color color);
	unsigned char convertAlphaCase(unsigned char value);
	std::pair<unsigned char, unsigned char> prepareChar(unsigned char value);
	unsigned char defineChar(unsigned char value);
	unsigned char defineAccent(unsigned char value);
	std::pair<unsigned int, unsigned int> getPrepCharWidth(std::pair<unsigned char, unsigned char> prepValue);
	std::pair<unsigned int, unsigned int> getPrepCharHeight(std::pair<unsigned char, unsigned char> prepValue);
private:
	std::map<unsigned char, std::shared_ptr<Surface>> drawable_Characters;
	std::vector<CharacterData> charDatas;
	FontData fntData;
};