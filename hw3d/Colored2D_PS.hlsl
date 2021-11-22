struct VSOut
{
    float4 pos : SV_Position;
    float3 viewPos : Position;
    float3 color : Color0;
};

float4 main(VSOut vsOutput) : SV_TARGET
{
	return float4(vsOutput.color, 1.0f);
}