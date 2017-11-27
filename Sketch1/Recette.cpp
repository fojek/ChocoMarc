#include "Recette.h"
#include <EEPROM.h>
#include <OneWire.h>

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