#pragma once
#include "UI_Component.h"

class UI_Button : public UI_Component
{
public:
	UI_Button(ComponentData data, Graphics& gfx, std::string textureFilePath, const std::string& buttonText, float textZoneScale);
	~UI_Button();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale) override;
	void SubmitToChannel() override;
	void LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef) override;
private:
	static void DefineTextScale(float& xValue, float& yValue, float scale);
private:
	std::shared_ptr<UISquare> textZone;

	static constexpr float minimumTextScale = 0.25f;
};