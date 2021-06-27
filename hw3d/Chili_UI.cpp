#include "Chili_UI.h"

Chili_UI::Chili_UI(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	uiElement = std::make_unique<UI_Element>(0.0f, 0.0f, 2.0f, 2.0f);
	uiElement->BuildComponents(gfx, rgRef);
}

Chili_UI::~Chili_UI()
{
}

void Chili_UI::update(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef, DirectX::XMFLOAT3 camRot, DirectX::XMFLOAT3 camPos)
{
	uiElement->AdjustPos2Cam(camRot, camPos);
	uiElement->SubmitToChannel();
}

void Chili_UI::spawnControlWindows(Graphics& gfx)
{
	uiElement->spawnControlWindows(gfx);
}



