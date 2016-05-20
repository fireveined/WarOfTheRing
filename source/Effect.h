#ifndef T1OOLTPa24_H_INCLUDED
#define T1OOLTPa24_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "gui/gui_component.h"
#include <list>

using namespace clan;


class CEffect
{
Sprite sprite;
Point pos;
Point pos2;
float timer;
float startTimer;
bool alphaEffect;
string type;
Colorf color;



public:

	CEffect(){}
	CEffect(string nam, Point p, float t=-1);
	
	CEffect(Point p, Point p2, Colorf c, float t);

	void setAlphaEffect(bool w){alphaEffect=w;};
	virtual void update();
	virtual void draw();
	virtual bool isAlive();

};

#endif