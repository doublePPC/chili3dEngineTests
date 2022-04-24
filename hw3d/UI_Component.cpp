#include "UI_Component.h"
#include "Surface.h"

UI_Component::UI_Component(ComponentData data, Graphics& gfx, const std::string& textureFilePath)
{
	relPos = data.relPos;
	size = data.size;
	DirectX::XMFLOAT4 tint = { 0.5f, 0.5f, 0.5f, 0.4f};
	image = std::make_shared<UISquare>(gfx, size.size, size.scaleX, size.scaleY, textureFilePath, tint);
}

UI_Component::UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<Surface> textImage)
{
	relPos = data.relPos;
	size = data.size;
	image = std::make_shared<UISquare>(gfx, size.size, size.scaleX, size.scaleY, textImage);
}

UI_Component::UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<TechniqueBuilder> drawTech)
{
	relPos = data.relPos;
	size = data.size;
	image = std::make_shared<UISquare>(gfx, size.size, size.scaleX, size.scaleY, drawTech);
}

UI_Component::~UI_Component()
{
}


// Public methods
void UI_Component::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	Size parentSizeData = { parentSize, parentXscale, parentYscale };
	DirectX::XMFLOAT2 relPos = UI_Math::CalculatePosRelativeToParent(parentSizeData, this->GetRelativePosition(), this->GetSize());
	DirectX::XMFLOAT3 compWorldPos = UI_Math::CalculatePtCoordFromPoint(inWorldPos, relPos);
	image->SetPos(UI_Math::GetUI_Facing(), compWorldPos);
	evaluateCornersPosition(relPos);
}

void UI_Component::SubmitToChannel()
{
	image->Submit(Chan::main);
}

void UI_Component::LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef)
{
	image->LinkTechniques(rgRef);
}

void UI_Component::SpawnControlWindow(Graphics& gfx, int index)
{
	std::string windowName = "Component " + std::to_string(index);
	if (ImGui::Begin(windowName.c_str()))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &relPos.x, -1.0f, 1.0f, "%.2f");
		ImGui::SliderFloat("Y", &relPos.y, -1.0f, 1.0f, "%.2f");
		ImGui::Text("");
		DirectX::XMFLOAT3 posDetails = image->getPos();
		std::string sqrXpos = "X : " + std::to_string(posDetails.x);
		std::string sqrYpos = "Y : " + std::to_string(posDetails.y);
		std::string sqrZpos = "Z : " + std::to_string(posDetails.z);
		ImGui::Text(sqrXpos.c_str());
		ImGui::Text(sqrYpos.c_str());
		ImGui::Text(sqrZpos.c_str());
		std::string cornerData = "TopLeft pos : X = " + std::to_string(relTopLeft.first) + "  Y = " + std::to_string(relTopLeft.second);
		ImGui::Text(cornerData.c_str());
		cornerData = "BotRight pos : X = " + std::to_string(relBotRight.first) + "  Y = " + std::to_string(relBotRight.second);
		ImGui::Text(cornerData.c_str());
		cornerData = "Mouse is onHover : " + std::to_string(this->mouseIsOnHover);
		ImGui::Text(cornerData.c_str());
	}
	ImGui::End();
}

RelativePosition UI_Component::GetRelativePosition()
{
	return relPos;
}

Size UI_Component::GetSize()
{
	return size;
}

std::shared_ptr<UISquare> UI_Component::getImage()
{
	return image;
}

std::pair<float, float> UI_Component::getTopLeft()
{
	return relTopLeft;
}

std::pair<float, float> UI_Component::getBotRight()
{
	return relBotRight;
}

void UI_Component::manageMouseEvent(float clicX, float clicY, mouseEvents _event)
{
	switch (_event)
	{
	case(mouseEvents::leftClick):
	{
		manageLeftClick();
		break;
	}
	case(mouseEvents::rightClick):
	{
		manageRightClick();
		break;
	}
	case(mouseEvents::onHover):
	{
		manageOnHover();
		break;
	}
	}
}

void UI_Component::resetOnHoverState()
{
	mouseIsOnHover = false;
}
// --------------------------------


// Protected Methods
void UI_Component::manageLeftClick()
{
}

void UI_Component::manageRightClick()
{
}

void UI_Component::manageOnHover()
{
	mouseIsOnHover = true;
}

DirectX::XMFLOAT3 UI_Component::GetInWorldPos()
{
	return image->getPos();
}
// -------------------------------


// Private Methods
void UI_Component::evaluateCornersPosition(DirectX::XMFLOAT2 relPos)
{
	float halfWidth = UI_Math::CalculateWidth(size.size, size.scaleX) / 2.0f;
	float halfHeight = UI_Math::CalculateHeight(size.size, size.scaleY) / 2.0f;
	relTopLeft = { relPos.x - halfWidth , relPos.y - halfHeight };
	relBotRight = { relPos.x + halfWidth, relPos.y + halfHeight };
}
// -------------------------------


