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