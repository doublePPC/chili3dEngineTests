#include "Map.h"
#include "ScenesCodex.h"

Map::Map(std::string filePath)
{
	if (filePath == "sponza")
	{
		HardCodedScenes::InitSponzaModels(models);
		HardCodedScenes::InitSponzaCubes(cubes);
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


