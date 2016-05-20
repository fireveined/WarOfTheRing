#include "resmanager.h"
#include "army.h"
#include "common/timer.h"
#include "gameplay.h"


int** CArmy::grid;
int CArmy::cellW = 50, CArmy::cellH = 50;
bool CArmy::onInput(const InputEvent &event)
{
	/*
	for(int a=0;a<objects.size();a++)
	{
	if(objects[a] && objects[a]->getQuad().is_inside(Pointf(event.mouse_pos)/Pointf(mapScale, mapScale)+Pointf(scrollX,scrollY)))
	if(objects[a]->onInput(event))
	return 1;
	}
	*/
	return 0;
}

void CArmy::addToGrid()
{
	int gx = getPosition().x / cellW, gy = getPosition().y / cellH;
	if (grid[gx][gy] == -1)
		grid[gx][gy] = id;
	else
	{
		int n = grid[gx][gy];
		while (getMap()->getArmy(n)->next != -1)
			n = getMap()->getArmy(n)->next;

		prev = n;
		getMap()->getArmy(n)->next = id;
	}
}

void CArmy::deleteFromGrid()
{
	int gx = getPosition().x / cellW, gy = getPosition().y / cellH;
	if (grid[gx][gy] == id)
	{
		grid[gx][gy] = -1;
		if (next != -1)
			grid[gx][gy] = next, getMap()->getArmy(this->next)->prev = -1;
	}
	else
	{

		getMap()->getArmy(this->prev)->next = this->next;
		if (next != -1)
			getMap()->getArmy(this->next)->prev = this->prev;

	}
	prev = -1;
	next = -1;
}

void CArmy::getArmiesInPoint(Point pos, float rad, std::vector<int>& vec)
{
	vec.clear();
	int gx = pos.x / cellW, gy = pos.y / cellH;
	int nx[9] = { 0,-1,0,1,1,1,0,-1,-1 };
	int ny[9] = { 0, -1,-1,-1,0,1,1,1,0 };
	for (int a = 0; a < 8; a++)
		if (grid[gx + nx[a]][gy + ny[a]] != -1)
		{
			int id = grid[gx + nx[a]][gy + ny[a]];
			if (getMap()->getArmy(id)->getPosition().distance(pos) < rad)
				vec.push_back(id);

			while (getMap()->getArmy(id)->next != -1)
			{
				id = getMap()->getArmy(id)->next;
				if (getMap()->getArmy(id)->getPosition().distance(pos) < rad)
					vec.push_back(id);
			}
		}

	bool whil = 1;
	while (whil)  //sortowanie od najwiêkszej si³y
	{
		whil = 0;
		for (int a = 1; a<vec.size(); a++)
			if (getMap()->getArmy(vec[a])->getStrength()>getMap()->getArmy(vec[a - 1])->getStrength())
			{
				int i = vec[a];
				vec[a] = vec[a - 1];
				vec[a - 1] = i;
				whil = 1;
			}

	}


}


CArmy::CArmy(int i, Point pos, int own)
{
	owner = own;
	selected = 0;
	objectType = "army";
	id = i;
	position = Rect(pos - Point(10, 30), Size(20, 30));
	next = -1, prev = -1;
	addToGrid();

	exist = 1;
	//setStat("strength", num);

	aimPoint = this->getPosition();

	cityId = -1;
	lastCityId = 0;
}

int CArmy::getStrength()
{
	int str = 0;
	for (int a = 0; a < units.size(); a++)
		str += units[a].getStrength();
	return str;
}

