#ifndef TEMPEREUSE
#define TEMPEREUSE

#include <PID_v1.h>
#include <EEPROM.h>

// Constantes
// Un cycle de temp�rage contient 3 temp�ratures
const int NUM_TEMP = 3;
// Intervalle de calcul
const int INTERVALLE = 200;

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