

#pragma once

#include <ClanLib/core.h>
#include "gui_component.h"


class CGUISlider : public CGUIComponent
{

float value, valueShown, barValue;
bool disabled;

	float animTimer;
		fastdelegate::FastDelegate2<CGUIComponent*, float> onChange;
		fastdelegate::FastDelegate2<CGUIComponent*, int> onDisable;
		bool vertical;

		float lightTimer;
public:

	float getValue(){return value;}
	void setValue(float f){value=f;} // 0-1

	void setBarValue(float f){barValue=f;} // 0-1

	CGUISlider(string name, clan::Point pos, int width, float value=0.5, bool vert=0);

		 void setOnChange(fastdelegate::FastDelegate2<CGUIComponent*, float> f){onChange=f;}
		  void setOnDisable(fastdelegate::FastDelegate2<CGUIComponent*, int> f){onDisable=f;}
	void updateArea();
	void draw();
	void update();
	bool onInput(const InputEvent &event);

	bool isActive(){return !disabled;};
	void disable(bool d){disabled=d;};
};