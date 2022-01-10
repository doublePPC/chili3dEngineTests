#pragma once
#include "UI_Component.h"

class UI_TextBox : public UI_Component
{
public:
	UI_TextBox() = delete;
	UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, std::string text, float averageLetterSize);
	~UI_TextBox();
private:
	std::shared_ptr<Surface> text;
	std::shared_ptr<Surface> visibleText;
};
