#ifndef reg_H_INCLUDED
#define reg_H_INCLUDED


#include <vector>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "gui/gui_component.h"
#include <list>
#include "object.h"



enum eTerrainType
{
	forest,
	mountains, 
	hills,
	plain,
	marshland,
	desert
};

enum eMapDrawMode
{
population,
political,
terrain,
resources,
basePoints
};

class CRegion : public CObject
{

	int id;
	Rect image, position;
	string name;

	eResType resType;
	char resAmount;

	std::vector<int> towns;
	Colorf color;

	eTerrainType terrain;

	int owner;
public:

	int getOwner(){return owner;}
	void setOwner(int o){owner=o;};


void checkForOwner();

	CRegion();

	eTerrainType getTerrain(){return terrain;}
	void setTerrain(eTerrainType t){terrain=t;}

	Colorf getColor(){return color;};
	void updateColor(eMapDrawMode mode, int max=-1);


		void deleteTown(int id)
	{
		for(int a=0;a<towns.size();a++)
			if(towns[a]==id){towns.erase(towns.begin()+a);a=9999;}
	}

	int getBasePoints();
	void addTown(int i){towns.push_back(i);}
	std::vector<int> getTowns(){return towns;};

		string getName(){return name;}
	void setName(string n){name=n;}

	int getID(){return id;}

	char getResAmount(){return resAmount;}
	eResType getResType(){return resType;}

	void setResAmount(char r){resAmount=r;}
	void setResType(eResType t){resType=t;}

	CRegion(int i, Rect im, Rect pos, eResType resname, char resnum);
	Rect getImage(){return image;}
		Rect getPosition(){return position;}
		Rect getPositionReal(){return Rect(position.left, position.top, position.right, position.bottom);}
				Rect getPositionRealScaled(float s){return Rect(position.left/0.15*s, position.top/0.15*s, position.right/0.15*s, position.bottom/0.15*s);}
	 bool onInput(const InputEvent &event);

 	void onClick(CGUIComponent* c, int key){};
	void onHover(CGUIComponent* c, int key){};
	void onPress(CGUIComponent* c, int key){};



};

#endif