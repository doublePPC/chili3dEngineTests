#pragma once
#include "UI_TechniqueBuilder.h"

class TechniqueAssembler
{
public:
	static void AssembleStep(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr<StepBuilder> stepData, UI_DrawTech techType);
private:
	static void AssembleBaseColored(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData);
	static void AssembleBaseFileTextured(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData);
	static void AssembleBaseSurfaceTextured(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData);
	static void AssembleOutlineMask(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData);
	static void AssembleOutlineDraw(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData);

	static void LoadKappaFailure(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData);
};