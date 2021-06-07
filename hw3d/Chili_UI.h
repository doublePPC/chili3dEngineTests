#pragma once
//#include "Camera.h"
#include "TestPlane.h"

class Chili_UI
{
public:
	Chili_UI();
	~Chili_UI();

	void update(DirectX::XMFLOAT3 nearPos, DirectX::XMFLOAT3 nearOrientation);
	void addElement(Graphics& gfx);
private:
	std::vector<std::unique_ptr<TestPlane>> componentsList;
};