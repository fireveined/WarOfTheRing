#include "gui_button.h"
#include "../device.h"
#include "../resmanager.h"
#include "../common/timer.h"

CGUIButton::CGUIButton(string nam, string  t, clan::Point pos)
{
	imageButton=0;
	create(nam);
	text=t;
	area=Rect(pos,Size(10,10));
	clickTimer=0;
	animTimer=0;
	type="button";
}


CGUIButton::CGUIButton(string nam, string  t, Rect img, clan::Point pos)
{
		imageButton=1;
	create(nam);
	imageName=t;
	imageRect=img;
	area=Rect(pos,imageRect.get_size());
	clickTimer=0;
		animTimer=0;
			type="button";
}


void CGUIButton::updateArea()
{
	if(imageButton==0)
	area=Rect(area.get_top_left(),Size(theme.button_image.get_width()*2+GetTextSize(theme.font, text).width,theme.button_image.get_height()));
	else
		area=Rect(area.get_top_left(),imageRect.get_size());
}

void CGUIButton::draw()
{
	drawChilds();
	Point pos=getPosition();
	
		Rect image=theme.button_image;

	
		if(imageButton==0)
		{
			/*
		if(pressed)
			image.translate(Point(0,image.get_height()*2));
		else
		if(hovered && clickTimer<0)
			image.translate(Point(0,image.get_height()*1));
*/


	GetImage("gui_themes").draw(GetGC(), image, Rect(pos, image.get_size()));

	GetImage("gui_themes").draw(GetGC(), Rect(image.get_top_right()+Point(1,0), Size(1,image.get_height())), 
		Rect(pos.x+image.get_width(), pos.y, Size(getArea().get_width()-image.get_width()*2,image.get_height())));

	DrawTextCenter(theme.font, text, getArea().get_center().x, getArea().get_center().y, theme.color);

	GetImage("gui_themes").draw(GetGC(), image, Rect(getArea().get_top_right().x,pos.y, Size(-image.get_width(),image.get_height())));

							if(pressed)
					GetGC().fill_rect(getArea(), Colorf(0,0,0,20));
		else
		if(clickTimer<0)
				GetGC().fill_rect(getArea(), Colorf(200,200,200,int(38.0f*max(min(animTimer, 1.0f),0.0f))));

		}
		else
		{


			GetImage(imageName).draw(GetGC(), imageRect, Rect(pos, imageRect.get_size()));

				if(pressed)
					GetGC().fill_rect(getArea(), Colorf(0,0,0,20));
		else
		if(clickTimer<0)
				GetGC().fill_rect(getArea(), Colorf(255,255,25,int(46.0f*max(min(animTimer, 1.0f),0.0f))));

		}


}

void  CGUIButton::update()
{
	updateChilds();
		clickTimer-=CTimer::dt;

		if(hovered)
		{
			animTimer+=CTimer::dt*2;
		}
		else
		{
			animTimer-=CTimer::dt*2;
		}
}


bool  CGUIButton::onInput(const InputEvent &event)
{
	onInputChilds(event);


	if(event.type==InputEvent::Type::no_key && event.str=="hover_on") {hovered=1; if(onHover) onHover(this, hovered); animTimer=0.0;}
	
	if(event.type==InputEvent::Type::no_key && event.str=="hover_off")
	{
		hovered=0; 
		
		if(onHover) onHover(this, hovered); 
		
		animTimer=1;
		if(pressed)animTimer=0;
		pressed=0; 

	}


	if(event.type==InputEvent::Type::pressed && event.id==mouse_left) {pressed=1; if(onPress)onPress(this, pressed);}
		else
			if(event.type==InputEvent::Type::released && (event.id==mouse_left || event.id==mouse_right)) 
			{
				pressed=0; 
				if(onPress)
				onPress(this, pressed); 	
				if(onClick)
				onClick(this, event.id); 
				clickTimer=0.08;
			}


		

	return true;
}
