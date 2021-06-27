#pragma once
#include "Drawable.h"
#include <string>

class TestSquare : public Drawable
{
public:
	TestSquare(Graphics& gfx, float size, float translationX, float translationY);
	TestSquare(Graphics& gfx, float size, float translationX, float translationY, std::string texture);
	~TestSquare();

	void LinkToCam();
	void Set2DPos(DirectX::XMFLOAT2 pos) noexcept;
	void AdjustToCamData(DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 pos) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SpawnControlWindow(Graphics& gfx) noexcept;
private:
	DirectX::XMFLOAT2 pos = {0.0f, 0.0f};
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	DirectX::XMFLOAT3 inWorldPos = { 0.0f, 0.0f, 0.0f };
	bool isLinkedToCam = false;

	static constexpr float offset = 1.0f;
};