#include "UI_Generics.h"

float UnIntToPercentScreenFloat(unsigned int value)
{
	float result;
	result = float(value) / 255.0f;
	result = (result - 0.5f) * 2.0f;
	return result;
}
