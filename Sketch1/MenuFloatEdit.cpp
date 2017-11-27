#include "MenuFloatEdit.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>
#include "util.h"

/******************************************
* Classe dérivée MENU_FLOAT
* Une ligne de texte et un float éditable
******************************************/

MenuFloatEdit::MenuFloatEdit(char ligne1[16], char ligne2[16], Action *a1, Action *a2, Action* a3, Action *a4, float & v) : val(v)
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

void MenuFloatEdit::updateL2(void)
{
	formatVal(l2, tempVal);
}
