#ifndef cr_H_INCLUDED
#define cr_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "gui/gui_component.h"
#include <list>
#include "town.h"
#include "region.h"

const int USE_FOR_ARMY = 1;
const int USE_FOR_TOWNS = 2;
const int USE_FOR_MARKET = 3;


class CCountry
{

	string name, ruler;

	int id;

	std::vector<int> regions;
	std::vector<int> towns;
	Colorf color;
	bool player;
	std::map<string, float> stats;
public:

	float getStat(string s) { return stats[s]; }
	void setStat(string s, float w) { stats[s] = w; }
	void addStat(string s, float w) { stats[s] += w; }

	CCountry();

	bool isPlayer() { return player; }
	void setPlayer() { player = 1; }

	Colorf getColor() { return color; };

	void deleteTown(int id)
	{
		for (int a = 0; a < towns.size(); a++)
			if (towns[a] == id) { towns.erase(towns.begin() + a); a = 9999; }
	}

	float getIncome(eResType res, int t = 0);
	float getUseOfRes(eResType res, int t = 0);
	float getRes(eResType res);
	void addRes(eResType res, float n);

	void addTown(int i) { towns.push_back(i); }

	std::vector<int> getRegions() { return regions; };
	std::vector<int> getTowns() { return towns; };

	string getName() { return name; }
	void setName(string n) { name = n; }

	int getID() { return id; }


	CCountry(int i, string name, Colorf col);

	void update();



};

#endif