// Recette.h

#ifndef _RECETTE_h
#define _RECETTE_h

// Constantes
// Un cycle de temp�rage contient 3 temp�ratures
const int NUM_TEMP = 3;

class Recette
{
	// Tableau des temp�ratures
	int tempCible[NUM_TEMP];
public:
	Recette();
	float setpoint(int);
	void set(float, float, float);
	bool loadRecette(int);
	bool saveRecette(int);
};

#endif