void CArmy::drawShield(Canvas cv, Point point, int bold)
{
	int str = getStrength();
	Colorf c = getMap()->getCountry(owner)->getColor();
	GetImage("village").set_color(c);

	string font = "small_font";
	Rect r(point, Size(position.get_size()));
	if (bold > 0)
	{
		font = "guifont_bold";
		r = Rect(point - Point(5, 7), Size(position.get_size()) + Size(10, 15));
		if (bold == 2)
		{
			cv.fill_ellipse(Pointf(point - Point(position.get_top_left() - position.get_center())), 30, 40, Gradient(Colorf(255, 255, 255, 80), Colorf(255, 255, 255, 0)));
			r = Rect(point - Point(8, 9), Size(position.get_size()) + Size(16, 19));
		}
		GetImage("village").draw(cv, Rect(0, 110, Size(30, 45)), r);
	}
	else
		GetImage("village").draw(cv, Rect(0, 80, Size(20, 30)), r);
	GetImage("village").set_color(Colorf::white);
	string t = IntToStr(str);
	int w = GetFont(font).get_text_size(cv, t).width / 2;
	Point pos = point - Point(position.get_top_left() - position.get_center()) - Point(w, 0);
	Colorf tc = Colorf(215, 215, 215);
	if (c.r == c.b && c.r == c.g)tc = Colorf(0, 0, 0);
	GetFont(font).draw_text(cv, pos.x, pos.y, t, tc);
}

Pointf slots[4] = { Point(-8,-8), Point(8,8), Point(-8,8), Point(8,-8) };

int getCounterSlot(int id)
{
	if (id == 0)return 1;
	if (id == 1)return 0;
	if (id == 2)return 3;
	if (id == 3)return 3;
}

Rectf CArmy::getVisibleArea()
{
	if (moving)return position;

	int onlyOne = -1;

	Pointf cor(0, 0);
	int p = prev;
	neighbours = -1;
	if ((prev != -1 && getMap()->getArmy(prev)->getPosition().distance(getPosition()) < 13) ||
		(next != -1 && getMap()->getArmy(next)->getPosition().distance(getPosition()) < 13))
		neighbours = 0;
	while (p != -1)
	{

		if (getMap()->getArmy(p)->getPosition().distance(getPosition()) < 13 && !getMap()->getArmy(p)->moving)
		{
			if (onlyOne == -1)onlyOne = getMap()->getArmy(p)->neighbours;
			else onlyOne = -5;
			neighbours++;
		}
		p = getMap()->getArmy(p)->prev;

	}
	if (neighbours != -1)
		cor = slots[neighbours];

	if (onlyOne > -1)cor = slots[getCounterSlot(onlyOne)];

	if (position.contains(Point(::map->getMouseX(), ::map->getMouseY())) || selected)
		cor *= 2;
	return Rect(position).translate(cor);
}


void CArmy::draw(Canvas cv)
{

	int str = getStrength();

	if (str != 0)
	{



		Rectf ar = getVisibleArea();
		if (ar != position)
			cv.draw_line(Pointf(getPosition()), Pointf(ar.get_center().x, ar.bottom), Colorf(0, 0, 0, 255));


		if (ar.contains(Point(::map->getMouseX(), ::map->getMouseY())) || selected)
			cv.fill_circle(Pointf(ar.get_center().x, ar.bottom), 5, Colorf(255, 255, 255, 50));


		drawShield(cv, Point(ar.get_top_left()));

	}

}


float CArmy::getResUse(eResType res)
{
	int c = 0;
	if (res == RES_FOOD)
	{
		for (int a = 0; a < units.size(); a++)
			c += units[a].getStat("count");

		return c / 50.0f;
	}
	if (res == RES_IRON)
	{
		for (int a = 0; a < units.size(); a++)
			if (units[a].getStat("tier") == 3)
				c += units[a].getStat("count");
		return c / 100;
	}
	else
		return 0;
}


