#include "Spieler.hpp"

//Bildschirmgroesse
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;

//initialisiert das Fenster
bool initialize();

//Laedt die Bilder
bool loadMedia();

//Schliesst SDL. Muss noch geaendert werden
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;//pointer

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images we will load and show on the screen
SDL_Surface* gbackgroundMap = IMG_Load("MonsterMap.png");
SDL_Surface* gcharacterLeft = IMG_Load("characterLeft.png");
SDL_Surface* gcharacterRight = IMG_Load("characterRight.png");
SDL_Surface* gcharacterBack = IMG_Load("characterBack.png");
SDL_Surface* gcharacterFront = IMG_Load("characterFront.png");
SDL_Surface* gwind = IMG_Load("wind.png");
SDL_Surface* gfire = IMG_Load("fire.png");
SDL_Surface* gstone = IMG_Load("stone.png");
SDL_Surface* gelectro = IMG_Load("electro.png");
SDL_Surface* gwater = IMG_Load("water.png");
SDL_Surface* ggrass = NULL;
SDL_Surface* gpsycho = IMG_Load("psycho.png");
SDL_Surface* cbackground = IMG_Load("cbackground.png");
SDL_Surface* blackbg = IMG_Load("blackbg.png");
SDL_Surface* whitebg = IMG_Load("whitebg.png");
SDL_Surface* numberzero = IMG_Load("Numero0.png");
SDL_Surface* numberone = IMG_Load("Numero1.png");
SDL_Surface* numbertwo = IMG_Load("Numero2.png");
SDL_Surface* numberthree = IMG_Load("Numero3.png");
SDL_Surface* star = IMG_Load("star.png");
SDL_Surface* stripe = IMG_Load("stripe.png");
SDL_Surface* swind = IMG_Load("swind.png");
SDL_Surface* sfire = IMG_Load("sfire.png");
SDL_Surface* sstone = IMG_Load("sstone.png");
SDL_Surface* selectro = IMG_Load("selectro.png");
SDL_Surface* swater = IMG_Load("swater.png");
SDL_Surface* sgrass = NULL;
SDL_Surface* spsycho = IMG_Load("spsycho.png");
SDL_Surface* cage = IMG_Load("cage.png");
SDL_Surface* flightarrow = IMG_Load("flightarrow.png");
SDL_Surface* hpotion = IMG_Load("hpotion.png");
SDL_Surface* mpotion = IMG_Load("mpotion.png");
SDL_Surface* cimage = IMG_Load("c.png");
SDL_Surface* fimage = IMG_Load("f.png");
SDL_Surface* himage = IMG_Load("h.png");
SDL_Surface* mimage = IMG_Load("m.png");
SDL_Surface* chbg = IMG_Load("chbg.png");
SDL_Surface bar;
SDL_PixelFormat* pixfmt=blackbg->format;
Uint32 color=SDL_MapRGB(pixfmt, 0, 0, 0);


SDL_Rect dest;

pair<bool,Monster> grenzenMonster;


bool initialize()//initialisiert Fenster
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
        SDL_Init(SDL_INIT_EVERYTHING);
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "MonsterQuest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    
    return success;
}

void close()//schliesst Fenster
{
    //Deallocate surface
    SDL_FreeSurface( gbackgroundMap );
    gbackgroundMap = NULL;
    SDL_FreeSurface( gcharacterFront );
    gcharacterFront = NULL;
    
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}


