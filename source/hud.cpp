#include "hud.h"
#include "gameplay.h"
#include "device.h"
#include "object.h"
#include "unit.h"
#include "Highlight.h"
#include "gui/gui_slider.h"

const int selectionBoxWidth=40;
std::vector<Rect> guiRects;

int selectedArmy=0;
int moveToArmyId=-1;

unsigned char armyCommandNew=0;
unsigned char armyCommandNew2=2;
char armyCommandType=-1;
int sliderW=16;
int unitRectW=63;
CHUD::CHUD()
{


	describeRect=Rect(0, 110, Size(434,125));
	describeRectScreen=Rect(0, 900-110, Size(434,125));

	armyRect=Rect(0, 510, Size(302,125));
	armyRectScreen=Rect(0, 900-110, Size(302,125));

	setArea(Rect(0,0,1440,900));

	initTownHUD();

	CGUIContainer* armyMan = new ::CGUIContainer("army_man");
	armyMan->setArea(Rect(0,700, Size(1400, 200)));
	addChild(armyMan);

	gPos=Point(-8, 102);

	int h=95+21+21+21;
	int sy=900-h, cx=unitRectW+12, sx=armyRect.get_width()+unitRectW;
	for(int a=0;a<10;a++)
		((CGUISlider*)armyMan->addChild(new ::CGUISlider("slider"+IntToStr(a), Point(sx+a*cx,sy), h, 0.5, 1)));//->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));


}


void sDate::init(double time)
{
	unsigned int hours=time/ONE_HOUR;

	day=hours/24;
	month=day/30;
	year=month/12+1;

	hour=hours%24;
	day=day%30+1;
	month=month%12+1;
}

string sDate::get()
{
	string s;
	s=IntToStr(hour)+":00  " + IntToStr(day)+"/"+IntToStr(month)+"/"+IntToStr(year);
	return s;
}

string sDate::diff(double time2)
{

	return "d";
}

string  sDate::getTime(double time, bool onlynum)
{
	float hours=time/ONE_HOUR;
	float day=int((hours/24.0f)*10)/10.0f;
	//int hour=hours%24;
	string s=FloatToStr(day);
	if(onlynum)
		return s;
	return s+" dni ";
}


int lookAtArmy=-1;

