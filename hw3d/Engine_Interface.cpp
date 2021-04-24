#include "Engine_Interface.h"
#include <algorithm>
#include "ChiliMath.h"
#include "imgui/imgui.h"
#include "ChiliUtil.h"
#include "Testing.h"
#include "PerfLog.h"
#include "TestModelProbe.h"
#include "Testing.h"
#include "Camera.h"
#include "Channels.h"

namespace dx = DirectX;

Chili_Engine::Chili_Engine(const std::string& commandLine)
	:
	commandLine(commandLine),
	wnd(1280, 720, "The Donkey Fart Box"),
	scriptCommander(TokenizeQuoted(commandLine)),
	light(wnd.Gfx(), { 10.0f,5.0f,0.0f })
{
	//sponza scene objects creation
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "A", dx::XMFLOAT3{ -13.5f,6.0f,3.5f }, 0.0f, PI / 2.0f));
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "B", dx::XMFLOAT3{ -13.5f,28.8f,-6.4f }, PI / 180.0f * 13.0f, PI / 180.0f * 61.0f));
	cameras.AddCamera(light.ShareCamera());

	//objects linking
	light.LinkTechniques(rg);
	cameras.LinkTechniques(rg);

	rg.BindShadowCamera(*light.ShareCamera());
}

Chili_Engine::~Chili_Engine()
{
}

// getters and setters
void Chili_Engine::ApplyCameraTranslation(float x, float y, float z)
{
	cameras->Translate({ x, y, z });
}

void Chili_Engine::ApplyCameraRotation(float x, float y)
{
	cameras->Rotate(x, y);
}

void Chili_Engine::DrawScene(float dt)
{
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	light.Bind(wnd.Gfx(), cameras->GetMatrix());
	rg.BindMainCamera(cameras.GetActiveCamera());

	// submit elements to the main channel
	light.Submit(Chan::main);
	for (int i = 0 ; i < cubeList.size() ; i++)
	{
		cubeList[i]->Submit(Chan::main);
	}
	for (auto it = modelList.begin(); it != modelList.end(); ++it)
	{
		auto current = it->first;
		modelList[current]->Submit(Chan::main);
	}
	cameras.Submit(Chan::main);
	
	// submit elements to the shadow channel
	for (int i = 0; i < cubeList.size(); i++)
	{
		cubeList[i]->Submit(Chan::shadow);
	}
	for (auto it = modelList.begin(); it != modelList.end(); ++it)
	{
		auto current = it->first;
		modelList[current]->Submit(Chan::shadow);
	}

	rg.Execute(wnd.Gfx());

	if (savingDepth)
	{
		rg.DumpShadowMap(wnd.Gfx(), "shadow.png");
		savingDepth = false;
	}

	// imgui windows
	const int size = modelList.size();
	std::vector<std::unique_ptr<MP>> modelProbeList;
	modelProbeList.reserve(size);
	for (auto it = modelList.begin(); it != modelList.end(); ++it)
	{
		modelProbeList.push_back(std::make_unique<MP>(it->first));
		modelProbeList.back()->SpawnWindow(*it->second);
	}
	
	cameras.SpawnWindow(wnd.Gfx());
	light.SpawnControlWindow();
	ShowImguiDemoWindow();
	for (int i = 0; i < cubeList.size(); i++)
	{
		std::string elemName = "Cube ";
		std::string name = elemName + std::to_string(i +1);
		cubeList[i]->SpawnControlWindow(wnd.Gfx(), name.c_str());
	}

	rg.RenderWindows(wnd.Gfx());

	// present
	wnd.Gfx().EndFrame();
	rg.Reset();
}

Window& Chili_Engine::GetWindowInstance()
{
	return wnd;
}

ImguiManager& Chili_Engine::GetImguiManager()
{
	return imgui;
}
// -----------------

// add/remove elements functions
void Chili_Engine::AddCube(float xpos, float ypos, float zpos, float scale)
{
	cubeList.push_back(std::make_unique<TestCube>(wnd.Gfx(), scale));
	cubeList.back()->SetPos({ xpos, ypos, zpos });
	cubeList.back()->LinkTechniques(rg);
}

void Chili_Engine::AddSeveralCubes(float scale, int qty)
{
	int spaceLeft = cubeList.capacity() - cubeList.size();
	if (spaceLeft < qty)
	{
		cubeList.reserve(cubeList.capacity() + qty - spaceLeft);
	}
	for (int i = 0; i < qty; i++)
	{
		cubeList.push_back(std::make_unique<TestCube>(wnd.Gfx(), scale));
		cubeList.back()->SetPos({ 0.0f + (float)i * 5.0f , 0.0f , 0.0f });
		cubeList.back()->LinkTechniques(rg);
	}
}

void Chili_Engine::RemoveAllCubes()
{
	cubeList.clear();
	cubeList.shrink_to_fit();
}

void Chili_Engine::AddModel(modelData data, bool setRootTransform)
{
	modelList.emplace(data.modelName , std::make_unique<Model>(wnd.Gfx(), data.filePath, data.scale));
	auto it = modelList.find(data.modelName);
	if (setRootTransform)
	{
		it->second->SetRootTransform(
			dx::XMMatrixRotationY(data.rotation) *
			dx::XMMatrixTranslation(data.xTranslation, data.yTranslation, data.zTranslation)
		);
	}
	it->second->LinkTechniques(rg);
}
// ------------------------


// others
void Chili_Engine::SetDemoWindow(bool value)
{
	showDemoWindow = value;
}

void Chili_Engine::SetSavingDepth(bool value)
{
	savingDepth = value;
}

void Chili_Engine::ShowImguiDemoWindow()
{
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
}
// -------------------
