#ifndef MENU_H
#define MENU_H

#include "Action.h"

enum TYPEVAL { NONE, INT, FLOAT };

/******************************************
* Classe de base pour les Menus
******************************************/
class Menu
{
protected:
	// Texte
	char l1[16];
	char l2[16];

	// Actions
	Action * action[4];

public:
	// Méthodes
	Menu();
	Menu(char[16], char[16], Action*, Action*, Action*, Action*);
	char * retourneL1(void) { return l1; }
	virtual char * retourneL2(void) { return l2; }
	Type typeAction(int a) { return action[a]->type(); }
	int destAction(int a) { return action[a]->dest(); }

	// Fonctions virtuelles pour les classes dérivées
	// Commandes possibles sur les menus
	virtual void incremente() {};
	virtual void decremente() {};
	virtual void confirme() {};
	virtual void ferme() {};
	// Valide qu'une variable doit être mise à jour
	virtual bool aChange() { return false; };
};

#endif