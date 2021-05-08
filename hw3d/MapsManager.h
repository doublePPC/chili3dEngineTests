#pragma once
#include "Engine_Interface.h"
#include "Map.h"

class MapManager
{
public:
	MapManager();
	~MapManager();

	void LoadCurrentMap(Chili_Engine& gfxEngine);
private:
	std::vector<Map> maps;
	int curMapId;
};