#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"
#include "UI_CBufStructs.h"
#include "UI_PlaneGeometry.h"

class ModelBuilder
{
public:
	ModelBuilder() = delete;
	ModelBuilder(std::pair<IndexedTriangleList, std::string> modelInfo, int size);
	~ModelBuilder();

	IndexedTriangleList& getModel();
	std::string& getTag();
private:
	IndexedTriangleList model;
	std::string geometryTag;
};

class StepBuilder
{
public:
	static void AssembleMainTechnique(std::shared_ptr<Technique> tech, std::shared_ptr<StepBuilder> step)
	{
		//tech = std::make_shared<Technique>(Chan::main);
		tech->AddStep(std::move(step->GetStep()));
	};
	static void AssembleMainTechnique(std::shared_ptr<Technique> tech, std::vector<StepBuilder>& steps)
	{
		tech = std::make_shared<Technique>(Chan::main);
		for(int i = 0 ; i < steps.size() ; i++)
		{
			tech->AddStep(std::move(steps.at(i).GetStep()));
		};
	};
	// the file extension for shader names (.cso) is already added in this class methods. Only provide the actual name
public:
	StepBuilder() = delete;
	StepBuilder(ModelBuilder& _modelRef, std::string stepName, Graphics& gfx);
	~StepBuilder();

	void AddVertexShader(std::string vertexShaderName);
	void AddPixelShader(std::string pixelShaderName);
	void AddTexture(std::string texture);
	void AddTexture(std::shared_ptr<Surface> texture);
	void AddCBuffer(baseTechsCBuf buffer);
	void AddCBuffer(tintTechCBuf buffer);
	void AddCBuffer(fadingTechCBuf buffer);
	void AddCBuffer(colorTechCBuf buffer);
	void AddDefaultRasterizer();

	Step& GetStep();
private:
	ModelBuilder& modelRef;
	Step step;
	Graphics& gfx;
public:
	// auto-filler methods
	static void AutoFiller_UIElementDrawStep(std::shared_ptr<StepBuilder> defaultStep)
	{
		defaultStep->AddVertexShader("Solid_VS");
		defaultStep->AddPixelShader("Solid_PS");

		colorTechCBuf colorConst;
		colorConst.materialColor = { 1.0f, 0.5f, 0.5f };
		defaultStep->AddCBuffer(colorConst);
		defaultStep->AddDefaultRasterizer();
	};

	static void AutoFiller_UIElementDrawStep(std::shared_ptr<StepBuilder> baseTexturedStep, std::string texture)
	{
		baseTexturedStep->AddVertexShader("Solid2D_VS");
		baseTexturedStep->AddTexture(texture);
		baseTexturedStep->AddPixelShader("Textured2D_VS");
	};
};