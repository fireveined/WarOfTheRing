#include "GameOptions.h"
#include "device.h"
#include "ResManager.h"
#include "gui/gui_button.h"
#include "gui/gui_slider.h"
#include <algorithm>






void CGameOptions::Init()
{
	GUI=new CGUIContainer("options_menu");
	CGUIManager::GetGUIManager()->addChild(GUI);
	GUI->setVisible(0);
	GUI->setTheme(sTheme("default_theme"));


		GUI->addChild(new CGUISlider("campaign3", Point(90,100), 167));
}

void CGameOptions::Render()
{


}


void CGameOptions::Update()
{



}

void CGameOptions::onInput(const InputEvent &event)
{



}

void CGameOptions::Active()
{
	
		GUI->setVisible(1);


}

void CGameOptions::Deactive()
{

		GUI->setVisible(0);
}

