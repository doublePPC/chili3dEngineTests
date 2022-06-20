#pragma once

#include "Engine_Interface.h"
#include "UI_Graphics.h"
#include "MapsManager.h"
#include <future>
#include "App_UImanager.h"

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
	void Update();

	void CreateSponzaSceneData();
	void InitUI();
private:
	Chili_Engine gfxEngine;
	ChiliTimer timer;
	float speed_factor = 1.0f;
	MapManager mapManager;
	std::shared_ptr<Chili_UI> ui;
	std::shared_ptr<std::vector<UIEventData>> listEvents;

	bool cubesAdded = false;
	bool testAdded = false;
	bool render_ChiliUI = false;
	bool uiHasOnHoverBehaviors = true;
	bool leftWasPreviouslyHeld = false;
	bool rightWasPreviouslyHeld = false;

	float previousMousePosX = -1.0f;
	float previousMousePosY = -1.0f;
};