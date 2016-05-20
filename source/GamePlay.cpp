#include "ResManager.h"
#include "GamePlay.h"
#include "device.h"
#include <iostream>
#include "gui/gui_slider.h"

int leftPanelW = 200;

std::list<CEffect> effects;
CMap* map;
CMap* getMap()
{
	return ::map;
}

void addEffect(CEffect e)
{
	effects.push_back(e);

}
int sliders[4];

CObject* last_sel = 0;

void CGamePlay::Render()
{




	SetCursor("cursor_normal");

	//GetImage("background_universe_game").draw(GetGC(),-getMap()->getScrollX()/11,-getMap()->getScrollY()/11);
	getMap()->draw();



	CObject* selectedObj = getMap()->getSelectedObject();

	if (selectedObj)
	{
		if (selectedObj->getObjectType() == "town")
		{
			CTown town = *((CTown*)selectedObj);
			GetFont("info").draw_text(GetGC(), 30, 100, IntToStr(town.getID()), Colorf::white);



		}

		if (selectedObj->getObjectType() == "region")
		{
			CRegion town = *((CRegion*)selectedObj);

		}

		if (selectedObj->getObjectType() == "road")
		{
			sRoad town = *((sRoad*)selectedObj);

		}



		if (selectedObj->getObjectType() == "army")
		{



		}


	}




}


void CGamePlay::Update()
{
	getMap()->update();

	updateSelection();

	list<CEffect>::iterator it = effects.begin();
	while (it != effects.end())
	{
		if ((*it).isAlive())
		{
			(*it).update();
			it++;
		}
		else
		{
			it = effects.erase(it);
		}
	}


}

void CGamePlay::updateSelection()
{


	last_sel = getMap()->getSelectedObject();
}


void CGamePlay::onInput(const InputEvent &event)
{


	//if(!(event.type==InputEvent::Type::pressed && event.mouse_pos.x<leftPanelW))
	getMap()->onInput(event);

	{

		if (event.type == InputEvent::Type::pointer_moved)
		{

		}

		if (event.type == InputEvent::Type::released && event.id == mouse_left)
		{


		}
		if (event.type == InputEvent::Type::pressed && event.id == mouse_left)
		{



		}

	}


	if (event.type == InputEvent::Type::pressed && event.id == mouse_right)
	{

	}


}

Rect CGamePlay::getSelection()
{
	//	return 	Rect(min(selX, getMap()->getMouseX()), min(selY, getMap()->getMouseY()), max(selX, getMap()->getMouseX()), max(selY, getMap()->getMouseY()));
	return Rect();
}

void CGamePlay::Active()
{

	pause = 0;
	GUI->setVisible(1);	CGUIComponent* g = CGUIManager::GetGUIManager()->getChild("scrimmish");

}


void CGamePlay::Deactive()
{

	GUI->setVisible(0);

}

