#include "MapsManager.h"

MapManager::MapManager()
	: curMapId(0)
{
	maps.emplace_back("sponza");
}

MapManager::~MapManager()
{
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
