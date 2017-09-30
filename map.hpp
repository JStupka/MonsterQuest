#include "Funktionen.hpp"

Monster genMon;
//Funktion map zeichnet Karte und Charakter, erlaubt Bewegung; generiert Begegnungen falls Bewegung auf Monster trifft
//initialisiert dann Kampf und zeigt vorher elementspezifische Zwischenschirme
int map(Spieler spieler, Spieler enemy)
{

	Character character1(gcharacterFront);
	SDL_BlitSurface( gbackgroundMap, NULL, gScreenSurface, NULL );

	//Update the surface
	SDL_UpdateWindowSurface( gWindow );

	SDL_Event e;
	SDL_Surface* surf = SDL_GetWindowSurface(gWindow);

	character1.zeichnen(surf);

            for (int x=0; x<3000000; x++) {//Spiel laeuft momentan für 3000000 Schritte



                if ( SDL_PollEvent( &e ) != 0 ) {//Bewegung mit Pfeiltasten
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            genMon = character1.bewegen(1, spieler);//Bewegung gibt Art des Monsters zurueck, falls eines gefunden wurde
                            break;
                        case SDLK_DOWN:
                            genMon = character1.bewegen(3, spieler);
                            break;
                        case SDLK_LEFT:
                        	genMon = character1.bewegen(4, spieler);
                            break;
                        case SDLK_RIGHT:
                        	genMon = character1.bewegen(2, spieler);
                            break;
                        case SDLK_ESCAPE:
                        	close();
                        	return 0;
                    }
                }

                SDL_BlitSurface( gbackgroundMap, NULL, gScreenSurface, NULL );
                character1.zeichnen(surf);
                SDL_UpdateWindowSurface(gWindow);


                if (genMon.dexNum != 0){
                	int monlevel = spieler.level() + (rand() % 6 - 4);//generiert auf Basis der Monsterart ein Monster mit zufaelligem Level (Spielerlevel -4 bis +2)
                	if(monlevel<1){
                		monlevel=1;
                	}
                	if(monlevel>30){//begrenzt zwischen 1 und 30
                		monlevel=30;
                	}
                	enemy.monster1=individuum(genMon,monlevel);

                    // Element anzeigen als Zwischenschirm um Wahl strategisch zu machen
                    switch(genMon.type){
                        case 1: SDL_BlitSurface( gwater, NULL, gScreenSurface, NULL ); break;
                        case 2: SDL_BlitSurface( gfire, NULL, gScreenSurface, NULL ); break;
                        case 3: SDL_BlitSurface( gelectro, NULL, gScreenSurface, NULL ); break;
                        case 4: SDL_BlitSurface( gstone, NULL, gScreenSurface, NULL ); break;
                        case 5: SDL_BlitSurface( gwind, NULL, gScreenSurface, NULL ); break;
                        case 6: SDL_BlitSurface( ggrass, NULL, gScreenSurface, NULL ); break;
                        case 7: SDL_BlitSurface( gpsycho, NULL, gScreenSurface, NULL ); break;
                    }

                    SDL_UpdateWindowSurface( gWindow );
                    SDL_Delay(1500);

                    tuple<int,individuum,individuum,individuum> result=combatroutine(spieler, enemy);//initialisiert Kampf
                    spieler.monster1=get<1>(result);//speichert Veraenderungen der Monster durch Kampf (level,xp,hp)
                    spieler.monster2=get<2>(result);
                    spieler.monster3=get<3>(result);
                    if(get<0>(result)==-1){//falls Kampf verloren, setzt Charakter auf Anfangsposition und heilt Monster; noch keine Strafe
                    	spieler.monster1.health=100;
                    	spieler.monster2.health=100;
                    	spieler.monster3.health=100;
                    	character1.xpos=200;
                    	character1.ypos=10;
                    }
                    genMon=none;

                    SDL_BlitSurface( gbackgroundMap, NULL, gScreenSurface, NULL );

                    //Update the surface
                    SDL_UpdateWindowSurface( gWindow );

                    SDL_Surface* surf = SDL_GetWindowSurface(gWindow);

                    character1.zeichnen(surf);//Rueckkehr zur Karte
                }
            }
    close();
    return 0;
}
