#include "MenuFloat.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>

/******************************************
* Classe dérivée MENU_FLOAT
* Une ligne de texte et un float
******************************************/

MENU_FLOAT::MENU_FLOAT(char ligne1[16], ACTION *a1, ACTION *a2, ACTION* a3, ACTION *a4, float & v) : val(v)
{
	strcpy(l1, ligne1);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;

	updateL2();
}

void MENU_FLOAT::updateL2(void)
{
	char temp[16];
	ftoa(temp, val, 1);
	strcpy(l2, temp);
}

bool MENU_FLOAT::aChange()
{

	if (deviationVal(val, val_old))
	{
		val_old = val;
		updateL2();
		return true;
	}

	return false;
}

bool MENU_FLOAT::deviationVal(float act, float old)
{
	// Deviation de 1% permise avant un refresh
	const float DEVIATION = 0.0001;

	if (act > old * (1 + (DEVIATION)) || act < old * (1 - (DEVIATION)))
		return true;

	return false;
}
