#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED


#include "common/Common.h"
#include "common/Timer.h"
#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include "gui/gui_container.h"
#include "gui/gui_manager.h"

using namespace clan;

enum eGameState
{
  //  GAME_INTRO,
    GAME_MENU,
	GAME_SCRIMMISH,
	GAME_CAMPAIGN,
	GAME_OPTIONS,
	GAME_LOAD,
    GAME_PLAY,

    GAME_STATE_LAST
};


class CGameState
{

protected:

    eGameState State;

    static eGameState ActState;
	CGUIContainer* GUI;
public:



    virtual void Render() {};
	 void onClick(CGUIComponent* c, int key){};
	void onHover(CGUIComponent* c, bool key){};
	void onPress(CGUIComponent* c, bool key){};

	virtual void Update() {};
    virtual void Init() {}
	virtual void onInput(const InputEvent &event){};


    CGameState() {}



    static eGameState GetActState()
    {
        return ActState;
    }
    static void SetActState(eGameState stat)
    {
        ActState=stat;
    }


    eGameState GetState()
    {
        return State;
    }
    void SetState(eGameState stat)
    {
        State=stat;
    }



	virtual void Active(){};
	virtual  void Deactive(){};
		


};




void drawStyledText(string font, Point pos, string txt, int align=0, int width=9999);
void setTooltipText(string t, float time=0, int tw=220);
void drawTooltip();

#endif // GAMESTATE_H_INCLUDED
