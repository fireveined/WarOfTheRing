

#pragma once

#include <ClanLib/core.h>
#include "gui_component.h"



class CGUIContainer : public CGUIComponent
{





public:



	CGUIContainer(string nam)
	{
			create(nam);
	}


	void draw();
	void update();
	bool onInput(const InputEvent &event);

};