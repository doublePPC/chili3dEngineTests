#include "UI_commonEffects.hlsli"

Texture2D tex : register(t0);

SamplerState splr : register(s0);

cbuffer CBuf : register(b1)
{
	float3 backgroundColor;
	float globalTransparency;
};

float4 main(float3 viewFragPos : Position, float2 tc : Texcoord) : SV_Target
{
	float4 finalColor = float4(tex.Sample(splr, tc).rgb, 1.0f);
	float transparency = BiThresholdWhiteFading(finalColor);
	finalColor.w = transparency * globalTransparency;
	return finalColor;
}