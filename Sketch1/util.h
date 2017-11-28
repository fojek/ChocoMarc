// util.h

#ifndef _UTIL_h
#define _UTIL_h

// Utilitaire de log par communication série
void p_log(char a[16], int b, int c);
void p_log_2(char a[16], int b, int c);

// Pour les menus avec valeurs actuelle
char * ftoa(char *, double, int);	// Convertir float en char
bool deviationVal(float, float); // Voir si il y a eu une variation acceptable

// Pour lecture/ecriture dans l'EEPROM
float readFloat(unsigned int addr);
void writeFloat(unsigned int addr, float x);

// Fonctions pour formatter les valeurs
void formatVal(char * l2, float val1, float val2, float val3); // Formate 3 floats en str
void formatValInt(char * l2, int val1, int val2, int val3); // Formate 3 int en str
void formatVal(char * l2, int val); // Formate 1 int en str
void formatVal(char * l2, float val); // Formate 1 float en str
// Sous fonctions formattage
char * format(char * v1, char * v2, char * v3); // Formate 3 char en "00.0 | 00.0 | 00.0 " 
#endif

