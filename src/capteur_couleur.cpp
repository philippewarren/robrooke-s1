#include "capteur_couleur.h"

Adafruit_TCS34725 CapteurCouleur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

const uint16_t TOUTES_COULEURS[] = {ROUGE, JAUNE, VERT, TURQUOISE, BLEU, MAUVE};
const uint16_t COULEURS_OCTOGONE[] = {ROUGE, JAUNE, VERT, BLEU};
const uint16_t COULEURS_LETTRES[] = {ROUGE, VERT, BLEU};

void initialiserCapteurCouleur()
{
    if (CapteurCouleur.begin())
    {
        Serial.println("Found sensor");
    }
    else
    {
        Serial.println("No TCS34725 found ... check your connections");
    }

    return;
}

void lireCapteurCouleur(uint8_t numero, uint16_t tableau[4])
{    
    uint16_t rouge;
    uint16_t vert;
    uint16_t bleu;
    uint16_t sansCouleur;

    // CapteurCouleur.setInterrupt(false);      // turn on LED
    CapteurCouleur.getRawData(&rouge, &vert, &bleu, &sansCouleur);
    // CapteurCouleur.setInterrupt(true);      // turn off LED
    
    tableau[0] = rouge;
    tableau[1] = vert;
    tableau[2] = bleu;
    tableau[3] = sansCouleur;

    return;
}

int evaluerCouleur(uint16_t tableau[4], const uint16_t couleursPossibles[] = TOUTES_COULEURS)
{
    rgbEnHsl(tableau);

    int couleur;
    //Rouge?
    if ((tableau[0]>=330 || tableau[0]<30) && (tableau[1]>15) && (tableau[2]>25 && tableau[2]<75))
    couleur = ROUGE;
    
    //Jaune?
    if ((tableau[0]>=30 || tableau[0]<90) && (tableau[1]>15) && (tableau[2]>25 && tableau[2]<75))
    couleur = JAUNE;

    //Vert?
    if ((tableau[0]>=90 || tableau[0]<150) && (tableau[1]>15) && (tableau[2]>25 && tableau[2]<75))
    couleur = VERT;

    //Turquoise?
    if ((tableau[0]>=150 || tableau[0]<210) && (tableau[1]>15) && (tableau[2]>25 && tableau[2]<75))
    couleur = TURQUOISE;

    //Bleu?
    if ((tableau[0]>=210 || tableau[0]<270) && (tableau[1]>15) && (tableau[2]>25 && tableau[2]<75))
    couleur = BLEU;

    //Mauve?
    if ((tableau[0]>=270 || tableau[0]<330) && (tableau[1]>15) && (tableau[2]>25 && tableau[2]<75))
    couleur = MAUVE;

    //Blanc?
    if (/*tableau[1]>75 &&*/ tableau[2]>=90)
    couleur = BLANC;

    //Noir?
    if (/*tableau[1]<25 &&*/ tableau[2]<15)
    couleur = NOIR;

    //Gris?
    if (tableau[1]<=15 && (tableau[2]>=15 || tableau[2]<90))
    couleur = GRIS;

    return couleur;
}