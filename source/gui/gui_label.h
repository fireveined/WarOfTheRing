

#pragma once

#include <ClanLib/core.h>
#include "gui_component.h"


class CGUILabel : public CGUIComponent
{

	string text;
	string title;
	Point oryginalPos;
	unsigned char align;

public:

		string getText(){return name;};
	void setText(string& s){text=s; updateArea();};

	CGUILabel(string name, string  t, Point pos, unsigned char al= align_top | align_left);

	//	CGUILabel(string name, string  title, string text , Point pos, unsigned char al=align_left);

		string getTitle(){return title;}
		void setTitle(string s){title=s;}

	void updateArea();
	void draw();
	void update();
	bool onInput(const InputEvent &event);


};