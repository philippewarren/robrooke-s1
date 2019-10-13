#include "init_robot.h"

char Bob  = 'I';
extern float largeurEss;

const byte brocheInterrupt = 21;
const byte brocheRestart = 20;

void initialiserBob()
{
  Bob = EEPROM.read(0);
  pinMode(brocheInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(brocheInterrupt), arretUrgence, FALLING);
  largeurEss = Bob=='A' ? 18.2 : 18.1;
// DIST_90 = (largeurParc-largeurEss)/2;    //la distance que Bob doit avancer pour un virage de 90 degres
// DIST_45 = DIST_90*TAN_22_5;              //la distance que Bob doit avancer pour un virage de 45 degres
}

//ISR d'arrêt d'urgence
void arretUrgence()
{
    arreterDeuxMoteurs();
    AX_BuzzerON();
    while (digitalRead(brocheRestart)!=HIGH)
    {
        //Attend qu'on reboot avec le bouton
    }
    AX_BuzzerOFF();
}