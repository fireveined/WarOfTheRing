//#include "Game.h".


#include "Device.h"

#include "ResManager.h"
#include "gamescrimmish.h"
#include "gameplay.h"
#include "gamemenu.h"
#include "gameload.h"
#include "gamecampaign.h"
#include "gameoptions.h"
#include "common/tokenizer.h"
#include <ClanLib/d3d.h>
#include "gui/gui_manager.h"

CDevice* CDevice::Device = 0;

bool keys[200];
bool keys2[200];
float LastLClick = 0;
eGameState CGameState::ActState;

Size getScreenSize()
{
	return Size(CDevice::GetDevice()->GetWidth(), CDevice::GetDevice()->GetHeight());
}

void input_callback3(const InputEvent &event)
{
	if (!CGUIManager::GetGUIManager()->onInput(event))
		CDevice::GetDevice()->GetActGameState()->onInput(event);


}

void input_callback(const InputEvent &event)
{
	keys[event.id] = 1;

	if (!CGUIManager::GetGUIManager()->onInput(event))
		CDevice::GetDevice()->GetActGameState()->onInput(event);

}


void input_callback2(const InputEvent &event)
{
	if (event.id != mouse_wheel_up && event.id != mouse_wheel_down)
		keys[event.id] = 0;

	if (!CGUIManager::GetGUIManager()->onInput(event))
		CDevice::GetDevice()->GetActGameState()->onInput(event);

}


CDevice::CDevice(int x, int y, int col, int z, bool f, char* window)
{
	Options.Width = x;
	Options.Height = y;
	Options.ColorDepth = col;
	Options.ZBufDepth = z;
	Options.Fullscreen = 1;
	Options.WindowText = window;

	InitDevice();
}

float mouseNoMoveTimer = 0;

CDevice::CDevice(DEVICE_MODE mode)
{
	Mode = mode;
	switch (mode)
	{

	case DEVICE_STANDARD:
		Options.Width = 1440;
		Options.Height = 900;
		Options.ColorDepth = 32;
		Options.ZBufDepth = 8;
		Options.Fullscreen = 1;
		Options.WindowText = "MiddleEarth";
		break;

	case DEVICE_WINDOWED:
		Options.Width = 1440;
		Options.Height = 900;
		Options.ColorDepth = 32;
		Options.ZBufDepth = 8;
		Options.Fullscreen = 0;
		Options.WindowText = "MiddleEarth";
		break;

	case DEVICE_HARDCORE:
		Options.Width = 320;
		Options.Height = 260;
		Options.ColorDepth = 8;
		Options.ZBufDepth = 8;
		Options.Fullscreen = 0;
		Options.WindowText = "XEngine HARDCORE!";
		break;

	case DEVICE_3D:
		Options.Width = 1280;
		Options.Height = 1024;
		Options.ColorDepth = 32;
		Options.ZBufDepth = 8;
		Options.Fullscreen = 1;
		Options.WindowText = "XEngine";
		break;

	}

	InitDevice();
}





CDevice::CDevice(SDeviceOptions options)
{
	Options = options;
}



