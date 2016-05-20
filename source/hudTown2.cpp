#include "hud.h"
#include "gameplay.h"
#include "device.h"
#include "object.h"
#include "unit.h"

#include "gui/gui_slider.h"
#include "gui/gui_label.h"

void CHUD::initTownHUD()
{



	panelRectScreen=Rect(0, 110, Size(250,676));


	CGUIContainer* cityMan = new ::CGUIContainer("city_man");
	cityMan->setArea(Rect(0,0, Size(250, 600)));
	addChild(cityMan);

	int sy=290, h=45, sx=32;
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider0", Point(sx,sy), 100, 0.5)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider1", Point(sx,sy+h*1), 100, 0.2)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider2", Point(sx,sy+h*2), 100, 0.6)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider3", Point(sx,sy+h*3), 100, 1)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));

	for(int a=0;a<4;a++)
		((CGUISlider*)cityMan->getChild("slider"+IntToStr(a)))->setOnDisable(MakeDelegate(this, &CHUD::onSliderDisable));

	gPos=Point(-8, 102);

	townOrderRect=Rect(35+gPos.x, 430+gPos.y, Size(180,35));


}

double slidersOld[4];

void CHUD::onSliderDisable(CGUIComponent* comp, int f)
{

	getMap()->getSelectedObject()->setStat(comp->getName()+"_disabled", f);
}


void CHUD::onSliderChange(CGUIComponent* comp, float f)
{
	CGUIContainer* cityMan = (CGUIContainer*)getChild("city_man");

	double slidersNew[4];
	CGUISlider* sliders[4];
	for(int a=0;a<4;a++)
	{
		sliders[a]=((CGUISlider*)cityMan->getChild("slider"+IntToStr(a)));
		slidersNew[a]=sliders[a]->getValue();
	}

	double diff=f-slidersOld[comp->getName()[comp->getName().size()-1]-'0'];
	double lack=0;


	for(int a=0;a<4;a++)
		if(sliders[a]!=comp)
		{
			double val=max(min(diff/3+lack, slidersNew[a]), -(1-slidersNew[a]));
			if(sliders[a]->isActive()==0)
				val=0;
			sliders[a]->setValue(slidersNew[a]-val);
			lack+=diff/3-val;

		}
		((CGUISlider*)comp)->setValue(f-lack);
		for(int a=0;a<4;a++)
		{
			slidersOld[a]=sliders[a]->getValue();
			getMap()->getSelectedObject()->setStat("slider"+IntToStr(a)+"_aim", slidersOld[a]);
		}

}

enum eHudMode
{
	military=0,
	managment
};


eHudMode hudMode=eHudMode::managment;

