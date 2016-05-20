

#ifndef CDEVICE_H
#define CDEVICE_H

#include <ClanLib/application.h>
#include <ClanLib/core.h>

#include <ClanLib/swrender.h>
#include <ClanLib/gl.h>
#include <ClanLib/gui.h>


using namespace clan;

#include "common/timer.h"
#include "GameState.h"
#include <ctime>

struct SDeviceOptions
{
	char ZBufDepth;
	char ColorDepth;
	bool Fullscreen;
	int Width;
	int Height;
	char* WindowText;
};


enum DEVICE_MODE
{
	DEVICE_STANDARD,
	DEVICE_WINDOWED,
	DEVICE_HARDCORE,
	DEVICE_3D

};


class CDevice
{


	bool IsRun;
	void InitDevice();

	static CDevice *Device;

	//CGameWindow* game;

	Canvas graphic;
	InputContext input;
	ResourceManager resources;

	GUIManager gui_manager;

	DisplayWindow* window;
	DEVICE_MODE Mode;
	GUIWindowManagerDirect wm;


	clan::GUIComponent *gui_window;
	bool on_close(Window *win);

	vector<CGameState*> GameStates;

	float stepTime;

	bool Alive;
public:

	void Run();
	string Cursorname;
	static CDevice* GetDevice()
	{
		return Device;
	}

	CDevice() {}
	SDeviceOptions Options;
	CGameState* GetGameState(eGameState g) { return GameStates[(int)g]; };
	CGameState* GetActGameState() { return GameStates[CGameState::GetActState()]; };

	int GetWidth()
	{
		return Options.Width;
	}

	int GetHeight()
	{
		return Options.Height;
	}

	CDevice(int x, int y, int col = 32, int z = 8, bool f = 1, char* window = "XEngine Window");
	CDevice(DEVICE_MODE mode);
	CDevice(SDeviceOptions options);

	bool DeviceRun();
	void End() { Alive = 0; }
	void Begin()
	{
		graphic.clear(Colorf::cadetblue);
	}

	void Flip()
	{
		KeepAlive::process();
		window->flip(0);
	}

	void SetCursor(string cur)
	{
		Cursorname = cur;
	}

	InputContext* GetInput()
	{
		return &input;
	}

	Canvas GetGraphic()
	{

		return graphic;
	}

	ResourceManager* GetResources()
	{
		return &resources;
	}

	GUIManager& GetGUIManager()
	{
		return gui_manager;
	}

	GUIComponent* GetGUIWindow()
	{
		return gui_window;
	}


	double getDeltaTime()
	{
		return stepTime;
	}
};

bool KeyPress(int key);
bool KeyDown(int k);
bool KeyUp(int k);
bool DoubleClick();

float GetMouseX();
float GetMouseY();
Point getMousePos();

extern bool keys[200];
extern bool keys2[200];



extern double ScaleRatioX, ScaleRatioY;
int SeparateText(vector<string> *Text, string &text, Font &f, int width);

#define GetGC() CDevice::GetDevice()->GetGraphic()
#define GetRes() CDevice::GetDevice()->GetResources()
#define GetGUI() CDevice::GetDevice()->GetGUIManager()
#define GetGUIWindow() CDevice::GetDevice()->GetGUIWindow()
#define SetCursor(c) CDevice::GetDevice()->SetCursor(c)
Size GetTextSize(std::string font, std::string text);
void DrawTextCenter(std::string font, std::string text, int x, int y, Colorf color);

void SeparateTextToChat(vector<string> *Text, string &text, Font &f, int width);
void DrawTexture(Canvas &gc, const Rectf &rect, const Colorf &color = Colorf::white, const Rectf &texture_unit1_coords = Rectf(0.0f, 0.0f, 1.0f, 1.0f));
Size getScreenSize();
double getDeltaTime();
#endif
