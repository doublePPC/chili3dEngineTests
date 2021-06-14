#include "Transform.hlsli"

cbuffer ObjectCBuf : register(b1)
{
    float2 translation;
    float padding1;
    float padding2;
};

float4 main( float2 pos : Position ) : SV_Position
{
	return float4(pos.x + translation.x, pos.y + translation.y, 0.0f, 1.0f);
}