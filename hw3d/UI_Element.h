#pragma once

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
	DirectX::XMFLOAT2 dimension;
	//DirectX::XMFLOAT3 translation = {0.0f, 0.0f, 0.0f};
	std::vector<std::shared_ptr<TestSquare>> listUIcomponents;
	std::shared_ptr<TestSquare> background;
};