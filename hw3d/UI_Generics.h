#pragma once

// external dependencies for the UI module

#include "Drawable.h"
#include "TestPlane.h"
#include "TestCube.h"
#include "BlurOutlineRenderGraph.h"
#include "Channels.h"
#include "ChiliMath.h"
#include "ChiliUtil.h"
#include "imgui/imgui.h"

#include <map>
#include <unordered_map>

// enums
enum class mouseEvents
{
	leftClick,
	rightClick,
	onHover
};

// data structs for ui objects

struct ImageData
{
	std::string filePath = "";
	std::string textImage = "";
};

struct RelativePosition
{
	float x;
	float y;
	float z;
};

struct Size
{
	float size;
	float scaleX;
	float scaleY;
};

struct ComponentData
{
	RelativePosition relPos;
	Size size;
	ImageData imgData;
};

struct ElementData
{
	RelativePosition relPos;
	Size size;
	ImageData imgData;
	std::vector<ComponentData> list_ComponentsData;
	unsigned int amountOfComponents;
	bool hasBackground;
};

struct UIData
{
	Graphics& gfx;
	Rgph::BlurOutlineRenderGraph& rgRef;
	std::vector<ElementData> list_ElementsData;
	unsigned int amountOfElements;
};