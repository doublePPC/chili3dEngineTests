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

struct modelData
{
	// includes all the data to create and add a new model in the container
	std::string modelName;
	std::string filePath;
	float scale, rotation, xTranslation, yTranslation, zTranslation;
};

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

	// add/remove elements functions
	void AddCube(float xpos, float ypos, float zpos, float scale);
	void AddSeveralCubes(float scale, int qty);
	void RemoveAllCubes();

	void AddModel(modelData data, bool setRootTransform);

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
	std::unordered_map<std::string, std::unique_ptr<Model>> modelList;
	
	bool savingDepth = false;
};

//Model sponza{ wnd.Gfx(),"Models\\sponza\\sponza.obj",1.0f / 20.0f };
//Model sponza{ wnd.Gfx(),"Models\\SceneTest\\testScene.obj",1.0f / 1.0f };
//std::unique_ptr<Model> sponzaRef = std::make_unique<Model>(wnd.Gfx(), "Models\\sponza\\sponza.obj", 1.0f / 20.0f);
//Model gobber{ wnd.Gfx(),"Models\\gobber\\GoblinX.obj",4.0f / 4.0f };
//Model nano{ wnd.Gfx(),"Models\\nano_textured\\nanosuit.obj",2.0f / 2.0f };
//std::vector<std::unique_ptr<Model>> modelList;

/*static MP sponzeProbe{ "Sponza" };
	static MP gobberProbe{ "Gobber" };
	static MP nanoProbe{ "Nano" };*/
	//sponzeProbe.SpawnWindow( sponza );
	/*sponzeProbe.SpawnWindow(*modelList[0]);
	gobberProbe.SpawnWindow(*modelList[1]);
	nanoProbe.SpawnWindow(*modelList[2]);*/

	/*modelList.push_back(std::make_unique<Model>(wnd.Gfx(), "Models\\sponza\\sponza.obj", 1.0f / 20.0f));
		modelList.push_back(std::make_unique<Model>(wnd.Gfx(), "Models\\gobber\\GoblinX.obj", 1.0f));
		modelList.push_back(std::make_unique<Model>(wnd.Gfx(), "Models\\nano_textured\\nanosuit.obj", 1.0f));*/