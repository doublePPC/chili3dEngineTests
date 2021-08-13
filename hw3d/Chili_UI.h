#pragma once
//#include "Camera.h"
#include "UI_Generics.h"
#include "UI_Element.h"
#include "UI_Maths.h"

class Chili_UI
{
public:
	Chili_UI(UIData data);
	Chili_UI() = delete;
	~Chili_UI();

	void update(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef, DirectX::XMFLOAT3 camRot, DirectX::XMFLOAT3 camPos);
	void spawnControlWindows(Graphics& gfx);
private:
	//DirectX::XMFLOAT3 getCenterPoint(DirectX::XMFLOAT3 camPos);
	//DirectX::XMFLOAT3 calculateElemPosition(DirectX::XMFLOAT3 center, DirectX::XMFLOAT4 elemRelativePos);
private:
	std::vector<std::unique_ptr<UI_Element>> list_UiElements;
};