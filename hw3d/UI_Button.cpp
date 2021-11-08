#include "UI_Button.h"
#include "Surface.h"

UI_Button::UI_Button(ComponentData data, Graphics& gfx, std::string textureFilePath, std::string buttonText)
	: UI_Component(data, gfx, textureFilePath)
{
	float textScaleX = 0.9f * data.size.scaleX;
	float textScaleY = 0.9f * data.size.scaleY;
	textZone = std::make_shared<UISquare>(gfx, data.size.size, textScaleX, textScaleY, UI_Utils::stringToSurface(buttonText));
}

UI_Button::~UI_Button()
{
}

void UI_Button::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	UI_Component::AdjustPosToParent(inWorldPos, parentSize, parentXscale, parentYscale);
	textZone->SetPos(UI_Math::GetUI_Facing(), GetInWorldPos());
}

void UI_Button::SubmitToChannel()
{
	UI_Component::SubmitToChannel();
	textZone->Submit(Chan::main);
}

void UI_Button::LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef)
{
	UI_Component::LinkTechniques(rgRef);
	textZone->LinkTechniques(rgRef);
}
