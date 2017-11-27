#include "MenuIntEdit.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>

/******************************************
* Classe d�riv�e MENU_INT
* Une ligne de texte et un int �ditable
******************************************/

MENU_INT_EDIT::MENU_INT_EDIT(char ligne1[16], char ligne2[16], ACTION * a1, ACTION * a2, ACTION * a3, ACTION * a4, int & v) : val(v)
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

void MENU_INT_EDIT::updateL2(void)
{
	char temp[16];
	sprintf(temp, "%d", tempVal);
	strcpy(l2, temp);
}
