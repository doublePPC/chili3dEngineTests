#pragma once
#include "Chili_UI.h"
#include "Engine_Interface.h"

class UI_Manager : public Chili_UI
{
public:
	UI_Manager(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef, float screenWidth, float screenHeight);
	UI_Manager() = delete;
	~UI_Manager();


private:

};