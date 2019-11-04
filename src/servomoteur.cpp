#include "servomoteur.h"

bool servoActif[] = {false, false};
const int ANGLE_INITIAL[] = {40, 0};
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
        POS_PINCE_OUVERTE = 95;
        POS_PINCE_FERMEE = 40;
        POS_BRAS_HAUT = 0;
        POS_BRAS_BAS = 0;
    }
    else
    {
        POS_PINCE_OUVERTE = 45;
        POS_PINCE_FERMEE = 178;
        POS_BRAS_HAUT = 0;
        POS_BRAS_BAS = 0;
    }
    return;
}

const int DELAIS_OCTOGONE = 1500;

bool initialiserServo(uint8_t indexDuServomoteur, bool estFixe = false)
{
    activerServo(indexDuServomoteur);
    changerAngleServo(indexDuServomoteur, ANGLE_INITIAL[indexDuServomoteur]);
    if (!estFixe)
        desactiverServo(indexDuServomoteur);
    return estFixe;
}

void initialiserDeuxServos()
{
    initialiserConstantesServos();
    initialiserServo(PINCE, ANGLE_INITIAL[PINCE]);
    initialiserServo(BRAS, ANGLE_INITIAL[BRAS]);
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