// prueft, dass Character nicht ueber Hindernisse laeuft
pair<bool,Monster> inGrenzen(int x,int y, Spieler spieler){//ueberprueft, ob Bewegung zulaessig und ob man einem Monster begegnet
    if (((x>=0) & (x<=310)) & ((y>=0) & (y<=310))) {// innerhalb bildschirm
        if ((x<213) || (y>=20)){// nicht oben rechts
            if (((x>=280) & (y<255)) || (y<80)){// nicht im Wasser/Electro/Gras Bereich
                int entdeckt=rand() % 6000+1;//Begegnung mit Wahrscheinlichkeit 1:60 (100:6000), kann je nach Gebiet angepasst werden
                if (entdeckt <= 100){//Aufteilung der 100 in Monsterarten
                	if(entdeckt<=5){
                		grenzenMonster = make_pair(true,charwizard);
                	}
                	if((entdeckt>5) & (entdeckt<=30)){
                		if((spieler.level()>=15)&(entdeckt>20)){
                	    grenzenMonster = make_pair(true,marbgiant);
                		}
                		else{
                    	    grenzenMonster = make_pair(true,marblous);
                		}
                	}
                	if((entdeckt>30) & (entdeckt<=70)){
                		if((spieler.level()>=10)&(entdeckt>60)){
                	    grenzenMonster = make_pair(true,madbird);
                		}
                		else{
                    	    grenzenMonster = make_pair(true,angrybird);
                		}
                	}
                	if(entdeckt==71){
                	    grenzenMonster = make_pair(true,weirdboy);
                	}
                	if((entdeckt>71) & (entdeckt<=100)){
                	    grenzenMonster = make_pair(true,rootshoes);
                	}

                    return grenzenMonster;
                }
                else{
                    grenzenMonster = make_pair(true,none);
                    return grenzenMonster;
                }
            }
            else {
                if ((x>=150) & (x<190) & (y<135)){// im Strandbereich (Wasser)
                    int entdeckt=rand() % 6000+1;
                    if (entdeckt <= 100){
                    	if(entdeckt<=10){
                    	     grenzenMonster = make_pair(true,diplomaticturtle);
                    	}
                    	if(entdeckt>10 & entdeckt<=40){
                    	     grenzenMonster = make_pair(true,squirtula);
                    	}
                    	if(entdeckt>40 & entdeckt<=55){
                    	     if((spieler.level()>=15)&(entdeckt>50)){
                    	     grenzenMonster = make_pair(true,marbgiant);
                    	     }
                    	     else{
                    	         grenzenMonster = make_pair(true,marblous);
                    	     }
                    	}
                    	if((entdeckt>55) & (entdeckt<=100)){
                    	     if((spieler.level()>=10)&(entdeckt>85)){
                    	     grenzenMonster = make_pair(true,madbird);
                    	     }
                    	     else{
                    	         grenzenMonster = make_pair(true,angrybird);
                    	     }
                    	}

                        return grenzenMonster;
                        
                    }
                    else{
                        grenzenMonster = make_pair(true,none);
                        return grenzenMonster;
                    }

                }
                else {
                    if ((x>=80) & (x<280) & (y>=210) & (y<255)){// im zweituntersten rechteck (Elektrobereich)
                        if (!((x>=98) & (x<125) & (y>=222) & (y<240))){// ausserhalb des Baumstumpfes
                            int entdeckt=rand() % 6000+1;
                            if(entdeckt<=100){//bei der Einrueckung versagt, Vorsicht!
                            if(entdeckt<=20){
                            	grenzenMonster = make_pair(true,charwizard);
                            }
                            if(entdeckt>20 & entdeckt<=30){
                            	if((spieler.level()>=20)&(entdeckt>25)){
                            		grenzenMonster = make_pair(true,charmelon);
                            	}
                            	else{
                            		grenzenMonster = make_pair(true,charglide);
                            	}
                            }
                            if(entdeckt>30 & entdeckt<=60){
                            	if((spieler.level()>=12)&(entdeckt>50)){
                            		grenzenMonster = make_pair(true,zappzor);
                            	}
                            	else{
                            		grenzenMonster = make_pair(true,bwazapp);
                            	}
                            }
                            if(entdeckt>60 & entdeckt<=65){
                            	grenzenMonster = make_pair(true,scaryskull);
                            }
                            if((entdeckt>65) & (entdeckt<=100)){
                            	if((spieler.level()>=15)&(entdeckt>85)){
                            		grenzenMonster = make_pair(true,marbgiant);
                            	}
                            	else{
                            		grenzenMonster = make_pair(true,marblous);
                            	}
                            }
                            return grenzenMonster;
                            }
                            else{
                                grenzenMonster = make_pair(true,none);
                                return grenzenMonster;
                            }

                        }
                        
                    }
                    else {
                        if ((x>=150) & (y>=255)){// im untersten Rechteck (Grasbereich)
                            int entdeckt=rand() % 6000+1;
                            if (entdeckt <= 100){
                            	if(entdeckt<=30){
                            	    grenzenMonster = make_pair(true,nomflower);
                            	}
                            	if((entdeckt>30) & (entdeckt<=60)){
                            	    grenzenMonster = make_pair(true,rootshoes);
                            	}
                            	if((entdeckt>60) & (entdeckt<=70)){
                            	    grenzenMonster = make_pair(true,weirdboy);
                            	}
                            	if((entdeckt>70) & (entdeckt<=100)){
                            	    if((spieler.level()>=12)&(entdeckt>85)){
                            	        grenzenMonster = make_pair(true,madbird);
                            	    }
                            	    else{
                            	        grenzenMonster = make_pair(true,angrybird);
                            	    }
                            	}
                                return grenzenMonster;
                            }
                            else{
                                grenzenMonster = make_pair(true,none);
                                return grenzenMonster;
                            }
                        }
                    }
                }
            
            }
            
        }
    }
    grenzenMonster = make_pair(false, none);
    return grenzenMonster;
}

