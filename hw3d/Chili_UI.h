#pragma once
//#include "Camera.h"
#include "TestPlane.h"
#include "TestCube.h"
#include "BlurOutlineRenderGraph.h"

class Chili_UI
{
public:
	Chili_UI();
	~Chili_UI();

	void update(DirectX::XMFLOAT3 nearPos, DirectX::XMFLOAT3 nearOrientation);
	void addElement(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef);
	//std::vector<std::unique_ptr<TestPlane>>& getComponentLists();
	std::vector<std::unique_ptr<TestCube>>& getComponentLists();
	void spawnControlWindows(Graphics& gfx);
private:
	std::vector<std::unique_ptr<TestCube>> componentsList;
};