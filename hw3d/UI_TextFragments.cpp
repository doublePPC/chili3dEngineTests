#include "UI_TextFragments.h"

UI_TextFragments::UI_TextFragments()
{
}

UI_TextFragments::UI_TextFragments(unsigned int projectedFragmentsAmount)
{
	fragments.reserve(projectedFragmentsAmount);
}

UI_TextFragments::~UI_TextFragments()
{
}

void UI_TextFragments::addFragment(const std::string& txt, Surface::Color tintEffect)
{
	txtFragment newFragment;
	newFragment.text = txt;
	newFragment.tintEffect = tintEffect;
	fragments.push_back(newFragment);
}

std::shared_ptr<Surface> UI_TextFragments::acquireSurfaceFromFragments()
{
	unsigned int lignHeight = UI_Utils::getFontBaseTextHeight();
	unsigned int totalWidth = 0;
	for (unsigned int i = 0; i < fragments.size(); i++)
	{
		totalWidth += UI_Utils::getTextPixelWidth(fragments[i].text);
	}
	surfaceCursor cursor = { totalWidth, lignHeight, 0, 0, 0, 0 };
	std::shared_ptr<Surface> surface = std::make_shared<Surface>(totalWidth, lignHeight);
	surface->Clear({ 0, 255, 255, 255 });
	for (unsigned int i = 0; i < fragments.size(); i++)
	{
		UI_Utils::drawTextOnSurface(fragments[i], surface, cursor);
	}
	return surface;
}
