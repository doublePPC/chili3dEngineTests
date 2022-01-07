#pragma once
#include "UI_Generics.h"
#include "UI_Font.h"
#include "Texture.h"

class UI_Utils
{
public:
	// font related methods
	static void loadFontFile(std::string fileName);
	static std::shared_ptr<Surface> stringToSurface(std::string value);
	static std::shared_ptr<Surface> charToSurface(char value);
	static void applyColorFilterToSurface(std::shared_ptr<Surface> image, unsigned char red, unsigned char green, unsigned blue);
	static void spawnFontControlWindow(Graphics& gfx);

	// color related arithmetic
	static unsigned char baseColorAddition(unsigned char first, unsigned char second);
private:
	static std::unique_ptr<UI_Font> textFont;
};