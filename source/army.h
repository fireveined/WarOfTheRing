#ifndef ar_H_INCLUDED
#define ar_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "gui/gui_component.h"
#include <list>
#include "object.h"
#include "unit.h"


class CArmy : public CObject
{

	int id;
	Rectf position;


	int region;

	bool exist;
	int owner;
	int roadId;
	std::vector<CUnit> units;

public:

	int cityId, lastCityId;
	float wayPassed;

	bool moving;
	int neighbours;
	Point aimPoint;
		std::vector<int> way;

	int getRoadId();
	
		int getOwner(){return owner;}
		void setOwner(int o){owner=o;};

	CArmy();

	bool ifExitst(){return exist;}
	void deleteArmy(){exist=0; deleteFromGrid();}



	int getRegion(){return region;};
	void setRegion(int r){region=r;}


		int getID(){return id;}

		int getStrength();
		int getUnitsCount(){return units.size();}

		void drawShield(Canvas cv, Point pos, int bold=0);

		CUnit* getUnit(int id);
		CUnit* getUnitByType(int type);
		void deleteUnits(CUnit* u, float count);

	void mergeWith(CArmy* a);

	CArmy(int i, Point pos, int owner);

	void draw(Canvas cv);
	void update();



		Rect getArea(){return position;}
		Point getPosition() const {return Point(position.get_center().x, position.bottom);} 
				Rectf getVisibleArea();


	 bool onInput(const InputEvent &event);

 	void onClick(CGUIComponent* c, int key){};
	void onHover(CGUIComponent* c, int key){};
	void onPress(CGUIComponent* c, int key){};

		int next, prev;
	static int** grid;
	static int cellW, cellH;
	static void getArmiesInPoint(Point pos, float rad, std::vector<int>& vec);

	 float getResUse(eResType res);

	 float getMorale();
	 float getCount();
	 float getSpeed();

	void addUnit(CUnit*u);
	void addToGrid();
		void deleteFromGrid();
};
bool compareArmyByPosition(int a1, int a2);

#endif