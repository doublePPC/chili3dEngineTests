#pragma once
#include "UI_TechniqueBuilder.h"
#include "UI_CBufStructs.h"
#include <string>

class UISquare : public Drawable
{
public:
	UISquare(Graphics& gfx, Size size, std::shared_ptr<TechniqueBuilder> drawTechnique);

	UISquare(Graphics& gfx, float size);
	UISquare(Graphics& gfx, float size, float scaleX, float scaleY, DirectX::XMFLOAT3 colorValue);
	UISquare(Graphics& gfx, float size, float scaleX, float scaleY, std::string texture);
	UISquare(Graphics& gfx, float size, float scaleX, float scaleY, std::string texture, DirectX::XMFLOAT4 tint);
	UISquare(Graphics& gfx, float size, float scaleX, float scaleY, std::shared_ptr<Surface> texture);
	~UISquare();

	void SetPos(DirectX::XMFLOAT3 ui_facing, DirectX::XMFLOAT3 elem_pos) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SpawnControlWindow(Graphics& gfx) noexcept;

	DirectX::XMFLOAT3 getPos() { return inWorldPos; };

	void disableDefaultTechnique();
	void AddTintTechnique(Graphics& gfx, DirectX::XMFLOAT4 tint);
private:
	float scaleX;
	float scaleY;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	DirectX::XMFLOAT3 inWorldPos = { 0.0f, 0.0f, 0.0f };
};