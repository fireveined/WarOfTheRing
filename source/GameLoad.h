#ifndef GAMELoad_H_INCLUDED
#define GAMELoad_H_INCLUDED

#include "GameState.h"


#include "common/timer.h"

#include "ResManager.h"


class CGameLoad : public CGameState
{

    CTimer Timer;

public:



    CGameLoad() {}

    void Render();
    void Init();
	    void Update();
		
void Active();
void Deactive();

	void onClick(CGUIComponent* c, int key){};
	void onHover(CGUIComponent* c, int key){};
	void onPress(CGUIComponent* c, int key){};

 void onInput(const InputEvent &event);
};


#endif // GAMEMENU_H_INCLUDED
