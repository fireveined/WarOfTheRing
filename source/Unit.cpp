#include "Map.h"
#include "unit.h"
#include "common/tokenizer.h"
#include "device.h"
#include "resmanager.h"
#include "gameplay.h"
#include "ActionGun.h"


CUnit unitTemplates[15][6];

bool CUnit::onInput(const InputEvent &event)
{
	return 1;
}

CUnit::CUnit(string temp)
{
		selected=0;
		objectType="unit";
		unitTemplate=temp;

		

}

	int CUnit::getStrength()
	{
		return getStat("count")/getStat("baseCount")*getStat("tier");

	}

	Rect CUnit::getIconImage()
	{
		return Rect(icon*60,nation*90, Size(60,90));
	}

	CUnit CUnit::getUnit(int nation, int id)
	{
	
		return unitTemplates[nation][id];
	}