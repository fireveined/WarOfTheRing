#include "resmanager.h"
#include "town.h"
#include "common/timer.h"
#include "gameplay.h"
#include "army.h"

std::vector<sRoad> mapRoads;

bool CTown::onInput(const InputEvent &event)
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



CTown::CTown(int i, int reg, Point pos, eTownType resname)
{
	owner=0;
	selected=0;
		objectType="town";
	id=i;
	position=Rect(pos,Size(30,30));
	type=resname;
	region=reg;
	name="Miasto";
	smokeTimer=rand()%500/200.0f;

	setStat("got_image", 1);
	setStat("base_points", rand()%100+10);

		setStat("slider0", 0.25);
	setStat("slider1", 0.25);
	setStat("slider2", 0.25);
	setStat("slider3", 0.25);

			setStat("slider0_aim", 0.25);
	setStat("slider1_aim", 0.25);
	setStat("slider2_aim", 0.25);
	setStat("slider3_aim", 0.25);

}

float CTown::getRealPP()
{
	float pp=getPoints();

	for(int a=0;a<townOrders.size();a++)
	{
		if(townOrders[a].unit==-1){

			pp*=(1-townOrders[a].costs[(int)RES_PP]); return pp;
		}
	}
	return pp;
}
		float CTown::getPPOn(eTownSlider s)
	{
		return getSlider(s)*getRealPP();
	}

				float CTown::getAimPPOn(eTownSlider s)
	{
		return getSliderAim(s)*getRealPP();
	}

