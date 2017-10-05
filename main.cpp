//Der Programmcode ist unter den Bedingungen der MIT-Lizenz nutzbar

#include "map.hpp"


string name;  // Spielernamen
char input; // Eingabe im spaeteren Input
int auswahl;
bool schleife = true; //Fuer Schleife



int main(int a, char **b){

	srand(time(NULL));
	individuum nullmon(none,1);//erstellt Plazhaltermonster
	nullmon.health=0;
	Spieler spieler("Name", nullmon, nullmon, nullmon, false, 5, 5);
	spieler.monster1=individuum(diplomaticturtle, 5);//bietet Wahl zwischen 3 Startmonstern
	spieler.monster2=individuum(charwizard, 5);
	spieler.monster3=individuum(nomflower, 5);
	initialize();
	int choice = chooseMon(spieler, false);
	if(choice!=1){
		spieler.monster1=individuum(angrybird,1);//fuellt Team mit schwachen Nebenmonstern auf
	}
	if(choice!=2){
		spieler.monster2=individuum(angrybird,1);
	}
	if(choice!=3){
		spieler.monster3=individuum(angrybird,1);
	}
	//Gegner hat Spielereigenschaften, wilde Monster besetzen eine Stelle im Team; false-->kein Trainer (Monster koennen gefangen werden)
	Spieler enemy("Gary", nullmon, nullmon, nullmon, false, 0, 0);
	map(spieler, enemy);//ruft map zur Bewegung auf, Begegnungen werden dort initialisiert


	return 0;
}
