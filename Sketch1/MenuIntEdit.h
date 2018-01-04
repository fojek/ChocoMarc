#pragma once
#include "Action.h"
#include "Menu.h"

/******************************************
* Classe dérivée MENU_INT
* Une ligne de texte et un int éditable
******************************************/
class MenuIntEdit : public Menu
{
	// Valeurs
	int &val;		// Référence à la variable contenue dans le menu
	int tempVal;
	bool &trigger;

public:
	// Méthodes
	MenuIntEdit(char[16], char[16], Action*, Action*, Action*, Action*, int&, bool&);
	void incremente() { ++tempVal; updateL2(); }
	void decremente() { --tempVal; updateL2(); }
	void confirme(void) { val = tempVal; trigger = true; updateL2(); }
	void ferme(void) { tempVal = val; updateL2(); }
	void updateL2(void);
};
