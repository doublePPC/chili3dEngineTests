#include "Chili_UI.h"


Chili_UI::Chili_UI(UIData data, float screenWidth, float screenHeight)
	: gfx(data.gfx),
	rgRef(data.rgRef)
{
	UI_Math::SaveScreenSizeValues(screenWidth, screenHeight);
	list_UiElements.reserve(data.amountOfElements);
	for (int i = 0; i < data.list_ElementsData.size(); i++)
	{
		list_UiElements.emplace_back(std::make_shared<UI_Element>(data.list_ElementsData[i], data.gfx, data.rgRef));
	}
}

Chili_UI::~Chili_UI()
{
}

void Chili_UI::update(DirectX::XMFLOAT3 camRot, DirectX::XMFLOAT3 camPos)
{
	UI_Math::Update(camRot, camPos);
	DirectX::XMFLOAT2 elemRelativePosition;

	// updating elements in the UI one by one
	for (int i = 0; i < list_UiElements.size(); i++)
	{
		elemRelativePosition = UI_Math::CalculatePosRelativeToScreen(list_UiElements[i]->getPos());
		list_UiElements[i]->AdjustPos2Cam(elemRelativePosition);
		list_UiElements[i]->SubmitToChannel();
	}
}

void Chili_UI::spawnControlWindows()
{
	if (ImGui::Begin("UI_Main"))
	{
		ImGui::Text("Last LeftClick Position");
		std::string value = "X : " + std::to_string(lastLeftClickX);
		ImGui::Text(value.c_str());
		value = "Y : " + std::to_string(lastLeftClickY);
		ImGui::Text(value.c_str());
		value = "Last left click was in : " + std::to_string(this->lastClickIn);
		ImGui::Text(value.c_str());
		//ImGui::SliderFloat("X", &datas.relPos.x, -1.0f, 1.0f, "%.2f");
		if (ImGui::Button("Click Me"))
		{
			if (!elementCreated)
			{
				ElementData newElementData;
				newElementData.hasBackground = false;
				newElementData.amountOfComponents = 1;
				newElementData.elemData.relPos = { -1.0f, -0.3f, 0.0f };
				newElementData.elemData.size = 0.6f;
				newElementData.elemData.scaleX = 1.0f;
				newElementData.elemData.scaleY = 1.0f;
				ComponentData newElementComponent = { newElementData.elemData, "Images\\kappa50.png" };
				newElementData.list_ComponentsData.push_back(newElementComponent);
				list_UiElements.emplace_back(std::make_shared<UI_Element>(newElementData, gfx, rgRef));
				elementCreated = true;
			}
		}
	}
	ImGui::End();
	for (int i = 0; i < list_UiElements.size(); i++)
	{
		list_UiElements[i]->spawnControlWindows(gfx, i);
	}
}

void Chili_UI::resetOnHoverState()
{
	for (int i = 0; i < list_UiElements.size(); i++)
	{
		list_UiElements[i]->resetOnHoverState();
	}
}

bool Chili_UI::onMouseEvent(float mouseX, float mouseY, mouseEvents event)
{
	std::pair<float, float> screenPos = UI_Math::MousePos2ScreenPos(mouseX, mouseY);
	this->lastLeftClickX = screenPos.first;
	this->lastLeftClickY = screenPos.second;
	bool clickDetected = false;
	short int counter = list_UiElements.size();
	while (counter > 0 && clickDetected == false)
	{
		clickDetected = list_UiElements[counter - 1]->onMouseEvent(screenPos.first, screenPos.second, event);
		if (!clickDetected)
		{
			list_UiElements[counter - 1]->componentHasBeenClicked(false);
		}
		counter--;
	}
	this->lastClickIn = clickDetected;
	if (clickDetected && list_UiElements.size() > 1)
	{
		this->changeElementFocus(counter);
	}
	return clickDetected;
}

void Chili_UI::changeElementFocus(int index)
{
	assert(index >= 0 && list_UiElements.empty() == false);
	std::shared_ptr<UI_Element> temporary = list_UiElements.back();
	list_UiElements.back() = list_UiElements[index];
	list_UiElements[index] = temporary;
}

