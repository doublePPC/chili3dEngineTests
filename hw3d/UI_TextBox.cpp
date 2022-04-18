#include "UI_TextBox.h"

UI_TextBox::UI_TextBox(ComponentData data, Graphics& gfx, const std::string& backgroundFilePath, const std::string& text, const Police& _police)
	: UI_Component(data, gfx, backgroundFilePath),
	police(_police)
{
	initialText = text;
	float scaleXFactor = data.size.scaleX;
	// calculate visible lign count
	float lignHeightFactor = UI_Math::CalculateTextLignHeightFactor(police.letterSize);  // amount of screen a lign takes vertically
	float scaleYFactor = UI_Math::CalculateTextLignYScale(data.size.size * data.size.scaleY, lignHeightFactor);
	float interlignSpace = UI_Math::CalculateInterlignHeight(scaleYFactor, police.interlign);
	visibleLignCount = (unsigned int)(data.size.size * data.size.scaleY / (scaleYFactor + interlignSpace));
	unsigned int pixelHorizontalCount = UI_Math::CalculateTextLignPixelWidth(scaleYFactor, UI_Utils::getFontBaseTextHeight(police.font), data.size.size * data.size.scaleX);

	//decompose text in fragments
	UI_TextFragments txtFragment(text, police);
	txtFragment.acquireLigns(pixelHorizontalCount, police, textLigns);

	unsigned int recursions = 0;
	if (visibleLignCount >= textLigns.size())
	{
		recursions = visibleLignCount;
		//visibleLignCount = recursions;
	}	
	else
	{
		// there is more ligns in the text than the amount that can be shown on screen
		recursions = textLigns.size();
		ComponentData scrollData;
		scrollData.relPos = { 1.0f, 0.0f, data.relPos.z };
		scrollData.size = data.size;
		scrollData.size.scaleX = scrollData.size.scaleX * 0.05f;
		scaleXFactor = scaleXFactor * 0.95f;
		std::shared_ptr<Surface> bar = std::make_shared<Surface>(Surface::FromFile("Images\\scrollBAR.png"));
		UI_Utils::applyWhiteFadingTransparency(bar);
		scrollBar = std::make_unique<UI_ScrollBar>(scrollData, gfx, bar, "Images\\arrowUP.png", "Images\\arrowDOWN.png", "Images\\cursor.png");
	}

	for (unsigned int i = 0 ; i < recursions ; i++)
	{
		std::shared_ptr<Surface> lignTextImage = std::make_shared<Surface>(pixelHorizontalCount, UI_Utils::getFontBaseTextHeight(police.font));
		lignTextImage->Clear({ 0, 255, 255, 255 });
		if (i < textLigns.size())
			UI_Utils::drawTextOnSurface(textLigns[i], lignTextImage, police);
		else
			lignTextImage = UI_Utils::stringToSurface(" ", police.font);
		data.drawTech = std::make_shared<TechniqueBuilder>(UI_DrawTech::baseSurfaceTextured);
		TechniqueBuilder::AutoFillerSurfaceTextured(data.drawTech, lignTextImage);
		visibleTextLigns.emplace_back(std::make_shared<UISquare>(gfx, data.size.size, scaleXFactor, lignHeightFactor, data.drawTech));
	}
	lignSize = scaleYFactor + interlignSpace;
	lign0Distance = ((data.size.size * data.size.scaleY) - scaleYFactor) / 4.0f;
}

UI_TextBox::~UI_TextBox()
{
}

void UI_TextBox::AdjustPosToParent(DirectX::XMFLOAT3 inWorldPos, float parentSize, float parentXscale, float parentYscale)
{
	UI_Component::AdjustPosToParent(inWorldPos, parentSize, parentXscale, parentYscale);
	float distance;
	for (unsigned int i = 0; i < visibleLignCount; i++)
	{
		distance = calculateDistance(i);
		DirectX::XMFLOAT3 lignInWorldPos = UI_Math::CalculatePtCoordFromPoint(GetInWorldPos(), { 0.0f, distance });
		visibleTextLigns[i]->SetPos(UI_Math::GetUI_Facing(), lignInWorldPos);
	}
	if (scrollBar != nullptr)
	{
		Size size = this->GetSize();
		scrollBar->AdjustPosToParent(GetInWorldPos(), size.size, size.scaleX, size.scaleY);
	}
}

void UI_TextBox::SubmitToChannel()
{
	UI_Component::SubmitToChannel();
	for (unsigned int i = cursor; i < cursor + visibleLignCount; i++)
	{
		visibleTextLigns[i]->Submit(Chan::main);
	}
	if (scrollBar != nullptr)
		scrollBar->SubmitToChannel();
}

void UI_TextBox::LinkTechniques(Rgph::BlurOutlineRenderGraph& rgRef)
{
	UI_Component::LinkTechniques(rgRef);
	for (unsigned int i = 0; i < visibleTextLigns.size(); i++)
	{
		visibleTextLigns[i]->LinkTechniques(rgRef);
	}
	if (scrollBar != nullptr)
		scrollBar->LinkTechniques(rgRef);
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
	if (scrollBar != nullptr)
		scrollBar->SpawnControlWindow(gfx, index);
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
		return lign0Distance - (lignSize * (float)lignId) / 2.0f;
}
