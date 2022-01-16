#pragma once
#include "UI_Component.h"

class UI_TextBox : public UI_Component
{
public:
	UI_TextBox() = delete;
	/*UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, const std::string& text, float averageLetterSize);*/
	UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, const std::string& text, unsigned int charsSize);
	~UI_TextBox();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale) override;
	void SubmitToChannel() override;
	void LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef) override;
private:
	bool isLignVisible(unsigned int lignId);
	float calculateDistance(unsigned int lignId);
private:
	/*std::shared_ptr<Surface> text;
	std::shared_ptr<Surface> visibleText;*/
	std::vector<std::shared_ptr<UISquare>> textLigns;
	unsigned int cursor = 0;
	unsigned int visibleLignCount = 0;
	// general values to calculate ligns position 
	float baseOffset;
	float jump;
	float medianLign;
};
