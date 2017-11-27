// MenuFloat.h

#ifndef _MENUFLOATEDIT_h
#define _MENUFLOATEDIT_h
#include "Menu.h"

/******************************************
* Classe dérivée MENU_FLOAT
* Une ligne de texte et un float éditable
******************************************/
class MENU_FLOAT_EDIT : public Menu
{
	// Constantes
	const float FLOAT_INC = 0.5;

	// Valeurs
	float &val;		// Référence à la variable contenue dans le menu
	float tempVal;

public:
	// Méthodes
	MENU_FLOAT_EDIT(char[16], char[16], ACTION*, ACTION*, ACTION*, ACTION*, float&);
	void incremente() { tempVal += FLOAT_INC; updateL2(); }
	void decremente() { tempVal -= FLOAT_INC; updateL2(); }
	void confirme(void) { val = tempVal; updateL2(); }
	void ferme(void) { tempVal = val; updateL2(); }
	void updateL2(void);
};

#endif