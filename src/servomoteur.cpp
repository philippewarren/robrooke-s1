#include "servomoteur.h"

float MS_PAR_ANGLE = 7.2;

bool servoActif[] = {false, false};
int ANGLE_INITIAL[] = {0, 0};
const int ANGLE_MINIMAL[] = {0, 0};
const int ANGLE_MAXIMAL[] = {180, 180};
uint8_t angleCourant[] = {ANGLE_INITIAL[PINCE], ANGLE_INITIAL[BRAS]};

int POS_PINCE_OUVERTE;
int POS_PINCE_FERMEE;
int POS_BRAS_HAUT;
int POS_BRAS_BAS;
int POS_BRAS_DEPLACEMENT;

void initialiserConstantesServos()
{
    if (Bob == 'A')
    {
        POS_PINCE_OUVERTE = 60;
        POS_PINCE_FERMEE = 180;
        POS_BRAS_HAUT = 115;
        POS_BRAS_BAS = 85;
        ANGLE_INITIAL[PINCE] = 60;
        ANGLE_INITIAL[BRAS] = 115;
        POS_BRAS_DEPLACEMENT = 135;
    }
    else
    {
        POS_PINCE_OUVERTE = 60;
        POS_PINCE_FERMEE = 180;
        POS_BRAS_HAUT = 115;
        POS_BRAS_BAS = 85;
        ANGLE_INITIAL[PINCE] = 60;
        ANGLE_INITIAL[BRAS] = 115;
        POS_BRAS_DEPLACEMENT = 135;
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

bool activerServo(uint8_t indexDuServomoteur)
{
    if (!servoActif[indexDuServomoteur])
    {
        SERVO_Enable(indexDuServomoteur);
        servoActif[indexDuServomoteur] = true;
        return true;
    }
    return false;
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
    if(activerServo(indexDuServomoteur))
    {
        SERVO_SetAngle(indexDuServomoteur, angleCourant[indexDuServomoteur]);
    }

    angle = angle<ANGLE_MINIMAL[indexDuServomoteur] ? ANGLE_MINIMAL[indexDuServomoteur] : angle;
    angle = angle>ANGLE_MAXIMAL[indexDuServomoteur] ? ANGLE_MAXIMAL[indexDuServomoteur] : angle;

    if(angleCourant<angle)
    {
        while(angleCourant[indexDuServomoteur]<angle)
        {
            SERVO_SetAngle(indexDuServomoteur, ++angleCourant[indexDuServomoteur]);
            delay(15);
        }
    }
    else if(angleCourant>angle)
    {
        while(angleCourant[indexDuServomoteur]>angle)
        {
            SERVO_SetAngle(indexDuServomoteur, --angleCourant[indexDuServomoteur]);
            delay(15);
        }
    }
    else SERVO_SetAngle(indexDuServomoteur, angleCourant[indexDuServomoteur]);
   
    // delay(MS_PAR_ANGLE*max(abs(ANGLE_MAXIMAL[indexDuServomoteur]-angle), abs(ANGLE_MINIMAL[indexDuServomoteur]-angle)));
    // delay(2000);
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

bool leverBrasDeplacement(bool estFixe = true)
{
    // changerAngleServo(BRAS,POS_BRAS_BAS, estFixe);
    // int angle = POS_BRAS_BAS;
    // while (angle < POS_BRAS_DEPLACEMENT)
    // {
    //     angle ++;
    //     SERVO_SetAngle(BRAS,angle);
    //     delay(15);
    // }
    changerAngleServo(BRAS,POS_BRAS_DEPLACEMENT, estFixe);
}

bool baisserBras(bool estFixe = true)
{
    // changerAngleServo(BRAS,POS_BRAS_DEPLACEMENT, estFixe);
    // int angle = POS_BRAS_DEPLACEMENT;
    // while (angle > POS_BRAS_BAS)
    // {
    //     angle --;
    //     SERVO_SetAngle(BRAS,angle);
    //     delay(15);
    // }
    changerAngleServo(BRAS,POS_BRAS_BAS, estFixe);
    
    return estFixe;
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