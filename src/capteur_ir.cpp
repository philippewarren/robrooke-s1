#include "capteur_ir.h"

const float TENSION_ARDUINO = 5.0;
const uint16_t ENTREE_ANALOGIQUE_MAX = 1023;

float entreeAnalogiqueEnTension(uint16_t entreeAnalogique)
{
  float tension = (float)((TENSION_ARDUINO/ENTREE_ANALOGIQUE_MAX)*(entreeAnalogique));

  return tension;
}

float tensionEnDistance(float tension)
{
  if (tension<=0.3) return 0;
  float distanceEnCM = 29.988 * pow(tension, -1.173);
  return distanceEnCM;
}

void classerTableauCroissant(uint16_t tableau[], const int NB_ELEMENTS)
{
    uint16_t temp;
    
    for (int i=0; i<NB_ELEMENTS-1; i++)
    {
        for (int j=i+1; j<NB_ELEMENTS-1; j++)
        {
            if(tableau[i]>tableau[j])
            {
                temp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = temp;
            }
        }
    }
    return;
}

uint16_t calculerMediane(uint16_t tableau[], const int NB_ELEMENTS)
{
    int position;
    uint16_t mediane;

    classerTableauCroissant(tableau, NB_ELEMENTS);
    position = ((NB_ELEMENTS-1)/2);
    mediane = tableau[position];

    return mediane;
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