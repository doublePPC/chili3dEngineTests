#include "Chili_UI.h"

Chili_UI::Chili_UI()
{
}

Chili_UI::~Chili_UI()
{
}

void Chili_UI::update(DirectX::XMFLOAT3 nearPos, DirectX::XMFLOAT3 nearOrientation)
{
	if (!componentsList.empty())
	{
		for (int i = 0; i < componentsList.size(); i++)
		{
			componentsList[i]->SetPos(nearPos);
			componentsList[i]->SetRotation(nearOrientation.x, nearOrientation.y, nearOrientation.z);
		}
	}
}

void Chili_UI::addElement(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	componentsList.emplace_back(std::make_unique<TestPlane>(gfx, 20.0f, "Images\\kappa50.png"));
	componentsList.back()->LinkTechniques(rgRef);
}

std::vector<std::unique_ptr<TestPlane>>& Chili_UI::getComponentLists()
{
	return componentsList;
}


