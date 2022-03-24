#include "UI_TextBox.h"

UI_TextBox::UI_TextBox(ComponentData data, Graphics& gfx, std::string backgroundFilePath, const std::string& text, const Police& _police)
	: UI_Component(data, gfx, backgroundFilePath),
	police(_police)
{
	initialText = text;
	// calculate visible lign count
	float lignScreenHeight = UI_Math::CalculateTextLignScreenHeight(police.letterSize);  // amount of screen a lign takes vertically
	float interlignSpace = UI_Math::CalculateInterlignHeight(lignScreenHeight, police.interlign); 
	float lignHeightSize = data.size.size * data.size.scaleY / lignScreenHeight; // amount of ligns that could fit within the textBox size
	visibleLignCount = (unsigned int)(data.size.size * data.size.scaleY / (lignScreenHeight + interlignSpace));
	unsigned int pixelHorizontalCount = UI_Math::CalculateTextLignPixelWidth(lignScreenHeight, UI_Utils::getFontBaseTextHeight(police.font), data.size.size * data.size.scaleX);

	//decompose text in fragments
	UI_TextFragments txtFragment(text, police);
	txtFragment.acquireLigns(pixelHorizontalCount, police, textLigns);

	for (unsigned int i = 0 ; i < visibleLignCount ; i++)
	{
		std::shared_ptr<Surface> lignTextImage = std::make_shared<Surface>(pixelHorizontalCount, UI_Utils::getFontBaseTextHeight(police.font));
		lignTextImage->Clear({ 0, 255, 255, 255 });
		if (i < textLigns.size())
			UI_Utils::drawTextOnSurface(textLigns[i], lignTextImage, police);
		else
			lignTextImage = UI_Utils::stringToSurface(" ", police.font);
		data.drawTech = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseSurfaceTextured);
		TechniqueBuilder::AutoFillerSurfaceTextured(data.drawTech, lignTextImage);
		visibleTextLigns.emplace_back(std::make_shared<UISquare>(gfx, data.size.size, data.size.scaleX, data.size.scaleY / lignHeightSize, data.drawTech));
	}
	lignSize = (data.size.size * data.size.scaleY) / visibleTextLigns.size();
	lign0Distance = ((data.size.size * data.size.scaleY) - lignSize) / 4.0f;
}

UI_TextBox::~UI_TextBox()
{
}

void UI_TextBox::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	UI_Component::AdjustPosToParent(inWorldPos, parentSize, parentXscale, parentYscale);
	for (unsigned int i = 0; i < visibleLignCount; i++)
	{
		float distance = calculateDistance(i);
		DirectX::XMFLOAT3 lignInWorldPos = UI_Math::CalculatePtCoordFromPoint(GetInWorldPos(), { 0.0f, distance });
		visibleTextLigns[i]->SetPos(UI_Math::GetUI_Facing(), lignInWorldPos);
	}
}

void UI_TextBox::SubmitToChannel()
{
	UI_Component::SubmitToChannel();
	for (unsigned int i = cursor; i < cursor + visibleLignCount; i++)
	{
		visibleTextLigns[i]->Submit(Chan::main);
	}
}

void UI_TextBox::LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef)
{
	UI_Component::LinkTechniques(rgRef);
	for (unsigned int i = 0; i < visibleTextLigns.size(); i++)
	{
		visibleTextLigns[i]->LinkTechniques(rgRef);
	}
}

void UI_TextBox::SpawnControlWindow(Graphics& gfx, int index)
{
	std::string windowName = "Text Box " + std::to_string(index);
	if (ImGui::Begin(windowName.c_str()))
	{
		std::string valueToDisplay = "Visible Ligns : " + std::to_string(visibleLignCount);
		ImGui::Text(valueToDisplay.c_str());
		valueToDisplay = "Lign Width : " + std::to_string(lignSize);
		ImGui::Text(valueToDisplay.c_str());
		valueToDisplay = "Amount of Ligns : " + std::to_string(textLigns.size());
		ImGui::Text(valueToDisplay.c_str());
		for (unsigned int i = 0; i < textLigns.size(); i++)
		{
			std::string contentToDisplay = "";
			for (unsigned int j = 0; j < textLigns[i].content.size(); j++)
				contentToDisplay = contentToDisplay + textLigns[i].content[j].text;
			ImGui::Text(contentToDisplay.c_str());
		}
		ImGui::Text("Text sent to constructor :");
		ImGui::Text(initialText.c_str());
	}
	ImGui::End();
}

bool UI_TextBox::isLignVisible(unsigned int lignId)
{
	return lignId >= cursor && lignId < cursor + visibleLignCount;
}

float UI_TextBox::calculateDistance(unsigned int lignId)
{
	if (visibleTextLigns.size() == 1)
		return 0.0f;
	else
		return lign0Distance - (lignSize * lignId) / 2;
}
