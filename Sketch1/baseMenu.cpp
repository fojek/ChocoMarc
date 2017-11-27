#include "baseMenu.h"
#include "MenuIntEdit.h"
#include "MenuFloatEdit.h"
#include "Menu3FloatEdit.h"
#include "Menu3Float.h"
#include "MenuFloat.h"

using namespace std;

BaseMenu::BaseMenu()
{
	// Initialisation du LCD (16 char, 2 colonnes)
	lcd.begin(16, 2);
}

BaseMenu::~BaseMenu()
{
	for (auto i : menu)
	{
		delete i;
	}
}

int BaseMenu::addMenu(char l1[16], char l2[16], Action * a1, Action * a2, Action * a3, Action * a4)
{
	Menu * m = new Menu(l1, l2, a1, a2, a3, a4);
	menu.push_back(m);
	return menu.size() - 1;
}

int BaseMenu::addMenu(char l1[16], char l2[16], Action * a1, Action * a2, Action * a3, Action * a4, int &val)
{
	MenuIntEdit * m = new MenuIntEdit(l1, l2, a1, a2, a3, a4, val);
	menu.push_back(m);
	return menu.size() - 1;
}

int BaseMenu::addMenu(char l1[16], char l2[16], Action * a1, Action * a2, Action * a3, Action * a4, float &val)
{
	MenuFloatEdit * m = new MenuFloatEdit(l1, l2, a1, a2, a3, a4, val);
	menu.push_back(m);
	return menu.size() - 1;
}

int BaseMenu::addMenu(char l1[16], Action * a1, Action * a2, Action * a3, Action * a4, float &val)
{
	MenuFloat * m = new MenuFloat(l1, a1, a2, a3, a4, val);
	menu.push_back(m);
	return menu.size() - 1;
}

int BaseMenu::addMenu(char l1[16], char l2[16], Action * a1, Action * a2, Action * a3, Action * a4, float &v1, float &v2, float &v3)
{
	Menu3Float * m = new Menu3Float(l1, l2, a1, a2, a3, a4, v1, v2, v3);
	menu.push_back(m);
	return menu.size() - 1;
}

int BaseMenu::addMenu(char l1[16], Action * a1, Action * a2, Action * a3, Action * a4, int &r)
{
	Menu3FloatEdit * m = new Menu3FloatEdit(l1, a1, a2, a3, a4, r);
	menu.push_back(m);
	return menu.size() - 1;
}

bool BaseMenu::GoToMenu(unsigned int dest)
{
	if (dest < menu.size())
	{
		menu.at(menuEnCours)->ferme();
		menuEnCours = dest;

		return true;
	}
	return false;
}

bool BaseMenu::PeseBouton(int bouton)
{
	switch (menu.at(menuEnCours)->typeAction(bouton))
	{
	case GoTo:
		return GoToMenu(menu.at(menuEnCours)->destAction(bouton));
	case INCREMENTE:
		menu.at(menuEnCours)->incremente();
		return true;
	case DECREMENTE:
		menu.at(menuEnCours)->decremente();
		return true;
	case CONFIRME:
		menu.at(menuEnCours)->confirme();
		return true;
	default:
		break;
	}
	return false;
}

char * BaseMenu::AfficheMenu()
{

	lcd.clear();
	lcd.print(menu.at(menuEnCours)->retourneL1());
	lcd.setCursor(0, 1);
	lcd.print(menu.at(menuEnCours)->retourneL2());

}

void BaseMenu::Update()
{

	if (menu.at(menuEnCours)->aChange()) {
		AfficheMenu();
	}
}