class Character {//Charakter als Objekt, das sich auf der Karte bewegt
public:
    SDL_Surface *bild;
    int xpos = 200;//Startposition
    int ypos = 10;
    int tempo = 4;
    SDL_Rect dest;
    SDL_Rect src;
    
    Character(SDL_Surface *_bild) {
        bild = _bild;
    }
    
    void zeichnen(SDL_Surface *surf){
    	src.x=200;
    	src.y=10;
    	src.w=13;
    	src.h=16;
    	dest.x=xpos;
    	dest.y=ypos;
        SDL_BlitSurface(bild, NULL, surf, &dest);
    }
    
    Monster bewegen(int richtung, Spieler spieler){//gibt gefundenes Monster aus, benoetigt spieler, das Spielerlevel ueber gefundene Monster entscheidet
        switch (richtung){
            case 1:
                grenzenMonster = inGrenzen(xpos, ypos - tempo, spieler);//inGrenzen gibt bool und Monster aus
                if (grenzenMonster.first){//falls bool true wird Bewegung dargestellt, false bei Hindernis/Rand oder gefundenem Monster
                    ypos -= tempo;
                    bild = gcharacterBack;
                }
                break;
            case 2:
                grenzenMonster = inGrenzen(xpos + tempo, ypos, spieler);
                if (grenzenMonster.first){
                    xpos += tempo;
                    bild = gcharacterRight;
                }
                break;

            case 3:
                grenzenMonster = inGrenzen(xpos, ypos + tempo, spieler);
                if (grenzenMonster.first){
                    ypos += tempo;
                    bild = gcharacterFront;
                }
                break;
            case 4:
                grenzenMonster = inGrenzen(xpos - tempo, ypos, spieler);
                if (grenzenMonster.first){
                    xpos -= tempo;
                    bild = gcharacterLeft;
                }
                break;
        }
        return(grenzenMonster.second);
    }
};

