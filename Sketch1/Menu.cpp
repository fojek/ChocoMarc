#include "Menu.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>
using namespace std;

/******************************************
* Classe de base MENU
* Deux lignes de texte
******************************************/

Menu::Menu() {}

Menu::Menu(char ligne1[16], char ligne2[16], Action * a1, Action * a2, Action * a3, Action * a4)
{
	strcpy(l1, ligne1);
	strcpy(l2, ligne2);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;
}