#include "capteur_ir.h"

float lireDistanceIR(uint8_t capteur, uint8_t amplitude = 3)
{
    int nombreDeLectures = (amplitude*2)-1;
    int lectures[nombreDeLectures];
    float distance;
    for (int i=0; i<nombreDeLectures; i++)
    {
        lectures[i] = ROBUS_ReadIR(capteur);
    }
    distance = entreeAnalogiqueEnTension(calculerMediane(lectures, nombreDeLectures));
    distance = tensionEnDistance(distance);

    return distance;
}