#pragma once

// external dependencies for the UI module

#include "TestPlane.h"
#include "TestSquare.h"
#include "TestCube.h"
#include "BlurOutlineRenderGraph.h"
#include "Channels.h"
#include "ChiliMath.h"
#include "ChiliUtil.h"
#include "imgui/imgui.h"

// generic functions for UI use

// transforms an unsigned int into a float between -1.0f and 1.0f
float UnIntToPercentScreenFloat(unsigned int value);

// enums
enum class mouseEvents
{
	leftClick,
	rightClick,
	onHover
};

// data structs for ui objects

struct RelativePosition
{
	float x;
	float y;
	float z;
};

struct PosAndSize
{
	RelativePosition relPos;
	float size;
	float scaleX;
	float scaleY;
};

struct ComponentData
{
	PosAndSize compData;
	std::string texturePath;
};

struct ElementData
{
	PosAndSize elemData;
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