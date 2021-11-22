#include "UI_Component.h"
#include "Surface.h"

UI_Component::UI_Component(ComponentData data, Graphics& gfx, std::string textureFilePath)
{
	relPos = data.relPos;
	size = data.size;
	DirectX::XMFLOAT4 tint = { 0.0f, 1.0f, 0.0f, 0.0f};
	image = std::make_shared<UISquare>(gfx, size.size, size.scaleX, size.scaleY, textureFilePath, tint);;
}

UI_Component::UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<Surface> textImage)
{
	relPos = data.relPos;
	size = data.size;
	image = std::make_shared<UISquare>(gfx, size.size, size.scaleX, size.scaleY, textImage);
}

UI_Component::UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<Technique> drawTechnique, ModelBuilder& modelRef)
{
	relPos = data.relPos;
	size = data.size;
	image = std::make_shared<UISquare>(gfx, size.scaleX, size.scaleY, drawTechnique, modelRef);
}

UI_Component::UI_Component(ComponentData data, Graphics& gfx, std::vector<std::shared_ptr<Technique>>& drawTechniques, ModelBuilder& modelRef)
{
	relPos = data.relPos;
	size = data.size;
	image = std::make_shared<UISquare>(gfx, size.scaleX, size.scaleY, drawTechniques, modelRef);
}

UI_Component::~UI_Component()
{
}

void UI_Component::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	// I decided to build the struct data here instead of inParameters because the struct doesn't use relativePos but WorldPos
	RelativePosition parentPos = { inWorldPos.x, inWorldPos.y, inWorldPos.z };
	Size parentSizeData = { parentSize, parentXscale, parentYscale };
	DirectX::XMFLOAT2 relPos = UI_Math::CalculatePosRelativeToParent(parentPos, parentSizeData, this->GetRelativePosition(), this->GetSize());
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
	//image->SpawnControlWindow(gfx);
}

RelativePosition UI_Component::GetRelativePosition()
{
	return relPos;
}

Size UI_Component::GetSize()
{
	return size;
}

DirectX::XMFLOAT3 UI_Component::GetInWorldPos()
{
	return image->getPos();
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

void UI_Component::manageLeftClick()
{
	state = true;
	relPos.x = -1.0f;
}

void UI_Component::manageRightClick()
{
	state = false;
	relPos.x = 1.0f;
}

void UI_Component::manageOnHover()
{
	mouseIsOnHover = true;
}

void UI_Component::resetOnHoverState()
{
	mouseIsOnHover = false;
}

void UI_Component::evaluateCornersPosition(DirectX::XMFLOAT2 relPos)
{
	float halfWidth = UI_Math::CalculateWidth(size.size, size.scaleX) / 2.0f;
	float halfHeight = UI_Math::CalculateHeight(size.size, size.scaleY) / 2.0f;
	relTopLeft = { relPos.x - halfWidth , relPos.y - halfHeight };
	relBotRight = { relPos.x + halfWidth, relPos.y + halfHeight };
}


