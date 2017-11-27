// Menu3FloatEdit.h
/******************************************
* Classe dérivée MENU3FloatEdit
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
	const int REFRESH_RATE = 500;		// Affichage mis à jour aux 1/2 secondes

	Recette * recette;
	int &numRecette; // Référence au numéro de recette (choisi par un MenuIntEdit)
	int numRecette_old = 0; // Pour vérifier si le numéro de recette a a changé
	int index = 0; // Pour cycler entre les setpoints

	// Dernières valeurs
	float val1_old, val2_old, val3_old;

public:
	// Méthodes
	Menu3FloatEdit(char[16], Action*, Action*, Action*, Action*, int numRecette);

	// Fonctions inutilisées
	void incremente();
	void decremente();
	void confirme(void);
	void ferme(void);
	char * retourneL2(void) { updateL2();  return l2; }
	void updateL2(void);
};

#endif

