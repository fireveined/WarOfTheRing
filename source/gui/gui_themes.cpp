#include "gui_manager.h"

sTheme::sTheme(string n)
{
	init(n);
}
void sTheme::init(string n)
{
	name=n;

	//if(name=="default_theme")
	{
		font="sf_font_25";
		label_font="sf_font_25";
		tooltip_font="tooltip_font_small";
		button_image=Rect(90,490, Size(12,40));

		slider_body_image=Rect(90,530, Size(12,50));
		slider_tick_image= Rect(107,530, Size(20,50));

		label_color=Colorf(255,255,255,170);
			color=Colorf(255,255,255,170);

	}


		if(name=="gui_theme")
	{
		font="sf_font_25";
		label_font="h3_font";
		tooltip_font="tooltip_font_small";
		button_image=Rect(90,490, Size(12,40));

		slider_body_image=Rect(90,530, Size(12,50));
		slider_tick_image= Rect(107,530, Size(20,50));

		label_color=Colorf(255,255,100,170);
			color=Colorf(255,255,255,170);

	}

		if(name=="wooden_theme")
	{
		font="gui_font";
		button_image=Rect(40,490, Size(15,50));
		color=Colorf(0,0,0,200);

	}
}