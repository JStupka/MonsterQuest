#include "Monster.hpp"

class Spieler  //Spieler mit 3 Monstern und Zaehlern fuer Traenke, Name momentan ungenutzt, bool trainer gibt an, ob Gegner wild oder nicht
{
public:
	string name;
	int healthpot;
	int manapot;
	individuum monster1;
	individuum monster2;
	individuum monster3;
	bool trainer;
	Spieler(string name, individuum monster1, individuum monster2, individuum monster3, bool trainer, int healthpot, int manapot){
		this-> name = name;
		this-> monster1 = monster1;
		this-> monster2 = monster2;
		this-> monster3 = monster3;
		this-> trainer = trainer;
		this-> healthpot = healthpot;
		this-> manapot = manapot;
	};

	double level(){
		double monlevel1 = monster1.level;
		double monlevel2 = monster2.level;
		double monlevel3 = monster3.level;
		double levelsumme = monlevel1 + monlevel2 + monlevel3;
		double durchschnittslevel = levelsumme/3;
		return durchschnittslevel;
	}

	void usepotion(bool mahe, individuum monster){ // mahe = 1 -> mana; mahe = 0 -> health
		if (mahe){
			monster.mana = 100;// zur Einfachheit gibt es erst mal nur eine Sorte an Traenken die health oder mana direkt auf 100 setzt
			manapot --;
		}
		else{
			monster.health = 100;
			healthpot --;
		}
	}

};
