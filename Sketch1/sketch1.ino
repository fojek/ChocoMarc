/*
 Name:		Sketch1.ino
 Created:	1/9/2017 10:23:03 AM
 Author:	mfortier
*/

#include <EEPROM.h>
#include <OneWire.h>
#include <PID_v1.h>
#include <ArduinoSTL.h>
#include "baseMenu.h"
#include "Tempereuse.h"

extern float readFloat(unsigned int);
extern void p_log(char[16], int, int);

// Enum et variables pour les boutons
enum BOUTON { btnUP, btnDOWN, btnLEFT, btnRIGHT, btnSELECT, btnNONE };
int lcd_key = 0;
int adc_key_in = 0;

// Prototypes de fonction
BOUTON read_LCD_buttons();

// Pins qui seront utilisées
const int HEATER = 15;
const int TEMP = 2;

// Variables pour les menus
int indexRecette = 0;
int indexRecette_old = indexRecette;
float temperature, cible, chauffage;

// Instance du menu
baseMenu menu;

// Instance de la tempéreuse
Tempereuse * tempereuse = new Tempereuse(HEATER, TEMP);

// the setup function runs once when you press reset or power the board
void setup() 
{
	// Démarrage de la communication série
	Serial.begin(9600);

	p_log("setup()_debut_", tempereuse->etape(), 0);
	
	tempereuse->init();

	p_log("setup()_debut_2", tempereuse->etape(), 0);

	Recette dummy;
	dummy.set(45, 26, 29);
	dummy.saveRecette(0);
	dummy.set(22, 23, 24);
	dummy.saveRecette(1);
	dummy.set(32, 33, 34);
	dummy.saveRecette(2);

	Serial.println((int)dummy.setpoint(0));

	dummy.loadRecette(0);

	Serial.println((int)dummy.setpoint(0));

	p_log("setup()_fin_", tempereuse->etape(), 0);

	// Définition des menus
	menu.addMenu("ChocoMarc v1.0", "< hit any key >",
				Action(TYPE::GoTo, 1),
				Action(TYPE::GoTo, 1),
				Action(TYPE::GoTo, 1),
				Action(TYPE::GoTo, 1));

	menu.addMenu("Choix de la recette :", "",
				Action(TYPE::INCREMENTE, 1), 
				Action(TYPE::DECREMENTE, 2), 
				Action(TYPE::CONFIRME, 0), 
				Action(TYPE::CONFIRME, 0),
				indexRecette);

	menu.addMenu("Temp|Cible|Chauf", "",
		Action(TYPE::GoTo, 0), 
		Action(TYPE::GoTo, 0), 
		Action(TYPE::GoTo, 0),
		Action(TYPE::GoTo, 0),
		temperature,
		cible,
		chauffage);

	menu.AfficheMenu();
	p_log("setup()_fin_", tempereuse->etape(), 0);

	//pinMode(HEATER, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	p_log("loop()_debut_cycle", tempereuse->etape(), 0);

	unsigned char commande;
	BOUTON bouton = read_LCD_buttons();

	if (bouton != btnNONE)
	{
		menu.PeseBouton(bouton);
		menu.AfficheMenu();
		p_log("loop()_bouton", bouton, 0);
	}

	menu.Update();
	tempereuse->update(temperature);
	Serial.println(temperature);
	if (!tempereuse->estEnMarche())
	{
		p_log("loop()_recette_démarrée", bouton, 0);
		tempereuse->start(indexRecette);
	}

	// Une recette différente a été choisie
	if (indexRecette != indexRecette_old)
	{
		indexRecette = indexRecette_old;
		// Charge la recette et démarre le PID
		menu.GoToMenu(2);
		tempereuse->start(indexRecette);
		p_log("loop()_recette_changée", bouton, 0);
	}

	p_log("loop()_fin_cycle", tempereuse->etape(), 0);

	cible = tempereuse->setPoint();
	chauffage = tempereuse->chauffage();

	delay(200);
}

BOUTON read_LCD_buttons() // read the buttons
{               
	adc_key_in = analogRead(0);       // read the value from the sensor 

	if (adc_key_in > 1000) return BOUTON::btnNONE;

	// For V1.1 us this threshold
	if (adc_key_in < 50)   return BOUTON::btnRIGHT;
	if (adc_key_in < 250)  return BOUTON::btnUP;
	if (adc_key_in < 450)  return BOUTON::btnDOWN;
	if (adc_key_in < 650)  return BOUTON::btnLEFT;
	if (adc_key_in < 850)  return BOUTON::btnSELECT;

	return BOUTON::btnNONE;                // when all others fail, return this.*/
}