float CTown::getPoints()
{
	if(type==eTownType::TOWN_CITY)
	{
	return getStat("base_points")*(1+getStat("upgrade")*0.08);
	}
	else
	if(type==eTownType::TOWN_VILLAGE)
	return getStat("base_points")/4;
	else
		return  0;
}

	void CTown::draw(Canvas cv)
	{
		Colorf c=getMap()->getCountry(owner)->getColor();
		c.a=0.3;
		if(getStat("got_image")==1)
			cv.fill_circle(getCenter().x, getCenter().y, position.get_width()/2+2, c);

				if(position.contains(Point(::map->getMouseX(), ::map->getMouseY())) || selected) 
			cv.fill_circle(getCenter().x, getCenter().y, position.get_width()/2+6, Colorf(255,255,255,50));


		if(getStat("got_image")==1)
		GetImage("village").draw(cv, Rect(30*(int)type,0,Size(30,30)), position);

	
		if(type==TOWN_CITY && selected)
		{
				int w=GetFont("small_font").get_text_size(cv, name).width/2;
				cv.fill_rect(Rectf(Pointf(getCenter()+Point(-w-2,30-2-8)), Sizef(w*2+4, 14)), Colorf(20,127,30,60));
			GetFont("small_font").draw_text(cv, Point(getCenter()+Point(-w,30)).x, Point(getCenter()+Point(-w,30)).y, name, Colorf(185,130,14));
		}

			

				int x=position.left+12;
		int y=position.top-5;

			int sx=x+sin(smokeTimer)*4+9;
		int sy=y+sin(smokeTimer)*2;

		Quadf pos(Point(sx,sy), Point(sx+20, y), Point(x+20, y+20), Point(x,y+20));
		if(type!=TOWN_ROAD)
		GetImage("village").draw(cv, Rectf((int)(smokeTimer/0.02)%1*20, 30, Sizef(20,20)), pos);


	}



	void CTown::update()
	{


		smokeTimer+=CTimer::dt*3;

		for(int a=0;a<4;a++)
		{
			if(getSliderAim((eTownSlider)a)>getSlider((eTownSlider)a))
				setStat("slider"+IntToStr(a), getSlider((eTownSlider)a)+0.01*CTimer::dt);

						if(getSliderAim((eTownSlider)a)<getSlider((eTownSlider)a))
				setStat("slider"+IntToStr(a), getSlider((eTownSlider)a)-0.01*CTimer::dt);

		}

		bool fu=0, fb=0;
		for(int a=0;a<townOrders.size();a++)
		{
			double prog=getMap()->getDeltaTime();

				if(townOrders[a].unit==-1)
				{
					if(!fb)
			townOrders[a].progress+=prog, fb=1;
				}
				else if(!fu)
				{
					fu=1;
				townOrders[a].progress+=prog*double(getAttrib("trainingTime"));
				townOrders[a].morale+=getAttrib("baseMorale")*CUnit::getUnit(getOwner(), townOrders[a].unit).getStat("baseMorale")*prog/townOrders[a].costs[(int)RES_TIME];
				}


			if(townOrders[a].progress>townOrders[a].costs[(int)RES_TIME])
			{
				if(townOrders[a].unit==-1)
					addBuild(townOrders[a].build, 1);
				else
				{
					CUnit unit=CUnit::getUnit(getOwner(), townOrders[a].unit);
					unit.setStat("morale", townOrders[a].morale);
					std::vector<int> armies;
					CArmy::getArmiesInPoint(getCenter(), 20, armies);
					CArmy* a;
					if(armies.size()==0)
								a=getMap()->addArmy(getCenter(), getOwner());
					else 
						a=getMap()->getArmy(armies[0]);
					a->addUnit(&unit);

				}


					townOrders.erase(townOrders.begin()+a);a--;
			}
		}

	}



	void CTown::setOwner(int o)
	{

		owner=o;
		getMap()->getRegion(region)->checkForOwner();
		if(type==eTownType::TOWN_CITY)
			getMap()->getRegion(region)->setOwner(owner);
		else
		{
		getMap()->getRegion(region)->checkForOwner();
		}

	}


	float CTown::getAttrib(string str)
	{

		if(str=="trainingTime")return (getPPOn(eTownSlider::army))/100.0f;
		if(str=="moraleDelta")return (getPPOn(eTownSlider::army))/20.0f;
		if(str=="baseMorale")return (getPPOn(eTownSlider::army)/3+70)/100.0f;
		if(str=="population")return getPoints()/getMap()->getRegion(region)->getBasePoints()*getMap()->getRegion(region)->getStat("population");
	}


			float CTown::getResIncome(eResType res)
			{
				float inc=0;
				CRegion* reg=getMap()->getRegion(region);
				if(res==RES_GOLD)inc=getAttrib("population")/500;
				else
					if(reg->getResType()==res)
					{
						inc = reg->getResAmount()*getPPOn(eTownSlider::mining);
					}

					return inc;

			}

	 float CTown::getResUse(eResType res)
	 {
		 float inc=0;
				CRegion* reg=getMap()->getRegion(region);

		 if(res==RES_FOOD)inc=getAttrib("population")/1000;
		 if(res==RES_TIMBER)inc=getAttrib("population")/2000;

		 return inc;
	 }



	 	float CTown::getResCostFor(int build, eResType typ)
		{
			float cost=0;
			if(typ==RES_TIME)
				cost=60*ONE_HOUR+15*getBuild(build);
			else
			if(typ==RES_GOLD)
				cost=30*getBuild(build);
			else
			if(typ==RES_PP)
				cost=0.55+getBuild(build)*0.02;
			else
			if(typ==RES_TIMBER)
				cost=35+getBuild(build)*8;

			return cost;
		}


		float CTown::getResUseOfOrders(eResType r)
		{

			float use=0;
		bool fu=0, fb=0;
		for(int a=0;a<townOrders.size();a++)
		{

				if(townOrders[a].unit==-1)
				{
					if(!fb)
					{
		fb=1;;
		if(townOrders[a].paused==0)
			use+=townOrders[a].costs[(int)r]/townOrders[a].costs[(int)RES_TIME]*ONE_WEEK;
					}

				}
				else if(!fu)
				{

		fu=1;;
		if(townOrders[a].paused==0)
			use+=townOrders[a].costs[(int)r]/townOrders[a].costs[(int)RES_TIME]*ONE_WEEK*getAttrib("trainingTime");
					}	
		if(fu && fb)return use;
		}
		return use;

		}