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
#include "Surface.h"

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

enum class textAlignment
{
	left,
	right,
	center,
	justified
};

enum class lignSpace
{
	simple,
	half,
	doubled
};

enum class fragmentType
{
	word,
	spaceBlock,
	endlign,
	undefined
};
// ------


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

struct TxtFragment
{
	std::string text;
	Surface::Color tintEffect;
	fragmentType typeOfFragment;
};

struct Police
{
	unsigned int letterSize;
	textAlignment alignment;
	lignSpace interlign;
	Surface::Color baseColor;
	const std::string& font;
	bool ignoreSpaceAtStartOfLign;
};

struct TextLign
{
	std::vector<TxtFragment> content;
	unsigned int remainingWidth;
};

struct CharacterData
{
	bool isCharDrawable = false;
	int distFromDrawLine = 0;
};

struct FontData
{
	bool hasUpperCase;
	bool hasLowerCase;
	bool hasAccents;
	unsigned int lignHeight;
	unsigned int spaceWidth;
	unsigned int drawingLignPos;
};
// ------


// constants block
const std::string FONT_DEFAULT = "default";
const std::string FONT_FUNKY = "funky";
