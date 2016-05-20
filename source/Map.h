#ifndef TOOLTIP_H_INCLUDED
#define TOOLTIP_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "gui/gui_component.h"
#include <list>
#include "region.h"
#include "country.h"
#include "army.h"
#include "common\Timer.h"

struct sPreRender
{
		Image image;
	FrameBuffer framebuffer;
	Canvas canvas;
	sPreRender(){};
	void init(int w, int h);
};

const double ONE_HOUR = 1.0/4.0;
const double ONE_WEEK = 168*ONE_HOUR;
class CMap
{
	int width, height;
	int realWidth, realHeight;
	float scrollX, scrollY, scrollTimer, scrollSpeed;
	int scrollX2, scrollY2;
	bool isScrolling;
	float mapScale, scaleSpeed;
	

	double gameSpeed;

	Image largeMapImage;

	std::vector<CTown> towns;
	std::vector<CRegion> regions;
	std::vector<CCountry> countries;
	std::vector<CArmy> armies;

	Image regionsImage;
	clan::PixelBuffer regionsImagePB;

	sPreRender zoomPreRender[3];

	CObject* selectedObject;

	bool drawResources;
	bool drawRoads;

	eMapDrawMode drawMode;

	double gameTime;
	
	int gameSpeedMode;

	
	Point armyMovePoint;


public:

	std::vector<int> armyWay;
	void showWay(int army, Colorf col);

	bool mouseOnHud;
	int showArmyWay;
int armyMove;
int wayLength;
bool isArmyMoving(){return armyMove!=-1;}


	double getGameTime(){return gameTime;}

	void changeGameSpeed(int s);

	double getGameSpeed(){return gameSpeed;};
	void setGameSpeed(double s){gameSpeed=s;}
	int addTown(CTown t);

	void changeMapDrawMode(eMapDrawMode d);

	void invertDrawResources(){drawResources=!drawResources;};
	void invertDrawRoads(){drawRoads=!drawRoads;};

	CMap();

	double getDeltaTime()
	{
		return CTimer::dt*getGameSpeed();
	}

	CObject* getSelectedObject()
	{
		return selectedObject;
	}

	CArmy* addArmy(Point pos, int owner);
	void zoom(int scale);

		void setSelectedObject(CObject* o)
	{
		if(selectedObject!=0)
			selectedObject->setSelected(0);
		selectedObject=o;
		if(o!=0)
		selectedObject->setSelected(1);
	}
	std::vector<CRegion>* getRegions(){return &regions;}

	std::vector<CTown>* getTowns(){return &towns;}

	std::vector<CCountry>* getCountries(){return &countries;}
		std::vector<CArmy>* getArmies(){return &armies;}

			std::vector<int>*  getArmiesInPoint(Point pos=Point(), int rad=0,  int gen=0);

		CTown* getTown(int id)
		{
			return &towns[id];
		}

				CArmy* getArmy(int id)
		{
			return &armies[id];
		}

				CCountry* getCountry(int id)
		{
			return &countries[id];
		}

				CCountry* getPlayer()
				{
					return &countries[1];
				}

				CRegion* getRegion(int id)
		{
			return &regions[id];
		}

	void update();
	void draw();
	
	void refreshArmiesInPoint(); 

	void redrawStaticObjects();

	void redrawRegions(); 

	 bool onInput(const InputEvent &event);

 	void onClick(CGUIComponent* c, int key){};
	void onHover(CGUIComponent* c, int key){};
	void onPress(CGUIComponent* c, int key){};
	
	void saveMap(string name);
	void loadMap(string name);
	void loadDatabase(string name);

	void drawBackground();

	float getScrollX(){return scrollX;}
	float getScrollY(){return scrollY;}

	float getScale(){return mapScale;}

	void setScroll(float x, float y);

	int getWidth(){return width;}
	int getHeight(){return height;}

	float getMouseX();
	float getMouseY();

};

#endif