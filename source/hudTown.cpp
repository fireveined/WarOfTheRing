#include "hud.h"
#include "gameplay.h"
#include "device.h"
#include "object.h"
#include "unit.h"
#include "Highlight.h"
#include "gui/gui_slider.h"
#include "gui/gui_label.h"

void CHUD::initTownHUD()
{



	panelRectScreen = Rect(0, 110, Size(276, 800));


	CGUIContainer* cityMan = new ::CGUIContainer("city_man");
	cityMan->setArea(Rect(0, 0, Size(250, 600)));
	addChild(cityMan);

	gPos = Point(-8, 102);

	int sy = gPos.y + 225, h = 45, sx = 47;
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider0", Point(sx, sy), 100, 0.5)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider1", Point(sx, sy + h * 1), 100, 0.2)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider2", Point(sx, sy + h * 2), 100, 0.6)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));
	((CGUISlider*)cityMan->addChild(new ::CGUISlider("slider3", Point(sx, sy + h * 3), 100, 1)))->setOnChange(MakeDelegate(this, &CHUD::onSliderChange));

	for (int a = 0; a < 4; a++)
		((CGUISlider*)cityMan->getChild("slider" + IntToStr(a)))->setOnDisable(MakeDelegate(this, &CHUD::onSliderDisable));



	townOrderRect = Rect(35 + gPos.x, 463 + gPos.y, Size(206, 48));


}

double slidersOld[4];

void CHUD::onSliderDisable(CGUIComponent* comp, int f)
{

	getMap()->getSelectedObject()->setStat(comp->getName() + "_disabled", f);
}


void CHUD::onSliderChange(CGUIComponent* comp, float f)
{
	CGUIContainer* cityMan = (CGUIContainer*)getChild("city_man");

	double slidersNew[4];
	CGUISlider* sliders[4];
	for (int a = 0; a < 4; a++)
	{
		sliders[a] = ((CGUISlider*)cityMan->getChild("slider" + IntToStr(a)));
		slidersNew[a] = sliders[a]->getValue();
	}

	double diff = f - slidersOld[comp->getName()[comp->getName().size() - 1] - '0'];
	double lack = 0;


	for (int a = 0; a < 4; a++)
		if (sliders[a] != comp)
		{
			double val = max(min(diff / 3 + lack, slidersNew[a]), -(1 - slidersNew[a]));
			if (sliders[a]->isActive() == 0)
				val = 0;
			sliders[a]->setValue(slidersNew[a] - val);
			lack += diff / 3 - val;

		}
	((CGUISlider*)comp)->setValue(f - lack);
	for (int a = 0; a < 4; a++)
	{
		slidersOld[a] = sliders[a]->getValue();
		getMap()->getSelectedObject()->setStat("slider" + IntToStr(a) + "_aim", slidersOld[a]);
	}

}
//IDEA **** rozwój fortyfikacji - budowanie na drogach
enum eHudMode
{
	military = 0,
	managment
};


eHudMode hudMode = eHudMode::managment;

