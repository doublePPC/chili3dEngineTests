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
#include <array>

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