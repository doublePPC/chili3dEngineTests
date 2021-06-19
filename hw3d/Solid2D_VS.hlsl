#include "Transform.hlsli"

cbuffer ObjectCBuf : register(b1)
{
    float2 translation;
    float padding1;
    float padding2;
};

struct VSOut
{
    float2 tex : Texcoord;
    float4 pos : SV_Position;
};

VSOut main(float2 pos : Position, float2 tex : Texcoord)
{
    VSOut vso;
    vso.pos = float4(pos.x + translation.x, pos.y + translation.y, 0.0f, 1.0f);
    vso.tex = tex;
    return vso;
}