Texture2D tex : register(t0);

SamplerState splr : register(s0);

//cbuffer ObjectCBuf : register(b1)
//{
//    float2 translation;
//    bool hasAlpha;
//    float padding;
//};

float4 main(float2 tc : Texcoord) : SV_TARGET
{
    float3 color = tex.Sample(splr, float2(tc.x, 1.0f - tc.y)).rgb;
    color.x = color.x;
    color.y = color.y;
    color.z = color.z;
	return float4(color, 1.0f);
}