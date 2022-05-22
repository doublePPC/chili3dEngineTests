#pragma once
#include "Engine_Interface.h"

// contains a series of hard-coded datas for scenes initialisation

class HardCodedScenes
{
public:
	// Chili's Sponza Scene
	static void InitSponzaModels(std::vector<modelData>& refMapData);
	static void InitSponzaCubes(std::vector<cubeData>& refMapData);

	// Test Scene
	static void InitTestModels(std::vector<modelData>& refMapData);

	static void InitCameras(std::vector<cameraData>& refCamData);
	static void InitLight(lightData& refLight);
};