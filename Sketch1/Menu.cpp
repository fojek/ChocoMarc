#include "Menu.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>
using namespace std;

// Prototypes
ACTION Action(TYPE, unsigned int);
bool deviationVal(float, float);

// Fonction pour convertir les float en char (Arduino playground)
char * Menu::ftoa(char * a, double f, int precision)
{
	char *ret = a;

	int entier = (int)f;
	float reste = f - entier;

	sprintf(ret, "%d", entier);

	if (f >= 10000 || f <= -1000) // 5 caract�res : ne peut pas afficher
		return "err.";
	else if (f >= 100 || f <= -10) // 3 ou 4 caract�res : affiche sans d�cimale
	{
		if (strlen(ret) == 3) // Si 3 caracteres, on ajoute un espace � la fin
			strcat(ret, " ");
		return ret;
	}
	else if (f >= 10 || f < 0) // 2 caract�res : on affiche une d�cimale
	{
		reste *= 10; // une d�cimale

		strcat(ret, ".");
		char decimale[4];
		int decimale_int = (int)reste;

		sprintf(decimale, "%d", decimale_int);


		strcat(ret, decimale);
		return ret;
	}
	else // Valeur entre 0 et 9 : on affiche 2 d�cimales
	{
		reste *= 100; // deux d�cimales

		strcat(ret, ".");
		char decimale[4];
		int decimale_int = (int)reste;

		sprintf(decimale, "%d", decimale_int);

		// La premi�re d�cimale est un z�ro
		if (decimale_int < 10)
			strcat(ret, "0");

		strcat(ret, decimale);
		//strcat(ret, " ");
		return ret;
	}
}

/******************************************
* Classe de base MENU
* Deux lignes de texte
******************************************/

Menu::Menu() {}

Menu::Menu(char ligne1[16], char ligne2[16], ACTION * a1, ACTION * a2, ACTION * a3, ACTION * a4)
{
	strcpy(l1, ligne1);
	strcpy(l2, ligne2);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;
}