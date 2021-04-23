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
	cubeList.push_back(std::make_unique<TestCube>(wnd.Gfx(), 4.0f));
	cubeList.push_back(std::make_unique<TestCube>(wnd.Gfx(), 4.0f));
	modelList.push_back(std::make_unique<Model>(wnd.Gfx(), "Models\\sponza\\sponza.obj", 1.0f / 20.0f));
	modelList.push_back(std::make_unique<Model>(wnd.Gfx(), "Models\\gobber\\GoblinX.obj", 1.0f));
	modelList.push_back(std::make_unique<Model>(wnd.Gfx(), "Models\\nano_textured\\nanosuit.obj", 1.0f));

	//objects data setups
	cubeList[0]->SetPos({ 10.0f, 5.0f, 6.0f });
	cubeList[1]->SetPos({ 10.0f, 5.0f, 14.0f });
	modelList[2]->SetRootTransform(
		dx::XMMatrixRotationY(PI / 2.f) *
		dx::XMMatrixTranslation(27.f, -0.56f, 1.7f)
	);
	modelList[1]->SetRootTransform(
		dx::XMMatrixRotationY(-PI / 2.f) *
		dx::XMMatrixTranslation(-8.f, 10.f, 0.f)
	);

	//objects linking
	cubeList[0]->LinkTechniques(rg);
	cubeList[1]->LinkTechniques(rg);
	light.LinkTechniques(rg);
	//sponza.LinkTechniques( rg );
	modelList[0]->LinkTechniques(rg);
	modelList[1]->LinkTechniques(rg);
	modelList[2]->LinkTechniques(rg);
	cameras.LinkTechniques(rg);

	rg.BindShadowCamera(*light.ShareCamera());
}

Chili_Engine::~Chili_Engine()
{
}

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
	for (int i = 0; i < modelList.size(); i++)
	{
		modelList[i]->Submit(Chan::main);
	}
	cameras.Submit(Chan::main);
	
	// submit elements to the shadow channel
	for (int i = 0; i < cubeList.size(); i++)
	{
		cubeList[i]->Submit(Chan::shadow);
	}
	for (int i = 0; i < modelList.size(); i++)
	{
		modelList[i]->Submit(Chan::shadow);
	}

	rg.Execute(wnd.Gfx());

	if (savingDepth)
	{
		rg.DumpShadowMap(wnd.Gfx(), "shadow.png");
		savingDepth = false;
	}

	// imgui windows
	static MP sponzeProbe{ "Sponza" };
	static MP gobberProbe{ "Gobber" };
	static MP nanoProbe{ "Nano" };
	//sponzeProbe.SpawnWindow( sponza );
	sponzeProbe.SpawnWindow(*modelList[0]);
	gobberProbe.SpawnWindow(*modelList[1]);
	nanoProbe.SpawnWindow(*modelList[2]);
	cameras.SpawnWindow(wnd.Gfx());
	light.SpawnControlWindow();
	ShowImguiDemoWindow();
	/*for (int i = 0; i < cubeList.size(); i++)
	{
		cubeList[i]->SpawnControlWindow(wnd.Gfx(), std::string("Cube") + std::to_string(i));
	}*/
	cubeList[0]->SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cubeList[1]->SpawnControlWindow(wnd.Gfx(), "Cube 2");

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
