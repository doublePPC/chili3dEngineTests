float BiThresholdWhiteFading(float3 color)
{
	float transparency;
	float colorSum = color.x + color.y + color.z;
	if (colorSum >= 2.85f)
		transparency = 0.0f;
	else if (colorSum >= 1.0f)
		transparency = 1.0f - colorSum / 2.85f;
	else
		transparency = 1.0f;
	return transparency;
}

float3 UniformTinting(float4 tintColor, float3 color)
{
	float3 resultColor;
	float colorOpacity = 1.0f - tintColor.w;
	resultColor.x = tintColor.x * tintColor.w + color.x * colorOpacity;
	resultColor.y = tintColor.y * tintColor.w + color.y * colorOpacity;
	resultColor.z = tintColor.z * tintColor.w + color.z * colorOpacity;
	return resultColor;
}

float3 LinearTintingTowardWhite(float4 tintColor, float3 color)
{
	float3 resultColor;
	float tintOpacity = (color.x + color.y + color.z) / 3.0f;
	float colorOpacity = 1.0f - tintOpacity;
	resultColor.x = tintColor.x * tintOpacity + color.x * colorOpacity;
	resultColor.y = tintColor.y * tintOpacity + color.y * colorOpacity;
	resultColor.z = tintColor.z * tintOpacity + color.z * colorOpacity;
	return resultColor;
}

float3 LinearTintingTowardBlack(float4 tintColor, float3 color)
{
	float3 resultColor;
	float colorOpacity = (color.x + color.y + color.z) / 3.0f;
	float tintOpacity = 1.0f - colorOpacity;
	resultColor.x = tintColor.x * tintOpacity + color.x * colorOpacity;
	resultColor.y = tintColor.y * tintOpacity + color.y * colorOpacity;
	resultColor.z = tintColor.z * tintOpacity + color.z * colorOpacity;
	return resultColor;
}

float3 TintingTechDispatcher(float4 tintColor, float3 color, int techId)
{
	float3 result = {0.0f, 0.0f, 0.0f};
	if (techId == 0)
	{
		result = UniformTinting(tintColor, color);
	}	
	else if (techId == 1)
	{
		result = LinearTintingTowardWhite(tintColor, color);
	}	
	else if (techId == 2)
	{
		result = LinearTintingTowardBlack(tintColor, color);
	}
	return result;
}