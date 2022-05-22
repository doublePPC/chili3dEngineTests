#pragma once
#include "Engine_Interface.h"
#include "Map.h"

class MapManager
{
public:
	MapManager();
	~MapManager();

	void SetCurrentMapToId(unsigned int mapId);
	void LoadCurrentMap(Chili_Engine& gfxEngine);
private:
	std::vector<Map> maps;
	unsigned int curMapId;
};