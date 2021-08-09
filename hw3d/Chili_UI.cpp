#include "Chili_UI.h"


Chili_UI::Chili_UI(UIData data)
{
	list_UiElements.reserve(data.amountOfElements);
	for (int i = 0; i < data.list_ElementsData.size(); i++)
	{
		list_UiElements.emplace_back(std::make_unique<UI_Element>(data.list_ElementsData[i], data.gfx, data.rgRef));
	}
}

Chili_UI::~Chili_UI()
{
}

void Chili_UI::update(Graphics& gfx, Rgph::BlurOutlineRenderGraph& rgRef, DirectX::XMFLOAT3 camRot, DirectX::XMFLOAT3 camPos)
{
	// determine the center point and rotation of the UI interface
	DirectX::XMFLOAT3 ui_centerPoint, elemPosition;
	
	this->camRot = camRot;
	UI_facing.x = camRot.y;               
	UI_facing.y = camRot.z + to_rad(45);
	UI_facing.z = 0.0f;

	ui_centerPoint = getCenterPoint(camPos);

	// updating elements in the UI one by one
	for (int i = 0; i < list_UiElements.size(); i++)
	{
		elemPosition = calculateElemPosition(ui_centerPoint, list_UiElements[i]->getPos());
		list_UiElements[i]->AdjustPos2Cam(UI_facing, elemPosition);
		list_UiElements[i]->SubmitToChannel();
	}
}

void Chili_UI::spawnControlWindows(Graphics& gfx)
{
	for (int i = 0; i < list_UiElements.size(); i++)
	{
		list_UiElements[i]->spawnControlWindows(gfx);
	}
}

DirectX::XMFLOAT3 Chili_UI::getCenterPoint(DirectX::XMFLOAT3 camPos)
{
	DirectX::XMFLOAT3 centerPoint;
	float hypothenuse = cos(camRot.y);
	float xFactor = sin(camRot.z) * hypothenuse;
	float zFactor = cos(camRot.z) * hypothenuse;

	centerPoint.x = camPos.x + xFactor;
	centerPoint.y = camPos.y - sin(camRot.y);
	centerPoint.z = camPos.z + zFactor;
	return centerPoint;
}

DirectX::XMFLOAT3 Chili_UI::calculateElemPosition(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 elemRelativePos)
{
	DirectX::XMFLOAT3 elemPosition;
	// pitch angle modifiers
	float hypothenuse = sin(camRot.y) * elemRelativePos.y;
	float pitchYmod = cos(camRot.y) * elemRelativePos.y;
	float pitchXmod = sin(camRot.z) * hypothenuse;
	float pitchZmod = cos(camRot.z) * hypothenuse;

	// yaw angle modifiers
	float xFactor = elemRelativePos.x * cos(camRot.z);
	float zFactor = elemRelativePos.x * sin(camRot.z);

	elemPosition.x = center.x + xFactor + pitchXmod;
	elemPosition.y = center.y + pitchYmod;
	elemPosition.z = center.z - zFactor + pitchZmod;
	return elemPosition;
}
