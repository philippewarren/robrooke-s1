#include "deplacement.h"

void syncroMoteur(const float nouvelleVitesse)
{
    //variables static
    static float vitesse = 0;
    static float correction = 1;
    static long dernierEncodeurDroit = 0;
    static long dernierEncodeurGauche = 0;

    //changement de vitesse
    if (nouvelleVitesse > -999)
    {
        if (vitesse*nouvelleVitesse < 0)
        {
            MOTOR_SetSpeed(0,1);
            MOTOR_SetSpeed(1,0);
            delay(100);
        }
        vitesse = nouvelleVitesse;
    }
    //adaptation de la vitesse
    long encodeurDroit = ENCODER_Read(1);
    long encodeurGauche = ENCODER_Read(0);
    if ((encodeurGauche-dernierEncodeurGauche)!=0&&(encodeurDroit-dernierEncodeurDroit)!=0)//pour eviter une correction infini
        correction = (float)(encodeurDroit-dernierEncodeurDroit)/correction/(encodeurGauche-dernierEncodeurGauche);

    //mise en place d'une nouvelle vitesse pour les moteurs
    MOTOR_SetSpeed(0,vitesse);
    MOTOR_SetSpeed(1,vitesse/correction);
    Serial.println((float)(encodeurDroit-dernierEncodeurDroit)/(encodeurGauche-dernierEncodeurGauche));

    //mise en mémoire static des valeurs d'encodeur
    dernierEncodeurGauche = encodeurGauche;
    dernierEncodeurDroit = encodeurDroit;
}