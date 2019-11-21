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

uint16_t lireValeurIR(uint8_t capteur, uint8_t amplitude = 5)
{
    int nombreDeLectures = (amplitude*2)-1;
    uint16_t lectures[nombreDeLectures];

    for (int i=0; i<nombreDeLectures; i++)
    {
        lectures[i] = ROBUS_ReadIR(capteur);
    }
    return calculerMediane(lectures, nombreDeLectures);
}

bool estLettrePince()
{
    int valeur = lireValeurIR(INTERNE);
    Serial.println(valeur);
    if (valeur<500 && valeur > 100) return true;
    else return false;
}

bool estLettreSuivant()
{
    int valeur = lireValeurIR(EXTERNE);
    if (valeur>100) return true;
    else return false;
}

void debugCapteurIR(uint8_t capteur)
{
    Serial.print("Distance: ");
    Serial.println(lireDistanceIR(capteur, 5));
    Serial.print("Nombre: ");
    Serial.println(ROBUS_ReadIR(capteur));
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