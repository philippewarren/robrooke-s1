#include "init_robot.h"

char Bob  = 'I';
volatile bool arretUrgence = false;
extern float largeurEss;

const int COULEURS_BOB[] = {VERT, JAUNE};

void initialiserRobot()
{
    BoardInit();
    Bob = EEPROM.read(0);
    initialiserDeuxServos();
    initialiserPortsDEL();
    initialiserCapteurCouleur();
    initialiserPortsDELCouleur();
    initialiserPortSuiveurLigne();
    largeurEss = Bob=='A' ? 18.2 : 18.1;
    leverBrasDeplacement();
    Serial.println("##Connection serie active et fonctionnelle.##");
}

void initialiserPortSuiveurLigne()
{
    pinMode(OUTPUT,12);
    digitalWrite(12,HIGH);
}

void initialiserPortsDEL()
{
    for (int i=1; i<=4; i++)
    {
        pinMode(PORT_DEL[i], OUTPUT);
    }
}