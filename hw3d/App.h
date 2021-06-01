#pragma once

#include "Engine_Interface.h"
#include "UI_Graphics.h"
#include "MapsManager.h"
#include <future>

class App
{
public:
	App( const std::string& commandLine = "" );
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame( float dt );
	void HandleInput( float dt );

	void CreateSponzaSceneData();
private:
	Chili_Engine gfxEngine;
	ChiliTimer timer;
	float speed_factor = 1.0f;
	MapManager mapManager;
	UI_Graphics userInterface;

	bool cubesAdded = false;
	bool render_ChiliUI = false;
};