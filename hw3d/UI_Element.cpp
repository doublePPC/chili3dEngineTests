#include "UI_Element.h"

UI_Element::UI_Element(ElementData data, Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	pos = { data.elemBaseData.posX, data.elemBaseData.posY };
	size = data.elemBaseData.size;
	if (data.amountOfComponents > 0)
	{
		listUIcomponents.reserve(data.amountOfComponents);
		for (int i = 0; i < data.list_ComponentsData.size(); i++)
		{
			listUIcomponents.emplace_back(std::make_shared<UI_Component>(data.list_ComponentsData[i], gfx));
			listUIcomponents.back()->getImage()->LinkTechniques(rgRef);
		}	
	}
	if (data.hasBackground)
	{
		//background = std::make_shared<TestSquare>(gfx, dimension.x, "Images\\vase_plant.png");
		background = std::make_shared<TestSquare>(gfx, size);
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
		listUIcomponents[i]->getImage()->Submit(Chan::main);
	}
}

void UI_Element::AdjustPos2Cam(DirectX::XMFLOAT3 elem_pos)
{
	if (background != nullptr)
	{
		background->SetPos(UI_Math::GetUI_Facing(), elem_pos);
	}
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->AdjustPosToParent({elem_pos.x, elem_pos.y, elem_pos.z, size});
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
			ImGui::SliderFloat("X", &pos.x, -1.0f, 1.0f, "%.2f");
			ImGui::SliderFloat("Y", &pos.y, -0.35f, 0.35f, "%.2f");
			ImGui::Text("");
		}
		ImGui::End();
	}
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->SpawnControlWindow(gfx);
	}
}

DirectX::XMFLOAT4 UI_Element::getPos()
{
	return {pos.x, pos.y, 0.0f, size};
}



