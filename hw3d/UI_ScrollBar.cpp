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
	// top arrow pos
	Size size = { this->GetSize().size, this->GetSize().scaleX , this->GetSize().scaleY * UI_ScrollBar::scaleProportion };
	DirectX::XMFLOAT2 relPos = UI_Math::CalculatePosRelativeToParent(this->GetSize(), { 0.0f, 1.0f }, size);
	DirectX::XMFLOAT3 compWorldPos = UI_Math::CalculatePtCoordFromPoint(this->GetInWorldPos(), relPos);
	arrowUP->SetPos(UI_Math::GetUI_Facing(), compWorldPos);
	// down arrow pos
	relPos = UI_Math::CalculatePosRelativeToParent(this->GetSize(), { 0.0f, -1.0f }, size);
	compWorldPos = UI_Math::CalculatePtCoordFromPoint(this->GetInWorldPos(), relPos);
	arrowDOWN->SetPos(UI_Math::GetUI_Facing(), compWorldPos);
	// cursor pos
	size.scaleX = size.scaleX * 0.5f;
	relPos = UI_Math::CalculatePosRelativeToParent(this->GetSize(), { 0.0f, cursorCurPos}, size);
	compWorldPos = UI_Math::CalculatePtCoordFromPoint(this->GetInWorldPos(), relPos);
	cursor->SetPos(UI_Math::GetUI_Facing(), compWorldPos);
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

void UI_ScrollBar::setCursorRelativePos(float newRelPos)
{
	cursorCurPos = 0.8f - newRelPos * 1.6f;
}

float UI_ScrollBar::getCursorYpos(float topPos)
{
	return cursorCurPos * (1.0f - UI_ScrollBar::scaleProportion * 2.0f) * topPos;
}
