#include "UI_Component.h"

UI_Component::UI_Component(ComponentData data, Graphics& gfx)
{
	datas = data.compData;
	DirectX::XMFLOAT4 tint = { 255.0f, 0.0f, 0.0f, 0.1f };
	image = std::make_shared<TestSquare>(gfx, datas.size, datas.scaleX, datas.scaleY, data.texturePath, tint);;
}

UI_Component::~UI_Component()
{
}

void UI_Component::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	// I decided to build the struct data here instead of inParameters because the struct doesn't use relativePos but WorldPos
	PosAndSize parentData = { inWorldPos.x, inWorldPos.y, inWorldPos.z, parentSize, parentXscale, parentYscale };
	DirectX::XMFLOAT2 relPos = UI_Math::CalculatePosRelativeToParent(parentData, this->GetPosSizeData());
	DirectX::XMFLOAT3 compWorldPos = UI_Math::CalculatePtCoordFromPoint(inWorldPos, relPos);
	image->SetPos(UI_Math::GetUI_Facing(), compWorldPos);
	evaluateCornersPosition(relPos);
}

void UI_Component::SubmitToChannel()
{
	image->Submit(Chan::main);
}

void UI_Component::SpawnControlWindow(Graphics& gfx, int index)
{
	std::string windowName = "Component " + std::to_string(index);
	if (ImGui::Begin(windowName.c_str()))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &datas.relPos.x, -1.0f, 1.0f, "%.2f");
		ImGui::SliderFloat("Y", &datas.relPos.y, -1.0f, 1.0f, "%.2f");
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

PosAndSize UI_Component::GetPosSizeData()
{
	return datas;
}

std::shared_ptr<TestSquare> UI_Component::getImage()
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
	datas.relPos.x = -1.0f;
}

void UI_Component::manageRightClick()
{
	state = false;
	datas.relPos.x = 1.0f;
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
	float halfWidth = UI_Math::CalculateWidth(datas.size, datas.scaleX) / 2.0f;
	float halfHeight = UI_Math::CalculateHeight(datas.size, datas.scaleY) / 2.0f;
	relTopLeft = { relPos.x - halfWidth , relPos.y - halfHeight };
	relBotRight = { relPos.x + halfWidth, relPos.y + halfHeight };
}


