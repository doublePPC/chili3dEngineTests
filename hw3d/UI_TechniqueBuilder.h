#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"
#include "UI_CBufStructs.h"
#include "UI_PlaneGeometry.h"

enum class UI_DrawTech
{
	baseColored,
	baseFileTextured,
	baseSurfaceTextured,
	outline
};

class StepBuilder
{
	// the file extension for shader names (.cso) is already added in this class methods. Only provide the actual name
public:
	StepBuilder() = delete;
	StepBuilder(StepBuilder& step) = delete;
	StepBuilder(std::string stepName);
	~StepBuilder();

	// setters
	void AddVertexShaderInfo(std::string vertexShaderName);
	void AddPixelShaderInfo(std::string pixelShaderName);
	void AddTexture(std::string filePath);
	void AddTexture(std::shared_ptr<Surface> surface);
	void AddEffectColor(float red, float green, float blue, float transparency);

	// getters
	std::string& GetVSName();
	std::string& GetPSName();
	std::string& GetTextureName();
	std::shared_ptr<Surface> GetSurfaceTexture();
	std::string& GetStepName();
	DirectX::XMFLOAT4 GetEffectColor();

	// validators
	bool hasVSName();
	bool hasPSname();
	bool hasFileTexture();
	bool hasSurfaceTexture();
	bool hasEffectColor();
private:
	std::string stepName;
	std::string pixelShaderName;
	std::string vertexShaderName;
	std::string fileTexture;
	std::shared_ptr<Surface> surfaceTexture;
	std::unique_ptr<DirectX::XMFLOAT4> effectColor;
};

class TechniqueBuilder
{
public:
	TechniqueBuilder() = delete;
	TechniqueBuilder(UI_DrawTech techType);
	~TechniqueBuilder();

	void AddStep(std::string stepName);
	void AddStep(std::shared_ptr<StepBuilder> step);

	int GetStepsAmount();
	std::shared_ptr<StepBuilder> GetStepInfo(int index);
	std::shared_ptr<StepBuilder> GetLastStepInfo();
	UI_DrawTech GetTechType();
	const std::string& GetTechName();
private:
	UI_DrawTech techType;
	std::string techName;
	std::vector<std::shared_ptr<StepBuilder>> steps;
public:
	static void AutoFillerBaseColored(std::shared_ptr<TechniqueBuilder> technique, DirectX::XMFLOAT4 color);
	static void AutoFillerFileTextured(std::shared_ptr<TechniqueBuilder> technique, std::string filePath);
	static void AutoFillerSurfaceTextured(std::shared_ptr<TechniqueBuilder> technique, std::shared_ptr<Surface> surface);
	static void AutoFillerOutline(std::shared_ptr<TechniqueBuilder> technique, DirectX::XMFLOAT4 color);
};