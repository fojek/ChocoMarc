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
	
	int menuEnCours = 0;

	// Instance de l'affichage (Syntaxe bizz à cause d'une erreur de compilation)
	// (Le compilateur croyait que c'était une méthode)
	LiquidCrystal lcd = LiquidCrystal(8, 9, 4, 5, 6, 7);

public:
	vector<Menu*> menu;
	BaseMenu();
	~BaseMenu();

	int addMenu(char[16], char[16], Action*, Action*, Action*, Action*);
	int addMenu(char[16], char[16], Action*, Action*, Action*, Action*, int&, bool&);
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