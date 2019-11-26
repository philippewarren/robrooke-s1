#ifndef INIT_ROBOT_H
#define INIT_ROBOT_H

#include <LibRobus.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <Adafruit_TCS34725.h>

#include "interactions.h"
#include "conversions.h"
#include "mouvement.h"
#include "del_couleur.h"

#include "capteur_couleur.h"
#include "capteur_ir.h"
#include "suiveur_ligne.h"
#include "servomoteur.h"

//Indice 0: où Bob-A va chercher le ballon
//Indice 1: où Bob-B va porter le ballon
extern const int COULEURS_BOB[];

//Bob-A ou Bob-B ('A' ou 'B', 'I' avant d'être initialisé)
extern char Bob;

//Appelle BoardInit() et cie, et initialise nos fonctions et variables
void initialiserBob();

//Initialise les ports pour les DEL
void initialiserPortsDEL();
//Initialise les ports pour les DEL de couleur
void initialiserPortsDELCouleur();
//Initialise les ports pour les boutons
void initialiserPortsBoutons();
//Initialise les ports du suiveur de ligne 
void initialiserPortSuiveurLigne();

//Initialise le port pour l'interrupt et l'attache
void initialiserInterrupt();



#endif