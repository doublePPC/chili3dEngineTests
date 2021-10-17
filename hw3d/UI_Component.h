#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx, std::string textureFilePath);
	//UI_Component(ComponentData data, Graphics& gfx, Surface surface);
	~UI_Component();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale);
	void SubmitToChannel();

	void SpawnControlWindow(Graphics& gfx, int index);
	RelativePosition GetRelativePosition();
	Size GetSize();
	std::shared_ptr<TestSquare> getImage();
	std::pair<float, float> getTopLeft();
	std::pair<float, float> getBotRight();

	// command methods
	void manageLeftClick();
	void manageRightClick();
	void manageOnHover();
	void resetOnHoverState();
private:
	void evaluateCornersPosition(DirectX::XMFLOAT2 relPos);
private:
	std::shared_ptr<TestSquare> image;
	RelativePosition relPos;
	Size size;
	std::pair<float, float> relTopLeft;
	std::pair<float, float> relBotRight;
	bool state = false;
	bool mouseIsOnHover = false;
};