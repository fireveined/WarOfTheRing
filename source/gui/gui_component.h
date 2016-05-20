#pragma once

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <string>
#include "../FastDelegate.h"
using namespace clan;
using namespace std;

struct sTheme
{
	string name, font, label_font, tooltip_font;
	Rect button_image, slider_tick_image, slider_body_image;
	Colorf color, label_color;

	sTheme(string name);
	void init(string name);
	sTheme(){init("default_theme");}
};


enum GUIAlign
{
	align_left= 1 << 0,
	align_right = 1 << 1,
	align_center = 1 << 2,
	align_top = 1 << 3,
	align_bottom = 1 << 4

};

struct CGUIButton;
struct CGUISlider;
struct CGUILabel;

class CGUIComponent {

	protected:
	string name;
	string type, tooltip;
	bool needTooltip;
	Rect area;
	bool visible;
	CGUIComponent* parent;
	std::map<string, CGUIComponent*> components;
		sTheme theme;
		bool hovered, pressed;

		float tooltipTimer;

			fastdelegate::FastDelegate2<CGUIComponent*, int> onClick;
	fastdelegate::FastDelegate2<CGUIComponent*, int> onHover;
	fastdelegate::FastDelegate2<CGUIComponent*, int> onPress;

public:

	bool ifNeedTooltip(){return needTooltip;}

	string getType(){return type;} 
	string getTooltip(){return tooltip;} 

	void setTooltip(string t){tooltip=t;};

virtual bool mouseIn(Point m)
	{
		return getArea().contains(m);
	}

	CGUILabel* getLabel(string s){return (CGUILabel*)getChild(s);}
	CGUIButton* getButton(string s){return (CGUIButton*)getChild(s);}
	CGUISlider* getSlider(string s){return (CGUISlider*)getChild(s);}

	 void setOnClick(fastdelegate::FastDelegate2<CGUIComponent*, int> f){onClick=f;}
		 void setOnHover(fastdelegate::FastDelegate2<CGUIComponent*, int> f){onHover=f;}
		 void setOnPress(fastdelegate::FastDelegate2<CGUIComponent*, int> f){onPress=f;}

		 void setWidth(int w){area=Rect(area.get_top_left(), Size(w, area.get_height()));}

	bool isHovered(){return hovered;}
	bool isPressed(){return pressed;}
	CGUIComponent(){parent=0;}

		CGUIComponent* getChild(string n);

		void create(string nam);

		CGUIComponent* getParent(){return parent;}

		void setParent(CGUIComponent* par);

		virtual void updateArea(){area=parent->getArea();}

		CGUIComponent* addChild(CGUIComponent* comp);

			void setTheme(sTheme &t){theme=t; updateArea();};
	sTheme getTheme(){return theme;}



	string getName(){return name;};
	virtual string getFullName(){return parent->getFullName()+"/"+name;}
	void setName(string& s){name=s;};

	Rect getArea(){Rect ar=area; if(parent)return ar.translate(parent->getPosition()); else return ar;};

virtual	Point getPosition(){return getArea().get_top_left();};

	void setArea(Rect a){area=a;}

	void setVisible(bool v){visible=v;};
	bool isVisible(){return visible;}

	void drawChilds();
	void updateChilds();
	bool onInputChilds(const InputEvent &event);
	virtual void draw(){}
	virtual void update(){}
	virtual bool onInput(const InputEvent &event){return 0;};

};