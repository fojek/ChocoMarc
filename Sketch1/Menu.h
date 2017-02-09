#ifndef MENU_H
#define MENU_H

enum TYPE { GoTo, INCREMENTE, DECREMENTE, CONFIRME };
enum TYPEVAL { NONE, INT, FLOAT };

struct ACTION
{
	TYPE type;
	unsigned int dest;
};

ACTION Action(TYPE, unsigned int);

// Constantes
const char l2TemplateInt[16] = "  %i  ";
const char l2TemplateFloat[16] = "  %f  ";

/******************************************
* Classe de base
******************************************/
class MENU
{
protected:
	// Texte
	char l1[16];
	char l2[16];

	// Actions
	ACTION action[4];

public:
	// M�thodes
	MENU();
	MENU(char[16], char[16], ACTION, ACTION, ACTION, ACTION);
	char * retourneL1(void) { return l1; }
	virtual char * retourneL2(void) { return l2; }
	TYPE typeAction(int a) { return action[a].type; }
	int destAction(int a) { return action[a].dest; }

	// Fonctions virtuelles pour les classes d�riv�es
	virtual void incremente() {};
	virtual void decremente() {};
	virtual void confirme() {};
	virtual void ferme() {};
	virtual bool aChange() { return false; };
};

/******************************************
* Classe d�riv�e MENU_INT
* Une ligne de texte et un int �ditable
******************************************/
class MENU_INT : public MENU
{
	// Valeurs
	int &val;		// R�f�rence � la variable contenue dans le menu
	int tempVal;

public:
	// M�thodes
	MENU_INT(char[16], char[16], ACTION, ACTION, ACTION, ACTION, int&);
	void incremente() { ++tempVal; updateL2(); }
	void decremente() { --tempVal; updateL2(); }
	void confirme(void) { val = tempVal; updateL2(); }
	void ferme(void) { tempVal = val; updateL2(); }
	void updateL2(void);
};

/******************************************
* Classe d�riv�e MENU_FLOAT
* Une ligne de texte et un float �ditable
******************************************/
class MENU_FLOAT : public MENU
{
	// Constantes
	const float FLOAT_INC = 0.5;

	// Valeurs
	float &val;		// R�f�rence � la variable contenue dans le menu
	float tempVal;

public:
	// M�thodes
	MENU_FLOAT(char[16], char[16], ACTION, ACTION, ACTION, ACTION, float&);
	void incremente() { tempVal += FLOAT_INC; updateL2(); }
	void decremente() { tempVal -= FLOAT_INC; updateL2(); }
	void confirme(void) { val = tempVal; updateL2(); }
	void ferme(void) { tempVal = val; updateL2(); }
	void updateL2(void);
};

/******************************************
* Classe d�riv�e MENU_3FLOAT
* Une ligne de texte et 3 int non �ditables
******************************************/
class MENU_3FLOAT : public MENU
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
	MENU_3FLOAT(char[16], char[16], ACTION, ACTION, ACTION, ACTION, float&, float&, float&);

	// Fonctions inutilis�es
	void incremente() {}
	void decremente() {}
	void confirme(void) {}
	void ferme(void) {}
	char * retourneL2(void) { updateL2();  return l2; }
	void updateL2(void);
	bool aChange();
};

#endif