void CArmy::update()
{
	moving = 0;

	Point aim = aimPoint;
	if (way.size() > 0)
	{
		aim = getMap()->getTown(way[way.size() - 1])->getCenter();

		if (aim.distance(getPosition()) < TOWN_RADIUS)
			cityId = way[way.size() - 1];


		if (aim.distance(getPosition()) < 4)
			way.pop_back();

	}
	else if (aim.distance(getPosition()) > 2 && aim.distance(getPosition()) < TOWN_RADIUS)
	{
		std::vector<int>&roads = getMap()->getTown(lastCityId)->roads;
		for (int a = 0; a < roads.size(); a++)
		{
			int t = mapRoads[roads[a]].town1;
			if (t == id)t = mapRoads[roads[a]].town2;
			if (getMap()->getTown(t)->getCenter().distance(getPosition()) < TOWN_RADIUS)
				cityId = lastCityId;
		}
	}


	if (cityId != -1 && getMap()->getTown(cityId)->getCenter().distance(getPosition()) > TOWN_RADIUS)
		lastCityId = cityId, cityId = -1;

	Pointf line(aim - getPosition());

	double speed = getSpeed()*getMap()->getDeltaTime();
	if (line.length() > 0)
	{
		deleteFromGrid();
		moving = 1;
		Pointf d = Pointf(line.x / line.length()*speed, line.y / line.length()*speed);
		wayPassed -= d.length();
		position = position.translate(d);

		addToGrid();
	}

	for (int a = 0; a < units.size(); a++)
	{
		double mor = -0.1 / units[a].getStat("tier");
		if (cityId != -1)
			mor += getMap()->getTown(cityId)->getAttrib("moraleDelta");

		units[a].addStat("morale", mor*getMap()->getDeltaTime() / ONE_HOUR);
		if (units[a].getStat("morale")>100)units[a].setStat("morale", 100);
		if (units[a].getStat("morale") < 10)units[a].setStat("morale", 10);
	}
}


CUnit* CArmy::getUnit(int id)
{
	return &units[id];
}

















CUnit* CArmy::getUnitByType(int tmp)
{
	for (int a = 0; a < units.size(); a++)
	{
		if (units[a].getType() == tmp)return &units[a];
	}

	units.push_back(unitTemplates[tmp / 6][tmp % 6]);
	return &units[units.size() - 1];
}


void CArmy::deleteUnits(CUnit* u, float count)
{
	u->addStat("count", -count);

	if (u->getStat("count") <= 0)

		for (int a = 0; a < units.size(); a++)
		{
			if (units[a].getType() == u->getType()) { units.erase(units.begin() + a); return; }
		}

}

void CArmy::addUnit(CUnit*u)
{
	CUnit*type = getUnitByType(u->getType());
	float morale = (type->getStat("morale")*type->getStat("count") + u->getStat("morale")*u->getStat("count"));
	type->addStat("count", u->getStat("count"));
	type->setStat("morale", morale / type->getStat("count"));

}


int CArmy::getRoadId()
{

	for (int a = 0; a < mapRoads.size(); a++)
	{
		if (mapRoads[a].exist && clan::LineMath::closest_point(Pointf(Pointf(getPosition())), Pointf(getMap()->getTown(mapRoads[a].town1)->getCenter()), Pointf(getMap()->getTown(mapRoads[a].town2)->getCenter())).distance(Pointf(getPosition())) < 9)
			return a;

	}
	return roadId;
}



bool compareArmyByPosition(int a1, int a2)
{
	return getMap()->getArmy(a1)->getPosition().y < getMap()->getArmy(a2)->getPosition().y;
}


float CArmy::getMorale()
{
	float morale = 0, c = 0;
	for (int a = 0; a < units.size(); a++)
		c += units[a].getStat("count"), morale += units[a].getStat("morale")*units[a].getStat("count");

	return morale / c;
}

float CArmy::getSpeed()
{


	return 80 * ONE_HOUR;
}

float CArmy::getCount()
{
	float  c = 0;
	for (int a = 0; a < units.size(); a++)
		c += units[a].getStat("count");

	return c;
}


void CArmy::mergeWith(CArmy* army)
{

	for (int a = 0; a < army->getUnitsCount(); a++)
	{
		addUnit(army->getUnit(a));
	}
	army->deleteArmy();
}