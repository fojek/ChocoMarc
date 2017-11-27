#include "Menu3Float.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>
#include "util.h"

/******************************************
* Classe dérivée MENU_3FLOAT
* Une ligne de texte et 3 float non-éditables
******************************************/

Menu3Float::Menu3Float(char ligne1[16], char ligne2[16], Action *a1, Action *a2, Action *a3, Action *a4, float & v1, float & v2, float & v3) : val1(v1), val2(v2), val3(v3)
{
	strcpy(l1, ligne1);
	strcpy(l2, ligne2);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;

	updateL2();
}

void Menu3Float::updateL2()
{
	formatVal(l2, val1, val2, val3);
}

bool Menu3Float::aChange()
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