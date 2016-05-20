#include "resmanager.h"
#include "region.h"
#include "gameplay.h"


int resToInt(eResType r)
{
	return (int)r;
}
eResType intToRes(int i)
{
	return (eResType)i;
}
string resToStr(int r)
{
	return TRANS("res"+IntToStr(r));
}

bool CRegion::onInput(const InputEvent &event)
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


CRegion::CRegion(int i, Rect im, Rect pos, eResType resname, char resnum)
{
	owner=0;
	selected=0;
	objectType="region";
	id=i;
	image=im;
	position=pos;
	resType=resname;
	resAmount=resnum;
	terrain=(eTerrainType)(rand()%6);
	name="Równina";
	setStat("population", rand()%9000+1000);
	updateColor(eMapDrawMode::terrain);
}

void CRegion::updateColor(eMapDrawMode mode, int max)
{

	if(mode==eMapDrawMode::terrain)
	{
		if(terrain==eTerrainType::desert)color=Colorf(243,230,40); 
		else
			if(terrain==eTerrainType::mountains)color=Colorf(122,122,122);
			else
				if(terrain==eTerrainType::marshland)color=Colorf(122,74,0);
				else
					if(terrain==eTerrainType::plain)color=Colorf(204,255,104);
					else
						if(terrain==eTerrainType::forest)color=Colorf(0,124,32); 
						else
							if(terrain==eTerrainType::hills)color=Colorf(150,112,68);
	}

		if(mode==eMapDrawMode::population)
	{
		float dif=getStat("population")/(float)max;
		int r = dif*255;
		int g = dif*255;
		int b = dif*255;
		color=Colorf(r,g,b); 
	}

		if(mode==eMapDrawMode::political)
		{
			color=getMap()->getCountry(owner)->getColor();
		}


				if(mode==eMapDrawMode::basePoints)
	{
		float dif=getBasePoints()/(float)max;
		int r = dif*255;
		int g = dif*255;
		int b = dif*255;
		color=Colorf(r,g,b); 
	}

}

	int CRegion::getBasePoints()
	{
		int bp=0;
		for(int a=0;a<towns.size();a++)
			bp+=getMap()->getTown(towns[a])->getPoints();
		if(bp==0)bp=1;
		return bp;
	}


	void CRegion::checkForOwner()
	{
		int o=getMap()->getTown(towns[0])->getOwner();
		for(int a=0;a<towns.size();a++)
		{
			if(getMap()->getTown(towns[a])->getType()==eTownType::TOWN_CITY) owner=getMap()->getTown(towns[a])->getOwner();
			if(o!=getMap()->getTown(towns[a])->getOwner() && (getMap()->getTown(towns[a])->getType()!=eTownType::TOWN_SPOT))
				return;
		}
		owner=o;
	}


int found=999999;
	void searchWay(int town1id, int rid, Point p2, int length)
	{
		//if(found)return;
		CTown& town=*getMap()->getTown(town1id);
		town.searchId=length;
		
			

		int b1[3]={-1,999999,999999},b2[3]={-1,999999,99999};
		for(int a=0;a<town.roads.size();a++)
		{
			if(town.roads[a]==rid && length<found){found=length;}

			int t=mapRoads[town.roads[a]].town1;
			if(t==town1id)t=mapRoads[town.roads[a]].town2;
		
			int dis=getMap()->getTown(t)->getCenter().distance(town.getCenter());
			int heur=getMap()->getTown(t)->getCenter().distance(p2);
			if(heur<b1[2] && getMap()->getTown(t)->searchId>length+dis)
			{
			if(b1[0]!=-1)
				b2[0]=b1[0], b2[1]=b1[1], b2[2]=b1[2];
			b1[1]=dis, b1[0]=t, b1[2]=heur;
			}

			if(heur<b2[2] && getMap()->getTown(t)->searchId>length+dis)
				 b2[1]=dis, b2[0]=t, b2[2]=heur;
		}

		if(found<length)return;
		if(b1[0]!=-1)
		searchWay(b1[0], rid, p2, length+b1[1]);

		if(b2[0]!=-1)
		searchWay(b2[0], rid, p2, length+b2[1]);
	}

	int getShortestWay(int id1, Point point1, int id2, Point point2,  std::vector<int>& way)
{
	found=99999;
	way.clear();

	int len=0;
	
		for(int a=0;a<getMap()->getTowns()->size();a++)
		getMap()->getTown(a)->searchId=999999;

		int startTown=mapRoads[id1].town1;
		if(getMap()->getTown(mapRoads[id1].town2)->getCenter().distance(point2)+getMap()->getTown(mapRoads[id1].town2)->getCenter().distance(point1) < getMap()->getTown(mapRoads[id1].town1)->getCenter().distance(point2)+getMap()->getTown(mapRoads[id1].town1)->getCenter().distance(point1))
			startTown=mapRoads[id1].town2;

		getMap()->getTown(startTown)->searchId=0;
		searchWay(startTown, id2, point2,0 );

		int endTown=mapRoads[id2].town1;
		if(getMap()->getTown(mapRoads[id2].town2)->getCenter().distance(point2)+getMap()->getTown(mapRoads[id2].town2)->searchId < getMap()->getTown(mapRoads[id2].town1)->getCenter().distance(point2)+getMap()->getTown(mapRoads[id2].town1)->searchId)
		endTown=mapRoads[id2].town2;

		int towni=endTown;
		int z=0;
		if(id1!=id2)
		way.push_back(towni);
		len=getMap()->getTown(towni)->searchId+point2.distance(getMap()->getTown(towni)->getCenter())+point1.distance(getMap()->getTown(startTown)->getCenter());;
		while(startTown!=towni && z<999)
		{
	z++;
			CTown& town=*getMap()->getTown(towni);
			int n=town.getID();
			for(int a=0;a<town.roads.size();a++)
			{
					int t=mapRoads[town.roads[a]].town1;
			if(t==town.getID())t=mapRoads[town.roads[a]].town2;

			if(getMap()->getTown(t)->searchId<getMap()->getTown(n)->searchId)
				n=t, towni=t;
			}
		
			way.push_back(towni);
		}



	return len; 
}

