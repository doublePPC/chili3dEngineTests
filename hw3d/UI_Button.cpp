#include "UI_Button.h"
#include "Surface.h"

UI_Button::UI_Button(ComponentData data, Graphics& gfx, std::string textureFilePath, const std::string& buttonText, float textZoneScale)
	: UI_Component(data, gfx, textureFilePath)
{
	float textScaleX = data.size.scaleX;
	float textScaleY = data.size.scaleY;
	UI_Button::DefineTextScale(textScaleX, textScaleY, textZoneScale);

	data.drawTech = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseSurfaceTextured);
	std::shared_ptr<Surface> textImage = UI_Utils::stringToSurface(buttonText);
	UI_Utils::applyColorFilterToSurface(textImage, 128, 96, 192);
	TechniqueBuilder::AutoFillerSurfaceTextured(data.drawTech, textImage);
	textZone = std::make_shared<UISquare>(gfx, data.size.size, textScaleX, textScaleY, data.drawTech);
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

// private static block
void UI_Button::DefineTextScale(float& xValue, float& yValue, float scale)
{
	if (scale <= UI_Button::minimumTextScale)
	{
		xValue = UI_Button::minimumTextScale * xValue;
		yValue = UI_Button::minimumTextScale * yValue;
	}
	else if (scale <= 1.0f)
	{
		xValue = scale * xValue;
		yValue = scale * yValue;
	}
}
