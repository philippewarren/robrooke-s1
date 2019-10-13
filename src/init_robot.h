#ifndef INIT_ROBOT_H
#define INIT_ROBOT_H

#include <Arduino.h>
#include <LibRobus.h>
#include <EEPROM.h>

#include "conversions.h"
#include "mouvement.h"
#include "interactions.h"

//Bob-A ou Bob-B ('A' ou 'B', 'I' avant d'être initialisé)
extern char Bob;

//Contient les ports utilisés pour les 4 DEL aux index 1 à 4, et 0 à l'index 0
extern const byte portDEL[];

//Appelle BoardInit() et cie, et initialise nos fonctions et variables
void initialiserBob();
//Initialise les ports pour les DEL
void initialiserPortsDEL();
//Initialise les ports pour l'ISR d'arrêt d'urgence
void initialiserPortsInterrupt();

//ISR d'arrêt d'urgence
void isrARRET();



#endif