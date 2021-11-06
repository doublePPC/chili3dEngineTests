Texture2D tex : register(t0);

SamplerState splr : register(s0);

cbuffer CBuf : register(b1)
{
	float3 backgroundColor;
	float backgroundTransparency;
};

float4 main(float3 viewFragPos : Position, float2 tc : Texcoord) : SV_Target
{
	float4 finalColor;
	float4 textureColor = float4(tex.Sample(splr, tc).rgb, 1.0f);
	float colorSum = textureColor.x + textureColor.y + textureColor.z;
	float transparency;
	if (colorSum >= 2.85f)
		transparency = 0.0f;
	else if (colorSum >= 1.0f)
		transparency = 1 - colorSum / 2.85f;
	else
		transparency = 1.0f;
	textureColor.w = textureColor.w - transparency;
	finalColor.x = textureColor.x * transparency + backgroundColor.x * textureColor.w;
	finalColor.y = textureColor.y * transparency + backgroundColor.y * textureColor.w;
	finalColor.z = textureColor.z * transparency + backgroundColor.z * textureColor.w;
	finalColor.w = 1.0f;
	return finalColor;
}