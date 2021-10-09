#pragma once
//#include "Camera.h"
#include "UI_Generics.h"
#include "UI_Element.h"
#include "UI_Maths.h"

class Chili_UI
{
public:
	Chili_UI(UIData data, float screenWidth, float screenHeight);
	Chili_UI() = delete;
	~Chili_UI();

	void update(DirectX::XMFLOAT3 camRot, DirectX::XMFLOAT3 camPos);
	void spawnControlWindows();
	void resetOnHoverState();

	// onEvent management
	bool onMouseEvent(float mouseX, float mouseY, mouseEvents event);
private:
	void changeElementFocus(int index);
private:
	std::vector<std::shared_ptr<UI_Element>> list_UiElements;
	bool elementCreated = false;
	bool lastClickIn = false;
	Graphics& gfx;
	Rgph::BlurOutlineRenderGraph& rgRef;
	float lastLeftClickX = 100.0f;
	float lastLeftClickY = 100.0f;
};