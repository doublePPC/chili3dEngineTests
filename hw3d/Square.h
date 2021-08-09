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
	static IndexedTriangleList Make2DTextured(std::optional<Dvtx::VertexLayout> layout = {})
	{
		using namespace Dvtx;
		using Type = Dvtx::VertexLayout::ElementType;

		auto itl = Make2D(std::move(VertexLayout{}
			.Append(Type::Position2D)
			.Append(Type::Texture2D)
		));

		itl.vertices[0].Attr<Type::Texture2D>() = { 0.0f,0.0f };
		itl.vertices[1].Attr<Type::Texture2D>() = { 1.0f,0.0f };
		itl.vertices[2].Attr<Type::Texture2D>() = { 0.0f,1.0f };
		itl.vertices[3].Attr<Type::Texture2D>() = { 1.0f,1.0f };

		return itl;
	}

	static IndexedTriangleList Make2D(std::optional<Dvtx::VertexLayout> layout = {})
	{
		using namespace Dvtx;
		using Type = Dvtx::VertexLayout::ElementType;

		if (!layout)
		{
			layout = Dvtx::VertexLayout{};
			layout->Append(Type::Position2D);
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

	static IndexedTriangleList Make2DRect(float width, float height, std::optional<Dvtx::VertexLayout> layout = {})
	{
		using namespace Dvtx;
		using Type = Dvtx::VertexLayout::ElementType;

		if (!layout)
		{
			layout = Dvtx::VertexLayout{};
			layout->Append(Type::Position2D);
		}

		VertexBuffer vertices(std::move(*layout), 4u);
		vertices[0].Attr<Type::Position2D>() = { -width / 2.0f, -height / 2.0f };
		vertices[1].Attr<Type::Position2D>() = { width / 2.0f, -height / 2.0f };
		vertices[2].Attr<Type::Position2D>() = { -width / 2.0f, height / 2.0f };
		vertices[3].Attr<Type::Position2D>() = { width / 2.0f, height / 2.0f };

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

		vertices[0].Attr<Type::Position3D>() = { -side,-side,side };
		vertices[1].Attr<Type::Position3D>() = { side,-side,side };
		vertices[2].Attr<Type::Position3D>() = { -side,side,side };
		vertices[3].Attr<Type::Position3D>() = { side,side,side };

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

		return itl;
	}
};