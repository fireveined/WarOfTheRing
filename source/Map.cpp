#include "Map.h"
#include "common/tokenizer.h"
#include "device.h"
#include "resmanager.h"
#include "Effect.h"
#include "gameplay.h"
#include "common/tokenizer.h"
#include <algorithm>

Point neighbours[4] = { Point(1,0), Point(0,1), Point(-1,0), Point(0,-1) };

void sPreRender::init(int w, int h)
{
	Texture2D MapTexture = Texture2D(GetGC(), w, h);
	image = Image(MapTexture, Size(w, h));
	framebuffer = FrameBuffer(GetGC());
	framebuffer.attach_color(0, MapTexture);
	canvas = Canvas(GetGC(), framebuffer);
}

int scrollMoveX, scrollMoveY = 0;

std::vector<int> armiesInPoint;

bool CMap::onInput(const InputEvent &event)
{


	if (event.type == InputEvent::Type::pointer_moved)
	{
		if (isScrolling)
		{
			scrollX -= (event.mouse_pos.x - scrollX2) / mapScale;
			scrollY -= (event.mouse_pos.y - scrollY2) / mapScale;
			scrollX2 = event.mouse_pos.x;
			scrollY2 = event.mouse_pos.y;
			if (scrollX < 0)scrollX = 0;
			if (scrollX > realWidth - getScreenSize().width / mapScale)scrollX = realWidth - getScreenSize().width / mapScale;
			if (scrollY > realHeight - getScreenSize().height / mapScale)scrollY = realHeight - getScreenSize().height / mapScale;
			if (scrollY < 0)scrollY = 0;
		}

	}

	if (event.type == InputEvent::Type::pressed && event.id == mouse_left)
	{
		isScrolling = 1;
		scrollX2 = event.mouse_pos.x;
		scrollY2 = event.mouse_pos.y;
		scrollMoveX = scrollX2;
		scrollMoveY = scrollY2;

	}


	if (!KeyPress(mouse_left))isScrolling = 0;


	CRegion* selectedRegion = 0;
	if (event.type == InputEvent::Type::released && event.id == mouse_left && !isArmyMoving())
	{

		if (Rect(scrollMoveX - 5, scrollMoveY - 5, Size(10, 10)).contains(event.mouse_pos))
		{
			float mx = min(max(getMouseX()*0.15, 0), regionsImagePB.get_width() - 1);
			float my = max(getMouseY()*0.15, 0);
			Color pixel = regionsImagePB.get_pixel(max((int)mx, 0), min((int)my, regionsImagePB.get_height() - 1));

			if (pixel.g == 255 && pixel.b % 5 == 0 && pixel.r - 1 < regions.size())
				setSelectedObject(&regions[pixel.r - 1]), selectedRegion = &regions[pixel.r - 1];
		}

		isScrolling = 0;
	}


	if (event.type == InputEvent::Type::released && event.id == mouse_left && Rect(scrollMoveX - 5, scrollMoveY - 5, Size(10, 10)).contains(event.mouse_pos) && !isArmyMoving())
		for (int a = 0; a < mapRoads.size(); a++)
		{
			if (mapRoads[a].exist && clan::LineMath::closest_point(Pointf(Pointf(getMouseX(), getMouseY())), Pointf(towns[mapRoads[a].town1].getCenter()), Pointf(towns[mapRoads[a].town2].getCenter())).distance(Pointf(getMouseX(), getMouseY())) < 6)
				setSelectedObject(&mapRoads[a]);

		}

	bool townSelected = 0;


	for (int a = 0; a < towns.size(); a++)
	{
		if (towns[a].ifExitst() && towns[a].getPosition().contains(Point(getMouseX(), getMouseY())))
		{
			if ((event.type == InputEvent::Type::released || event.type == InputEvent::Type::doubleclick) && event.id == mouse_left && Rect(scrollMoveX - 5, scrollMoveY - 5, Size(10, 10)).contains(event.mouse_pos) && !isArmyMoving())
			{
				getArmiesInPoint(towns[a].getCenter(), 30, 1);

				if (event.type == InputEvent::Type::doubleclick)
					armyMove = armiesInPoint[0];
				setSelectedObject(&towns[a]);
				townSelected = 1;
			}
			towns[a].onInput(event);

		}

	}

	if (!townSelected)
		for (int a = 0; a < armies.size(); a++)
		{
			if (armies[a].ifExitst() && armies[a].getVisibleArea().contains(Point(getMouseX(), getMouseY())))
			{
				if ((event.type == InputEvent::Type::released || event.type == InputEvent::Type::doubleclick) && event.id == mouse_left && Rect(scrollMoveX - 5, scrollMoveY - 5, Size(10, 10)).contains(event.mouse_pos) && !isArmyMoving())
				{
					if (event.type == InputEvent::Type::doubleclick)
						armyMove = a;

					getArmiesInPoint(armies[a].getPosition(), 20, 1);
					setSelectedObject(&armies[a]);

				}
				if (armies[a].onInput(event))
					return 1;
			}

		}



	if (event.type == InputEvent::Type::released && event.id == mouse_right)
		setSelectedObject(0);


	//ŒCIE¯KA DLA ARMI
	int dis[2] = { 99999,99999 };
	if (isArmyMoving())
		for (int a = 0; a < mapRoads.size(); a++)
		{
			Point p = clan::LineMath::closest_point(Pointf(Pointf(getMouseX(), getMouseY())), Pointf(towns[mapRoads[a].town1].getCenter()), Pointf(towns[mapRoads[a].town2].getCenter()));
			int disz = p.distance(Pointf(getMouseX(), getMouseY()));
			if (mapRoads[a].exist &&  disz < dis[0])
			{
				if (event.type == InputEvent::Type::released && event.id == mouse_left && Rect(scrollMoveX - 5, scrollMoveY - 5, Size(10, 10)).contains(event.mouse_pos))
				{

					armies[armyMove].way = armyWay;
					armies[armyMove].aimPoint = armyMovePoint;
					armies[armyMove].wayPassed = wayLength;

					armyMove = -1;
					a = 999999;
				}
				else
					wayLength = getShortestWay(armies[armyMove].getRoadId(), armies[armyMove].getPosition(), a, p, armyWay);

				dis[0] = disz;
				dis[1] = a;
				armyMovePoint = p;
			}

		}


	return 0;
}




