Texture2D tex : register(t0);

SamplerState splr : register(s0);

cbuffer ObjectCBuf : register(b1)
{
    float2 translation;
    bool hasAlpha;
    float padding;
};

float4 main(float2 tc : Texcoord) : SV_TARGET
{
    float3 color = tex.Sample(splr, float2(tc.x, 1.0f - tc.y)).rgb;
    float alphaValue = 1.0f;
    if (hasAlpha)
    {
        alphaValue = tex.Sample(splr, float2(tc.x, 1.0f - tc.y)).a;
    }   
    color.x = color.x * alphaValue;
    color.y = color.y * alphaValue;
    color.z = color.z * alphaValue;
	return float4(color, 1.0f);
}