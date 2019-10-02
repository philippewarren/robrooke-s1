#include <LibRobus.h>
#include <EEPROM.h>

const double CLICS_PAR_CM = 3200/(2.54*3*PI);

double clicsEnCm(long nbClics);

long long cmEnClics(float nbCm);

void resetDeuxEncodeurs();

void changerVitesseMoteur(uint8_t moteur, float nouvelleVitesse);

void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD);

void arreterDeuxMoteurs();