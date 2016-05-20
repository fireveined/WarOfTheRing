#ifndef tw_H_INCLUDED
#define tw_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "gui/gui_component.h"
#include <list>
#include "object.h"
#include "common\Common.h"

const int TOWN_RADIUS=15;

class CArmy;
enum eTownType
{
TOWN_CITY,
TOWN_VILLAGE,
TOWN_STRONGHOLD,
TOWN_SPOT,
TOWN_ROAD
};
enum eTownSlider
{
	army=0,
	mining,
	tech,
	administration
};

class sRoad : public CObject
{
public:
	int id;
	int town1, town2;
	int length;
	bool upgraded;
	bool exist;
	sRoad(){objectType="road"; }


};

int getShortestWay(int id1, Point point1, int id2, Point point2,  std::vector<int>& way);

struct sTownOrder
{
double start;
double progress;
float costs[(int)RES_ALL_NUM];
int unit;
int build;
bool paused;
sTownOrder(){paused=0;}
double morale;
};

extern std::vector<sRoad> mapRoads;

class CTown : public CObject
{

	int id;
	Rect position;
	eTownType type;

	string name;
	int region;

	float smokeTimer;
	

	bool exist;
	int owner;

	
public:
		std::vector<int> roads;
			int searchId;

	std::vector<sTownOrder> townOrders;

		int getOwner(){return owner;}
	void setOwner(int o);

	CTown();

	bool ifExitst(){return exist;}
	void deleteTown(){exist=0;}

	float getBuild(int n)
	{
		string buildings[3]={"fortyfications",  "barracks", "upgrade"};
		return getStat(buildings[n]);
	}
	void addBuild(int n, float add)
	{

			string buildings[3]={"fortyfications",  "barracks", "upgrade"};
			setStat(buildings[n],getStat(buildings[n])+ add);
	}


	float getSlider(eTownSlider s)
	{
		return getStat("slider"+IntToStr((int)s));
	}

		float getSliderAim(eTownSlider s)
	{
		return getStat("slider"+IntToStr((int)s)+"_aim");

	}
		float getRealPP();
		float getPPOn(eTownSlider s);

				float getAimPPOn(eTownSlider s);
				float getAttrib(string str);

	int getRegion(){return region;};
	void setRegion(int r){region=r;}
	void addRoad(int id)
	{
		roads.push_back(id);
	}

	void deleteRoad(int id)
	{
		for(int a=0;a<roads.size();a++)
			if(roads[a]==id){roads.erase(roads.begin()+a);a=9999;}
	}


	float getResCostFor(int build, eResType typ);
	float getResUseOfOrders(eResType t);

	string getName(){return name;}
	void setName(string n){name=n;}
		int getID(){return id;}

	eTownType getType(){return type;}
	void setType(eTownType t){type=t;}

	float getPoints();

	CTown(int i, int reg, Point pos, eTownType resname);

	void draw(Canvas cv);
	void update();

	float getResIncome(eResType res);
	float getResUse(eResType res);

		Rect getPosition(){return position;}
		Point getCenter(){return position.get_center();}

	 bool onInput(const InputEvent &event);

 	void onClick(CGUIComponent* c, int key){};
	void onHover(CGUIComponent* c, int key){};
	void onPress(CGUIComponent* c, int key){};



};

#endif