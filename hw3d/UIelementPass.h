#pragma once
#include "RenderQueuePass.h"
#include "Job.h"
#include <vector>
#include "PixelShader.h"
#include "VertexShader.h"
#include "Stencil.h"
#include "Rasterizer.h"
#include "Blender.h"

class Graphics;

namespace Rgph
{
	class UIelementPass : public RenderQueuePass
	{
	public:
		UIelementPass(Graphics& gfx, std::string name)
			:
			RenderQueuePass(std::move(name))
		{
			using namespace Bind;
			RegisterSink(DirectBufferSink<Bind::RenderTarget>::Make("renderTarget", renderTarget));
			RegisterSink(DirectBufferSink<Bind::DepthStencil>::Make("depthStencil", depthStencil));
			RegisterSource(DirectBufferSource<Bind::RenderTarget>::Make("renderTarget", renderTarget));
			RegisterSource(DirectBufferSource<Bind::DepthStencil>::Make("depthStencil", depthStencil));
			//AddBind(VertexShader::Resolve(gfx, "Solid2D_VS.cso"));
			//AddBind(PixelShader::Resolve(gfx, "Solid_PS.cso"));
			AddBind(Stencil::Resolve(gfx, Stencil::Mode::DepthOff));
			//AddBind(Rasterizer::Resolve(gfx, false));
			//std::optional<float> factors = std::make_optional<float>(0.5f, 0.5f, 0.5f, 0.5f);
			AddBind(Blender::Resolve(gfx, true));
		}
	};
}