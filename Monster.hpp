#include "Attack.hpp"

//Typenliste:
//Wasser 1
//Feuer 2
//Elektro 3
//Stein 4
//Wind 5
//Pflanze 6
//Psycho 7
int checktype(int typ1, int typ2){//Liste fuer Modifikatoren basierend auf Typanfaelligkeiten; 1 sehr effektiv (4/3), 2 nicht sehr effektiv (3/4)
	switch(typ1){
	break;
	case 1: switch(typ2){
	case 2: return 1;break;
	case 4: return 1;break;
	case 6: return -1;break;
	}
	break;
	case 2: switch(typ2){
	case 1: return -1;break;
	case 2: return -1;break;
	case 4: return -1;break;
	case 6: return 1;break;
	}
	break;
	case 3: switch(typ2){
	case 1: return 1;break;
	case 4: return -1;break;
	case 5: return 1;break;
	}
	break;
	case 4: switch(typ2){
	case 2: return 1;break;
	case 3: return 1;break;
	case 5: return -1;break;
	}
	break;
	case 5: switch(typ2){
	case 4: return -1;break;
	case 6: return 1;break;
	}
	break;
	case 6: switch(typ2){
	case 1: return 1;break;
	case 2: return -1;break;
	case 4: return 1;break;
	case 5: return -1;break;
	}
	break;
	case 7: switch(typ2){
	case 2: return 1;break;
	case 3: return 1;break;
	case 5: return 1;break;
	case 6: return 1;break;
	}
	break;
	}
	return 0;
}


class Monster  //Monsterart gibt allgemeine Werte fuer jedes Monster dieser Art an; Name, Typ und Kennnummer, Basiswerte und Levelmodifikatoren, welche Attacken es beherrscht
{
public:
	string name;
    int type; //types: water, fire, electro, stone, wind, grass, psycho
    int dexNum;
    double atkbase;
    double defbase;
    double initbase;
    double atkmod;
    double defmod;
    double initmod;
    int xpval; //Erfahrungsbasiswert nach Besiegen dieses Monstertyps
    int maxLevel; //Level, nach dem Evolution stattfindet
    int nextevo; // dexNum der naechsten evolution. nextevo ist gleich wie eigene dexNum wenn es keine weitere Evolution gibt
    Attack baseattack1;
    Attack baseattack2;
    SDL_Surface* sprite;
    SDL_Surface* spritem;

    //Konstruktor
    Monster(string name, int type, int dexNum, double atkbase, double defbase, double initbase, double atkmod, double defmod, double initmod, int xpval, int maxLevel, int nextevo, Attack baseattack1, Attack baseattack2, SDL_Surface* sprite, SDL_Surface* spritem){
    	this-> name = name;
    	this-> type = type;
    	this-> dexNum = dexNum;
    	this-> atkbase = atkbase;
    	this-> defbase = defbase;
    	this-> initbase = initbase;
    	this-> atkmod = atkmod;
    	this-> defmod = defmod;
    	this-> initmod = initmod;
    	this-> xpval = xpval;
    	this-> maxLevel = maxLevel;
    	this-> nextevo = nextevo;
    	this-> baseattack1 = baseattack1;
    	this-> baseattack2 = baseattack2;
    	this-> sprite = sprite;
    	this-> spritem = spritem;
    };
    Monster(){};

private:
};

// Attacken (name, typ, strength, precision, manacost)
Attack struggle("Struggle", 7, 10, 80, 0);
Attack aquaBubble("Aqua Bubble", 1, 25, 70, 10);
Attack waterfall("Waterfall", 1, 25, 100, 25);
Attack iceThorn("Ice Thorn", 1, 50, 70, 30);
Attack lavaspit("Lavaspit", 2, 35, 70, 15);
Attack cinders("Cinders", 2, 25, 90, 20);
Attack thirdDegreeBurn("Third Degree Burn", 2, 45, 90, 25);
Attack lightning("Lightning", 3, 45, 80, 25);
Attack staticDischarge("Static Discharge", 3, 20, 95, 15);
Attack dust("Dust", 4, 15, 100, 10);
Attack slingshot("Slingshot", 4, 35, 80, 20);
Attack landslide("Landslide", 4, 25, 100, 35);
Attack tackle("Tackle", 4, 25, 70, 10);
Attack swoop("Swoop", 5, 30, 80, 15);
Attack hurricane("Hurricane", 5, 50, 65, 20);
Attack growl("Growl", 5, 15, 100, 10);
Attack solarBeam("Solar Beam", 6, 40, 80, 25);
Attack vineWhip("Vine Whip", 6, 30, 90, 10);
Attack razorLeaf("Razor Leaf", 6, 45, 85, 25);
Attack mindBlast("Mind Blast", 7, 50, 100, 20);
Attack shadowTorrent("Shadow Torrent", 7, 60, 80, 20);


