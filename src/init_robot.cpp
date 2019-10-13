#include "init_robot.h"

char Bob  = 'I';
extern float largeurEss;

void initialiserBob()
{
  Bob = EEPROM.read(0);
  largeurEss = Bob=='A' ? 18.2 : 18.1;
// DIST_90 = (largeurParc-largeurEss)/2;    //la distance que Bob doit avancer pour un virage de 90 degres
// DIST_45 = DIST_90*TAN_22_5;              //la distance que Bob doit avancer pour un virage de 45 degres
}