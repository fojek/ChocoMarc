#pragma once
#include "Action.h"
#include "Menu.h"

/******************************************
* Classe d�riv�e MENU_INT
* Une ligne de texte et un int �ditable
******************************************/
class MenuIntEdit : public Menu
{
	// Valeurs
	int &val;		// R�f�rence � la variable contenue dans le menu
	int tempVal;

public:
	// M�thodes
	MenuIntEdit(char[16], char[16], Action*, Action*, Action*, Action*, int&);
	void incremente() { ++tempVal; updateL2(); }
	void decremente() { --tempVal; updateL2(); }
	void confirme(void) { val = tempVal; updateL2(); }
	void ferme(void) { tempVal = val; updateL2(); }
	void updateL2(void);
};
