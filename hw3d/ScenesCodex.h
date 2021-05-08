#pragma once
#include "Engine_Interface.h"

// contains a series of hard-coded datas for scenes initialisation

class HardCodedScenes
{
public:
	static void InitSponzaModels(std::vector<modelData>& refMapData);
	static void InitSponzaCubes(std::vector<cubeData>& refMapData);
};