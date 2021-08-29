#include "UI_Component.h"

UI_Component::UI_Component(ComponentData data, Graphics& gfx)
{
	datas = data.compData;
	image = std::make_shared<TestSquare>(gfx, datas.size.width, data.texturePath);
}

UI_Component::~UI_Component()
{
}

void UI_Component::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, Size parentSize)
{
	// I decided to build the struct data here instead of inParameters because the struct doesn't use relativePos but WorldPos
	PosAndSizeData parentData = { inWorldPos.x, inWorldPos.y, inWorldPos.z, parentSize.width, parentSize. height };
	DirectX::XMFLOAT3 pos = UI_Math::CalculatePosRelativeToParent(parentData, this->GetPosSizeData());
	image->SetPos(UI_Math::GetUI_Facing(), pos);
}

void UI_Component::SpawnControlWindow(Graphics& gfx)
{
	if (ImGui::Begin("Component"))
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
	}
	ImGui::End();
}

PosAndSizeData UI_Component::GetPosSizeData()
{
	return datas;
}

std::shared_ptr<TestSquare> UI_Component::getImage()
{
	return image;
}

