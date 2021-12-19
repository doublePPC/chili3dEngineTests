#include "App.h"

App::App( const std::string& commandLine )
	:
	gfxEngine(commandLine),
	mapManager()
{
	//gfxEngine.AddUI();
	ui = gfxEngine.GetEmptyUI();
	InitUI();
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
		if (wnd.kbd.KeyIsPressed('T'))
		{
			//gfxEngine.testTechnique();
		}
	}

	while( const auto delta = wnd.mouse.ReadRawDelta() )
	{
		if( !wnd.CursorEnabled() )
		{
			gfxEngine.ApplyCameraRotation( (float)delta->x,(float)delta->y );
		}
	}

	if (uiHasOnHoverBehaviors)
	{
		if (wnd.mouse.GetPosX() != this->previousMousePosX || wnd.mouse.GetPosY() != this->previousMousePosY)
		{
			ui->resetOnHoverState();
			ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::onHover);
		}
		if (wnd.mouse.LeftIsPressed())
		{
			ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::leftClick);
		}
		if (wnd.mouse.RightIsPressed())
		{
			ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::rightClick);
		}
	}
	else
	{
		if (wnd.mouse.LeftIsPressed())
		{
			ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::leftClick);
		}
		if (wnd.mouse.RightIsPressed())
		{
			ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::rightClick);
		}
	}
}

void App::Update()
{
	//ui->update(gfxEngine.GetActiveCamRot(), gfxEngine.GetActiveCamPos());
}

void App::CreateSponzaSceneData()
{
	mapManager.LoadCurrentMap(gfxEngine);
}
void App::InitUI()
{
	/*ElementData newElementData;
	newElementData.hasBackground = false;
	newElementData.amountOfComponents = 0;
	newElementData.relPos = { -1.0f, -0.3f, 0.0f };
	newElementData.size = { 0.3f, 1.0f, 1.0f };
	list_UiElements.emplace_back(std::make_shared<UI_Element>(newElementData, gfx, rgRef));*/

	/*ElementData elementONEdata;
	RelativePosition componentPos = { 0.5f, 0.0f, 0.0f };
	Size componentSize = { 0.5f, 1.0f, 1.0f };
	ImageData componentImg;
	componentImg.filePath = "Images\\buttonIcon.png";
	elementONEdata.hasBackground = true;
	elementONEdata.amountOfComponents = 1;
	elementONEdata.relPos = { 0.0f, 0.2f, 0.0f };
	elementONEdata.size = { 0.5f, 2.0f, 1.0f };
	ComponentData elemONEcomponent = { componentPos, componentSize, componentImg };
	elementONEdata.list_ComponentsData.push_back(elemONEcomponent);*/

	// Element creation (UI window)
	ElementData win1Data;
	win1Data.hasBackground = true;
	win1Data.amountOfComponents = 1;
	win1Data.relPos = { 0.0f, 0.2f, 0.0f };
	win1Data.size = { 0.5f, 2.0f, 1.0f };

	ComponentData win1Comp1Data;
	win1Comp1Data.relPos = { 0.5f, 0.0f, 0.0f };
	win1Comp1Data.size = { 0.5f, 1.0f, 1.0f };
	win1Comp1Data.drawTech = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseFileTextured);
	TechniqueBuilder::AutoFillerFileTextured(win1Comp1Data.drawTech, "Images\\buttonIcon.png");
	win1Data.list_ComponentsData.push_back(win1Comp1Data);

	ui->addElement(win1Data);
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