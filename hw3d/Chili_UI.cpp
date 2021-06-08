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
		float bias = 5.0f;
		nearPos.x = nearPos.x + bias;
		for (int i = 0; i < componentsList.size(); i++)
		{
			componentsList[i]->SetPos(nearPos);
			componentsList[i]->SetRotation(nearOrientation.x, nearOrientation.y, nearOrientation.z);
		}
	}
}

void Chili_UI::addElement(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef)
{
	// "Images\\kappa50.png"
	componentsList.emplace_back(std::make_unique<TestCube>(gfx, 20.0f));
	componentsList.back()->LinkTechniques(rgRef);
}

std::vector<std::unique_ptr<TestCube>>& Chili_UI::getComponentLists()
{
	return componentsList;
}

void Chili_UI::spawnControlWindows(Graphics& gfx)
{
	for (int i = 0; i < componentsList.size(); i++)
	{
		componentsList[i]->SpawnControlWindow(gfx, "My 1st UI element");
	}
}


