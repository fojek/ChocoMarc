// Fonctions réutilisables

#include "util.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ArduinoSTL.h>
#include <PID_v1.h>
#include <OneWire.h>
#include <EEPROM.h>

// Fonction pour convertir les float en char (Arduino playground)
char * ftoa(char * a, double f, int precision)
{
	char *ret = a;

	int entier = (int)f;
	float reste = f - entier;

	sprintf(ret, "%d", entier);

	if (f >= 10000 || f <= -1000) // 5 caractères : ne peut pas afficher
		return "err.";
	else if (f >= 100 || f <= -10) // 3 ou 4 caractères : affiche sans décimale
	{
		if (strlen(ret) == 3) // Si 3 caracteres, on ajoute un espace à la fin
			strcat(ret, " ");
		return ret;
	}
	else if (f >= 10 || f < 0) // 2 caractères : on affiche une décimale
	{
		reste *= 10; // une décimale

		strcat(ret, ".");
		char decimale[4];
		int decimale_int = (int)reste;

		sprintf(decimale, "%d", decimale_int);


		strcat(ret, decimale);
		return ret;
	}
	else // Valeur entre 0 et 9 : on affiche 2 décimales
	{
		reste *= 100; // deux décimales

		strcat(ret, ".");
		char decimale[4];
		int decimale_int = (int)reste;

		sprintf(decimale, "%d", decimale_int);

		// La première décimale est un zéro
		if (decimale_int < 10)
			strcat(ret, "0");

		strcat(ret, decimale);
		//strcat(ret, " ");
		return ret;
	}
}

bool deviationVal(float act, float old)
{
	// Deviation de 1% permise avant un refresh
	const float DEVIATION = 0.0001;

	if (abs(act - old) / act > DEVIATION)
		return true;

	return false;
}

void formatVal(char * l2, int val)
{
	char temp1[17];
	// Convertit en char
	ftoa(temp1, val, 0);
	// Copie dans la ligne 2
	strcpy(l2, temp1);
}

void formatVal(char * l2, float val)
{
	char temp1[17];
	// Convertit en char
	ftoa(temp1, val, 0);
	// Copie dans la ligne 2
	strcpy(l2, temp1);
}

void formatValInt(char * l2, int val1, int val2, int val3)
{
	char temp1[15];
	char temp2[5];
	char temp3[5];

	// Convertit les int en char
	ftoa(temp1, val1, 0);
	ftoa(temp2, val2, 0);
	ftoa(temp3, val3, 0);

	// Copie dans la ligne 2
	strcpy(l2, format(temp1, temp2, temp3));
}

void formatVal(char * l2, float val1, float val2, float val3) {

	char temp1[15];
	char temp2[5];
	char temp3[5];

	// Convertit les float en char
	ftoa(temp1, val1, 0);
	ftoa(temp2, val2, 0);
	ftoa(temp3, val3, 0);

	// Copie dans la ligne 2
	strcpy(l2, format(temp1, temp2, temp3));

}

char * format(char * v1, char * v2, char * v3) {
	// Forme la chaîne de caractère : "00.0| 00.0 | 00.0"
	strcat(v1, "| ");
	strcat(v1, v2);
	strcat(v1, "|");
	strcat(v1, v3);

	// Copie dans la ligne 2
	return v1;
}

void p_log_2(char a[16], int b, int c)
{
	Serial.print("Fonction ");
	Serial.print(a);
	Serial.print(", : ");
	Serial.print(b);
	Serial.print(", : ");
	Serial.println(c);
}

void p_log(char a[16], int b, int c)
{
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

}