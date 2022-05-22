#include "Map.h"
#include "ScenesCodex.h"

Map::Map(std::string filePath):
	light(lightData())
{
	if (filePath == "sponza")
	{
		HardCodedScenes::InitSponzaModels(models);
		HardCodedScenes::InitSponzaCubes(cubes);
		HardCodedScenes::InitCameras(cameras);
		HardCodedScenes::InitLight(light);
	}
	else if (filePath == "test")
	{
		HardCodedScenes::InitTestModels(models);
		HardCodedScenes::InitCameras(cameras);
		HardCodedScenes::InitLight(light);
	}
}

Map::~Map()
{
}

std::string Map::GetName()
{
	return name;
}


int Map::GetModelCount()
{
	return models.size();
}

modelData Map::GetModelDataById(int id)
{
	return models[id];
}


int Map::GetCubeCount()
{
	return cubes.size();
}

cubeData Map::GetCubeDataById(int id)
{
	return cubes[id];
}

int Map::GetCameraCount()
{
	return cameras.size();
}

const std::vector<cameraData>& Map::GetCameraList()
{
	return cameras;
}

lightData Map::GetLightData()
{
	return light;
}


