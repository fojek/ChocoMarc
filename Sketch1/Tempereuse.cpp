
#include <OneWire.h>
#include "Tempereuse.h"

// Prototypes de fonctions
float readFloat(unsigned int);
void writeFloat(unsigned int, float);
void p_log(char[16], int, int);

Recette::Recette()
{}

float Recette::setpoint(int etape)
{
	p_log("Recette::setpoint()", etape, tempCible[etape]);
	return tempCible[etape];
}

void Recette::set(float s1, float s2, float s3)
{
	p_log("Recette::set", s1, s2);
	tempCible[0] = s1;
	tempCible[1] = s2;
	tempCible[2] = s3;
}

bool Recette::loadRecette(int index)
{
	// Index de boucle
	uint8_t i;

	// Adresse de base de la recette
	uint8_t adresse = index * NUM_TEMP * sizeof(float);

	// Ne pas lire une adresse invalide
	if (adresse + sizeof(float) > EEPROM.length())
		return false;

	// Recherche des températures
	for (i = 0; i < NUM_TEMP; ++i)
	{
		tempCible[i] = readFloat(adresse + i * sizeof(float));
	}

	p_log("Recette::loadRecette()", index, tempCible[0]);
	return true;
}

bool Recette::saveRecette(int index)
{
	Serial.println("Recette sauvegardée");
	// Index de boucle
	uint8_t i;

	// Ne pas lire une adresse invalide
	uint8_t adresse = index * NUM_TEMP * sizeof(float);

	// Ne pas écrire une adresse invalide
	if (adresse + sizeof(float) > EEPROM.length())
		return false;

	// Sauvegarde des températures
	for (i = 0; i < NUM_TEMP; ++i)
	{
		writeFloat(adresse + i * sizeof(float), tempCible[i]);
		if ((int)readFloat(adresse + i * sizeof(float)) != (int)tempCible[i])
			return false;
		p_log("Recette::loadRecette()", adresse + i * sizeof(float), tempCible[i]);
	}

	p_log("Recette::saveRecette()", index, tempCible[0]);

	return true;
}

Tempereuse::Tempereuse(int hPin, int tPin) : heaterPin(hPin), tempPin(tPin), etapeEnCours(0)
{
}

void Tempereuse::init()
{
	p_log("Tempereuse::init()_debut", etapeEnCours, 0);
	// Instance du PID (&input, &output, &setpoint, P, I, D, mode)
	pid = new PID(&temperature, &sortie, &setpoint, 40, 0.5, 1, DIRECT);
	pid->SetOutputLimits(0, windowSize);
	
	// Pin de sortie
	pinMode(heaterPin, OUTPUT);
	
	// Capteur de température
	temp = new OneWire(tempPin);

	// Recette
	recette = new Recette();
	recette->loadRecette(0);  // Recette par défaut
	etapeEnCours = 0;
	dernierUpdate = 0;

	// Adresse fixe du capteur de température. Pour contourner une erreur de compilation de la fct search de onewire.
	// À adapter au capteur! il faut lire l'adresse avec l'exemple de OneWire.
	addr[0] = 0x28;
	addr[1] = 0xFF;
	addr[2] = 0x9C;
	addr[3] = 0xCB;
	addr[4] = 0x60;
	addr[5] = 0x16;
	addr[6] = 0x03;
	addr[7] = 0x72;

	//28 FF 9C CB 60 16 3 72
	p_log("Tempereuse::init()_fin", etapeEnCours, 0);
}

void Tempereuse::start(int r)
{
	etapeEnCours = 0;
	recette->loadRecette(r);
	pid->SetMode(AUTOMATIC);
	enMarche = true;
	p_log("Tempereuse::start()", etapeEnCours, recette->setpoint(0));
}

void Tempereuse::stop()
{
	enMarche = false; 
	etapeEnCours = 0;
	pid->SetMode(MANUAL);
	sortie = 0;
}

