

#pragma once

#include <ClanLib/core.h>
#include "gui_component.h"



class CGUIManager : public CGUIComponent
{

	map<string, sTheme> themes;

public:

	string getFullName(){return "";}
	sTheme& getTheme(string& s){return themes[s];}
	Point getPosition(){return Point(0,0);};
	void draw();
	void update();
	bool onInput(const InputEvent &event);
	static CGUIManager GUIManagerInstance;
	static CGUIManager* GetGUIManager()
	{
		return &GUIManagerInstance;
	}
};