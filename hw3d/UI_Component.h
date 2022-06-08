#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"
#include "UI_Square.h"
#include "UI_TextFragments.h"

struct ComponentData
{
	RelativePosition relPos;
	Size size;
	std::shared_ptr<TechniqueBuilder> drawTech = nullptr;
};

class UI_Component
{
public:
	UI_Component(ComponentData data, Graphics& gfx, const std::string& textureFilePath);
	UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<Surface> textImage);
	UI_Component(ComponentData data, Graphics& gfx, std::shared_ptr<TechniqueBuilder> drawTech);
	virtual ~UI_Component();

	virtual void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale);
	virtual void SubmitToChannel();
	virtual void LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef);
	virtual void SpawnControlWindow(Graphics& gfx, int index);

	RelativePosition GetRelativePosition();
	Size GetSize();
	std::shared_ptr<UISquare> getImage();
	std::pair<float, float> getTopLeft();
	std::pair<float, float> getBotRight();

	// command methods
	virtual void manageMouseEvent(float clicX, float clicY, mouseEvents _event);
	void resetOnHoverState();
protected:
	virtual void manageLeftClick();
	virtual void manageRightClick();
	virtual void manageOnHover();
	virtual void manageHoldLeft();
	virtual void manageHoldRight();
	virtual void manageReleaseLeft();
	virtual void manageReleaseRight();
	virtual void manageWheelUp();
	virtual void manageWheelDown();
	DirectX::XMFLOAT3 GetInWorldPos();
private:
	void evaluateCornersPosition(DirectX::XMFLOAT2 relPos);
private:
	std::shared_ptr<UISquare> image;
	RelativePosition relPos;
	Size size;
	std::pair<float, float> relTopLeft;
	std::pair<float, float> relBotRight;
	bool mouseIsOnHover = false;
};