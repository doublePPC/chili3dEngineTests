#pragma once
#include "UI_Component.h"
#include "UI_Button.h"

class UI_ScrollBar : public UI_Component
{
public:
	UI_ScrollBar() = delete;
	UI_ScrollBar(ComponentData data, Graphics& gfx, std::shared_ptr<Surface> scrollBar, const std::string& upPath, const std::string& downPath, const std::string& cursorPath);
	~UI_ScrollBar();

	void AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale) override;
	void SubmitToChannel() override;
	void LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef) override;
	void SpawnControlWindow(Graphics& gfx, int index) override;
private:
	float getCursorYpos(float topPos);
private:
	std::shared_ptr<UISquare> arrowUP;
	std::shared_ptr<UISquare> arrowDOWN;
	std::shared_ptr<UISquare> cursor;
	float cursorCurPos = -0.5f;
	static constexpr float scaleProportion = 0.1f;
};