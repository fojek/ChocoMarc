#include "MenuFloat.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>
#include "util.h"

/******************************************
* Classe dérivée MENU_FLOAT
* Une ligne de texte et un float
******************************************/

MenuFloat::MenuFloat(char ligne1[16], Action *a1, Action *a2, Action* a3, Action *a4, float & v) : val(v)
{
	strcpy(l1, ligne1);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;

	updateL2();
}

void MenuFloat::updateL2(void)
{
	formatVal(l2, val);
}

bool MenuFloat::aChange()
{

	if (deviationVal(val, val_old))
	{
		val_old = val;
		updateL2();
		return true;
	}

	return false;
}