bool Tempereuse::update(float &t_aff)
{
	p_log("Tempereuse::update()", dernierUpdate, millis());

	//Si le temps de l'update n'est pas arrivé...
	if ((dernierUpdate + INTERVALLE) > millis())
		return false;

	dernierUpdate = millis();

	// Mécanique de l'update
	temperature = getTemp();
	if (estEnMarche())
	{
		pid->Compute();

		switch (etapeEnCours)
		{
		// Rampe initiale
		case 0:
			if (temperature > recette->setpoint(etapeEnCours))
				++etapeEnCours;
			break;
		// Refroidissement
		case 1:
			if (temperature < recette->setpoint(etapeEnCours))
				++etapeEnCours;
			break;
		// Augmentation de la température, puis maintien
		case 2:
		default:
			break;
		}

		pid->Compute();
		setpoint = recette->setpoint(etapeEnCours);

		unsigned long now = millis();

		if (now - windowStartTime>windowSize)
		{ //time to shift the Relay Window
			windowStartTime += windowSize;
			p_log("WindowSize", windowSize, windowStartTime);
		}

		if(sortie > now - windowStartTime)
		{
			digitalWrite(heaterPin, HIGH);
			p_log("Output", heaterPin, HIGH);
		}
		else
		{
			digitalWrite(heaterPin, LOW);
			p_log("Output", heaterPin, LOW);
		}
	}

	t_aff = temperature;

	p_log("Tempereuse::update()", etapeEnCours, sortie);

	return true;
}

bool Tempereuse::initTemp()
{
	byte data[12];
	byte addr[8];

	if (!temp->search(addr)) {
		temp->reset_search();
		delay(250);
		return false;
	}

	p_log("Tempereuse::initTemp()", etapeEnCours, 0);

	return true;
}

Tempereuse::~Tempereuse()
{
	delete temp;
}

double Tempereuse::getTemp()
{
	byte i;
	byte type_s = 0;
	byte data[12];
	
	// Ici la conversion est exécutée, depuis le cycle précédent

	temp->reset();
	temp->select(addr);

	temp->write(0xBE);         // Read Scratchpad

	for (i = 0; i < 9; i++) {           // we need 9 bytes
		data[i] = temp->read();
	}

	// Convert the data to actual temperature
	// because the result is a 16 bit signed integer, it should
	// be stored to an "int16_t" type, which is always 16 bits
	// even when compiled on a 32 bit processor.
	int raw = (data[1] << 8) | data[0];
	
	byte cfg = (data[4] & 0x60);
	// at lower res, the low bits are undefined, so let's zero them
	if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
	else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
	else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms

	p_log("Tempereuse::getTemp()", etapeEnCours, 0);

	// On demande le début de la conversion ici, pour gagner du temps
	temp->reset();
	temp->select(addr);
	temp->write(0x44, 1);        // start conversion, with parasite power on at the end

	//delay(1000);     // maybe 750ms is enough, maybe not
					 // we might do a temp->depower() here, but the reset will take care of it.

	//// default is 12 bit resolution, 750 ms conversion time
	return (double)raw / 16.0;
}

// De Arduino Playground
float readFloat(unsigned int addr)
{
	union
	{
		byte b[4];
		float f;
	} data;
	for (int i = 0; i < 4; i++)
	{
		data.b[i] = EEPROM.read(addr + i);
	}

	//p_log("readFloat()", data.f, 0);

	return data.f;
}

// De Arduino Playground
void writeFloat(unsigned int addr, float x)
{
	union
	{
		byte b[4];
		float f;
	} data;
	data.f = x;
	for (int i = 0; i < 4; i++)
	{
		EEPROM.write(addr + i, data.b[i]);
	}
	//p_log("writeFloat()", 0, 0);

}

void p_log(char a[16], int b, int c)
{
	Serial.print("Fonction ");
	Serial.print(a);
	Serial.print(", : ");
	Serial.print(b);
	Serial.print(", : ");
	Serial.println(c);
}