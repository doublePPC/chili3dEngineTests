#include "Transform.hlsli"

//cbuffer ObjectCBuf : register(b1)
//{
//    float2 translation;
//    float padding1;
//    float padding2;
//};

struct VSOut
{
    float3 viewPos : Position;
    float2 tex : Texcoord;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : Position, float2 tex : Texcoord)
{
    VSOut vso;
    vso.viewPos = (float3) mul(float4(pos, 1.0f), modelView);
    vso.pos = mul(float4(pos, 1.0f), modelViewProj);
    vso.tex = tex;
    return vso;
}