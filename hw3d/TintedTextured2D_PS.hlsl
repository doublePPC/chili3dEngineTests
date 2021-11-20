#include "UI_commonEffects.hlsli"

Texture2D tex : register(t0);

SamplerState splr : register(s0);

cbuffer CBuf : register(b1)
{
	float4 color;
	int techCode;
	float globalTransparency;
	float2 padding;
};

float4 main(float3 viewFragPos : Position, float2 tc : Texcoord) : SV_Target
{
	float3 finalColor;
	float3 textureColor = float3(tex.Sample(splr, tc).rgb);
	finalColor = TintingTechDispatcher(color, textureColor, techCode);
    return float4(finalColor, globalTransparency);
}