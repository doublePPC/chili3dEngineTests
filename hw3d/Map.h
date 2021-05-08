#pragma once
#include "Engine_Interface.h"

class Map {
public:
	Map() = delete;
	Map(const std::string filePath);
	~Map();

	std::string GetName();

	int GetModelCount();
	modelData GetModelDataById(int id);

	int GetCubeCount();
	cubeData GetCubeDataById(int id);
private:
	std::vector<modelData> models;
	std::vector<cubeData> cubes;
	const std::string name;
};