#pragma once
#include "UI_Generics.h"
#include "UI_Font.h"
#include "Texture.h"
#include "UI_Graphics.h"

class UI_Utils
{
public:
	// font related methods
	static void loadFontFile(const std::string& fontName, const std::string& fileName);

	static std::shared_ptr<Surface> stringToSurface(const std::string& value, const std::string& fontName);
	static std::shared_ptr<Surface> charToSurface(unsigned char value, const std::string& fontName);
	static void applyColorFilterToSurface(std::shared_ptr<Surface> image, unsigned char red, unsigned char green, unsigned blue);

	static unsigned int getTextPixelWidth(const std::string& text, const std::string& fontName);
	static unsigned int getTextPixelWidth(std::shared_ptr<std::string> text, const std::string& fontName);
	static unsigned int getCharPixelWidth(unsigned char c, const std::string& fontName);
	static unsigned int getFontBaseTextHeight(const std::string& fontName);
	static unsigned int getFontSpaceWidth(const std::string& fontName);
	static void drawTextOnSurface(const TextLign& lign, std::shared_ptr<Surface> surface, const Police& police);

	static void spawnFontControlWindow(Graphics& gfx);
private:
	static std::unordered_map<std::string, std::unique_ptr<UI_Font>> textFonts;
};