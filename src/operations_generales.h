#ifndef OPERATIONS_GENERALES_H
#define OPERATIONS_GENERALES_H

#include <LibRobus.h>

//Prend un tableau d'int et sa longueur, et classe les membres du tableau en ordre croissant
void classerTableauCroissant(uint16_t tableau[], int NB_ELEMENTS);

//Prend un tableau d'int et sa longueur (impaire), et renvoie la mediane parmi ses membres
uint16_t calculerMediane(uint16_t tableau[], int NB_ELEMENTS);



#endif