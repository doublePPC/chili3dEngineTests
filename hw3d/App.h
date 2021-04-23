#pragma once

#include "Engine_Interface.h"

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
private:
	Chili_Engine gfxEngine;
	ChiliTimer timer;
	float speed_factor = 1.0f;

	bool cubesAdded = false;
};