float tooltipTime = 0;
void CDevice::InitDevice()
{

	srand(time(0));
	SetupCore setup_core;
	SetupDisplay setup_display;

	SetupGL setup_gl;
	//clan::SetupSWRender setup_swrender;



	SetupGUI setup_gui;
	//	CL_SetupNetwork setup_network;
	FileLogger file_logger("log.txt");
	file_logger.enable();



	DisplayWindowDescription description;
	description.set_size(Size(Options.Width, Options.Height), false);
	//description.set_fullscreen(Options.Fullscreen);
	description.set_title(Options.WindowText);

	//gui_manager.set_theme(theme);


	description.set_title(Options.WindowText);
	description.show_caption(false);
	description.set_size(Size(Options.Width, Options.Height), false);
	description.set_fullscreen(Options.Fullscreen);
	//description.set_refresh_rate(60);
	description.set_allow_resize(1);
	window = new DisplayWindow(description);
	//(*window).func_close().set(this, &CDevice::on_close, (CL_Window*)window);
	Slot slot_input_down = window->get_ic().get_keyboard().sig_key_down().connect(&input_callback);

	Slot slot_in5put_down = window->get_ic().get_keyboard().sig_key_up().connect(&input_callback2);
	Slot slot_input_dow2n = window->get_ic().get_mouse().sig_key_down().connect(&input_callback);
	Slot slot_input_d4own = window->get_ic().get_mouse().sig_key_up().connect(&input_callback2);
	Slot slot_mouse_dblclick = window->get_ic().get_mouse().sig_key_dblclk().connect(&input_callback);
	Slot slot_mouse_dblclick2 = window->get_ic().get_mouse().sig_pointer_move().connect(&input_callback3);
	//::CWindow(description)
	//func_render().set(this, &CDevice::Loop);
		//	set_constant_repaint(true);

	graphic = Canvas(*window);
	input = window->get_ic();
	//window->hide_cursor();

	wm = GUIWindowManagerDirect(*window, graphic);
	gui_manager = GUIManager(wm, "data/GUIThemeAero");
	resources = clan::XMLResourceManager::create(clan::XMLResourceDocument("data/resources.xml"));
	clan::DisplayWindowDescription win_desc;
	win_desc.set_allow_resize(true);
	win_desc.set_title("GUI Direct Application");
	win_desc.set_position(graphic.get_size(), false);
	gui_window = new clan::GUIComponent(&gui_manager, win_desc, "");


	log_event("INIT", "Zainicjowano ClanLib.");

	IsRun = 1;
	Device = this;


	CGUIManager::GetGUIManager()->setArea(Rect(0, 0, Options.Width, Options.Height));
	CGUIManager::GetGUIManager()->setParent(CGUIManager::GetGUIManager());

	GameStates.push_back(new CGameMenu());
	GameStates.push_back(new CGameScrimmish());
	GameStates.push_back(new CGameCampaign());
	GameStates.push_back(new CGameOptions());
	GameStates.push_back(new CGameLoad());
	GameStates.push_back(new CGamePlay());

	for (int a = 0; a < GameStates.size(); a++)
		GameStates[a]->Init();

	GameStates[0]->Active();


	Cursorname = "cursor_normal";

	CGameState::SetActState(GAME_MENU);
	clan::GameTime game_time;

	window->hide_cursor();
	Alive = 1;


	stepTime = 0.02;
	float acum = 0;

	int oldmx = 0, oldmy;


	while (Alive)
	{
		Cursorname = "cursor_normal";
		mouseNoMoveTimer += CTimer::dt;
		if (mouseNoMoveTimer < tooltipTime && (GetMouseX() != oldmx || GetMouseY() != oldmy))mouseNoMoveTimer = 0;
		oldmx = GetMouseX();
		oldmy = GetMouseY();

		setTooltipText("");

		game_time.update();
		float t = clock();


		LastLClick += CTimer::dt;
		if (DoubleClick())LastLClick = 0;

		//	if(CTimer::dt>0.1)CTimer::dt=0.1;
		//	if(cursor.is_null())cursor=CL_Image(GetGC(),"cursor",GetRes());

		ScaleRatioX = (float)GetGC().get_width() / (float)CDevice::GetDevice()->GetWidth();
		ScaleRatioY = (float)GetGC().get_height() / (float)CDevice::GetDevice()->GetHeight();

		Mat4f matrix = Mat4f::scale((float)GetGC().get_width() / (float)CDevice::GetDevice()->GetWidth(),
			(float)GetGC().get_height() / (float)CDevice::GetDevice()->GetHeight(), 1.0f);
		//	if(CDevice::GetDevice()->GetWidth()!=GetGC().get_width())
	//GetGC().set_modelview(matrix);


		GetGC().clear(Colorf::black);



		acum += CTimer::dt;

		//if(acum>stepTime)
		{
			acum -= stepTime;
			GameStates[CGameState::GetActState()]->Update();
		}

		GameStates[CGameState::GetActState()]->Render();



		CGUIManager::GetGUIManager()->draw();
		CGUIManager::GetGUIManager()->update();

		GetImage(Cursorname).draw(GetGC(), GetMouseX(), GetMouseY());

		CTimer::FPS();

		if (KeyDown(mouse_left))LastLClick = 0;
		if (KeyDown(keycode_escape))Alive = 0;

		for (int a = 0; a < 200; a++)
			keys2[a] = keys[a];
		keys[mouse_wheel_up] = 0;
		keys[mouse_wheel_down] = 0;






		gui_manager.render_windows();

		GetFont("guifont_bold").draw_text(GetGC(), 751, 23, "FPS: " + IntToStr(CTimer::fFPS), Colorf::white);

		if (mouseNoMoveTimer > tooltipTime)
			drawTooltip();
		//	GetImage(Cursorname).draw(GetGC(), GetMouseX(), GetMouseY());

		window->flip(0);
		clan::KeepAlive::process();
	}



}


