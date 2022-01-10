#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"

class UI_TextFragments
{
public:
	UI_TextFragments();
	UI_TextFragments(unsigned int projectedFragmentsAmount);
	~UI_TextFragments();

	void addFragment(std::string& txt, Surface::Color tintEffect);

	std::shared_ptr<Surface> acquireSurfaceFromFragments();
private:
	std::vector<txtFragment> fragments;
};