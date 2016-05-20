
#include "GamePlay.h"
#include <string>
using namespace std;

string TRANS(string str)
{

	if(str=="res0")return "Zboże";
	if(str=="res1")return "Ryby";
		if(str=="res2")return "Drewno";
	if(str=="res3")return "Kamień";
	if(str=="res4")return "Żelazo";
	if(str=="res5")return "Złoto";
		if(str=="res7")return "Pożywienie";
	if(str=="res8")return "Materiały budowlane";


	if(str=="terrain0")return "Las";
	if(str=="terrain1")return "Góry";
	if(str=="terrain2")return "Wzgórza";
	if(str=="terrain3")return "Równina";
	if(str=="terrain4")return "Bagna";
	if(str=="terrain5")return "Pustynia";

	if(str=="build0")return "Fortyfikacje";
	if(str=="build1")return "Koszary";
	if(str=="build2")return "Ratusz";

	if(0)
	{
	if(str=="Przychód")return "Income";
	if(str=="Wykorzystanie")return "Use";

	}
	return str;
}

