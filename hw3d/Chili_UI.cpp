#include "Chili_UI.h"


Chili_UI::Chili_UI(UIData data, float screenWidth, float screenHeight)
	: gfx(data.gfx),
	rgRef(data.rgRef)
{
	UI_Math::SaveScreenSizeValues(screenWidth, screenHeight);
	UI_Utils::loadFontFile(FONT_DEFAULT, "Images\\DefaultFont.png");
	UI_Utils::loadFontFile(FONT_FUNKY , "Images\\FunkyFont.jpg");
	
	list_UiElements.reserve(data.amountOfElements);
	for (int i = 0; i < data.list_ElementsData.size(); i++)
	{
		list_UiElements.emplace_back(std::make_shared<UI_Element>(data.list_ElementsData[i], data.gfx, data.rgRef));
	}
}

Chili_UI::Chili_UI(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef, float screenWidth, float screenHeight)
	: gfx(gfx),
	rgRef(rgRef)
{
	UI_Math::SaveScreenSizeValues(screenWidth, screenHeight);
	UI_Utils::loadFontFile(FONT_DEFAULT, "Images\\DefaultFont.png");
	UI_Utils::loadFontFile(FONT_FUNKY, "Images\\FunkyFont.jpg");
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
		value = "ImGui Window Width : " + std::to_string(width);
		ImGui::Text(value.c_str());
		value = "ImGui Window Height : " + std::to_string(height);
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
				std::shared_ptr<TechniqueBuilder> tech;
				tech = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseFileTextured);
				TechniqueBuilder::AutoFillerFileTextured(tech, "Images\\kappa50.png");
				
				std::shared_ptr<UI_Component> newElemComponent = std::make_shared<UI_Component>(compData, gfx, tech);
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
				list_UiElements.emplace_back(std::make_shared<UI_Element>(newElementData, gfx, rgRef));

				ComponentData buttonData = { newElementData.relPos, newElementData.size };
				std::string buttonFilePath = "Images\\buttonIcon.png";
				std::string buttonText = "UP";
				std::shared_ptr<UI_Button> testButton = std::make_shared<UI_Button>(buttonData, gfx, buttonFilePath, buttonText, -1.0f);
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

void Chili_UI::addElement(ElementData newElem)
{
	list_UiElements.emplace_back(std::make_shared<UI_Element>(newElem, gfx, rgRef));
}

void Chili_UI::addComponentToLastElement(std::shared_ptr<UI_Component> preBuiltComp, Rgph::BlurOutlineRenderGraph& rgRef)
{
	if (list_UiElements.size() > 0)
	{
		list_UiElements.back()->addComponent(preBuiltComp, rgRef);
	}
	else
	{
		// TODO : send warning that an attempt was made to build a component in an empty UI structure
	}
}

void Chili_UI::adjustScreenSize(int width, int height)
{
	UI_Math::SaveScreenSizeValues(width, height);
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

void Chili_UI::setTestValues(float wid, float hei)
{
	width = wid;
	height = hei;
}

void Chili_UI::changeElementFocus(int index)
{
	assert(index >= 0 && list_UiElements.empty() == false);
	std::shared_ptr<UI_Element> temporary = list_UiElements.back();
	list_UiElements.back() = list_UiElements[index];
	list_UiElements[index] = temporary;
}

