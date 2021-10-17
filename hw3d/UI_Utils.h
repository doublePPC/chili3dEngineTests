#pragma once
#include "UI_Generics.h"

class UI_Utils
{
public:
	// font related methods
	static void loadFontFile(std::string fileName);
	static Surface getFontFragment(int start, int width, int height);
private:
	static std::unique_ptr<Surface> textFont;
};