void drawStyledText(string fonts, Point pos, string txt, int align, int w)
{

	Font font = GetFont(fonts);

	int x = pos.x;
	int y = pos.y;

	vector<string> tooltip;
	SeparateText(&tooltip, txt, font, w - 12);

	int actx = 0;
	int fonth = font.get_text_size(GetGC(), "ge837j").height;

	int h = 9 + fonth;
	float actbr = 0;
	bool bold = 0;

	vector<int> widths;
	widths.push_back(0);
	for (int a = 0; a < tooltip.size(); a++)
	{
		if (tooltip[a].length()>0 && tooltip[a][0] != '#')widths[widths.size() - 1] += font.get_text_size(GetGC(), tooltip[a]).width;
		if (tooltip[a] == "#br")h += fonth, widths.push_back(0);
		if (tooltip[a] == "#line")h += fonth*0.6, widths.push_back(0);
	}


	Colorf actColor(200, 200, 200, 200);
	for (int a = 0; a < tooltip.size(); a++)
	{
		if (tooltip[a] != "")
		{
			if (tooltip[a][0] == '#')
			{
				if (tooltip[a] == "#br")actbr++, actx = 0;
				if (tooltip[a] == "#font_def")actColor = Colorf(200, 200, 200, 200), font = GetFont(fonts);
				if (tooltip[a] == "#font_bold")font = GetFont(fonts + "_bold");

				if (tooltip[a] == "#col_red")actColor = Colorf(250, 100, 100, 200);
				if (tooltip[a] == "#col_white")actColor = Colorf(200, 200, 200, 200);
				if (tooltip[a] == "#col_green")actColor = Colorf(100, 250, 100, 200);

				if (tooltip[a] == "#line") { GetGC().draw_line(Pointf(x, y + 7 + actbr*fonth), Pointf(x + w - 3, y + 7 + actbr*fonth), Colorf(144, 144, 144, 144)); actbr += 0.6, actx = 0; }
			}
			else
			{
				if (align == 2)
					font.draw_text(GetGC(), Pointf(-widths[(int)actbr] + x + actx, y + actbr*fonth), tooltip[a], actColor);
				else
					font.draw_text(GetGC(), Pointf(x + actx, y + actbr*fonth), tooltip[a], actColor);
				actx += font.get_text_size(GetGC(), tooltip[a]).width;
			}
		}

	}

}

