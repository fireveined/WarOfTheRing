#include "GameMenu.h"
#include "device.h"
#include "ResManager.h"
#include "gui/gui_button.h"
#include "gui/gui_manager.h"
#include <algorithm>
#include <fstream>
#include "LinearParticle/L_ParticleSystem.h"


Size GetTextSize(std::string font, std::string text)
{
	return GetFont(font).get_text_size(GetGC(),text);
};

/*
void CGameMenu::PlayButtonFunc()
{
GameStates[GAME_PLAY_OPTIONS]->Active();
Deactive();
CGameState::SetActState(GAME_PLAY_OPTIONS);
}

void CGameMenu::ExitButtonFunc()
{
	CDevice::GetDevice()->End();
}
*/

void CGameMenu::onClick(CGUIComponent* c, int key)
{
	if(key==mouse_left)
	{
	if(c->getName()=="exit")
		CDevice::GetDevice()->End();

		if(c->getName()=="load")
		{
			Deactive();
			CGameState::SetActState(GAME_LOAD);
			CDevice::GetDevice()->GetActGameState()->Active();
		}

				if(c->getName()=="campaign")
		{
			Deactive();
			CGameState::SetActState(GAME_CAMPAIGN);
			CDevice::GetDevice()->GetActGameState()->Active();
		}

				
						if(c->getName()=="scrimmish")
		{
			Deactive();
			CGameState::SetActState(GAME_PLAY);
			CDevice::GetDevice()->GetActGameState()->Active();
		}

						if(c->getName()=="options")
		{
			Deactive();
			CGameState::SetActState(GAME_OPTIONS);
			CDevice::GetDevice()->GetActGameState()->Active();
		}



	}




}

Image miniMap;
	clan::PixelBuffer pixelBuffer;

		Image MapImage, WaterImage;
	FrameBuffer MapFramebuffer, WaterFramebuffer;
	Canvas MapCanvas, WaterCanvas;
	int ww=5555,hh=5555;
void CGameMenu::Init()
{
	/*
		pixelBuffer=PixelBuffer(5000, 5000, tf_rgba8).copy();
	miniMap=Image(GetGC(), pixelBuffer, Rect(0,0,Size(5000,5000)));

	Texture2D MapTexture=Texture2D(GetGC(), ww, hh);

	MapImage = Image(MapTexture, MapTexture.get_size() );
	MapFramebuffer = FrameBuffer(GetGC());
	MapFramebuffer.attach_color(0, MapTexture);
	MapCanvas = Canvas(GetGC(), MapFramebuffer);

	*/
	GUI=new CGUIContainer("main_menu");
	CGUIManager::GetGUIManager()->addChild(GUI);

	GUI->setTheme(sTheme("default_theme"));


	GUI->addChild(new CGUIButton("campaign", "Kampania", Point(90,100)))->setWidth(290);
	GUI->addChild(new CGUIButton("scrimmish", "Wolna gra", Point(90,150)))->setWidth(290);
	GUI->addChild(new CGUIButton("load", "Wczytaj", Point(90,200)))->setWidth(290);
	GUI->addChild(new CGUIButton("options", "opcje", Point(90,250)))->setWidth(290);
	GUI->addChild(new CGUIButton("exit", "wyjœcie", Point(90,300)))->setWidth(290);

	GUI->getChild("exit")->setOnClick(MakeDelegate(this, &CGameMenu::onClick));
	GUI->getChild("scrimmish")->setOnClick(MakeDelegate(this, &CGameMenu::onClick));
	GUI->getChild("load")->setOnClick(MakeDelegate(this, &CGameMenu::onClick));
	GUI->getChild("options")->setOnClick(MakeDelegate(this, &CGameMenu::onClick));
	GUI->getChild("options")->setTooltip("Wybierz opcje gry");

	GUI->getChild("campaign")->setOnClick(MakeDelegate(this, &CGameMenu::onClick));



		//GUI->addChild(new CGUIButton("button2", "gui_themes", Rect(118,451, Size(80,80)), Point(250,100)));
	
}


void CGameMenu::Render()
{

		}