void CHUD::draw()
{
	guiRects.clear();

	GetImage("gui_atlas").draw(GetGC(), Rect(0, 0, Size(720,100)), Rect(0, 0, Size(720,100)));

	sDate date(getMap()->getGameTime());



	if(makeHighlight(Point(596,54), 13))
	{
		if(KeyDown(mouse_left))getMap()->changeGameSpeed(1);
	}

	if(makeHighlight(Point(628,54), 13))
	{
		if(KeyDown(mouse_left))getMap()->changeGameSpeed(-1);
	}

	float speed=getMap()->getGameSpeed();
	DrawTextCenter("guifont", date.get()+ " (x"+FloatToStr(speed)+")", 512, 54, Colorf(222,222,222,222));

	int x=0, y=900-122, w=434, h=125;
	Rect imgr=Rect(x+15,y+14, Size(122,98));

	//***************************WYSIWETLANIE OPISU REGIONU
	if(getMap()->getSelectedObject() && getMap()->getSelectedObject()->getObjectType()=="region")
	{
		CRegion* reg = ((CRegion*)getMap()->getSelectedObject());

		GetImage("gui_atlas").draw(GetGC(), describeRect, Rect(x, y, Size(w,h)));

		int tw=GetTextSize("tooltip_bold", reg->getName()).width/2;
		GetFont("tooltip_bold").draw_text(GetGC(), Pointf(x+300-tw, y+24), reg->getName(), Colorf(200,200,200,200));

		GetImage("map_images").draw(GetGC(), Rect(0, 0 ,Size(300,177)), imgr);
		if(makeHighlight(imgr))
			setTooltipText(TRANS("terrain"+IntToStr((int)reg->getTerrain())), 0.1);

		GetImage("flags").set_alpha(0.9);
		Rect flagr(x+15,y+14, Size(50, 30));
		GetImage("flags").draw(GetGC(), Rect(0,110*reg->getOwner() ,Size(180,110)), flagr);
		GetImage("flags").set_alpha(1);
		if(makeHighlight(flagr))
			setTooltipText(TRANS(getMap()->getCountry(reg->getOwner())->getName()), 0.1);




		int tx=x+155, ty=y+60;
		drawStyledText("guifont", Point(tx,ty), TRANS("Region zamieszkuje #font_bold ")+IntToStr(reg->getStat("population"))+" #font_def mieszkańców." );

		string amount[3]={"małe", "duże", "bardzo duże"};
		string res[5]={"zboża", "ryb", "drewna", "kamienia", "żelaza"};
		drawStyledText("guifont", Point(tx,ty+25), TRANS("W regionie znajdują się #font_bold ")+amount[reg->getResAmount()-1]+
			" #font_def złoża #font_bold "+res[(int)reg->getResType()], 0, 260);
	}


	//***************************WYSIWETLANIE OPISU DROGI
	if(getMap()->getSelectedObject() && getMap()->getSelectedObject()->getObjectType()=="road") 
	{
		sRoad* reg = ((sRoad*)getMap()->getSelectedObject());

		GetImage("gui_atlas").draw(GetGC(), describeRect, Rect(x, y, Size(w,h)));

		string s=getMap()->getTown(reg->town1)->getName()+" - "+getMap()->getTown(reg->town2)->getName();
		int tw=GetTextSize("tooltip_bold", s).width/2;
		GetFont("tooltip_bold").draw_text(GetGC(), Pointf(x+300-tw, y+24), s, Colorf(200,200,200,200));

		GetImage("map_images").draw(GetGC(), Rect(0, 176 ,Size(150,100)), imgr);


		int tx=x+155, ty=y+60;
		drawStyledText("guifont", Point(tx,ty), TRANS("Droga ma długość #font_bold ")+IntToStr(reg->length)+" #font_def mil." );

		string upg="nie jest";
		if(reg->upgraded)upg="jest";
		drawStyledText("guifont", Point(tx,ty+25), TRANS("Droga #font_bold ")+upg+" #font_def utwardzana." );

	}

	CGUIContainer* armyMan = (CGUIContainer*)getChild("army_man");
	static int oldFirstArmy = 2 ;
	//***************************WYSIWETLANIE OPISU ARMI
	if(getMap()->getSelectedObject() && (getMap()->getSelectedObject()->getObjectType()=="army" || getMap()->getSelectedObject()->getObjectType()=="town") && getMap()->getArmiesInPoint()->size()>0) 
	{


		std::vector<int> armies= *getMap()->getArmiesInPoint();

		if(armies.size()==0)
			return;
		if(oldFirstArmy!=armies[0] && KeyDown(mouse_left))
			selectedArmy=0;
		oldFirstArmy=armies[0];
		if(selectedArmy>armies.size()-1)
			selectedArmy=armies.size()-1;

		CArmy* army=getMap()->getArmy(armies[selectedArmy]);
		if(lookAtArmy!=-1 && lookAtArmy<armies.size())
			army=getMap()->getArmy(armies[lookAtArmy]);

		if(getMap()->getSelectedObject()->getObjectType()=="town")x=panelRectScreen.right+gPos.x;

		int ax=x+armyRect.get_width(), ay=900-93, cx=unitRectW;

		if(armyCommandType==0)cx+=sliderW;
		guiRects.push_back(Rect(x,y, Size(w+army->getUnitsCount()*cx,h)));
		GetImage("gui_atlas").draw(GetGC(), armyRect, Rect(x, y, Size(armyRect.get_width(),h)));



		


		int tx=x+155-130, ty=y+60;




		//		for(int a=army->getUnitsCount();a<6;a++)
		//GetImage("units").draw(GetGC(), Rect(0,0, Size(60,90)),Rect(ax+cx*a, ay, Size(60,90)));

		for(int a=0;a<10;a++)
			armyMan->getSlider("slider"+IntToStr(a))->setVisible(0);

		for(int a=0;a<army->getUnitsCount();a++)
		{

			GetImage("gui_atlas").draw(GetGC(), Rect(0, 240, Size(66,21)), Rect(ax-3+a*cx, 900-116-21, Size(66,21))); // tło dla morale
			GetImage("gui_atlas").draw(GetGC(), Rect(0, 240, Size(66,21)), Rect(ax-3+a*cx, 900-116, Size(66,21))); // tło dla liczebnosci armi

			Rect pos=Rect(ax+cx*a, ay, Size(60,90));
			GetImage("units").draw(GetGC(), army->getUnit(a)->getIconImage(),pos); //ikonka

			int count=army->getUnit(a)->getStat("count");
			if(armyCommandType!=-1)
				count*=1-armyMan->getSlider("slider"+IntToStr(a))->getValue();
			string t=IntToStr(count);
			DrawTextCenter("guifont", t, pos.get_center().x, pos.top-13, Colorf(192,192,192,205)); // LICZEBNOŚC

			t=	IntToStr(army->getUnit(a)->getStat("morale"))+"%";  
			DrawTextCenter("guifont", t, pos.get_center().x, pos.top-13-21, Colorf(116,252,116,235)); //morale

			if(makeHighlight(pos, Colorf(255,255,255,80)))
			{			

				setTooltipText("#font_bold "+army->getUnit(a)->name+" #font_def #col_red ("+army->getUnit(a)->getUnitTypeString()+") #br #col_white "+army->getUnit(a)->describe, 0.5);
				//	if(KeyDown(mouse_left))army->deleteUnits(army->getUnit(a), 50);
			}

			GetImage("gui_atlas").draw(GetGC(), Rect(0, 240+21, Size(66,116-21)), Rect(ax-3+a*cx, 900-116+21, Size(66,116-21))); //domkniecie


			if(armyCommandType==0)
			{	
				armyMan->getSlider("slider"+IntToStr(a))->setArea(Rect(ax+cx*a+unitRectW, 900-116-42, Size(sliderW, 116+42)));
				armyMan->getSlider("slider"+IntToStr(a))->setVisible(1);

				armyMan->setVisible(1);

				Rect addBut=Rect(ax-3+a*cx, 900-116-42, Size(66,21));
				GetImage("gui_atlas").draw(GetGC(), Rect(0, 240, Size(66,21)), addBut); // tło dla liczebnosci drugiej armi

				string t=	IntToStr(army->getUnit(a)->getStat("count")*armyMan->getSlider("slider"+IntToStr(a))->getValue());
				DrawTextCenter("guifont", t, pos.get_center().x, pos.top-13-42, Colorf(192,192,192,205)); // LICZEBNOŚC2

				//	if(makeHighlight(addBut) && KeyUp(mouse_left))

			}

		}
		// obsluga ikonek armi*******************
		getMap()->showArmyWay=selectedArmy;

		lookAtArmy=-1;

		for(int a=0;a<armies.size();a++)
		{
			int aw=40;
			Point pos=Point(x+30+a*aw, y+70);
			int bold=1;
			Rect r=Rect(pos-Point(11,11), Size(44,49));
			bool cursorOver=makeHighlight(r.get_center(),25, Colorf(255,255,255,90));
			if(cursorOver || a==selectedArmy)
			{
				if(cursorOver)
				{
					lookAtArmy=a;
					getMap()->showArmyWay=a;
					CArmy &army = *getMap()->getArmy(armies[a]);
					//tooltip o armi

					string str="Stan: #setx:100 #font_bold "+IntToStr(army.getCount())+ " #br ";
					str+=" #font_bold Morale: #setx:100 #col_green #font_bold "+IntToStr(army.getMorale())+ " #br ";
					for(int z=5;z<9;z++)
					{
						if(z!=6)
						{
							float cost=army.getResUse((eResType)z);
							if(cost>1)
							str+=" #font_def #br #col_white "+resToStr(z)+": #setx:100 "+" #font_bold #col_red "+IntToStr(cost);
						}
						if(z==8)z=0;
						if(z==4)z=999;
					}
					setTooltipText(str, 0.05);

				}

				//guziki dowodzenia armią też

				if(cursorOver && KeyDown(mouse_left))
				{
					if(armyCommandType==1 && moveToArmyId==-1 && a!=selectedArmy)
					{
						moveToArmyId=a;
						getMap()->getArmy(armies[selectedArmy])->mergeWith(getMap()->getArmy(armies[a]));
						armyCommandType=-1;
					}
					else
					selectedArmy=a, armyCommandType=-1;
					//if(DoubleClick())
					getMap()->refreshArmiesInPoint();
						getMap()->armyMove=armies[a];
				}
				if(selectedArmy==a)
					bold=2;
			}
			getMap()->getArmy(armies[a])->drawShield(GetGC(), pos, bold);
		}


		if(KeyDown(mouse_right)) 	getMap()->armyMove=-1, armyCommandType=-1;
		if(getMap()->isArmyMoving())
		{
			CDevice::GetDevice()->SetCursor("cursor_action");
		}

		//INFORMACJE O ODDZIALE (data dotarcia itd)
		int ar=lookAtArmy;
		if(ar==-1)ar=selectedArmy;
		ar=armies[ar];
		getMap()->showArmyWay=ar;

		float way=getMap()->getArmy(ar)->wayPassed;
	string aim;

	if(getMap()->isArmyMoving())
		{
			way=getMap()->wayLength;
			if(getMap()->armyWay.size()>0)
			aim=getMap()->getRegion(getMap()->getTown(getMap()->armyWay[0])->getRegion())->getName();
		}
		else if(getMap()->getArmy(ar)->way.size()>0)
			aim=getMap()->getRegion(getMap()->getTown(getMap()->getArmy(ar)->way[0])->getRegion())->getName();
		if(way>0)
		{	
	
			float speed=getMap()->getArmy(ar)->getSpeed();

					sDate date(getMap()->getGameTime()+way/speed);
			GetFont("guifont").draw_text(GetGC(), Pointf(x+130, y+80), "W "+aim+" "+date.get(), Colorf(200,200,200,200));
		}


		//OSBLUGA GUZIKÓW DOWODZENIA ARMIĄ

		int bx=33+x, by=33+y;
		int r=13, next=40;

		for(int a=0;a<3;a++)
		{
			if(makeHighlight(Point(bx+next*a,by), r, Colorf(255,255,255,110)))
			{
					if(KeyUp(mouse_left)) 
					{
						for(int a=0;a<10;a++)
							armyMan->getSlider("slider"+IntToStr(a))->setValue(0);
					
					
					}

				if(a==0)
				{ 
					setTooltipText("Podziel oddział", 0.1); 
					if(KeyUp(mouse_left)) 	armyCommandType=0;
				}

				if(a==1)
				{ 
					setTooltipText("Złącz oddziały", 0.1); 
					if(KeyUp(mouse_left)) 	armyCommandType=1, moveToArmyId=-1;
				}

								if(a==2)
				{ 
					setTooltipText("Złącz oddziały", 0.1); 
					if(KeyUp(mouse_left)) 	armyCommandType=2;
				}

			}

		}

		if(armyCommandType!=-1)   
		{
			int xx=x+250, yy=y+28;
			GetImage("gui_atlas").draw(GetGC(), Rect(300, 410, Size(35, 86)), Rect(xx, yy, Size(35, 86)) );

			if(makeHighlight(Point(xx+18, yy+18+50), 18) && KeyUp(mouse_left))
				armyCommandType=-1;

			if(makeHighlight(Point(xx+18, yy+18), 18) && KeyUp(mouse_left))
			{

				if(armyCommandType==0)
				{
					CArmy& narmy=*getMap()->addArmy(army->getPosition(), army->getOwner());
					int num=0;
					for(int a=0;a<army->getUnitsCount();a++)
					{
						CUnit& unit = *army->getUnit(a); 
						int c=unit.getStat("count");
						int nc=c*armyMan->getSlider("slider"+IntToStr(a))->getValue();
						if(nc>0)
						{
							num+=nc;
							narmy.getUnitByType(unit.getType())->setStat("count", nc);
							narmy.getUnitByType(unit.getType())->setStat("morale", unit.getStat("morale"));

							army->deleteUnits(army->getUnit(a), nc);
						}
					}
					if(num==0)narmy.deleteArmy();
				}


				armyCommandType=-1;


			}



		}

	}
	else selectedArmy=0, armyMan->setVisible(0);;



	GetGC().mult_translate(area.get_top_left());

	//**************** obsluga przycisków mapy
	x=274, y=55;
	int r=13, next=32;

	for(int a=0;a<7;a++)
	{
		if(makeHighlight(Point(x+next*a,y), r))
		{

			if(a==0){ if(KeyUp(mouse_left)) getMap()->changeMapDrawMode(eMapDrawMode::political); setTooltipText("Mapa polityczna", 0.2);}
			if(a==1){ if(KeyUp(mouse_left)) getMap()->changeMapDrawMode(eMapDrawMode::terrain); setTooltipText("Mapa terenu", 0.2);}
			if(a==2){ if(KeyUp(mouse_left)) getMap()->changeMapDrawMode(eMapDrawMode::basePoints); setTooltipText("Mapa rozwoju", 0.2);}
			if(a==3){ if(KeyUp(mouse_left)) getMap()->changeMapDrawMode(eMapDrawMode::population); setTooltipText("Mapa populacji", 0.2);}
			if(a==4){ if(KeyUp(mouse_left)) getMap()->zoom(1); setTooltipText("Przybliż", 0.2);}
			if(a==5){ if(KeyUp(mouse_left)) getMap()->zoom(-1); setTooltipText("Oddal", 0.2);}
			if(a==6){ if(KeyUp(mouse_left)) getMap()->invertDrawResources(); setTooltipText("Rysuj ikonki surowców", 0.2);}

		}

	}


	// ************* PASEK SUROWCÓW

	string res[6]={"grain", "fish", "wood", "stone", "iron", "gold"};
	x=200, y=21, next=96;
	CCountry* player=getMap()->getPlayer();

	for(int a=0;a<6;a++)
	{
		int tw=GetTextSize("tooltip_bold", IntToStr(player->getRes((eResType)a))).width;
		GetFont("tooltip_bold").draw_text(GetGC(), Pointf(x+next*a-tw,y), IntToStr(player->getRes((eResType)a)), Colorf(200,200,200,200));

		if(makeHighlight(Rect(113+next*a,6, Size(next, 21))))
		{ 
			float inc=player->getIncome((eResType)a), use=player->getUseOfRes((eResType)a);
			string prefix=" #col_green +";
			if(inc-use<0)prefix=" #col_red -";
			setTooltipText("#font_bold "+TRANS("res"+IntToStr(a))+" #font_def #br #line "+
				TRANS("Przychód")+":  #col_green +"+IntToStr(inc) + "  #br #col_white "+
				TRANS("Wykorzystanie")+":  #col_red -"+IntToStr(use) + " #br #line #col_white "+
				TRANS("Razem")+": "+prefix+IntToStr(inc-use), 0.1);
		}
	}


	drawTownHUD();

	drawChilds();

}

