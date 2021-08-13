#pragma once
#include "UI_Maths.h"
#include "UI_Generics.h"
#include "UI_Component.h"

class UI_Element
{
public:
	UI_Element(ElementData data, Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef);
	~UI_Element();

	// update methods
	void SubmitToChannel();
	void AdjustPos2Cam(DirectX::XMFLOAT3 ui_facing, DirectX::XMFLOAT3 elem_pos);
	void spawnControlWindows(Graphics& gfx);
	// getters
	DirectX::XMFLOAT4 getPos();
private:
	DirectX::XMFLOAT2 pos;
	float size;
	std::vector<std::shared_ptr<UI_Component>> listUIcomponents;
	std::shared_ptr<TestSquare> background;
};