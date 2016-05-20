#ifndef TOOLTP_H_INCLUDED
#define TOOLTP_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "gui/gui_component.h"
#include <list>


enum eResType
{
	RES_WHEAT,
	RES_FISH,
	RES_WOOD,
	RES_STONE,
	RES_IRON,
	RES_GOLD,
	RES_NUM,
	RES_FOOD,
	RES_TIMBER,
	RES_PP,
	RES_TIME,
	RES_ALL_NUM

};

int resToInt(eResType r);
eResType intToRes(int i);
string resToStr(int r);

class CObject
{
protected:

	string objectType;
	std::map<string, float> stats;
	bool selected;
public:

	string getObjectType() { return objectType; };


	float getStat(string s) { return stats[s]; }
	void setStat(string s, float w) { stats[s] = w; }
	void addStat(string s, float w) { stats[s] += w; }

	virtual bool isSelected() { return selected; };
	void setSelected(bool s) { selected = s; }


	CObject() {}

	virtual	float getResIncome(eResType res) { return 0; };
	virtual float getResUse(eResType res) { return 0; };
};




#endif