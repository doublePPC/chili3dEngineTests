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
	scriptCommander(TokenizeQuoted(commandLine))
{
	this->light = std::make_unique<PointLight>(wnd.Gfx(), dx::XMFLOAT3{ 0.0f, 0.0f, 0.0f });
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "default", dx::XMFLOAT3{ -10.0f, 10.0f, 5.0f }, 0.0f, 0.0f));
	cameras.AddCamera(this->light->ShareCamera());

	test = std::make_unique<UISquare>(wnd.Gfx(), 0.7f, 1.0f, 1.0f, "Images\\stripes.png");
	test->SetPos({0.0f, 0.0f, 0.0f}, { -9.5f, 10.0f, 7.0f });

	//objects linking
	this->light->LinkTechniques(rg);
	cameras.LinkTechniques(rg);
	test->LinkTechniques(rg);

	rg.BindShadowCamera(*this->light->ShareCamera());
}

Chili_Engine::~Chili_Engine()
{
}

void Chili_Engine::ApplyCameraTranslation(float x, float y, float z)
{
	cameras->Translate({ x, y, z });
}

DirectX::XMFLOAT3 Chili_Engine::GetActiveCamPos()
{
	DirectX::XMFLOAT3 camPos = cameras.GetActiveCamera().GetPos();
	return camPos;
}

void Chili_Engine::ApplyCameraRotation(float x, float y)
{
	cameras->Rotate(x, y);
}

DirectX::XMFLOAT3 Chili_Engine::GetActiveCamRot()
{
	DirectX::XMFLOAT3 camRot = cameras.GetActiveCamera().GetRot();
	return camRot;
}

void Chili_Engine::DrawScene(float dt)
{
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	light->Bind(wnd.Gfx(), cameras->GetMatrix());
	rg.BindMainCamera(cameras.GetActiveCamera());

	// submit elements to the main channel
	light->Submit(Chan::main);
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
	test->Submit(Chan::main);
	if (ui != nullptr)
	{
		DirectX::XMFLOAT3 rot = cameras.GetActiveCamera().GetRot();
		DirectX::XMFLOAT3 pos = cameras.GetActiveCamera().GetPos();
		ui->update(rot, pos);
	}
	
	
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
	light->SpawnControlWindow();
	ShowImguiDemoWindow();
	for (int i = 0; i < cubeList.size(); i++)
	{
		std::string elemName = "Cube ";
		std::string name = elemName + std::to_string(i +1);
		cubeList[i]->SpawnControlWindow(wnd.Gfx(), name.c_str());
	}
	if(ui != nullptr)
		ui->spawnControlWindows();
	rg.RenderWindows(wnd.Gfx());
	

	// present
	wnd.Gfx().EndFrame();
	rg.Reset();
}

const std::vector<unsigned int>& Chili_Engine::AcquireRenderedTexture()
{
	return wnd.Gfx().GetRenderedTexture();
}

void Chili_Engine::SetRenderToTextureFlag()
{
	wnd.Gfx().SetRenderingToTexture();
}

Window& Chili_Engine::GetWindowInstance()
{
	return wnd;
}

int Chili_Engine::GetWindowWidth()
{
	return wnd.getWidth();
}

int Chili_Engine::GetWindowHeight()
{
	return wnd.getHeight();
}

ImguiManager& Chili_Engine::GetImguiManager()
{
	return imgui;
}
// -----------------

// add/remove elements functions
void Chili_Engine::AddCube(cubeData data)
{
	cubeList.push_back(std::make_unique<TestCube>(wnd.Gfx(), data.scale));
	cubeList.back()->SetPos({ data.xPos, data.yPos, data.zPos });
	cubeList.back()->LinkTechniques(rg);
}

void Chili_Engine::RemoveAllCubes()
{
	cubeList.clear();
	cubeList.shrink_to_fit();
}

void Chili_Engine::AddModel(modelData data)
{
	modelList.emplace(data.modelName , std::make_unique<Model>(wnd.Gfx(), data.filePath, data.scale));
	auto it = modelList.find(data.modelName);
	if (data.hasTransform)
	{
		it->second->SetRootTransform(
			dx::XMMatrixRotationY(data.rotation) *
			dx::XMMatrixTranslation(data.xTranslation, data.yTranslation, data.zTranslation)
		);
	}
	it->second->LinkTechniques(rg);
}

void Chili_Engine::SetupLightCameras(const std::vector<cameraData>& cams, lightData light)
{
	this->light.release();
	this->light = std::make_unique<PointLight>(wnd.Gfx(), dx::XMFLOAT3{ light.xPos, light.yPos, light.zPos }, light.radius);

	for (int i = 0; i < cams.size(); i++)
	{
		cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), cams[i].name, dx::XMFLOAT3{ cams[i].xPos, cams[i].yPos, cams[i].zPos }, cams[i].pitch, cams[i].yaw));
	}
	cameras.AddCamera(this->light->ShareCamera());

	//objects linking
	this->light->LinkTechniques(rg);
	cameras.LinkTechniques(rg);

	rg.BindShadowCamera(*this->light->ShareCamera());
}

std::shared_ptr<Chili_UI> Chili_Engine::GetEmptyUI()
{
	std::shared_ptr<Chili_UI> newUI = std::make_shared<Chili_UI>(wnd.Gfx(), rg, GetWindowWidth(), GetWindowHeight());
	ui = newUI;
	return newUI;
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
