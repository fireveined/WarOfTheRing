#include "resmanager.h"
#include "country.h"
#include "gameplay.h"

CCountry::CCountry(int i, string n, Colorf col)
{

	id = i;
	color = col;
	setStat("population", rand() % 9000 + 1000);
	player = 0;
	name = n;
	ruler = "JP2";
}


void CCountry::update()
{
	for (int a = 0; a < (int)RES_NUM; a++)
	{
		addRes((eResType)a, getIncome((eResType)a)*CTimer::dt / ONE_WEEK);
		addRes((eResType)a, -getUseOfRes((eResType)a)*CTimer::dt / ONE_WEEK);
	}

}

float CCountry::getIncome(eResType res, int type)
{
	float inc = 0;
	for (int a = 0; a < towns.size(); a++)
	{
		CTown* t = getMap()->getTown(towns[a]);
		inc += t->getResIncome(res);

	}
	return inc;
}

float CCountry::getUseOfRes(eResType res, int type)
{
	float inc = 0;
	if (res == RES_WHEAT)inc += getUseOfRes(RES_FOOD) / 2;
	else
		if (res == RES_FISH)inc += getUseOfRes(RES_FOOD) / 2;
		else
			if (res == RES_STONE)inc += getUseOfRes(RES_TIMBER) / 2;
			else
				if (res == RES_WOOD)inc += getUseOfRes(RES_TIMBER) / 2;

	for (int a = 0; a < towns.size(); a++)
	{
		CTown* t = getMap()->getTown(towns[a]);
		inc += t->getResUse(res);

		inc += t->getResUseOfOrders(res);

	}

	for (int a = 0; a < getMap()->getArmies()->size(); a++)
	{
		if (getMap()->getArmies()->at(a).getOwner() == this->id)
			inc += getMap()->getArmies()->at(a).getResUse(res);
	}

	return inc;

}

float CCountry::getRes(eResType res)
{

	return getStat("res" + IntToStr(res));

}

void CCountry::addRes(eResType res, float n)
{

	addStat("res" + IntToStr(res), n);
}