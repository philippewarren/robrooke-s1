#ifndef INTERACTIONS_H
#define INTERACTIONS_H
#include <LibRobus.h>
#include <Arduino.h>
#include "init_robot.h"

// Vrai si clique et relache, faux si ce n'est pas le cas
bool loopEstCliqueEtRelache(uint8_t);

//Allume une DEL, de 1 (défaut) à 4. 0 allume toutes les DEL
void allumerDEL(uint8_t numeroDEL = 1);

//Éteint une DEL, de 1 (défaut) à 4. 0 éteint toutes les DEL
void eteindreDEL(uint8_t numeroDEL = 1);

//Allume, puis éteint une DEL, de 1 (défaut) à 4, après delais (en ms). 0 flashe toutes les DEL
//Reste allumée pendant une seconde par défaut
void flasherDEL(uint8_t numeroDEL = 1, int delais = 1000);

#endif