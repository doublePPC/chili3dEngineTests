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
#include "Chili_UI.h"

// the following structs stores the datas for creation of scene objects
struct modelData
{
	std::string modelName;
	std::string filePath;
	float scale, rotation, xTranslation, yTranslation, zTranslation;
	bool hasTransform;
};

struct cubeData
{
	float scale, xPos, yPos, zPos;
};

struct cameraData
{
	std::string name;
	float xPos, yPos, zPos;
	float pitch, yaw;
};

struct lightData
{
	float xPos, yPos, zPos;
	float radius;
};

class Chili_Engine
{
public:
	Chili_Engine(const std::string& commandLine = "");
	~Chili_Engine();

	
	void ApplyCameraTranslation(float x, float y, float z);
	DirectX::XMFLOAT3 GetActiveCamPos();
	void ApplyCameraRotation(float x, float y);
	DirectX::XMFLOAT3 GetActiveCamRot();
	void DrawScene(float dt);
	const std::vector<unsigned int>& AcquireRenderedTexture();
	void SetRenderToTextureFlag();

	Window& GetWindowInstance();
	int GetWindowWidth();
	int GetWindowHeight();
	ImguiManager& GetImguiManager();
	Graphics& getGraphics();
	Rgph::BlurOutlineRenderGraph& getRenderGraph();
	void adjustScreenSize(int width, int height);

	// add/remove elements functions
	void AddCube(cubeData data);
	void RemoveAllCubes();

	void AddModel(modelData data);

	void SetupLightCameras(const std::vector<cameraData>& cams, lightData light);

	std::shared_ptr<Chili_UI> GetEmptyUI();

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
	std::unique_ptr<PointLight> light;
	std::vector<std::unique_ptr<TestCube>> cubeList;
	std::unordered_map<std::string, std::unique_ptr<Model>> modelList;
	std::shared_ptr<Chili_UI> ui;

	std::unique_ptr<UISquare> test;
	
	bool savingDepth = false;
	bool techniqueChanged = false;
};