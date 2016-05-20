#include "gui_Label.h"
#include "../device.h"
#include "../resmanager.h"
#include "../common/timer.h"

CGUILabel::CGUILabel(string nam, string  t, Point pos, unsigned char al)
{
	create(nam);
	text=t;
	title="";
	area=Rect(pos+Point(0,GetTextSize(theme.label_font, t).height*0.8),Size(GetTextSize(theme.label_font, t)));
	oryginalPos=pos+Point(0,GetTextSize(theme.label_font, t).height*0.8);
	align = al;

if(al & align_bottom)area.translate(Point(0, -area.get_height()*0.8));
if(al & align_right)area.translate(Point(-area.get_width(),0));


if(al & align_center && (al & align_right || al & align_left))area.translate(Point(0, -area.get_height()*0.8/2));
else
if(al & align_center && (al & align_bottom || al & align_top))area.translate(Point(-area.get_width()/2,0));
else
if(al & align_center)area.translate(Point(-area.get_width()/2, -area.get_height()*0.8/2));


	type="label";
}
/*
CGUILabel(string name, string  tit, string tex , Point pos, unsigned char al=align_left)
{
	
		create(nam);
	text=tex;
	title=tit;
	area=Rect(pos+Point(0,GetTextSize(theme.label_font, t).height*0.8+GetTextSize(theme.label_font, t).height*0.8),Size(GetTextSize(theme.label_font, t)));
	oryginalPos=pos+Point(0,GetTextSize(theme.label_font, t).height*0.8);
	align = al;

if(al & align_bottom)area.translate(Point(0, -area.get_height()*0.8));
if(al & align_right)area.translate(Point(-area.get_width(),0));


if(al & align_center && (al & align_right || al & align_left))area.translate(Point(0, -area.get_height()*0.8/2));
else
if(al & align_center && (al & align_bottom || al & align_top))area.translate(Point(-area.get_width()/2,0));
else
if(al & align_center)area.translate(Point(-area.get_width()/2, -area.get_height()*0.8/2));


	type="label";
}
*/

void CGUILabel::updateArea()
{

	area=Rect(oryginalPos,Size(GetTextSize(theme.label_font, text)));

	if(align & align_bottom)area.translate(Point(0, -area.get_height()*0.8));
if(align & align_right)area.translate(Point(-area.get_width(),0));


if(align & align_center && (align & align_right || align & align_left))area.translate(Point(0, -area.get_height()/2));
else
if(align & align_center && (align & align_bottom || align & align_top))area.translate(Point(-area.get_width()/2,0));
else
if(align & align_center)area.translate(Point(-area.get_width()*0.8/2, -area.get_height()*0.8/2));
}

void CGUILabel::draw()
{
	drawChilds();
	Point pos=getPosition();


	GetFont(theme.label_font).draw_text(GetGC(), pos.x, pos.y, text, theme.label_color);

}

void  CGUILabel::update()
{
	updateChilds();


}


bool  CGUILabel::onInput(const InputEvent &event)
{
	onInputChilds(event);


	if(event.type==InputEvent::Type::no_key && event.str=="hover_on") {hovered=1; if(onHover) onHover(this, hovered); }
	
	if(event.type==InputEvent::Type::no_key && event.str=="hover_off")
	{
		hovered=0; 
		if(onHover) onHover(this, hovered); 
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

			}


		

	return true;
}
