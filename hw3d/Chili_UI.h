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

	// onEvent management
	bool onMouseEvent(float mouseX, float mouseY, mouseEvents event);
private:
	void changeElementFocus(int index);
private:
	std::vector<std::shared_ptr<UI_Element>> list_UiElements;
	bool elementCreated = false;
	bool element2Created = false;
	bool lastClickIn = false;
	float lastLeftClickX = 100.0f;
	float lastLeftClickY = 100.0f;
protected:
	Graphics& gfx;
	Rgph::BlurOutlineRenderGraph& rgRef;
};