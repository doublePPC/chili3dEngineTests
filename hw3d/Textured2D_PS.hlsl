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
	return float4(tex.Sample(splr, tc).rgb, 1.0f);
}