Texture2D tex : register(t0);

SamplerState splr : register(s0);


float4 main(float3 viewFragPos : Position, float2 tc : Texcoord) : SV_Target
{
    return float4(tex.Sample(splr, tc).rgb, 1.0f);
}