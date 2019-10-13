#include "init_robot.h"

char Bob  = 'I';
extern float largeurEss;

void initialiserBob()
{
    BoardInit();
    initialiserPortsDEL();
    initialiserPortsBoutons();
    initialiserPortsInterrupt();
    Bob = EEPROM.read(0);
    largeurEss = Bob=='A' ? 18.2 : 18.1;
    // DIST_90 = (largeurParc-largeurEss)/2;    //la distance que Bob doit avancer pour un virage de 90 degres
    // DIST_45 = DIST_90*TAN_22_5;              //la distance que Bob doit avancer pour un virage de 45 degres
      Serial.println("##Connection serie active et fonctionnelle.##");
}

void initialiserPortsDEL()
{
    for (int i=1; i<=4; i++)
    {
        pinMode(PORT_DEL[i], OUTPUT);
    }
}

void initialiserPortsBoutons()
{
    for (int i=0; i<=4; i++)
    {
        pinMode(PORT_BOUTON[i], INPUT);
    }
}

void initialiserPortsInterrupt()
{
    pinMode(PORT_INTERRUPT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PORT_INTERRUPT), isrARRET, FALLING);
}

void isrARRET()
{
    arreterDeuxMoteurs();
    AX_BuzzerON();
    allumerDEL(0);
    while (digitalRead(PORT_RESTART)!=HIGH)
    {
        //Attend qu'on reboot avec le bouton
    }
    AX_BuzzerOFF();
    eteindreDEL(0);
}