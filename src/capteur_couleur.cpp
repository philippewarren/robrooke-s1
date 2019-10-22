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
    // CapteurCouleur.setInterrupt(true);      // turn off LED
    
    return;
}

void lireCapteurCouleur(uint8_t numeroDeCapteur, uint16_t tableauVide[4])
{    
    uint16_t rouge;
    uint16_t vert;
    uint16_t bleu;
    uint16_t sansCouleur;

    // CapteurCouleur.setInterrupt(false);      // turn on LED
    CapteurCouleur.getRawData(&rouge, &vert, &bleu, &sansCouleur);
    // CapteurCouleur.setInterrupt(true);      // turn off LED
    
    tableauVide[0] = (uint16_t)(256*(float)rouge/sansCouleur);
    tableauVide[1] = (uint16_t)(256*(float)vert/sansCouleur);
    tableauVide[2] = (uint16_t)(256*(float)bleu/sansCouleur);
    tableauVide[3] = sansCouleur;

    return;
}

int evaluerCouleur(uint16_t tableauRGB[4], const uint16_t couleursPossibles[] = TOUTES_COULEURS)
{
    rgbEnHsl(tableauRGB);
    const int SEUIL_GRIS = 0;

    int couleur;
    //Rouge?
    if ((tableauRGB[0]>=330 || tableauRGB[0]<30) && (tableauRGB[1]>SEUIL_GRIS) && (tableauRGB[2]>25 && tableauRGB[2]<75))
    couleur = ROUGE;
    
    //Jaune?
    if ((tableauRGB[0]>=30 || tableauRGB[0]<90) && (tableauRGB[1]>SEUIL_GRIS) && (tableauRGB[2]>25 && tableauRGB[2]<75))
    couleur = JAUNE;

    //Vert?
    if ((tableauRGB[0]>=90 || tableauRGB[0]<150) && (tableauRGB[1]>SEUIL_GRIS) && (tableauRGB[2]>25 && tableauRGB[2]<75))
    couleur = VERT;

    //Turquoise?
    if ((tableauRGB[0]>=150 || tableauRGB[0]<210) && (tableauRGB[1]>SEUIL_GRIS) && (tableauRGB[2]>25 && tableauRGB[2]<75))
    couleur = TURQUOISE;

    //Bleu?
    if ((tableauRGB[0]>=210 || tableauRGB[0]<270) && (tableauRGB[1]>SEUIL_GRIS) && (tableauRGB[2]>25 && tableauRGB[2]<75))
    couleur = BLEU;

    //Mauve?
    if ((tableauRGB[0]>=270 || tableauRGB[0]<330) && (tableauRGB[1]>SEUIL_GRIS) && (tableauRGB[2]>25 && tableauRGB[2]<75))
    couleur = MAUVE;

    //Blanc?
    if (/*tableauRGB[1]>75 &&*/ tableauRGB[2]>=90)
    couleur = BLANC;

    //Noir?
    if (/*tableauRGB[1]<25 &&*/ tableauRGB[2]<15)
    couleur = NOIR;

    //Gris?
    if (/*tableauRGB[1]<=SEUIL_GRIS &&*/ (tableauRGB[2]>=15 || tableauRGB[2]<90))
    //couleur = GRIS;

    return couleur;
}