// Erstelle die Monster (name, typ, dexNum, atkbase, defbase, initbase, atkmod, defmod, initmod, maxLevel, nextevo, baseattack1, baseattack2, sprite, spritem)
Monster none("None", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, struggle, struggle, IMG_Load("blackbar.png"), IMG_Load("blackbar.png"));
Monster diplomaticturtle("Diplomaticturtle", 1, 1, 15, 18, 12, 0.75, 0.9, 0.6, 60, 30, 1, waterfall, slingshot, IMG_Load("mwater1.png"), IMG_Load("mwater1m.png"));
Monster squirtula("Squirtula", 1, 2, 15, 12, 18, 0.75, 0.6, 0.9, 50, 30, 2, aquaBubble, vineWhip, IMG_Load("mwater2.png"), IMG_Load("mwater2m.png"));
Monster charwizard("Charwizard", 2, 3, 18, 12, 15, 0.9, 0.6, 0.75, 60, 30, 3, lavaspit, staticDischarge, IMG_Load("mfire3.png"), IMG_Load("mfire3m.png"));
Monster charglide("Charglide", 2, 4, 18, 15, 15, 0.6, 0.5, 0.5, 55, 19, 5, cinders, swoop, IMG_Load("mfire1.png"), IMG_Load("mfire1m.png"));
Monster charmelon("Charmelon", 2, 5, 21, 15, 18, 1, 0.75, 0.75, 70, 30, 5, thirdDegreeBurn, hurricane, IMG_Load("mfire2.png"), IMG_Load("mfire2m.png"));
Monster bwazapp("Bwazapp", 3, 6, 12, 12, 18, 0.4, 0.3, 0.7, 45, 11, 7, staticDischarge, growl, IMG_Load("melectro1.png"), IMG_Load("melectro1m.png"));
Monster zappzor("Zappzor", 3, 7, 18, 15, 21, 0.9, 0.6, 1.1, 65, 30, 7, lightning, solarBeam, IMG_Load("melectro2.png"), IMG_Load("melectro2m.png"));
Monster marblous("Marblous", 4, 8, 10, 21, 8, 0.6, 1, 0.2, 55, 14, 9, tackle, slingshot, IMG_Load("mrock1.png"), IMG_Load("mrock1m.png"));
Monster marbgiant("Marbgiant", 4, 9, 12, 22, 12, 0.75, 1.1, 0.4, 70, 30, 9, iceThorn, landslide, IMG_Load("mrock2.png"), IMG_Load("mrock2m.png"));
Monster angrybird("Angrybird", 5, 10, 12, 8, 18, 0.6, 0.3, 0.7, 30, 9, 11, growl, tackle, IMG_Load("mwind1.png"), IMG_Load("mwind1m.png"));
Monster madbird("Madbird", 5, 11, 15, 12, 18, 0.7, 0.4, 0.9, 55, 30, 11, swoop, waterfall, IMG_Load("mwind2.png"), IMG_Load("mwind2m.png"));
Monster nomflower("Nomflower", 6, 12, 18, 15, 12, 0.9, 0.75, 0.6, 60, 30, 12, vineWhip, dust, IMG_Load("mgrass1.png"), IMG_Load("mgrass1m.png"));
Monster rootshoes("Rootshoes", 6, 13, 15, 15, 15, 0.75, 0.75, 0.75, 50, 30, 13, razorLeaf, staticDischarge, IMG_Load("mgrass2.png"), IMG_Load("mgrass2m.png"));
Monster weirdboy("Weirdboy", 6, 14, 12, 18, 15, 0.7, 0.8, 0.75, 60, 30, 14, mindBlast, solarBeam, IMG_Load("mpsycho1.png"), IMG_Load("mpsycho1m.png"));
Monster scaryskull("Scaryskull", 6, 15, 18, 12, 15, 0.9, 0.7, 0.8, 80, 30, 15, shadowTorrent, iceThorn, IMG_Load("mpsycho2.png"), IMG_Load("mpsycho2m.png"));

