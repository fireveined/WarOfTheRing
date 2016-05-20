#ifndef GAMEMENU_H_INCLUDED
#define GAMEMENU_H_INCLUDED

#include "GameState.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include "common/timer.h"
#include <ClanLib/gui.h>
#include "ResManager.h"


class CGameMenu : public CGameState
{

	CTimer Timer;

public:


	CGameMenu() {}

	void Render();
	void Init();
	void Update();

	void onClick(CGUIComponent* c, int key);
	void onHover(CGUIComponent* c, int  key) {};
	void onPress(CGUIComponent* c, int  key) {};

	void Active();
	void Deactive();
	void PlayButtonFunc();
	void OptionsButtonFunc();
	void ExitButtonFunc();
	void onInput(const InputEvent &event);
};


#endif // GAMEMENU_H_INCLUDED
