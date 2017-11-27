#pragma once
#include "Action.h"
#include "Menu.h"

/******************************************
* Classe dérivée MENU_INT
* Une ligne de texte et un int éditable
******************************************/
class MENU_INT_EDIT : public Menu
{
	// Valeurs
	int &val;		// Référence à la variable contenue dans le menu
	int tempVal;

public:
	// Méthodes
	MENU_INT_EDIT(char[16], char[16], ACTION*, ACTION*, ACTION*, ACTION*, int&);
	void incremente() { ++tempVal; updateL2(); }
	void decremente() { --tempVal; updateL2(); }
	void confirme(void) { val = tempVal; updateL2(); }
	void ferme(void) { tempVal = val; updateL2(); }
	void updateL2(void);
};
