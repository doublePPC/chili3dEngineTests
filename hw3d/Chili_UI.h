#pragma once
//#include "Camera.h"
#include "UI_Generics.h"
#include "UI_Element.h"

class Chili_UI
{
public:
	Chili_UI(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef);
	Chili_UI() = delete;
	~Chili_UI();

	void update(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef);
private:
	std::unique_ptr<UI_Element> uiElement;
};