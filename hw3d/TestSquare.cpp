#include "TestSquare.h"
#include "Square.h"
#include "BindableCommon.h"
#include "imgui/imgui.h"
#include "Channels.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"

TestSquare::TestSquare(Graphics& gfx, float size, float translationX, float translationY):
	pos(translationX, translationY)
{
	using namespace Bind;
	namespace dx = DirectX;

	auto model = Square::Make2D();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	{
		Technique solid{ Chan::main };
		Step only("lambertian");

		auto pvs = VertexShader::Resolve(gfx, "Solid2D_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));
		struct VSTranslation
		{
			dx::XMFLOAT2 translation;
			float padding1, padding2;
		} translationConst;
		translationConst.translation = { translationX, translationY };
		only.AddBindable(VertexConstantBuffer<VSTranslation>::Resolve(gfx, translationConst, 1u));

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

TestSquare::TestSquare(Graphics& gfx, float size, float translationX, float translationY, std::string texture):
	pos(translationX, translationY)
{
	using namespace Bind;
	namespace dx = DirectX;

	auto model = Square::Make2DTextured();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$square2D." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		Technique solid{ Chan::main };
		Step only{ "lambertian" };

		auto tex = Texture::Resolve(gfx, texture);
		bool hasAlpha = tex->HasAlpha();
		only.AddBindable(tex);
		only.AddBindable(Sampler::Resolve(gfx));


		auto pvs = VertexShader::Resolve(gfx, "Solid2D_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));
		struct VSTranslation
		{
			dx::XMFLOAT2 translation;
			float padding1, padding2;
		} translationConst;
		translationConst.translation = { translationX, translationY };
		only.AddBindable(VertexConstantBuffer<VSTranslation>::Resolve(gfx, translationConst, 1u));

		only.AddBindable(PixelShader::Resolve(gfx, "Textured2D_PS.cso"));

		struct PSposAdjustment
		{
			dx::XMFLOAT2 translation;
			bool hasAlpha;
			float padding;
		} texelPosAdjustment;
		texelPosAdjustment.translation = { translationX, translationY };
		texelPosAdjustment.hasAlpha = hasAlpha;
		only.AddBindable(PixelConstantBuffer<PSposAdjustment>::Resolve(gfx, texelPosAdjustment, 1u));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, hasAlpha));

		solid.AddStep(std::move(only));
		AddTechnique(std::move(solid));
	}
}

TestSquare::~TestSquare()
{
}

void TestSquare::Set2DPos(DirectX::XMFLOAT2 pos) noexcept
{
	this->pos = pos;
}

void TestSquare::AdjustToCamData(DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 pos) noexcept
{
	// to_rad(90) - 
	inWorldPos.x = pos.x + sin(rot.z) * TestSquare::offset;
	inWorldPos.y = pos.y - sin(rot.y) * TestSquare::offset;
	inWorldPos.z = pos.z + cos(rot.z) * TestSquare::offset * cos(rot.y);
	roll = -rot.y;
	pitch = rot.z + to_rad(180);
	yaw = 0.0f;
}

DirectX::XMMATRIX TestSquare::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) *
		DirectX::XMMatrixTranslation(inWorldPos.x, inWorldPos.y, inWorldPos.z);
}

void TestSquare::SpawnControlWindow(Graphics& gfx) noexcept
{
	if (ImGui::Begin("Square"))
	{
		ImGui::Text("2D Position");
		ImGui::SliderFloat("X", &pos.x, -5.0f, 5.0f, "%.1f");
		ImGui::SliderFloat("Y", &pos.y, -5.0f, 5.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
	}
	ImGui::End();
}

