#pragma once

#include "UI_Generics.h"
#include "UI_Component.h"

class UI_Element
{
public:
	UI_Element(float xPos, float yPos, float width, float height);
	~UI_Element();

	void BuildComponents(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef);
	void SubmitToChannel();
private:
	DirectX::XMFLOAT2 topLeft;
	DirectX::XMFLOAT2 dimension;
	std::unique_ptr<UI_Component> comp1 = nullptr;
	std::unique_ptr<UI_Component> comp2 = nullptr;
	std::vector<std::shared_ptr<TestPlane>> listUIcomponents;
};