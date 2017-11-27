// Menu3Float.h

#ifndef _MENU3FLOAT_h
#define _MENU3FLOAT_h
#include "Action.h"
#include "Menu.h"

/******************************************
* Classe d�riv�e MENU_3FLOAT
* Une ligne de texte et 3 float non �ditables
******************************************/

class MENU_3FLOAT : public Menu
{
	// Constantes
	const int REFRESH_RATE = 500;		// Affichage mis � jour aux 1/2 secondes

										// Valeurs
	float &val1;		// R�f�rence � la variable contenue dans le menu
	float &val2;
	float &val3;

	// Derni�res valeurs
	float val1_old, val2_old, val3_old;

public:
	// M�thodes
	MENU_3FLOAT(char[16], char[16], ACTION*, ACTION*, ACTION*, ACTION*, float&, float&, float&);

	// Fonctions inutilis�es
	void incremente() {}
	void decremente() {}
	void confirme(void) {}
	void ferme(void) {}
	char * retourneL2(void) { updateL2();  return l2; }
	void updateL2(void);
	bool aChange();
	bool deviationVal(float act, float old);
};

#endif

