Texture2D tex : register(t0);

SamplerState splr : register(s0);

cbuffer ObjectCBuf : register(b1)
{
    float2 translation;
    float padding1;
    float padding2;
};

float4 main( float2 tc : Texcoord) : SV_TARGET
{
	
	return float4(tex.Sample(splr, float2(tc.x -0.9f + translation.x, 1.0f - tc.y +0.5f + translation.y)).rgb, 1.0f);
}