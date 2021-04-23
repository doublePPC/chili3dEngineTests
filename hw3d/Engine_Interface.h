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

	// getters and setters
	void ApplyCameraTranslation(float x, float y, float z);
	void ApplyCameraRotation(float x, float y);
	void DrawScene(float dt);

	Window& GetWindowInstance();
	ImguiManager& GetImguiManager();

	// elements functions
	void AddCube(float xpos, float ypos, float zpos, float scale);

	// others
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
	std::vector<std::unique_ptr<TestCube>> cubeList;
	std::vector<std::unique_ptr<Model>> modelList;
	
	bool savingDepth = false;
};

//Model sponza{ wnd.Gfx(),"Models\\sponza\\sponza.obj",1.0f / 20.0f };
//Model sponza{ wnd.Gfx(),"Models\\SceneTest\\testScene.obj",1.0f / 1.0f };
//std::unique_ptr<Model> sponzaRef = std::make_unique<Model>(wnd.Gfx(), "Models\\sponza\\sponza.obj", 1.0f / 20.0f);
//Model gobber{ wnd.Gfx(),"Models\\gobber\\GoblinX.obj",4.0f / 4.0f };
//Model nano{ wnd.Gfx(),"Models\\nano_textured\\nanosuit.obj",2.0f / 2.0f };