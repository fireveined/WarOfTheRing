#include "hud.h"
#include "gameplay.h"
#include "device.h"
#include "object.h"
#include "unit.h"
#include "Highlight.h"
#include "gui/gui_slider.h"
#include "gui/gui_label.h"



void CHUD::drawTownHUDTopPanel(CTown*town)
{
	





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
			Rect dis(gPos.x+239, gPos.y+48, Size(24,24));
			if(makeHighlight(dis.get_center(), 14))
			{


				string str="#font_bold Surowce: #font_def #br ";
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
			rightVars.push_back(IntToStr(town->getBuild(screen-4)));

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
		drawStyledText("guifont", Point(gPos.x+33, gPos.y+68), leftV);

		string rightV="";
		for(int a=0;a<rightVars.size();a++)
			rightV+=rightVars[a]+" #br ";
		drawStyledText("guifont", Point(224+gPos.x, gPos.y+68), rightV, 2);

		//



}
