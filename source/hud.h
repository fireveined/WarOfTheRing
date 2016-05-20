

#pragma once

#include <ClanLib/core.h>
#include "gui/gui_component.h"

class CTown;

class CHUD : public CGUIComponent
{


	Rect panelRectScreen, describeRect, describeRectScreen, townOrderRect, armyRect, armyRectScreen;
	Point gPos;
	float animTimer;

	int screen;
	std::vector<string> leftVars;
	std::vector<string> rightVars;

	int buildInQueue[3];

public:



	CHUD();


	void drawTownHUD();
	void drawTownHUDTopPanel(CTown* town);
	void initTownHUD();
	void onSliderChange(CGUIComponent* comp, float f);
	void onSliderDisable(CGUIComponent* comp, int f);

	void draw();
	void update();
	bool onInput(const InputEvent &event);


};

struct sDate
{
	int hour, day, month, year;
	sDate() {}
	sDate(double t) { init(t); }

	void init(double time);

	string get();
	string diff(double time2);
	static string getTime(double tim, bool onlynum = 0);
};