void CGameMenu::Update()
{
	
	if(0)
	{
clan::PixelBuffer pb("data/map/region_map.png");
	unsigned char *map_data = pb.get_data_uint8();
		int iw=pb.get_width();
	int ih=pb.get_height();

	int pitch2=pb.get_pitch();
	int bpp2=pb.get_bytes_per_pixel();

	int regionsNum=map_data[0];
	int pos1[2][255];
	int pos2[2][255];
	Rect regionsRects[255][2];
	for(int a=0;a<regionsNum;a++){pos1[0][a]=0, pos1[1][a]=0, pos2[0][a]=0, pos2[1][a]=0;}


	for(int a=0;a<regionsNum;a++)
		for(int x=0;x<iw;x++)
			for(int y=0;y<ih;y++)
		{	
			if(map_data[(y)*pitch2+(x)*bpp2]==a+1 && map_data[(y)*pitch2+(x)*bpp2+2]%5==0 && map_data[(y)*pitch2+(x)*bpp2+1]==255)
			{

				if(pos1[0][a]==0 || pos1[0][a]>x)pos1[0][a]=x;
			if(pos1[1][a]==0 || pos1[1][a]>y)pos1[1][a]=y;
			if(pos2[0][a]<x)pos2[0][a]=x;
			if(pos2[1][a]<y)pos2[1][a]=y;

			}

			}

int w=0,h=0;
	for(int a=0;a<regionsNum;a++)
	{
		if(h<pos2[1][a]-pos1[1][a]+1)h=pos2[1][a]-pos1[1][a]+1;
		w+=pos2[0][a]-pos1[0][a]+1;
	}
		clan::PixelBuffer regionsImagePB=PixelBuffer(w,h, tf_rgba8).copy();
	//regionsImage=Image(GetGC(), regionsImagePB, Rect(0,0,Size(w, h)));
	unsigned char *regions_data = (unsigned char *) regionsImagePB.get_data();
		int pitch=regionsImagePB.get_pitch();
	int bpp=regionsImagePB.get_bytes_per_pixel();

//	int pitchMain=mainMap.get_pitch();
				for(int x=0;x<w;x++)
		for(int y=0;y<h;y++)
			regions_data[(y)*pitch+(x)*bpp+3]=0;

		int off=0;
	for(int a=0;a<regionsNum;a++)
	{
		Color col(rand()%255, rand()%255, rand()%255);
			for(int x=pos1[0][a];x<pos2[0][a]+1;x++)
		for(int y=pos1[1][a];y<pos2[1][a]+1;y++)
		{
			if(map_data[(y)*pitch2+(x)*bpp2]==0 && map_data[(y)*pitch2+(x)*bpp2+2]==0 && map_data[(y)*pitch2+(x)*bpp2+1]==0 && map_data[(y)*pitch2+(x)*bpp2+3]>100)
			{

					regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp]=map_data[(y)*pitch2+(x)*bpp2];
			regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp+1]=map_data[(y)*pitch2+(x)*bpp2+1];
			regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp+2]=map_data[(y)*pitch2+(x)*bpp2+2];
			regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp+3]=rand()%30+30;
			}
			else
if(map_data[(y)*pitch2+(x)*bpp2]==a+1 && map_data[(y)*pitch2+(x)*bpp2+2]%5==0 && map_data[(y)*pitch2+(x)*bpp2+1]==255)
{	
	int alpha=90;
	bool border=0;


int cx=(pos1[0][a]+pos2[0][a])/2;
int cy=(pos1[1][a]+pos2[1][a])/2;
float cw=(pos2[0][a]-pos1[0][a])/2;
float ch=(pos2[1][a]-pos1[1][a])/2;
//alpha=(1-abs(cx-x)/cw)*50*(1-abs(cx-x)/cw)*(1-abs(cx-x)/cw)+40 +(1-abs(cy-y)/ch)*50*(1-abs(cy-y)/ch)*(1-abs(cy-y)/ch)+40;

	for(int xx=x-1;xx<x+2;xx++)
			for(int yy=y-1;yy<y+2;yy++)
if(!(map_data[(yy)*pitch2+(xx)*bpp2]==a+1 && map_data[(yy)*pitch2+(xx)*bpp2+2]%5==0 && map_data[(yy)*pitch2+(xx)*bpp2+1]==255))
	{
	//regions_data[(yy-pos1[1][a])*pitch+(xx-pos1[0][a]+off)*bpp]=0;
			//regions_data[(yy-pos1[1][a])*pitch+(xx-pos1[0][a]+off)*bpp+1]=0;
			//regions_data[(yy-pos1[1][a])*pitch+(xx-pos1[0][a]+off)*bpp+2]=0;
			alpha=45;
			yy=9999;
			xx=9999;
      border=1;
	}

	//if(!border)
	{
	regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp]=255;
			regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp+1]=255;
			regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp+2]=255;
	}
						regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp+3]=alpha;
}
else
	regions_data[(y-pos1[1][a])*pitch+(x-pos1[0][a]+off)*bpp+3]=0;
		}
		regionsRects[a][1]=Rect(pos1[0][a]*1/0.15-3, pos1[1][a]*1/0.15-3, (pos2[0][a]+1)*1/0.15+3, (pos2[1][a]+1)*1/0.15+3);
		regionsRects[a][0]=Rect(off,0,  pos2[0][a]-pos1[0][a]+off+1, pos2[1][a]-pos1[1][a]+1);
		off+=pos2[0][a]-pos1[0][a]+1;
	}


//		regionsImage.set_subimage(GetGC(), 0,0, regionsImagePB, Rect(0,0,w, h));	
		PNGProvider::save(regionsImagePB, "data/map/mapImage.png");
		ofstream myfile;
  myfile.open ("data/map/mapDescribe.txt", ios::trunc | ios::out);
  myfile << "data/map/mapImage.png ";
  myfile<<"data/map/region_map.png ";
  myfile<<regionsNum<<" ";
	for(int a=0;a<regionsNum;a++)
	{
		  myfile << a+1<<" ";
		  Rect r=regionsRects[a][0];
	myfile<<r.left<<" "<<r.top<<" "<<r.right<<" "<<r.bottom<<" ";
	r=regionsRects[a][1];
	myfile<<r.left<<" "<<r.top<<" "<<r.right<<" "<<r.bottom<<" ";
	}

  myfile.close();

		//largeMapImage=Image(GetGC(), mainMap, Rect(0,0, mainMap.get_size()));
		//regionsImagePB=pb.copy();
  exit(1);
  }
}

 void CGameMenu::onInput(const InputEvent &event)
 {


 }

void CGameMenu::Active()
{
	
				GUI->setVisible(1);


}

void CGameMenu::Deactive()
{

				GUI->setVisible(0);

}

