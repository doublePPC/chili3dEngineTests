#include "App.h"

App::App( const std::string& commandLine )
	:
	gfxEngine(commandLine),
	mapManager()
{
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
		if (wnd.kbd.KeyIsPressed('N'))
		{
			if (!testAdded)
			{
				// recreates Chili's Sponza Scene
				testAdded = true;
				mapManager.SetCurrentMapToId(1);
				mapManager.LoadCurrentMap(gfxEngine);
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

	const auto wheel = wnd.mouse.Read();
	if (wheel.has_value() && ui != nullptr)
	{
		if (wheel->GetType() == Mouse::Event::Type::WheelUp)
		{
			ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::wheelUp);
		}
		else if (wheel->GetType() == Mouse::Event::Type::WheelDown)
		{
			ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::wheelDown);
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
			if (leftWasPreviouslyHeld == false)
			{
				// a new left click has been registered
				ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::leftClick);
				leftWasPreviouslyHeld = true;
			}
			else
			{
				// a left click from a previous frame is still going on
			}
		}
		else
		{
			if (leftWasPreviouslyHeld == true)
			{
				// a left release event has been acknowledged
				leftWasPreviouslyHeld = false;
			}		
		}
		if (wnd.mouse.RightIsPressed())
		{
			if (rightWasPreviouslyHeld == false)
			{
				// a new right click has been registered
				ui->onMouseEvent(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), mouseEvents::rightClick);
				rightWasPreviouslyHeld = true;
			}
			else
			{
				// a right click from a previous frame is still going on
			}
		}
		else
		{
			if (rightWasPreviouslyHeld == true)
			{
				// a right release event has been acknowledged
				rightWasPreviouslyHeld = false;
			}
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

	//ui->addElement(win1Data);

	ElementData winLeftData;
	winLeftData.hasBackground = true;
	winLeftData.amountOfComponents = 0;
	winLeftData.relPos = { -1.0f, 0.0f, 0.0f };
	winLeftData.size = { 0.5f, 1.0f, 1.0f };
	//ui->addElement(winLeftData);

	ElementData winRightData;
	winRightData.hasBackground = true;
	winRightData.amountOfComponents = 0;
	winRightData.relPos = { 1.0f, 0.0f, 0.0f };
	winRightData.size = { 0.5f, 1.0f, 1.0f };
	//ui->addElement(winRightData);

	//ElementData win2Data;
	//win2Data.hasBackground = true;
	//win2Data.amountOfComponents = 1;
	//win2Data.relPos = { -0.5f, 0.0f, 0.0f };
	//win2Data.size = { 0.5f, 2.0f, 1.0f };

	//ComponentData win2Comp1Data;
	//win2Comp1Data.relPos = { 0.0f, 0.0f, 0.0f };
	//win2Comp1Data.size = { 0.3f, 2.0f, 1.0f };
	//win2Comp1Data.drawTech = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseSurfaceTextured);
	////std::shared_ptr<Surface> textImage = UI_Utils::stringToSurface("Pusheen");
	//Surface::Color colorOne = { 1, 128, 255, 128 };
	//Surface::Color colorTwo = { 1, 192, 192, 192 };
	//UI_TextFragments textDetails(2);
	//std::string textOne = "P  ";
	//std::string textTwo = "usheen";
	//textDetails.addFragment(textOne, colorOne);
	//textDetails.addFragment(textTwo, colorTwo);
	//std::shared_ptr<Surface> textImage = textDetails.acquireSurfaceFromFragments();
	//TechniqueBuilder::AutoFillerSurfaceTextured(win2Comp1Data.drawTech, textImage);
	//win2Data.list_ComponentsData.push_back(win2Comp1Data);

	//ui->addElement(win2Data);

	//ElementData newElementData;
	//newElementData.hasBackground = false;
	//newElementData.amountOfComponents = 0;
	//newElementData.relPos = { 0.5f, -0.3f, 0.0f };
	//newElementData.size = { 0.3f, 1.0f, 1.0f };
	////list_UiElements.emplace_back(std::make_shared<UI_Element>(newElementData, gfx, rgRef));
	//ui->addElement(newElementData);

	//ComponentData buttonData = { newElementData.relPos, newElementData.size };
	//std::string buttonFilePath = "Images\\buttonIcon.png";
	//std::string buttonText = "UP";
	//std::shared_ptr<UI_Button> testButton = std::make_shared<UI_Button>(buttonData, gfxEngine.getGraphics(), buttonFilePath, buttonText);
	////list_UiElements.back()->addComponent(testButton, rgRef);
	//ui->addComponentToLastElement(testButton, gfxEngine.getRenderGraph());

	ElementData win3Data;
	win3Data.hasBackground = true;
	win3Data.amountOfComponents = 1;
	win3Data.relPos = { -0.5f, 0.0f, 0.0f };
	win3Data.size = { 1.6f, 1.0f, 1.0f };
	//ui->addElement(win3Data);

	Police comp3Police = { 11, textAlignment::right, lignSpace::simple, { 255, 64, 64, 64}, FONT_DEFAULT, true };

	ComponentData win3Comp1Data;
	win3Comp1Data.relPos = { 0.0f, 0.0f, 0.0f };
	win3Comp1Data.size = { 1.2f, 1.0f, 1.0f };
	std::string TxtBoxBackFilePath = "Images\\brickwall.jpg";
	std::string TxtBoxContent = "Salut les |cffffcc00amis|r! Je suis content de tester ce programme amateur de ma conception. Maintenant, je peux mettre de la ponctuation (n'est-ce pas merveilleux!). |cff32cd32Alors|r, puisque j'ai maintenant conçu la scroll bar et son comportement de base, je dois prolonger la longueur de mon texte pour mettre tout ça à l'épreuve.";
	//std::string TxtBoxContent = "anticonstitutionnelle";
	//std::string TxtBoxContent = "ï ì î è à È À Ù ù ò Ò É é ê Ê Â â";
	//std::string TxtBoxContent = "Être ou ne pas être... telle est la question que je me posais : Est-ce que le programme va planter si je mets des circonflexes!";
	//std::string TxtBoxContent = "Les Des Mes Ces Mon Ton Son La Le Il De Du Tu ... Bon, je dois m'assurer que ce texte devienne assez long pour qu'une scroll bar soit requise afin de tout l'afficher.";
	std::shared_ptr<UI_TextBox> testTxtBox = std::make_shared<UI_TextBox>(win3Comp1Data, gfxEngine.getGraphics(), TxtBoxBackFilePath, TxtBoxContent, comp3Police);
	//ui->addComponentToLastElement(testTxtBox, gfxEngine.getRenderGraph());
}

void App::DoFrame( float dt )
{
	gfxEngine.adjustScreenSize(gfxEngine.GetWindowWidth(), gfxEngine.GetWindowHeight());
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