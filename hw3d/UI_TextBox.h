#pragma once
#include "UI_Component.h"

class UI_TextBox : public UI_Component
{
public:
	UI_TextBox() = delete;
	UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, const std::string& text, const Police& police);
	~UI_TextBox();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale) override;
	void SubmitToChannel() override;
	void LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef) override;
	void SpawnControlWindow(Graphics& gfx, int index) override;
private:
	bool isLignVisible(unsigned int lignId);
	float calculateDistance(unsigned int lignId);
private:
	std::vector<TextLign> textLigns;
	std::vector<std::shared_ptr<UISquare>> visibleTextLigns;
	Police police;
	unsigned int cursor = 0;
	unsigned int visibleLignCount = 0;
	// general values to calculate ligns position 
	float lign0Distance;
	float lignSize;
};
