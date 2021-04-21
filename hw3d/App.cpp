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
	}

	while( const auto delta = wnd.mouse.ReadRawDelta() )
	{
		if( !wnd.CursorEnabled() )
		{
			gfxEngine.ApplyCameraRotation( (float)delta->x,(float)delta->y );
		}
	}
}

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