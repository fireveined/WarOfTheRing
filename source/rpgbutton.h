/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Mark Page
*/

#pragma once

#include <ClanLib/gui.h>
#include "ResManager.h"
#include "Device.h"
#define MENUBUTTON_SMALL 0
#define MENUBUTTON_BIG 1

#define BUTTON_ANIM_TIME 0.5
enum eButtonState
{
	BUTTON_NORMAL,
	BUTTON_ABOVE,
	BUTTON_PRESSED,
	BUTTON_CLICKED
};
class MenuButton : public clan::GUIComponent {
public:

			Callback_v0 func_clicked;
		bool ImageButton;	
	bool Size;
	eButtonState State,OldState;
	float AnimTimer;
	std::string FontName, ButtonName;
	bool IsClicked(){return State==BUTTON_CLICKED;}
			void ChangeState(eButtonState s){OldState=State;State=s;AnimTimer=BUTTON_ANIM_TIME;};
        MenuButton(clan::GUIComponent *parent, std::string txt, int x, int y, string bn) : clan::GUIComponent(parent)
        {
			ImageButton=1;
			State=BUTTON_NORMAL;
			set_id(txt);
			FontName="button_font_medium";
			if(bn=="small_button")FontName="tooltip_font";
			ButtonName=bn;
                set_tag_name(txt);
                func_render().set(this, &MenuButton::on_render);
                func_process_message().set(this, &MenuButton::on_process_message);
				set_geometry(Rect(x,y,clan::Size(GetSprite(ButtonName+"_normal").get_width(),GetSprite(ButtonName+"_normal").get_height())));
        }

		        MenuButton(clan::GUIComponent *parent, std::string txt, Rectf r, std::string font) : clan::GUIComponent(parent)
        {
			ImageButton=0;
			State=BUTTON_NORMAL;
			FontName=font;
			set_id(txt);
                set_tag_name(txt);
                func_render().set(this, &MenuButton::on_render);
                func_process_message().set(this, &MenuButton::on_process_message);
				set_geometry(r);
        }

 
private:
        void on_render(clan::Canvas &gc, const clan::Rect &clip_rect)
        {
			AnimTimer-=CTimer::dt;
			std::string fo=FontName;
							clan::Size s= GetTextSize(fo,get_tag_name());
							int tx=get_geometry().get_size().width/2-s.width/2;
							int ty=get_geometry().get_size().height/2+s.height/3;

							if(ImageButton)
							{
								std::string butname=ButtonName;
							  if(State==BUTTON_PRESSED)
				{
					GetSprite(butname+"_clicked").draw(gc, 0,0);
					ty+=2;
				}
			    else
			    if(State==BUTTON_ABOVE)
					GetSprite(butname+"_above").draw(gc, 0,0);
				else
					GetSprite(butname+"_normal").draw(gc, 0,0);

					GetFont(fo).draw_text(gc, tx,ty, get_tag_name(), Colorf(44,14,0,211));

								if(AnimTimer>0)
				{
						    if(OldState==BUTTON_PRESSED)
				{
					GetSprite(butname+"_clicked").set_alpha((AnimTimer/BUTTON_ANIM_TIME));
					GetSprite(butname+"_clicked").draw(gc, 0,0);
					GetSprite(butname+"_clicked").set_alpha(1);
				}
			    else
			    if(OldState==BUTTON_ABOVE)
				{
					GetSprite(butname+"_above").set_alpha((AnimTimer/BUTTON_ANIM_TIME));
					GetSprite(butname+"_above").draw(gc, 0,0);
					GetSprite(butname+"_above").set_alpha(1);
				}
				else
				{
					GetSprite(butname+"_normal").set_alpha((AnimTimer/BUTTON_ANIM_TIME));
					GetSprite(butname+"_normal").draw(gc, 0,0);
					GetSprite(butname+"_normal").set_alpha(1);
				}
				GetFont(fo).draw_text(gc, tx,ty, get_tag_name(), Colorf(44,14,0,211));

				}

							}
							else
							{		

								int tx=get_geometry().get_center().x-s.width/2;
							int ty=get_geometry().get_center().y+s.height/3;


								  if(State==BUTTON_PRESSED)
				{
				GetGC().fill_rect(get_geometry(), Colorf(1.0f,1.0f,1.0,0.5));
					ty+=2;
				}
			    else
			    if(State==BUTTON_ABOVE)
				{
					GetGC().fill_rect(get_geometry(), Colorf(1.0f,1.0f,1.0,min((1-AnimTimer/BUTTON_ANIM_TIME)*0.3,0.3)));
				}
				else
				{
					GetGC().fill_rect(get_geometry(), Colorf(1.0f,1.0f,1.0,0.01));
				}
				GetFont(fo).draw_text(GetGC(), tx,ty, get_tag_name(), Colorf(44,14,0, 210));


				if(AnimTimer>0)
				{

											  if(OldState==BUTTON_PRESSED)
				{
				GetGC().fill_rect(get_geometry(), Colorf(1.0f,1.0f,1.0,(AnimTimer/BUTTON_ANIM_TIME)*0.5));
					ty+=2;
				}
			    else
			    if(OldState==BUTTON_ABOVE)
				{
					GetGC().fill_rect(get_geometry(), Colorf(1.0f,1.0f,1.0,(AnimTimer/BUTTON_ANIM_TIME)*0.3));
				}
				else
				{

				}


				}

							}


			  
								if(State==BUTTON_NORMAL && get_geometry().contains(Vec2f(GetMouseX(), GetMouseY())))
									ChangeState(BUTTON_ABOVE);
			



				if(State==BUTTON_CLICKED)
				ChangeState(BUTTON_NORMAL);
        }
 
        void on_process_message(std::tr1::shared_ptr<clan::GUIMessage> &message)
		{

			std::shared_ptr<GUIMessage_Input> input_msg = std::dynamic_pointer_cast<GUIMessage_Input>(message);
	if (input_msg)
		on_input_message(input_msg);


			std::shared_ptr<GUIMessage_Pointer> pointer = std::dynamic_pointer_cast<GUIMessage_Pointer>(message);
			if (pointer)
			{
				if (pointer->pointer_type == GUIMessage_Pointer::pointer_leave)
					ChangeState(BUTTON_NORMAL);
				if (pointer->pointer_type ==GUIMessage_Pointer::pointer_enter)
					ChangeState(BUTTON_ABOVE);
				message->consumed = true;
			}
        }
    
		void on_input_message(std::shared_ptr<GUIMessage_Input> input_msg)
		{
		


					if (input_msg->input_event.type == InputEvent::pressed && 
				(input_msg->input_event.id == mouse_left || input_msg->input_event.id == keycode_return || input_msg->input_event.id == keycode_space || input_msg->input_event.id == keycode_numpad_enter))
			{
				ChangeState(BUTTON_PRESSED);
				input_msg->consumed = true;
			}
			else if( input_msg->input_event.type == InputEvent::released &&
				(input_msg->input_event.id == mouse_left || input_msg->input_event.id == keycode_return || input_msg->input_event.id == keycode_space || input_msg->input_event.id == keycode_numpad_enter) &&
				State==BUTTON_PRESSED )
			{
				ChangeState(BUTTON_CLICKED);
				input_msg->consumed = true;
				
				if (!func_clicked.is_null())
					func_clicked.invoke();
			}

		}






};