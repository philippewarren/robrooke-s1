#include "capteur_ir.h"

float lireDistanceIR(uint8_t capteur, uint8_t amplitude = 3)
{
    int nombreDeLectures = (amplitude*2)-1;
    uint16_t lectures[nombreDeLectures];
    float distance;
    for (int i=0; i<nombreDeLectures; i++)
    {
        lectures[i] = ROBUS_ReadIR(capteur);
    }
    distance = entreeAnalogiqueEnTension(calculerMediane(lectures, nombreDeLectures));
    distance = tensionEnDistance(distance);

    if (distance<10) distance = 0;
    if (distance>80) distance = 100;

    return distance;
}

bool estLettre(uint8_t capteur)
{
    float seuil;
    float distance = lireDistanceIR(capteur, 5);

    if (capteur == INTERNE) seuil = SEUIL_LETTRE_INTERNE;
    else seuil = SEUIL_LETTRE_EXTERNE;

    if (distance < seuil) return true;
    else return false;
}

bool estLettrePince()
{
    return estLettre(INTERNE);
}

bool estLettreSuivant()
{
    return estLettre(EXTERNE);
}