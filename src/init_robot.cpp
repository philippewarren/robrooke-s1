#include "init_robot.h"

char Bob  = 'I';
extern float largeurEss;
const byte portDEL[] = {0, 45, 47, 49, 51};

const byte portInterrupt = 21;
const byte portRestart = 20;

void initialiserBob()
{
    BoardInit();
    Bob = EEPROM.read(0);
    initialiserPortsDEL();
    initialiserPortsInterrupt();
    largeurEss = Bob=='A' ? 18.2 : 18.1;
    // DIST_90 = (largeurParc-largeurEss)/2;    //la distance que Bob doit avancer pour un virage de 90 degres
    // DIST_45 = DIST_90*TAN_22_5;              //la distance que Bob doit avancer pour un virage de 45 degres
}

void initialiserPortsDEL()
{
    for (int i=1; i<=4; i++)
    {
        pinMode(portDEL[i], OUTPUT);
    }
}

void initialiserPortsInterrupt()
{
    pinMode(portInterrupt, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(portInterrupt), isrARRET, FALLING);
}

void isrARRET()
{
    arreterDeuxMoteurs();
    AX_BuzzerON();
    allumerDEL(0);
    while (digitalRead(portRestart)!=HIGH)
    {
        //Attend qu'on reboot avec le bouton
    }
    AX_BuzzerOFF();
    eteindreDEL(0);
}