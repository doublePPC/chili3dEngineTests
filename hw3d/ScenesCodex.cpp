#include "ScenesCodex.h"

void HardCodedScenes::InitSponzaModels(std::vector<modelData>& refMapData)
{
	// create Sponza
	modelData sponza;
	sponza.filePath = "Models\\sponza\\sponza.obj";
	sponza.modelName = "Sponza";
	sponza.rotation = 0.0f;
	sponza.scale = 1.0f / 20.0f;
	sponza.xTranslation = 0.0f;
	sponza.yTranslation = 0.0f;
	sponza.zTranslation = 0.0f;
	sponza.hasTransform = false;
	refMapData.push_back(sponza);
	// create Gobber
	modelData gobber;
	gobber.filePath = "Models\\gobber\\GoblinX.obj";
	gobber.modelName = "Gobber";
	gobber.rotation = -PI / 2.f;
	gobber.scale = 1.0f;
	gobber.xTranslation = -8.f;
	gobber.yTranslation = 10.f;
	gobber.zTranslation = 0.f;
	gobber.hasTransform = true;
	refMapData.push_back(gobber);
	// create Nano
	modelData nano;
	nano.filePath = "Models\\nano_textured\\nanosuit.obj";
	nano.modelName = "Nano";
	nano.rotation = PI / 2.f;
	nano.scale = 1.0f;
	nano.xTranslation = 27.f;
	nano.yTranslation = -0.56f;
	nano.zTranslation = 1.7f;
	nano.hasTransform = true;
	refMapData.push_back(nano);
}

void HardCodedScenes::InitSponzaCubes(std::vector<cubeData>& refMapData)
{
	cubeData cube1, cube2;
	cube1.scale = 4.0f;
	cube1.xPos = 10.0f;
	cube1.yPos = 5.0f;
	cube1.zPos = 6.0f;
	cube2.scale = 4.0f;
	cube2.xPos = 10.0f;
	cube2.yPos = 5.0f;
	cube2.zPos = 14.0f;
	refMapData.push_back(cube1);
	refMapData.push_back(cube2);
}

void HardCodedScenes::InitCameras(std::vector<cameraData>& refCamData)
{
	cameraData cam1, cam2;
	cam1.name = "A";
	cam1.xPos = -13.5f;
	cam1.yPos = 6.0f;
	cam1.zPos = 3.5f;
	cam1.pitch = 0.0f;
	cam1.yaw = PI / 2.0f;
	cam2.name = "B";
	cam2.xPos = -13.5f;
	cam2.yPos = 28.8f;
	cam2.zPos = -6.4f;
	cam2.pitch = PI / 180.0f * 13.0f;
	cam2.yaw = PI / 180.0f * 61.0f;
	refCamData.push_back(cam1);
	refCamData.push_back(cam2);
}

void HardCodedScenes::InitLight(lightData& refLight)
{
	refLight.radius = 0.5f;
	refLight.xPos = 10.0f;
	refLight.yPos = 5.0f;
	refLight.zPos = 0.0f;
}
