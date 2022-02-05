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

//void UI_Utils::string2StringLigns(unsigned int lignPixelWidth, const std::string& text, std::vector<std::string>& ligns)
//{
//	// segment the string to know the different parts of it
//	std::shared_ptr<std::vector<stringSegmentData>> segmentationData = std::make_shared<std::vector<stringSegmentData>>();
//	UI_Utils::acquireStringSegmentationData(text, segmentationData);
//
//	unsigned int pixelsRemaining = lignPixelWidth;
//	unsigned int currentLign = 0;
//	// fill the vector of strings with the data that can enter in a lign
//	for (unsigned int i = 0; i < segmentationData->size(); i++)
//	{
//		if (segmentationData->at(i).segmentType == stringSegmentType::endlign)
//		{
//			currentLign++;
//			pixelsRemaining = lignPixelWidth;
//		}
//		else if (segmentationData->at(i).segmentType == stringSegmentType::undefined)
//		{
//			// undisplayable characters... the segment is discarded
//		}
//		else
//		{
//			// the next segment is a word or a space block
//			if (segmentationData->at(i).pixelWidth < pixelsRemaining)
//			{
//				// next segment fits whole in the current lign
//				if (pixelsRemaining == lignPixelWidth)
//				{
//					// first segment in the lign
//					ligns.push_back(text.substr(segmentationData->at(i).start, segmentationData->at(i).length));
//				}
//				else
//				{
//					// segment to be added to current lign
//					ligns[currentLign] = ligns[currentLign] + text.substr(segmentationData->at(i).start, segmentationData->at(i).length);
//				}
//				pixelsRemaining -= segmentationData->at(i).pixelWidth;
//			}
//			else if (segmentationData->at(i).pixelWidth > lignPixelWidth)
//			{
//				// next segment is larger than total length of a lign
//				// for now, it is just ignored... To be implemented eventually!
//			}
//			else
//			{
//				// next segment can fit in a lign, but not enough room in current lign
//				currentLign++;
//				ligns.push_back(text.substr(segmentationData->at(i).start, segmentationData->at(i).length));
//				pixelsRemaining = lignPixelWidth - segmentationData->at(i).pixelWidth;
//			}
//		}
//		
//	}
//}

void UI_Utils::drawTextOnSurface(const txtFragment& text, std::shared_ptr<Surface> surface, surfaceCursor& cursor)
{
	textFont->drawTextOnSurface(text, surface, cursor);
}

void UI_Utils::drawTextOnSurface(const std::string& text, std::shared_ptr<Surface> surface, Surface::Color color)
{
	textFont->drawTextOnSurface(text, surface, color);
}

void UI_Utils::drawTextOnSurface(const textLign& lign, std::shared_ptr<Surface> surface, const police& police)
{
	textFont->drawTextOnSurface(lign, surface, police);
}

// ** private methods **
/*
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

void UI_Utils::acquireStringSegmentationData(const std::string& text, std::shared_ptr<std::vector<stringSegmentData>> data4Segmentation, Surface::Color baseColor)
{
	unsigned int currentSegId = 0;
	unsigned int looper = 0;
	data4Segmentation->reserve(text.length() / 2);
	Surface::Color currentColor = baseColor;
	// prepare first segment
	if (text.at(0) == '|' && text.length() >= 12)
	{
		// check if color code is present
		if (text.at(1) == 'c')
		{
			currentColor = UI_Utils::readColorCode(text.substr(2, 8));
			looper = 10;
		}
	}
	stringSegmentData currentSegment;
	currentSegment.start = looper;
	currentSegment.segmentType = UI_Utils::char2SegmentType(text.at(looper));
	currentSegment.length = 1;
	currentSegment.pixelWidth = UI_Utils::getCharPixelWidth(text.at(looper));
	currentSegment.color = currentColor;
	data4Segmentation->push_back(currentSegment);
	// manage rest of the string
	for (looper; looper < text.length(); looper++)
	{
		if (text.at(looper) == '|' && text.length() - looper >= 2)
		{
			// color change management

		}
		else
		{
			if (UI_Utils::charMatchesSegmentType(text.at(looper), data4Segmentation->at(currentSegId).segmentType))
			{
				// keep filling data in the current index of the vector as long as char type matches segment type
				data4Segmentation->at(currentSegId).length++;
				data4Segmentation->at(currentSegId).pixelWidth += UI_Utils::getCharPixelWidth(text.at(looper));
			}
			else
			{
				// prepare a new segment in the vector
				stringSegmentData newSegment;
				newSegment.start = looper;
				newSegment.segmentType = UI_Utils::char2SegmentType(text.at(looper));
				newSegment.length = 1;
				newSegment.pixelWidth = UI_Utils::getCharPixelWidth(text.at(looper));
				data4Segmentation->push_back(newSegment);
				currentSegId++;
			}
		}
		
	}
}
*/
