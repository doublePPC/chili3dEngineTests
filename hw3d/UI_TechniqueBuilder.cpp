#include "UI_TechniqueBuilder.h"
#include "Square.h"
#include "BindableCommon.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"
#include "Surface.h"

TechniqueBuilder::TechniqueBuilder(std::string VSname)
	: tech({Chan::main}),
	vertexShaderName(VSname + ".cso")
{
}

TechniqueBuilder::~TechniqueBuilder()
{
}

void TechniqueBuilder::AddStep(Graphics& gfx, std::string pixelShaderName)
{
	using namespace Bind;
	namespace dx = DirectX;

	steps.emplace_back("UIelementDraw");

	steps.back().AddBindable(PixelShader::Resolve(gfx, pixelShaderName + ".cso"));
	steps.back().AddBindable(std::make_shared<TransformCbuf>(gfx));
	steps.back().AddBindable(Rasterizer::Resolve(gfx, false));
}

void TechniqueBuilder::AddStep(Graphics& gfx, std::string pixelShaderName, std::string texture)
{
	using namespace Bind;
	namespace dx = DirectX;

	steps.emplace_back("UIelementDraw");
	auto tex = Texture::Resolve(gfx, texture);
	bool hasAlpha = tex->HasAlpha();
	steps.back().AddBindable(tex);
	steps.back().AddBindable(Sampler::Resolve(gfx));

	steps.back().AddBindable(PixelShader::Resolve(gfx, pixelShaderName + ".cso"));
	steps.back().AddBindable(std::make_shared<TransformCbuf>(gfx));
	steps.back().AddBindable(Rasterizer::Resolve(gfx, hasAlpha));
}

Technique& TechniqueBuilder::GetTechnique()
{
	return tech;
}

Step& TechniqueBuilder::GetStep(int stepIndex)
{
	return steps[stepIndex];
}

std::string& TechniqueBuilder::GetVSname()
{
	return vertexShaderName;
}

int TechniqueBuilder::getStepsAmount()
{
	return steps.size();
}
