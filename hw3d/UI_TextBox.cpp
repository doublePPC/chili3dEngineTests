#include "UI_TextBox.h"

UI_TextBox::UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, std::string text, float averageLetterSize)
	: UI_Component(data, gfx, backgroundFilePath)
{
	// calculate visible Text Height in pixel
	float lignHeightSize = averageLetterSize / (data.size.size * data.size.scaleY);
	float pixelVerticalCount = (float)UI_Utils::getFontBaseTextHeight() / lignHeightSize;

	// calculate visible Text Width in pixel
	float pixelHorizontalCount = pixelVerticalCount / (data.size.size * data.size.scaleY) * (data.size.size * data.size.scaleX);

	// setup visible surface
	visibleText = std::make_shared<Surface>((unsigned int)pixelHorizontalCount, (unsigned int)pixelVerticalCount);
}

UI_TextBox::~UI_TextBox()
{
}
