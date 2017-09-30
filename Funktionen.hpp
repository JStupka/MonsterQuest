#include "graphics.hpp"



int attackalgorithm(individuum monpact, individuum moneact){//entscheide, welche Attacke Gegner verwendet
	if(moneact.mana<moneact.attack1.manacost){//teste, ob zureichend Mana fuer Angriff
		if(moneact.mana<moneact.attack2.manacost){
			return 0;//falls Mana unzureichend fuer beide, nutze Verzweifler
		}
		else{
			return 2;//zu wenig Mana fuer 1-->Angriff 2
		}
	}
	if(moneact.mana<moneact.attack2.manacost){
		return 1;//zu wenig Mana fuer 2-->Angriff 1
	}
	else{//genug Mana fuer beide
		int r=rand()%100+1;
		int r1;
		int sus1=checktype(moneact.attack1.type,monpact.type);//pruefe auf Typanfaelligkeiten
		int sus2=checktype(moneact.attack2.type,monpact.type);
		if(sus1>sus2){//falls anfaelliger auf Angriff 1 als auf 2, nutze mit p=70% Angriff 1
			r1=70;
		}
		if(sus2>sus1){//70% Angriff 2
			r1=30;
		}
		else{//sonst gleich
			r1=50;
		}
		if(r>r1){
			return 2;
		}
		else{
			return 1;
		}
	}
}


