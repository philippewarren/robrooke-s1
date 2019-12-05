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
    pinMode(pin, OUTPUT);
}

void initialiserPortsDEL()
{
    for (int i=1; i<=4; i++)
    {
        pinMode(PORT_DEL[i], OUTPUT);
    }
}

void initialiserPortsDELCouleur()
{
    pinMode(PORT_ROUGE, OUTPUT);
    pinMode(PORT_VERT, OUTPUT);
    pinMode(PORT_BLEU, OUTPUT);
    pinMode(PORT_JAUNE, OUTPUT);
}