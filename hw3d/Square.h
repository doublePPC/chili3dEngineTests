#pragma once

#include <optional>
#include "Vertex.h"
#include "IndexedTriangleList.h"
#include <DirectXMath.h>
#include "ChiliMath.h"
#include <array>
#include <optional>

class Square
{
public:
	static IndexedTriangleList Make2D(std::optional<Dvtx::VertexLayout> layout = {})
	{
		using namespace Dvtx;
		using Type = Dvtx::VertexLayout::ElementType;

		if (!layout)
		{
			layout = Dvtx::VertexLayout{};
			layout->Append(Type::Position2D);
			//layout->Append(Type::Position2D);
		}

		constexpr float side = 1.0f / 2.0f;

		VertexBuffer vertices(std::move(*layout), 4u);
		vertices[0].Attr<Type::Position2D>() = { -side,-side };
		vertices[1].Attr<Type::Position2D>() = { side,-side };
		vertices[2].Attr<Type::Position2D>() = { -side,side };
		vertices[3].Attr<Type::Position2D>() = { side,side };
		return{
			std::move(vertices),{
				0,2,1, 2,3,1}
		};
	}

	static IndexedTriangleList Make(std::optional<Dvtx::VertexLayout> layout = {})
	{
		using namespace Dvtx;
		using Type = Dvtx::VertexLayout::ElementType;

		if (!layout)
		{
			layout = Dvtx::VertexLayout{};
			layout->Append(Type::Position3D);
		}

		constexpr float side = 1.0f / 2.0f;

		VertexBuffer vertices(std::move(*layout), 4u);
		/*vertices[0].Attr<Type::Position3D>() = { -side,-side,-side };
		vertices[1].Attr<Type::Position3D>() = { side,-side,-side };
		vertices[2].Attr<Type::Position3D>() = { -side,side,-side };
		vertices[3].Attr<Type::Position3D>() = { side,side,-side };*/
		vertices[0].Attr<Type::Position3D>() = { -side,-side,side };
		vertices[1].Attr<Type::Position3D>() = { side,-side,side };
		vertices[2].Attr<Type::Position3D>() = { -side,side,side };
		vertices[3].Attr<Type::Position3D>() = { side,side,side };
		//vertices[0].Attr<Type::Position2D>() = { -side, -side };

		/*return{
			std::move(vertices),{
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
			}
		};*/
		return{
			std::move(vertices),{
				0,2,1, 2,3,1}
		};
	}

	static IndexedTriangleList MakeTextured()
	{
		using namespace Dvtx;
		using Type = Dvtx::VertexLayout::ElementType;

		auto itl = Make(std::move(VertexLayout{}
			.Append(Type::Position3D)
			.Append(Type::Normal)
			.Append(Type::Texture2D)
		));

		itl.vertices[0].Attr<Type::Texture2D>() = { 0.0f,0.0f };
		itl.vertices[1].Attr<Type::Texture2D>() = { 1.0f,0.0f };
		itl.vertices[2].Attr<Type::Texture2D>() = { 0.0f,1.0f };
		itl.vertices[3].Attr<Type::Texture2D>() = { 1.0f,1.0f };
		/*itl.vertices[4].Attr<Type::Texture2D>() = { 0.0f,0.0f };
		itl.vertices[5].Attr<Type::Texture2D>() = { 1.0f,0.0f };
		itl.vertices[6].Attr<Type::Texture2D>() = { 0.0f,1.0f };
		itl.vertices[7].Attr<Type::Texture2D>() = { 1.0f,1.0f };
		itl.vertices[8].Attr<Type::Texture2D>() = { 0.0f,0.0f };
		itl.vertices[9].Attr<Type::Texture2D>() = { 1.0f,0.0f };
		itl.vertices[10].Attr<Type::Texture2D>() = { 0.0f,1.0f };
		itl.vertices[11].Attr<Type::Texture2D>() = { 1.0f,1.0f };
		itl.vertices[12].Attr<Type::Texture2D>() = { 0.0f,0.0f };
		itl.vertices[13].Attr<Type::Texture2D>() = { 1.0f,0.0f };
		itl.vertices[14].Attr<Type::Texture2D>() = { 0.0f,1.0f };
		itl.vertices[15].Attr<Type::Texture2D>() = { 1.0f,1.0f };
		itl.vertices[16].Attr<Type::Texture2D>() = { 0.0f,0.0f };
		itl.vertices[17].Attr<Type::Texture2D>() = { 1.0f,0.0f };
		itl.vertices[18].Attr<Type::Texture2D>() = { 0.0f,1.0f };
		itl.vertices[19].Attr<Type::Texture2D>() = { 1.0f,1.0f };
		itl.vertices[20].Attr<Type::Texture2D>() = { 0.0f,0.0f };
		itl.vertices[21].Attr<Type::Texture2D>() = { 1.0f,0.0f };
		itl.vertices[22].Attr<Type::Texture2D>() = { 0.0f,1.0f };
		itl.vertices[23].Attr<Type::Texture2D>() = { 1.0f,1.0f };*/

		return itl;
	}
};