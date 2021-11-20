#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"
#include "UI_CBufStructs.h"

class TechniqueBuilder
{
	// the file extension for shader names (.cso) is already added in this class methods. Only provide the actual name
public:
	TechniqueBuilder(std::string VSname);
	~TechniqueBuilder();

	void AddStep(Graphics& gfx, std::string pixelShaderName);
	void AddStep(Graphics& gfx, std::string pixelShaderName, std::string texture);

	Technique& GetTechnique();
	Step& GetStep(int stepIndex);
	std::string& GetVSname();
	int getStepsAmount();
private:
	Technique tech;
	std::vector<Step> steps;
	std::string vertexShaderName;
};