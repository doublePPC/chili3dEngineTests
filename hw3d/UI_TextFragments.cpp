#include "UI_TextFragments.h"

UI_TextFragments::UI_TextFragments()
{
}

UI_TextFragments::UI_TextFragments(unsigned int projectedFragmentsAmount)
{
	fragments.reserve(projectedFragmentsAmount);
}

UI_TextFragments::UI_TextFragments(const std::string& text, const Police& police)
{
	// task : fragment the text
	Surface::Color currentColor = police.baseColor;
	std::string nextFragmentTxt = "";
	fragmentType currentFragmentType = fragmentType::undefined;
	for (unsigned int i = 0; i < text.length(); i++)
	{
		if (UI_TextFragments::nextCharBeginsAnEffect(text.at(i), text, i))
		{
			if (nextFragmentTxt.length() > 0)
			{
				// close last fragment
				TxtFragment newFragment;
				newFragment.text = nextFragmentTxt;
				newFragment.tintEffect = currentColor;
				newFragment.typeOfFragment = currentFragmentType;
				fragments.push_back(newFragment);
				nextFragmentTxt = "";
			}
			unsigned int effectLength = UI_TextFragments::readEffect(text, i, currentColor, police.baseColor);
			i += effectLength;
		}
		else
		{
			if (nextFragmentTxt == "")
			{
				// begin a new fragment
				nextFragmentTxt = text.at(i);
				currentFragmentType = UI_TextFragments::char2FragmentType(text.at(i));
			}
			else
			{
				if (UI_TextFragments::charMatchesFragmentType(text.at(i), currentFragmentType))
				{
					// continue current fragment
					nextFragmentTxt = nextFragmentTxt + text.at(i);
				}
				else
				{
					// close current fragment and begin a new one
					TxtFragment newFragment;
					newFragment.text = nextFragmentTxt;
					newFragment.tintEffect = currentColor;
					newFragment.typeOfFragment = currentFragmentType;
					fragments.push_back(newFragment);
					nextFragmentTxt = text.at(i);
					currentFragmentType = UI_TextFragments::char2FragmentType(text.at(i));
				}
			}
		}
	}
	if (nextFragmentTxt != "")
	{
		// save last fragment
		TxtFragment newFragment;
		newFragment.text = nextFragmentTxt;
		newFragment.tintEffect = currentColor;
		newFragment.typeOfFragment = currentFragmentType;
		fragments.push_back(newFragment);
	}
}

UI_TextFragments::~UI_TextFragments()
{
}

void UI_TextFragments::addFragment(std::string& txt, Surface::Color tintEffect)
{
	std::for_each(txt.begin(), txt.end(), [](char& c) { c = ::toupper(c); });
	TxtFragment newFragment;
	newFragment.text = txt;
	newFragment.tintEffect = tintEffect;
	fragments.push_back(newFragment);
}


TextLign UI_TextFragments::acquireSingleLign(unsigned int lignWidth, const Police& police)
{
	TextLign lign;
	unsigned int looper = 0;
	unsigned int widthRemaining = lignWidth;
	unsigned int lignTextWidth = 0;
	bool lignCompleted = false;
	unsigned int fragmentTxtWidth = 0;

	while (looper < fragments.size() && lignCompleted == false)
	{
		fragmentTxtWidth = UI_Utils::getTextPixelWidth(fragments[looper].text, police.font);
		if (widthRemaining > fragmentTxtWidth)
		{
			lign.content.push_back(fragments[looper]);
			widthRemaining = widthRemaining - fragmentTxtWidth;
			lignTextWidth += fragmentTxtWidth;
		}
		else
			lignCompleted = true;	
	}
	lign.remainingWidth = lignWidth - lignTextWidth;
	return lign;
}

void UI_TextFragments::acquireLigns(unsigned int lignWidth, const Police& police, std::vector<TextLign>& contentToFill)
{
	UI_TextFragments::Lign lignBuilder(contentToFill, lignWidth);
	
	for (unsigned int i = 0; i < fragments.size(); i++)
	{
		if (fragments[i].typeOfFragment == fragmentType::endlign)
		{
			// save a lign for each endlign symbol encountered
			for (unsigned int j = 0; j < fragments[i].text.length(); j++)
				lignBuilder.saveLign(police);
		}
		else
		{
			lignBuilder.evaluateFragment(fragments[i], police);
		}
	}
	// check to remove last fragment if last lign ends with a spaceBlock
	if (contentToFill.size() > 0)
	{
		if (contentToFill.back().content.size() > 0)
		{
			if (contentToFill.back().content.back().typeOfFragment == fragmentType::spaceBlock)
			{
				// remove last fragment from last lign if it is a space block
				contentToFill.back().remainingWidth += UI_Utils::getTextPixelWidth(contentToFill.back().content.back().text, police.font);
				contentToFill.back().content.pop_back();
			}
		}
	}
}




// private methods
fragmentType UI_TextFragments::char2FragmentType(unsigned char value)
{
	fragmentType type;
	if (UI_Font::isAlphaNumerical(value) || UI_Font::isPunctuationSymbol(value) || UI_Font::isAccentuated(value))
	{
		type = fragmentType::word;
	}
	else if (UI_Font::isSpaceChar(value))
	{
		type = fragmentType::spaceBlock;
	}
	else if (value == 13 || value == 10)
	{
		type = fragmentType::endlign;
	}
	else
	{
		type = fragmentType::undefined;
	}
	return type;
}

