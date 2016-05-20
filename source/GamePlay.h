#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include "common/timer.h"
#include <ClanLib/gui.h>
#include "ResManager.h"
#include "Effect.h"
#include "GameState.h"
#include "Map.h"

extern CMap* map;
extern std::list<CEffect> effects;
CMap* getMap();
extern int sliders[4];

extern int leftPanelW;
class CGamePlay : public CGameState
{

    bool pause;
    CTimer timer;


	

public:

	Rect getSelection();
	bool isSelection(){return 0;}

	void updateSelection();

    CGamePlay() {}
    void Render();
	    void Update();
    void Init();
void Active();
void Deactive();
 void onInput(const InputEvent &event);

 	void onClick(CGUIComponent* c, int key){};
	void onHover(CGUIComponent* c, int key){};
	void onPress(CGUIComponent* c, int key){};

	clan::OpenFileDialog* openFileDialog;
	clan::SaveFileDialog* saveFileDialog;

	void CGamePlay::projectMenuFunction(string* data);
	void CGamePlay::mapMenuFunction(string* data);
		void CGamePlay::townMenuFunction(string* data);
			void CGamePlay::armyMenuFunction(string* data);
};

string TRANS(string str);

	void addEffect(CEffect e);

#endif // GAMEPLAY_H_INCLUDED
