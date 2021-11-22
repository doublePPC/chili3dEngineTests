#include "Chili_UI.h"


Chili_UI::Chili_UI(UIData data, float screenWidth, float screenHeight)
	: gfx(data.gfx),
	rgRef(data.rgRef)
{
	UI_Math::SaveScreenSizeValues(screenWidth, screenHeight);
	UI_Utils::loadFontFile("Images\\FunkyFont.jpg");
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
		elemRelativePosition = UI_Math::CalculatePosRelativeToScreen(list_UiElements[i]->getRelativePosition(), list_UiElements[i]->getSize());
		list_UiElements[i]->AdjustPos2Cam(elemRelativePosition);
		list_UiElements[i]->SubmitToChannel();
	}
}

void Chili_UI::spawnControlWindows()
{
	UI_Utils::spawnFontControlWindow(gfx);
	if (ImGui::Begin("UI_Main"))
	{
		ImGui::Text("Last LeftClick Position");
		std::string value = "X : " + std::to_string(lastLeftClickX);
		ImGui::Text(value.c_str());
		value = "Y : " + std::to_string(lastLeftClickY);
		ImGui::Text(value.c_str());
		value = "Last left click was in : " + std::to_string(this->lastClickIn);
		ImGui::Text(value.c_str());
		if (ImGui::Button("Click Me"))
		{
			if (!elementCreated)
			{
				ElementData newElementData;
				newElementData.hasBackground = false;
				newElementData.amountOfComponents = 0;
				newElementData.relPos = { -1.0f, -0.3f, 0.0f };
				newElementData.size = { 0.3f, 1.0f, 1.0f };
				list_UiElements.emplace_back(std::make_shared<UI_Element>(newElementData, gfx, rgRef));

				ComponentData compData = { newElementData.relPos, newElementData.size };
				ModelBuilder model(UI_Plane::Make(), 0.3f);
				std::shared_ptr<StepBuilder> drawStep = std::make_shared<StepBuilder>(model, "UIelementDraw", gfx);
				StepBuilder::AutoFiller_UIElementDrawStep(drawStep);
				//drawTechnique->AddStep(gfx, "TintedTextured2D_PS", "Images\\kappa50.png");
				std::shared_ptr<Technique> drawTech = std::make_shared<Technique>(Chan::main);
				StepBuilder::AssembleMainTechnique(drawTech, drawStep);
				std::shared_ptr<UI_Component> newElemComponent = std::make_shared<UI_Component>(compData, gfx, drawTech, model);
				list_UiElements.back()->addComponent(newElemComponent, rgRef);

				elementCreated = true;
			}
		}
		if (ImGui::Button("Click Me Too"))
		{
			if (!element2Created)
			{
				ElementData newElementData;
				newElementData.hasBackground = false;
				newElementData.amountOfComponents = 0;
				newElementData.relPos = { 0.5f, -0.3f, 0.0f };
				newElementData.size = { 0.3f, 1.0f, 1.0f };
				//ComponentData newElementComponent = { newElementData.relPos, newElementData.size };
				//newElementComponent.imgData.textImage = "P";
				//newElementData.list_ComponentsData.push_back(newElementComponent);
				list_UiElements.emplace_back(std::make_shared<UI_Element>(newElementData, gfx, rgRef));

				ComponentData buttonData = { newElementData.relPos, newElementData.size };
				std::string buttonFilePath = "Images\\buttonIcon.png";
				std::string buttonText = "UP";
				std::shared_ptr<UI_Button> testButton = std::make_shared<UI_Button>(buttonData, gfx, buttonFilePath, buttonText);
				list_UiElements.back()->addComponent(testButton, rgRef);

				element2Created = true;
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
	if (clickDetected && list_UiElements.size() > 1 && event != mouseEvents::onHover)
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

