#ifndef GAMEINTRO_H_INCLUDED
#define GAMEINTRO_H_INCLUDED

#include "GameState.h"



class CGameIntro : public CGameState
{

    CTimer Timer;

public:
    CGameIntro() {}
    void Render();
    void Init();
void Active();
void Deactive();

};

#endif // GAMEINTRO_H_INCLUDED
