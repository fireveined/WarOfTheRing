#include "Map.h"
#include "common/tokenizer.h"
#include "device.h"
#include "resmanager.h"
#include "Effect.h"
#include "gameplay.h"
#include "common/tokenizer.h"

string convertSpaces(string s)
{
	for(int a=0;a<s.size();a++)
		if(s[a]==' ')s[a]='*';
	return s;
}

void CMap::loadMap(string file)
{
	this->setSelectedObject(0);	
	towns.clear();
	regions.clear();
	armies.clear();
	mapRoads.clear();


	CTokenizer tok;
	tok.TokenizeFile("data/map/mapa2.txt");

	regionsImagePB = clan::PixelBuffer(tok.GetToken()).copy();
	regionsImage=Image(GetGC(), regionsImagePB, Rect(0,0, regionsImagePB.get_size()));

	regionsImagePB = clan::PixelBuffer(tok.GetToken()).copy();
	string mapname=tok.GetToken();

	int num = tok.GetParam();

	for(int a=0;a<num;a++)
	{
		int id = tok.GetParam();

		string name=tok.GetToken();

		int t[4]={tok.GetParam(),tok.GetParam(),tok.GetParam(),tok.GetParam()};
		Rect imgR(t[0], t[1], t[2], t[3]);

		int t2[4]={tok.GetParam(),tok.GetParam(),tok.GetParam(),tok.GetParam()};
		Rect mapR(t2[0], t2[1], t2[2], t2[3]);

		int pop=tok.GetParam();
		int res=tok.GetParam();
		int ter=tok.GetParam();
		regions.push_back(CRegion(id, imgR, mapR, (eResType)(res/3), res%3+1));
		regions[id].setStat("population", pop);
		regions[id].setTerrain((eTerrainType)ter);
		regions[id].setName(name);
	}


		 num = tok.GetParam();

	for(int a=0;a<num;a++)
	{
		int id = tok.GetParam();
		if(id==-1)
		{
			towns.push_back(CTown(id, 1, Point(), (eTownType)(2)));
			towns[towns.size()-1].deleteTown();
		}
		else
		{
		int reg= tok.GetParam();
		int type= tok.GetParam();

		int x=tok.GetParam(),y=tok.GetParam();
		Point pos(x,y);

		string name=tok.GetToken();

			addTown(CTown(id, reg, pos, (eTownType)(type)));

			towns[id].setName(name);
			towns[id].setStat("base_points", tok.GetParam());
			towns[id].setOwner(tok.GetParam());
				countries[towns[id].getOwner()].addTown(id);
			towns[id].setStat("got_image", tok.GetParam());

				  	for(int a=0;a<4;a++)
						towns[id].setStat("slider"+IntToStr(a), tok.GetParam()/3000.0f);

						for(int a=0;a<4;a++)
							towns[id].setStat("slider"+IntToStr(a)+"_aim", towns[id].getStat("slider"+IntToStr(a)));

					towns[id].setStat("upgrade", tok.GetParam());
					towns[id].setStat("fortyfications", tok.GetParam());
					towns[id].setStat("barracks", tok.GetParam());



		armies.push_back(CArmy(armies.size(), towns[id].getCenter(),  towns[id].getOwner()));

		}

	}

			 num = tok.GetParam();

	for(int a=0;a<num;a++)
	{
		int t1 = tok.GetParam();

		int t2= tok.GetParam();
		int type= tok.GetParam();

				sRoad road;
						road.town1=t1; road.town2=t2; road.id=a; road.exist=1; road.upgraded=type; 
						road.length=towns[t1].getCenter().distance(towns[t2].getCenter()); 
						mapRoads.push_back(road);
						towns[t1].addRoad(road.id);
						towns[t2].addRoad(road.id);
			

}



				 num = tok.GetParam();
	for(int a=0;a<num;a++)
	{
			int x=tok.GetParam(),y=tok.GetParam();
		Point pos(x,y);
		int owner = tok.GetParam();
		int count= tok.GetParam();

		armies.push_back(CArmy(armies.size(), pos,  owner));

		for(int z=0; z<count;z++)
		{
				int type= tok.GetParam();
			CUnit u=CUnit::getUnit(type/6, type%6);
			armies[armies.size()-1].getUnitByType(u.getType())->addStat("count", tok.GetParam());
		}
	

	

}


}

