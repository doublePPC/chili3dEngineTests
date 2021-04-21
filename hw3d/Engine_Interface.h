#pragma once
#include "Window.h"
#include "ChiliTimer.h"
#include "ImguiManager.h"
#include "CameraContainer.h"
#include "PointLight.h"
#include "TestCube.h"
#include "Model.h"
#include "ScriptCommander.h"
#include "BlurOutlineRenderGraph.h"
#include "ChiliMath.h"

class Chili_Engine
{
public:
	Chili_Engine(const std::string& commandLine = "");
	~Chili_Engine();

	void ApplyCameraTranslation(float x, float y, float z);
	void ApplyCameraRotation(float x, float y);
	void DrawScene(float dt);

	Window& GetWindowInstance();
	ImguiManager& GetImguiManager();

	void SetDemoWindow(bool value);
	void SetSavingDepth(bool value);
private:
	void ShowImguiDemoWindow();
private:
	std::string commandLine;
	bool showDemoWindow = false;
	ImguiManager imgui;
	Window wnd;
	ScriptCommander scriptCommander;
	Rgph::BlurOutlineRenderGraph rg{ wnd.Gfx() };
	CameraContainer cameras;
	PointLight light;
	TestCube cube{ wnd.Gfx(),4.0f };
	TestCube cube2{ wnd.Gfx(),4.0f };
	//Model sponza{ wnd.Gfx(),"Models\\sponza\\sponza.obj",1.0f / 20.0f };
	//Model sponza{ wnd.Gfx(),"Models\\SceneTest\\testScene.obj",1.0f / 1.0f };
	std::unique_ptr<Model> sponzaRef = std::make_unique<Model>(wnd.Gfx(), "Models\\sponza\\sponza.obj", 1.0f / 20.0f);
	Model gobber{ wnd.Gfx(),"Models\\gobber\\GoblinX.obj",4.0f / 4.0f };
	Model nano{ wnd.Gfx(),"Models\\nano_textured\\nanosuit.obj",2.0f / 2.0f };
	bool savingDepth = false;
};