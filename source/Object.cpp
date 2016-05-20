#include "Map.h"
#include "Object.h"
#include "action.h"
#include "device.h"
#include "GamePlay.h"

#include "actionbuild.h"

	void CObject::addToMapList()
	{
			for(int x=area.left/fieldW;x<area.right/fieldW;x++)
				for(int y=area.top/fieldW;y<area.bottom/fieldW;y++)
					getMap()->getField(x,y)->objects.push_back(this);
	}


bool CObject::onInput(const InputEvent &event)
{
	if(event.type==InputEvent::Type::pressed && event.id==mouse_left && getMap()->getSelectedCommanders()->size()==0)
	{
		if(!event.ctrl)getMap()->unselectAll();
		getMap()->select(this);
	}

		for(int a=0;a<actions.size();a++)
		{
			if(actions[a]->mouseIn(Point(Pointf(event.mouse_pos)/Pointf(getMap()->getScale(),getMap()->getScale()))))
				actions[a]->onInput(event);
		}

	return 0;
}




void CObject::update()
{

			for(int a=0;a<actions.size();a++)
		actions[a]->update();

}



	CAction*  CObject::getActionBuild()
	{
		
		for(int a=0;a<actions.size();a++)
		if(actions[a]->getType()=="action_build" && ((CActionBuild*)actions[a])->isSelected())
			return actions[a];
			return 0;
	}

void CObject::draw()
{

			for(int a=0;a<actions.size();a++)
		actions[a]->draw();
}	
