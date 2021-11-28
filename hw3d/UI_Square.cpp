#include "UI_Square.h"
#include "Plane.h"
#include "Square.h"
#include "BindableCommon.h"
#include "imgui/imgui.h"
#include "Channels.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"
#include "Surface.h"
#include "UI_PlaneGeometry.h"
#include "UI_TechniqueAssembler.h"

UISquare::UISquare(Graphics& gfx, float size, float _scaleX, float _scaleY, std::shared_ptr<TechniqueBuilder> technique)
{
	scaleX = _scaleX;
	scaleY = _scaleY;

	using namespace Bind;
	namespace dx = DirectX;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	{
		std::unique_ptr<Technique> solid;
		if (technique->GetTechName() == "")
		{
			solid = std::make_unique<Technique>(Chan::main);
		}
		else
		{
			solid = std::make_unique<Technique>(technique->GetTechName(), Chan::main);
		}
		
		for (int i = 0; i < technique->GetStepsAmount(); i++)
		{
			Step step(technique->GetStepInfo(i)->GetStepName());
			TechniqueAssembler::AssembleStep(gfx, step, model, technique->GetStepInfo(i), technique->GetTechType());
			solid->AddStep(std::move(step));
		}
		AddTechnique(std::move(*solid));
	}
}

UISquare::UISquare(Graphics& gfx, float size, float _scaleX, float _scaleY, std::vector<std::shared_ptr<TechniqueBuilder>>& techniques)
{
	scaleX = _scaleX;
	scaleY = _scaleY;

	using namespace Bind;
	namespace dx = DirectX;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (int i = 0; i < techniques.size(); i++)
	{
		std::unique_ptr<Technique> solid;
		if (techniques[i]->GetTechName() == "")
		{
			solid = std::make_unique<Technique>(Chan::main);
		}
		else
		{
			solid = std::make_unique<Technique>(techniques[i]->GetTechName(), Chan::main);
		}

		for (int j = 0; j < techniques[i]->GetStepsAmount(); j++)
		{
			Step step(techniques[i]->GetStepInfo(j)->GetStepName());
			TechniqueAssembler::AssembleStep(gfx, step, model, techniques[i]->GetStepInfo(j), techniques[i]->GetTechType());
			solid->AddStep(std::move(step));
		}
		AddTechnique(std::move(*solid));
	}
}

UISquare::UISquare(Graphics& gfx, float size)
{
	scaleX = 1.0f;
	scaleY = 1.0f;

	using namespace Bind;
	namespace dx = DirectX;

	auto model = Square::Make();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	{
		Technique solid{ Chan::main };
		Step only("UIelementDraw");

		auto pvs = VertexShader::Resolve(gfx, "Solid_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));

		only.AddBindable(PixelShader::Resolve(gfx, "Solid_PS.cso"));

		struct PSColorConstant
		{
			dx::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
			float padding;
		} colorConst;
		only.AddBindable(PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst, 1u));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, false));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
}

UISquare::UISquare(Graphics& gfx, float size, float _scaleX, float _scaleY, DirectX::XMFLOAT3 colorValue)
{
	scaleX = _scaleX;
	scaleY = _scaleY;

	using namespace Bind;
	namespace dx = DirectX;

	//auto model = Plane::Make();
	auto model = UI_Plane::MakeColored({ colorValue.x, colorValue.y, colorValue.z});
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	auto tcb = std::make_shared<TransformCbuf>(gfx);
	// UI Draw technique
	{
		Technique solid{ Chan::main };
		Step only("UIelementDraw");

		auto pvs = VertexShader::Resolve(gfx, "Solid_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));

		only.AddBindable(PixelShader::Resolve(gfx, "Solid_PS.cso"));

		struct PSColorConstant
		{
			dx::XMFLOAT3 color;
			float transparency = 0.5f;
		} colorConst;
		colorConst.color = colorValue;
		only.AddBindable(PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst, 1u));

		only.AddBindable(tcb);

		only.AddBindable(Rasterizer::Resolve(gfx, false));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
	// Outline technique
	{
		Technique outline("Outline", Chan::main);
		{
			Step mask("outlineMask");

			// TODO: better sub-layout generation tech for future consideration maybe
			mask.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *VertexShader::Resolve(gfx, "Solid_VS.cso")));

			mask.AddBindable(std::move(tcb));

			// TODO: might need to specify rasterizer when doubled-sided models start being used

			outline.AddStep(std::move(mask));
		}
		{
			Step draw("outlineDraw");

			Dcb::RawLayout lay;
			lay.Add<Dcb::Float4>("color");
			auto buf = Dcb::Buffer(std::move(lay));
			buf["color"] = DirectX::XMFLOAT4{ 1.0f,0.4f,0.4f,1.0f };
			draw.AddBindable(std::make_shared<Bind::CachingPixelConstantBufferEx>(gfx, buf, 1u));

			// TODO: better sub-layout generation tech for future consideration maybe
			draw.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *VertexShader::Resolve(gfx, "Solid_VS.cso")));

			draw.AddBindable(std::make_shared<TransformCbuf>(gfx));

			// TODO: might need to specify rasterizer when doubled-sided models start being used

			outline.AddStep(std::move(draw));
		}
		AddTechnique(std::move(outline));
	}
}

