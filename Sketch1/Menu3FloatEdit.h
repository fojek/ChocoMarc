// Menu3FloatEdit.h
/******************************************
* Classe d�riv�e MENU3FloatEdit
* Une ligne de texte et 3 float editables
******************************************/

#ifndef _MENU3FLOATEDIT_h
#define _MENU3FLOATEDIT_h
#include "Menu.h"
#include "Recette.h"
#include <string.h>

class Menu3FloatEdit : public Menu
{
	// Constantes
	const int REFRESH_RATE = 500;		// Affichage mis � jour aux 1/2 secondes

	Recette * recette;
	int &numRecette; // R�f�rence au num�ro de recette (choisi par un MenuIntEdit)
	int numRecette_old = 0; // Pour v�rifier si le num�ro de recette a a chang�
	int index = 0; // Pour cycler entre les setpoints

	// Derni�res valeurs
	float val1_old, val2_old, val3_old;

public:
	// M�thodes
	Menu3FloatEdit(char[16], Action*, Action*, Action*, Action*, int numRecette);

	// Fonctions inutilis�es
	void incremente();
	void decremente();
	void confirme(void);
	void ferme(void);
	char * retourneL2(void) { updateL2();  return l2; }
	void updateL2(void);
};

#endif

