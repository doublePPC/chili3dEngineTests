#include "UI_TextBox.h"

//UI_TextBox::UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, const std::string& text, float averageLetterSize)
//	: UI_Component(data, gfx, backgroundFilePath)
//{
//	// calculate visible Text Height in pixel
//	float lignHeightSize = averageLetterSize / (data.size.size * data.size.scaleY);
//	float pixelVerticalCount = (float)UI_Utils::getFontBaseTextHeight() / lignHeightSize;
//
//	// calculate visible Text Width in pixel
//	float pixelHorizontalCount = pixelVerticalCount / (data.size.size * data.size.scaleY) * (data.size.size * data.size.scaleX);
//
//	// setup visible surface
//	visibleText = std::make_shared<Surface>((unsigned int)pixelHorizontalCount, (unsigned int)pixelVerticalCount);
//}

UI_TextBox::UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, const std::string& text, unsigned int letterSize)
	: UI_Component(data, gfx, backgroundFilePath)
{
	// calculate visible lign count
	float lignHeight = UI_Math::CalculateTextLignHeight(letterSize);
	visibleLignCount = (unsigned int)(data.size.size * data.size.scaleY / lignHeight);
	unsigned int pixelHorizontalCount = (unsigned int)((float)UI_Utils::getFontBaseTextHeight() / lignHeight * (data.size.size * data.size.scaleX));
	unsigned int textRefCursor = 0;
	while (textRefCursor < text.length())
	{
		std::shared_ptr<std::string> lignText = UI_Utils::getTextLignFromString(pixelHorizontalCount, text, textRefCursor);
		std::shared_ptr<Surface> lignTextImage = UI_Utils::stringToSurface(*lignText);
		data.drawTech = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseSurfaceTextured);
		TechniqueBuilder::AutoFillerSurfaceTextured(data.drawTech, lignTextImage);
		textLigns.emplace_back(std::make_shared<UISquare>(gfx, data.size.size, data.size.scaleX, data.size.scaleY / (float)visibleLignCount, data.drawTech));	
	}
	baseOffset = (data.size.size * data.size.scaleY) / textLigns.size() * 2.0f;
	jump = 1.0f / textLigns.size();
	medianLign = textLigns.size() / 2.0f + 0.5f;
}

UI_TextBox::~UI_TextBox()
{
}

void UI_TextBox::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	UI_Component::AdjustPosToParent(inWorldPos, parentSize, parentXscale, parentYscale);
	for (unsigned int i = cursor; i < cursor + visibleLignCount; i++)
	{
		float distance = calculateDistance(i);
		DirectX::XMFLOAT3 lignInWorldPos = UI_Math::CalculatePtCoordFromPoint(GetInWorldPos(), { 0.0f, distance });
		textLigns[i]->SetPos(UI_Math::GetUI_Facing(), lignInWorldPos);
	}
}

void UI_TextBox::SubmitToChannel()
{
	UI_Component::SubmitToChannel();
	for (unsigned int i = cursor; i < cursor + visibleLignCount; i++)
	{
		textLigns[i]->Submit(Chan::main);
	}
}

void UI_TextBox::LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef)
{
	UI_Component::LinkTechniques(rgRef);
	for (unsigned int i = 0; i < textLigns.size(); i++)
	{
		textLigns[i]->LinkTechniques(rgRef);
	}
}

bool UI_TextBox::isLignVisible(unsigned int lignId)
{
	return lignId >= cursor && lignId < cursor + visibleLignCount;
}

float UI_TextBox::calculateDistance(unsigned int lignId)
{
	// central lign in an odd amount of visible ligns has same position than the component itself
	if ((float)lignId == medianLign || textLigns.size() == 1)
		return 0.0f;
	else if ((float)lignId < medianLign)
	{
		float offset;
		if ((unsigned int)medianLign % 2 != 0)
			offset = medianLign - (float)lignId;        // odd number of ligns
		else
			offset = medianLign - 0.5f - (float)lignId; // even number of ligns
		return (baseOffset + jump * offset) * -1.0f;
	}
	else
	{
		float offset;
		if ((unsigned int)medianLign % 2 != 0)
			offset = (float)lignId - medianLign;        // odd number of ligns
		else
			offset = (float)lignId - medianLign - 0.5f; // even number of ligns
		return baseOffset + jump * offset;
	}
}