void CHUD::drawTownHUD()
{
	//***************************WYSIWETLANIE OPISU MIASTA
	if(getMap()->getSelectedObject() && getMap()->getSelectedObject()->getObjectType()=="town") 
	{
		CGUIContainer* cityMan = (CGUIContainer*)getChild("city_man");
		cityMan->setVisible(1);


		CTown* town = ((CTown*)getMap()->getSelectedObject());


		GetImage("gui_atlas").draw(GetGC(), Rect(470, 110, panelRectScreen.get_size()), Rect(gPos, panelRectScreen.get_size()));

		DrawTextCenter("guifont_bold", town->getName(), gPos.x+139, gPos.y+22, Colorf(211,211,211,211) );

		int screen=-1;
		std::vector<string> leftVars;
		std::vector<string> rightVars;

		string strs[4]={"Wojsko: ", "Wydobycie: ", "Rozwój: ", "Zarządzanie: "};
		for(int a=0;a<4;a++)
		{
			if(hudMode==eHudMode::managment)
			{
				((CGUISlider*)cityMan->getChild("slider"+IntToStr(a)))->setVisible(1);
				Point spos=cityMan->getChild("slider"+IntToStr(a))->getPosition();
				Point pos=spos+Point(85, -12);
				int pp=town->getPPOn((eTownSlider)a);
				int ppAim=town->getAimPPOn((eTownSlider)a);
				string aim="";
				if(pp!=ppAim)aim="("+IntToStr(ppAim)+")";
				::DrawTextCenter("guifont_bold", strs[a]+IntToStr(pp)+aim, pos.x, pos.y, Colorf(200,200,200) );

				((CGUISlider*)cityMan->getChild("slider"+IntToStr(a)))->setBarValue(town->getSlider((eTownSlider)a));
				((CGUISlider*)cityMan->getChild("slider"+IntToStr(a)))->setValue(town->getSliderAim((eTownSlider)a));
				((CGUISlider*)cityMan->getChild("slider"+IntToStr(a)))->disable(town->getStat("slider"+IntToStr(a)+"_disabled"));
				slidersOld[a]=town->getSliderAim((eTownSlider)a);

				if (Rect(spos-Point(10,20), Size(190, 45)).contains(Point(GetMouseX(), GetMouseY())))screen=a;
			}
			else
				((CGUISlider*)cityMan->getChild("slider"+IntToStr(a)))->setVisible(0);
		}


		// ******* EKRAN Z JEDNOSTKAMI *********************************************************************************************************
		if(hudMode==eHudMode::military) 
		{


			int ax=gPos.x+37, ay=gPos.y+165, w=64;
			for(int a=0;a<6;a++)
			{
				CUnit unit=CUnit::getUnit(town->getOwner(), a);
				Rect pos=Rect(ax+w*(a%3), ay+96*(a/3), Size(60,90));
				GetImage("units").draw(GetGC(), unit.getIconImage(),pos);

				Rect disR=Rect(ax-2+(a%3)*w, ay+96*(a/3)-3, Size(w, 96));
				if(disR.contains(Point(GetMouseX(), GetMouseY())))
				{			
					setTooltipText("#font_bold "+unit.name+" #font_def #col_red ("+unit.getUnitTypeString()+") #br #col_white "+unit.describe, 0.3);
					GetGC().fill_rect(pos, Colorf(255,255,255,80));
					screen=999;

					leftVars.push_back("Nazwa:");
					leftVars.push_back("Czas:");
					leftVars.push_back("Morale:");
					leftVars.push_back("Koszt:");

					rightVars.push_back(unit.name);
					rightVars.push_back(FloatToStr(int(unit.getStat("trainingTime")/town->getAttrib("trainingTime")*10)/10.0f)+"("+FloatToStr(unit.getStat("trainingTime"))+") dni");
					rightVars.push_back(FloatToStr(int(unit.getStat("baseMorale")*town->getAttrib("baseMorale")))+"("+FloatToStr(unit.getStat("baseMorale"))+") %");
					rightVars.push_back("100 szt.");

					if(KeyDown(mouse_left) && DoubleClick() && ((CTown*)getMap()->getSelectedObject())->townOrders.size()<6)
					{
						sTownOrder ord;
						ord.morale=0, ord.unit=a;
						ord.start=getMap()->getGameTime();
						ord.progress=0;
						ord.cost=ONE_HOUR*unit.getStat("trainingTime")*24;
						((CTown*)getMap()->getSelectedObject())->townOrders.push_back(ord);
					}

				}

				GetImage("gui_atlas").draw(GetGC(), Rect(1, 260, Size(w,96)), disR);

			}



		}


		string buildings[3]={"fortyfications",  "barracks", "upgrade"};
		for(int a=0;a<3;a++)
		{

			Point pos=Point(90+55*a, 393)+gPos;
			drawStyledText("guifont", pos, IntToStr(town->getStat(buildings[a])), 2);

			if(a==(int)hudMode+1)
				GetGC().fill_rect(Rect(Point(41+56*a, 373)+gPos, Size(57,28)), Colorf(255,255,255,15));

			if(Rect(Point(41+56*a, 373)+gPos, Size(57,34)).contains(getMousePos()))
			{
				GetGC().fill_rect(Rect(Point(41+56*a, 373)+gPos, Size(57,28)), Colorf(255,255,255,15));
				screen=4+a;
				if(KeyDown(mouse_left))
				{
					if(a==1)hudMode=eHudMode::military;
					if(a==2)hudMode=eHudMode::managment;
				}

							string str;
				for(int z=5;z<9;z++)
				{

					if(z!=6)
					{
						float cost=town->getResCostFor(a, (eResType)z);
						string trans=TRANS("res"+IntToStr(z));
						trans[0]-='A'-'a';
						if(cost>1)
							str+="#col_red "+IntToStr(cost)+" #col_white "+trans+" #br ";
					}
					if(z==8)z=0;
					if(z==4)z=999;
				}

				str=str.substr(0, str.length()-4);
				setTooltipText(str, 0.05);

				// BUDOWIE W ON INPUCIE
			}

		}





		//******  KOLEJKA BUDOWY

		bool fb=0, fu=0;

		for(int a=0;a<town->townOrders.size();a++)
		{

			Rect rect=townOrderRect;
			rect.translate(Point(0, townOrderRect.get_height()*a));
			sTownOrder ord=town->townOrders[a];

			if(ord.unit==-1 && !fb)
			{
				GetGC().fill_rect(rect, Colorf(0,255,0,50));
				fb=1;
			}

			if(ord.unit!=-1 && !fu)
			{
				GetGC().fill_rect(rect, Colorf(0,255,0,50));
				fu=1;
			}

			string name=TRANS("build"+IntToStr(ord.build));
			if(ord.unit!=-1)name=CUnit::getUnit(town->getOwner(), ord.unit).name;


			GetFont("guifont").draw_text(GetGC(), Pointf(rect.left+10, rect.top+14), name + " ("+IntToStr(ord.progress/ord.cost*100)+"%)", Colorf(222,222,222,222));
			if(ord.unit!=-1)
				GetFont("guifont").draw_text(GetGC(), Pointf(rect.left+10, rect.top+28), sDate::getTime((ord.cost-ord.progress)/town->getAttrib("trainingTime")), Colorf(222,222,222,182));
			else
				GetFont("guifont").draw_text(GetGC(), Pointf(rect.left+10, rect.top+28), sDate::getTime((ord.cost-ord.progress)), Colorf(222,222,222,182));


			if(rect.contains(getMousePos()))
			{
				GetGC().fill_rect(rect, Colorf(255,255,255,20));
				screen=999;

				if(ord.unit!=-1)
					leftVars.push_back("Jednostka:");
				else
					leftVars.push_back("Budowa:");

				leftVars.push_back("Szybkość:");
				leftVars.push_back("Zostało:");


				rightVars.push_back(name);

				if(ord.unit!=-1)
				{
					rightVars.push_back(IntToStr(town->getAttrib("trainingTime")*100)+"%");
					rightVars.push_back(sDate::getTime((ord.cost-ord.progress)/town->getAttrib("trainingTime")));
				}
				else
				{
					rightVars.push_back("66% PP");
					rightVars.push_back(sDate::getTime(ord.cost-ord.progress));
				}


			}
		}






		///***** wyświetlanie panelu na górze


		if(screen<4)
			leftVars.push_back("PP:");

		if(screen==-1) //domyslne informacje o miescie
		{

			leftVars.push_back("W rękach:");
			leftVars.push_back("Morale:");
			leftVars.push_back("Populacja:");

			rightVars.push_back(IntToStr(town->getPoints()));
			rightVars.push_back(getMap()->getCountry(town->getOwner())->getName());
			rightVars.push_back("86% #col_green (+) #col_white");
			rightVars.push_back(IntToStr(town->getAttrib("population")));

			Rect gold(750,110, Size(20,20));
			Rect dis(gPos.x+216, gPos.y+48, Size(24,24));
			if(dis.contains(getMousePos()))
			{

				GetGC().fill_circle(Pointf(dis.get_center()),  15, Gradient(Colorf(255,255,255,80), Colorf(255,255,255,0)));
				string str;
				for(int a=5;a<9;a++)
				{

					if(a!=6)
					{
						float inc=town->getResIncome((eResType)a);
						float use=town->getResUse((eResType)a);
						string trans=TRANS("res"+IntToStr(a));
						trans[0]-='A'-'a';
						if(int(inc-use)>1)
							str+="#col_green +"+IntToStr(inc-use)+" #col_white "+trans+" #br ";
						if(int(inc-use)<-1)
							str+="#col_red -"+IntToStr(use-inc)+" #col_white "+trans+" #br ";
					}
					if(a==8)a=0;
					if(a==4)a=999;
				}

				str=str.substr(0, str.length()-4);
				setTooltipText(str, 0.05);
			}	




		}
		else if(screen<4)
			rightVars.push_back(FloatToStr(int(town->getPPOn((eTownSlider)screen)*10)/10.0f));

		if(screen==0) //domyslne informacje o miescie
		{
			leftVars.push_back("Rekrutacja:");
			leftVars.push_back("Morale:");
			rightVars.push_back(IntToStr(town->getAttrib("trainingTime")*100)+"%");
			rightVars.push_back(IntToStr(town->getAttrib("baseMorale")*100)+"%");
		}


		if(screen==1) //domyslne informacje o miescie
		{
			leftVars.push_back("Wydobycie:");
			rightVars.push_back(IntToStr(120)+"%");
		}

		if(screen==2) //domyslne informacje o miescie
		{
			leftVars.push_back("Technologie:");
			rightVars.push_back(IntToStr(120)+"%");
		}

		if(screen==3) //domyslne informacje o miescie
		{
			leftVars.push_back("Zarządzanie:");
			rightVars.push_back(IntToStr(120)+"%");
		}

		if(screen>3 && screen<100)
		{

			leftVars.push_back(TRANS("build"+IntToStr(screen-4))+": ");
			rightVars.push_back(IntToStr(town->getStat(buildings[screen-4])));

			if(screen-4==1)
			{
				leftVars.push_back("Rekrutacja:");
			leftVars.push_back("Morale:");
			rightVars.push_back(IntToStr(town->getAttrib("trainingTime")*100)+"%");
			rightVars.push_back(IntToStr(town->getAttrib("baseMorale")*100)+"%");
			}

		}

		string leftV="";
		for(int a=0;a<leftVars.size();a++)
			leftV+=leftVars[a]+" #br ";
		drawStyledText("guifont", Point(40, gPos.y+68), leftV);

		string rightV="";
		for(int a=0;a<rightVars.size();a++)
			rightV+=rightVars[a]+" #br ";
		drawStyledText("guifont", Point(191, gPos.y+68), rightV, 2);

		//








	}
	else
		getChild("city_man")->setVisible(0);


}
