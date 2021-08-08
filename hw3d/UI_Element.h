#pragma once

#include "UI_Generics.h"
#include "UI_Component.h"

class UI_Element
{
public:
	UI_Element(unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height);
	~UI_Element();

	// setup methods
	void ReserveContainerSpace(unsigned int space);
	void AddComponent(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef);
	// update methods
	void SubmitToChannel();
	void AdjustPos2Cam(DirectX::XMFLOAT3 ui_facing, DirectX::XMFLOAT3 elem_pos);
	void spawnControlWindows(Graphics& gfx);
	// getters
	DirectX::XMFLOAT3 getPos();
private:
	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT2 oldPos = {0.0f, 0.0f};
	DirectX::XMFLOAT2 dimension;
	DirectX::XMFLOAT3 translation = {0.0f, 0.0f, 0.0f};
	std::vector<std::shared_ptr<TestSquare>> listUIcomponents;
};