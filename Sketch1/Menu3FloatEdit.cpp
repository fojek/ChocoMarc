#include "Menu3FloatEdit.h"
#include "util.h"

/******************************************
* Classe d�riv�e MENU3FloatEdit
* Une ligne de texte et 3 float editables
******************************************/

Menu3FloatEdit::Menu3FloatEdit(char ligne1[16], Action * a1, Action * a2, Action * a3, Action * a4, int pnRecette) : numRecette(pnRecette)
{
	strcpy(l1, ligne1);

	action[0] = a1;
	action[1] = a2;
	action[2] = a3;
	action[3] = a4;

	recette = new Recette();

	recette->loadRecette(numRecette);

	updateL2();
}

void Menu3FloatEdit::incremente()
{
	recette->set(index, recette->get(index) + 0.5);
	updateL2();
}

void Menu3FloatEdit::decremente()
{
	recette->set(index, recette->get(index) - 0.5);
	updateL2();
}

void Menu3FloatEdit::confirme(void)
{
	++index;
	if (index >= NUM_TEMP) {
		index = 0;
		ferme();
	}
}

void Menu3FloatEdit::ferme(void)
{
	recette->saveRecette(numRecette);
}

void Menu3FloatEdit::updateL2(void)
{
	if (numRecette != numRecette_old) {
		recette->loadRecette(numRecette);
		numRecette != numRecette_old;
		index = 0;
	}

	formatVal(l2, recette->get(0), recette->get(1), recette->get(2));
}
