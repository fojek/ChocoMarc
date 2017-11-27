#include "MenuIntEdit.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>

/******************************************
* Classe dérivée MENU_INT
* Une ligne de texte et un int éditable
******************************************/

MenuIntEdit::MenuIntEdit(char ligne1[16], char ligne2[16], Action * a1, Action * a2, Action * a3, Action * a4, int & v) : val(v)
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

void MenuIntEdit::updateL2(void)
{
	char temp[16];
	sprintf(temp, "%d", tempVal);
	strcpy(l2, temp);
}
