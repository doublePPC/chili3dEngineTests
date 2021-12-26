#include "App_UImanager.h"

UI_Manager::UI_Manager(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef, float screenWidth, float screenHeight)
	: Chili_UI(gfx, rgRef, screenWidth, screenHeight)
{
}

UI_Manager::~UI_Manager()
{
}