//wird spaeter als Graphikbaustein verwendet
SDL_Surface createbar(double length, int r, int g, int b){//erstellt einen Balken der Laenge length mit den Farbwerten rgb (dieser Kommentar war vermutlich unnoetig...)
	SDL_Surface *surface = SDL_CreateRGBSurface(0, length, 5, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
	return *surface;
}

//wird spaeter als Graphikbaustein verwendet
void typevis(int type, int x0, int y0){
	SDL_Rect dest;
	dest.x=x0;
	dest.y=y0;
	SDL_Surface* temp;
	switch(type){
	case 1: temp=swater;break;
	case 2: temp=sfire;break;
	case 3: temp=selectro;break;
	case 4: temp=sstone;break;
	case 5: temp=swind;break;
	case 6: temp=sgrass;break;
	case 7: temp=spsycho;break;
	}
	SDL_BlitSurface(temp,NULL,gScreenSurface,&dest);
}

//wird spaeter als Graphikbaustein verwendet
void mondatavis(individuum ind, int x0, int y0, bool a){//zeigt in Form von Balken die Daten eines Monster an; zeigt XP nur, falls zu spieler gehoerig (a==true)
	typevis(ind.type, x0, y0);
	SDL_Rect dest;
	dest.x=x0;
	dest.y=y0+25;
	bar=createbar(100,255,0,0);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);
	bar=createbar(ind.health,0,255,0);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);//zeigt HP in gruen auf rot
	dest.y+=7;
	bar=createbar(100,0,0,0);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);
	bar=createbar(ind.mana,0,0,255);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);//zeigt Mana in blau auf schwarz
	if(a){
	dest.y+=7;
	bar=createbar(100,100,100,100);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);
	bar=createbar(ind.xp,255,255,0);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);//zeigt XP in gelb auf grau
	}
}

//wird spaeter als Graphikbaustein verwendet
void atkvis(Attack att, int x0, int y0){//zeigt in Form von Balken die Daten einer Attacke an
	SDL_Rect dest;
	typevis(att.type, x0, y0);
	dest.x=x0+25;
	dest.y=y0;
	bar=createbar(100,255,255,255);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);
	bar=createbar(att.strength,255,0,0);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);//zeigt Staerke in rot auf weiss
	dest.y+=7;
	bar=createbar(100,255,255,255);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);
	bar=createbar(att.precision,255,255,0);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);//zeigt Praezision in gelb auf weiss
	dest.y+=7;
	bar=createbar(100,255,255,255);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);
	bar=createbar(att.manacost,0,0,255);
	SDL_BlitSurface(&bar,NULL,gScreenSurface,&dest);//zeigt Manakosten in blau auf weiss
}

//wird spaeter als Graphikbaustein verwendet
void monlevelvis(individuum ind, int x0, int y0){//zeigt Level graphisch an, jeweils 5 Level als ein Stern, den Rest als Striche
	int temp=ind.level;
	SDL_Rect dest;
	dest.x=x0;
	dest.y=y0;
	while(temp>=5){
		SDL_BlitSurface(star,NULL,gScreenSurface,&dest);
		dest.x+=12;
		temp-=5;
	}
	while(temp>=1){
		SDL_BlitSurface(stripe,NULL,gScreenSurface,&dest);
		dest.x+=4;
		temp--;
	}
}