Point searchPos;
int searchRad;
float checkTimer = 0;

void CMap::refreshArmiesInPoint()
{
	checkTimer = 99;
}
std::vector<int>*  CMap::getArmiesInPoint(Point pos, int rad, int gen) //pobiera armie wokó³ danego punktu
{

	checkTimer += CTimer::dt;
	if (gen > 0 || checkTimer >= 1.5)
	{
		if (getSelectedObject() && getSelectedObject()->getObjectType() == "army")searchPos = ((CArmy*)getSelectedObject())->getPosition();
		if (pos != Point() && gen == 1)searchPos = pos;
		pos = searchPos;
		if (rad != 0 && gen == 1)searchRad = rad;
		rad = searchRad;

		checkTimer = 0;
		CArmy::getArmiesInPoint(searchPos, searchRad, armiesInPoint);
	}



	return &armiesInPoint;
}


std::vector<int> armyIds;

CMap::CMap()
{

	selectedObject = 0;
	scrollX = 0;
	scrollY = 0;
	realWidth = 6322;
	realHeight = 4281;
	scrollSpeed = 1500;
	mapScale = 3;
	isScrolling = 0;
	drawResources = 1;
	drawRoads = 1;

	gameSpeedMode = 3;
	gameSpeed = 1;

	showArmyWay = -1;
	armyMove = -1;

	CArmy::grid = new int*[realWidth / CArmy::cellW + 2];

	for (int j = 0; j < realWidth / CArmy::cellW + 2; j++)
		CArmy::grid[j] = new int[realHeight / CArmy::cellH + 2];

	for (int j = 0; j < realWidth / CArmy::cellW + 2; j++)
		for (int X = 0; X < realHeight / CArmy::cellW + 2; X++)
			CArmy::grid[j][X] = -1;


	clan::PixelBuffer mainMap("data/map/third_age_map.png");
	largeMapImage = Image(GetGC(), mainMap, Rect(0, 0, mainMap.get_size()));

	zoomPreRender[0].init(realWidth*0.32, realHeight*0.32);
	zoomPreRender[2].init(realWidth, realHeight);
	largeMapImage.draw(zoomPreRender[2].canvas, Rectf(0, 0, Sizef(mainMap.get_size())));
	zoomPreRender[2].image.draw(zoomPreRender[0].canvas, Rectf(0, 0, realWidth*0.32, realHeight*0.32));




	loadDatabase("ghe");
	countries[1].setPlayer();

	armyIds.resize(armies.size());

	redrawRegions();
	gameTime = 0;
}




void CMap::update()
{
	if (KeyPress(keycode_1))mapScale = 1.1;
	if (KeyPress(keycode_2))mapScale = 0.7;
	if (KeyPress(keycode_3))mapScale = 0.32;

	for (int a = 0; a < towns.size(); a++)
	{
		towns[a].update();

	}



	for (int a = 0; a < armies.size(); a++)
	{
		armies[a].update();

	}
	for (int a = 0; a < countries.size(); a++)
	{
		countries[a].update();

	}

	gameTime += CTimer::dt*gameSpeed;

}

