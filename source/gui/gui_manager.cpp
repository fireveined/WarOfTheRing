#include "gui_manager.h"
#include "../device.h"
#include "../resmanager.h"
	 CGUIManager CGUIManager::GUIManagerInstance;



void CGUIComponent::create(string s)
{
	name=s;
	visible=1;
	hovered=0;
	pressed=0;
	needTooltip=0;
	tooltipTimer=0;
}

CGUIComponent* CGUIComponent::addChild(CGUIComponent* comp)
{
	comp->setParent(this);
	comp->setTheme(theme);
	components[comp->getName()]=comp;
	return comp;
}

CGUIComponent* CGUIComponent::getChild(string n)
{
	if(n.find_first_of( '/' )!=std::string::npos)
	return components[n.substr(0,n.find_first_of( '/' ))]->getChild(n.substr(n.find_first_of( '/' )+1));
	else
return components[n];
}
void CGUIComponent::setParent(CGUIComponent* par)
{

	parent=par;
	theme=par->getTheme();
}



void CGUIComponent::drawChilds()
{
	CGUIComponent*tolt=0;
	    for (std::map<string,CGUIComponent*>::iterator it=components.begin(); it!=components.end(); ++it)
		{
			if(it->second->isVisible())
       it->second->draw();
			if(it->second->ifNeedTooltip())tolt=it->second;
		 }

		if(tolt)
		{
			string s=tolt->getTooltip();
			string f=tolt->getTheme().tooltip_font;
				GetGC().fill_rect(Rect(GetMouseX()+20, GetMouseY()+20, GetTextSize(f,s)+Size(8,2)), Colorf(0,0,0,110));
				GetGC().draw_box(Rect(GetMouseX()+20, GetMouseY()+20, GetTextSize(f,s)+Size(8,2)), Colorf(155,155,155,150));
					GetFont(f).draw_text(GetGC(), GetMouseX()+20+4, GetMouseY()+20+GetTextSize(f,s).height,s, Colorf(177,177,177,180));
		}

}


void CGUIComponent::updateChilds()
{

	    for (std::map<string,CGUIComponent*>::iterator it=components.begin(); it!=components.end(); ++it)
		{
				if(it->second->isVisible())
       it->second->update();
		 }

		if(hovered)
			tooltipTimer+=CTimer::dt;
		else
			tooltipTimer=0;

		if(tooltipTimer>0.7 && tooltip.size()>0)
			needTooltip=1;
		else
			needTooltip=0;

}

bool CGUIComponent::onInputChilds(const InputEvent &event)
{

		    for (std::map<string,CGUIComponent*>::iterator it=components.begin(); it!=components.end(); ++it)
		{
			if(it->second->isVisible() && it->second->mouseIn(event.mouse_pos))
			{

				if(event.type==InputEvent::Type::pointer_moved && !it->second->isHovered())
				{	
					InputEvent e=event;
					e.type=InputEvent::Type::no_key, e.str="hover_on";
					it->second->onInput(e);	
				}

			return 	it->second->onInput(event);
			}
			else if(it->second->isHovered())
			{
				InputEvent e=event;
				e.type=InputEvent::Type::no_key, e.str="hover_off";
				it->second->onInput(e);
			}

		 }
			return 0;
}



void CGUIManager::draw()
{

	drawChilds();

}

void CGUIManager::update()
{
	updateChilds();
}


bool CGUIManager::onInput(const InputEvent &event)
{
return	onInputChilds(event);
}