void combatscreen(individuum ind1, individuum ind2, Spieler spieler, Spieler enemy){

	SDL_BlitSurface(cbackground, NULL, gScreenSurface, NULL);//oberer Hintergrund
	SDL_Rect dest;
	dest.x=0;
	dest.y=200;
	SDL_BlitSurface(blackbg, NULL, gScreenSurface, &dest);//unterer Hintergrund
	dest.x=200;
	dest.y=10;
	SDL_BlitSurface(ind2.monster.sprite, NULL, gScreenSurface, &dest);//gegnerisches Monster
	dest.x=40;
	dest.y=110;
	SDL_BlitSurface(ind1.monster.spritem, NULL, gScreenSurface, &dest);//eigenes Monster
	int x=60;
	int y=40;
	mondatavis(ind2, x, y, false);
	x=160;
	y=140;
	mondatavis(ind1, x, y, true);
	x=20;
	if(ind1.mana>=ind1.attack1.manacost){
		y=210;
		atkvis(ind1.attack1,x,y);
		dest.x=150;
		dest.y=210;
		SDL_BlitSurface(numberone,NULL,gScreenSurface,&dest);
	}
	if(ind1.mana>=ind1.attack2.manacost){
		y=250;
		atkvis(ind1.attack2,x,y);
		dest.x=150;
		dest.y=250;
		SDL_BlitSurface(numbertwo,NULL,gScreenSurface,&dest);
	}
	if((ind1.mana<ind1.attack1.manacost)&&(ind1.mana<ind1.attack2.manacost)){
		y=290;
		atkvis(ind1.attack0,x,y);
		dest.x=150;
		dest.y=290;
		SDL_BlitSurface(numberzero,NULL,gScreenSurface,&dest);
	}
	if(spieler.healthpot>0){
		dest.x=200;
		dest.y=230;
		SDL_BlitSurface(hpotion, NULL, gScreenSurface, &dest);
		dest.x=220;
		SDL_BlitSurface(himage, NULL, gScreenSurface, &dest);
	}
	if(spieler.manapot>0){
		dest.x=200;
		dest.y=270;
		SDL_BlitSurface(mpotion, NULL, gScreenSurface, &dest);
		dest.x=220;
		SDL_BlitSurface(mimage, NULL, gScreenSurface, &dest);
	}
	if(!enemy.trainer){
		dest.x=260;
		dest.y=230;
		SDL_BlitSurface(flightarrow, NULL, gScreenSurface, &dest);
		dest.x=280;
		SDL_BlitSurface(fimage, NULL, gScreenSurface, &dest);
		dest.x=260;
		dest.y=270;
		SDL_BlitSurface(cage, NULL, gScreenSurface, &dest);
		dest.x=280;
		SDL_BlitSurface(cimage, NULL, gScreenSurface, &dest);
	}
	SDL_UpdateWindowSurface(gWindow);
	return;
}

int chooseMon(Spieler spieler, bool alive){//stellt Monsterauswahl fuer spieler dar, gibt Wahl als integer aus; bool entscheidet, ob besiegte Monster gewaehlt werden duerfen
	int wahlMon=0;
	SDL_Rect dest;
	SDL_BlitSurface(chbg, NULL, gScreenSurface, NULL);
	dest.x=20;
	dest.y=120;
	if(((spieler.monster1.health>0) & (alive==true)) || (alive==false)){//zeige Monster, wenn sie nicht besiegt sind oder wenn es egal ist
	SDL_BlitSurface(spieler.monster1.monster.sprite, NULL, gScreenSurface, &dest);
	int x=10;
	int y=220;
	mondatavis(spieler.monster1, x, y, true);
	y=265;
	monlevelvis(spieler.monster1, x, y);
	}
	dest.x=120;
	dest.y=120;
	if(((spieler.monster2.health>0) & (alive==true)) || (alive==false)){
	SDL_BlitSurface(spieler.monster2.monster.sprite, NULL, gScreenSurface, &dest);
	int x=110;
	int y=220;
	mondatavis(spieler.monster2, x, y, true);
	y=265;
	monlevelvis(spieler.monster2, x, y);
	}
	dest.x=220;
	dest.y=120;
	if(((spieler.monster3.health>0) & (alive==true)) || (alive==false)){
	SDL_BlitSurface(spieler.monster3.monster.sprite, NULL, gScreenSurface, &dest);
	int x=210;
	int y=220;
	mondatavis(spieler.monster3, x, y, true);
	y=265;
	monlevelvis(spieler.monster3, x, y);
	}
	dest.y=100;
	dest.x=50;
	SDL_BlitSurface(numberone, NULL, gScreenSurface, &dest);
	dest.x=150;
	SDL_BlitSurface(numbertwo, NULL, gScreenSurface, &dest);
	dest.x=250;
	SDL_BlitSurface(numberthree, NULL, gScreenSurface, &dest);
	SDL_UpdateWindowSurface(gWindow);
	SDL_Delay(1000);
	SDL_Event event;
	while(wahlMon==0){
	if ( SDL_PollEvent( &event ) != 0 ) {
	switch (event.key.keysym.sym) {
	                        case SDLK_1:
	                        	wahlMon=1;
	                            break;
	                        case SDLK_2:
	                        	wahlMon=2;
	                        	break;
	                        case SDLK_3:
	                        	wahlMon=3;
	                        	break;
	                    }
	                }
	}
	return wahlMon;
}
