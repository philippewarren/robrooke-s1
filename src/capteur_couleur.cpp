#include "capteur_couleur.h"

Adafruit_TCS34725 CapteurCouleur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

const uint16_t TOUTES_COULEURS[] = {ROUGE, JAUNE, VERT, TURQUOISE, BLEU, MAUVE};
const uint16_t COULEURS_OCTOGONE[] = {ROUGE, JAUNE, VERT, BLEU};
const uint16_t COULEURS_LETTRES[] = {ROUGE, VERT, BLEU};

const uint16_t BORNES_COULEUR[] = {15, 165};

    const int SEUIL_NOIR = 35;
    const int SEUIL_BLANC = 85;
    const int SEUIL_GRIS = 15;

void initialiserCapteurCouleur()
{
    if (CapteurCouleur.begin())
    {
        Serial.println("Capteur couleur branché");
    }
    else
    {
        Serial.println("Pas de capteur couleur ... verifiez la connection");
    }
    
    return;
}

void lireCapteurCouleur(uint8_t numeroDeCapteur, uint16_t tableauVide[4])
{    
    uint16_t rouge;
    uint16_t vert;
    uint16_t bleu;
    uint16_t sansCouleur;

    CapteurCouleur.getRawData(&rouge, &vert, &bleu, &sansCouleur);

    Serial.print(rouge);
    Serial.print("\t");
    Serial.print(vert);
    Serial.print("\t");
    Serial.print(bleu);
    Serial.print("\t");
    Serial.println(sansCouleur);
    
    tableauVide[0] = (uint16_t)(256*(float)rouge/sansCouleur);
    tableauVide[1] = (uint16_t)(256*(float)vert/sansCouleur);
    tableauVide[2] = (uint16_t)(256*(float)bleu/sansCouleur);
    tableauVide[3] = sansCouleur;

    rgbEnHsl(tableauVide);

    return;
}

int evaluerCouleur(uint16_t tableauRGB[4], const uint16_t couleursPossibles[] = TOUTES_COULEURS)
{
    // rgbEnHsl(tableauRGB);

    int couleur = 0;

    //Blanc, noir, gris
    if (tableauRGB[1]<=SEUIL_GRIS || (tableauRGB[2]<=SEUIL_NOIR || tableauRGB[2]>=SEUIL_BLANC))
    {
        // Blanc?
        if (tableauRGB[2]>=SEUIL_BLANC)
            couleur = BLANC;

        //Noir?
        else if (tableauRGB[2]<=SEUIL_NOIR)
            couleur = NOIR;

        //Gris?
        else
            couleur = GRIS;
    }
    else
    {
        // 6 couleurs
        if (couleursPossibles == TOUTES_COULEURS)
        {
            //Rouge?
            if (tableauRGB[0]>=330 || tableauRGB[0]<30)
                couleur = ROUGE;

            //Jaune?
            else if (tableauRGB[0]>=30 && tableauRGB[0]<90)
                couleur = JAUNE;

            //Vert?
            else if (tableauRGB[0]>=90 && tableauRGB[0]<150)
                couleur = VERT;

            //Turquoise?
            else if (tableauRGB[0]>=150 && tableauRGB[0]<210)
                couleur = TURQUOISE;

            //Bleu?
            else if (tableauRGB[0]>=210 && tableauRGB[0]<270)
                couleur = BLEU;

            //Mauve?
            else if (tableauRGB[0]>=270 && tableauRGB[0]<330)
                couleur = MAUVE;
        }

        // 4 couleurs
        else if (couleursPossibles == COULEURS_OCTOGONE)
        {
            //Rouge?
            if (tableauRGB[0]>=285 || tableauRGB[0]<45)
                couleur = ROUGE;

            //Jaune?
            else if (tableauRGB[0]>=40 && tableauRGB[0]<90)
                couleur = JAUNE;

            //Vert?
            else if (tableauRGB[0]>=90 && tableauRGB[0]<155)
                couleur = VERT;

            //Bleu?
            else if (tableauRGB[0]>=155 && tableauRGB[0]<285)
                couleur = BLEU;
        }
    }

    return couleur;
}

int obtenirCouleurPlancher()
{
    uint16_t tableau[4];
    lireCapteurCouleur(0,tableau);
    return evaluerCouleur(tableau,COULEURS_OCTOGONE);
}

void debugCapteurCouleur()
{
    static uint16_t tableau[4];
    static String nomCouleur;
    lireCapteurCouleur(0, tableau);
    
    Serial.print("R: ");
    Serial.print(tableau[0]);
    Serial.print("\tV: ");
    Serial.print(tableau[1]);
    Serial.print("\tB: ");
    Serial.print(tableau[2]);
    Serial.print("\tC: ");
    Serial.print(tableau[3]);
    Serial.print("\tCouleur: ");
    switch (evaluerCouleur(tableau, COULEURS_OCTOGONE))
    {
        case ROUGE:
            nomCouleur = "ROUGE";
            break;
        case BLEU:
            nomCouleur = "BLEU";
            break;
        case VERT:
            nomCouleur = "VERT";
            break;
        case JAUNE:
            nomCouleur = "JAUNE";
            break;
    }
    Serial.println(nomCouleur);
    delay(1000);
}