#include "UI_Element.h"

UI_Element::UI_Element(unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height)
{
	pos = { UnIntToPercentScreenFloat(xPos), UnIntToPercentScreenFloat(yPos) };
	dimension = { float(width) / 255.0f, float(height) / 255.0f };
}

UI_Element::~UI_Element()
{
}

void UI_Element::ReserveContainerSpace(unsigned int space)
{
	listUIcomponents.reserve(space);
}

void UI_Element::AddComponent(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	//"Images\\kappa50.png"
	listUIcomponents.emplace_back(std::make_shared<TestSquare>(gfx, 0.5f, 0.0f, 0.0f, "Images\\vase_plant.png"));
	listUIcomponents.back()->LinkTechniques(rgRef);
	listUIcomponents.back()->LinkToCam();
}

void UI_Element::SubmitToChannel()
{
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->Submit(Chan::main);
	}
}

void UI_Element::AdjustPos2Cam(DirectX::XMFLOAT3 ui_facing, DirectX::XMFLOAT3 elem_pos)
{
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->AdjustToCamData(ui_facing, elem_pos);
	}
}

void UI_Element::spawnControlWindows(Graphics& gfx)
{
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->SpawnControlWindow(gfx);
	}
}

DirectX::XMFLOAT3 UI_Element::getPos()
{
	return {pos.x, pos.y, 0.0f};
}

