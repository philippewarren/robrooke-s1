#include "servomoteur.h"

bool servoActif[] = {false, false};
const int ANGLE_INITIAL[] = {0, 0};
const int ANGLE_MINIMAL[] = {0, 0};
const int ANGLE_MAXIMAL[] = {180, 180};

const int POS_PINCE_OUVERTE = 0;
const int POS_PINCE_FERMEE = 0;
const int POS_BRAS_HAUT = 0;
const int POS_BRAS_BAS = 0;

void initialiserServoFixe(uint8_t indexDuServomoteur)
{
    activerServo(indexDuServomoteur);
    changerAngleServoFixe(indexDuServomoteur, ANGLE_INITIAL[indexDuServomoteur]);
    return;
}

void initialiserServoLibre(uint8_t indexDuServomoteur)
{
    initialiserServoFixe(indexDuServomoteur);
    desactiverServo(indexDuServomoteur);
    return;
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

void changerAngleServoFixe(uint8_t indexDuServomoteur, uint8_t angle)
{
    activerServo(indexDuServomoteur);
    angle = angle<ANGLE_MINIMAL[indexDuServomoteur] ? ANGLE_MINIMAL[indexDuServomoteur] : angle;
    angle = angle>ANGLE_MAXIMAL[indexDuServomoteur] ? ANGLE_MAXIMAL[indexDuServomoteur] : angle;

    SERVO_SetAngle(indexDuServomoteur, angle);

    return;
}

void changerAngleServoLibre(uint8_t indexDuServomoteur, uint8_t angle)
{
    activerServo(indexDuServomoteur);
    angle = angle<ANGLE_MINIMAL[indexDuServomoteur] ? ANGLE_MINIMAL[indexDuServomoteur] : angle;
    angle = angle>ANGLE_MAXIMAL[indexDuServomoteur] ? ANGLE_MAXIMAL[indexDuServomoteur] : angle;

    SERVO_SetAngle(indexDuServomoteur, angle);
    desactiverServo(indexDuServomoteur);

    return;
}

void ouvrirPince(bool estFixe = false)
{
    if (estFixe)
        changerAngleServoFixe(PINCE,POS_PINCE_OUVERTE);
    else
        changerAngleServoLibre(PINCE, POS_PINCE_OUVERTE);
    return;
}

void fermerPince(bool estFixe = true)
{
     if (estFixe)
        changerAngleServoFixe(PINCE,POS_PINCE_FERMEE);
    else
        changerAngleServoLibre(PINCE, POS_PINCE_FERMEE);
    return;
}