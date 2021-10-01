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
	float halfWidth = UI_Math::CalculateWidth(datas.size, datas.scaleX) / 2.0f;
	float halfHeight = UI_Math::CalculateHeight(datas.size, datas.scaleY) / 2.0f;
	topLeft = UI_Math::CalculateTopLeft(elem_pos.x, elem_pos.y, halfWidth, halfHeight);
	botRight = UI_Math::CalculateBotRight(elem_pos.x, elem_pos.y, halfWidth, halfHeight);
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
			cornerData = "A component has been clicked : " + std::to_string(this->aComponentHasBeenClicked);
			ImGui::Text(cornerData.c_str());
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
	if (elementClicked)
	{
		this->manageLeftClick(clicX, clicY);
	}
	return elementClicked;
}

PosAndSize UI_Element::getPos()
{
	return datas;
}

void UI_Element::componentHasBeenClicked(bool value)
{
	this->aComponentHasBeenClicked = value;
}

bool UI_Element::mouseClickCheckup(float clicX, float clicY)
{
	// assuming the element is rect shaped
	return clicX > this->topLeft.first && clicX < this->botRight.first
		&& clicY > this->topLeft.second && clicY < this->botRight.second;
}

void UI_Element::manageLeftClick(float clicX, float clicY)
{
	std::pair<float, float> mouseConvertedPos = this->convertMouseClick(clicX, clicY);
	bool clickedComponentDetected = false;
	short int loopCounter = listUIcomponents.size();
	while (loopCounter > 0 && clickedComponentDetected == false)
	{
		std::pair<float, float> currentCompTopLeft = listUIcomponents[loopCounter - 1]->getTopLeft();
		std::pair<float, float> currentCompBotRight = listUIcomponents[loopCounter - 1]->getBotRight();
		clickedComponentDetected = currentCompTopLeft.first < mouseConvertedPos.first && 
			currentCompBotRight.first > mouseConvertedPos.first &&
			currentCompTopLeft.second < mouseConvertedPos.second &&
			currentCompBotRight.second > mouseConvertedPos.second;
		loopCounter--;
	}
	componentHasBeenClicked(clickedComponentDetected);
}

std::pair<float, float> UI_Element::convertMouseClick(float clicX, float clicY)
{
	// get where is the click in percentage within the element
	std::pair<float, float> axisRanges;
	std::pair<float, float> clickRelPos;
	axisRanges.first = botRight.first - topLeft.first;
	clickRelPos.first = clicX - topLeft.first;
	clickRelPos.first = clickRelPos.first / axisRanges.first;
	axisRanges.second = botRight.second - topLeft.second;
	clickRelPos.second = clicY - topLeft.second;
	clickRelPos.second = clickRelPos.second / axisRanges.second;

	// get where is the click within the size
	float width = botRight.first - topLeft.first;
	float height = botRight.second - topLeft.second;
	clickRelPos.first = -1 + clickRelPos.first * 2.0f;
	clickRelPos.first = clickRelPos.first * width / 2.0f;
	clickRelPos.second = -1 + clickRelPos.second * 2.0f;
	clickRelPos.second = clickRelPos.second * height / 2.0f;

	return clickRelPos;
}



