#include "UI_Component.h"

UI_Component::UI_Component(ComponentData data, Graphics& gfx)
{
	size = data.compBaseData.size;
	pctXpos = data.compBaseData.posX;
	pctYpos = data.compBaseData.posY;
	image = std::make_shared<TestSquare>(gfx, size, data.texturePath);
}

UI_Component::~UI_Component()
{
}

void UI_Component::AdjustPosToParent(DirectX::XMFLOAT4 parentData)
{
	DirectX::XMFLOAT3 pos = UI_Math::CalculatePosRelativeToParent(parentData, this->GetImgPosSizeData());
	image->SetPos(UI_Math::GetUI_Facing(), pos);
}

void UI_Component::SpawnControlWindow(Graphics& gfx)
{
	if (ImGui::Begin("Component"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pctXpos, -1.0f, 1.0f, "%.2f");
		ImGui::SliderFloat("Y", &pctYpos, -0.35f, 0.35f, "%.2f");
		ImGui::Text("");
	}
	ImGui::End();
}

DirectX::XMFLOAT4 UI_Component::GetImgPosSizeData()
{
	return {pctXpos, pctYpos, 0.0f, size};
}

std::shared_ptr<TestSquare> UI_Component::getImage()
{
	return image;
}