float ptak = 0;
// TO DO: zmienic 
float mapModeTimer = 0;
void CMap::draw()
{


	// rysowanie t³a
	drawBackground();



	if (mapScale < 0.42)
		zoomPreRender[0].image.draw(GetGC(), Rectf(scrollX*mapScale, scrollY*mapScale, Sizef(1440, 900)), Rectf(0, 0, 1440, 900));
	else
		zoomPreRender[2].image.draw(GetGC(), Rectf(scrollX, scrollY, Sizef(1440 / mapScale, 900 / mapScale)), Rectf(0, 0, 1440, 900));

	GetGC().set_scale(mapScale, mapScale);
	GetGC().mult_translate(-scrollX, -scrollY);



	float mx = min(max(getMouseX()*0.15, 0), regionsImagePB.get_width() - 1);
	float my = max(getMouseY()*0.15, 0);
	Color pixel = regionsImagePB.get_pixel(max((int)mx, 0), min((int)my, regionsImagePB.get_height() - 1));

	if (drawRoads)
		for (int a = 0; a < mapRoads.size(); a++)
		{
			if (mapRoads[a].exist)
			{
				GetGC().draw_line(Pointf(towns[mapRoads[a].town1].getCenter()), Pointf(towns[mapRoads[a].town2].getCenter()), Colorf::gray);
				GetGC().draw_line(Pointf(towns[mapRoads[a].town1].getCenter()) + Pointf(-1, -1), Pointf(towns[mapRoads[a].town2].getCenter()) + Pointf(-1, -1), Colorf::gray);

				if (mapRoads[a].upgraded)
				{
					GetGC().draw_line(Pointf(towns[mapRoads[a].town1].getCenter()) + Pointf(2, 2), Pointf(towns[mapRoads[a].town2].getCenter()) + Pointf(2, 2), Colorf::gray);
				}
			}

		}

	if (drawRoads)
		if (getSelectedObject() && getSelectedObject()->getObjectType() == "road")
		{
			sRoad town = *((sRoad*)getSelectedObject());
			GetGC().draw_line(Pointf(towns[town.town1].getCenter()), Pointf(towns[town.town2].getCenter()), Colorf::white);
			GetGC().draw_line(Pointf(towns[town.town1].getCenter()) + Pointf(2, 2), Pointf(towns[town.town2].getCenter()) + Pointf(2, 2), Colorf::white);
			GetGC().draw_line(Pointf(towns[town.town1].getCenter()) + Pointf(-1, -1), Pointf(towns[town.town2].getCenter()) + Pointf(-1, -1), Colorf::white);

		}




	for (int a = 0; a < towns.size(); a++)
	{
		if (towns[a].ifExitst())
		{
			towns[a].draw(GetGC());
		}
	}


	if (isArmyMoving() && !mouseOnHud)
	{
		showWay(-1, Colorf(255, 0, 0));
	}
	if (mouseOnHud)
	{
		showWay(showArmyWay, Colorf(122, 122, 122));
	}

	for (int a = 0; a < regions.size(); a++)
	{
		Colorf c = regions[a].getColor();
		if (pixel.g == 255 && pixel.b % 5 == 0 && pixel.r == regions[a].getID() + 1 || regions[a].isSelected())
		{
			//	if(Ket)
			//c.set_alpha(255);
			regionsImage.set_color(Color(min(255, c.r*1.3 * 255), min(255, c.g*1.3 * 255), min(255, c.b*1.3 * 255), c.a * 255));
			//regionsImage.set_color(regions[a].getColor().set_alpha(255));
		}
		else
			regionsImage.set_color(c);

		regionsImage.draw(GetGC(), regions[a].getImage(), regions[a].getPositionReal());

		regionsImage.set_color(Colorf(222, 222, 222, 180));


		if (drawResources)
			GetImage("resources_image").draw(GetGC(), Rect((int)regions[a].getResType() * 30, regions[a].getResAmount() * 30 - 30, Size(30, 30)), Rect(regions[a].getPositionReal().get_center(), Size(30, 30)));
	}


	armyIds.resize(armies.size());
	for (int a = 0; a < armyIds.size(); a++)
		armyIds[a] = a;
	std::sort(armyIds.begin(), armyIds.end(), compareArmyByPosition);

	for (int a = 0; a < armyIds.size(); a++)
	{
		if (armies[armyIds[a]].ifExitst())
		{
			armies[armyIds[a]].draw(GetGC());
		}
	}





	GetImage("village").draw(GetGC(), Rect((int)(ptak / 0.1) % 2, 50, Size(20, 20)), Rect(ptak + 2000, ptak + 2000, Size(20, 20)));

	for (list<CEffect>::iterator it = effects.begin(); it != effects.end(); it++)
	{
		(*it).draw();
	}


	GetGC().set_translate(0, 0);
	GetGC().set_scale(1, 1);

	mouseOnHud = 0;
	//	GetFont("wut").draw_text(GetGC(), 10, 50, "X: "+IntToStr(fields[(int)(scrollX+GetMouseX())/10][(int)(scrollY+GetMouseY())/10].deformant*10), Colorf::white);

}

