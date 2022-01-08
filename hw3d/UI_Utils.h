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

	static std::shared_ptr<Surface> stringToSurface(std::string value);
	static std::shared_ptr<Surface> charToSurface(unsigned char value);
	static void applyColorFilterToSurface(std::shared_ptr<Surface> image, unsigned char red, unsigned char green, unsigned blue);

	static unsigned int getTextPixelWidth(const std::string& text);
	static unsigned int getFontBaseTextHeight();
	static void drawTextOnSurface(const txtFragment& text, std::shared_ptr<Surface> surface, surfaceCursor& cursor);

	static void spawnFontControlWindow(Graphics& gfx);
private:
	static std::unique_ptr<UI_Font> textFont;
};