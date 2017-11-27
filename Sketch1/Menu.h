#ifndef MENU_H
#define MENU_H

#include "Action.h"

enum TYPEVAL { NONE, INT, FLOAT };

// Constantes
const char l2TemplateInt[16] = "  %i  ";
const char l2TemplateFloat[16] = "  %f  ";

/******************************************
* Classe de base
******************************************/
class Menu
{
protected:
	// Texte
	char l1[16];
	char l2[16];

	// Actions
	ACTION * action[4];

public:
	// Méthodes
	Menu();
	Menu(char[16], char[16], ACTION*, ACTION*, ACTION*, ACTION*);
	char * retourneL1(void) { return l1; }
	virtual char * retourneL2(void) { return l2; }
	TYPE typeAction(int a) { return action[a]->type(); }
	int destAction(int a) { return action[a]->dest(); }
	char * ftoa(char * a, double f, int precision);

	// Fonctions virtuelles pour les classes dérivées
	virtual void incremente() {};
	virtual void decremente() {};
	virtual void confirme() {};
	virtual void ferme() {};
	virtual bool aChange() { return false; };
};

#endif