void CMap::saveMap(string file)
{

//PathHelp.

//		regionsImage.set_subimage(GetGC(), 0,0, regionsImagePB, Rect(0,0,w, h));	
	//	PNGProvider::save(regionsImagePB, "data/map/mapImage.png");
		ofstream myfile;
  myfile.open ("data/map/mapa2.txt", ios::trunc | ios::out);
  myfile << "data/map/mapImage.png ";
  myfile<<"data/map/region_map.png ";
  myfile<<convertSpaces("Nazwa mapy");
  myfile<<"\n";
  myfile<<regions.size()<<" ";
  myfile<<"\n";
	for(int a=0;a<regions.size();a++)
	{
		  myfile << a<<" ";
		  Rect r=regions[a].getImage();
		  myfile<<convertSpaces(regions[a].getName())<<" ";
	myfile<<r.left<<" "<<r.top<<" "<<r.right<<" "<<r.bottom<<" ";
	r=regions[a].getPositionReal();
	myfile<<r.left<<" "<<r.top<<" "<<r.right<<" "<<r.bottom<<" ";

	myfile<<regions[a].getStat("population")<<" ";
	myfile<<(int)regions[a].getResType()*3+regions[a].getResAmount()-1<<" ";

	myfile<<(int)regions[a].getTerrain()<<" ";
	myfile<<"\n";
	}



	  myfile<<towns.size()<<" ";
	  myfile<<"\n";
	for(int a=0;a<towns.size();a++)
	{
		if(towns[a].ifExitst()==0)
			myfile<<-1<<" ";
		else
		{
		  myfile << a<<" ";
		  
		  myfile<<towns[a].getRegion()<<" ";
		  myfile<<(int)towns[a].getType()<<" ";

		  myfile<<towns[a].getPosition().get_top_left().x<<" ";
		myfile<<towns[a].getPosition().get_top_left().y<<" ";

		  myfile<<convertSpaces(towns[a].getName())<<" ";

		  myfile<<(int)towns[a].getStat("base_points")<<" ";
		  myfile<<towns[a].getOwner()<<" ";
		  	  myfile<<towns[a].getStat("got_image")<<" ";

			  	for(int z=0;z<4;z++)
					  myfile<<towns[a].getStat("slider"+IntToStr(z))<<" ";

				myfile<<towns[a].getStat("upgrade")<<" ";
				myfile<<towns[a].getStat("fortification")<<" ";
				myfile<<towns[a].getStat("barracks")<<" ";
		}
				myfile<<"\n";
	}


	int roadsize=0;
		for(int a=0;a<mapRoads.size();a++)
		if(mapRoads[a].exist==1)
			roadsize++;

	  myfile<<roadsize<<" ";
	  myfile<<"\n";
	for(int a=0;a<mapRoads.size();a++)
	{
		if(mapRoads[a].exist==1)
		{
			  myfile<<mapRoads[a].town1<<" ";
			  myfile<<mapRoads[a].town2<<" ";
			  myfile<<"0"<<" ";
				}
			  myfile<<"\n";
	}


		int armiessize=0;
		for(int a=0;a<armies.size();a++)
			if(armies[a].ifExitst()==1)
			armiessize++;

	  myfile<<armiessize<<" ";
		  myfile<<"\n";
	for(int a=0;a<armies.size();a++)
	{
				if(armies[a].ifExitst())
		{
		myfile<<armies[a].getPosition().x<<" ";
		myfile<<armies[a].getPosition().y<<" ";
		myfile<<armies[a].getOwner()<<" ";
		myfile<<armies[a].getUnitsCount()<<" ";

			for(int z=0;z<armies[a].getUnitsCount();z++)
	{
		myfile<<armies[a].getUnit(z)->getType()<<" ";
		myfile<<armies[a].getUnit(z)->getStat("count")<<" ";
			}
				}
		myfile<<"\n";
	}


  myfile.close();
 changeMapDrawMode(eMapDrawMode::terrain);
}


string getLongString(CTokenizer* tok)
{

	string ret;
	string token=tok->GetToken();
	while(token[token.size()-1]!='\"')
	{
		ret+=tok->GetToken(0)+" ";
		token=tok->GetToken();
	}
	ret+=tok->GetToken(0).substr(0, tok->GetToken(0).size()-1);
	return ret.substr(1,9999);
}
void CMap::loadDatabase(string file)
{

	CTokenizer base;
	base.TokenizeFile("data/database/database.txt");


	while(base.ParseToken())
	{
	
		CTokenizer tok;
		tok.TokenizeFile("data/database/"+base.GetToken(1));

	tok.GetToken();
	string name=tok.GetToken();
	Color color;

	
	int unit_id=0;
	while(tok.ParseToken())
	{
		string token=tok.GetToken(0);

		if(token=="color:")
			{
				int col[3]={tok.GetParam(), tok.GetParam(), tok.GetParam()};
		color=Color(col[0], col[1], col[2], 255);
		}
		else
		if(token=="unit:")
		{
			
			unitTemplates[countries.size()][unit_id].name=getLongString(&tok);
			int unit_typ=0;
			tok.ParseToken();

			while(tok.GetToken(1)!="}")
			{
				string token=tok.GetToken(0);
				if(token=="describe:")unitTemplates[countries.size()][unit_id].describe=getLongString(&tok);
				else
				if(token=="type:")
				{
					string typ=tok.GetToken(1);
					if(typ=="swordsman")unitTemplates[countries.size()][unit_id].unitType=eUnitType::swordsman;
					if(typ=="archer")unitTemplates[countries.size()][unit_id].unitType=eUnitType::archer;
					if(typ=="pikeman")unitTemplates[countries.size()][unit_id].unitType=eUnitType::pikeman;
					if(typ=="cavalaryman")unitTemplates[countries.size()][unit_id].unitType=eUnitType::cavalaryman;

				}
				else
				{
					string name=token.substr(0, token.size()-1);
					float v=tok.GetParam();
					unitTemplates[countries.size()][unit_id].setStat(name, v);

					if(name=="trainingTime")unitTemplates[countries.size()][unit_id].costs[(int)RES_TIME]=v*24*ONE_HOUR;
					if(name=="costIron")unitTemplates[countries.size()][unit_id].costs[(int)RES_IRON]=v;
					if(name=="costGold")unitTemplates[countries.size()][unit_id].costs[(int)RES_GOLD]=v;
					if(name=="costFood")unitTemplates[countries.size()][unit_id].costs[(int)RES_FOOD]=v;
					if(name=="costTimber")unitTemplates[countries.size()][unit_id].costs[(int)RES_TIMBER]=v;

				}

			}
			unitTemplates[countries.size()][unit_id].setStat("morale", unitTemplates[countries.size()][unit_id].getStat("baseMorale"));
						unitTemplates[countries.size()][unit_id].setStat("count", 0);
			unitTemplates[countries.size()][unit_id].nation=countries.size();
			unitTemplates[countries.size()][unit_id].icon=unit_id;
			unit_id++;


		}

	}


	countries.push_back(CCountry(countries.size(), name, Colorf(color)));;
	}
}
