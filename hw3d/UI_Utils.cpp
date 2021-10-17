#include "UI_Utils.h"
#include "Surface.h"

std::unique_ptr<Surface> UI_Utils::textFont;

void UI_Utils::loadFontFile(std::string fileName)
{
	textFont = std::make_unique<Surface>(Surface::FromFile(fileName));
}

Surface UI_Utils::getFontFragment(int start, int width, int height)
{
	Surface s = Surface(width, height);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			s.PutPixel(i, j, textFont->GetPixel(start + i, start + j));
		}
	}

	return s;
}
