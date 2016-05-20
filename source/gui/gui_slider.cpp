#include "gui_slider.h"
#include "../device.h"
#include "../resmanager.h"
#include "../common/timer.h"

float maxLightTimer=0.25;
Rect sliderImg=Rect(50, 630, Size(171, 19));
const int sliderMargin=5;
CGUISlider::CGUISlider(string nam, clan::Point pos, int width, float v, bool vert)
{
	
	vertical=vert;
	create(nam);
	area=Rect(pos,Size(171,19));
	if(vert)
		area=Rect(pos, Size(12, width));
	value=v;
	animTimer=0;
		type="slider";
		disabled=0;
		lightTimer=0;
}



void CGUISlider::updateArea()
{
	theme=parent->getTheme();
		if(!vertical)
	area=Rect(area.get_top_left(),
		Size(sliderImg.get_size()));


}

void CGUISlider::draw()
{
	drawChilds();
	Point pos=getPosition();
	
	//	Rect tick=theme.slider_tick_image;
		Rect image=theme.slider_body_image;
	/*



	GetImage("gui_themes").draw(GetGC(), image, Rect(pos, image.get_size()));

	GetImage("gui_themes").draw(GetGC(), Rect(image.get_top_right()+Point(1,0), Size(1,image.get_height())), 
		Rect(pos.x+image.get_width(), pos.y, Size(getArea().get_width()-image.get_width()*2,image.get_height())));


	GetImage("gui_themes").draw(GetGC(), image, Rect(getArea().get_top_right().x,pos.y, Size(-image.get_width(),image.get_height())));


	float v=value;
	if(hovered)v=valueShown;
	int tw=float((getArea().get_width()-image.get_width()*2)/tick.get_width())*v;

	GetGC().fill_rect(Rect(getArea().get_top_left()+Point(image.get_width()+2,3), Size(tw*tick.get_width()-4, image.get_height()-6)), Colorf(200,200,200,int(76.0f*max(min(animTimer, 1.0f),0.0f))));


	for(int a=0;a<tw;a++)
	{
	GetImage("gui_themes").draw(GetGC(), tick, Rect(pos+Point(image.get_width(),0)+a*Point(tick.get_width(),0), tick.get_size()));
	}

	*/
			
		if(!vertical)
		{
		Rect img=sliderImg;
		if(disabled)
		GetImage("gui_themes").set_color(Colorf(130,130,130));	
	

		GetImage("gui_themes").draw(GetGC(), img , Rect(pos, img.get_size()));
		float det=(lightTimer/maxLightTimer);
		if(!disabled)
		GetImage("gui_themes").set_color(Colorf(220+int(35*det),80+int(60*det),80+int(60*det)));
		GetImage("gui_themes").draw(GetGC(), Rect(img.get_top_left()-Point(0,20), Size( img.get_width()*barValue,img.get_height())) , Rect(pos, Size( img.get_width()*barValue,img.get_height()) ));
		GetImage("gui_themes").set_color(Colorf::white);

			if((int)(barValue*10)!=(int)(value*10))
		{
			int wsp=animTimer*6;
			int wu=0;
				if(value<barValue)wsp=-wsp;
			int w=(img.get_width()*barValue-6)*(wsp%20)/20;
			if(value<barValue)wu=(img.get_width()*barValue-6);
			GetGC().fill_rect(Rect(pos+Point(w+wu,2), Size(6, img.get_height()-4) ), Gradient(Colorf(255,255,255,0), Colorf(255,255,255,10)));
		}

		int w=img.get_width()-sliderMargin*2;
		Rect tick=Rect(20, 630, Size(8, 26));
		GetImage("gui_themes").draw(GetGC(), tick, Rect( pos.x+sliderMargin+w*value-tick.get_width()/2,pos.y+img.get_height()/2-tick.get_height()/2, tick.get_size()));
		}
		else
		{
				int tw=20;
				Rect ar=getArea();
			Rect tick=Rect(220, 570, Size(tw, 10));
			
				float det=(lightTimer/maxLightTimer);
			GetImage("gui_themes").draw(GetGC(), Rect(250, 500, Size(16, 150)), ar);
						GetGC().fill_rect(ar, Colorf(255,255,255,int(24*det)));
			GetImage("gui_themes").draw(GetGC(), tick, Rect(ar.left-tw/2+ar.get_width()/2, ar.bottom-value*ar.get_height()-tick.get_height()/2, Size(tick.get_size())));

		}
	
}

void  CGUISlider::update()
{
	updateChilds();
	
	if(KeyUp(mouse_left))pressed=0;

		if(pressed && !disabled) 
	{
		if(!vertical)
		{
		float x=GetMouseX()-getPosition().x-sliderMargin;
		float w=getArea().get_width()-sliderMargin*2;
		value=max(min(x/w,1.0f),0);
		}
		else
		{
		float x=GetMouseY()-getPosition().y-sliderMargin;
		float w=getArea().get_height()-sliderMargin*2;
		value=max(min((w-x)/w,1.0f),0);

		}

		if(onChange)onChange(this, value);
			
	}
	//	if(!pressed)
//hovered=0; 
		
			animTimer+=CTimer::dt*10;

			if(hovered)lightTimer+=CTimer::dt*2;
			else
				lightTimer-=CTimer::dt;

			if(lightTimer>maxLightTimer)lightTimer=maxLightTimer;
			if(lightTimer<0)lightTimer=0;
}


bool  CGUISlider::onInput(const InputEvent &event)
{
	onInputChilds(event);

	if(event.type==InputEvent::Type::pointer_moved)
	{
		if(!vertical)
		{
		float x=event.mouse_pos.x-getPosition().x-theme.slider_body_image.get_width()+theme.slider_tick_image.get_width();
		float w=getArea().get_width()-theme.slider_body_image.get_width()*2;
		valueShown=min(x/w,1.0f);
		}
	}


	if(event.type==InputEvent::Type::no_key && event.str=="hover_on") 
	{
		hovered=1; if(onHover) onHover(this, hovered); animTimer=0.0;
	}
	
	if(event.type==InputEvent::Type::no_key && event.str=="hover_off")
	{
	
		valueShown=-1;
		if(onHover) onHover(this, hovered); 
			hovered=0; 
		animTimer=1;
		if(pressed)animTimer=0;
		

	}


	if((pressed || (event.type==InputEvent::Type::pressed && event.id==mouse_left)) && !disabled) 
	{
		if(!vertical)
		{
		float x=event.mouse_pos.x-getPosition().x-sliderMargin;
		float w=getArea().get_width()-sliderMargin*2;
		value=min(x/w,1.0f);
		}
		else
		{
					float x=event.mouse_pos.y-getPosition().y-sliderMargin;
		float w=getArea().get_height()-sliderMargin*2;
		value=max(min((w-x)/w,1.0f),0);
		}
		pressed=1; 
		if(onPress)onPress(this, pressed);
		if(onChange)onChange(this, value);
	}

	if((event.type==InputEvent::Type::pressed || event.type==InputEvent::Type::doubleclick) && event.id==mouse_right && !vertical) 
	{
		disabled=!disabled;
	if(onDisable)onDisable(this, disabled);
	}
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
