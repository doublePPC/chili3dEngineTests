#include "TestPlane.h"
#include "Plane.h"
#include "Square.h"
#include "BindableCommon.h"
#include "imgui/imgui.h"
#include "Channels.h"
#include "TransformCbufDoubleboi.h"
#include "ConstantBuffersEx.h"

TestPlane::TestPlane(Graphics& gfx, float size, std::string texture)
{
	// constructor useful for UI widgets, uses solid shaders
	using namespace Bind;
	namespace dx = DirectX;

	//auto model = Plane::Make();
	auto model = Square::MakeTextured();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	//const auto geometryTag = "$plane." + std::to_string(size);
	const auto geometryTag = "$square." + std::to_string(size);
	pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
	pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
	pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	{
		Technique Solid{ Chan::main };
		Step only{ "lambertian" };

		only.AddBindable(Texture::Resolve(gfx, texture));
		only.AddBindable(Sampler::Resolve(gfx));

		auto pvs = VertexShader::Resolve(gfx, "ShadowTest_VS.cso");
		only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
		only.AddBindable(std::move(pvs));

		only.AddBindable(PixelShader::Resolve(gfx, "ShadowTest_PS.cso"));

		Dcb::RawLayout lay;
		lay.Add<Dcb::Float3>("specularColor");
		lay.Add<Dcb::Float>("specularWeight");
		lay.Add<Dcb::Float>("specularGloss");
		auto buf = Dcb::Buffer(std::move(lay));
		buf["specularColor"] = dx::XMFLOAT3{ 1.0f,1.0f,1.0f };
		buf["specularWeight"] = 0.1f;
		buf["specularGloss"] = 20.0f;
		only.AddBindable(std::make_shared<Bind::CachingPixelConstantBufferEx>(gfx, buf, 1u));

		only.AddBindable(std::make_shared<TransformCbuf>(gfx));

		only.AddBindable(Rasterizer::Resolve(gfx, false));

		Solid.AddStep(std::move(only));
		AddTechnique(std::move(Solid));

	}
}

TestPlane::TestPlane(Graphics& gfx, float size, std::string texture, std::string texNormalMap)
{
	/*using namespace Bind;
	namespace dx = DirectX;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(size, size, 1.0f));
	const auto geometryTag = "$plane." + std::to_string(size);
	AddBind(VertexBuffer::Resolve(gfx, geometryTag, model.vertices));
	AddBind(IndexBuffer::Resolve(gfx, geometryTag, model.indices));

	AddBind(Texture::Resolve(gfx, "Images\\" + texture));
	AddBind(Texture::Resolve(gfx, "Images\\" + texNormalMap, 2u));

	auto pvs = VertexShader::Resolve(gfx, "PhongVS.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(PixelShader::Resolve(gfx, "PhongPSNormalMapObject.cso"));

	AddBind(PixelConstantBuffer<PSMaterialConstant>::Resolve(gfx, pmc, 1u));

	AddBind(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

	AddBind(Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_shared<TransformCbufDoubleboi>(gfx, *this, 0u, 2u));*/
}

TestPlane::TestPlane(Graphics& gfx, float baseSize, float rectFactor, std::string texture, std::string texNormalMap)
{
	/*using namespace Bind;
	namespace dx = DirectX;

	auto model = Plane::Make();
	model.Transform(dx::XMMatrixScaling(baseSize, baseSize * rectFactor, 1.0f));
	const auto geometryTag = "$plane." + std::to_string(baseSize);
	AddBind(VertexBuffer::Resolve(gfx, geometryTag, model.vertices));
	AddBind(IndexBuffer::Resolve(gfx, geometryTag, model.indices));

	AddBind(Texture::Resolve(gfx, "Images\\" + texture));
	AddBind(Texture::Resolve(gfx, "Images\\" + texNormalMap, 2u));

	auto pvs = VertexShader::Resolve(gfx, "PhongVS.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));

	AddBind(PixelShader::Resolve(gfx, "PhongPSNormalMapObject.cso"));

	AddBind(PixelConstantBuffer<PSMaterialConstant>::Resolve(gfx, pmc, 1u));

	AddBind(InputLayout::Resolve(gfx, model.vertices.GetLayout(), pvsbc));

	AddBind(Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_shared<TransformCbufDoubleboi>(gfx, *this, 0u, 2u));*/
}

void TestPlane::SetPos(DirectX::XMFLOAT3 pos) noexcept
{
	this->pos = pos;
}

void TestPlane::SetRotation(float roll, float pitch, float yaw) noexcept
{
	this->roll = roll;
	this->pitch = pitch;
	this->yaw = yaw;
}

DirectX::XMMATRIX TestPlane::GetTransformXM() const noexcept
{
	return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}

void TestPlane::SpawnControlWindow(Graphics& gfx) noexcept
{
	if (ImGui::Begin("Plane"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Y", &pos.y, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Z", &pos.z, -80.0f, 80.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		ImGui::Text("Shading");
		bool changed0 = ImGui::SliderFloat("Spec. Int.", &pmc.specularIntensity, 0.0f, 1.0f);
		bool changed1 = ImGui::SliderFloat("Spec. Power", &pmc.specularPower, 0.0f, 100.0f);
		bool checkState = pmc.normalMappingEnabled == TRUE;
		bool changed2 = ImGui::Checkbox("Enable Normal Map", &checkState);
		pmc.normalMappingEnabled = checkState ? TRUE : FALSE;
		if (changed0 || changed1 || changed2)
		{
			//QueryBindable<Bind::PixelConstantBuffer<PSMaterialConstant>>()->Update(gfx, pmc);
		}
	}
	ImGui::End();
}
