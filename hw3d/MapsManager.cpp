#include "MapsManager.h"

MapManager::MapManager()
	: curMapId(0)
{
	maps.emplace_back("sponza");
	maps.emplace_back("test");
}

MapManager::~MapManager()
{
}

void MapManager::SetCurrentMapToId(unsigned int mapId)
{
	if (mapId > maps.size())
		curMapId = maps.size() - 1;
	else
		curMapId = mapId;
}

void MapManager::LoadCurrentMap(Chili_Engine& gfxEngine)
{
	for (int i = 0; i < maps[curMapId].GetModelCount(); i++)
	{
		gfxEngine.AddModel(maps[curMapId].GetModelDataById(i));
	}
	for (int i = 0; i < maps[curMapId].GetCubeCount(); i++)
	{
		gfxEngine.AddCube(maps[curMapId].GetCubeDataById(i));
	}
	gfxEngine.SetupLightCameras(maps[curMapId].GetCameraList(), maps[curMapId].GetLightData());
}
