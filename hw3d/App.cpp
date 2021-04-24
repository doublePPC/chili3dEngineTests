#include "App.h"

App::App( const std::string& commandLine )
	:
	gfxEngine(commandLine)
{
	
}

void App::HandleInput( float dt )
{
	Window& wnd = gfxEngine.GetWindowInstance();
	while( const auto e = wnd.kbd.ReadKey() )
	{
		if( !e->IsPress() )
		{
			continue;
		}

		switch( e->GetCode() )
		{
		case VK_ESCAPE:
			if( wnd.CursorEnabled() )
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			gfxEngine.SetDemoWindow(true);
			break;
		case VK_RETURN:
			gfxEngine.SetSavingDepth(true);
			break;
		}
	}

	if( !wnd.CursorEnabled() )
	{
		if( wnd.kbd.KeyIsPressed( 'W' ) )
		{
			gfxEngine.ApplyCameraTranslation(0.0f, 0.0f, dt);
		}
		if( wnd.kbd.KeyIsPressed( 'A' ) )
		{
			gfxEngine.ApplyCameraTranslation(-dt, 0.0f, 0.0f);
		}
		if( wnd.kbd.KeyIsPressed( 'S' ) )
		{
			gfxEngine.ApplyCameraTranslation(0.0f, 0.0f, -dt);
		}
		if( wnd.kbd.KeyIsPressed( 'D' ) )
		{
			gfxEngine.ApplyCameraTranslation(dt, 0.0f, 0.0f);
		}
		if( wnd.kbd.KeyIsPressed( 'R' ) )
		{
			gfxEngine.ApplyCameraTranslation(0.0f, dt, 0.0f);
		}
		if( wnd.kbd.KeyIsPressed( 'F' ) )
		{
			gfxEngine.ApplyCameraTranslation(0.0f, -dt, 0.0f);
		}
		if (wnd.kbd.KeyIsPressed('M'))
		{
			if (!cubesAdded)
			{
				// recreates Chili's Sponza Scene
				cubesAdded = true;
				this->CreateSponzaSceneData();
			}
		}
	}

	while( const auto delta = wnd.mouse.ReadRawDelta() )
	{
		if( !wnd.CursorEnabled() )
		{
			gfxEngine.ApplyCameraRotation( (float)delta->x,(float)delta->y );
		}
	}
}

void App::CreateSponzaSceneData()
{
	gfxEngine.AddCube(10.0f, 5.0f, 6.0f, 4.0f);
	gfxEngine.AddCube(10.0f, 5.0f, 14.0f, 4.0f);

	// create Sponza
	modelData sponzaData;
	sponzaData.filePath = "Models\\sponza\\sponza.obj";
	sponzaData.modelName = "Sponza";
	sponzaData.rotation = 0.0f;
	sponzaData.scale = 1.0f / 20.0f;
	sponzaData.xTranslation = 0.0f;
	sponzaData.yTranslation = 0.0f; 
	sponzaData.zTranslation = 0.0f;
	gfxEngine.AddModel(sponzaData, false);

	// create Gobber
	modelData gobberData;
	gobberData.filePath = "Models\\gobber\\GoblinX.obj";
	gobberData.modelName = "Gobber";
	gobberData.rotation = -PI / 2.f;
	gobberData.scale = 1.0f;
	gobberData.xTranslation = -8.f;
	gobberData.yTranslation = 10.f;
	gobberData.zTranslation = 0.f;
	gfxEngine.AddModel(gobberData, true);

	// create Nano
	modelData nanoData;
	nanoData.filePath = "Models\\nano_textured\\nanosuit.obj";
	nanoData.modelName = "Nano";
	nanoData.rotation = PI / 2.f;
	nanoData.scale = 1.0f;
	nanoData.xTranslation = 27.f;
	nanoData.yTranslation = -0.56f;
	nanoData.zTranslation = 1.7f;
	gfxEngine.AddModel(nanoData, true);
};

void App::DoFrame( float dt )
{
	gfxEngine.DrawScene(dt);
}

App::~App()
{}

int App::Go()
{
	while( true )
	{
		// process all messages pending, but to not block for new messages
		if( const auto ecode = Window::ProcessMessages() )
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		// execute the game logic
		const auto dt = timer.Mark() * speed_factor;
		HandleInput( dt );
		DoFrame( dt );
	}
}