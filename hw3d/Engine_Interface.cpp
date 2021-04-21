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
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "A", dx::XMFLOAT3{ -13.5f,6.0f,3.5f }, 0.0f, PI / 2.0f));
	cameras.AddCamera(std::make_unique<Camera>(wnd.Gfx(), "B", dx::XMFLOAT3{ -13.5f,28.8f,-6.4f }, PI / 180.0f * 13.0f, PI / 180.0f * 61.0f));
	cameras.AddCamera(light.ShareCamera());

	cube.SetPos({ 10.0f,5.0f,6.0f });
	cube2.SetPos({ 10.0f,5.0f,14.0f });
	nano.SetRootTransform(
		dx::XMMatrixRotationY(PI / 2.f) *
		dx::XMMatrixTranslation(27.f, -0.56f, 1.7f)
	);
	gobber.SetRootTransform(
		dx::XMMatrixRotationY(-PI / 2.f) *
		dx::XMMatrixTranslation(-8.f, 10.f, 0.f)
	);

	cube.LinkTechniques(rg);
	cube2.LinkTechniques(rg);
	light.LinkTechniques(rg);
	//sponza.LinkTechniques( rg );
	sponzaRef->LinkTechniques(rg);
	gobber.LinkTechniques(rg);
	nano.LinkTechniques(rg);
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

	light.Submit(Chan::main);
	cube.Submit(Chan::main);
	//sponza.Submit( Chan::main );
	sponzaRef->Submit(Chan::main);
	cube2.Submit(Chan::main);
	gobber.Submit(Chan::main);
	nano.Submit(Chan::main);
	cameras.Submit(Chan::main);

	//sponza.Submit( Chan::shadow );
	sponzaRef->Submit(Chan::shadow);
	cube.Submit(Chan::shadow);
	//sponza.Submit( Chan::shadow );
	sponzaRef->Submit(Chan::shadow);
	cube2.Submit(Chan::shadow);
	gobber.Submit(Chan::shadow);
	nano.Submit(Chan::shadow);

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
	sponzeProbe.SpawnWindow(*sponzaRef);
	gobberProbe.SpawnWindow(gobber);
	nanoProbe.SpawnWindow(nano);
	cameras.SpawnWindow(wnd.Gfx());
	light.SpawnControlWindow();
	ShowImguiDemoWindow();
	cube.SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cube2.SpawnControlWindow(wnd.Gfx(), "Cube 2");

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
