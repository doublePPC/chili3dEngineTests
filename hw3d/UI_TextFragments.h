#pragma once
#include "UI_Generics.h"
#include "UI_Maths.h"
#include "UI_Utils.h"

class UI_TextFragments
{
public:
	UI_TextFragments();
	UI_TextFragments(unsigned int projectedFragmentsAmount);
	UI_TextFragments(const std::string& text, const police& police);
	~UI_TextFragments();

	void addFragment(std::string& txt, Surface::Color tintEffect);

	std::shared_ptr<Surface> acquireSurfaceFromFragments();
	textLign acquireSingleLign(unsigned int lignWidth, const police& police);
	void acquireLigns(unsigned int lignWidth, const police& police, std::vector<textLign>& contentToFill);
private:
	static fragmentType char2FragmentType(unsigned char value);
	static bool charMatchesFragmentType(unsigned char value, fragmentType type);
	static bool nextCharBeginsAnEffect(unsigned char value, const std::string& text, unsigned int pos);
	static unsigned char biAlpha2Hexadecimal(unsigned char first, unsigned char second);
	static unsigned int readEffect(const std::string& text, unsigned int pos, Surface::Color& color, const Surface::Color& baseColor);
private:
	std::vector<txtFragment> fragments;
};