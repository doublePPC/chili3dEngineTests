#include "Transform.hlsli"

struct VSOut
{
    float4 pos : SV_Position;
    float3 viewPos : Position;
    float3 color : Color0;
};

VSOut main(float3 pos : Position, float3 colour : Color)
{
    VSOut vso;
    vso.viewPos = (float3) mul(float4(pos, 1.0f), modelView);
    vso.pos = mul(float4(pos, 1.0f), modelViewProj);
    vso.color = colour;
    return vso;
}