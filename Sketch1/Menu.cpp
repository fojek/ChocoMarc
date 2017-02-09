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
char * ftoa(char * a, double f, int precision)
{
	char *ret = a;

	int entier = (int)f;
	float reste = f - entier;

	sprintf(ret, "%d", entier);

	if (f >= 10000 || f <= -1000) // 5 caractères : ne peut pas afficher
		return "err.";
	else if (f >= 100 || f <= -10) // 3 ou 4 caractères : affiche sans décimale
	{
		if (strlen(ret) == 3) // Si 3 caracteres, on ajoute un espace à la fin
			strcat(ret, " ");
		return ret;
	}
	else if (f >= 10 || f < 0) // 2 caractères : on affiche une décimale
	{
		reste *= 10; // une décimale

		strcat(ret, ".");
		char decimale[4];
		int decimale_int = (int)reste;

		sprintf(decimale, "%d", decimale_int);


		strcat(ret, decimale);
		return ret;
	}
	else // Valeur entre 0 et 9 : on affiche 2 décimales
	{
		reste *= 100; // deux décimales

		strcat(ret, ".");
		char decimale[4];
		int decimale_int = (int)reste;

		sprintf(decimale, "%d", decimale_int);

		// La première décimale est un zéro
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

MENU::MENU() {}

MENU::MENU(char ligne1[16], char ligne2[16], ACTION a1, ACTION a2, ACTION a3, ACTION a4)
{
	strcpy(l1, ligne1);
	strcpy(l2, ligne2);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;
}

/******************************************
 * Classe dérivée MENU_INT
 * Une ligne de texte et un int éditable
 ******************************************/

MENU_INT::MENU_INT(char ligne1[16], char ligne2[16], ACTION a1, ACTION a2, ACTION a3, ACTION a4, int & v) : val(v)
{
	strcpy(l1, ligne1);
	strcpy(l2, ligne2);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;

	tempVal = val;

	updateL2();
}

void MENU_INT::updateL2(void)
{
	char temp[16];
	sprintf(temp, "%d", tempVal);
	strcpy(l2, temp);
}

/******************************************
* Classe dérivée MENU_FLOAT
* Une ligne de texte et un float éditable
******************************************/

MENU_FLOAT::MENU_FLOAT(char ligne1[16], char ligne2[16], ACTION a1, ACTION a2, ACTION a3, ACTION a4, float & v) : val(v)
{
	strcpy(l1, ligne1);
	strcpy(l2, ligne2);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;

	tempVal = val;

	updateL2();
}

void MENU_FLOAT::updateL2(void)
{
	char temp[16];
	ftoa(temp, tempVal, 4);
	strcpy(l2, temp);
}

/******************************************
* Classe dérivée MENU_3FLOAT
* Une ligne de texte et 3 float non-éditables
******************************************/
MENU_3FLOAT::MENU_3FLOAT(char ligne1[16], char ligne2[16], ACTION a1, ACTION a2, ACTION a3, ACTION a4, float & v1, float & v2, float & v3) : val1(v1), val2(v2), val3(v3)
{
	strcpy(l1, ligne1);
	strcpy(l2, ligne2);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;

	updateL2();
}

void MENU_3FLOAT::updateL2()
{
	char temp1[17];
	char temp2[5];
	char temp3[5];

	// Convertit les float en char
	ftoa(temp1, val1, 1);
	ftoa(temp2, val2, 1);
	ftoa(temp3, val3, 1);

	// Forme la chaîne de caractère : "00.0| 00.0 | 00.0"
	strcat(temp1, "| ");
	strcat(temp1, temp2);
	strcat(temp1, "| ");
	strcat(temp1, temp3);

	// Copie dans la ligne 2
	strcpy(l2, temp1);
}

bool MENU_3FLOAT::aChange()
{
	if (deviationVal(val1, val1_old) || deviationVal(val2, val2_old) || deviationVal(val3, val3_old))
	{
		val1_old = val1;
		val2_old = val2;
		val3_old = val3;
		return true;
	}

	return false;
}

// Fonction pour la création des actions 
ACTION Action(TYPE t, unsigned int d)
{
	ACTION a;
	a.type = t;
	a.dest = d;
	return a;
}

bool deviationVal(float act, float old)
{
	// Deviation de 1% permise avant un refresh
	const float DEVIATION = 0.0001;

	if (act > old * (1 + (DEVIATION)) || act < old * (1 - (DEVIATION)))
		return true;

	return false;
}
