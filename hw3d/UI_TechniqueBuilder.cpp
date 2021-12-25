#include "UI_TechniqueBuilder.h"
#include "Square.h"
#include "BindableCommon.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"
#include "Surface.h"

// StepBuilder methods
StepBuilder::StepBuilder(std::string _stepName)
{
	stepName = _stepName;
	vertexShaderName = "";
	pixelShaderName = "";
	fileTexture = "";
	surfaceTexture = nullptr;
	effectColor = nullptr;
}

StepBuilder::~StepBuilder()
{
}

void StepBuilder::AddVertexShaderInfo(std::string _vertexShaderName)
{
	vertexShaderName = _vertexShaderName + ".cso";
}

void StepBuilder::AddPixelShaderInfo(std::string _pixelShaderName)
{
	pixelShaderName = _pixelShaderName + ".cso";
}

void StepBuilder::AddTexture(std::string filePath)
{
	fileTexture = filePath;
}

void StepBuilder::AddTexture(std::shared_ptr<Surface> surface)
{
	surfaceTexture = surface;
}

void StepBuilder::AddEffectColor(float red, float green, float blue, float transparency)
{
	effectColor = std::make_unique<DirectX::XMFLOAT4>(red, green, blue, transparency);
}

std::string& StepBuilder::GetVSName()
{
	return vertexShaderName;
}

std::string& StepBuilder::GetPSName()
{
	return pixelShaderName;
}

std::string& StepBuilder::GetTextureName()
{
	return fileTexture;
}

std::shared_ptr<Surface> StepBuilder::GetSurfaceTexture()
{
	return surfaceTexture;
}

std::string& StepBuilder::GetStepName()
{
	return stepName;
}
DirectX::XMFLOAT4 StepBuilder::GetEffectColor()
{
	return *effectColor;
}
bool StepBuilder::hasVSName()
{
	if (vertexShaderName == "")
		return false;
	else
		return true;
}
bool StepBuilder::hasPSname()
{
	if (pixelShaderName == "")
		return false;
	else
		return true;
}
bool StepBuilder::hasFileTexture()
{
	if (fileTexture == "")
		return false;
	else
		return true;
}
bool StepBuilder::hasSurfaceTexture()
{
	if (surfaceTexture == nullptr)
		return false;
	else
		return true;
}
bool StepBuilder::hasEffectColor()
{
	if (effectColor == nullptr)
		return false;
	else
		return true;
}
//  -------

// Technique Builder Methods
TechniqueBuilder::TechniqueBuilder(UI_DrawTech techType)
{
	this->techType = techType;
	if (techType == UI_DrawTech::outline)
	{
		techName = "Outline";
	}
	else
	{
		techName = "";
	}
}

TechniqueBuilder::~TechniqueBuilder()
{
}

void TechniqueBuilder::AddStep(std::string stepName)
{
	steps.push_back(std::make_shared<StepBuilder>(stepName));
}

void TechniqueBuilder::AddStep(std::shared_ptr<StepBuilder> step)
{
	steps.push_back(step);
}

int TechniqueBuilder::GetStepsAmount()
{
	return steps.size();
}

std::shared_ptr<StepBuilder> TechniqueBuilder::GetStepInfo(int index)
{
	return steps[index];
}

std::shared_ptr<StepBuilder> TechniqueBuilder::GetLastStepInfo()
{
	return steps.back();
}

UI_DrawTech TechniqueBuilder::GetTechType()
{
	return techType;
}

const std::string& TechniqueBuilder::GetTechName()
{
	return techName;
}


// static Autofiller Methods
void TechniqueBuilder::AutoFillerBaseColored(std::shared_ptr<TechniqueBuilder> technique, DirectX::XMFLOAT4 color)
{
	technique = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseColored);
	technique->AddStep("UIelementDraw");
	technique->GetLastStepInfo()->AddVertexShaderInfo("Solid_VS");
	technique->GetLastStepInfo()->AddPixelShaderInfo("Solid_PS");
	technique->GetLastStepInfo()->AddEffectColor(color.x, color.y, color.z, color.w);
}

void TechniqueBuilder::AutoFillerFileTextured(std::shared_ptr<TechniqueBuilder> technique, std::string filePath)
{
	//technique = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseFileTextured);
	technique->AddStep("UIelementDraw");
	technique->GetLastStepInfo()->AddVertexShaderInfo("Solid2D_VS");
	technique->GetLastStepInfo()->AddPixelShaderInfo("Textured2D_PS");
	technique->GetLastStepInfo()->AddTexture(filePath);
}

void TechniqueBuilder::AutoFillerSurfaceTextured(std::shared_ptr<TechniqueBuilder> technique, std::shared_ptr<Surface> surface)
{
	//technique = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseSurfaceTextured);
	technique->AddStep("UIelementDraw");
	technique->GetLastStepInfo()->AddVertexShaderInfo("Solid2D_VS");
	technique->GetLastStepInfo()->AddPixelShaderInfo("Textured2D_PS");
	//technique->GetLastStepInfo()->AddPixelShaderInfo("WhiteFadingTextured2D_PS");
	technique->GetLastStepInfo()->AddTexture(surface);
}

void TechniqueBuilder::AutoFillerOutline(std::shared_ptr<TechniqueBuilder> technique, DirectX::XMFLOAT4 color)
{
	technique = std::make_shared<TechniqueBuilder>(UI_DrawTech::outline);
	technique->AddStep("outlineMask");
	technique->GetLastStepInfo()->AddVertexShaderInfo("Solid_VS");
	technique->AddStep("outlineDraw");
	technique->GetLastStepInfo()->AddVertexShaderInfo("Solid_VS");
	technique->GetLastStepInfo()->AddEffectColor(color.x, color.y, color.z, color.w);
}
