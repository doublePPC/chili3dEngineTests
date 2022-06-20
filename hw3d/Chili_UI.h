#pragma once
//#include "Camera.h"
#include "UI_Generics.h"
#include "UI_Element.h"
#include "UI_Maths.h"
#include "UI_Utils.h"

struct UIData
{
	Graphics& gfx;
	Rgph::BlurOutlineRenderGraph& rgRef;
	std::vector<ElementData> list_ElementsData;
	unsigned int amountOfElements;
};

class Chili_UI
{
public:
	Chili_UI(UIData data, float screenWidth, float screenHeight);
	Chili_UI(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef, float screenWidth, float screenHeight);
	Chili_UI() = delete;
	~Chili_UI();

	void update(DirectX::XMFLOAT3 camRot, DirectX::XMFLOAT3 camPos);
	void spawnControlWindows();
	void resetOnHoverState();
	void addElement(ElementData newElem);
	void addComponentToLastElement(std::shared_ptr<UI_Component> preBuiltComp, Rgph::BlurOutlineRenderGraph& rgRef);
	void adjustScreenSize(int width, int height);

	std::shared_ptr<UI_Component> searchComponentByID(const std::string& ID);
	std::shared_ptr<UI_Element> searchElementByCompID(const std::string& ID);
	// onEvent management
	bool onMouseEvent(float mouseX, float mouseY, mouseEvents event);
	void setTestValues(float wid, float hei);

	void setTestValue(int value);
private:
	void changeElementFocus(int index);
private:
	std::vector<std::shared_ptr<UI_Element>> list_UiElements;
	bool elementCreated = false;
	bool element2Created = false;
	bool lastClickIn = false;
	float lastLeftClickX = 100.0f;
	float lastLeftClickY = 100.0f;
	float width = 0.0f;
	float height = 0.0f;
	int testWheelMove = 0;
protected:
	Graphics& gfx;
	Rgph::BlurOutlineRenderGraph& rgRef;
};