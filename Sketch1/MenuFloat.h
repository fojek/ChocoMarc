// MenuFloat.h
#ifndef _MENUFLOAT_h
#define _MENUFLOAT_h

#include "Menu.h"

/******************************************
* Classe d�riv�e MENU_FLOAT
* Une ligne de texte et un float �ditable
******************************************/

class MenuFloat : public Menu
{
	// Constantes
	const float FLOAT_INC = 0.5;

	// Valeurs
	float &val;		// R�f�rence � la variable contenue dans le menu
	float val_old;

public:
	// M�thodes
	MenuFloat(char[16], Action*, Action*, Action*, Action*, float&);
	void incremente() {}
	void decremente() {}
	void confirme(void) {}
	void ferme(void) {}
	void updateL2(void);
	bool aChange();
};
#endif