void CHUD::drawTownHUD()
{
	//***************************WYSIWETLANIE OPISU MIASTA
	if (getMap()->getSelectedObject() && getMap()->getSelectedObject()->getObjectType() == "town")
	{
		CGUIContainer* cityMan = (CGUIContainer*)getChild("city_man");
		cityMan->setVisible(1);


		CTown* town = ((CTown*)getMap()->getSelectedObject());


		GetImage("gui_atlas").draw(GetGC(), Rect(470, 110, panelRectScreen.get_size()), Rect(gPos, panelRectScreen.get_size()));

		DrawTextCenter("guifont_bold", town->getName(), gPos.x + 139, gPos.y + 22, Colorf(211, 211, 211, 211));

		screen = -1;
		leftVars.clear();
		rightVars.clear();

		//******************************************** SUWAKI ***************************

		string strs[4] = { "Wojsko: ", "Wydobycie: ", "Rozwoj: ", "Zarzadzanie: " };
		for (int a = 0; a < 4; a++)
		{
			if (hudMode == eHudMode::managment)
			{
				((CGUISlider*)cityMan->getChild("slider" + IntToStr(a)))->setVisible(1);
				Point spos = cityMan->getChild("slider" + IntToStr(a))->getPosition();
				Point pos = spos + Point(85, -12);
				int pp = town->getPPOn((eTownSlider)a);
				int ppAim = town->getAimPPOn((eTownSlider)a);
				string aim = "";
				if (pp != ppAim)aim = "(" + IntToStr(ppAim) + ")";
				::DrawTextCenter("h1", strs[a] + IntToStr(pp) + aim, pos.x, pos.y, Colorf(200, 200, 200));

				((CGUISlider*)cityMan->getChild("slider" + IntToStr(a)))->setBarValue(town->getSlider((eTownSlider)a));
				((CGUISlider*)cityMan->getChild("slider" + IntToStr(a)))->setValue(town->getSliderAim((eTownSlider)a));
				((CGUISlider*)cityMan->getChild("slider" + IntToStr(a)))->disable(town->getStat("slider" + IntToStr(a) + "_disabled"));
				slidersOld[a] = town->getSliderAim((eTownSlider)a);

				if (Rect(spos - Point(10, 20), Size(190, 45)).contains(Point(GetMouseX(), GetMouseY())))screen = a;
			}
			else
				((CGUISlider*)cityMan->getChild("slider" + IntToStr(a)))->setVisible(0);
		}


		// ******* EKRAN Z JEDNOSTKAMI *********************************************************************************************************
		if (hudMode == eHudMode::military)
		{


			int ax = gPos.x + 37, ay = gPos.y + 210, w = 64;
			for (int a = 0; a < 6; a++)
			{
				CUnit unit = CUnit::getUnit(town->getOwner(), a);
				Rect pos = Rect(ax + w*(a % 3), ay + 96 * (a / 3), Size(60, 90));
				GetImage("units").draw(GetGC(), unit.getIconImage(), pos);

				Rect disR = Rect(ax - 2 + (a % 3)*w, ay + 96 * (a / 3) - 3, Size(w, 96));
				if (makeHighlight(disR))
				{

					string str;
					str = "#font_bold " + CUnit::getUnit(town->getOwner(), a).name + " #font_def  #col_green (" + unit.getUnitTypeString() + ")  #br #line #col_white  ";

					str += " #icon:1 #font_boldd " + sDate::getTime(unit.costs[(int)RES_TIME] / town->getAttrib("trainingTime")) + " #font_def #setx:100  ";
					str += " #icon:0 #font_bolxd " + FloatToStr(int(unit.getStat("baseMorale")*town->getAttrib("baseMorale"))) + " % #font_def  #br  ";
					int licz = 0;
					for (int z = 5; z < 9; z++)
					{
						if (z != 6)
						{

							float cost = unit.costs[z];
							string trans = resToStr(z);
							trans[0] -= 'A' - 'a';
							if (cost > 1)
							{
								licz++;
								if (licz == 1)str += " #line ";
								str += "  #col_red  " + IntToStr(cost) + " #col_white " + trans + "  #br ";
								//	if(licz%2==1)
									//	str+=" #setx:"+IntToStr(100)+" ";
									//else str+=" #br ";
							}
						}
						if (z == 8)z = 0;
						if (z == 4)z = 999;
					}

					str = str.substr(0, str.length() - 4);
					setTooltipText(str, 0.05, 190);

					//GetGC().fill_rect(pos, Colorf(255,255,255,80));

					if (KeyDown(mouse_left) && DoubleClick() && ((CTown*)getMap()->getSelectedObject())->townOrders.size() < 6)
					{
						sTownOrder ord;
						ord.morale = 0, ord.unit = a;
						ord.start = getMap()->getGameTime();
						ord.progress = 0;
						for (int z = 0; z < (int)RES_ALL_NUM; z++)
						{
							ord.costs[z] = unit.costs[z];
						}

						((CTown*)getMap()->getSelectedObject())->townOrders.push_back(ord);
					}

				}

				GetImage("gui_atlas").draw(GetGC(), Rect(1, 260, Size(w, 96)), disR);

			}



		}

		///// **************************** 3 PRZYCIKI BUDYNKÓW*********************************8

		buildInQueue[0] = 0;
		buildInQueue[1] = 0;
		buildInQueue[2] = 0;

		string buildings[3] = { "fortyfications",  "barracks", "upgrade" };
		for (int a = 0; a < 3; a++)
		{

			Point pos = Point(24, 154) + gPos;
			int w = 76, h = 28;
			Rect header(panelRectScreen.get_width() / 2 + gPos.x - 130 / 2, gPos.y + 150, Size(130, 30));
			Point tpos = Point(pos.x + w - w*0.18 + w*a, pos.y + 20);
			drawStyledText("guifont", tpos, IntToStr(town->getStat(buildings[a])), 2);


			if (a == (int)hudMode + 1)
			{
				GetGC().fill_rect(Rect(pos + Point(w*a, 0), Size(w, h)), Colorf(255, 255, 255, 25));

				//	GetImage("gui_atlas").draw(GetGC(), Rect(pos-Point(2,2),  Size(w+4,h+4)), Rect(pos-Point(2,2),  Size(w+4,h+4)));
			}

			if (makeHighlight(Rect(pos + Point(w*a, 0), Size(w, h))))
			{

				screen = 4 + a;
				if (KeyDown(mouse_left))
				{
					if (a == 1)hudMode = eHudMode::military;
					if (a == 2)hudMode = eHudMode::managment;
				}

				// tooltip z kosztami budowy
				string str = "#font_bold " + TRANS("build" + IntToStr(a)) + " #font_def #br ";
				str += sDate::getTime(town->getResCostFor(a, RES_TIME)) + " #br ";
				str += IntToStr(town->getResCostFor(a, RES_PP) * 100) + "% PP #br ";

				for (int z = 5; z < 9; z++)
				{
					if (z != 6)
					{
						float cost = town->getResCostFor(a, (eResType)z);
						string trans = resToStr(z);
						trans[0] -= 'A' - 'a';
						if (cost > 1)
							str += "#col_red " + IntToStr(cost) + " #col_white " + trans + " #br ";
					}
					if (z == 8)z = 0;
					if (z == 4)z = 999;
				}

				str = str.substr(0, str.length() - 4);
				setTooltipText(str, 0.05);

				// BUDOWIE W ON INPUCIE
			}

		}





		//******  KOLEJKA BUDOWY

		bool fb = 0, fu = 0;
		float timeB = 0, timeU = 0;
		bool erased = 0;
		for (int a = 0; a < town->townOrders.size(); a++)
		{

			Rect rect = townOrderRect;
			rect.translate(Point(0, townOrderRect.get_height()*a));
			sTownOrder ord = town->townOrders[a];


			//podswietlanie
			if (ord.unit == -1 && !fb)
			{
				GetGC().fill_rect(rect, Colorf(0, 255, 0, 50));
				fb = 1;
			}

			if (ord.unit != -1 && !fu)
			{
				GetGC().fill_rect(rect, Colorf(0, 255, 0, 50));
				fu = 1;
			}

			if (rect.contains(getMousePos()))
			{
				GetGC().fill_rect(rect, Colorf(255, 255, 255, 20));
			}


			float time;
			if (ord.unit != -1)
			{
				time = (ord.costs[(int)RES_TIME] - ord.progress) / town->getAttrib("trainingTime");
				timeU += time;
				time = timeU;
			}
			else
			{
				time = (ord.costs[(int)RES_TIME] - ord.progress);
				timeB += time;
				time = timeB;
				buildInQueue[ord.build]++;
			}


			string name = TRANS("build" + IntToStr(ord.build));
			if (ord.unit != -1)name = CUnit::getUnit(town->getOwner(), ord.unit).name;


			GetFont("guifont_big_bold").draw_text(GetGC(), Pointf(rect.left + 10, rect.top + 16), name + " (" + IntToStr(ord.progress / ord.costs[(int)RES_TIME] * 100) + "%)", Colorf(222, 222, 222, 222));
			GetFont("guifont_big").draw_text(GetGC(), Pointf(rect.left + 10, rect.top + 35), sDate::getTime(time), Colorf(222, 222, 222, 182));


			// ANULUJ BUDOWE BUTTON
			Rect but(840, 140, Size(20, 20));
			Rect dis(rect.right - 28 - 25, rect.top + 15, Size(20, 20));
			GetImage("gui_atlas").draw(GetGC(), but, dis);
			if (makeHighlight(dis.get_center(), 14) && !erased)
			{

				if (KeyDown(mouse_left))
				{
					erased = 1;
					town->townOrders.erase(town->townOrders.begin() + a); a--; if (a == -1)a = 0;
				}

			}

			//INFORMACJE O KOSZTACH
			Rect gold(840, 110, Size(24, 24));
			dis = Rect(rect.right - 28, rect.top + 15, Size(24, 24));
			GetImage("gui_atlas").draw(GetGC(), gold, dis);
			if (makeHighlight(dis.get_center(), 14) && !erased)
			{


				// tooltip z kosztami budowy
				string str;

				if (ord.unit == -1)
				{
					str = "#font_bold " + TRANS("build" + IntToStr(a)) + " #font_def #br ";
					str += IntToStr(ord.costs[(int)RES_PP] * 100) + "% PP #br ";
				}
				else
				{
					str = "#font_bold " + CUnit::getUnit(town->getOwner(), ord.unit).name + " #font_def #br ";
				}

				float t = (ord.costs[(int)RES_TIME] - ord.progress) / town->getAttrib("trainingTime");
				if (ord.unit == -1)t = (ord.costs[(int)RES_TIME] - ord.progress);
				str += sDate::getTime(t) + " #br ";

				for (int z = 5; z < 9; z++)
				{
					if (z != 6)
					{
						float cost = ord.costs[z];
						string trans = resToStr(z);
						trans[0] -= 'A' - 'a';
						if (cost > 1)
							str += "#col_red " + IntToStr(cost) + " #col_white " + trans + " #br ";
					}
					if (z == 8)z = 0;
					if (z == 4)z = 999;
				}

				str = str.substr(0, str.length() - 4);
				setTooltipText(str, 0.05);
			}








		}
		// koniec kolejki budowy



		drawTownHUDTopPanel(town);




	}
	else
		getChild("city_man")->setVisible(0);


}
