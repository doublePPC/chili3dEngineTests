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
		Step only{ "UIelementDraw" };

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

void TestSquare::LinkToCam()
{
	isLinkedToCam = true;
}

void TestSquare::Set2DPos(DirectX::XMFLOAT2 pos) noexcept
{
	this->pos = pos;
}

void TestSquare::AdjustToCamData(DirectX::XMFLOAT3 ui_rot, DirectX::XMFLOAT3 ui_pos, float camPitch, float camYaw) noexcept
{
	if (isLinkedToCam)
	{

		// pitch angle modifiers
		float hypothenuse = sin(camPitch) * this->pos.y;
		float pitchYmod = cos(camPitch) * this->pos.y;
		float pitchXmod = sin(camYaw) * hypothenuse;
		float pitchZmod = cos(camYaw) * hypothenuse;

		// yaw angle modifiers
		float xFactor = this->pos.x * cos(camYaw);
		float zFactor = this->pos.x * sin(camYaw);

		inWorldPos.x = ui_pos.x + xFactor + pitchXmod;
		inWorldPos.y = ui_pos.y + pitchYmod;
		inWorldPos.z = ui_pos.z - zFactor + pitchZmod;

		roll = ui_rot.x;
		pitch = ui_rot.y;
		yaw = ui_rot.z;

		this->xModYaw = xFactor;
		this->xModPitch = pitchXmod;
		this->zModYaw = zFactor;
		this->zModPitch = pitchZmod;
	}	
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
		if (isLinkedToCam)
		{
			std::string text;
			ImGui::Text("2D Position");
			text = "X : " + std::to_string(inWorldPos.x);
			ImGui::Text(text.c_str());
			ImGui::SliderFloat("X offset", &pos.x, -5.0f, 5.0f, "%.1f");
			text = "Y : " + std::to_string(inWorldPos.y);
			ImGui::Text(text.c_str());
			ImGui::SliderFloat("Y offset", &pos.y, -5.0f, 5.0f, "%.1f");
			text = "Z : " + std::to_string(inWorldPos.z);
			ImGui::Text(text.c_str());
			ImGui::Text("Orientation");
			text = "Roll: " + std::to_string(roll);
			ImGui::Text(text.c_str());
			text = "Pitch : " + std::to_string(pitch);
			ImGui::Text(text.c_str());
			text = "Yaw : " + std::to_string(yaw);
			ImGui::Text(text.c_str());
		}
		else
		{
			ImGui::Text("2D Position");
			ImGui::SliderFloat("X", &pos.x, -5.0f, 5.0f, "%.1f");
			ImGui::SliderFloat("Y", &pos.y, -5.0f, 5.0f, "%.1f");
			ImGui::Text("Orientation");
			ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
			ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
			ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		}
	}
	ImGui::End();
}

float TestSquare::AdjustPitchAngle(float basePitch)
{
	float newPitch;
	if (this->pos.y != 0.0f)
	{
		newPitch = atan(this->pos.y / offset) + basePitch;
	}
	else
	{
		newPitch = basePitch;
	}
	return newPitch;
}

float TestSquare::AdjustYawAngle(float baseYaw)
{
	float newYaw;
	if (this->pos.x != 0.0f)
	{
		newYaw = atan(this->pos.x / offset) + baseYaw;
	}
	else
	{
		newYaw = baseYaw;
	}
	return newYaw;
}

float TestSquare::AdjustPitchDistance(float distance)
{
	float newDistance;
	newDistance = distance * distance + this->pos.y * this->pos.y;
	newDistance = sqrt(newDistance);
	return newDistance;
}

float TestSquare::AdjustYawDistance(float distance)
{
	float newDistance;
	newDistance = distance * distance + this->pos.x * this->pos.x;
	newDistance = sqrt(newDistance);
	return newDistance;
}

