#include "UI_Element.h"

UI_Element::UI_Element(ElementData data, Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	pos = { UnIntToPercentScreenFloat(data.elemBaseData.posX), UnIntToPercentScreenFloat(data.elemBaseData.posY) };
	dimension = { data.elemBaseData.size, data.elemBaseData.rectFactor };
	if (data.amountOfComponents > 0)
	{
		listUIcomponents.reserve(data.amountOfComponents);
		for (int i = 0; i < data.list_ComponentsData.size(); i++)
		{
			listUIcomponents.emplace_back(std::make_shared<TestSquare>(gfx, data.list_ComponentsData[i].compBaseData.size, data.list_ComponentsData[i].texturePath));
			listUIcomponents.back()->LinkTechniques(rgRef);
		}	
	}
	if (data.hasBackground)
	{
		background = std::make_shared<TestSquare>(gfx, dimension.x, "Images\\vase_plant.png");
		background->LinkTechniques(rgRef);
	}
	else
	{
		background = nullptr;
	}
}

UI_Element::~UI_Element()
{
}

void UI_Element::SubmitToChannel()
{
	if (background != nullptr)
	{
		background->Submit(Chan::main);
	}
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->Submit(Chan::main);
	}
}

void UI_Element::AdjustPos2Cam(DirectX::XMFLOAT3 ui_facing, DirectX::XMFLOAT3 elem_pos)
{
	if (background != nullptr)
	{
		background->SetPos(ui_facing, elem_pos);
	}
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->SetPos(ui_facing, elem_pos);
	}
}

void UI_Element::spawnControlWindows(Graphics& gfx)
{
	if (background != nullptr)
	{
		/*background->SpawnControlWindow(gfx);*/
		if (ImGui::Begin("Background"))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &pos.x, -1.25f, 1.25f, "%.2f");
			ImGui::SliderFloat("Y", &pos.y, -0.6f, 0.6f, "%.2f");
			ImGui::Text("");
		}
		ImGui::End();
	}
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		//listUIcomponents[i]->SpawnControlWindow(gfx);
		if (ImGui::Begin("Component"))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &pos.x, -1.5f, 1.5f, "%.2f");
			ImGui::SliderFloat("Y", &pos.y, -0.6f, 0.6f, "%.2f");
			ImGui::Text("");
		}
		ImGui::End();
	}
}

DirectX::XMFLOAT3 UI_Element::getPos()
{
	return {pos.x, pos.y, 0.0f};
}

