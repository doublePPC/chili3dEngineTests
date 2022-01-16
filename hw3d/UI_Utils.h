#pragma once
#include "UI_Generics.h"
#include "UI_Font.h"
#include "Texture.h"
#include "UI_Graphics.h"

class UI_Utils
{
public:
	// font related methods
	static void loadFontFile(std::string fileName);

	static std::shared_ptr<Surface> stringToSurface(const std::string& value);
	static std::shared_ptr<Surface> charToSurface(unsigned char value);
	static void applyColorFilterToSurface(std::shared_ptr<Surface> image, unsigned char red, unsigned char green, unsigned blue);

	static unsigned int getTextPixelWidth(const std::string& text);
	static unsigned int getTextPixelWidth(std::shared_ptr<std::string> text);
	static unsigned int getCharPixelWidth(unsigned char c);
	static unsigned int getFontBaseTextHeight();
	static unsigned int getFontSpaceWidth();
	static std::shared_ptr<std::string> getWordFromText(const std::string& text, unsigned int startingPoint);
	static std::shared_ptr<std::string> getTextLignFromString(unsigned int horizontalPixelCount, const std::string& textRef, unsigned int& startingPoint);
	static void drawTextOnSurface(const txtFragment& text, std::shared_ptr<Surface> surface, surfaceCursor& cursor);

	static void spawnFontControlWindow(Graphics& gfx);
private:
	static std::unique_ptr<UI_Font> textFont;
};