tuple<int,individuum,individuum,individuum> combatroutine(Spieler spieler, Spieler enemy){
	bool flightparameter=false;
	int pact=chooseMon(spieler, true);//counter für aktives Monster des Spielers
	int eact=1;//counter für aktives Monster des Gegners
	int enaction;
	char whichaction;
	individuum monpact;//temporaere Diener im Zwischenspeicher
	individuum moneact;
	do{//Matchroutine (3vs3) bis alle Diener eines Kontrahenten besiegt sind
		switch(pact){
		case 1: monpact=spieler.monster1; break;//temporaere Diener im Zwischenspeicher, damit allgemein fuer monster1/2/3 geschrieben werden kann
		case 2: monpact=spieler.monster2; break;
		case 3: monpact=spieler.monster3; break;
		}
		switch(eact){
		case 1: moneact=enemy.monster1; break;
		case 2: moneact=enemy.monster2; break;
		case 3: moneact=enemy.monster3; break;
		}
		while((monpact.health>0) & (moneact.health>0)){//einzelne Kampfroutine (1vs1) bis ein Kaempfer besiegt ist
			combatscreen(monpact, moneact, spieler, enemy);
			SDL_Delay(1500);
			enaction=1;
			whichaction='n';
			SDL_Event event;
			while(whichaction=='n'){//frage Spieleraktion ab
				if ( SDL_PollEvent( &event ) != 0 )
				{
				switch (event.key.keysym.sym)
				   {
				                        case SDLK_1:
				                        	if(monpact.mana>monpact.attack1.manacost){//erlaubt Angriff 1 nur bei zureichendem Mana
				                        	whichaction='1';
				                        	}
				                            break;
				                        case SDLK_2:
				                        	if(monpact.mana>monpact.attack2.manacost){
				                        	whichaction='2';
				                        	}
				                        	break;
				                        case SDLK_0:
				                        	if((monpact.mana<monpact.attack1.manacost)&(monpact.mana<monpact.attack1.manacost)){//erlaubt struggle nur bei unzureichendem Mana
				                        	whichaction='0';
				                        	}
				                        	break;
				                        case SDLK_c:
				                        	if(enemy.trainer==false){//erlaubt Fangen des Monsters nur, wenn es niemandem gehoert (Trainer noch nicht im Spiel)
				                        	whichaction='c';//c fuer cage
				                        	}
				                        	break;
				                        case SDLK_f:
				                        	whichaction='f';
				                        	break;
				                        case SDLK_h:
				                        	if(spieler.healthpot>0){
				                        	whichaction='h';
				                        	}
				                        	break;
				                        case SDLK_m:
				                        	if(spieler.manapot>0){
				                        	whichaction='m';
				                        	}
				                        	break;
				   }
				}
				SDL_FlushEvents(0,-1);
			}
			if(whichaction=='f'){//Flucht bricht sofort Kampf ab
				flightparameter=true;
				break;
			}
			if(whichaction=='h'){//Heiltraenke vor moeglichem Schlagabtausch
				spieler.usepotion(0, monpact);
				combatscreen(monpact, moneact, spieler, enemy);
			}
			if(whichaction=='m'){
				spieler.usepotion(1, monpact);
				combatscreen(monpact, moneact, spieler, enemy);
			}
			if(whichaction=='c'){

				int wahlMon=chooseMon(spieler, false);
				switch(wahlMon){
				case 1: spieler.monster1=moneact; break;
				case 2: spieler.monster2=moneact; break;
				case 3: spieler.monster2=moneact; break;
				}
				moneact.health=0; break;//gegnerisches Monster wird "besiegt"
			}
			if((moneact.health<30) & (enemy.healthpot>0)){//Gegner nutzt Traenke, falls noetig, und verbraucht dabei seine Aktion
				enemy.usepotion(0,moneact);
				combatscreen(monpact, moneact, spieler, enemy);
				enaction=0;
			}
			if((enaction==1) & (moneact.mana<moneact.attack1.manacost) & (moneact.mana<moneact.attack2.manacost) & (enemy.manapot>0)){
				enemy.usepotion(1,moneact);
				combatscreen(monpact, moneact, spieler, enemy);
				enaction=0;
			}

			pair<double,int> ang;//angriff ist Funktion der Klasse Individuum, gibt Angriffsstaerke und Typ aus
			if(moneact.init>monpact.init){//Reihenfolge der Angriffe abhaengig vom Initiativewert der Monster; hier zunaechst Gegner schneller
				if((enaction==1) & (moneact.health>0)){//Gegner greift nur an, falls Aktion noch nicht verbraucht
					int attackswitch=attackalgorithm(monpact,moneact);
					switch(attackswitch){
					case 0: ang=moneact.angriff(moneact.attack0,false); break;//angriff ist Funktion der Klasse Individuum, gibt Angriffsstaerke und Typ aus
					case 1: ang=moneact.angriff(moneact.attack1,false); break;
					case 2: ang=moneact.angriff(moneact.attack2,false); break;
					}
					monpact.verteidigen(ang,true);//verteidigen auch Funktion der Klasse Individuum, nimmt Staerke und Typ and und reduziert HP
					combatscreen(monpact, moneact, spieler, enemy);
					SDL_Delay(1500);
				}
				if(monpact.health>0){//falls angegriffenes Monster noch bei Bewusstsein, Gegenangriff
					switch(whichaction){
					case '0': ang=monpact.angriff(monpact.attack0,true); break;//angriff ist Funktion der Klasse Individuum, gibt Angriffsstaerke und Typ aus
					case '1': ang=monpact.angriff(monpact.attack1,true); break;
					case '2': ang=monpact.angriff(monpact.attack2,true); break;
					}
					moneact.verteidigen(ang,false);
					combatscreen(monpact, moneact, spieler, enemy);
					SDL_Delay(1500);
				}
			}

			if(moneact.init<=monpact.init){
				if(monpact.health>0){
					switch(whichaction){
					case '0': ang=monpact.angriff(monpact.attack0,true); break;//angriff ist Funktion der Klasse Individuum, gibt Angriffsstaerke und Typ aus
					case '1': ang=monpact.angriff(monpact.attack1,true); break;
					case '2': ang=monpact.angriff(monpact.attack2,true); break;
					}
					moneact.verteidigen(ang,false);
					combatscreen(monpact, moneact, spieler, enemy);
					SDL_Delay(1500);
				}
				if((enaction==1) & (moneact.health>0)){//falls angegriffenes Monster noch bei Bewusstsein, Gegenangriff
					int attackswitch=attackalgorithm(monpact,moneact);
					switch(attackswitch){
					case 0: break;
					case 1: ang=moneact.angriff(moneact.attack1,false); break;//angriff ist Funktion der Klasse Individuum, gibt Angriffsstaerke und Typ aus
					case 2: ang=moneact.angriff(moneact.attack2,false); break;
					}
					monpact.verteidigen(ang,true);
					combatscreen(monpact, moneact, spieler, enemy);
					SDL_Delay(1500);
				}
			}
		};//bis ein Kaempfer besiegt
		if(monpact.health>0){//falls Spieler gesiegt, erhoehe XP (irgendetwas stimmt hier nicht)
			bool up = monpact.gainXP(moneact);//boolean gibt an, ob 100% XP ueberschritten
			if(up){
				monpact.levelup();
			}
		}
		switch(pact){//temporaere Daten werden permanent
		case 1: spieler.monster1=monpact; break;
		case 2: spieler.monster2=monpact; break;
		case 3: spieler.monster3=monpact; break;
		}
		switch(eact){
		case 1: enemy.monster1=moneact; break;
		case 2: enemy.monster2=moneact; break;
		case 3: enemy.monster3=moneact; break;
		}
		if(flightparameter==true){
			break;
		}
		if(monpact.health>0){//naechster gegnerischer Diener wird eingesetzt
			eact+=1;
		}
		if(moneact.health>0){//neuer Diener wird ausgewaehlt
			if(spieler.monster1.health+spieler.monster2.health+spieler.monster3.health>0){
			pact = chooseMon(spieler, true);
			}
		}
	}while((enemy.monster1.health+enemy.monster2.health+enemy.monster3.health>0) & (spieler.monster1.health+spieler.monster2.health+spieler.monster3.health>0));//bis alle Kaempfer besiegt
	spieler.monster1.mana=100;//setze Mana zurueck fuer naechsten Kampf
	spieler.monster2.mana=100;
	spieler.monster3.mana=100;
	int result;
	if(flightparameter==true){
		result=0;//weder Sieg noch Niederlage (falls Belohnungen fuer Siege eingebaut werden)
	}
	if(spieler.monster1.health+spieler.monster2.health+spieler.monster3.health>0){//falls Spielerdiener leben
		result=1;//Sieg des Spielers
	}
	else{
		result=-1;//Sieg des Gegners
	}
	tuple<int,individuum,individuum,individuum> combatresult=make_tuple(result,spieler.monster1,spieler.monster2,spieler.monster3);
	return combatresult;
}

