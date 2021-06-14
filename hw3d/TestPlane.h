#pragma once
#include "Drawable.h"
#include <string>

class TestPlane : public Drawable
{
public:
	TestPlane(Graphics& gfx, float size, float translationX, float translationY);
	TestPlane(Graphics& gfx, float size, std::string texture);
	TestPlane(Graphics& gfx, float size, std::string texture, std::string texNormal);
	TestPlane(Graphics& gfx, float baseSize, float rectFactor, std::string texture, std::string texNormal);
	void SetPos(DirectX::XMFLOAT3 pos) noexcept;
	void SetRotation(float roll, float pitch, float yaw) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	void SpawnControlWindow(Graphics& gfx) noexcept;
private:
	struct PSMaterialConstant
	{
		float specularIntensity = 0.18f;
		float specularPower = 18.0f;
		BOOL normalMappingEnabled = TRUE;
		float padding[1];
	} pmc;
	DirectX::XMFLOAT3 position = { 0.0f,0.0f, 0.0f };
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	std::string  texDirectory;
};