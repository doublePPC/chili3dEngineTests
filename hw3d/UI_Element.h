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
	// command methods
	bool onLeftClick(float clicX, float clicY);
	// getters and setters
	PosAndSize getPos();
	void componentHasBeenClicked(bool value);
private:
	bool mouseClickCheckup(float clicX, float clicY);
	void manageLeftClick(float clicX, float clicY);
	std::pair<float, float> convertMouseClick(float clicX, float clicY);
private:
	PosAndSize datas;
	std::pair<float, float> topLeft;
	std::pair<float, float> botRight;
	std::vector<std::shared_ptr<UI_Component>> listUIcomponents;
	std::shared_ptr<TestSquare> background;
	bool aComponentHasBeenClicked = false;
};