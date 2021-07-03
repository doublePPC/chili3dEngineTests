#include "Chili_UI.h"
#include "ChiliMath.h"

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
	// determine the center point and rotation of the UI interface
	DirectX::XMFLOAT3 ui_facing, ui_centerPoint;
	
	float hypothenuse = cos(camRot.y);
	float xFactor = sin(camRot.z) * hypothenuse;
	float zFactor = cos(camRot.z) * hypothenuse;

	ui_centerPoint.x = camPos.x + xFactor;
	ui_centerPoint.y = camPos.y - sin(camRot.y);
	ui_centerPoint.z = camPos.z + zFactor;

	ui_facing.x = camRot.y;               
	ui_facing.y = camRot.z + to_rad(45);
	ui_facing.z = 0.0f;

	// updating elements in the UI one by one
	uiElement->AdjustPos2Cam(ui_facing, ui_centerPoint, camRot.y, camRot.z);
	uiElement->SubmitToChannel();
}

void Chili_UI::spawnControlWindows(Graphics& gfx)
{
	uiElement->spawnControlWindows(gfx);
}



