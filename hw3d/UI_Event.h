#pragma once
#include "UI_Generics.h"
#include "UI_Element.h"
#include "UI_Maths.h"
#include "UI_Utils.h"

class UI_Event
{
public:
private:
	std::weak_ptr<UI_Component> refCompo;
	mouseEvents eventType;
};