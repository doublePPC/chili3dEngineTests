#pragma once
#include "Drawable.h"
#include <string>

class TestSquare : public Drawable
{
public:
	TestSquare(Graphics& gfx, float size, float translationX, float translationY);
	TestSquare(Graphics& gfx, float size, float translationX, float translationY, std::string texture);
	~TestSquare();

	void SetPos(DirectX::XMFLOAT2 pos) noexcept;
	//void SetRotation(float roll, float pitch, float yaw) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SpawnControlWindow(Graphics& gfx) noexcept;
private:
	DirectX::XMFLOAT2 pos = {-1.0f, 0.0f };
	//float roll = 0.0f;
	//float pitch = 0.0f;
	//float yaw = 0.0f;
};