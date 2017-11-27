#ifndef BASEMENU_H
#define BASEMENU_H

#include <vector>
#include <LiquidCrystal.h>
#include "Menu.h"

using namespace std;

class BaseMenu
{
	const int LARGEUR = 16;
	const int HAUTEUR = 2;

	// Vecteur d'addresses de la classe de base MENU
	vector<Menu*> menu;
	int menuEnCours = 0;

	// Instance de l'affichage (Syntaxe bizz � cause d'une erreur de compilation)
	// (Le compilateur croyait que c'�tait une m�thode)
	LiquidCrystal lcd = LiquidCrystal(8, 9, 4, 5, 6, 7);

public:
	BaseMenu();
	~BaseMenu();

	int addMenu(char[16], char[16], Action*, Action*, Action*, Action*);
	int addMenu(char[16], char[16], Action*, Action*, Action*, Action*, int&);
	int addMenu(char[16], char[16], Action*, Action*, Action*, Action*, float&);
	int addMenu(char[16], Action*, Action*, Action*, Action*, float&);
	int addMenu(char[16], char[16], Action*, Action*, Action*, Action*, float&, float&, float&);
	int addMenu(char[16], Action*, Action*, Action*, Action*, int&);

	bool GoToMenu(unsigned int);
	bool PeseBouton(int);
	int MenuActuel() { return menuEnCours; }
	char * AfficheMenu();
	void Update();
};

#endif