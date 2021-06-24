#include "UI_Element.h"

UI_Element::UI_Element(float xPos, float yPos, float width, float height)
{
	topLeft = { xPos, yPos };
	dimension = { width, height };
	comp1 = std::make_unique<UI_Component>("Images\\kappa50.png", 64, 64, 20, 20);
	comp2 = std::make_unique<UI_Component>("Images\\vase_plant.png", 96, 96, 128, 80);
}

UI_Element::~UI_Element()
{
}

void UI_Element::BuildComponents(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	DirectX::XMFLOAT4 componentData;
	listUIcomponents.reserve(2);
	componentData = comp1->GetImgPosSizeData(topLeft, dimension);
	listUIcomponents.emplace_back(std::make_shared<TestSquare>(gfx, 0.8f, 0.5f, componentData.y, comp1->getImgFilepath()));

	componentData = comp2->GetImgPosSizeData(topLeft, dimension);
	listUIcomponents.emplace_back(std::make_shared<TestSquare>(gfx, 1.0f, -1.0f, componentData.y, comp2->getImgFilepath()));

	listUIcomponents[0]->LinkTechniques(rgRef);
	listUIcomponents[1]->LinkTechniques(rgRef);
}

void UI_Element::SubmitToChannel()
{
	for (int i = 0; i < listUIcomponents.size(); i++)
	{
		listUIcomponents[i]->Submit(Chan::main);
	}
}
