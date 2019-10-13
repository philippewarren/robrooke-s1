#ifndef INIT_ROBOT_H
#define INIT_ROBOT_H

#include <Arduino.h>
#include <LibRobus.h>
#include <EEPROM.h>

#include "conversions.h"
#include "mouvement.h"
#include "interactions.h"


extern char Bob;

void initialiserBob();

void arretUrgence();

#endif