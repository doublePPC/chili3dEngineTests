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
	void AdjustPos2Cam(DirectX::XMFLOAT2 elem_pos);
	void spawnControlWindows(Graphics& gfx, int index);
	// getters
	PosAndSize getPos();
private:
	PosAndSize datas;
	std::vector<std::shared_ptr<UI_Component>> listUIcomponents;
	std::shared_ptr<TestSquare> background;
};