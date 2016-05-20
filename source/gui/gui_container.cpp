#include "gui_container.h"




void CGUIContainer::draw()
{
	drawChilds();
}

void CGUIContainer::update()
{
	updateChilds();
}


bool CGUIContainer::onInput(const InputEvent &event)
{

		if(event.type==InputEvent::Type::no_key && event.str=="hover_on")hovered=1;
	
	if(event.type==InputEvent::Type::no_key && event.str=="hover_off")
		hovered=0; 
return	onInputChilds(event);
}
