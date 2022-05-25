#pragma once
#include <DirectXMath.h>
#include "Frustum.h"

class Graphics;
namespace Rgph
{
	class RenderGraph;
}

class Projection
{
public:
	Projection( Graphics& gfx,float width,float height,float nearZ,float farZ );
	DirectX::XMMATRIX GetMatrix() const;
	DirectX::XMFLOAT3 GetFrustPos() const;
	DirectX::XMFLOAT3 GetFrustRot() const;
	void RenderWidgets( Graphics& gfx );
	void SetPos( DirectX::XMFLOAT3 );
	void SetRotation( DirectX::XMFLOAT3 );
	void Submit( size_t channel ) const;
	void LinkTechniques( Rgph::RenderGraph& rg );
	void Reset( Graphics& gfx );
	void AdjustProjSize(Graphics& gfx, float newWidth, float newHeight);
private:
	float width;
	float height;
	float nearZ;
	float farZ;
	float homeWidth;
	float homeHeight;
	float homeNearZ;
	float homeFarZ;
	Frustum frust;
};