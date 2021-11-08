#include "UI_Square.h"
#include "Plane.h"
#include "Square.h"
#include "BindableCommon.h"
#include "imgui/imgui.h"
#include "Channels.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"
#include "Surface.h"

UISquare::UISquare(Graphics& gfx, Size size, std::shared_ptr<TechniqueBuilder> drawTechnique)
{
	using namespace Bind;
	namespace dx = DirectX;

	scaleX = size.scaleX;
	scaleY = size.scaleY;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(size.size, size.size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size.size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		for (int i = 0; i < drawTechnique->getStepsAmount(); i++)
		{
			auto pvs = VertexShader::Resolve(gfx, drawTechnique->GetVSname());
			drawTechnique->GetStep(i).AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
			drawTechnique->GetStep(i).AddBindable(std::move(pvs));

			drawTechnique->GetTechnique().AddStep(std::move(drawTechnique->GetStep(i)));
		}
		AddTechnique(std::move(drawTechnique->GetTechnique()));
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

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		Technique solid{ Chan::main };
		Step only("UIelementDraw");

		auto pvs = VertexShader::Resolve(gfx, "Solid2D_VS.cso");
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

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, false));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
}

UISquare::UISquare(Graphics& gfx, float size, float _scaleX, float _scaleY, std::string texture)
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

		only.AddBindable(PixelShader::Resolve(gfx, "Textured2D_PS.cso"));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, hasAlpha));

		solid.AddStep(std::move(only));
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
		struct PSColorConstant
		{
			dx::XMFLOAT3 color;
			float transparency;
		} colorConst;
		colorConst.color = {tint.x, tint.y, tint.z};
		colorConst.transparency = tint.w;
		only.AddBindable(PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst, 1u));

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

		only.AddBindable(PixelShader::Resolve(gfx, "TexturedwSolidBackground_PS.cso"));
		struct PSColorConstant
		{
			dx::XMFLOAT3 backgroundColor;
			float backgroundTransparency;
		} colorDataConst;
		colorDataConst.backgroundColor = { 0.0f, 255.0f, 0.0f };
		colorDataConst.backgroundTransparency = 0.1f;
		only.AddBindable(PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorDataConst, 1u));

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
		struct PSColorConstant
		{
			dx::XMFLOAT3 color;
			float transparency;
		} colorConst;
		colorConst.color = { tint.x, tint.y, tint.z };
		colorConst.transparency = tint.w;
		only.AddBindable(PixelConstantBuffer<PSColorConstant>::Resolve(gfx, colorConst, 1u));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, hasAlpha));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
}


