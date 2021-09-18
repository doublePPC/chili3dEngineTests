#pragma once
#include "Drawable.h"
#include <string>

class TestSquare : public Drawable
{
public:
	TestSquare(Graphics& gfx, float size);
	TestSquare(Graphics& gfx, float size, float scaleX, float scaleY, DirectX::XMFLOAT3 colorValue);
	TestSquare(Graphics& gfx, float size, float scaleX, float scaleY, std::string texture);
	~TestSquare();

	void SetPos(DirectX::XMFLOAT3 ui_facing, DirectX::XMFLOAT3 elem_pos) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SpawnControlWindow(Graphics& gfx) noexcept;

	DirectX::XMFLOAT3 getPos() { return inWorldPos; };
private:
	float scaleX;
	float scaleY;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	DirectX::XMFLOAT3 inWorldPos = { 0.0f, 0.0f, 0.0f };
};