#include "Map.h"
#include "common/tokenizer.h"
#include "device.h"
#include "resmanager.h"
#include "Effect.h"
#include "gameplay.h"
#include "common/tokenizer.h"
#include <algorithm>

void CMap::showWay(int army, Colorf col)
{
	if(army==-1 && !isArmyMoving())return;
	std::vector<int>& way = armyWay;
		Point aim=armyMovePoint;

	if(army!=-1)
		way=armies[army].way, aim=armies[army].aimPoint;
	else
	army=armyMove;

		for(int a=0;a<way.size()+1;a++)
		{

	
			Pointf p1,p2;

			if(a==0)
				p1=Pointf(aim);
			else
			p1=Pointf(towns[way[a-1]].getCenter());

			if(a==armyWay.size())
				p2=Pointf(getArmy(army)->getPosition());
			else
			p2=Pointf(towns[way[a]].getCenter());

					GetGC().draw_line(p1, p2, col);
		GetGC().draw_line(p1+Pointf(2,2), p2+Pointf(2,2), col);
		GetGC().draw_line(p1+Pointf(-1,-1), p2+Pointf(-1,-1), col);

						if(a==way.size())
GetGC().fill_circle(p2, 12, col);
				
		}
}


	void CMap::changeGameSpeed(int g)
	{

		if(g>0 && gameSpeedMode>1)
		gameSpeedMode--;
	
		if(g<0 && gameSpeedMode<5)
		gameSpeedMode++;

		if(gameSpeedMode==1)gameSpeed=0.25;
		if(gameSpeedMode==2)gameSpeed=0.5;
		if(gameSpeedMode==3)gameSpeed=1;
		if(gameSpeedMode==4)gameSpeed=2;
		if(gameSpeedMode==5)gameSpeed=4;

	}

void CMap::zoom(int scale)
{
	if(scale==1)mapScale+=0.25;
	if(scale==-1)mapScale-=0.25;
	if(mapScale>1.15)mapScale=1.15;
	if(mapScale<0.5)mapScale=0.5;

}


int CMap::addTown(CTown t)
{

	int reg=t.getRegion();


	regions[reg].addTown(t.getID());
	towns.push_back(t);
	return towns.size()-1;
}

CArmy* CMap::addArmy(Point p, int ow)
{

		armies.push_back(CArmy(armies.size(), p,  ow));
	return &armies[armies.size()-1];
}


void CMap::changeMapDrawMode(eMapDrawMode d)
{
	drawMode=d;

	float max=0;
	for(int a=0;a<regions.size();a++)
	{
		if(d==eMapDrawMode::population)
			if(regions[a].getStat("population")>max)max=regions[a].getStat("population");

				if(d==eMapDrawMode::basePoints)
			if(regions[a].getBasePoints()>max)max=regions[a].getBasePoints();
	}

	for(int a=0;a<regions.size();a++)
	{
		regions[a].updateColor(d, max);
	}

}


float CMap::getMouseX()
{
	return scrollX+GetMouseX()/mapScale;
}

float CMap::getMouseY()
{
	return scrollY+GetMouseY()/mapScale;
}

void CMap::redrawRegions()
{
	/*
	regionsCanvas.clear(Colorf(30,30,30,0));

	for(int a=0;a<regions.size();a++)
	{

	if(pixel.r==a+1 && pixel.g==255 && (int)(pixel.b)%5==0)
	{


	regionsImage.set_color(Colorf(255,255,255,255));
	}

	BlendStateDescription desc;
	desc.set_blend_function(blend_one , blend_zero, blend_one, blend_zero);
	//regionsCanvas.set_blend_state(BlendState(GetGC(), desc));

	regionsImage.draw(regionsCanvas, regions[a].getImage(),regions[a].getPosition());


	regionsCanvas.reset_blend_state();



	//	GetGC().reset_blend_state();
	//regionsImage.set_color(Colorf(255,255,255,185));
	}

	*/
}

void CMap::redrawStaticObjects()
{


}


void CMap::drawBackground()
{


}


void CMap::setScroll(float x, float y)
{
	scrollX=max(min(x, realWidth-getScreenSize().width/mapScale),0);
	scrollY=max(min(y, realHeight-getScreenSize().height/mapScale),0);
}

