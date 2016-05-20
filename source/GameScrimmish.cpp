#include "GameScrimmish.h"
#include "device.h"
#include "ResManager.h"
#include "gui/gui.h"
#include <algorithm>




	void CGameScrimmish::onClick(CGUIComponent* c, int key)
	{
		if(c->getType()=="slider")
		{
			string s="BARDZO MAŁA";
			if(key>20)s="MAŁA";
			if(key>38)s="ŚREDNIA";
			if(key>62)s="DUŻA";
			if(key>85)s="OGROMNA";
			c->getLabel("label")->setText(s);
		}

		if(c->getType()=="button")
		{

			if(c->getName()=="back")
			{
				Deactive();
				CGameState::SetActState(GAME_MENU);
				CDevice::GetDevice()->GetActGameState()->Active();
			}

			if(c->getName()=="start")
			{
				Deactive();
				CGameState::SetActState(GAME_PLAY);
				CDevice::GetDevice()->GetActGameState()->Active();
			}

		}

	}


void CGameScrimmish::Init()
{
		GUI=new CGUIContainer("scrimmish");
	CGUIManager::GetGUIManager()->addChild(GUI);
	GUI->setVisible(0);
	GUI->setTheme(sTheme("default_theme"));


	
}

void CGameScrimmish::Render()
{

			GetImage("background_universe").draw(GetGC(),0,0);
}


void CGameScrimmish::Update()
{



}

void CGameScrimmish::onInput(const InputEvent &event)
{



}

void CGameScrimmish::Active()
{
	
			GUI->setVisible(1);


}

void CGameScrimmish::Deactive()
{
			GUI->setVisible(0);

}

