

#pragma once

#include <ClanLib/core.h>
#include "gui_component.h"


class CGUIButton : public CGUIComponent
{

	string text, imageName;
	Rect imageRect;

	float clickTimer;
	float animTimer;
	bool imageButton;
public:

		string getText(){return name;};
	void setText(string& s){text=s; updateArea();};

	void setImageRect(Rect img){imageRect=img; updateArea();}
	CGUIButton(string name, string  t, clan::Point pos);
		CGUIButton(string name, string  image_name, Rect img, clan::Point pos);

	void updateArea();
	void draw();
	void update();
	bool onInput(const InputEvent &event);


};