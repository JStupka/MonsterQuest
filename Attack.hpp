#include <iostream>
#include <string>
#include <tuple>
#include <math.h>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;


class Attack
{
public:



	string name;
	int type; //types: grass, water, fire, electro, stone, wind, psycho
	int strength;
	int precision;
	int manacost;
	//Attack();
	Attack(string name, int type, int strength, int precision, int manacost){
		this->name = name;
		this->type = type;
		this->strength = strength;
		this->precision = precision;
		this->manacost = manacost;
	};
	Attack(){}
private:
};

