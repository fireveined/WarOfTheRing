#include "ResManager.h"
#include "GamePlay.h"
#include "device.h"
#include <iostream>
#include "gui/gui_slider.h"
#include "hud.h"


/*

void slidersChanged()
{

}
*/




void CGamePlay::mapMenuFunction(string* data)
{
	string type=*data;
	if(type=="roads")
		getMap()->invertDrawRoads();

	if(type=="resources")
		getMap()->invertDrawResources();

	if(type=="terrain_map")
		getMap()->changeMapDrawMode(eMapDrawMode::terrain);

	if(type=="population_map")
		getMap()->changeMapDrawMode(eMapDrawMode::population);

	if(type=="base_points_map")
		getMap()->changeMapDrawMode(eMapDrawMode::basePoints);

	if(type=="political_map")
		getMap()->changeMapDrawMode(eMapDrawMode::political);
}



void CGamePlay::Init()
{	
	 
	GUI=new CGUIContainer("game_play");
	CGUIManager::GetGUIManager()->addChild(GUI);
	GUI->setVisible(0);
	GUI->setTheme(sTheme("default_theme"));

	CHUD* hud = new CHUD();
	GUI->addChild(hud);

	::map=new CMap();

		getMap()->loadMap(" ");

	openFileDialog = new clan::OpenFileDialog(GetGUIWindow());
	openFileDialog->set_title("Open");

	saveFileDialog = new clan::SaveFileDialog(GetGUIWindow());
	saveFileDialog->set_title("Save");
}

