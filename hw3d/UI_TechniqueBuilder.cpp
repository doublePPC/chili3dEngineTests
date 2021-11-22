#include "UI_TechniqueBuilder.h"
#include "Square.h"
#include "BindableCommon.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"
#include "Surface.h"

//  ModelBuilder methods
ModelBuilder::ModelBuilder(std::pair<IndexedTriangleList, std::string> modelInfo, int size)
	: model(modelInfo.first)
{
	model.Transform(DirectX::XMMatrixScaling(size, size, 1.0f));
	geometryTag = modelInfo.second + std::to_string(size);
}

ModelBuilder::~ModelBuilder()
{
}

IndexedTriangleList& ModelBuilder::getModel()
{
	return model;
}

std::string& ModelBuilder::getTag()
{
	return geometryTag;
}
//  -------


// StepBuilder methods
StepBuilder::StepBuilder(ModelBuilder& _modelRef, std::string stepName, Graphics& gfx)
	: modelRef(_modelRef),
	step(stepName),
	gfx(gfx)
{
	step.AddBindable(std::make_shared<Bind::TransformCbuf>(gfx));
}

StepBuilder::~StepBuilder()
{
}

void StepBuilder::AddVertexShader(std::string vertexShaderName)
{
	auto pvs = Bind::VertexShader::Resolve(gfx, vertexShaderName + ".cso");
	step.AddBindable(Bind::InputLayout::Resolve(gfx, modelRef.getModel().vertices.GetLayout(), *pvs));
	step.AddBindable(std::move(pvs));
}

void StepBuilder::AddPixelShader(std::string pixelShaderName)
{
	step.AddBindable(Bind::PixelShader::Resolve(gfx, pixelShaderName + ".cso"));
}

void StepBuilder::AddTexture(std::string texture)
{
	auto tex = Bind::Texture::Resolve(gfx, texture);
	bool hasAlpha = tex->HasAlpha();
	step.AddBindable(tex);
	step.AddBindable(Bind::Sampler::Resolve(gfx));
	step.AddBindable(Bind::Rasterizer::Resolve(gfx, hasAlpha));
}

void StepBuilder::AddTexture(std::shared_ptr<Surface> texture)
{
	auto tex = std::make_shared<Bind::Texture>(gfx, texture);
	bool hasAlpha = tex->HasAlpha();
	step.AddBindable(tex);
	step.AddBindable(Bind::Sampler::Resolve(gfx));
	step.AddBindable(Bind::Rasterizer::Resolve(gfx, hasAlpha));
}

void StepBuilder::AddCBuffer(baseTechsCBuf buffer)
{
	step.AddBindable(Bind::PixelConstantBuffer<baseTechsCBuf>::Resolve(gfx, buffer, 1u));
}

void StepBuilder::AddCBuffer(tintTechCBuf buffer)
{
	step.AddBindable(Bind::PixelConstantBuffer<tintTechCBuf>::Resolve(gfx, buffer, 1u));
}

void StepBuilder::AddCBuffer(fadingTechCBuf buffer)
{
	step.AddBindable(Bind::PixelConstantBuffer<fadingTechCBuf>::Resolve(gfx, buffer, 1u));
}

void StepBuilder::AddCBuffer(colorTechCBuf buffer)
{
	step.AddBindable(Bind::PixelConstantBuffer<colorTechCBuf>::Resolve(gfx, buffer, 1u));
}

void StepBuilder::AddDefaultRasterizer()
{
	// used if a texture isn't bound
	step.AddBindable(Bind::Rasterizer::Resolve(gfx, false));
}

Step& StepBuilder::GetStep()
{
	return step;
}
//  -------