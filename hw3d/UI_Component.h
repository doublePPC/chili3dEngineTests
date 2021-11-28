#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"
#include "UI_Square.h"

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx, std::string textureFilePath);
	UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<Surface> textImage);
	UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<TechniqueBuilder> drawTech);
	~UI_Component();

	virtual void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale);
	virtual void SubmitToChannel();
	virtual void LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef);

	void SpawnControlWindow(Graphics& gfx, int index);
	RelativePosition GetRelativePosition();
	Size GetSize();
	std::shared_ptr<UISquare> getImage();
	std::pair<float, float> getTopLeft();
	std::pair<float, float> getBotRight();

	// command methods
	void manageLeftClick();
	void manageRightClick();
	void manageOnHover();
	void resetOnHoverState();
protected:
	DirectX::XMFLOAT3 GetInWorldPos();
private:
	void evaluateCornersPosition(DirectX::XMFLOAT2 relPos);
private:
	std::shared_ptr<UISquare> image;
	RelativePosition relPos;
	Size size;
	std::pair<float, float> relTopLeft;
	std::pair<float, float> relBotRight;
	bool state = false;
	bool mouseIsOnHover = false;
};