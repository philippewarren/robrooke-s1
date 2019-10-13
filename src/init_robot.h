#ifndef INIT_ROBOT_H
#define INIT_ROBOT_H

#include <LibRobus.h>
#include <Arduino.h>
#include <EEPROM.h>

#include "interactions.h"
#include "conversions.h"
#include "mouvement.h"

//Bob-A ou Bob-B ('A' ou 'B', 'I' avant d'être initialisé)
extern char Bob;

//Appelle BoardInit() et cie, et initialise nos fonctions et variables
void initialiserBob();
//Initialise les ports pour les DEL
void initialiserPortsDEL();
//Initialise les ports pour les boutons
void initialiserPortsBoutons();
//Initialise les ports pour l'ISR d'arrêt d'urgence
void initialiserPortsInterrupt();

//ISR d'arrêt d'urgence
void isrARRET();



#endif