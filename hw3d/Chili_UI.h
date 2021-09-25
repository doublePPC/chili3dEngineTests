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

	// onEvent management
	bool onLeftClick(float mouseX, float mouseY);
private:

private:
	std::vector<std::unique_ptr<UI_Element>> list_UiElements;
	bool elementCreated = false;
	bool lastClickIn = false;
	Graphics& gfx;
	Rgph::BlurOutlineRenderGraph& rgRef;
	float lastLeftClickX = 100.0f;
	float lastLeftClickY = 100.0f;
};