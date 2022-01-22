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

stringSegmentType UI_Utils::char2SegmentType(unsigned char value)
{
	stringSegmentType type;
	if (UI_Font::isAlphaNumerical(value) || UI_Font::isPunctuationSymbol(value))
	{
		type = stringSegmentType::word;
	}
	else if (UI_Font::isSpaceChar(value))
	{
		type = stringSegmentType::spaceBlock;
	}
	else if (value == 13 || value == 10)
	{
		type = stringSegmentType::endlign;
	}
	else
	{
		type = stringSegmentType::undefined;
	}
	return type;
}

bool UI_Utils::charMatchesSegmentType(unsigned char value, stringSegmentType type)
{
	if (type == stringSegmentType::word)
		return UI_Font::isAlphaNumerical(value) || UI_Font::isPunctuationSymbol(value);
	else if (type == stringSegmentType::spaceBlock)
		return UI_Font::isSpaceChar(value);
	else if (type == stringSegmentType::endlign)
		return value == 13 || value == 10;
	else
		return false;
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

void UI_Utils::acquireStringSegmentationData(const std::string& text, std::shared_ptr<std::vector<stringSegmentData>> data4Segmentation)
{
	unsigned int currentSegId = 0;
	data4Segmentation->reserve(text.length() / 2);
	// prepare first segment
	stringSegmentData currentSegment;
	currentSegment.start = 0;
	currentSegment.segmentType = UI_Utils::char2SegmentType(text.at(0));
	currentSegment.length = 1;
	currentSegment.pixelWidth = UI_Utils::getCharPixelWidth(text.at(0));
	data4Segmentation->push_back(currentSegment);
	// manage rest of the string
	for (unsigned int i = 1; i < text.length(); i++)
	{
		if(UI_Utils::charMatchesSegmentType(text.at(i), data4Segmentation->at(currentSegId).segmentType))
		{
			// keep filling data in the current index of the vector as long as char type matches segment type
			data4Segmentation->at(currentSegId).length++;
			data4Segmentation->at(currentSegId).pixelWidth += UI_Utils::getCharPixelWidth(text.at(i));
		}
		else
		{
			// prepare a new segment in the vector
			stringSegmentData newSegment;
			newSegment.start = i;
			newSegment.segmentType = UI_Utils::char2SegmentType(text.at(i));
			newSegment.length = 1;
			newSegment.pixelWidth = UI_Utils::getCharPixelWidth(text.at(i));
			data4Segmentation->push_back(newSegment);
			currentSegId++;
		}
	}
}

std::pair<unsigned int, unsigned int> UI_Utils::junkyTest(const std::string& text, std::shared_ptr<std::vector<stringSegmentData>> segmentData)
{
	if (segmentData->size() > 0)
	{
		return std::pair<unsigned int, unsigned>(segmentData->at(0).start, segmentData->at(0).length);
	}
	else
		return std::pair<unsigned int, unsigned int>(0,0);
}



