#include "UI_ScrollBar.h"

UI_ScrollBar::UI_ScrollBar(ComponentData data, Graphics& gfx, std::shared_ptr<Surface> scrollBar, const std::string& upPath, const std::string& downPath, const std::string& cursorPath)
	: UI_Component(data, gfx, scrollBar)
{
	std::shared_ptr<Surface> tempSurface;
	tempSurface = std::make_shared<Surface>(Surface::FromFile(upPath));
	UI_Utils::applyWhiteFadingTransparency(tempSurface);
	arrowUP = std::make_shared<UISquare>(gfx, data.size.size, data.size.scaleX, data.size.scaleY * UI_ScrollBar::scaleProportion, tempSurface);
	tempSurface = std::make_shared<Surface>(Surface::FromFile(downPath));
	UI_Utils::applyWhiteFadingTransparency(tempSurface);
	arrowDOWN = std::make_shared<UISquare>(gfx, data.size.size, data.size.scaleX, data.size.scaleY * UI_ScrollBar::scaleProportion, tempSurface);
	tempSurface = std::make_shared<Surface>(Surface::FromFile(cursorPath));
	UI_Utils::applyWhiteFadingTransparency(tempSurface);
	cursor = std::make_shared<UISquare>(gfx, data.size.size, data.size.scaleX * 0.5f, data.size.scaleY * UI_ScrollBar::scaleProportion, tempSurface);
}

UI_ScrollBar::~UI_ScrollBar()
{
}

void UI_ScrollBar::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	UI_Component::AdjustPosToParent(inWorldPos, parentSize, parentXscale, parentYscale);
	float topPos = parentSize * parentYscale * (1.0f - UI_ScrollBar::scaleProportion) / 4.0f;
	DirectX::XMFLOAT3 objectWorldPos = UI_Math::CalculatePtCoordFromPoint(GetInWorldPos(), { 0.0f, topPos });
	arrowUP->SetPos(UI_Math::GetUI_Facing(), objectWorldPos);
	objectWorldPos = UI_Math::CalculatePtCoordFromPoint(GetInWorldPos(), { 0.0f, topPos * -1.0f });
	arrowDOWN->SetPos(UI_Math::GetUI_Facing(), objectWorldPos);
	objectWorldPos = UI_Math::CalculatePtCoordFromPoint(GetInWorldPos(), { 0.0f, getCursorYpos(topPos) });
	cursor->SetPos(UI_Math::GetUI_Facing(), objectWorldPos);
}

void UI_ScrollBar::SubmitToChannel()
{
	UI_Component::SubmitToChannel();
	arrowUP->Submit(Chan::main);
	arrowDOWN->Submit(Chan::main);
	cursor->Submit(Chan::main);
}

void UI_ScrollBar::LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef)
{
	UI_Component::LinkTechniques(rgRef);
	arrowUP->LinkTechniques(rgRef);
	arrowDOWN->LinkTechniques(rgRef);
	cursor->LinkTechniques(rgRef);
}

void UI_ScrollBar::SpawnControlWindow(Graphics& gfx, int index)
{
}

float UI_ScrollBar::getCursorYpos(float topPos)
{
	return cursorCurPos * (1.0f - UI_ScrollBar::scaleProportion * 2.0f) * topPos;
}