string tooltipText;
int tooltipWidth = 220;
void drawTooltip()
{
	if (tooltipText == "")return;
	string fontstr = "tooltip";
	Font font = GetFont(fontstr);
	int w = tooltipWidth;
	int x = GetMouseX() + 18;
	int y = GetMouseY();

	vector<string> tooltip;
	int gw = SeparateText(&tooltip, tooltipText, font, w - 12);
	if (w == 220)
		w = gw + 16;
	int actx = 0;
	int fonth = font.get_text_size(GetGC(), "ge837j").height;

	int h = 9 + fonth;
	float actbr = 0;
	bool bold = 0;
	for (int a = 0; a < tooltip.size(); a++)
	{
		if (tooltip[a] == "#br")h += fonth;
		if (tooltip[a] == "#line")h += fonth*0.6;
	}

	if (y + h > ::getScreenSize().height)y = getScreenSize().height - h;
	if (x + w > ::getScreenSize().width)x = getScreenSize().width - w;

	GetGC().fill_rect(Rect(x, y, Size(w, h)), Colorf(0, 0, 0, 220));
	GetGC().draw_box(Rect(x, y, Size(w, h)), Colorf(88, 88, 88, 240));

	Colorf actColor(200, 200, 200, 200);
	for (int a = 0; a < tooltip.size(); a++)
	{
		if (tooltip[a] != "")
		{
			if (tooltip[a][0] == '#')
			{
				if (tooltip[a] == "#br")actbr++, actx = 0;
				else
					if (tooltip[a] == "#font_def")actColor = Colorf(200, 200, 200, 200), font = GetFont(fontstr);
					else
						if (tooltip[a] == "#font_bold")font = GetFont(fontstr + "_bold");
						else
							if (tooltip[a] == "#col_red")actColor = Colorf(250, 100, 100, 200);
							else
								if (tooltip[a] == "#col_white")actColor = Colorf(200, 200, 200, 200);
								else
									if (tooltip[a] == "#col_green")actColor = Colorf(100, 250, 100, 200);
									else
										if (tooltip[a] == "#line") { GetGC().draw_line(Pointf(x + 8, y + 7 + actbr*fonth), Pointf(x + w - 8, y + 7 + actbr*fonth), Colorf(144, 144, 144, 144)); actbr += 0.6, actx = 0; }
										else
											if (tooltip[a].find("#icon:") < 999)
											{
												GetImage("gui_atlas").draw(GetGC(), Rect(790 + 20 * StrToInt(tooltip[a].substr(6, 5)), 110, Size(16, 16)), Rect(x + actx + 6, y + 4 + actbr*fonth, Size(16, 16)));
												actx += 23;
											}
											else
												if (tooltip[a].find("#setx:") < 999)
												{
													actx = StrToInt(tooltip[a].substr(6, 5));
												}
			}
			else
			{

				font.draw_text(GetGC(), Pointf(x + 6 + actx, y + 15 + actbr*fonth), tooltip[a], actColor);
				actx += font.get_text_size(GetGC(), tooltip[a]).width;
			}
		}

	}

}

string lastNotNull;
int lastNotNullTimer = 0;
void setTooltipText(string t, float ti, int twa)
{
	tooltipWidth = twa;
	tooltipTime = ti;
	if (t == "" && tooltipText == "") mouseNoMoveTimer = 0;
	if (t == "" && lastNotNull != "")mouseNoMoveTimer = 0;
	//	if(tooltipText=="")
	lastNotNull = tooltipText;
	tooltipText = t;
	//if(t!="")=t;
}

bool CDevice::on_close(Window *win)
{
	win->exit_with_code(0);
	return true;
}


void CDevice::Run()
{

}


double getDeltaTime()
{
	return CDevice::GetDevice()->getDeltaTime();
}

bool CDevice::DeviceRun()
{

	// CTimer::FPS();
	 //if(input.get_keyboard().get_keycode(KEY_ESCAPE))return false;

	return true;


}

bool KeyPress(int key)
{

	return  keys[key];

}

double  ScaleRatioX, ScaleRatioY;
bool KeyDown(int key)
{


	// if(CDevice::GetDevice()->GetKeyboard()->IsK ey(key) && WasDown)
	return keys[key] && !keys2[key];

}

bool KeyUp(int key)
{


	// if(CDevice::GetDevice()->GetKeyboard()->IsKey(key) && WasDown)
	return !keys[key] && keys2[key];

}

bool DoubleClick()
{

	return (KeyDown(mouse_left) && LastLClick < 0.3);

}