bool UI_TextFragments::charMatchesFragmentType(unsigned char value, fragmentType type)
{
	if (type == fragmentType::word)
		return UI_Font::isAlphaNumerical(value) || UI_Font::isPunctuationSymbol(value);
	else if (type == fragmentType::spaceBlock)
		return UI_Font::isSpaceChar(value);
	else if (type == fragmentType::endlign)
		return value == 13 || value == 10;
	else
		return false;
}

bool UI_TextFragments::nextCharBeginsAnEffect(unsigned char value, const std::string& text, unsigned int pos)
{
	if (value == '|')
	{
		if (text.length() - (pos + 1) >= 9)
		{
			// could be any effect
			if (text.at(pos + 1) == 'c' || text.at(pos + 1) == 'r')
				return true;
			else
				return false;
		}
		else if (text.length() - (pos + 1) >= 1)
		{
			// can only be a reset effect
			if (text.at(pos + 1) == 'r')
				return true;
			else
				return false;
		}
		else
			// '|' is the last character of the string, so can't begin an effect
			return false;
	}
	else
		// the next character in the string isn't the effect marker 
		return false;
}

unsigned char UI_TextFragments::biAlpha2Hexadecimal(unsigned char first, unsigned char second)
{
	unsigned char value = 0;
	if (first >= 48 && first <= 57)
		value += (first - 48) * 16;
	else if (first >= 65 && first <= 70)
		value += (first - 55) * 16;
	else if (first >= 97 && first <= 102)
		value += (first - 87) * 16;
	if (second >= 48 && second <= 57)
		value += second - 48;
	else if (second >= 65 && second <= 70)
		value += second - 55;
	else if (second >= 97 && second <= 102)
		value += second - 87;
	return value;
}

unsigned int UI_TextFragments::readEffect(const std::string& text, unsigned int pos, Surface::Color& color, const Surface::Color& baseColor)
{
	if (text.at(pos + 1) == 'c')
	{
		// read color effect
		Surface::Color newColor;
		newColor.SetA(UI_TextFragments::biAlpha2Hexadecimal(text.at(pos + 2), text.at(pos + 3)));
		newColor.SetR(UI_TextFragments::biAlpha2Hexadecimal(text.at(pos + 4), text.at(pos + 5)));
		newColor.SetG(UI_TextFragments::biAlpha2Hexadecimal(text.at(pos + 6), text.at(pos + 7)));
		newColor.SetB(UI_TextFragments::biAlpha2Hexadecimal(text.at(pos + 8), text.at(pos + 9)));
		color = newColor;
		return 9;
	}
	else
	{
		// read reset effect
		color = baseColor;
		return 1;
	}
}

// lign Builder class
UI_TextFragments::Lign::Lign(std::vector<TextLign>& cntToFill, unsigned int lignWidth)
	: contentToFill(cntToFill),
	lignTotalWidth(lignWidth)
{
	widthRemaining = lignTotalWidth;
	lign = TextLign();
}

UI_TextFragments::Lign::~Lign()
{
	// save last lign if it contains data
	if (lignTextWidth > 0)
	{
		lign.remainingWidth = lignTotalWidth - lignTextWidth;
		contentToFill.push_back(lign);
	}
}

void UI_TextFragments::Lign::evaluateFragment(const TxtFragment& fragment, const Police& police)
{
	unsigned int fragmentWidth = UI_Utils::getTextPixelWidth(fragment.text, police.font);
	if (fragmentWidth > lignTotalWidth)
	{
		// fragment is too large for a whole lign
		if (lignTextWidth > 0)
			saveLign(police);
		addFragment(fragment, fragmentWidth, police.ignoreSpaceAtStartOfLign);
		saveLign(police);
	}
	else if (fragmentWidth > widthRemaining)
	{
		// fragment is too large for remaining available space
		saveLign(police);
		addFragment(fragment, fragmentWidth, police.ignoreSpaceAtStartOfLign);
	}
	else
	{
		// fragment is small enough to fit on current lign
		addFragment(fragment, fragmentWidth, police.ignoreSpaceAtStartOfLign);
	}
}

void UI_TextFragments::Lign::saveLign(const Police& police)
{
	if (lign.content.back().typeOfFragment == fragmentType::spaceBlock)
	{
		unsigned int lastFragWidth = UI_Utils::getTextPixelWidth(lign.content.back().text, police.font);
		lignTextWidth = lignTextWidth - lastFragWidth;
		widthRemaining = widthRemaining + lastFragWidth;
		lign.content.pop_back();
	}
	lign.remainingWidth = lignTotalWidth - lignTextWidth;
	contentToFill.push_back(lign);
	this->resetValues();
}

void UI_TextFragments::Lign::addFragment(const TxtFragment& fragment, unsigned int fragWidth, bool ignoreFirstBlockIfSpace)
{
	if (fragment.typeOfFragment == fragmentType::spaceBlock)
	{
		if (lign.content.size() > 0 || ignoreFirstBlockIfSpace == false)
		{
			lign.content.push_back(fragment);
			widthRemaining = widthRemaining - fragWidth;
			lignTextWidth = lignTextWidth + fragWidth;
		}
	}
	else
	{
		lign.content.push_back(fragment);
		widthRemaining = widthRemaining - fragWidth;
		lignTextWidth = lignTextWidth + fragWidth;
	}	
}

void UI_TextFragments::Lign::resetValues()
{
	lign = TextLign();
	lignTextWidth = 0;
	widthRemaining = lignTotalWidth;
}