/*
void CHUD::drawBar(Rect r, Colorf c1, Colorf c2, Colorf c3,  float val)
{

GetGC().fill_rect(Rectf(Pointf(r.get_top_left()), Sizef(val*r.get_width(), r.get_height())), Colorf(0,0,0,180));
GetGC().fill_rect(Rectf(Pointf(r.get_top_left()), Sizef(val*r.get_width(), r.get_height())), Gradient(c1, c2));
GetGC().draw_box(r, c3);
//GetGC().draw_box(Rectf(Pointf(r.get_top_left()+Point(1,1)), Sizef(r.get_size()-Size(1,1))), c3);
}

*/

void  CHUD::update()
{


	updateChilds();

	if(hovered)
	{
		animTimer+=CTimer::dt;
	}
	else
	{
		animTimer-=CTimer::dt;
	}




}


bool CHUD::onInput(const InputEvent &event)
{
	onInputChilds(event);


	if(event.type==InputEvent::Type::no_key && event.str=="hover_on") {hovered=1; if(onHover) onHover(this, hovered); }

	if(event.type==InputEvent::Type::no_key && event.str=="hover_off")
	{
		hovered=0; 

		if(onHover) onHover(this, hovered); 
		pressed=0; 

	}

	if(event.type==InputEvent::Type::doubleclick && event.id==mouse_left && getMap()->getSelectedObject() && getMap()->getSelectedObject()->getObjectType()=="town" &&
		((CTown*)getMap()->getSelectedObject())->townOrders.size()<6)
	{
		for(int a=0;a<3;a++)
		{

			if(Rect(Point(41+56*a, 373)+gPos, Size(57,34)).contains(getMousePos()) && buildInQueue[a]==0)
			{

				sTownOrder ord;
				ord.build=a, ord.unit=-1;
				ord.start=getMap()->getGameTime();
				ord.progress=0;
				for(int z=0;z<(int)RES_ALL_NUM;z++)
				{
					ord.costs[z]=((CTown*)getMap()->getSelectedObject())->getResCostFor(a, intToRes(z));
				}

				((CTown*)getMap()->getSelectedObject())->townOrders.push_back(ord);

			}
		}
	}




	if(event.type==InputEvent::Type::pressed && event.id==mouse_left)
	{
		pressed=1; 
		if(onPress)onPress(this, pressed);

	}
	else
		if(event.type==InputEvent::Type::released && (event.id==mouse_left || event.id==mouse_right)) 
		{
			pressed=0; 
			if(onPress)
				onPress(this, pressed); 	
			if(onClick)
				onClick(this, event.id); 

		}


		Point mous=Point(GetMouseX(), GetMouseY());

		bool can=1;
		for(int a=0;a<guiRects.size();a++)
			if(guiRects[a].contains(mous))can=0,a=999;
		//if(GetImage("gui_hud").get_texture().get_texture().get_pixeldata(GetGC(), tf_rgba8).get_pixel(GetMouseX(), max(GetMouseY()-area.top,0)).a>0.8  )
		if((!can || Rect(0, 0, Size(500, 100)).contains(mous) || Rect(500, 0, Size(202, 30)).contains(mous) 
			|| (getMap()->getSelectedObject() && describeRectScreen.contains(mous)) ||
			(getMap()->getSelectedObject() && getMap()->getSelectedObject()->getObjectType()=="town" && panelRectScreen.contains(mous))
			)&& event.type!=InputEvent::Type::pointer_moved)
		{
			getMap()->mouseOnHud=1;
			return true;
		
		}else
			return false;
}
