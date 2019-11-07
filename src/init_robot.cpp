#include "init_robot.h"

char Bob  = 'I';
volatile bool arretUrgence = false;
extern float largeurEss;

const int COULEURS_BOB[] = {VERT, JAUNE};

void initialiserBob()
{
    BoardInit();
    Bob = EEPROM.read(0);
    initialiserDeuxServos();
    initialiserPortsDEL();
    //initialiserPortsBoutons();
    //initialiserPortsInterrupt();
    largeurEss = Bob=='A' ? 18.2 : 18.1;
    // DIST_90 = (largeurParc-largeurEss)/2;    //la distance que Bob doit avancer pour un virage de 90 degres
    // DIST_45 = DIST_90*TAN_22_5;              //la distance que Bob doit avancer pour un virage de 45 degres
    Serial.println("##Connection serie active et fonctionnelle.##");
    //initialiserCapteurCouleur();
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
    pinMode(PORT_INTERRUPT, INPUT);
    attachInterrupt(digitalPinToInterrupt(PORT_INTERRUPT), isrARRET, FALLING);
}

void isrARRET()
{
    arretUrgence = true;
    arreterDeuxMoteurs();
}