float GetMouseX()
{
	return (float)CDevice::GetDevice()->GetInput()->get_mouse().get_x();
}

float GetMouseY()
{
	return (float)CDevice::GetDevice()->GetInput()->get_mouse().get_y();
}

Point getMousePos()
{
	return Point(GetMouseX(), GetMouseY());
}



Window* mes;
void ShowMessage(const std::string & txt)
{

	DisplayWindowDescription desc;
	desc.set_size(Size(333, 133), false);
	desc.show_caption(0);
	desc.set_topmost(1);

	//desc.set_decorations(0); 
	mes = new Window(GetGUIWindow(), desc);

}



int SeparateText(vector<string> *Text, string &text, Font &f, int width)
{


	vector<string> words;

	text += " ";
	CTokenizer token(text);

	while (token.ParseToken())
	{
		if (f.get_text_size(GetGC(), token.GetToken(0)).width > width)
		{
			words.push_back(token.GetToken(0).substr(0, token.GetToken(0).length() / 2));
			words.push_back(token.GetToken(0).substr(token.GetToken(0).length() / 2, token.GetToken(0).length() / 2));
		}
		else
			words.push_back(token.GetToken(0));
	}


	int maxw = 0;

	(*Text).push_back("");
	int br = 0;
	int wid = 0;
	for (int l = 0; l < words.size(); l++)

		if (words[l][0] == '#')
		{




			if (words[l] == "#br")
			{
				(*Text).push_back("#br");
				(*Text).push_back("");
				wid = 0;
				br++;
			}
			else
			{

				(*Text).push_back(words[l]);
				if (words[l].find("#icon:") < 999)
					wid += 23;


				if (words[l].find("#setx:") < 999)
				{
					wid = StrToInt(words[l].substr(6, 5));
				}
				(*Text).push_back("");
			}


		}
		else if (wid + f.get_text_size(GetGC(), words[l] + " ").width > width - 5)
		{
			(*Text).push_back("#br");
			(*Text).push_back(words[l] + " ");
			wid = f.get_text_size(GetGC(), words[l] + " ").width;
			maxw = width;
		}
		else
		{
			(*Text)[(*Text).size() - 1] += words[l] + " ";
			wid += f.get_text_size(GetGC(), words[l] + " ").width;
			if (wid + 5 > maxw)
				maxw = wid + 5;
		}




		return maxw;
}





Image& CImageManager::zGetImage(const string& name)
{
	Image& t = Resources[name];
	if (t.is_null()) {
		t = Image::resource(GetGC(), name, *GetRes()); AddImage(t, name);
		log_event("WARNING", "Nie można znaleść bitmapy '" + name + "'.");
	}
	return t;
}

Sprite& CSpriteManager::zGetImage(const string& name)
{
	Sprite& t = Resources[name];
	if (t.is_null()) {
		t = Sprite::resource(GetGC(), name, *GetRes()); AddSprite(t, name);
		log_event("WARNING", "Nie można znaleść sprajta '" + name + "'.");
	}
	return t;
}

Texture& CTextureManager::zGetTexture(const string& name)
{
	Texture& t = Resources[name];
	if (t.is_null()) {
		t = Texture::resource(GetGC(), name, *GetRes()); AddTexture(t, name);
		log_event("WARNING", "Nie można znaleść textury '" + name + "'.");
	}
	return t;
}
Font& CFontManager::zGetFont(const string& name)
{
	clan::FontDescription de;
	de.set_typeface_name(name);
	Font& t = Resources[name];
	if (t.is_null()) { t = Font::resource(GetGC(), de, *GetRes()); AddFont(t, name); log_event("WARNING", "Nie można znaleść czcionki '" + name + "'."); }
	return t;
}



void DrawTextCenter(std::string font, std::string text, int x, int y, Colorf color)
{
	Size ts = GetTextSize(font, text);
	float w = 7.5 / 11.0*GetFont(font).get_font_metrics().get_height();
	GetFont(font).draw_text(GetGC(), x - ts.width / 2, y + (int)(w / 2), text, color);
}


