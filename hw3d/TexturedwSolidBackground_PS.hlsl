Texture2D tex : register(t0);

SamplerState splr : register(s0);

cbuffer CBuf : register(b1)
{
	float3 backgroundColor;
	float backgroundTransparency;
	float3 textureTransparentColor;
	float transpColorTransparency;
};

float4 main(float3 viewFragPos : Position, float2 tc : Texcoord) : SV_Target
{
	float4 finalColor;
	float3 textureColor = float3(tex.Sample(splr, tc).rgb);
	if (all(textureColor == textureTransparentColor))
	{
		float backTransparency = 1.0f - transpColorTransparency;
		finalColor.x = textureTransparentColor.x * transpColorTransparency + backgroundColor.x * backTransparency;
		finalColor.y = textureTransparentColor.y * transpColorTransparency + backgroundColor.y * backTransparency;
		finalColor.z = textureTransparentColor.z * transpColorTransparency + backgroundColor.z * backTransparency;
	}
	else
	{
		float textureTransparency = 1.0f - backgroundTransparency;
		finalColor.x = textureColor.x * textureTransparency + backgroundColor.x * backgroundTransparency;
		finalColor.y = textureColor.y * textureTransparency + backgroundColor.y * backgroundTransparency;
		finalColor.z = textureColor.z * textureTransparency + backgroundColor.z * backgroundTransparency;
	}
	finalColor.w = 1.0f;
	return finalColor;
}