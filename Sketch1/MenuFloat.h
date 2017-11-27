// MenuFloat.h
#ifndef _MENUFLOAT_h
#define _MENUFLOAT_h

#include "Menu.h"

/******************************************
* Classe dérivée MENU_FLOAT
* Une ligne de texte et un float éditable
******************************************/

class MENU_FLOAT : public Menu
{
	// Constantes
	const float FLOAT_INC = 0.5;

	// Valeurs
	float &val;		// Référence à la variable contenue dans le menu
	float val_old;

public:
	// Méthodes
	MENU_FLOAT(char[16], ACTION*, ACTION*, ACTION*, ACTION*, float&);
	void incremente() {}
	void decremente() {}
	void confirme(void) {}
	void ferme(void) {}
	void updateL2(void);
	bool aChange();
	bool deviationVal(float act, float old);
};
#endif

