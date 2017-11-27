#include "Menu3Float.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>

/******************************************
* Classe dérivée MENU_3FLOAT
* Une ligne de texte et 3 float non-éditables
******************************************/

MENU_3FLOAT::MENU_3FLOAT(char ligne1[16], char ligne2[16], ACTION *a1, ACTION *a2, ACTION *a3, ACTION *a4, float & v1, float & v2, float & v3) : val1(v1), val2(v2), val3(v3)
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

bool MENU_3FLOAT::deviationVal(float act, float old)
{
	// Deviation de 1% permise avant un refresh
	const float DEVIATION = 0.0001;

	if (act > old * (1 + (DEVIATION)) || act < old * (1 - (DEVIATION)))
		return true;

	return false;
}