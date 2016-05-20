#ifndef TOOLTP2a_H_INCLUDED
#define TOOLTP2a_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "object.h"
#include <list>


enum eUnitType
{

	archer,
	pikeman,
	swordsman,
	cavalaryman

};

class CUnit : public CObject
{

	



public:

	float costs[(int)RES_ALL_NUM];
int icon, nation;
	string unitTemplate, name, describe;
	eUnitType unitType;
	CUnit(string temp);

	CUnit(){}

	const string& getTemplate(){return unitTemplate;}

	Rect getIconImage();

	virtual bool onInput(const InputEvent &event);

	static CUnit getUnit(int nation, int id);
	int getStrength();

	int getType(){return nation*6+icon;}

	string getUnitTypeString()
	{
		string types[4]={"Strzelec", "Pikeman", "Swordsman", "Cavalaryman" };
		return types[(int)unitType];
	}
};

extern CUnit unitTemplates[15][6];
#endif