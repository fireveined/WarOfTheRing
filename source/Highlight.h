#ifndef T1OOL2TPa24_H_INCLUDED
#define T1OOL2TPa24_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <list>
#include <map>

using namespace clan;

enum eHighlightType
{
	radius,
	image,
	rect
};

struct  sHighlight
{

public:

	Point center;
	int radius;
	Rect rect;
	float anim;
	std::string image;
	eHighlightType type;

	Colorf color;

	sHighlight() { anim = 0; }
	sHighlight(Point p, int rad) { init(p, rad); };
	sHighlight(Rect rec) { init(rec); };
	sHighlight(std::string& img, Rect rec) { init(img, rec); };

	bool init();
	bool init(Point p, int rad, Colorf col = Colorf(255, 255, 255, 40));
	bool init(Rect rec, Colorf col = Colorf(255, 255, 255, 40));
	bool init(std::string& img, Rect rec, Colorf col = Colorf(255, 255, 255, 40));

	bool update();


};


bool makeHighlight(Point p, int rad, Colorf col = Colorf(255, 255, 255, 65));
bool makeHighlight(Rect rec, Colorf col = Colorf(255, 255, 255, 25));
bool makeHighlight(std::string& img, Rect rec, Colorf col = Colorf(255, 255, 255, 25));

//bool makeInterval(float sec);
#endif