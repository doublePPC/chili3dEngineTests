Texture2D tex : register(t0);

SamplerState splr : register(s0);

cbuffer CBuf : register(b1)
{
	float3 color;
	float transparency;
};

float4 main(float3 viewFragPos : Position, float2 tc : Texcoord) : SV_Target
{
	float4 finalColor;
	float4 textureColor = float4(tex.Sample(splr, tc).rgb, 1.0f - transparency);
	finalColor.x = color.x * transparency + textureColor.x * textureColor.w;
	finalColor.y = color.y * transparency + textureColor.y * textureColor.w;
	finalColor.z = color.z * transparency + textureColor.z * textureColor.w;
	finalColor.w = 1.0f;
    return finalColor;
}