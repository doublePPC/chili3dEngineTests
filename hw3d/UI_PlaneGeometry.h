#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"
#include "IndexedTriangleList.h"
#include <DirectXMath.h>

class UI_Plane
{
private:
	static void BuildIndices(std::vector<unsigned short>& indicesVect, int div_x, int div_y, const int nVert_x)
	{
		const auto vxy2i = [nVert_x](size_t x, size_t y)
		{
			return (unsigned short)(y * nVert_x + x);
		};
		for (size_t y = 0; y < div_y; y++)
		{
			for (size_t x = 0; x < div_x; x++)
			{
				const std::array<unsigned short, 4> indexArray =
				{ vxy2i(x,y),vxy2i(x + 1,y),vxy2i(x,y + 1),vxy2i(x + 1,y + 1) };
				indicesVect.push_back(indexArray[0]);
				indicesVect.push_back(indexArray[2]);
				indicesVect.push_back(indexArray[1]);
				indicesVect.push_back(indexArray[1]);
				indicesVect.push_back(indexArray[2]);
				indicesVect.push_back(indexArray[3]);
			}
		}
	};

public:
	static IndexedTriangleList MakeTesselated(Dvtx::VertexLayout layout, int divisions_x, int divisions_y)
	{
		namespace dx = DirectX;
		assert(divisions_x >= 1);
		assert(divisions_y >= 1);

		float width = 0.5f;
		float height = 0.5f;
		const int nVertices_x = divisions_x + 1;
		const int nVertices_y = divisions_y + 1;
		Dvtx::VertexBuffer vb{ std::move(layout) };

		{
			const float side_x = width / 2.0f;
			const float side_y = height / 2.0f;
			const float divisionSize_x = width / float(divisions_x);
			const float divisionSize_y = height / float(divisions_y);

			for (int y = 0, i = 0; y < nVertices_y; y++)
			{
				const float y_pos = float(y) * divisionSize_y - side_y;
				for (int x = 0; x < nVertices_x; x++, i++)
				{
					const float x_pos = float(x) * divisionSize_x - side_x;
					vb.EmplaceBack(
						dx::XMFLOAT3{ x_pos,y_pos,0.0f }
					);
				}
			}
		}
	
		std::vector<unsigned short> indices;
		indices.reserve(sq(divisions_x * divisions_y) * 6);
		BuildIndices(indices, divisions_x, divisions_y, nVertices_x);

		return{ std::move(vb),std::move(indices) };
	}

	static IndexedTriangleList MakeTesselatedTextured(Dvtx::VertexLayout layout, int divisions_x, int divisions_y)
	{
		namespace dx = DirectX;
		assert(divisions_x >= 1);
		assert(divisions_y >= 1);

		float width = 0.5f;
		float height = 0.5f;
		const int nVertices_x = divisions_x + 1;
		const int nVertices_y = divisions_y + 1;
		Dvtx::VertexBuffer vb{ std::move(layout) };

		{
			const float side_x = width / 2.0f;
			const float side_y = height / 2.0f;
			const float divisionSize_x = width / float(divisions_x);
			const float divisionSize_y = height / float(divisions_y);
			const float divisionSize_x_tc = 1.0f / float(divisions_x);
			const float divisionSize_y_tc = 1.0f / float(divisions_y);

			for (int y = 0, i = 0; y < nVertices_y; y++)
			{
				const float y_pos = float(y) * divisionSize_y - side_y;
				const float y_pos_tc = 1.0f - float(y) * divisionSize_y_tc;
				for (int x = 0; x < nVertices_x; x++, i++)
				{
					const float x_pos = float(x) * divisionSize_x - side_x;
					const float x_pos_tc = float(x) * divisionSize_x_tc;
					vb.EmplaceBack(
						dx::XMFLOAT3{ x_pos,y_pos,0.0f },
						dx::XMFLOAT2{ x_pos_tc,y_pos_tc }
					);
				}
			}
		}

		std::vector<unsigned short> indices;
		indices.reserve(sq(divisions_x * divisions_y) * 6);
		BuildIndices(indices, divisions_x, divisions_y, nVertices_x);

		return{ std::move(vb),std::move(indices) };
	};

	static IndexedTriangleList MakeTesselatedColored(Dvtx::VertexLayout layout, int divisions_x, int divisions_y, DirectX::XMFLOAT3 color)
	{
		namespace dx = DirectX;
		assert(divisions_x >= 1);
		assert(divisions_y >= 1);

		float width = 0.5f;
		float height = 0.5f;
		const int nVertices_x = divisions_x + 1;
		const int nVertices_y = divisions_y + 1;
		Dvtx::VertexBuffer vb{ std::move(layout) };

		{
			const float side_x = width / 2.0f;
			const float side_y = height / 2.0f;
			const float divisionSize_x = width / float(divisions_x);
			const float divisionSize_y = height / float(divisions_y);

			for (int y = 0, i = 0; y < nVertices_y; y++)
			{
				const float y_pos = float(y) * divisionSize_y - side_y;
				for (int x = 0; x < nVertices_x; x++, i++)
				{
					const float x_pos = float(x) * divisionSize_x - side_x;
					vb.EmplaceBack(
						dx::XMFLOAT3{ x_pos,y_pos,0.0f },
						color
					);
				}
			}
		}

		std::vector<unsigned short> indices;
		indices.reserve(sq(divisions_x * divisions_y) * 6);
		BuildIndices(indices, divisions_x, divisions_y, nVertices_x);

		return{ std::move(vb),std::move(indices) };
	};

	static IndexedTriangleList MakeColored(DirectX::XMFLOAT3 color)
	{
		using Dvtx::VertexLayout;
		VertexLayout vl;
		vl.Append(VertexLayout::Position3D);
		vl.Append(VertexLayout::Float3Color);

		return MakeTesselatedColored(vl, 1, 1, color);
	};

	static IndexedTriangleList MakeTextured()
	{
		using Dvtx::VertexLayout;
		VertexLayout vl;
		vl.Append(VertexLayout::Position3D);
		vl.Append(VertexLayout::Texture2D);

		return MakeTesselatedTextured(vl, 1, 1);
	}

	static std::pair<IndexedTriangleList, std::string> Make()
	{
		using Dvtx::VertexLayout;
		VertexLayout vl;
		vl.Append(VertexLayout::Position3D);

		return std::make_pair<IndexedTriangleList, std::string>(MakeTesselated(vl, 1, 1), "$square2D.");
	}
};