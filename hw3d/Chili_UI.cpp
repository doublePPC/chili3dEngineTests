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
	UI_Math::Update(camRot, camPos);
	DirectX::XMFLOAT3 elemPosition;

	// updating elements in the UI one by one
	for (int i = 0; i < list_UiElements.size(); i++)
	{
		elemPosition = UI_Math::CalculatePosRelativeToScreen(list_UiElements[i]->getPos());
		list_UiElements[i]->AdjustPos2Cam(elemPosition);
		list_UiElements[i]->SubmitToChannel();
	}
}

void Chili_UI::spawnControlWindows(Graphics& gfx)
{
	if (ImGui::Begin("UI_Main"))
	{
		//ImGui::Text("Position");
		//ImGui::SliderFloat("X", &datas.relPos.x, -1.0f, 1.0f, "%.2f");
	}
	ImGui::End();
	for (int i = 0; i < list_UiElements.size(); i++)
	{
		list_UiElements[i]->spawnControlWindows(gfx, i);
	}
}

//DirectX::XMFLOAT3 Chili_UI::getCenterPoint(DirectX::XMFLOAT3 camPos)
//{
//	DirectX::XMFLOAT3 centerPoint;
//	float hypothenuse = cos(camRot.y);
//	float xFactor = sin(camRot.z) * hypothenuse;
//	float zFactor = cos(camRot.z) * hypothenuse;
//
//	centerPoint.x = camPos.x + xFactor;
//	centerPoint.y = camPos.y - sin(camRot.y);
//	centerPoint.z = camPos.z + zFactor;
//	return centerPoint;
//}

//DirectX::XMFLOAT3 Chili_UI::calculateElemPosition(DirectX::XMFLOAT3 center, DirectX::XMFLOAT4 elemRelativePos)
//{
//	DirectX::XMFLOAT3 elemPosition;
//	// evaluate boundaries according to element's size
//	float Xboundary = (1.0f - elemRelativePos.w) / 2.0f + 1.0f;
//	float Xtranslation = elemRelativePos.x * Xboundary;
//	float Yboundary = (1.0f - elemRelativePos.w) / 2.0f + (2.0f - elemRelativePos.w);
//	float Ytranslation = elemRelativePos.y * Yboundary;
//
//	// pitch angle modifiers
//	float hypothenuse = sin(camRot.y) * Ytranslation;
//	float pitchYmod = cos(camRot.y) * Ytranslation;
//	float pitchXmod = sin(camRot.z) * hypothenuse;
//	float pitchZmod = cos(camRot.z) * hypothenuse;
//
//	// yaw angle modifiers
//	float xFactor = Xtranslation * cos(camRot.z);
//	float zFactor = Xtranslation * sin(camRot.z);
//
//	elemPosition.x = center.x + xFactor + pitchXmod;
//	elemPosition.y = center.y + pitchYmod;
//	elemPosition.z = center.z - zFactor + pitchZmod;
//	return elemPosition;
//}
