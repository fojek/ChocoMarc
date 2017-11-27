#ifndef TEMPEREUSE
#define TEMPEREUSE

#include <PID_v1.h>
#include "Recette.h"

// Constantes
// Intervalle de calcul
const int INTERVALLE = 200;

class Tempereuse
{
	// Constantes
	const int windowSize = 5000; // Fen�tre de r�action, 5s
	unsigned long windowStartTime = 0;

	// Pins utilis�es
	int heaterPin;
	int tempPin;

	// Pointeur pour le contr�leur PID
	PID * pid;
	Recette * recette;

	// Pointeur pour la capteur de temp�rature OneWire
	OneWire  * temp;
	byte addr[8];

	// Variables pour le proc�d�
	bool enMarche;
	int etapeEnCours = 0;
	unsigned long dernierUpdate;

	// Donn�es pour le PID
	double temperature;
	double setpoint;
	double sortie;

public:
	Tempereuse(int, int);
	void init();
	void start(int);
	void stop();
	bool estEnMarche() { return enMarche; };
	bool update(float&);
	bool initTemp();
	double chauffage() { return sortie; };
	float setPoint() { return (float)recette->setpoint(etapeEnCours); Serial.println(etapeEnCours); };
	int etape() { return etapeEnCours; };
	~Tempereuse();
	
	double getTemp();
};

#endif