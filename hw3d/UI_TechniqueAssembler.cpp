#include "UI_TechniqueAssembler.h"
#include "Plane.h"
#include "Square.h"
#include "BindableCommon.h"
#include "imgui/imgui.h"
#include "Channels.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"
#include "Surface.h"

void TechniqueAssembler::AssembleStep(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData, UI_DrawTech techType)
{
	switch (techType)
	{
	case(UI_DrawTech::baseColored):
	{
		TechniqueAssembler::AssembleBaseColored(gfx, step, modelInfo, stepData);
		break;
	}
	case(UI_DrawTech::baseFileTextured):
	{
		TechniqueAssembler::AssembleBaseFileTextured(gfx, step, modelInfo, stepData);
		break;
	}
	case(UI_DrawTech::baseSurfaceTextured):
	{
		TechniqueAssembler::AssembleBaseSurfaceTextured(gfx, step, modelInfo, stepData);
		break;
	}
	case(UI_DrawTech::outline):
	{
		if (stepData->GetStepName() == "outlineMask")
		{
			TechniqueAssembler::AssembleOutlineMask(gfx, step, modelInfo, stepData);
		}
		else
		{
			TechniqueAssembler::AssembleOutlineDraw(gfx, step, modelInfo, stepData);
		}
		break;
	}
	}
}

void TechniqueAssembler::AssembleBaseColored(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData)
{
	auto pvs = Bind::VertexShader::Resolve(gfx, stepData->GetPSName());
	step.AddBindable(Bind::InputLayout::Resolve(gfx, modelInfo.vertices.GetLayout(), *pvs));
	step.AddBindable(std::move(pvs));

	step.AddBindable(Bind::PixelShader::Resolve(gfx, stepData->GetPSName()));

	struct PSColorConstant
	{
		DirectX::XMFLOAT3 color;
		float transparency;
	} colorConst;
	DirectX::XMFLOAT4 colorValue = stepData->GetEffectColor();
	colorConst.color = { colorValue.x, colorValue.y, colorValue.z };
	colorConst.transparency = colorValue.w;
	step.AddBindable(Bind::PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst, 1u));

	step.AddBindable(std::make_shared<Bind::TransformCbuf>(gfx));

	step.AddBindable(Bind::Rasterizer::Resolve(gfx, false));
}

void TechniqueAssembler::AssembleBaseFileTextured(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData)
{
	auto tex = Bind::Texture::Resolve(gfx, stepData->GetTextureName());
	//auto tex = Bind::Texture::Resolve(gfx, "Images\\kappa50.png");
	bool hasAlpha = tex->HasAlpha();
	step.AddBindable(tex);
	step.AddBindable(Bind::Sampler::Resolve(gfx));

	auto pvs = Bind::VertexShader::Resolve(gfx, stepData->GetVSName());
	step.AddBindable(Bind::InputLayout::Resolve(gfx, modelInfo.vertices.GetLayout(), *pvs));
	step.AddBindable(std::move(pvs));

	step.AddBindable(Bind::PixelShader::Resolve(gfx, stepData->GetPSName()));

	step.AddBindable(std::make_shared<Bind::TransformCbuf>(gfx));

	step.AddBindable(Bind::Rasterizer::Resolve(gfx, hasAlpha));
}

void TechniqueAssembler::AssembleBaseSurfaceTextured(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData)
{
	auto tex = std::make_shared<Bind::Texture>(gfx, stepData->GetSurfaceTexture());
	bool hasAlpha = tex->HasAlpha();
	step.AddBindable(tex);
	step.AddBindable(Bind::Sampler::Resolve(gfx));

	auto pvs = Bind::VertexShader::Resolve(gfx, stepData->GetVSName());
	step.AddBindable(Bind::InputLayout::Resolve(gfx, modelInfo.vertices.GetLayout(), *pvs));
	step.AddBindable(std::move(pvs));

	step.AddBindable(Bind::PixelShader::Resolve(gfx, stepData->GetPSName()));
	fadingTechCBuf colorDataConst;
	colorDataConst.backgroundColor = { 0.0f, 255.0f, 0.0f };
	colorDataConst.globalTransparency = 1.0f;
	step.AddBindable(Bind::PixelConstantBuffer<fadingTechCBuf>::Resolve(gfx, colorDataConst, 1u));

	step.AddBindable(std::make_shared<Bind::TransformCbuf>(gfx));

	step.AddBindable(Bind::Rasterizer::Resolve(gfx, hasAlpha));
}

void TechniqueAssembler::AssembleOutlineMask(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData)
{
}

void TechniqueAssembler::AssembleOutlineDraw(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData)
{
}

void TechniqueAssembler::LoadKappaFailure(Graphics& gfx, Step& step, IndexedTriangleList& modelInfo, std::shared_ptr <StepBuilder> stepData)
{
}