class individuum
{
public:

	Monster monster;
	string name;
	int type;
    int level;	// 30 ist erst mal das maximale Level
    double health;
    double mana;
    double atk;
    double def;
    double init;
    int maxLevel;
    int nextevo; // dexNum der naechsten evolution. nextevo ist gleich wie eigene dexNum wenn es keine weitere Evolution gibt
    double xp;
    Attack attack1;
    Attack attack2;
    Attack attack0 = struggle;

    //Konstruktor
    individuum(Monster monster, int level){
    	this-> monster = monster;
    	name = monster.name;
    	type = monster.type;
    	atk = monster.atkbase+monster.atkmod*level;
    	def = monster.defbase+monster.defmod*level;
    	init = monster.initbase+monster.initmod*level;
    	maxLevel = monster.maxLevel;
    	nextevo = monster.nextevo;
    	attack1 = monster.baseattack1;
    	attack2 = monster.baseattack2;
    	this-> level = level;
    	health = 100;
    	mana = 100;
    	xp = 0;
    };
    individuum(){};

	void evolution(){
        switch (monster.dexNum){
            case 4: monster = charmelon; break;
            case 6: monster = zappzor; break;
            case 8: monster = marbgiant; break;
            case 10: monster = madbird; break;
        }
    	name = monster.name;
    	type = monster.type;
    	atk = monster.atkbase+monster.atkmod*level;
    	def = monster.defbase+monster.defmod*level;
    	init = monster.initbase+monster.initmod*level;
    	maxLevel = monster.maxLevel;
    	nextevo = monster.nextevo;
    	attack1 = monster.baseattack1;
    	attack2 = monster.baseattack2;
		};

	void levelup(){
		if(level<30){
			level = level+1;
			if (level > maxLevel){
				evolution();
			}
	    	atk = monster.atkbase+monster.atkmod*level;
	    	def = monster.defbase+monster.defmod*level;
	    	init = monster.initbase+monster.initmod*level;
		}
		if(level==30){
			return;
		}
	};

	bool gainXP(individuum ind){
		bool levelup=false;
		xp = ind.monster.xpval;//Modifikatoren herausgenommen, damit es grundsaetzlich funktioniert
		if (xp >= 100){
			xp = xp-100;
			levelup=true;
		}
		return levelup;
	};

	pair<double,int> angriff(Attack attk, int p){
		double dmg;
		int r=rand() % 100+1;//ueberpruefe ob Treffer
		if (r>attk.precision){
			dmg=0;//falls nicht kein Schaden
		}
		else {
			if(p==1){
				dmg=attk.strength*atk*1.3;//Schaden aus Angriff des Dieners und Staerke der Attacke; Spielerangriff ein wenig staerker
			}
			else{
				dmg=attk.strength*atk;
			}
		}
		pair<double,int> tempdmg (dmg,attk.type);
		mana-=attk.manacost;
		return tempdmg;//Uebergibt pair aus Schadenswert und Typ
	};

	void verteidigen(pair<double, int> tempdmg, int p){//Uebernimmt pair aus Schadenswert und Typ
		int effective=checktype(tempdmg.second,type);
		double dmg;
		switch(effective){//modifiziert nach Effektivitaetsmultiplikator (auf 3/4 bzw 4/3)
		case -1: dmg=tempdmg.first*0.75/def; break;
		case 0: dmg=tempdmg.first/def; break;
		case 1: dmg=tempdmg.first*1.33/def; break;
		}
		if(p==1){
			dmg=1.3*dmg;
		}
		health-=dmg;//zieht Schaden ab und setzt Health minimal auf null
		if(health<0){
			health=0;
		}
		return;
	};


};
