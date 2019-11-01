#include "servomoteur.h"

bool servoActif[] = {false, false};
const int ANGLE_INITIAL[] = {0, 0};
const int ANGLE_MINIMAL[] = {0, 0};
const int ANGLE_MAXIMAL[] = {180, 180};

const int POS_PINCE_OUVERTE = 45;
const int POS_PINCE_FERMEE = 178;
const int POS_BRAS_HAUT = 0;
const int POS_BRAS_BAS = 0;

const int DELAIS_OCTOGONE = 1500;

bool initialiserServo(uint8_t indexDuServomoteur, bool estFixe = false)
{
    activerServo(indexDuServomoteur);
    changerAngleServo(indexDuServomoteur, ANGLE_INITIAL[indexDuServomoteur]);
    if (!estFixe)
        desactiverServo(indexDuServomoteur);
    return estFixe;
}

void activerServo(uint8_t indexDuServomoteur)
{
    if (!servoActif[indexDuServomoteur]) 
        SERVO_Enable(indexDuServomoteur);
    return;
}

void desactiverServo(uint8_t indexDuServomoteur)
{
    if (servoActif[indexDuServomoteur]) 
        SERVO_Disable(indexDuServomoteur);
    return;
}

bool changerAngleServo(uint8_t indexDuServomoteur, uint8_t angle, bool estFixe = true)
{
    activerServo(indexDuServomoteur);
    angle = angle<ANGLE_MINIMAL[indexDuServomoteur] ? ANGLE_MINIMAL[indexDuServomoteur] : angle;
    angle = angle>ANGLE_MAXIMAL[indexDuServomoteur] ? ANGLE_MAXIMAL[indexDuServomoteur] : angle;

    SERVO_SetAngle(indexDuServomoteur, angle);
    if (!estFixe)
    {
        desactiverServo(indexDuServomoteur);
    }

    return estFixe;
}

bool ouvrirPince(bool estFixe = true)
{
    changerAngleServo(PINCE,POS_PINCE_OUVERTE, estFixe);
    return estFixe;
}

bool fermerPince(bool estFixe = true)
{
    changerAngleServo(PINCE,POS_PINCE_FERMEE, estFixe);
    return estFixe;
}

bool ouvrirPinceOctogone(bool estFixe = true)
{
    bool retour = false;
    static bool ouverte = false;
    static long tempsInitial = 0;
    long delais = 0;
    if (tempsInitial==0) tempsInitial = millis();

    if (!ouverte)
    {
        ouvrirPince(estFixe);
        ouverte = true;
    }

    delais = millis()-tempsInitial;

    if (delais>=DELAIS_OCTOGONE)
    {
        tempsInitial=0;
        ouverte = false;
        retour = true;
    }
    
    return retour;
}

bool fermerPinceOctogone(bool estFixe = true)
{
    bool retour = false;
    static bool fermee = false;
    static long tempsInitial = 0;
    long delais = 0;
    if (tempsInitial==0) tempsInitial = millis();

    if (!fermee)
    {
        fermerPince(estFixe);
        fermee = true;
    }

    delais = millis()-tempsInitial;

    if (delais>=DELAIS_OCTOGONE)
    {
        tempsInitial=0;
        fermee = false;
        retour = true;
    }
    
    return retour;
}