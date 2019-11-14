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

#include "loop_normal.h"
#include "loop_urgence.h"
#include "loop_A.h"
#include "loop_B.h"

//Indice 0: où Bob-A va chercher le ballon
//Indice 1: où Bob-B va porter le ballon
extern const int COULEURS_BOB[];

//Bob-A ou Bob-B ('A' ou 'B', 'I' avant d'être initialisé)
extern char Bob;

//Utilisée pour signifier que l'interrupt est activé
extern volatile bool arretUrgence;

//Appelle BoardInit() et cie, et initialise nos fonctions et variables
void initialiserBob();

//Initialise les ports pour les DEL
void initialiserPortsDEL();
//Initialise les ports pour les boutons
void initialiserPortsBoutons();
//Initialise les ports pour l'ISR d'arrêt d'urgence
void initialiserPortsInterrupt();
//Initialise les lecteurs de catpeur IR lisant des distances
void initialiserCapteursIR();

//ISR d'arrêt d'urgence
void isrARRET();



#endif