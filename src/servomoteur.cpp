#include "servomoteur.h"

float MS_PAR_ANGLE = 7.2;

bool servoActif[] = {false, false};
int ANGLE_INITIAL[] = {0, 0};
const int ANGLE_MINIMAL[] = {0, 0};
const int ANGLE_MAXIMAL[] = {180, 180};

int POS_PINCE_OUVERTE;
int POS_PINCE_FERMEE;
int POS_BRAS_HAUT;
int POS_BRAS_BAS;

void initialiserConstantesServos()
{
    if (Bob == 'A')
    {
        POS_PINCE_OUVERTE = 60;
        POS_PINCE_FERMEE = 180;
        POS_BRAS_HAUT = 0;
        POS_BRAS_BAS = 0;
        ANGLE_INITIAL[PINCE] = 60;
        ANGLE_INITIAL[BRAS] = 0;
    }
    else
    {
        POS_PINCE_OUVERTE = 60;
        POS_PINCE_FERMEE = 180;
        POS_BRAS_HAUT = 0;
        POS_BRAS_BAS = 0;
        ANGLE_INITIAL[PINCE] = 60;
        ANGLE_INITIAL[BRAS] = 30;
    }
    return;
}

const int DELAIS_OCTOGONE = 1500;

bool initialiserServo(uint8_t indexDuServomoteur, bool estFixe = false)
{
    activerServo(indexDuServomoteur);
    changerAngleServo(indexDuServomoteur, ANGLE_INITIAL[indexDuServomoteur], estFixe);
    return estFixe;
}

void initialiserDeuxServos()
{
    initialiserConstantesServos();
    initialiserServo(PINCE);
    initialiserServo(BRAS);
}

void activerServo(uint8_t indexDuServomoteur)
{
    if (!servoActif[indexDuServomoteur])
    {
        SERVO_Enable(indexDuServomoteur);
        servoActif[indexDuServomoteur] = true;
    }
    return;
}

void desactiverServo(uint8_t indexDuServomoteur)
{
    if (servoActif[indexDuServomoteur]) 
    {
        SERVO_Disable(indexDuServomoteur);
        servoActif[indexDuServomoteur] = false;
    }
    return;
}

bool changerAngleServo(uint8_t indexDuServomoteur, uint8_t angle, bool estFixe = true)
{
    activerServo(indexDuServomoteur);
    angle = angle<ANGLE_MINIMAL[indexDuServomoteur] ? ANGLE_MINIMAL[indexDuServomoteur] : angle;
    angle = angle>ANGLE_MAXIMAL[indexDuServomoteur] ? ANGLE_MAXIMAL[indexDuServomoteur] : angle;

    SERVO_SetAngle(indexDuServomoteur, angle);
    delay((indexDuServomoteur==PINCE) ? MS_PAR_ANGLE*max(abs(ANGLE_MAXIMAL[indexDuServomoteur]-angle), abs(ANGLE_MINIMAL[indexDuServomoteur]-angle)) : 3000);
    // delay(3000);
    if (estFixe==false)
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

bool leverBras(bool estFixe = true)
{
    changerAngleServo(BRAS,POS_BRAS_HAUT, estFixe);
    return estFixe;
}

bool baisserBras(bool estFixe = true)
{
    changerAngleServo(BRAS,POS_BRAS_BAS, estFixe);
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

void loopAjustementServo(uint8_t indexDuServomoteur)
{
    static int angle = 0;
    changerAngleServo(indexDuServomoteur, angle);
    Serial.println(angle);

    if (loopEstCliqueEtRelache(0)) angle += 5;
    if (loopEstCliqueEtRelache(1)) angle -= 5;
    if (loopEstCliqueEtRelache(3)) angle = 0;
    angle = (angle>180) ? 0 : angle;
    angle = (angle<0) ? 180 : angle;
}