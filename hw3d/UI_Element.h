#pragma once
#include "UI_Maths.h"
#include "UI_Generics.h"
#include "UI_Utils.h"
#include "UI_Component.h"
#include "UI_Button.h"

struct ElementData
{
	RelativePosition relPos;
	Size size;
	std::shared_ptr<TechniqueBuilder> drawTech = nullptr;
	std::vector<ComponentData> list_ComponentsData;
	unsigned int amountOfComponents;
	bool hasBackground;
};

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
	bool onMouseEvent(float clicX, float clicY, mouseEvents event);
	// getters and setters
	RelativePosition getRelativePosition();
	Size getSize();
	void componentHasBeenClicked(bool value);
	void resetOnHoverState();
	void addComponent(ComponentData data, std::string textureFilePath, Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef);
	void addComponent(std::shared_ptr<UI_Component> preBuiltComp, Rgph::BlurOutlineRenderGraph& rgRef);
private:
	bool mouseIsOnElementCheckup(float clicX, float clicY);
	void manageMouseEvent(float clicX, float clicY, mouseEvents event);
	std::pair<float, float> convertMousePos(float clicX, float clicY);
	void dispatchMouseEvent(mouseEvents event, int compId);
private:
	RelativePosition relPos;
	Size size;
	std::pair<float, float> topLeft;
	std::pair<float, float> botRight;
	std::vector<std::shared_ptr<UI_Component>> listUIcomponents;
	std::shared_ptr<UISquare> background;
	bool aComponentHasBeenClicked = false;
	bool mouseIsOnHover = false;
};