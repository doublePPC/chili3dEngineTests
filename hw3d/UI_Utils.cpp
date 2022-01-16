#include "UI_Utils.h"
#include "Surface.h"

std::unique_ptr<UI_Font> UI_Utils::textFont;

void UI_Utils::loadFontFile(std::string fileName)
{
	textFont = std::make_unique<UI_Font>(fileName);
}

std::shared_ptr<Surface> UI_Utils::stringToSurface(const std::string& value)
{
	if (value.length() == 1)
		return textFont->getSurfaceFromChar(*value.c_str());
	else
		return textFont->getSurfaceFromString(value);
}

std::shared_ptr<Surface> UI_Utils::charToSurface(unsigned char value)
{
	return textFont->getSurfaceFromChar(value);
}

void UI_Utils::applyColorFilterToSurface(std::shared_ptr<Surface> image, unsigned char red, unsigned char green, unsigned blue)
{
	for (int i = 0; i < image->GetWidth(); i++)
	{
		for (int j = 0; j < image->GetHeight(); j++)
		{
			auto color = image->GetPixel(i, j);
			color.SetR(UI_Font::baseColorAddition(red, color.GetR()));
			color.SetG(UI_Font::baseColorAddition(green, color.GetG()));
			color.SetB(UI_Font::baseColorAddition(blue, color.GetB()));
			image->PutPixel(i, j, color);
		}
	}
}

void UI_Utils::spawnFontControlWindow(Graphics& gfx)
{
	textFont->spawnControlWindow(gfx);
}

unsigned int UI_Utils::getTextPixelWidth(const std::string& text)
{
	unsigned int result = 0;

	for (unsigned int i = 0; i < text.length(); i++)
	{
		result += textFont->getCharWidth(text.at(i));
	}
	return result;
}

unsigned int UI_Utils::getTextPixelWidth(std::shared_ptr<std::string> text)
{
	unsigned int result = 0;

	for (unsigned int i = 0; i < text->length(); i++)
	{
		result += textFont->getCharWidth(text->at(i));
	}
	return result;
}

unsigned int UI_Utils::getCharPixelWidth(unsigned char c)
{
	return textFont->getCharWidth(c);
}

unsigned int UI_Utils::getFontBaseTextHeight()
{
	return textFont->getCharHeight();
}

unsigned int UI_Utils::getFontSpaceWidth()
{
	return textFont->getSpaceWidth();
}

std::shared_ptr<std::string> UI_Utils::getWordFromText(const std::string& text, unsigned int startingPoint)
{
	std::shared_ptr<std::string> result;
	std::string word = "";
	bool completed = false;
	unsigned int cursor = startingPoint;
	unsigned char currentChar;
	while (!completed && cursor < text.length())
	{
		currentChar = text.at(cursor);
		if (currentChar != 13 && currentChar != 32)
		{
			word = word + text.at(cursor);
		}
		else
		{
			completed = true;
		}
		cursor++;
	}
	result = std::make_shared<std::string>(word);
	return result;
}

std::shared_ptr<std::string> UI_Utils::getTextLignFromString(unsigned int horizontalPixelCount, const std::string& textRef, unsigned int& startingPoint)
{
	std::shared_ptr<std::string> result = nullptr;
	std::string lignText = "";

	unsigned int counter = startingPoint;
	unsigned int pixelsLeft = horizontalPixelCount;
	while (pixelsLeft > 0 && counter < textRef.length())
	{
		std::shared_ptr<std::string> nextWord = UI_Utils::getWordFromText(textRef, counter);
		unsigned int wordWidth = UI_Utils::getTextPixelWidth(nextWord);
		if (pixelsLeft >= wordWidth)
		{
			// add whole word to lign if space left is sufficient
			lignText = lignText + *nextWord;
			pixelsLeft = pixelsLeft - wordWidth;
			counter = counter + nextWord->length();
			// manage space character and carriage return
			if (textRef.at(counter) == 13 || pixelsLeft < textFont->getSpaceWidth())
			{
				pixelsLeft = 0;
			}
			else if (textRef.at(counter) == 32)
			{
				lignText = lignText + " ";
				pixelsLeft = pixelsLeft - textFont->getSpaceWidth();
				counter++;
			}
		}
		else if (pixelsLeft >= UI_Utils::getFontSpaceWidth())
		{
			// add char to char until limit is reached
			while (pixelsLeft >= UI_Utils::getCharPixelWidth(nextWord->at(counter)))
			{
				lignText = lignText + nextWord->at(counter);
				pixelsLeft = pixelsLeft - UI_Utils::getCharPixelWidth(nextWord->at(counter));
				counter++;
			}
			pixelsLeft = 0;
		}
		else
		{
			pixelsLeft = 0;
		}
	}
	result = std::make_shared<std::string>(lignText);
	startingPoint = counter;
	return result;
}

void UI_Utils::drawTextOnSurface(const txtFragment& text, std::shared_ptr<Surface> surface, surfaceCursor& cursor)
{
	textFont->drawTextOnSurface(text, surface, cursor);
}