UISquare::UISquare(Graphics& gfx, float size, float _scaleX, float _scaleY, std::string texture)
{
	scaleX = _scaleX;
	scaleY = _scaleY;

	using namespace Bind;
	namespace dx = DirectX;

	//auto model = Plane::Make();
	auto model = UI_Plane::MakeTextured();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		Technique solid{ Chan::main };
		{
			Step only{ "UIelementDraw" };

			auto tex = Texture::Resolve(gfx, texture);
			bool hasAlpha = tex->HasAlpha();
			only.AddBindable(tex);
			only.AddBindable(Sampler::Resolve(gfx));

			auto pvs = VertexShader::Resolve(gfx, "Solid2D_VS.cso");
			only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
			only.AddBindable(std::move(pvs));

			only.AddBindable(PixelShader::Resolve(gfx, "Textured2D_PS.cso"));

			only.AddBindable(std::make_shared<TransformCbuf>(gfx));

			only.AddBindable(Rasterizer::Resolve(gfx, hasAlpha));

			solid.AddStep(std::move(only));
		}
		AddTechnique(std::move(solid));
	}
}

UISquare::UISquare(Graphics& gfx, float size, float _scaleX, float _scaleY, std::string texture, DirectX::XMFLOAT4 tint)
{
	scaleX = _scaleX;
	scaleY = _scaleY;

	using namespace Bind;
	namespace dx = DirectX;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		Technique solid{ Chan::main };
		Step only{ "UIelementDraw" };

		auto tex = Texture::Resolve(gfx, texture);
		bool hasAlpha = tex->HasAlpha();
		only.AddBindable(tex);
		only.AddBindable(Sampler::Resolve(gfx));


		auto pvs = VertexShader::Resolve(gfx, "Solid2D_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));

		only.AddBindable(PixelShader::Resolve(gfx, "TintedTextured2D_PS.cso"));
		tintTechCBuf colorConst;
		colorConst.color = {tint.x, tint.y, tint.z, tint.w};
		colorConst.techCode = 2;
		colorConst.globalTransparency = 1.0f;
		only.AddBindable(PixelConstantBuffer<tintTechCBuf>::Resolve(gfx, colorConst, 1u));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, hasAlpha));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
}

UISquare::UISquare(Graphics& gfx, float size, float _scaleX, float _scaleY, std::shared_ptr<Surface> texture)
{
	scaleX = _scaleX;
	scaleY = _scaleY;

	using namespace Bind;
	namespace dx = DirectX;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		Technique solid{ Chan::main };
		Step only{ "UIelementDraw" };

		auto tex = std::make_shared<Texture>(gfx, texture);
		bool hasAlpha = tex->HasAlpha();
		only.AddBindable(tex);
		only.AddBindable(Sampler::Resolve(gfx));

		auto pvs = VertexShader::Resolve(gfx, "Solid2D_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));

		only.AddBindable(PixelShader::Resolve(gfx, "WhiteFadingTextured2D_PS.cso"));
		fadingTechCBuf colorDataConst;
		colorDataConst.backgroundColor = { 0.0f, 255.0f, 0.0f };
		colorDataConst.globalTransparency = 1.0f;
		only.AddBindable(PixelConstantBuffer<fadingTechCBuf>::Resolve(gfx, colorDataConst, 1u));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, hasAlpha));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
}

UISquare::~UISquare()
{
}

void UISquare::SetPos(DirectX::XMFLOAT3 ui_facing, DirectX::XMFLOAT3 elem_pos) noexcept
{
	inWorldPos = elem_pos;
	roll = ui_facing.x;
	pitch = ui_facing.y;
	yaw = ui_facing.z;	
}

DirectX::XMMATRIX UISquare::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixScaling(scaleX, scaleY, 1.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) *
		DirectX::XMMatrixTranslation(inWorldPos.x, inWorldPos.y, inWorldPos.z);
}

void UISquare::SpawnControlWindow(Graphics& gfx) noexcept
{
	if (ImGui::Begin("Square"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &inWorldPos.x, -5.0f, 5.0f, "%.1f");
		ImGui::SliderFloat("Y", &inWorldPos.y, -5.0f, 5.0f, "%.1f");
		ImGui::SliderFloat("Z", &inWorldPos.z, -5.0f, 5.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		ImGui::Text("Scale");
		ImGui::SliderFloat("Horizontal", &scaleX, 0.1f, 2.0f, "%.1f");
		ImGui::SliderFloat("Vertical", &scaleY, 0.1f, 2.0f, "%.1f");
	}
	ImGui::End();
}

void UISquare::disableDefaultTechnique()
{
	if (techniques.size() > 0)
	{
		if (techniques[0].IsActive())
		{
			techniques[0].SetActiveState(false);
		}
	}
}

void UISquare::AddTintTechnique(Graphics& gfx, DirectX::XMFLOAT4 tint)
{
	using namespace Bind;
	namespace dx = DirectX;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(0.5f, 0.5f, 1.0f));
	{
		Technique solid{ Chan::main };
		Step only{ "UIelementDraw" };

		auto tex = Texture::Resolve(gfx, "Images\\stripes.png");
		bool hasAlpha = tex->HasAlpha();
		only.AddBindable(tex);
		only.AddBindable(Sampler::Resolve(gfx));


		auto pvs = VertexShader::Resolve(gfx, "Solid2D_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));

		only.AddBindable(PixelShader::Resolve(gfx, "TintedTextured2D_PS.cso"));
		tintTechCBuf colorConst;
		colorConst.color = { tint.x, tint.y, tint.z, tint.w };
		colorConst.techCode = 2;
		colorConst.globalTransparency = 1.0f;
		only.AddBindable(PixelConstantBuffer<tintTechCBuf>::Resolve(gfx, colorConst, 1u));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, hasAlpha));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
}


