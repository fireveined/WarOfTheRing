#include "highlight.h"
#include "Device.h"
#include "ResManager.h"

const float anim_max = 0.21;

bool sHighlight::init()
{
	//anim=0;
	return update();
}

bool sHighlight::init(Point p, int rad, Colorf col)
{
	color = col;
	center = p;
	radius = rad;
	type = eHighlightType::radius;
	return init();
}

bool sHighlight::init(Rect rec, Colorf col)
{
	color = col;
	rect = rec;
	type = eHighlightType::rect;
	return init();
}

bool sHighlight::init(std::string& img, Rect rec, Colorf col)
{
	color = col;
	image = img;
	rect = rec;
	type = eHighlightType::image;
	return init();
}

bool sHighlight::update()
{
	if (anim > anim_max)anim = anim_max;

	Colorf col = color;
	col.a = color.a*anim / anim_max;

	if (type == eHighlightType::radius)
	{
		Colorf col2 = col;
		col2.a = 0;
		GetGC().fill_circle(Pointf(center), radius, Gradient(col, col2));
		if (center.distance(getMousePos()) < radius)
		{
			anim += CTimer::dt;
			return 1;
		}

	}

	if (type == eHighlightType::rect)
	{
		col.a *= 1.4;
		Colorf col2 = col;
		col2.a = col.a*0.1;
		GetGC().fill_rect(rect, Gradient(col2, col, col, col2));
		if (rect.contains(getMousePos()))
		{
			anim += CTimer::dt;
			return 1;
		}

	}

	anim -= CTimer::dt / 2;
	if (anim < 0)anim = 0;
	return 0;
}


std::map<Point, sHighlight> highlightsMap;

bool makeHighlight(Point p, int rad, Colorf col)
{
	return highlightsMap[p].init(p, rad, col);
}
bool makeHighlight(Rect rec, Colorf col)
{
	return highlightsMap[rec.get_top_left()].init(rec, col);
}

bool makeHighlight(std::string& img, Rect rec, Colorf col)
{
	return highlightsMap[rec.get_top_left()].init(img, rec, col);
}

/*
std::map<int, float> timersMap;
bool makeInterval(float sec, int id)
{
	if(timersMap[(int)(sec*1000)]+sec<CTimer::fTime)
		{
			timersMap[(int)(sec*1000)]=CTimer::fTime;
	return 1;
	}
return 0;
}
*/