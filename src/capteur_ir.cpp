#include "capteur_ir.h"

#define TEST 0

int lireCapteurIR(uint8_t capteur, uint8_t amplitude = 3)
{
    int nombreDeLectures = (amplitude*2)-1;
    uint16_t lectures[nombreDeLectures];
    for (int i=0; i<nombreDeLectures; i++)
    {
        lectures[i] = ROBUS_ReadIR(capteur);
    }

    return nombreDeLectures;
}

float lireDistanceIR(uint8_t capteur, uint8_t amplitude = 3)
{
    int nombreDeLectures = (amplitude*2)-1;
    uint16_t lectures[nombreDeLectures];
    for (int i=0; i<nombreDeLectures; i++)
    {
        lectures[i] = ROBUS_ReadIR(capteur);
    }
    float distance;
    distance = entreeAnalogiqueEnTension(calculerMediane(lectures, nombreDeLectures));
    distance = tensionEnDistance(distance);

    if (distance<10) distance = 0;
    if (distance>80) distance = 100;

    return distance;
}

bool estLettre(uint8_t capteur, uint8_t amplitude = 5)
{
    int nombreDeLectures = (amplitude*2)-1;
    uint16_t lectures[nombreDeLectures];
    for (int i=0; i<nombreDeLectures; i++)
    {
        lectures[i] = ROBUS_ReadIR(capteur);
    }
    if (calculerMediane(lectures, nombreDeLectures) >= 100) return true;
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

void debugCapteurIR()
{
    Serial.print("Distance interne: ");
    Serial.println(lireDistanceIR(INTERNE, 5));
    Serial.print("Nombre interne: ");
    Serial.println(ROBUS_ReadIR(INTERNE));
    delay(1000);
}

void debugEstLettre()
{
    Serial.print("Présence pince: ");
    Serial.print(estLettrePince());
    Serial.print("\tPrésence suivant: ");
    Serial.println(estLettreSuivant());
    delay(1000);
}