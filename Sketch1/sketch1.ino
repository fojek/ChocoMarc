/*
 Name:		Sketch1.ino
 Created:	1/9/2017 10:23:03 AM
 Author:	mfortier
*/

#include "util.h"
#include "Recette.h"
#include "Action.h"
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

// Pins qui seront utilis�es
const int HEATER = 15;
const int TEMP = 2;

// Variables pour les menus
int indexRecette = 0;
int indexRecette_old = indexRecette;
int recetteEnEdition = 0;
float temperature, cible, chauffage;
bool goLoadRecipe = false;
bool dummyBool = false;

// Instance du menu
BaseMenu menu;

// Initialisation des menus
BOUTON bouton = btnNONE;
BOUTON bouton_old = btnNONE;

// Instance de la temp�reuse
Tempereuse * tempereuse = new Tempereuse(HEATER, TEMP);

// the setup function runs once when you press reset or power the board
void setup()
{
	// D�marrage de la communication s�rie
	Serial.begin(9600);

	p_log("setup()_debut_", tempereuse->etape(), 0);

	tempereuse->init();

	p_log("setup()_debut_2", tempereuse->etape(), 0);

	Recette dummy;

	dummy.set(45, 27, 31);	// Chocolat noir
	dummy.saveRecette(0);
	//dummy.loadRecette(0);

	Serial.println((int)dummy.setpoint(0));

	p_log("setup()_fin_", tempereuse->etape(), 0);

	// D�finition des menus
	menu.addMenu("ChocoMarc v1.0", " < Continuer > ",
		Action::createNull(),
		Action::createNull(),
		Action::createGoto(1),
		Action::createGoto(1));

	menu.addMenu("Temp. actuelle",
		Action::createNull(),
		Action::createNull(),
		Action::createGoto(2),
		Action::createGoto(2),
		temperature);

	menu.addMenu("Choix recette   ", "",
		Action::createInc(),
		Action::createDec(),
		Action::createConfirme(),
		Action::createGoto(3),
		indexRecette,
		goLoadRecipe);

	menu.addMenu("Edition recette #", "",
		Action::createInc(),
		Action::createDec(),
		Action::createConfirme(),
		Action::createGoto(4),
		recetteEnEdition,
		dummyBool);

	menu.addMenu("Recette X",
		Action::createInc(),
		Action::createDec(),
		Action::createConfirme(),
		Action::createGoto(1),
		recetteEnEdition);

	menu.addMenu("Temp|Cible|Chauf", "",
		Action::createNull(),
		Action::createNull(),
		Action::createGoto(0),
		Action::createGoto(0),
		temperature,
		cible,
		chauffage);

	for (int i = 0; i < menu.menu.size(); ++i)
	{
		menu.menu[i]->logAll();
	}

	menu.AfficheMenu();
	p_log("setup()_fin_", tempereuse->etape(), 0);

}

// the loop function runs over and over again until power down or reset
void loop() {
	p_log("loop()_debut_cycle", tempereuse->etape(), 0);
	p_log_2("edit", recetteEnEdition, 0);

	unsigned char commande;
	bouton = read_LCD_buttons();

	// Pour �viter que les boutons fassent plusieurs actions rapidement
	if (bouton != bouton_old)
	{
		if (bouton != btnNONE) {
			menu.PeseBouton(bouton);
			menu.AfficheMenu();
			p_log("loop()_bouton", bouton, 0);
		}

		bouton_old = bouton;

	}

	menu.Update();

	// Charge la recette et d�marre le PID
	if (goLoadRecipe) {
		menu.GoToMenu(5);
		tempereuse->start(indexRecette);
		p_log("loop()_recette_d�marr�e", bouton, 0);
		goLoadRecipe = false;
	}

	tempereuse->update(temperature);

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