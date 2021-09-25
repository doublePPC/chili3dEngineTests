#include "UI_Element.h"

UI_Element::UI_Element(ElementData data, Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	datas = data.elemData;
	topLeft = { 100.0f, 100.0f };
	botRight = { 100.0f, 100.0f };
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
		//background = std::make_shared<TestSquare>(gfx, datas.size, datas.scaleX, datas.scaleY, "Images\\stripes.png" );
		DirectX::XMFLOAT3 color = { 0.9f, 0.9f, 0.9f };
		background = std::make_shared<TestSquare>(gfx, datas.size, datas.scaleX, datas.scaleY, color);
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

void UI_Element::AdjustPos2Cam(DirectX::XMFLOAT2 elem_pos)
{
	DirectX::XMFLOAT3 elemInWorldPos = UI_Math::CalculatePtCoordFromCenter(elem_pos);
	topLeft = UI_Math::CalculateTopLeft(elem_pos.x, elem_pos.y, datas.size * datas.scaleX, datas.size * datas.scaleY);
	botRight = UI_Math::CalculateBotRight(elem_pos.x, elem_pos.y, datas.size * datas.scaleX, datas.size * datas.scaleY);
	if (background != nullptr)
	{
		background->SetPos(UI_Math::GetUI_Facing(), elemInWorldPos);
	}
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->AdjustPosToParent(elemInWorldPos, datas.size, datas.scaleX, datas.scaleY );
	}
}

void UI_Element::spawnControlWindows(Graphics& gfx, int index)
{
	if (background != nullptr)
	{
		std::string windowName = "Background " + std::to_string(index);
		if (ImGui::Begin(windowName.c_str()))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &datas.relPos.x, -1.0f, 1.0f, "%.2f");
			ImGui::SliderFloat("Y", &datas.relPos.y, -1.0f, 1.0f, "%.2f");
			ImGui::Text("");
			std::string cornerData = "TopLeft pos : X = " + std::to_string(topLeft.first) + "  Y = " + std::to_string(topLeft.second);
			ImGui::Text(cornerData.c_str());
			cornerData = "BotRight pos : X = " + std::to_string(botRight.first) + "  Y = " + std::to_string(botRight.second);
			ImGui::Text(cornerData.c_str());
			ImGui::Text("");
			DirectX::XMFLOAT3 posDetails = background->getPos();
			std::string sqrXpos = "X : " + std::to_string(posDetails.x);
			std::string sqrYpos = "Y : " + std::to_string(posDetails.y);
			std::string sqrZpos = "Z : " + std::to_string(posDetails.z);
			ImGui::Text(sqrXpos.c_str());
			ImGui::Text(sqrYpos.c_str());
			ImGui::Text(sqrZpos.c_str());
		}
		ImGui::End();
	}
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->SpawnControlWindow(gfx, i);
	}
}

bool UI_Element::onLeftClick(float clicX, float clicY)
{
	bool elementClicked = this->mouseClickCheckup(clicX, clicY);
	return elementClicked;
}

PosAndSize UI_Element::getPos()
{
	return datas;
}

bool UI_Element::mouseClickCheckup(float clicX, float clicY)
{
	// assuming the element is rect shaped
	return clicX > this->topLeft.first && clicX < this->botRight.first
		&& clicY > this->topLeft.second && clicY < this->botRight.second;
}



